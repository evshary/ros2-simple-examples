from service_interfaces.srv import ExampleService

import rclpy
from rclpy.node import Node


class ExampleServer(Node):

    def __init__(self):
        super().__init__('example_server_py')
        self.srv = self.create_service(ExampleService, 'example_service_name', self.response_callback)

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