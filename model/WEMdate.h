#ifndef WEMdate_H
#define WEMdate_H

#include<string>
#include<iostream>
#include<fstream>
#include<cmath>
#include<assert>
using namespace std;

extern ofstream LogFile;

class WEMdate
{
private:
protected:
public:
WEMdate();
~WEMdate();

int monthdays[12];
int monthstartday[12];

int m_Year;
int m_Month;
int m_Day;
int m_DayOfYear;

int m_FirstDayNum;

void m_InputDate();
void m_InputDate(WEMdate date);

void m_SetDate(int y, int m, int d);
void m_SetDate(int y, int daynumber);

int m_GetYear();
int m_GetMonth();
int m_GetDay();

int m_CalcDaysDiff(WEMdate CompDate);

int m_InOrNot(WEMdate, WEMdate, WEMdate);


};

#endif

 
 
