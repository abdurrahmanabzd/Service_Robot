#!/bin/sh
xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
xterm -e "source devel/setup.bash; roslaunch pick_objects world.launch" &
sleep 5
xterm -e "source devel/setup.bash; roslaunch pick_objects amcl.launch" &
sleep 5
xterm -e "source devel/setup.bash; roslaunch pick_objects rviz_config.launch" &
sleep 5
xterm -e "source devel/setup.bash; rosrun using_markers add_markers_time"

