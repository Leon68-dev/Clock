"# Clock" 

Windows publish
windeployqt Clock_qt.exe


Ubuntu
# Оновлення системи
sudo apt update

# Встановлення інструментів розробки (GCC, CMake)
sudo apt install build-essential cmake

# Встановлення Qt 6 (або Qt 5, залежно від того, що ви встановили)
# Для Qt 6:
sudo apt install qt6-base-dev qt6-tools-dev qt6-multimedia-dev
# Якщо ви використовуєте Qt 5:
# sudo apt install qt5-default qtbase5-dev qttools5-dev qtmultimedia5-dev

sudo apt update
sudo apt install git
# Встановіть ваше ім'я користувача
git config --global user.name "Your Name"

# Встановіть вашу електронну пошту
git config --global user.email "your.email@example.com"

Clock_qt/
├── .gitignore
├── CMakeLists.txt
├── main.cpp
├── res/
│   ├── resources.qrc
│   ├── digital_7italic.ttf
│   └── ... (всі інші ресурси)
└── src/
    ├── MainWindow.h/cpp
    ├── SetupDialog.h/cpp
    └── ... (всі інші .h/.cpp)

mkdir build_linux
cd build_linux

cmake .. -DCMAKE_BUILD_TYPE=Release
-DCMAKE_PREFIX_PATH=/path/to/your/qt/version/gcc_64.

make -j$(nproc)

./Clock_qt
