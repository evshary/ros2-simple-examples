# Copyright 2024 ChenYing Kuo
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
import rclpy
from rclpy.node import Node
from simple_interfaces.srv import ExampleService


class ExampleServer(Node):

    def __init__(self):
        super().__init__('simple_server_py')
        self.srv = self.create_service(ExampleService,
                                       'example_service_name',
                                       self.response_callback)

    def response_callback(self, request, response):
        self.get_logger().info('Incoming request: param=%d' % (request.param))
        response.result = 0
        return response


def main(args=None):
    try:
        with rclpy.init(args=args):
            node = ExampleServer()
            rclpy.spin(node)
    except KeyboardInterrupt:
        pass


if __name__ == '__main__':
    main()
