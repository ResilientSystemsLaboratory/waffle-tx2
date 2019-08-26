#include "navigation_node.hpp"

namespace TurtleBot3Navigation
{
  void cloud_callback(const sensor_msgs::PointCloud2Ptr msg)
  {
    hasNoObsticleCloud = false;
    assert (msg != 0);
    //ROS_INFO("Processing Cloud Message!");

    //Update the point cloud used for planning
    obstacleCloud = msg;
    //ROS_INFO("DOES ASSIGNMENT WORK?");
  }
  
  void createBoundingboxAndPub(ros::Publisher& pub, float minimumViewPoint, float maximumViewPoint, 
      float yAxisBoundarySlope, float yAxisBoundaryIntercept, float zAxisBoundarySlope, float zAxisBoundaryIntercept)
  {
    nav_msgs::Path path; 
    geometry_msgs::PoseStamped pose;
    path.header.stamp = ros::Time::now();
    path.header.frame_id = "base_link";
      
    std::vector<float> extremes(6,0);

    extremes[0] = minimumViewPoint;
    extremes[1] = maximumViewPoint;
    extremes[2] = yAxisBoundarySlope*minimumViewPoint+yAxisBoundaryIntercept;
    extremes[3] = yAxisBoundarySlope*maximumViewPoint+yAxisBoundaryIntercept;
    extremes[4] = zAxisBoundarySlope*minimumViewPoint+zAxisBoundaryIntercept;
    extremes[5] = zAxisBoundarySlope*maximumViewPoint+zAxisBoundaryIntercept;

    //Close Left Bottom
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[0];
    pose.pose.position.y = extremes[2];
    pose.pose.position.z = -extremes[4];
    path.poses.push_back(pose);
    
    //Far Left Bottom
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[1];
    pose.pose.position.y = extremes[3];
    pose.pose.position.z = -extremes[5];
    path.poses.push_back(pose);

    //Far Right Bottom
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[1];
    pose.pose.position.y = -extremes[3];
    pose.pose.position.z = -extremes[5];
    path.poses.push_back(pose);
    
    //Close Right Bottom
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[0];
    pose.pose.position.y = -extremes[2];
    pose.pose.position.z = -extremes[4];
    path.poses.push_back(pose);
  
    //Close Left Bottom
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_base";
    pose.pose.position.x = extremes[0];
    pose.pose.position.y = extremes[2];
    pose.pose.position.z = -extremes[4];
    path.poses.push_back(pose);

    //Close Left Top
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[0];
    pose.pose.position.y = extremes[2];
    pose.pose.position.z = extremes[4];
    path.poses.push_back(pose);

    //Far Left Top
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[1];
    pose.pose.position.y = extremes[3];
    pose.pose.position.z = extremes[5];
    path.poses.push_back(pose);
    
    //Far Left Bottom
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[1];
    pose.pose.position.y = extremes[3];
    pose.pose.position.z = -extremes[5];
    path.poses.push_back(pose);
    
    //Far Left Top
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[1];
    pose.pose.position.y = extremes[3];
    pose.pose.position.z = extremes[5];
    path.poses.push_back(pose);

    //Far Right Top
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[1];
    pose.pose.position.y = -extremes[3];
    pose.pose.position.z = extremes[5];
    path.poses.push_back(pose);
    
    //Far Right Bottom
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[1];
    pose.pose.position.y = -extremes[3];
    pose.pose.position.z = -extremes[5];
    path.poses.push_back(pose);
    
    //Far Right Top
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[1];
    pose.pose.position.y = -extremes[3];
    pose.pose.position.z = extremes[5];
    path.poses.push_back(pose);

    //Close Right Top
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[0];
    pose.pose.position.y = -extremes[2];
    pose.pose.position.z = extremes[4];
    path.poses.push_back(pose);
    
    //Close Right Bottom
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[0];
    pose.pose.position.y = -extremes[2];
    pose.pose.position.z = -extremes[4];
    path.poses.push_back(pose);
    
    //Close Right Top
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[0];
    pose.pose.position.y = -extremes[2];
    pose.pose.position.z = extremes[4];
    path.poses.push_back(pose);
    
    //Close Left Top
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "base_link";
    pose.pose.position.x = extremes[0];
    pose.pose.position.y = extremes[2];
    pose.pose.position.z = extremes[4];
    path.poses.push_back(pose);

    //Publish the shape
    pub.publish(path);
  }
  
