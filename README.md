# ros2_smartphone_teleop
ROS2 Smartphone Teleop Package

# 1. Build Instrcutions
 ```
 source /opt/ros/<ros2_distro>/setup.bash
 cd <your_ros2_ws>/
 git clone https://github.com/mlherd/ros2_smartphone_teleop.git
 cd smartphone_teleop
 colcon build --sysmlink-install
 source install/setup.bash
 ```
 
# 2.Usage
- ## 2.1 Robot Bringup
  Bring up your robot in phsical robot or simulation. Make sure it subscribes to `/cmd_vel` topic.
- ## 2.2 ROS2
  ```ros2 run ros2 run smartphone_teleop smartphone_teleop```
- ## 2.2 Step 3 Smartphone App
  - Install and Start [HyperIMU](https://play.google.com/store/apps/details?id=com.ianovir.hyper_imu&hl=en_US) on your phone.
  
  Warning: `Make sure your phone is coneected to the same network as your robot.`
  
  - Enable accelerometer sensor in the app.
  
  - Start streaming data

# 3.Nodes

- ## 3.1 smartphone_teleop

  - ## 3.1.1 Published Topics
    - cmd_vel ([geometry_msgs/Twist](http://docs.ros.org/api/geometry_msgs/html/msg/Twist.html))
      - A stream of velocity commands meant for execution by a mobile base.


