#include "WEMflow.h"

WEMflow::WEMflow()
{
m_InWater = new float [g_ModelRunDay];
m_InNH4 = new float [g_ModelRunDay];
m_InNO3 = new float [g_ModelRunDay];
m_InPO4 = new float [g_ModelRunDay];
m_InPOC = new float [g_ModelRunDay];
m_InPON = new float [g_ModelRunDay];
m_InPOP = new float [g_ModelRunDay];
m_InDOC = new float [g_ModelRunDay];
m_InDON = new float [g_ModelRunDay];
m_InDOP = new float [g_ModelRunDay];

m_WaterTable = new float [g_ModelRunDay];

m_OutWater = new float [g_ModelRunDay];
m_OutNH4 = new float [g_ModelRunDay];
m_OutNO3 = new float [g_ModelRunDay];
m_OutPO4 = new float [g_ModelRunDay];
m_OutPOC = new float [g_ModelRunDay];
m_OutPON = new float [g_ModelRunDay];
m_OutPOP = new float [g_ModelRunDay];
m_OutDOC = new float [g_ModelRunDay];
m_OutDON = new float [g_ModelRunDay];
m_OutDOP = new float [g_ModelRunDay];

for(int day = 0; day < (g_ModelRunDay); day++)
        {
                m_InWater[day] = 0.0;
                m_InNH4[day] = 0.0;
                m_InNO3[day] = 0.0;
                m_InPO4[day] = 0.0;
                m_InPOC[day] = 0.0;
                m_InPON[day] = 0.0;
                m_InPOP[day] = 0.0;
                m_InDOC[day] = 0.0;
                m_InDON[day] = 0.0;
                m_InDOP[day] = 0.0;

                m_OutWater[day] = 0.0;
                m_OutNH4[day] = 0.0;
                m_OutNO3[day] = 0.0;
                m_OutPO4[day] = 0.0;

                m_OutPOC[day] = 0.0;
                m_OutPON[day] = 0.0;
                m_OutPOP[day] = 0.0;
                m_OutDOC[day] = 0.0;
                m_OutDON[day] = 0.0;
                m_OutDOP[day] = 0.0;
        }

        m_InNH4Con = new float [g_ModelRunDay];
        m_InNO3Con = new float [g_ModelRunDay];
        m_InPO4Con = new float [g_ModelRunDay];

for(int day = 0; day < (g_ModelRunDay); day++)
        {
        m_InNH4Con[day] = 0.0;
        m_InNO3Con[day] = 0.0;
        m_InPO4Con[day] = 0.0;
        }
}


WEMflow::~WEMflow()
{
        delete []m_InWater;
        delete []m_InNH4;
        delete []m_InNO3;
        delete []m_InPO4;
        delete []m_InDOC;
        delete []m_InDON;
        delete []m_InDOP;
        delete []m_InPOC;
        delete []m_InPON;
        delete []m_InPOP;

        delete []m_WaterTable;

        delete []m_OutWater;
        delete []m_OutNH4;
        delete []m_OutNO3;
        delete []m_OutPO4;

        delete []m_OutPOC;
        delete []m_OutPON;
        delete []m_OutPOP;
        delete []m_OutDOC;
        delete []m_OutDON;
        delete []m_OutDOP;

        delete []m_InNH4Con;
        delete []m_InNO3Con;
        delete []m_InPO4Con;
}


void WEMflow::m_ReadHydrology()
{
int year, month, day;
ifstream inhydrology;
inhydrology.open(inhydrofilename.c_str());
if(!inhydrology)
        {
        cout<<"The hydrology input data is not exist!!! "<<endl;
        exit(1);
        }
else
        {
        if(g_WaterOrOutflow == 1)
        {
        for(int i = 0; i < (g_ModelRunDay); i++)
                {
                inhydrology>>year>>month>>day>>
                m_InWater[i]>>m_InNH4[i]>>
                m_InNO3[i]>>m_InPO4[i]>>m_InDOC[i]>>
                m_InDON[i]>>m_InDOP[i]>>m_InPOC[i]>>
                m_InPON[i]>>m_InPOP[i]>>m_WaterTable[i];
//                m_WaterTable[i] += 0.25;
//                if(m_WaterTable[i] < 0) m_WaterTable[i] = 0.0;
//                cout<<i<<" day "<<m_WaterTable[i]<<endl;
                }
        }
        else
        {
        for(int i = 0; i < (g_ModelRunDay); i++)
                {
                inhydrology>>year>>month>>day
                >>m_InWater[i]>>m_InNH4[i]>>
                m_InNO3[i]>>m_InPO4[i]>>m_InDOC[i]>>
                m_InDON[i]>>m_InDOP[i]>>m_InPOC[i]>>
                m_InPON[i]>>m_InPOP[i]>>m_OutWater[i];
                }
        }
        }

}
