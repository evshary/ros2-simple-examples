# ROS 2 Simple examples

Some ROS 2 examples for testing

## Service

```shell
# C++ server
ros2 run simple_examples_cpp example_server
# C++ client
ros2 run simple_examples_cpp example_client
# Python server
ros2 run simple_examples_py add_two_ints_server
# Python client
ros2 run simple_examples_py add_two_ints_client
```

## QoS

```shell
# Adjust the QoS in the code
ros2 run simple_examples_cpp qos_pub
ros2 run simple_examples_cpp qos_sub
```
