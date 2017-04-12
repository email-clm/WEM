#ifndef WEMbiomass_H
#define WEMbiomass_H

#include<iostream>
#include<cmath>
#include<fstream>
#include<stdlib>

using namespace std;

class WEMbiomass
{
private:
protected:
public:
WEMbiomass();
~WEMbiomass();

float m_C;
float m_N;
float m_P;

float m_AddC(float addc);
float m_ExtC(float extc);
float m_AddN(float addn);
float m_ExtN(float extn);
float m_AddP(float addp);
float m_ExtP(float extp);

double m_AddC(double addc);
double m_ExtC(double extc);
double m_AddN(double addn);
double m_ExtN(double extn);
double m_AddP(double addp);
double m_ExtP(double extp);

WEMbiomass operator = (float value);
WEMbiomass operator + (float value);
WEMbiomass operator - (float value);
WEMbiomass operator = (WEMbiomass bio);
WEMbiomass operator + (WEMbiomass bio);
WEMbiomass operator - (WEMbiomass bio);
WEMbiomass operator += (WEMbiomass bio);
WEMbiomass operator -= (WEMbiomass bio);
WEMbiomass operator * (float rate);
WEMbiomass operator / (float rate);
WEMbiomass operator *= (float rate);
WEMbiomass operator /= (float rate);    

};


#endif
 
 
