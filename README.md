# Simple Qt screen rotation manager

This repository is a fork of GuLinux's [ScreenRotator](https://github.com/GuLinux/ScreenRotator). 

Extra functionalities:
- executing custom scripts whenever the rotation changes
- resetting rotation on recieving SIGTERM

More on this in the [configuration](#configuration) section.

Similar to the current solution implemented in Gnome, but works on all other X11 desktop environments as well (KDE, XFCE, etc).

## Compilation requirements

 - cmake
 - gcc
 - Qt5 (with modules x11extras, sensors)
 - xrandr
 - XInput (Xi)
 
On ubuntu, run the following command to install dependencies:
```
sudo apt install -y git cmake build-essential qtbase5-dev libxrandr-dev libxi-dev libqt5x11extras5-dev libqt5sensors5-dev 
```

## Installation

To build and install ScreanRot, run the following commands:

```
git clone https://github.com/coddra/screanRot
cd screanRot
./install.sh
```

You can run the program by calling `sreenrotator`.

## Links

Main icon: https://www.iconfinder.com/icons/326583/orientation_rotation_screen_icon#size=256

## Configuration

Custom commands can be executed by editing `~/.config/screanrot/landscape.sh` or `~/.config/screanrot/portrait.sh`. 
These shell scripts are invoked on entering landscape or portrait mode respectively.
