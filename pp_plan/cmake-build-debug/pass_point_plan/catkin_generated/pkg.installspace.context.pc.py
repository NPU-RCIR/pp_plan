# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "bspline;bspline_opt;traj_utils;message_runtime".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lplan_manage".split(';') if "-lplan_manage" != "" else []
PROJECT_NAME = "pass_point_plan"
PROJECT_SPACE_DIR = "/usr/local"
PROJECT_VERSION = "0.0.0"
