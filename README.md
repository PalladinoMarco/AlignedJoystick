# AlignedJoy
This library allows an Arduino board to read a variety of analog joystick by aligning axis values (XY).

Arduino offers a very simple way to read analog values (see [_analogRead()_](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)).
Interfacing a joystick with Arduino is a breeze, but then why use this library?

Not all joysticks have similar values for their respective axes and there is no default offset, such as the PSP1000 joystick, the joystick of a remote control for dynamic modeling etc.
What if for our application we need to move something on x and y with the same rate?

It is not always enough to make a map and a constrain because when x and y will have the same angle we will not have the same values.

Aligend Joystick, as the name suggests, offers a reading of the axis values (x/y) of each joystick installed in an aligned way. With the axes having the same angle we will get reading values very close to each other. To get axis alignment you need to calibrate the joystick.

Read the [_Wiki_](https://github.com/PalladinoMarco/AlignedJoystick/wiki) for more information.

## Installation
1. Download [the Master branch](https://github.com/PalladinoMarco/AlignedJoystick/archive/master.zip) from gitHub.
2. Open Arudino IDE
3. Select menu **_Sketch -> Include Library -> Add .ZIP Library_**
4. Select the zip file downloaded
5. You can now include the library from  **_Sketch -> Include Library -> AlignedJoystick_**

If you want to use examples, menu **_File -> Examples -> AlignedJoystick_**

NOTE: If you want include the source of this library directly in your project folder use the preprocessor directives:
```C++
#include "AlignedJoystick.h"
```
