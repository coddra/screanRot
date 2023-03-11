#!/bin/bash

cd "$(dirname "$0")"

rm -rf build
mkdir build
cd build
cmake ..
make all
sudo cp ../screenrotator-msg.sh ~/.local/bin/screenrotator-msg
sudo make install
