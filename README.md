# Service Robot Project
A project to implement localization and navigation to a mobile robot with ROS packages.

In this project, I have used my own simple robot and turtlebot robot for testing the code. You could change the robot by changing the arguments in script files.


**Localization**

Localization was made with ***Adaptive Monte Carlo Localization*** algorithm, which help localizing the robot using particle filters. The algorithm estimates the robots position while it's moving in the environment using sensor data (ex. odometry, laser scan). AMCL generates distribution of likely states which are called *particles*. The more the particle is likely to be accurate the more *wieght* it has. Particles with less weight end up removed. This way, with time, the robot predicts a more presice state of its position. 
Documentation on AMCL ROS package: http://wiki.ros.org/amcl


**Navigation**

Navigation was achieved with ***ROS 2D navigation stack***. It's based on a Uniform Cost Search algorithm, *Dijkstra's algorithm* to be precise. It plans a path from the robots current position to the goal position. It also plans a new path whenever the robot encounters an obstacle. This navigation stack is implemented in the project using "move_base" package. 
Documentation on ROS navigation stack: http://wiki.ros.org/navigation


**Markers**

Markers are used in this project for visualization on *RViz*. Markers represent virtual objects that are being picked up and droped at desired location by the robot. 


*Note:* For testing the project in your environment, clone the repository to your catkin workspace. use the shell script files in the "scripts" file to launch the code with ease. 
