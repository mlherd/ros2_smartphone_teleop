# ros2_smartphone_teleop
ROS2 Smartphone Teleop Package
This packages allows you to remote control your robot's mobile base.
Uses hand gustures to control the robot.
A simple wireless solution test robots. Tested with ROS2 Eloquent.

Link to the project video: https://www.linkedin.com/embed/feed/update/urn:li:ugcPost:6651575595417370624

# 1.Build Instructions
 ```
 source /opt/ros/<ros2_distro>/setup.bash
 cd <your_ros2_ws>/
 git clone https://github.com/mlherd/ros2_smartphone_teleop.git
 cd ros2_smartphone_teleop
 colcon build --sysmlink-install
 source install/setup.bash
 ```
 
# 2.Usage
- ## 2.1 Robot Bringup
  Bring up your physical robot or simulation. Make sure it subscribes to `/cmd_vel` topic.
- ## 2.2 Run smartphone_teleop
  ```ros2 run ros2 run smartphone_teleop smartphone_teleop```
- ## 2.2 Step 3 Smartphone App
  - Install and Start [HyperIMU](https://play.google.com/store/apps/details?id=com.ianovir.hyper_imu&hl=en_US) on your phone.
  
  Warning: Make sure your phone is coneected to the same network as your robot.
  
  - Enable accelerometer sensor in the app. `sensorlist->accelerometer`
  
  - Set the data stream protocol to UDP `settings->stream protocal`
  
  - set sampling rate to 50ms. `settings->sample rate (ms)`
  
  - set server IP adrees to your robots or host computer IP address `settings->server ip address`
  
  - set server port number to 5000 `settings->server port number`
  
  - Start streaming data

# 3.Nodes

- ## 3.1 smartphone_teleop

  - ## 3.1.1 Published Topics
    - cmd_vel ([geometry_msgs/Twist](http://docs.ros.org/api/geometry_msgs/html/msg/Twist.html))
      - A stream of velocity commands meant for execution by a mobile base.
