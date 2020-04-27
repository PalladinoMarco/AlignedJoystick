/**********************************************************************************************************
  
  @file AlignedJoy.h
  @brief Joystick calibrated class
  @author Marco Palladino <marck.palladino@gmail.com>
  @version 1.0
  @date 2020/03/28
  @see https://github.com/PalladinoMarco/AlignedJoystick

  @details
  AlignedJoy is a class written in C++ for Arduino to interface classic analog joysticks.
  Reading the analog values of a joystick with Arduino is very simple, so what is the purpose of this class?
  Through the methods of the class you can calibrate one or more joysticks, read and memorize the calibration points.
  For dynamic applications, calibrated points can be stored in eeprom. Or once the calibration points are obtained,
  they can be set in constant mode. See description of methods.
  The strength of the class is that having the calibration parameters is able to align the values of the axes
  of the respective joysticks. It’s very useful when you want to manage something with a certain precision and
  when you have a joystick with misaligned axis values.

  # LICENSE #
  
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
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/**
AXIS_TRAVEL CONSTANT
 @brief Minimum axis travel value from one end to the other (Xmax-Xmin).
 @details
  This parameter is used as a safety control during calibration or when setting extreme points
  using the "Setcalibrationpoint" method, in order to ensure a minimum excursion between the two
  points and in reference to the central point (joystick at rest).
*/
#define AXIS_TRAVEL 550

/// @brief axes flags
typedef enum axis:uint8_t {X=0, Y} axis_t;

/// @brief calibration point flags
typedef enum point:uint8_t{
  /// minimum point
  MIN=0, 
  /// middle point
  MID, 
  /// maximum point
  MAX
  } point_t;

class AlignedJoy
{
  public:
  
  /**
  @brief Class onstructor. Create a new object of the joystick and set the axes (X/Y) pin to input mode
  @param xPin (x analog port pin of the device)
  @param yPin (y analog port pin of the device)
  */
  AlignedJoy(uint8_t xPin, uint8_t yPin);
  /// Class destructor
  ~AlignedJoy(){};

  /**
  @brief Start calibration of the joystick in center position.
  @details
    Use this method only if the calibration of the axles is desired.
    Calibration is divided into two steps to allow defining the desired functionality
    (messages, delays, etc.) between the two phases.
  @param timeOfCal is the calibration time in milliseconds.
  @return true o false.
  */
  void           middleCalibration(uint16_t timeOfCal);

  /**
  @brief Calibration of the axes at the extreme points (min end max for each axis).
  @details
    It is recommended to rotate the joystick in a circular way along its perimeter (maximum radius
    for each axis) throughout the calibration time.
  @param timeOfCal is the calibration time in milliseconds.
  @return true o false.
  */
  bool           axesCalibration(uint16_t timeOfCal);

  /**
  @brief Method that allows you to set the minimum and maximum calibration points for each axis.
  @details
    Useful to set the values read by eeprom. Allows you to set the values individually, 
    useful for making changes in run time.
  @warning 
    All calibration points (min and maximum) for each axis (x and y) must be defined to 
    obtain a scale reading of the two axes.
    Only the extreme calibration points can be set, the center point is defined only for calibration purposes.
  @param axis X or Y axle enumerator flag.
  @param point MIN, MID or MAX enumertor flag of the calibration point.
  @param value point value to set. For example to set value (876) of the X MAX
          @code 
          objectname.setCalibratedPoint(X, MAX, 876); 
          @endcode 
  */
  void           setCalibratedPoint(axis_t axis, point_t point, uint16_t value);

  /**
  @brief This method returns the value of the required axis and point.
  @details
    It can be used to compare the saved values with the new ones, to read the values saved in 
    the eeprom with the "setCalibratedPoint" function or for debug.
    @see https://github.com/PalladinoMarco/AlignedJoystick/wiki wiki documentation for more details.
  @param axis X or Y axle enumerator flag.
  @param point MIN, MID or MAX enumertor flag of the calibration point.
  @return calibrated point of the axis request. For example to get the calibrated point of Y MIN
          @code
          objectname.getCalibratedPoint(Y, MIN);
          @endcode
  */
  uint16_t       getCalibratedPoint(axis_t axis, point_t point);

  /**
  @brief This method returns the required axis value. If calibrated, returns the aligned axis values.
  @param axis X or Y axle enumerator flag.
  @return analog read of the axis request. For example to read Y axis @code objectname.read(Y); @endcode
  */
  uint16_t       read(axis_t axis);

  /**
  @brief This method returns the required joystick axis values in the set range (map functions)
  @details
    If you want to get a mapping by keeping the scale of calibrated values do not use the arduino map 
    unction (already included in the method) but use the optional parameters "out_min" and "out_max"
    of the read method.
    For arduino map @see https://www.arduino.cc/reference/en/language/functions/math/map/
  @param axis X or Y axle enumerator flag.
  @param out_min minimum range output value.
  @param out_max maximum range output value.
  @return analog read of the relative axis in map mode, for example to control a servo motor, do this:
          @code
          objectname.read(X, 1000, 2000);
          objectname.read(Y, 1000, 2000);
          @endcode
  */
  uint16_t       read(axis_t axis, int32_t out_min, int32_t out_max);
  
  private:
  /*
  sets a single minimum and maximum value, equal for each axis of the joystick to scale them.
  */
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
  bool     joystickCentered;
  bool     joystickFullCalibrated;
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
