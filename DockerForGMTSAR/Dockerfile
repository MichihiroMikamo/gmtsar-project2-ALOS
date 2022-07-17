######################################################################################
### The source is originally from https://gitlab.ssec.wisc.edu/nickb/docker-gmtsar
### Before making this image, you need to download GMTSAR source code. line. 27   
######################################################################################

FROM nvidia/cuda:9.2-cudnn7-devel-ubuntu18.04

RUN apt-get -y update \
&&  apt-get -y upgrade \
&&  apt-get -y install gcc g++ gfortran make cmake autoconf \
&&  apt-get -y install libtiff-dev liblapack-dev \
&&  apt-get -y install libgmt-dev gmt gmt-dcw gmt-gshhg gmt csh \
&&  apt-get -y install curl \
&&  apt-get -y clean \
&&  rm -rf /var/lib/apt/lists/*

ENV ORBITS_DIR=/usr/local/orbits

RUN curl -O https://topex.ucsd.edu/gmtsar/tar/ORBITS.tar \
&&  mkdir -p $ORBITS_DIR \
&&  tar xf ORBITS.tar -C $ORBITS_DIR \
&&  rm ORBITS.tar

ENV GMTSAR_INSTALL=/usr/local/GMTSAR

# our source code came from:
#git clone --branch 6.0 https://github.com/gmtsar/gmtsar GMTSAR
COPY GMTSAR GMTSAR

RUN cd GMTSAR \
&&  autoconf \
&&  ./configure --prefix=$GMTSAR_INSTALL --with-orbits-dir=$ORBITS_DIR \
&&  make \
&&  make install

# add rsync for our own data-moving purposes
RUN apt-get -y update \
&&  apt-get -y install rsync \
&&  apt-get -y clean \
&&  rm -rf /var/lib/apt/lists/*

ENV PATH=$GMTSAR_INSTALL/bin:$PATH


##############################################
### Install opencv and other c++ libraries ###
##############################################

# Configure apt and install packages
RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils dialog 2>&1 \
    # 
    # Verify git, process tools, lsb-release (useful for CLI installs) installed
    && apt-get -y install git iproute2 procps lsb-release \
    #
    # Install C++ tools
    && apt-get -y install build-essential cmake cppcheck valgrind 

RUN apt-get update \
    &&  apt-get install -y \
    build-essential \
    cmake \
    git \
    libgtk2.0-dev \
    pkg-config \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev  \
    libgoogle-glog-dev \
    libatlas-base-dev \
    libeigen3-dev \
    libsuitesparse-dev \
    libgtkglext1 \
    libgtkglext1-dev

#RUN git clone https://github.com/opencv/opencv.git \
RUN git clone https://github.com/opencv/opencv.git -b 4.5.1 \
    &&  mkdir build-opencv \
    &&  chmod 755 build-opencv \
    &&  cd build-opencv \
    &&  cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_OPENGL=ON ../opencv \
    &&  make -j32 \
    &&  make install \
    &&  make clean

RUN apt-get install -y libboost-all-dev

# Install apt-getable dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libgoogle-glog-dev libatlas-base-dev libeigen3-dev libsuitesparse-dev

RUN mkdir eigen-inst && \
    mkdir eigen-build && \
    mkdir eigen-source && \
    cd eigen-source && \
    git clone https://gitlab.com/libeigen/eigen.git && \
    cd ../eigen-build && \
    cmake ../eigen-source/eigen -DCMAKE_INSTALL_PREFIX=../eigen-inst && \
    make install


# add ceres libraries. 2021.5.18 mikamo 
RUN mkdir ceres-inst && \
    cd ceres-inst && \
    git clone https://ceres-solver.googlesource.com/ceres-solver && \
    mkdir ceres-bin && \
    cd ceres-bin && \
    cmake ../ceres-solver -DCMAKE_INSTALL_PREFIX=../ceres-inst -DBUILD_EXAMPLES=0 && \
    make -j32 && \
    make install


RUN apt-get install -y x11-apps
RUN apt-get install -y libglu1-mesa-dev mesa-common-dev freeglut3-dev
RUN apt-get install -y libglfw3 libglfw3-dev
RUN apt-get install -y libglew-dev
RUN apt-get install -y libcanberra-gtk-module libcanberra-gtk3-module

# Clean up
RUN apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*


###########################
### from pytorch-image2 ###
###########################

RUN apt update && apt install -y python3-pip
RUN pip3 install --upgrade pip

RUN pip3 install torch==1.7.1 torchvision==0.8.2 torchaudio==0.7.2
RUN pip3 install torch-scatter==2.0.6 -f https://pytorch-geometric.com/whl/torch-1.7.0+cu102.html
RUN pip3 install torch-sparse==0.6.9 -f https://pytorch-geometric.com/whl/torch-1.7.0+cu102.html
RUN pip3 install torch-cluster==1.5.9 -f https://pytorch-geometric.com/whl/torch-1.7.0+cu102.html
RUN pip3 install torch-spline-conv==1.2.1 -f https://pytorch-geometric.com/whl/torch-1.7.0+cu102.html
RUN pip3 install torch-geometric==1.7.0

# install opencv
RUN pip3 install opencv-python
# write below otherwise you can't import cv2
RUN apt-get install -y libgl1-mesa-dev

# install cupy
RUN pip3 install cupy-cuda102
# install torchsummary
RUN pip3 install torchsummary
# install tensorboard
RUN pip3 install tensorboard
