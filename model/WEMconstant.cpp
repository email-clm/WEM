#include"WEMconstant.h"


WEMconstant::WEMconstant()
{

// general constant
        m_PI= 3.14159265;                                // PI
        m_GasK = 8.3143;                                 //(m3 Pa mol-1 K-1) gas law constant
        m_ConstE = 2.71828183;                           //
//constant for estimation of daylength                   
        m_SPECPERRAD = 13750.9871;                       //seconds per radian of hour angle
        m_MINDECL = -0.4092797;                          //minimum declination (radians)
        m_DAYSOFF = 11.25;                               //julian day offset of winter solstice
        m_RADPERDAY = 0.017214;                          //radians of Earth orbit per julian day
        m_RADDPERDEG = 0.01745329;                       //radians per degree
        m_SRADDT = 600.0;                                //timestep for radiation routine (seconds)

        m_airM = 28.9644e-3;                             //(kg mol-1) molecular weight of air
        m_waterM = 18.0148e-3;                           //(kg mol-1) molecular weight of water
        m_G_STD = 9.80665;                               //(m s-2) standard gravitational accel.
        m_P_STD = 101325.0;                              //(Pa) standard pressure at 0.0 m elevation
        m_T_STD = 288.15;                                //(K) standard temp at 0.0 m elevation
        m_CP = 1010.0;                                   //(J kg-1 K-1) specific heat of air
        m_LR_STD = 0.0065;                               //(-K m-1) standard temperature lapse rate
        m_EPS = 0.62196351;                              //(MW/MA) unitless ratio of molec weights
        m_R = 8.314;                                    // gas constant

m_IceK = 2.2;        //(J s-1 m-1 degree-1) thermal conductivity
m_OrgK = 0.25;       //(J s-1 m-1 degree-1) thermal conductivity
m_WaterK = 0.57;     //(J s-1 m-1 degree-1) thermal conductivity
m_AirK = 0.025;     //(J s-1 m-1 degree-1) thermal conductivity

m_IceC = 1.9e6;      //(J m-2 degree -1) heat capacity
m_OrgC = 2.5e6;      //(J m-2 degree -1) heat capacity
m_WaterC = 4.2e6;   //(J m-2 degree -1) heat capacity
m_AirC = 1.25e3;    //(J m-2 degree -1) heat capacity

m_OrgBD = 6.0e3;     // mean of 0.9-1.8/m3
m_SPBD = 2.67e6;     // mean of 2.6-2.75g/m3

}

WEMconstant::~WEMconstant()
{
;
}
 
 
