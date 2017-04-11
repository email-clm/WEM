#include"WEMwater.h"


WEMwater::WEMwater()
{
;
}

WEMwater::~WEMwater()
{
;
}
void WEMwater::m_Release()
{
;
}

void WEMwater::m_Initialization()
{
string iniwaterfile;
cout<<"Please input the name of data file which contains the initial information of water components: "<<endl;
cin>>iniwaterfile;

ifstream ini;
ini.open(iniwaterfile.c_str());
if(!ini)
        {
        cout<<"The initial file of water information is not exist!! "<<endl;
        exit(1);
        }
else
        {
        ini>>m_DNH4>>m_DNO3>>m_DPO4>>O_DON.m_C>>O_DON.m_N>>O_DON.m_P>>O_PON.m_C>>O_PON.m_N>>O_PON.m_P>>m_WaterVolume>>m_WaterT;
        }
        
m_WaterDepth = m_WaterVolume;
        
ini.close();
}


 
