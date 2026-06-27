Clock Linux

A desktop clock application ported to Linux using C++ and Qt6.

System Requirements

1. Update Package Lists

sudo apt update

2. Install Dependencies

sudo apt install build-essential cmake git qt6-base-dev qt6-multimedia-dev libxkbcommon-dev libgl1-mesa-dev libfuse2 wget

How to Build

Using Terminal

mkdir build
cd build
cmake ..
make
./Clock_qt

Publishing (Creating AppImage)

To create a standalone universal binary for distribution, download the packaging
tools and run the script.

1. Download Packaging Tools

wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy-x86_64.AppImage
mv linuxdeploy-x86_64.AppImage linuxdeploy

wget https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage
chmod +x linuxdeploy-plugin-qt-x86_64.AppImage
mv linuxdeploy-plugin-qt-x86_64.AppImage linuxdeploy-plugin-qt

2. Run Packaging Script

chmod +x make-appimage.sh
./make-appimage.sh
