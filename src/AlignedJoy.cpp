/**********************************************************************************************************
Joystick calibrated class
@file Aligned Joystick class cpp
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

#include "AlignedJoy.h"


/**********************************************************************************************************
PSP JOYSTICK
@description Create a new object of the joystick and set the axes (X/Y) pin to input mode
@param xPin and yPin (analog port pin of the device)
**********************************************************************************************************/
AlignedJoy::AlignedJoy(uint8_t xPin, uint8_t yPin)
{
  this->xPin = xPin;
  this->yPin = yPin;
  
  pinMode(this->xPin,INPUT);
  pinMode(this->yPin,INPUT);
};

/**********************************************************************************************************
AXES ALIGNMENT
@description Private method: sets a single minimum and maximum value, equal for each axis of the joystick 
             to scale them.
**********************************************************************************************************/
void AlignedJoy::axesAlign(void)
{
  // Imposed the smallest value between the two calibrated minima.
  this->alignMin = min(this->xAxisCalibMinimum, this->yAxisCalibMinimum);
  // Imposed the largest value between the two calibrated maxima.
  this->alignMax = max(this->xAxisCalibMaximum, this->yAxisCalibMaximum);
}

/**********************************************************************************************************
AXES CALIBRATION IN CENTER POSITION
@description Start calibration of the joystick in center position. Use this method only if the calibration
             of the axles is desired.
             Calibration is divided into two steps to allow defining the desired functionality
             (messages, delays, etc.) between the two phases.
@param "timeOfCal" is the calibration time in milliseconds
@return true o false
**********************************************************************************************************/
void AlignedJoy::middleCalibration(uint16_t timeOfCal)
{
  // New istance of the timer
  calibrationTimer TIME_CAL_1;
  
  // Repeat for the required time
  while(TIME_CAL_1 < timeOfCal)
  {
    // Assigns the value to each loop.
    this->xAxisCalibCenter = analogRead(this->xPin);
    this->yAxisCalibCenter = analogRead(this->yPin);
  }
  // set flag true
  this->joystickCentered = true;
}

