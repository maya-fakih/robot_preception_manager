import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    pkg_share = get_package_share_directory('perception_manager')

    namespace_arg = DeclareLaunchArgument(
        'namespace',
        default_value='robot1',
    )

    params_file = os.path.join(pkg_share, 'config', 'params.yaml')

    perception_manager_node = Node(
        package='perception_manager',
        executable='perception_manager_node',
        name='perception_manager',
        namespace=LaunchConfiguration('namespace'),
        parameters=[params_file],
        output='screen',
    )

    camera_tf_broadcaster_node = Node(
        package='perception_manager',
        executable='camera_tf_broadcaster',
        name='camera_tf_broadcaster',
        namespace=LaunchConfiguration('namespace'),
        parameters=[params_file],
        output='screen',
    )

    return LaunchDescription([
        namespace_arg,
        perception_manager_node,
        camera_tf_broadcaster_node,
    ])