FROM pytorch/pytorch:2.3.1-cuda12.1-cudnn8-devel
ARG DEBIAN_FRONTEND=nointeractive
ENV TZ=Asia/Shanghai


# Change mirror.
# RUN ls /
# RUN sed -i 's/archive\.ubuntu\./mirrors\.cloud\.tencent\./g' /etc/apt/sources.list && \
#     sed -i 's/security\.ubuntu\./mirrors\.cloud\.tencent\./g' /etc/apt/sources.list


# Install necessary tools
RUN apt update && apt install -y --no-install-recommends sudo vim net-tools openssh-server wget curl aria2 git zip unzip rsync golang \
                                build-essential ninja-build software-properties-common lsb-release pkg-config python3 python3-dev \
                                python3-pip python3-wheel python3-setuptools openssl ruby doxygen clinfo pocl-opencl-icd nodejs \
                                default-jre graphviz libssl-dev libxml2-dev libjsoncpp-dev libomp-dev libpng-dev libtiff-dev \
                                zlib1g-dev libedit-dev libstb-dev libsfml-dev libglew-dev libglm-dev libtclap-dev
                                

# Add default non-root sudoer user and start ssh service
RUN groupadd -r -g 1000 george && useradd -rm -d /home/george -s /bin/bash -g george -G sudo -u 1000 george
RUN echo 'george:123456' | chpasswd && echo "george ALL=(ALL) ALL" >> /etc/sudoers
RUN echo "PermitUserEnvironment yes" >> /etc/ssh/sshd_config && service ssh start


# my own proxy settings
# ENV http_proxy=http://192.168.3.81:7890
# ENV https_proxy=http://192.168.3.81:7890

USER root


# Install llvm
WORKDIR /tmp
RUN aria2c https://apt.llvm.org/llvm.sh  && chmod +x llvm.sh && ./llvm.sh 18
# ENV CC=clang-18
# ENV CXX=clang++-18


# Install cmake
RUN aria2c https://github.com/Kitware/CMake/releases/download/v3.30.0/cmake-3.30.0-linux-x86_64.sh && \
    bash cmake-3.30.0-linux-x86_64.sh --skip-license --prefix=/usr/local


# Install PyPI packages
RUN pip3 install --upgrade pip
RUN pip3 install setuptools>=41.0.0
ADD requirements.txt /tmp/requirements.txt
RUN pip3 install -r  /tmp/requirements.txt


# Clean up
RUN rm -rf /tmp/*


EXPOSE 22
EXPOSE 8888
WORKDIR /home/george
ADD startup.sh startup.sh
ENTRYPOINT ["bash", "startup.sh"]
