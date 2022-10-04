#!/bin/sh
xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/pick_objects/worlds/indoor.world" &
sleep 5
xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/pick_objects/maps/map.yaml" &
sleep 5
xterm -e "source devel/setup.bash; roslaunch pick_objects rviz_config.launch" &
sleep 5
xterm -e "source devel/setup.bash; rosrun pick_objects pick_objects" &
sleep 5
xterm -e "source devel/setup.bash; rosrun using_markers add_markers"

