/*
  ThreeAxisArmKinematics.cpp - Library for calculating 3 axis robot arm kinematics.
  Created by Landon R. Faris, June 2, 2021.
*/

#include "Arduino.h"
#include "ScaraArmKinematics.h"
#include "math.h"



ScaraArmKinematics::ScaraArmKinematics(float BaseJointLength, float ShoulderJointLength, float baseJointOffset) 
: shoulderJointLength(shoulderJointLength), baseJointLength(BaseJointLength),
  baseJointOffset(baseJointOffset) { }

void ScaraArmKinematics::forwardKinematics(float newAngles[2]) {
    for (int i=0; i<2; i++) angles[i] = newAngles[i];
    forwardKinematics();
}
void ScaraArmKinematics::forwardKinematics(float newAngles[2], float (&posOut)[2]) {
  forwardKinematics(newAngles);
  getPosition(posOut);
}

void ScaraArmKinematics::inverseKinematics(float newPos[2]) {
  for (int i=0; i<2; i++) pos[i] = newPos[i];
  inverseKinematics();
}
void ScaraArmKinematics::inverseKinematics(float newPos[2], float (&anglesOut)[2]) {
  inverseKinematics(newPos);
  getAngles(anglesOut);
}

void ScaraArmKinematics::getPosition(float (&posOut)[2]) {
  for (int i=0; i<2; i++) posOut[i] = pos[i];
}
void ScaraArmKinematics::getAngles(float (&anglesOut)[2]) {
  for (int i=0; i<2; i++) anglesOut[i] = angles[i];
}

//Private
void ScaraArmKinematics::inverseKinematics() {
  float x = pos[0];
  float y = pos[1];

  //issue here is that almost every position has more than one way to get to it
  //x = cos(currentRadians[0])*baseJointLength+cos(currentRadians[0]+currentRadians[1])*shoulderJointLength
  //y =  sin(currentRadians[0])*baseJointLength+sin(currentRadians[0]+currentRadians[1])*shoulderJointLength


  angles[0] = ;
  angles[1] = ;
}

void ScaraArmKinematics::forwardKinematics() {
  float currentRadians[2] = {
      angles[0] * Pi/180,
      (angles[1] * Pi/180)
    };

  pos[0] = cos(currentRadians[0])*baseJointLength+cos(currentRadians[0]+currentRadians[1])*shoulderJointLength;
  pos[1] = sin(currentRadians[0])*baseJointLength+sin(currentRadians[0]+currentRadians[1])*shoulderJointLength;
}