/*
  ThreeAxisArmKinematics.cpp - Library for calculating 3 axis robot arm kinematics.
  Created by Landon R. Faris, June 2, 2021.
*/

#ifndef ScaraArmKinematics_h
#define ScaraArmKinematics_h

#include "Arduino.h"

class ScaraArmKinematics
{
  public:
    ScaraArmKinematics(float BaseJointLength, float ShoulderJointLength, float baseJointOffset);
    
    void forwardKinematics(float newAngles[2], float (&posOut)[2]);
    void forwardKinematics(float newAngles[2]);

    void inverseKinematics(float newPos[2], float (&anglesOut)[2]);
    void inverseKinematics(float newPos[2]);
    
    void getPosition(float (&posOut)[2]);
    void getAngles(float (&anglesOut)[2]);
  private:

    void forwardKinematics();
    void inverseKinematics();

    float shoulderJointLength;
    float baseJointLength;
    float baseJointOffset;
    float pos[2];
    float angles[2];
    
    const float Pi = 3.1415926; //not overkill dw, float cuts it off too
};

#endif
