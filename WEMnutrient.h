#ifndef WEMnutrient_H
#define WEMnutrient_H
#include<vector>
#include<iostream>

using namespace std;

class WEMnutrient
{
private:
protected:
public:
WEMnutrient();
~WEMnutrient();

float m_C;

float m_N;

float m_P;

WEMnutrient operator = (float);
WEMnutrient operator + (float);
WEMnutrient operator - (float);

WEMnutrient operator = (WEMnutrient);
WEMnutrient operator + (WEMnutrient);
WEMnutrient operator - (WEMnutrient);
WEMnutrient operator += (WEMnutrient);
WEMnutrient operator -= (WEMnutrient);
WEMnutrient operator * (float);
WEMnutrient operator / (float);
WEMnutrient operator *= (float);
WEMnutrient operator /= (float);


};

#endif
 
 
