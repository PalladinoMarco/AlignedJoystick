/**********************************************************************************************************
Joystick calibrated class
@file Aligned Joystick class Header
@author Marco Palladino
@contact marck.palladino@gmail.com
@version 1.0
@date 2020/03/28
https://github.com/PalladinoMarco/AlignedJoy

@description
AlignedJoy is a class written in C++ for Arduino to interface classic analog joysticks.
Reading the analog values of a joystick with Arduino is very simple, so what is the purpose of this class?
Through the methods of the class you can calibrate one or more joysticks, read and memorize the calibration points.
For dynamic applications, calibrated points can be stored in eeprom. Or once the calibration points are obtained,
they can be set in constant mode. See description of methods.
The strength of the class is that having the calibration parameters is able to align the values of the axes
of the respective joysticks. It’s very useful when you want to manage something with a certain precision and
when you have a joystick with misaligned axis values.

@license
MIT License

Copyright (c) 2020 Marco Palladino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**********************************************************************************************************/
#pragma once

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**********************************************************************************************************
AXIS_TRAVEL CONSTANT
@description Minimum axis travel value from one end to the other (Xmax-Xmin).
             This parameter is used as a safety control during calibration or when setting extreme points
             using the "Setcalibrationpoint" method, in order to ensure a minimum excursion between the two
             points and in reference to the central point (joystick at rest).
**********************************************************************************************************/
#define AXIS_TRAVEL 550

typedef enum axis:uint8_t {X=0, Y} axis_t;
typedef enum point:uint8_t{MIN=0, MID, MAX} point_t;

class AlignedJoy
{
  public:
  // constructor
  AlignedJoy(uint8_t xPin, uint8_t yPin);
  ~AlignedJoy(){};

  // methods
  void           middleCalibration(uint16_t timeOfCal);
  bool           axesCalibration(uint16_t timeOfCal);
  void           setCalibratedPoint(axis_t axis, point_t point, uint16_t value);
  uint16_t       getCalibratedPoint(axis_t axis, point_t point);
  uint16_t       read(axis_t axis, int32_t = 0, int32_t = 0);
  
  private:
  void     axesAlign();
  uint8_t  xPin;
  uint8_t  yPin;
  uint16_t alignMin;
  uint16_t alignMax;
  uint16_t xAxisCalibCenter;
  uint16_t xAxisCalibMinimum;
  uint16_t xAxisCalibMaximum;
  uint16_t yAxisCalibCenter;
  uint16_t yAxisCalibMinimum;
  uint16_t yAxisCalibMaximum;
  bool     joystickCentered = false;
  bool     joystickFullCalibrated = false;
};

// class from elapsed-Millis
// https://github.com/pfeerick/elapsedMillis/wiki

/* Elapsed time types - for easy-to-use measurements of elapsed time
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2011 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
class calibrationTimer
{
private:
  unsigned long ms;
public:
  calibrationTimer(void) { ms = millis(); }
  calibrationTimer(unsigned long val) { ms = millis() - val; }
  calibrationTimer(const calibrationTimer &orig) { ms = orig.ms; }
  operator unsigned long () const { return millis() - ms; }
  calibrationTimer & operator = (const calibrationTimer &rhs) { ms = rhs.ms; return *this; }
  calibrationTimer & operator = (unsigned long val) { ms = millis() - val; return *this; }
  calibrationTimer & operator -= (unsigned long val)      { ms += val ; return *this; }
  calibrationTimer & operator += (unsigned long val)      { ms -= val ; return *this; }
  calibrationTimer operator - (int val) const           { calibrationTimer r(*this); r.ms += val; return r; }
  calibrationTimer operator - (unsigned int val) const  { calibrationTimer r(*this); r.ms += val; return r; }
  calibrationTimer operator - (long val) const          { calibrationTimer r(*this); r.ms += val; return r; }
  calibrationTimer operator - (unsigned long val) const { calibrationTimer r(*this); r.ms += val; return r; }
  calibrationTimer operator + (int val) const           { calibrationTimer r(*this); r.ms -= val; return r; }
  calibrationTimer operator + (unsigned int val) const  { calibrationTimer r(*this); r.ms -= val; return r; }
  calibrationTimer operator + (long val) const          { calibrationTimer r(*this); r.ms -= val; return r; }
  calibrationTimer operator + (unsigned long val) const { calibrationTimer r(*this); r.ms -= val; return r; }
};
