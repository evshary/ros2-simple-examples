// Copyright 2024 ChenYing Kuo
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "rclcpp/rclcpp.hpp"

#include "simple_interfaces/srv/example_service.hpp"

using namespace std::chrono_literals;  // used by 1s

simple_interfaces::srv::ExampleService::Response::SharedPtr send_request(
    rclcpp::Node::SharedPtr node,
    rclcpp::Client<simple_interfaces::srv::ExampleService>::SharedPtr client,
    simple_interfaces::srv::ExampleService::Request::SharedPtr request)
{
    auto result = client->async_send_request(request);
    // Waiting
    if (rclcpp::spin_until_future_complete(node, result) == 
        rclcpp::FutureReturnCode::SUCCESS)
    {
        return result.get();
    } else {
        return NULL;
    }
}

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);

    // Node name
    auto node = rclcpp::Node::make_shared("simple_client_cpp");
    // Ceraete a client to query service name "example_service_name"
    auto client = node->create_client<simple_interfaces::srv::ExampleService>("example_service_name");

    // Build the request
    auto request = std::make_shared<simple_interfaces::srv::ExampleService::Request>();
    request->param = 1;

    //// Waiting until the service is up
    while (!client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node->get_logger(), "Catch interrupt and stop the program!");
            return 0;
        }
        RCLCPP_INFO(node->get_logger(), "Waiting for service...");
    }

    // Send the request
    auto result = send_request(node, client, request);
    if (result) {
        RCLCPP_INFO(node->get_logger(), "result=%d", result->result);
    } else {
        RCLCPP_ERROR(node->get_logger(), "Catch interrupt and stop the program!");
    }

    rclcpp::shutdown();

    return 0;
}