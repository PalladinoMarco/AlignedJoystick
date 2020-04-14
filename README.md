# AlignedJoy
This library allows an Arduino board to read a variety of analog joystick by aligning axis values (XY).

AlignedJoy is a class written in C++ for Arduino to interface classic analog joysticks.
Reading the analog values of a joystick with Arduino is very simple, so what is the purpose of this class?
Through the methods of the class you can calibrate one or more joysticks, read and memorize the calibration points.
For dynamic applications, calibrated points can be stored in eeprom. Or once the calibration points are obtained,
they can be set in constant mode. See description of methods.
The strength of the class is that having the calibration parameters is able to align the values of the axes
of the respective joysticks. It’s very useful when you want to manage something with a certain precision and
when you have a joystick with misaligned axis values.
