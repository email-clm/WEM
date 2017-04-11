#ifndef WEMconstant_H
#define WEMconstant_H
class WEMconstant
{
private:
protected:
public:
WEMconstant();
~WEMconstant();

// general constant
float m_PI;
float m_GasK;
float m_ConstE;
//constant for estimation of daylength
float m_SPECPERRAD;
float m_MINDECL;
float m_DAYSOFF;
float m_RADPERDAY;
float m_RADDPERDEG;
float m_SRADDT;

float m_airM;
float m_waterM;
float m_G_STD;
float m_P_STD;
float m_T_STD;
float m_CP;
float m_LR_STD;
float m_EPS;
float m_R;

float m_IceK;
float m_OrgK;
float m_WaterK;
float m_AirK;

float m_IceC;
float m_OrgC;
float m_WaterC;
float m_AirC;

float m_OrgBD;
float m_SPBD;  
};


#endif
 
 
