#!/bin/bash
rm -rf appdir
rm -f Clock-x86_64.AppImage
mkdir -p appdir/usr/bin
mkdir -p appdir/usr/share/icons/hicolor/256x256/apps
mkdir -p appdir/usr/share/applications
if [ ! -d "build" ]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Release
fi
cmake --build build --config Release
if [ ! -f "Clock_qt.png" ] && [ ! -f "res/Clock_qt.png" ]; then
    wget -q -O Clock_qt.png "https://upload.wikimedia.org/wikipedia/commons/thumb/8/8a/Simple_clock_icon.svg/256px-Simple_clock_icon.svg.png"
fi
cp build/Clock_qt appdir/usr/bin/
cp Clock_qt.png appdir/usr/share/icons/hicolor/256x256/apps/clock.png || cp res/Clock_qt.png appdir/usr/share/icons/hicolor/256x256/apps/clock.png
cat <<EOF > appdir/usr/share/applications/clock.desktop
[Desktop Entry]
Type=Application
Name=Clock
Exec=Clock_qt
Icon=clock
Categories=Utility;
EOF
export PATH=$PATH:.
export QMAKE=/usr/lib/qt6/bin/qmake
./linuxdeploy --appdir appdir --plugin qt --output appimage