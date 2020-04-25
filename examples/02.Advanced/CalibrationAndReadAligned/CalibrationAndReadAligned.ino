/*
 * This sample sketch allows you to read and display through the serial
 * print the calibrated values of the joystick.
*/

// INCLUDE LIBRARY
#include <AlignedJoy.h>

// PINs DEFINITION
// joystick 1
#define PIN_JOY1_X   0  //(up  down)
#define PIN_JOY1_Y   1  //(left  right)

// TIMERs DEFINITION
// joystick calibration
#define TIME_CAL_1 2000
#define TIME_CAL_2 3000

// CLASS CONSTRUCTOR
// new joystick object
AlignedJoy joystick_1(PIN_JOY1_X, PIN_JOY1_Y);

void setup() {
  
 // SERIAL INITIALIZE
 Serial.begin(9600);
 while(!Serial){}

 // JOYSTICK CALIBRATION
 /*
  * Start the joystick calibration in the center position. Use this method only if the calibration of the axles is desired (axesCalibration).
  */
 // CALIBRATION 1
 Serial.print("Center Joystick Calibration \n\nLeave the joystick in the centre position during the calibration\ntime which is set to ");
 Serial.print(TIME_CAL_1);
 Serial.println(" milliseconds.");
 delay(5000);
 Serial.println("Calibration started!");
 delay(500);
 /*
  * for calibrate the joystick center point use "centerCalibration" method; objectname.centerCalibration(uint16_t timeOfCal).
  * "timeOfCal" is the calibration time in milliseconds
  */
 joystick_1.middleCalibration(TIME_CAL_1);
 Serial.println("Joystick Centered!");
 delay(2000);
 
 // CALIBRATION 2
  /*
  * Calibration of the axes at the extreme points (min end max for each axis).
  * It is recommended to rotate the joystick in a circular way along its circumference throughout
  * the calibration time.
  */
 Serial.print("Start axes Calibration \n\nRotate the joystick in a circular way along its circumference\nthroughout the calibration time (");
 Serial.print(TIME_CAL_2);
 Serial.println(" milliseconds).");
 delay(5000);
 Serial.println("Calibration started!");
 delay(500);
 /*
  * for calibrate the joystick axes points use "axesCalibration" method (bool type); objectname.axesCalibration(uint16_t timeOfCal).
  * "timeOfCal" is the calibration time in milliseconds.
  */
 if(joystick_1.axesCalibration(TIME_CAL_2))
 {
  Serial.println("Calibration succesfully!!");
 }
 else
 {
  Serial.println("Calibration failed!!");
 }

  // Print all points calibrated
  /*
   * You can use these values to save them to eeprom memory. In this way you will avoid requiring the joystick calibration at each boot time.
   * To set the parameters read by eeprom you have to use the "setCalibratedPoint" method.
   * If your project does not require the re-calibration of the joystick then you can make a sketch like this only to display the calibrated
   * values to set them in the final project using the "setCalibratedPoint" method.
   * To get the calibrated point values use getCalibratedPoint(axis_t axis, point_t point).
   * The parameters: the labels of the "axis_t" shall be X and Y; the labels of "point_t" is MIN, MID and MAX.
   */
  Serial.print("X min -> ");
  Serial.print(joystick_1.getCalibratedPoint(X, MIN));
  Serial.print(" | center ->  ");
  Serial.print(joystick_1.getCalibratedPoint(X, MID));
  Serial.print(" | max -> ");
  Serial.println(joystick_1.getCalibratedPoint(X, MAX));
  Serial.print("Y min -> ");
  Serial.print(joystick_1.getCalibratedPoint(Y, MIN));
  Serial.print(" | center ->  ");
  Serial.print(joystick_1.getCalibratedPoint(Y, MID));
  Serial.print(" | max -> ");
  Serial.println(joystick_1.getCalibratedPoint(Y, MAX));
}

void loop() {
 /* 
  *  for read axis value use "read" method; objectname.read(axis_t axis).
  *  The parameters: the labels of the "axis_t" shall be X and Y
  */
  
 // print joystick axes value
 Serial.print("joystick_1 X -> ");
 Serial.print(joystick_1.read(X));
 Serial.print(" | Y -> ");
 Serial.println(joystick_1.read(Y));
 delay(500);
 
}