/**********************************************************************************************************
AXES CALIBRATION
@description Calibration of the axes at the extreme points (min end max for each axis).
             It is recommended to rotate the joystick in a circular way along its perimeter (maximum radius
             for each axis) throughout the calibration time.
@param "timeOfCal" is the calibration time in milliseconds
@return true o false
**********************************************************************************************************/
bool AlignedJoy::axesCalibration(uint16_t timeOfCal)
{
  if(joystickCentered)
  {
    // New values for comparison
    static uint16_t last_X_min = this->xAxisCalibCenter;
    static uint16_t last_X_max = this->xAxisCalibCenter;
    static uint16_t last_Y_min = this->yAxisCalibCenter;
    static uint16_t last_Y_max = this->yAxisCalibCenter;

    // New istance of the timer
    calibrationTimer TIME_CAL_2;

    // Repeat for the required time
    while(TIME_CAL_2 < timeOfCal)
    { 
      // Read analog value
      uint16_t x = analogRead(this->xPin);
      uint16_t y = analogRead(this->yPin);

      // Logic acquisition. Assigns the lowest or highest values to each loop.
      if(x < this->xAxisCalibCenter && x < last_X_min)
      {
        last_X_min = this->xAxisCalibMinimum = x;
      }
      if(x > this->xAxisCalibCenter && x > last_X_max)
      {
        last_X_max = this->xAxisCalibMaximum = x;
      }
      if(y < this->yAxisCalibCenter && y < last_Y_min)
      {
        last_Y_min = this->yAxisCalibMinimum = y;
      }
      if(y > this->yAxisCalibCenter && y > last_Y_max)
      {
        last_Y_max = this->yAxisCalibMaximum = y;
      }
    }
    
    // verify that there is the minimum excursion between the minimum and the maximum of each axis.
    if((this->xAxisCalibMaximum - this->xAxisCalibMinimum) >= AXIS_TRAVEL &&
       (this->yAxisCalibMaximum - this->yAxisCalibMinimum) >= AXIS_TRAVEL)
    {
      // set flag true
      this->joystickFullCalibrated = true;

      // align axes
      axesAlign();
      
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

/**********************************************************************************************************
SET CALIBRATION POINT
@description Method that allows you to set the minimum and maximum calibration points for each axis.
             Useful to set the values read by eeprom. Allows you to set the values individually, 
             useful for making changes in run time.
             WARNING: All calibration points (min and maximum) for each axis (x and y) must be defined to 
             obtain a scale reading of the two axes.
             Only the extreme calibration points can be set, the center point is defined only for
             calibration purposes.
@param axis = X or Y label, point = MIN, MID or MAX label, pointValue = point value to set, for
       example to set value (876) of the X MAX -> setCalibratedPoint(X, MAX, 876);
**********************************************************************************************************/
void AlignedJoy::setCalibratedPoint(axis_t axis, point_t point, uint16_t pointValue)
{  
   switch(point)
    {
      case MIN:
        switch(axis)
        {
          case X:
           this->xAxisCalibMinimum = pointValue;
          break;
          case Y:
           this->yAxisCalibMinimum = pointValue;  
          break;
        }
      break;
      
      case MAX:
        switch(axis)
        {
          case X:
           this->xAxisCalibMaximum = pointValue;
          break;
          case Y:
           this->yAxisCalibMaximum = pointValue;
          break;
        }
      break;
    }
      // verify that there is the minimum excursion between the minimum and the maximum of each axis.
      if((this->xAxisCalibMaximum - this->xAxisCalibMinimum) >= AXIS_TRAVEL &&
         (this->yAxisCalibMaximum - this->yAxisCalibMinimum) >= AXIS_TRAVEL)
      {
        // set flag true
        this->joystickFullCalibrated = true;

        // align axes
        axesAlign();
      }
}

/**********************************************************************************************************
GET AXES CALIBRATION POINT
@description This method returns the value of the required axis and point. 
             It can be used to compare the saved values with the new ones, to read the values saved in 
             the eeprom with the "setCalibratedPoint" function or for debug.
             See wiki documentation for more details.
@param axis = X or Y label, point = MIN, MID or MAX label
@return calibrated point of the axis request.
        For example to get the calibrated point of Y MIN -> getCalibratedPoint(Y, MIN);
**********************************************************************************************************/
uint16_t AlignedJoy::getCalibratedPoint(axis_t axis, point_t point)
{
  uint16_t pointValue;
  
    switch(point)
    {
      case MIN:
        switch(axis)
        {
          case X:
            pointValue = this->xAxisCalibMinimum; 
          break;
          case Y:
           pointValue = this->yAxisCalibMinimum; 
          break;
        }
      break;
  
      case MID:
        switch(axis)
        {
          case X:
           pointValue = this->xAxisCalibCenter;
          break;
          case Y:
           pointValue = this->yAxisCalibCenter;
          break;
        }
      break;
  
      case MAX:
        switch(axis)
        {
          case X:
           pointValue = this->xAxisCalibMaximum;
          break;
          case Y:
           pointValue = this->yAxisCalibMaximum;
          break;
        }
      break;
    }
  return pointValue;
}

/**********************************************************************************************************
READ JOYSTICK AXIS
@description This method returns the required axis value. If calibrated, returns the aligned axis values.
@param axis = X or Y label.
@return analog read of the relative axis, for example to read Y axis -> read(Y);
**********************************************************************************************************/
uint16_t AlignedJoy::read(axis_t axis)
{
  uint16_t axisValue;

    switch(axis)
    {
      case X:
      if(joystickFullCalibrated)
      {
        axisValue = map(analogRead(this->xPin), this->xAxisCalibMinimum, this->xAxisCalibMaximum, this->alignMin, this->alignMax);
      }
      else
      {
        axisValue = analogRead(this->xPin);
      }
      break;

      case Y:
      if(joystickFullCalibrated)
      {
        axisValue = map(analogRead(this->yPin), this->yAxisCalibMinimum, this->yAxisCalibMaximum, this->alignMin, this->alignMax);
      }
      else
      {
        axisValue = analogRead(this->yPin);
      }
      break;
    }
   return axisValue;
}

/**********************************************************************************************************
READ JOYSTICK AXIS (MAP)
@description If you want to get a mapping by keeping the scale of calibrated values do not use the arduino map 
             function (already included in the method) but use the optional parameters "out_min" and "out_max"
			 of the read method.
             For arduino map see https://www.arduino.cc/reference/en/language/functions/math/map/
@param axis = X or Y label. "out_min" and "out_max" = min and max output value to get a map in scale.
@return analog read of the relative axis in map mode, for example to control a servo motor, do this:
        read(X, 1000, 2000);
        read(Y, 1000, 2000);
**********************************************************************************************************/
uint16_t AlignedJoy::read(axis_t axis, int32_t out_min, int32_t out_max)
{
	return map(read(axis), this->alignMin, this->alignMax, out_min, out_max);
}