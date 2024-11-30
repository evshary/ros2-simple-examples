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
#include "rclcpp_components/register_node_macro.hpp"

#include "simple_interfaces/srv/example_service.hpp"

namespace simple_server_node
{

class SimpleServerNode : public rclcpp::Node
{
public:
  explicit SimpleServerNode(const rclcpp::NodeOptions & options)
  : Node("simple_server_cpp", options)
  {
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    auto handle_example_service =
      [this](const std::shared_ptr<rmw_request_id_t> request_header,
        const std::shared_ptr<simple_interfaces::srv::ExampleService::Request> request,
        std::shared_ptr<simple_interfaces::srv::ExampleService::Response> response) -> void
      {
        (void)request_header;
        RCLCPP_INFO(this->get_logger(), "Incoming request: param=%d", request->param);
        response->result = 0;
      };
    // Create a service that will use the callback function to handle requests. The service's name is example_service_name.
    srv_ = create_service<simple_interfaces::srv::ExampleService>("example_service_name", handle_example_service);
  }

private:
  rclcpp::Service<simple_interfaces::srv::ExampleService>::SharedPtr srv_;
};

}

RCLCPP_COMPONENTS_REGISTER_NODE(simple_server_node::SimpleServerNode)