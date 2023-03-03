# Simple Qt screen rotation manager

This repository is a fork of GuLinux's [ScreenRotator](https://github.com/GuLinux/ScreenRotator). 

Extra functionalities:
- lock, unlock or reset screen rotation with inter process communication
- run shell commands on changing orientation

See more in the [Messaging](#messaging) and [Commands](#commands) section.

Similar to the current solution implemented in Gnome, but works on all other X11 desktop environments as well (KDE, XFCE, I3, etc).

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

## Messaging

To send messages to an active `screenrotator`, use `sreenrotator-msg`. It accepts the following commands:
- `lock`
- `unlock`
- `toggle-lock`
- `reset`

You can send multiple commands like this:
```
screenrotator-msg reset lock
```

## Commands

You can pass the commands to execute on entering landscape or portrait mode as command line arguments. Prefix the commands with three dashes, like this:

```
screenrotator --- ~/.config/polybar/mode landscape --- ~/.config/polybar/mode portrait
```

