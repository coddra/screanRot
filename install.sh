#!/bin/bash

cd "$(dirname "$0")"

rm -rf build
mkdir build
cd build
cmake ..
make all
doas cp ../screenrotator-msg.sh /bin/screenrotator-msg
sudo make install