  void createPathAndPub(ros::Publisher& pub)
  {
    nav_msgs::Path path; 
    path.header.stamp = ros::Time::now();
    path.header.frame_id = "base_link";
    for(int i = 0; i < 15; i++)
    {
      geometry_msgs::PoseStamped pose; 
      pose.header.stamp = ros::Time::now();
      pose.header.frame_id = "base_link";
      pose.pose.position.x = i;
      pose.pose.position.y = 0;
      pose.pose.position.z = 0;
      path.poses.push_back(pose);
    }
    pub.publish(path);
  }
  
  void createCloudAndPub(ros::Publisher& pub)
  {
    sensor_msgs::PointCloud2Ptr cloud;
    cloud.reset(new sensor_msgs::PointCloud2);
    cloud->header.frame_id = "base_link";
    cloud->is_bigendian = false;
    cloud->is_dense = false;
    cloud->width = NUMBER_OF_RRT_NODES;
    cloud->height = 1;
    
    sensor_msgs::PointCloud2Modifier modifier(*cloud);
    modifier.setPointCloud2Fields(4, "x", 1, sensor_msgs::PointField::FLOAT32, 
        "y", 1, sensor_msgs::PointField::FLOAT32,
        "z", 1, sensor_msgs::PointField::FLOAT32,
        "rgb", 1, sensor_msgs::PointField::FLOAT32);
    sensor_msgs::PointCloud2Iterator<float> iter_x(*cloud, "x"),
      iter_y(*cloud, "y"),
      iter_z(*cloud, "z"),
      iter_rgb(*cloud,"rgb");
   
    for (size_t i = 0; i < (cloud->width)*(cloud->height); ++i) 
    {
      *iter_x = (float) i;
      *iter_y = (float) i;
      *iter_z = (float) i;
      *iter_rgb = 0xFF0000;
      ++iter_x; ++iter_y; ++iter_z; ++iter_rgb;
    }
  pub.publish(cloud); 
  }
   
  float generateRandomValue(float minimum, float maximum)
  {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dis(minimum, maximum); // distribution in range [min, max]
    return dis(rng);
  } 
  std::vector<float> generateRandomValues(float quantity, float minimum, float maximum)
  {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dis(minimum, maximum); // distribution in range [min, max]
    std::vector<float> numbers(quantity, 0);
    for (float& i : numbers)
      i = dis(rng);
    return numbers;
  }

  float calcDistBetweenPoints(sensor_msgs::PointCloud2Ptr cloud, size_t cloudPointIndex, float point_x, float point_y, float point_z)
  {
    //Create iterators to walk through the point cloud
    sensor_msgs::PointCloud2Iterator<float> iter_x(*cloud, "x"),
      iter_y(*cloud, "y"),
      iter_z(*cloud, "z");
    iter_x = iter_x + cloudPointIndex;
    iter_y = iter_y + cloudPointIndex;
    iter_z = iter_z + cloudPointIndex;

    float x = point_x-(*iter_x);
    float xx = x*x;
    //ROS_INFO("X: %f, XX: %f", x, xx);
    float y = point_y-(*iter_y);
    float yy = y*y;
    //ROS_INFO("Y: %f, YY: %f", y, yy);
    float z = point_z-(*iter_z);
    float zz = z*z; 
    //ROS_INFO("Z: %f, ZZ: %f", z, zz);
    //use euclidean norm to find distance between the two points
    float dist = sqrt( xx + yy + zz);
    //ROS_INFO("Distance: %f", dist);
    return dist;
  }

