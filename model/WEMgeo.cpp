#include"WEMgeo.h"

WEMgeo::WEMgeo()
{
m_Lati = 0.0;
m_Elev = 0.0;
m_BulkD = 0.0;
}

WEMgeo::~WEMgeo()
{
;
}

void WEMgeo::m_ReadGeoData()
{
cout<<"Please input the latitude, elevation, and bulk density"<<endl;
cin>>m_Lati>>m_Elev>>m_BulkD;
}

