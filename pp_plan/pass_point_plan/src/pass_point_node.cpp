#include <pass_point_node.h>
#define sign(x) ( ((x) <0 )? -1 : (((x)> 0) ? 1 : 0 ))

int main(int argc, char** argv) {
    ros::init(argc, argv, "pass_point_node");
    ros::NodeHandle nh("~");
    odom_sub_ = nh.subscribe("/odom_world", 1, &odometryCallback);
    cmd_pub_  = nh.advertise<swarmtal_msgs::drone_onboard_command>("/planning/command", 10);
    visualization_.reset(new PlanningVisualization(nh));
    Config::loadParameters(config, nh);
    bspline_optimizers_.reset(new BsplineOptimizer);
    bspline_optimizers_->setParam(nh);
    bspline_optimizers_yaw_.reset(new BsplineOptimizer);
    bspline_optimizers_yaw_->setParam(nh);
    double time_s;
    init_ctrl_cmd(cmd);
    while (ros::ok())
    {
      if(!opti_success)
      {
          optimize_pp();
          Vector3d start_yaw = Vector3d(0,0,0);
          planYaw(start_yaw);
          time_s = ros::Time::now().toSec();
      }
        visualization_->drawBspline(my_plan.position_traj_, 0.1, Eigen::Vector4d(1.0, 0, 0.0, 1), false, 0.2,
                                    Eigen::Vector4d(0, 0, 1, 1));
        visualization_->displayLineStrip(my_plan.pp_line, 0.05, Eigen::Vector4d(0.0, 1.0, 0.0, 1), 0);
      if(opti_success)
      {
          double t_cur = ros::Time::now().toSec() - time_s;
          pub_ctrl_cmd(t_cur);
      }
        ros::spinOnce();
        ros::Duration(0.02).sleep();
    }

    return 0;
}

void optimize_pp()
{
    double ts = config.ctrl_pt_dist / config.max_vel;
    vector<Vector3d> point_set, start_end_derivatives;
    vector<Vector3d> waypts;
    vector<int> wayptsidx;
    getWaypts(waypts, wayptsidx);
    my_plan.pass_points = waypts;
    getSamples(ts, waypts, point_set, start_end_derivatives);
    my_plan.pp_line = point_set;
    Eigen::MatrixXd ctrl_pts;
    NonUniformBspline::parameterizeToBspline(ts, point_set, start_end_derivatives, ctrl_pts);
    NonUniformBspline init(ctrl_pts, 3, ts);
//    for(int i=0; i<waypts.size(); i++)
//        std::cout<<"way points: "<<waypts[i].transpose()<<" index: "<<wayptsidx[i]<<std::endl;
    bspline_optimizers_->setWaypoints(waypts, wayptsidx);
    int cost_function = BsplineOptimizer::SMOOTHNESS | BsplineOptimizer::FEASIBILITY;
    ctrl_pts = bspline_optimizers_->BsplineOptimizeTraj(ctrl_pts, ts, cost_function, 1, 1);
//    for(int i=0; i<ctrl_pts.rows(); i++)
//        std::cout<<ctrl_pts.row(i)<<std::endl;
    NonUniformBspline pos = NonUniformBspline(ctrl_pts, 3, ts);
    my_plan.position_traj_ = pos;
    my_plan.velocity_traj_     = my_plan.position_traj_.getDerivative();
    my_plan.acceleration_traj_ = my_plan.velocity_traj_.getDerivative();
    opti_success = true;
}

void getWaypts(vector<Vector3d> &wypts, vector<int> &wyptsidx)
{
    int idx = 0;
    if(have_odom_)
    {
        wypts.push_back(odom_pos_);
        wyptsidx.push_back(0);
        idx = 1;
    }
    for (int i=0; i<config.waypoint_num_; i++)
    {
        Vector3d wypt;
        wypt.x() = config.waypoints_[i][0];
        wypt.y() = config.waypoints_[i][1];
        wypt.z() = config.waypoints_[i][2];
        wypts.push_back(wypt);
        wyptsidx.push_back(idx);
        idx++;
    }
}

vector<double> allocateTime(const vector<Vector3d> &wayPs, double conservativeness)
{
    int N = (int)(wayPs.size()) - 1;
    std::vector<double> durations;

    if (N > 0)
    {
        durations.reserve(N);
        durations.clear();

        double speed = config.max_vel / conservativeness;
        double accRate = config.max_acc / conservativeness;

        Eigen::Vector3d p0, p1;
        double dtxyz, D, acct, accd, dcct, dccd, t1, t2, t3;
        for (int k = 0; k < N; k++)
        {
            double vel, acc, dis;
            p0 = wayPs[k];
            p1 = wayPs[k + 1];
            D = (p1 - p0).norm();

            dis = D;
            vel = speed;
            acc = accRate;

            acct = vel / acc;
            accd = (acc * acct * acct / 2);
            dcct = vel / acc;
            dccd = acc * dcct * dcct / 2;

            if (D < accd + dccd)
            {
                t1 = sqrt(acc * dis) / acc;
                t2 = (acc * t1) / acc;
                dtxyz = t1 + t2;
            } else
            {
                t1 = acct;
                t2 = (dis - accd - dccd) / vel;
                t3 = dcct;
                dtxyz = t1 + t2 + t3;
            }
            durations.push_back(dtxyz);
        }
    }

    return durations;
}