  float calcDistBetweenPoints(float point_x1, float point_y1, float point_z1, float point_x2, float point_y2, float point_z2)
  {
    float x = point_x2-point_x1;
    float xx = x*x;
    //ROS_INFO("X: %f, XX: %f", x, xx);
    float y = point_y2-point_y1;
    float yy = y*y;
    //ROS_INFO("Y: %f, YY: %f", y, yy);
    float z = point_z2-point_z1;
    float zz = z*z; 
    //ROS_INFO("Z: %f, ZZ: %f", z, zz);
    //use euclidean norm to find distance between the two points
    float dist = sqrt( xx + yy + zz);
    //ROS_INFO("Distance: %f", dist);
    return dist;
  }
  
  size_t findClosestPoint(sensor_msgs::PointCloud2Ptr cloud, size_t nodesGenerated, float point_x, float point_y, float point_z)
  { 
    //set index to first point and minimum distance to the first point in the cloud
    size_t index = 0;
    float distMin = calcDistBetweenPoints(cloud, 0, point_x, point_y, point_z);
    
    //walk through the point cloud checking for the minimum distance to the given point
    for(size_t i = 1; i < nodesGenerated; i++)
    {
      //use euclidean norm to find distance between the two points
      float dist = calcDistBetweenPoints(cloud, i, point_x, point_y, point_z);
      //Compare the current minimum to the newly measured distance
      if(distMin > dist)
      {
        //if new minimum, index and save new minimum distance
        index = i;
        distMin = dist;
      }
    }
    return index;
  }

  bool noCollision(sensor_msgs::PointCloud2Ptr cloud, float point_x, float point_y, float point_z, float minAllowedDistance)
  {
    sensor_msgs::PointCloud2Iterator<float> iter_x(*cloud, "x"),
      iter_y(*cloud, "y"),
      iter_z(*cloud, "z");
    for (size_t i = 0; i < (cloud->width)*(cloud->height); ++i) 
    {
      float dist = calcDistBetweenPoints(cloud, i, point_x, point_y, point_z);
      if(dist < minAllowedDistance)
      {
        ROS_INFO("Collision Detected %f < %f", dist, minAllowedDistance);
        return false;
      }
      ++iter_x; ++iter_y; ++iter_z;
    }
    return true;
  }
  
  bool noCollision(sensor_msgs::PointCloud2Ptr cloud, float point_x1, float point_y1, float point_z1, float point_x2, float point_y2, float point_z2, float minAllowedDistance, float stepDistance)
  {
    //Calculate the Total Distance
    float dist = calcDistBetweenPoints(point_x1, point_y1, point_z1, point_x2, point_y2, point_z2);
    //Calculate the Unit Vector 
    float dx = (point_x2 - point_x1)/dist;
    float dy = (point_y2 - point_y1)/dist;
    float dz = (point_z2 - point_z1)/dist;
    //initial Point
    float x = point_x1;
    float y = point_y1;
    float z = point_z1;

    for(size_t i = 0; i < ceil(dist/stepDistance); i++)
    {
      if(noCollision(cloud, x, y, z, minAllowedDistance))
      {
        if( stepDistance > calcDistBetweenPoints(x, y, z, point_x2, point_y2, point_z2))
        {
          x = point_x2;
          y = point_y2;
          z = point_z2;
        } else {
          x += stepDistance*dx;
          y += stepDistance*dy;
          z += stepDistance*dz;
        }
      } else {
        return false;
      }
    }
    return false;
  }

