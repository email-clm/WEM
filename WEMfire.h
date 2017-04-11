#ifndef WEMfire_H
#define WEMfire_H

#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib>
#include<vector>

using namespace std;
extern ofstream LogFile;
extern int g_ModelRunDay;
extern int g_TotalRunDay;

extern float g_Max(float, float);
extern float g_Min(float, float);
extern double g_Max(double, double);
extern double g_Min(double, double);

class WEMfire
{
public:
WEMfire();
~WEMfire();

float *m_Fire;

};

#endif
