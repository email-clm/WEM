//---------------------------------------------------------------------------
#pragma hdrstop

#include "WEMdate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include<iostream>

using namespace std;

WEMdate::WEMdate()
{
monthdays[0]=31;
monthdays[1]=28;
monthdays[2]=31;
monthdays[3]=30;
monthdays[4]=31;
monthdays[5]=30;
monthdays[6]=31;
monthdays[7]=31;
monthdays[8]=30;
monthdays[9]=31;
monthdays[10]=30;
monthdays[11]=31;

monthstartday[0]=0;
monthstartday[1]=31;
monthstartday[2]=59;
monthstartday[3]=90;
monthstartday[4]=120;
monthstartday[5]=151;
monthstartday[6]=181;
monthstartday[7]=212;
monthstartday[8]=243;
monthstartday[9]=273;
monthstartday[10]=304;
monthstartday[11]=334;
}

WEMdate::~WEMdate()
{
//TODO:
}

void WEMdate::m_InputDate()
{
AGAIN:
cout<<"In this model, Feburary is treated as 28 days through all the simulation years!!"<<endl;
LogFile<<"In this model, Feburary is treated as 28 days through all the simulation years!!"<<endl;

cout<<"  Please input the model start date: year      month       day "<<endl;
LogFile<<"  Please input the model start date: year      month       day "<<endl;

cin>>m_Year;
cin>>m_Month;
cin>>m_Day;

LogFile<<m_Year<<endl;
LogFile<<m_Month<<endl;
LogFile<<m_Day<<endl;

        if(m_Month>12 || m_Day >31)
        {
        int is;
        cout<<"The date is invalid, try again!! 1 for YES, 0 for NO"<<endl;
        LogFile<<"The date is invalid, try again!!"<<endl;
        cin>>is;
        assert(is == 0);
        goto AGAIN;
        }

m_FirstDayNum = m_Day + monthstartday[m_Month - 1];
}

void WEMdate::m_InputDate(WEMdate date)
{
AGAIN:
cout<<"In this model, we assume the Feburary only has 28 days in all years!!"<<endl;
LogFile<<"In this model, we assume the Feburary only has 28 days in all years!!"<<endl;

cout<<"  Please input the model end date: year      month       day  "<<endl;
LogFile<<"  Please input the model end date: year      month       day  "<<endl;

cin>>m_Year;
cin>>m_Month;
cin>>m_Day;

LogFile<<m_Year<<endl;
LogFile<<m_Month<<endl;
LogFile<<m_Day<<endl;

        if(m_Month>12 || m_Day >31)
        {
        cout<<"The date is invalid, try again!!!"<<endl;
        LogFile<<"The date is invalid, try again!!"<<endl;
        goto AGAIN;
        }
        else
        {
                if(m_Year < date.m_Year)
                {
                cout<<"The model end year could not previous to model start!!"<<endl;
                cout<<"                 Plese input again               !!"<<endl;

                LogFile<<"The model end year could not previous to model start!!"<<endl;
                LogFile<<"                 Plese input again               !!"<<endl;

                goto AGAIN;
                }
                else
                {
                        if(m_Year == date.m_Year)
                        {
                                if(m_Month < date.m_Month)
                                {
                                cout<<"In the same year, the end month could not previous to start month!!"<<endl;
                                LogFile<<"In the same year, the end month could not previous to start month!!"<<endl;

                                cout<<"                 Plese input again               !!"<<endl;
                                LogFile<<"                 Plese input again               !!"<<endl;

                                goto AGAIN;
                                }
                                else
                                {
                                        if(m_Month == date.m_Month)
                                        {
                                                if(m_Day < date.m_Day)
                                                {
                                                cout<<"The model end day could not previous to model start!!"<<endl;
                                                LogFile<<"The model end day could not previous to model start!!"<<endl;

                                                cout<<"                 Plese input again               !!"<<endl;
                                                LogFile<<"                 Plese input again               !!"<<endl;

                                                goto AGAIN;
                                                }
                                        }
                                }
                        }
                }
        }
m_FirstDayNum = m_Day + monthstartday[m_Month - 1];
}

// Calculating the number of day for model run!!!
int WEMdate::m_CalcDaysDiff(WEMdate CompDate)
{
         int tyear,tday,tdayn;
         tyear = m_Year - CompDate.m_GetYear();
         tday = m_FirstDayNum - CompDate.m_FirstDayNum;
         tdayn = tyear * 365 + tday + 1;
         return(tdayn);
}

void WEMdate::m_SetDate(int y, int m, int d)
{
m_Year = y;
m_Month = m;
m_Day = d;
m_FirstDayNum = m_Day + monthstartday[m_Month - 1];
m_DayOfYear = m_FirstDayNum;
}

void WEMdate::m_SetDate(int y, int daynumber)
{
m_Year = y;
m_DayOfYear = daynumber;
m_FirstDayNum = daynumber;
}

int WEMdate::m_InOrNot(WEMdate date, WEMdate start, WEMdate end)
{
int IsIn;
int monthdays[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(start.m_Year > end.m_Year)
        {
        cout<<"The end year could not be previous to start year!! "<<endl;
        system("pause");
        return  0;
        }
        if(date.m_Month < 1 || date.m_Month > 12 || start.m_Month < 1 || start.m_Month > 12 || start.m_Month < 1 || end.m_Month > 12)
        {
        cout<<"Wrong Month Number!! "<<endl;
        system("pause");
        return  0;
        }
        if(date.m_Day < 1 || date.m_Day > monthdays[date.m_Month - 1] || start.m_Day < 1 || start.m_Day > monthdays[start.m_Month - 1] || end.m_Day < 1 || end.m_Day > monthdays[end.m_Month - 1])
        {
        cout<<"Wrong Day Number!! "<<endl;
        system("pause");
        return  0;
        }

        if((date.m_Year < start.m_Year) || (date.m_Year > end.m_Year))
        IsIn = 0;
        else
        {
                if(((date.m_Year == start.m_Year) && (date.m_Month < start.m_Month)) || ((date.m_Year == end.m_Year) && (date.m_Month > end.m_Month)))
                IsIn = 0;
                else
                {
                        if(((date.m_Year == start.m_Year) && (date.m_Month == start.m_Month) && (date.m_Day < start.m_Day)) || ((date.m_Year == end.m_Year) && (date.m_Month == end.m_Month) && (date.m_Day > end.m_Day)))
                        IsIn = 0;
                        else
                        {
                        IsIn = 1;
                        }
                }

        }
return IsIn;
}


int WEMdate::m_GetYear()
{
return m_Year;
}
int WEMdate::m_GetMonth()
{
return m_Month;
}
int WEMdate::m_GetDay()
{
return m_Day;
}



