#include"WEMnutrient.h"


WEMnutrient::WEMnutrient()
{
;
}

WEMnutrient::~WEMnutrient()
{
;
}

WEMnutrient WEMnutrient::operator = (float value)
{
m_C = value;
m_N = value;
m_P = value;
return *this;
}

WEMnutrient WEMnutrient::operator + (float value)
{
m_C += value;
m_N += value;
m_P += value;
return *this;
}

WEMnutrient WEMnutrient::operator - (float value)
{
m_C -= value;
m_N -= value;
m_P -= value;
return *this;
}

WEMnutrient WEMnutrient::operator = (WEMnutrient bio)
{
m_C = bio.m_C;
m_N = bio.m_N;
m_P = bio.m_P;
return *this;
}

WEMnutrient WEMnutrient::operator + (WEMnutrient bio)
{
m_C = m_C + bio.m_C;
m_N = m_N + bio.m_N;
m_P = m_P + bio.m_P;
return *this;
}


WEMnutrient WEMnutrient::operator - (WEMnutrient bio)
{
m_C = m_C - bio.m_C;
m_N = m_N - bio.m_N;
m_P = m_P - bio.m_P;
return *this;
}

WEMnutrient WEMnutrient::operator += (WEMnutrient bio)
{
m_C += bio.m_C;
m_N += bio.m_N;
m_P += bio.m_P;
return *this;
}

WEMnutrient WEMnutrient::operator -= (WEMnutrient bio)
{
m_C -= bio.m_C;
m_N -= bio.m_N;
m_P -= bio.m_P;
return *this;
}

WEMnutrient WEMnutrient::operator * (float rate)
{
m_C = m_C * rate;
m_N = m_P * rate;
m_P = m_P * rate;
return *this;
}

WEMnutrient WEMnutrient::operator / (float rate)
{
m_C = m_C / rate;
m_N = m_P / rate;
m_P = m_P / rate;
return *this;
}

WEMnutrient WEMnutrient::operator *= (float rate)
{
m_C *= rate;
m_N *= rate;
m_P *= rate;
return *this;
}

WEMnutrient WEMnutrient::operator /= (float rate)
{
m_C /= rate;
m_N /= rate;
m_P /= rate;
return *this;
}
 
 
