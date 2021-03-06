#! /bin/bash

if [ $# -eq 0 ]; then
    CV_VERSION = 3.4.11
else
    CV_VERSION = $1
    echo "Version 3.4.11 is installed..."
fi

echo "OpenCV Version ${CV_VERSION} is installed..."
cd ~

# Download OpenCV zip files.
sudo apt update && sudo apt install -y cmake g++ wget unzip git
echo "Download ${CV_VERSION} version OpenCV and OpenCV Contrib..."
git clone --single-branch --branch ${CV_VERSION} https://github.com/opencv/opencv.git
git clone --single-branch --branch ${CV_VERSION} https://github.com/opencv/opencv_contrib.git

# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt install -y libgtk2.0-dev pkg-config libavcodec-dev \
libavformat-dev libswscale-dev python3-dev python3-numpy \
libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev  \
libdc1394-22-dev libcanberra-gtk-dev

# Create build directory and switch into it
cd opencv && mkdir build && cd build

sudo cmake -DBUILD_opencv_world=1 -DCMAKE_CONFIGURATION_TYPE=Release -DOPENCV_ENABLE_NONFREE=1 -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules -DCMAKE_INSTALL_PREFIX=/usr/local ..
sudo make -j$(nproc) && sudo make install

cd ~
