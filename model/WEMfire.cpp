#include"WEMfire.h"

WEMfire::WEMfire()
{
m_Fire = new float[g_ModelRunDay];

string filename;
cout<<"Please input the file name which contain the fire information during model run!! "<<endl;
cout<<" '1' stand for fire occurence, '0' stands for no fire occurence  in that day! "<<endl;
cin>>filename;
ifstream infire;
infire.open(filename.c_str());
if(!infire)
        {
        cout<<"The data file contain the fire information is not exist!! "<<endl;
        exit(1);
        }
else
        {
        for(int i = 0; i < g_ModelRunDay; i++)
                {
                        infire>>m_Fire[i];
                }
        }
infire.close();
}

WEMfire::~WEMfire()
{
delete []m_Fire;
}

