FROM ros:jazzy-ros-base

RUN apt-get update && apt-get install -y \
    python3-colcon-common-extensions \
    python3-pip \
    ros-jazzy-tf2-ros \
    ros-jazzy-tf2-tools \
    nano \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ros2_ws
RUN echo "source /opt/ros/jazzy/setup.bash" >> /root/.bashrc
CMD ["bash"]