  sensor_msgs::PointCloud2Ptr generateRandomInViewCloud(float minimumViewPoint, float maximumViewPoint, 
      float yAxisBoundarySlope, float yAxisBoundaryIntercept, float zAxisBoundarySlope, float zAxisBoundaryIntercept)
  {
    //ROS_INFO("Started Generating Point Cloud In Camera View!");
    //create a new point cloud with a pointer
    sensor_msgs::PointCloud2Ptr cloud;
    cloud.reset(new sensor_msgs::PointCloud2);
    //ROS_INFO("New Point Cloud Initialised!");
    //Set the frame of the point cloud
    cloud->header.frame_id = "base_link";
    //Set 
    cloud->is_bigendian = false;
    //Set
    cloud->is_dense = false;
    //Since the cloud is unordered, the width is set to 1
    cloud->width = NUMBER_OF_RRT_NODES;
    //Since the cloud is unordered, the height is set to the number of points
    cloud->height = 1;
    //Create a modifier to edit the new point cloud
    sensor_msgs::PointCloud2Modifier modifier(*cloud);
    //ROS_INFO("Created Point Cloud Modifier!");
    //Use the modifier to set the fields in the point cloud
    modifier.setPointCloud2Fields(6, "x", 1, sensor_msgs::PointField::FLOAT32, 
        "y", 1, sensor_msgs::PointField::FLOAT32,
        "z", 1, sensor_msgs::PointField::FLOAT32,
        "rgb", 1, sensor_msgs::PointField::FLOAT32,
        "parentIndex", 1, sensor_msgs::PointField::UINT32,
        "cost", 1, sensor_msgs::PointField::FLOAT32);
    //ROS_INFO("Created Point Cloud Fields!");
    //Create the iterators that will walk through and set each point
    sensor_msgs::PointCloud2Iterator<float> iter_x(*cloud, "x"),
      iter_y(*cloud, "y"),
      iter_z(*cloud, "z"),
      iter_rgb(*cloud,"rgb"),
      iter_pi(*cloud, "parentIndex"),
      iter_c(*cloud, "cost");
    //ROS_INFO("Created initial Point Cloud for generation!");
    //Set the first point as the current location of the robot
    *iter_x = 0; 
    *iter_x = 0; 
    *iter_x = 0; 
    *iter_rgb = 0xFF0000;
    *iter_pi = 0;
    *iter_c = 0;
    //ROS_INFO("Created initial Point in point cloud!");
    //ROS_INFO("Point: (%f ,%f, %f) Parent Index: %f", *iter_x, *iter_y, *iter_z, *iter_pi);
    ++iter_x; ++iter_y; ++iter_z; ++iter_rgb; ++iter_pi; ++iter_c;
    //Keep track of the amount of RRT Nodes
    size_t numberOfNodes = 1;

    //create the iterators that will acess a point given an index
    sensor_msgs::PointCloud2Iterator<float> it_x(*cloud, "x"),
      it_y(*cloud, "y"),
      it_z(*cloud, "z");
    //ROS_INFO("Created iterators for indexing!");
    //Generate the x coordinates
    vector<float> x_points = generateRandomValues(((cloud->width)*(cloud->height))-1, minimumViewPoint, maximumViewPoint);
    //ROS_INFO("Genorated x-axis coordinate points!");
   size_t pointCount = 1;
    for (float& x : x_points)
    {
      float yExtreme = yAxisBoundarySlope*(x)+yAxisBoundaryIntercept; 
      float y = generateRandomValue(-yExtreme, yExtreme);
      float zExtreme = zAxisBoundarySlope*(x)+zAxisBoundaryIntercept; 
      float z = generateRandomValue(-zExtreme, zExtreme);
      size_t index = findClosestPoint(cloud, numberOfNodes, x, y, z);      
      float dist = calcDistBetweenPoints(cloud, index, x, y, z);
      //ROS_INFO("Random Point: (%f ,%f, %f) Parent Index: %lu Distance: %f", x, y, z, (unsigned long) index, dist);
      
      float x_p = *(it_x + index);
      float y_p = *(it_y + index);
      float z_p = *(it_z + index);
      //ROS_INFO("Parent Point: (%f ,%f, %f)", x_p, y_p, z_p);
     
      float dx = (x - x_p)/dist;
      float dy = (y - y_p)/dist;
      float dz = (z - z_p)/dist;
      //ROS_INFO("Unit Vector: (%f ,%f, %f)", dx, dy, dz);
    
      //stringstream ss;
      //ss << "Obstacle Cloud " << obstacleCloud << endl; 
      //ROS_INFO("%s",ss.str().c_str());
      
      if(noCollision(obstacleCloud, x_p, y_p, z_p, x_p + dx, y_p + dy, z_p + dz, COLLISION_DISTANCE, COLLISION_STEP_DISTANCE))
      {
      *iter_x = x_p + dx;
      *iter_y = y_p + dy;
      *iter_z = z_p + dz;
      *iter_pi = index;
      *iter_c = dist;

      ROS_INFO("Accepted Point (%lu of %lu): (%f ,%f, %f) Parent Index: %lu", pointCount, x_points.size(), *iter_x, *iter_y, *iter_z, (unsigned long) *iter_pi);
      *iter_rgb = 0x00FF00;
      ++iter_x; ++iter_y; ++iter_z; ++iter_rgb; ++iter_pi; ++iter_c; ++numberOfNodes; ++pointCount;
      } else {
      /*
      *iter_x = x_p + dx;
      *iter_y = y_p + dy;
      *iter_z = z_p + dz;
      *iter_pi = index;
      *iter_c = dist;

      ROS_INFO("Rejected Point (%lu of %lu): (%f ,%f, %f) Parent Index: %lu", pointCount, x_points.size(), *iter_x, *iter_y, *iter_z, (unsigned long) *iter_pi);
      *iter_rgb = 0xFF0000;
      */
      }
    }
    return cloud;
  }
} //Namespace 

