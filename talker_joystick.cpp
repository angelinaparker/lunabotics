// Teleop class using xbox xontroller connected to local computer.
// Used ROS tutorials to build the class https://wiki.ros.org/joy/Tutorials/WritingTeleopNode



#include "ros/ros.h" // include ROS library
#include <geometry_msgs/twist.h> // includes the twist msg so that we can publish twist commands
#include <sensor_msgs/Joy.h> // includes the joystick msg so that we can listen to the joy topic


// Create teleop class
class TeleopHades

{
public:
    TeleopHades();
    
private:
    
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy); // Define joCallback function that takes a Joymsg

  ros::NodeHandle nh_; // ROS node handle

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_; // ROS Publisher
  ros::Subscriber joy_sub_; // ROS Subscriber

};
    

TeleopHades::TeleopHades():
// Define linear_ and angular_ variables that are used to define which axis the joystick
// will control our turtle
  linear_(1),
  angular_(2)
{
// Check the parameter server for new scaler values for driving vehicle
  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);
    

    // Create publisher that will advertise on cmd_vel topic
    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("hades1/cmd_vel", 1);

    // Subscribe to the joystick topic for input to drive the turtle. Up to 10 messages will be buffered.
    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopHades::joyCallback, this);

}

void TeleopHades::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
    geometry_msgs::Twist twist; //
    twist.angular.z = a_scale_*joy->axes[angular_];
    twist.linear.x = l_scale_*joy->axes[linear_];
    vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "teleop_turtle"); // Initialize ROS node
    TeleopTurtle teleop_turtle;

    ros::spin();
}
















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "talker");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
