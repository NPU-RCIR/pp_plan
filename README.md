# pp_plan
A lightweight motion planning algorithm according to Fast_planner, no obstacle avoidance function, but according to the input sequence of points to plan a smooth trajectory.
# pp_plan
A lightweight motion planning algorithm according to Fast_planner, no obstacle avoidance function, but according to the input sequence of points to plan a smooth trajectory.

## 1. Quick Start
```
  sudo apt-get install libnlopt-dev libarmadillo-dev
  cd ${YOUR_WORKSPACE_PATH}/src
  git clone https://github.com/NPU-RCIR/co-pp_plan.git
  cd ../
  catkin_make
```

## 2. Run

```
  source devel/setup.bash
  roslaunch pass_point_plan plan_pp.launch
```
https://github.com/NPU-RCIR/pp_plan/blob/master/pp_plan/img/result.png
## 3. Change waypoints
You can modify the number and coordinates of path points in the launch file to make the final optimized trajectory pass through these path points and meet the requirements of smoothness and dynamic feasibility.

https://github.com/NPU-RCIR/pp_plan/blob/master/pp_plan/img/change_waypoints.png
