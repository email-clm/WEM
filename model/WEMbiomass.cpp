#include"WEMbiomass.h"


WEMbiomass::WEMbiomass()
{
m_C = 0.0;
m_N = 0.0;
m_P = 0.0;
}

WEMbiomass::~WEMbiomass()
{
;
}


float WEMbiomass::m_AddC(float addc)
{
return (m_C + addc);
}

float WEMbiomass::m_ExtC(float extc)
{
return (m_C + extc);
}

float WEMbiomass::m_AddN(float addn)
{
return (m_N + addn);
}

float WEMbiomass::m_ExtN(float extn)
{
return (m_N + extn);
}

float WEMbiomass::m_AddP(float addp)
{
return (m_P + addp);
}

float WEMbiomass::m_ExtP(float extp)
{
return (m_P - extp);
}

double WEMbiomass::m_AddC(double addc)
{
return (m_C + addc);
}

double WEMbiomass::m_ExtC(double extc)
{
return (m_C + extc);
}

double WEMbiomass::m_AddN(double addn)
{
return (m_N + addn);
}

double WEMbiomass::m_ExtN(double extn)
{
return (m_N + extn);
}

double WEMbiomass::m_AddP(double addp)
{
return (m_P + addp);
}

double WEMbiomass::m_ExtP(double extp)
{
return (m_P - extp);
}

WEMbiomass WEMbiomass::operator = (float value)
{
m_C = value;
m_N = value;
m_P = value;
return *this;
}

WEMbiomass WEMbiomass::operator + (float value)
{
m_C += value;
m_N += value;
m_P += value;
return *this;
}

WEMbiomass WEMbiomass::operator - (float value)
{
m_C -= value;
m_N -= value;
m_P -= value;
return *this;
}

WEMbiomass WEMbiomass::operator = (WEMbiomass bio)
{
m_C = bio.m_C;
m_N = bio.m_N;
m_P = bio.m_P;
return *this;
}

WEMbiomass WEMbiomass::operator + (WEMbiomass bio)
{
m_C = m_C + bio.m_C;
m_N = m_N + bio.m_N;
m_P = m_P + bio.m_P;
return *this;
}


WEMbiomass WEMbiomass::operator - (WEMbiomass bio)
{
m_C = m_C - bio.m_C;
m_N = m_N - bio.m_N;
m_P = m_P - bio.m_P;
return *this;
}

WEMbiomass WEMbiomass::operator += (WEMbiomass bio)
{
m_C += bio.m_C;
m_N += bio.m_N;
m_P += bio.m_P;
return *this;
}

WEMbiomass WEMbiomass::operator -= (WEMbiomass bio)
{
m_C -= bio.m_C;
m_N -= bio.m_N;
m_P -= bio.m_P;
return *this;
}

WEMbiomass WEMbiomass::operator * (float rate)
{
m_C = m_C * rate;
m_N = m_N * rate;
m_P = m_P * rate;
return *this;
}

WEMbiomass WEMbiomass::operator / (float rate)
{
m_C = m_C / rate;
m_N = m_N / rate;
m_P = m_P / rate;
return *this;
}

WEMbiomass WEMbiomass::operator *= (float rate)
{
m_C *= rate;
m_N *= rate;
m_P *= rate;
return *this;
}

WEMbiomass WEMbiomass::operator /= (float rate)
{
m_C /= rate;
m_N /= rate;
m_P /= rate;
return *this;
}


