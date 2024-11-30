from setuptools import find_packages, setup

package_name = 'simple_examples_py'

setup(
    name=package_name,
    version='1.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ChenYing Kuo',
    maintainer_email='evshary@gmail.com',
    description='Simple Python Service and Client Demo',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'example_client = simple_examples_py.services.simple_client:main',
            'example_server = simple_examples_py.services.simple_server:main'
        ],
    },
)