void getSamples(double& ts, const vector<Vector3d> &wayPs, vector<Vector3d>& point_set, vector<Vector3d>& start_end_derivatives)
{
    vector<double> t_seg;
    t_seg = allocateTime(wayPs, 1.0);
    double T_sum=0, T_step=0;
    for(int i=0; i<t_seg.size(); i++)
        T_sum = T_sum + t_seg[i];
    int K = floor(T_sum / ts);
    ts    = T_sum / double(K + 1);
    Eigen::Vector3d p0, p1;
    for(int i=0; i<t_seg.size(); i++)
    {
        p0 = wayPs[i];
        p1 = wayPs[i + 1];
        double t_s = t_seg[i];
        Eigen::Vector3d pt;

        for (double ti = T_step; ti < T_step + t_s; ti += ts) {
            for(int j=0; j<3; j++)
            {
                double dis, vel, acc, acct;
                vel = config.max_vel*abs((p1-p0).normalized()(j));
                acc = config.max_acc*abs((p1-p0).normalized()(j)) + 1e-5;
                acct = vel/acc;
                dis = (p1-p0)(j);
                if((acc*acct*acct)>=abs(dis))
                {
                    double a = 4 * abs(dis) / (t_s * t_s);
                    //std::cout<<" a1: "<<a<<" abs(dis): "<<abs(dis)<<" ti: "<<ti<<std::endl;
                    if (ti < (T_step + t_s / 2.0)) pt(j) = p0(j) + 1.0 / 2.0 * a * (ti-T_step) * (ti-T_step) * sign(dis);
                    else pt(j) = p1(j) - 1.0 / 2.0 * a * pow((T_step + t_s - ti), 2) * sign(dis);
                } else {
                    double v = abs(dis)/(t_s-acct);
                    double a = v/acct;
                    //std::cout<<" a2: "<<a<<" ti: "<<ti<<std::endl;
                    if(ti < (T_step+acct)) pt(j) = p0(j) + 1.0 / 2.0 * a * (ti-T_step) * (ti-T_step) * sign(dis);
                    else if (ti < (T_step+t_s-acct)) pt(j) = p0(j) + 1.0 / 2.0 * a * acct * acct * sign(dis) + (ti-T_step-acct)*v*sign(dis);
                    else pt(j) = p1(j) - 1.0 / 2.0 * a * pow((T_step + t_s - ti), 2) * sign(dis);
                }
            }
            point_set.push_back(pt);
            //std::cout<<pt.transpose()<<std::endl;
        }
        T_step = T_step+t_s;
    }
    Eigen::Vector3d start_vel, end_vel, start_acc, end_acc;
    start_vel << 0,0,0;
    end_vel = start_vel;
    start_acc << 0,0,0;
    end_acc = start_acc;
    start_end_derivatives.push_back(start_vel);
    start_end_derivatives.push_back(end_vel);
    start_end_derivatives.push_back(start_acc);
    start_end_derivatives.push_back(end_acc);
}

void odometryCallback(const nav_msgs::OdometryConstPtr& msg) {
    odom_pos_(0) = msg->pose.pose.position.x;
    odom_pos_(1) = msg->pose.pose.position.y;
    odom_pos_(2) = msg->pose.pose.position.z;

    odom_vel_(0) = msg->twist.twist.linear.x;
    odom_vel_(1) = msg->twist.twist.linear.y;
    odom_vel_(2) = msg->twist.twist.linear.z;

    odom_orient_.w() = msg->pose.pose.orientation.w;
    odom_orient_.x() = msg->pose.pose.orientation.x;
    odom_orient_.y() = msg->pose.pose.orientation.y;
    odom_orient_.z() = msg->pose.pose.orientation.z;

    have_odom_ = true;
}