using namespace TurtleBot3Navigation;
int main(int argc, char** argv)
{
  ros::init(argc, argv, "tx2_navigation_node");
  ros::NodeHandle node;
  ros::Rate loop_rate(NAVIGATION_LOOPRATE);

  ros::Publisher path_pub = node.advertise<nav_msgs::Path>("camera_boundry",1);
  ros::Publisher cloud_pub = node.advertise<sensor_msgs::PointCloud2>("cloud_rrt",1);
  ros::Subscriber pointCloud_sub = node.subscribe("/zed/zed_node/point_cloud/cloud_registered", 1, cloud_callback); 
  //Wait for obsticle cloud
  while(hasNoObsticleCloud)
  {
    ros::spinOnce();
    ros::Duration(1).sleep(); // sleep in seconds
  }

  //Main Loop
  while(ros::ok())
  {
    ros::spinOnce();
    ROS_INFO("Spin Once!");
    //createPathAndPub(path_pub);
    createBoundingboxAndPub(path_pub, BOUND_BOX_MIN_RANGE, BOUND_BOX_MAX_RANGE, BOUND_BOX_Y_AXIS_SLOPE, BOUND_BOX_Y_AXIS_INTERCEPT,
        BOUND_BOX_Z_AXIS_SLOPE, BOUND_BOX_Z_AXIS_INTERCEPT);
   
    ROS_INFO("Created Bounding Box!");
    //createCloudAndPub(cloud_pub);
    sensor_msgs::PointCloud2Ptr cloud = generateRandomInViewCloud(BOUND_BOX_MIN_RANGE, BOUND_BOX_MAX_RANGE, BOUND_BOX_Y_AXIS_SLOPE, 
        BOUND_BOX_Y_AXIS_INTERCEPT, BOUND_BOX_Z_AXIS_SLOPE, BOUND_BOX_Z_AXIS_INTERCEPT);
    ROS_INFO("Generated In View Point Cloud!");
    cloud_pub.publish(cloud);
    ROS_INFO("Published Point Cloud!");
    loop_rate.sleep();
  }
  return 0;
}
