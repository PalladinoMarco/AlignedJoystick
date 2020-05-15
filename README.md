[![arduino-library-badge](https://www.ardu-badge.com/badge/AlignedJoy.svg?)](https://www.ardu-badge.com/AlignedJoy/ide)

# AlignedJoy
This library allows an Arduino board to read a variety of analog joystick by aligning axis values (XY).

# Description
Arduino offers a very simple way to read analog values (see [_analogRead()_](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)).
Interfacing a joystick with Arduino is a breeze, but then why use this library?

Not all joysticks have similar values for their respective axes and there is no default offset, such as the PSP1000 joystick, the joystick of a remote control for dynamic modeling etc.
What if for our application we need to move something on x and y with the same rate?

It is not always enough to make a map and a constrain because when x and y will have the same angle we will not have the same values.

Aligend Joystick, as the name suggests, offers a reading of the axis values (x/y) of each joystick installed in an aligned way. With the axes having the same angle we will get reading values very close to each other. To get axis alignment you need to calibrate the joystick.

Read the [_Wiki_](https://github.com/PalladinoMarco/AlignedJoystick/wiki) for more information.

## License
MIT License

Copyright (c) 2020 Marco Palladino

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