void planYaw(const Vector3d& start_yaw) {
    ROS_INFO("plan yaw");
    auto t1 = ros::Time::now();
    // calculate waypoints of heading

    auto&  pos      = my_plan.position_traj_;
    double duration = pos.getTimeSum();

    double dt_yaw  = 0.3;
    int    seg_num = ceil(duration / dt_yaw);
    dt_yaw         = duration / seg_num;

    const double            forward_t = 2.0;
    double                  last_yaw  = start_yaw(0);
    vector<Eigen::Vector3d> waypts;
    vector<int>             waypt_idx;

    // seg_num -> seg_num - 1 points for constraint excluding the boundary states

    for (int i = 0; i < seg_num; ++i) {
        double          tc = i * dt_yaw;
        Eigen::Vector3d pc = pos.evaluateDeBoorT(tc);
        double          tf = min(duration, tc + forward_t);
        Eigen::Vector3d pf = pos.evaluateDeBoorT(tf);
        Eigen::Vector3d pd = pf - pc;

        Eigen::Vector3d waypt;
        if (pd.norm() > 1e-6) {
            waypt(0) = atan2(pd(1), pd(0));
            waypt(1) = waypt(2) = 0.0;
            calcNextYaw(last_yaw, waypt(0));
        } else {
            waypt = waypts.back();
        }
        waypts.push_back(waypt);
        waypt_idx.push_back(i);
    }

    // calculate initial control points with boundary state constraints

    Eigen::MatrixXd yaw(seg_num + 3, 1);
    yaw.setZero();

    Eigen::Matrix3d states2pts;
    states2pts << 1.0, -dt_yaw, (1 / 3.0) * dt_yaw * dt_yaw, 1.0, 0.0, -(1 / 6.0) * dt_yaw * dt_yaw, 1.0,
            dt_yaw, (1 / 3.0) * dt_yaw * dt_yaw;
    yaw.block(0, 0, 3, 1) = states2pts * start_yaw;

    Eigen::Vector3d end_v = my_plan.velocity_traj_.evaluateDeBoorT(duration - 0.1);
    Eigen::Vector3d end_yaw(atan2(end_v(1), end_v(0)), 0, 0);
    calcNextYaw(last_yaw, end_yaw(0));
    yaw.block(seg_num, 0, 3, 1) = states2pts * end_yaw;

    // solve
    bspline_optimizers_yaw_->setWaypoints(waypts, waypt_idx);
    int cost_func = BsplineOptimizer::SMOOTHNESS | BsplineOptimizer::WAYPOINTS;
    yaw           = bspline_optimizers_yaw_->BsplineOptimizeTraj(yaw, dt_yaw, cost_func, 1, 1);

    // update traj info
    my_plan.yaw_traj_.setUniformBspline(yaw, 3, dt_yaw);
    my_plan.yawdot_traj_    = my_plan.yaw_traj_.getDerivative();
    my_plan.yawdotdot_traj_ = my_plan.yawdot_traj_.getDerivative();
}

void calcNextYaw(const double& last_yaw, double& yaw) {
    // round yaw to [-PI, PI]

    double round_last = last_yaw;

    while (round_last < -M_PI) {
        round_last += 2 * M_PI;
    }
    while (round_last > M_PI) {
        round_last -= 2 * M_PI;
    }

    double diff = yaw - round_last;

    if (fabs(diff) <= M_PI) {
        yaw = last_yaw + diff;
    } else if (diff > M_PI) {
        yaw = last_yaw + diff - 2 * M_PI;
    } else if (diff < -M_PI) {
        yaw = last_yaw + diff + 2 * M_PI;
    }
}

void pub_ctrl_cmd(double t)
{
    Vector3d pt = my_plan.position_traj_.evaluateDeBoor(t);
    Vector3d v  = my_plan.velocity_traj_.evaluateDeBoor(t);
    Vector3d a  = my_plan.acceleration_traj_.evaluateDeBoor(t);
    VectorXd yaw = my_plan.yaw_traj_.evaluateDeBoor(t);

    cmd.param1 = int(pt.x()*10000);
    cmd.param2 = int(pt.y()*10000);
    cmd.param3 = int(pt.z()*10000);
    cmd.param4 = int(yaw[0]*10000);
    cmd.param5 = int(v.x()*10000);
    cmd.param6 = int(v.y()*10000);
    cmd.param8 = int(a.x()*10000);
    cmd.param9 = int(a.y()*10000);
    cmd_pub_.publish(cmd);
}

void init_ctrl_cmd(swarmtal_msgs::drone_onboard_command &ctrl_cmd)
{
    ctrl_cmd.command_type = ctrl_cmd.CTRL_POS_COMMAND;
    ctrl_cmd.param1 = 0;
    ctrl_cmd.param2 = 0;
    ctrl_cmd.param3 = 0;
    ctrl_cmd.param4 = NAN;
    ctrl_cmd.param5 = 0;
    ctrl_cmd.param6 = 0;
    ctrl_cmd.param7 = 0;
    ctrl_cmd.param8 = 0;
    ctrl_cmd.param9 = 0;
    ctrl_cmd.param10 = 0;
}