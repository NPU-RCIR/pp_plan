#include <bspline_opt/bspline_optimizer.h>
#include <bspline/non_uniform_bspline.h>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <visualization_msgs/Marker.h>
#include <traj_utils/planning_visualization.h>
#include <swarmtal_msgs/drone_pos_control_state.h>
#include <swarmtal_msgs/drone_pos_ctrl_cmd.h>
#include <swarmtal_msgs/drone_onboard_command.h>

using namespace fast_planner;
using namespace Eigen;

struct Config {
    double max_vel;
    double max_acc;
    double ctrl_pt_dist;
    int waypoint_num_;
    double waypoints_[50][3];

    static void loadParameters(Config &conf, const ros::NodeHandle &nh_priv) {
        nh_priv.param("optimization/max_vel", conf.max_vel, -1.0);
        nh_priv.param("optimization/max_acc", conf.max_acc, -1.0);
        nh_priv.param("optimization/control_points_distance", conf.ctrl_pt_dist, -1.0);

        nh_priv.param("optimization/waypoint_num", conf.waypoint_num_, -1);
        for (int i = 0; i < conf.waypoint_num_; i++) {
            nh_priv.param("optimization/waypoint" + to_string(i) + "_x", conf.waypoints_[i][0], -1.0);
            nh_priv.param("optimization/waypoint" + to_string(i) + "_y", conf.waypoints_[i][1], -1.0);
            nh_priv.param("optimization/waypoint" + to_string(i) + "_z", conf.waypoints_[i][2], -1.0);
        }
    }
};

struct PlanData {
    vector<Vector3d> pass_points;
    vector<Vector3d> pp_line;
    vector<MatrixXd> ctrl_pts;
    NonUniformBspline position_traj_, velocity_traj_, acceleration_traj_, yaw_traj_, yawdot_traj_, yawdotdot_traj_;
};

Config config;
PlanData my_plan;
BsplineOptimizer::Ptr bspline_optimizers_, bspline_optimizers_yaw_;
Eigen::Vector3d odom_pos_, odom_vel_;  // odometry state
Eigen::Quaterniond odom_orient_;
bool have_odom_, opti_success;
ros::Subscriber odom_sub_;
ros::Publisher cmd_pub_;
PlanningVisualization::Ptr visualization_;
swarmtal_msgs::drone_onboard_command cmd;

void optimize_pp();
vector<double> allocateTime(const vector<Vector3d> &wayPs, double conservativeness);
void getSamples(double& ts, const vector<Vector3d> &wayPs, vector<Vector3d>& point_set, vector<Vector3d>& start_end_derivatives);
void odometryCallback(const nav_msgs::OdometryConstPtr& msg);
void getWaypts(vector<Vector3d> &wypt, vector<int> &wyptidx);
void planYaw(const Vector3d& start_yaw);
void calcNextYaw(const double& last_yaw, double& yaw);
void pub_ctrl_cmd(double t);
void init_ctrl_cmd(swarmtal_msgs::drone_onboard_command &ctrl_cmd);


