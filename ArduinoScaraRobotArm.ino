/*
 * motor controller reference: https://lastminuteengineers.com/a4988-stepper-motor-driver-arduino-tutorial/
 * arduino cam possibility: https://circuitdigest.com/microcontroller-projects/how-to-use-ov7670-camera-module-with-arduino
 * 
 *                                        Questions or ideas
 * make another inverse kinematics that allows you to pass a vector  
 * I think the kinematics assumes the second joint is at z=0, negative z's might work but it's confusing
 *  Deal with time function overflows
 */

#include "src/ScaraArmKinematics/ScaraArmKinematics.h"
#include "src/a4988DriveModule/a4988DriveModule.h"
#include "src/ScaraArm/ScaraArm.h"

const int numJoints = 2;

const int motorStepsPerRev= ; //steps on the actual stepper motor
const int microStepRatio = ; //x microsteps / y full step
const float gearRatios[numJoints] = {,}; //x motor rotations / y joint


const unsigned int dirPins[numJoints] = {,};
const unsigned int stepPins[numJoints] = {,};
const int driveEnablePin = 8;

int maxTPS[numJoints] = {,};
int maxAccel = ;

ScaraArmKinematics kinematics(); 

stepperMotor motors[numJoints] = {
  stepperMotor(driveEnablePin, dirPins[BASE], stepPins[BASE], 200, maxTPS[0], maxAccel),
  stepperMotor(driveEnablePin, dirPins[SHOULDER], stepPins[SHOULDER], 200, maxTPS[1], maxAccel)
};

int maxAngles[numJoints] = {170, 90};

a4988DriveModule driveModules[numJoints] = {
  a4988DriveModule(motors[BASE], gearRatios[BASE], microStepRatio, maxAngles[BASE]), 
  a4988DriveModule(motors[SHOULDER], gearRatios[SHOULDER], microStepRatio, maxAngles[SHOULDER]),
};

ScaraArm arm(driveModules[BASE], driveModules[SHOULDER], kinematics, driveEnablePin);



const float stepsPerRev[numJoints] = {
  motorStepsPerRev * microStepRatio * gearRatios[BASE],
  motorStepsPerRev * microStepRatio * gearRatios[SHOULDER],
};

const float degreesPerStep[numJoints] = {360. / stepsPerRev[BASE], 360. / stepsPerRev[SHOULDER]};

int jointSteps[numJoints] = {0}; //initialize all values in array to 0
int jointSetSteps[numJoints] = {0};
double currentMicros = 0;

void setup() {
  for (int pin : dirPins) { pinMode(pin, OUTPUT); }
  for (int pin : stepPins) { pinMode(pin, OUTPUT); }
  pinMode(driveEnablePin, OUTPUT);
  digitalWrite(driveEnablePin, HIGH);

  driveModules[0].setAngleOffset(0);
  driveModules[1].setAngleOffset(25.4);
  driveModules[2].setAngleOffset(142.9);

  Serial.begin(9600);
  delay(1000);
  Serial.println("Initialized");
  // arm.enableArm(true);
  // Serial.println("Enabled arm");
}

void loop() {
  if (Serial.available()) {
    delay(10e4);
  }
}
