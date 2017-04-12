#ifndef WEMgeoH

#define WEMgeoH

#include<cmath>
#include<string>
#include<cmath>
#include<fstream>
#include<iostream>
#include<ctime>
#include<vector>
#include"WEMconstant.h"

using namespace std;

class WEMgeo
{
private:
protected:
public:
WEMgeo();
~WEMgeo();

void m_ReadGeoData();

float m_Lati;
float m_Elev;
float m_BulkD;
};

#endif


