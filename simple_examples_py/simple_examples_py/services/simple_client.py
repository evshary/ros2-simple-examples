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
from rclpy.executors import ExternalShutdownException
from simple_interfaces.srv import ExampleService


def main(args=None):
    try:
        with rclpy.init(args=args):
            node = rclpy.create_node('simple_client_py')

            cli = node.create_client(ExampleService, 'example_service_name')
            while not cli.wait_for_service(timeout_sec=1.0):
                print('service not available, waiting again...')
            req = ExampleService.Request()
            req.param = 1
            future = cli.call_async(req)
            rclpy.spin_until_future_complete(node, future)
            if future.result() is not None:
                node.get_logger().info('result=%d' % future.result().result)
            else:
                node.get_logger().error('Exception while calling service: %r' % future.exception())
    except (KeyboardInterrupt, ExternalShutdownException):
        pass


if __name__ == '__main__':
    main()
