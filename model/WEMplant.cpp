#include"WEMplant.h"

WEMplant::WEMplant()
{
m_LeafDCI = 0.0;
m_LeafDNI = 0.0;
m_LeafDPI = 0.0;
m_ShootDCI = 0.0;
m_ShootDNI = 0.0;
m_ShootDPI = 0.0;
m_RhizomeDCI = 0.0;
m_RhizomeDNI = 0.0;
m_RhizomeDPI = 0.0;
m_FRootDCI = 0.0;
m_FRootDNI = 0.0;
m_FRootDPI = 0.0;
m_CRootDCI = 0.0;
m_CRootDNI = 0.0;
m_CRootDPI = 0.0;

}

WEMplant::~WEMplant()
{
;
}

void WEMplant::m_Release()
{
;
}

// New function for photosynthesis

float f1_stomata(float a, float b)
{
        float out;
        out = pow(a,float((b-25.)/10.));
        return out;
}

float f2_stomata(float a)
{
        float out;
        out = 1. + exp((-2.2e05+710.*(a+273.16))/(8.314*(a+273.16)));
        return out;
}

float WEMplant::Stomata(WEMplantparameter plantpara, float* outrs, float tv,
                float ei, float apar, float o2, float co2, float pgcm,
                 float tgcm, float igs,float btran, float foln, float rb)
{
        //reference:            Gordon Bonan

        //float tv;         //foliage temperature (kelvin)
        //float ei;         //vapor pressure inside leaf (sat vapor press at tv) (pa)
        //float ea;         //vapor pressure of canopy air (pa)
        //float apar;       //par absorbed per unit lai (w/m**2)
        //float o2;         //atmospheric o2 concentration (pa)
        //float co2;        //atmospheric co2 concentration (pa)
        //float pgcm;       //air pressure at agcm reference height (pa)
        //float tgcm;       //air temperature at agcm reference height (kelvin)
        //int igs;          //growing season index (0=off, 1=on)
        //float btran;      //soil water transpiration factor (0 to 1)
        //float foln;       //foliage nitrogen concentration (%)
        //float rb;         //boundary layer resistance (s/m)

        //float tmin = psnparam.tmin;       //minimum temperature for photosynthesis (kelvin)

        float qe25 = plantpara.qe25;       //quantum efficiency at 25c (umol co2 / umol photon)
        float ko25 = plantpara.ko25;       //o2 michaelis-menten constant at 25c (pa)
        float kc25 = plantpara.kc25;       //co2 michaelis-menten constant at 25c (pa)
        float vcmx25 = plantpara.vcmx25;     //maximum rate of carboxylation at 25c (umol co2/m**2/s)
//        float aqe = plantpara.aqe;        //q10 for qe25
        float ako = plantpara.ako;        //q10 for ko25
        float akc = plantpara.akc;        //q10 for kc25
        float avcmx = plantpara.avcmx;      //q10 for vcmx25
        float bp = plantpara.bp;         //minimum leaf conductance (umol/m**2/s)
        float mp = plantpara.mp;         //slope for conductance-to-photosynthesis relationship
        float folnmx = plantpara.folnmx;     //foliage nitrogen concentration when f(n)=1 (%)
        int c3psn = plantpara.c3psn;        //photosynthetic pathway: 0. = c4, 1. = c3

        //output
        float rs;         //leaf stomatal resistance (s/m)
        float psn;        //foliage photosynthesis (umol co2 /m**2/ s) [always +]

        //local
        float tc;         //foliage temperature (degree celsius)
        float cs;         //co2 concentration at leaf surface (pa)
        float kc;         //co2 michaelis-menten constant (pa)
        float ko;         //o2 michaelis-menten constant (pa)
        float a,b,c,q;    //intermediate calculations for rs
        float r1,r2;      //roots for rs
        float fnf;        //foliage nitrogen adjustment factor (0 to 1)
        float ppf;        //absorb photosynthetic photon flux (umol photons/m**2/s)
        float wc;         //rubisco limited photosynthesis (umol co2/m**2/s)
        float wj;         //light limited photosynthesis (umol co2/m**2/s)
        float we;         //export limited photosynthesis (umol co2/m**2/s)
        float cp;         //co2 compensation point (pa)
        float ci;         //internal co2 (pa)
        float awc;        //intermediate calcuation for wc
        float vcmx;       //maximum rate of carboxylation (umol co2/m**2/s)
        float j;          //electron transport (umol co2/m**2/s)
        float cea;        //constrain ea or else model blows up
        float cf;         //s m**2/umol -> s/m

        cf = pgcm /(8.314 * tgcm) * 1.e06;                                   //s m**2/umol -> s/m
        rs = 1./bp * cf;                                                //maximum leaf stomatal resistance (s/m)
        psn = 0.;                                                       //foliage photosynthesis (umol co2 /m**2/ s) [always +]

        (*outrs) = rs;

        if(apar<=0.) return (0.0);

        fnf = g_Min(foln/g_Max(10e-10,double(folnmx)), 1.0);                           //foliage nitrogen adjustment factor (0 to 1)
        tc = tv - 273.15;                                                 //foliage temperature (degree celsius)
        ppf = 4.6 * apar;                                                 //absorb photosynthetic photon flux (umol photons/m**2/s)
        j = ppf * qe25;                                                   //electron transport (umol co2/m**2/s)
        kc = kc25 * f1_stomata(akc,tc);                                   //co2 michaelis-menten constant (pa)
        ko = ko25 * f1_stomata(ako,tc);                                   //o2 michaelis-menten constant (pa)
        awc = kc * (1.+o2/ko);                                          //intermediate calcuation for wc
        cp = 0.5 * kc / ko * o2 * 0.21;                                         //co2 compensation point (pa)
        vcmx = vcmx25 * f1_stomata(avcmx,tc) / f2_stomata(tc) * fnf * btran;   //maximum rate of carboxylation (umol co2/m**2/s

        //first guess ci

        ci = 0.7*co2*c3psn + 0.4*co2*(1.-c3psn);                        //internal co2 (pa)

        //rb: s/m -> s m**2 / umol
        rb = rb/cf;
        //constrain ea or else model blows up
        cea = 0.25*ei*c3psn+0.40*ei*(1.-c3psn);

        //ci iteration
        int niter = 3;  //number of iterations
        for(int iter=0; iter<niter; iter++){
                wj = g_Max(float(ci-cp), float(0.0)) * j / (ci + 2. * cp) * c3psn +
                        j*(1.-c3psn);
                wc = g_Max(float(ci-cp), float(0.0)) * vcmx / (ci + awc) * c3psn +
                        vcmx*(1.-c3psn);
                we = 0.5 * vcmx * c3psn +
                        4000. * vcmx * ci / pgcm * (1.-c3psn);
                psn = g_Min(g_Min(wj,wc),we) * igs;

                cs = g_Max(float(co2-1.37*rb*pgcm*psn), float(10e-10));
                a = mp*psn*pgcm*cea / (cs*ei) + bp;
                b = ( mp*psn*pgcm/cs + bp ) * rb - 1.;
                c = -rb;
                if (b >= 0.) q = -0.5*( b + sqrt(b*b-4.*a*c) );
                else q = -0.5*( b - sqrt(b*b-4.*a*c));

                r1 = q/a;
                r2 = c/q;
                rs = g_Max(r1,r2);
                ci = g_Max(cs-psn*pgcm*1.65*rs, 0.0);

        }

        //rs, rb:  s m**2 / umol -> s/m
        rs = rs*cf;
        rb = rb*cf;

        (*outrs) = rs;
        return (psn);

}
// End of the new function for photosynthesis


float WEMplant::m_DayLength(float lat, int JulDay)
{
float Second;
lat = lat * O_Cons.m_PI / 180.0;
        float Decline = 0;
        Decline = O_Cons.m_MINDECL * cos((JulDay + O_Cons.m_DAYSOFF) * O_Cons.m_RADPERDAY);
        Second = 2 * acos(-sin(lat) * sin(Decline) / cos(lat) / cos(Decline)) * O_Cons.m_SPECPERRAD;
return Second;
}

void WEMplant::m_GPP(WEMplantparameter O_PlantPara, float tavg, float soilt, float co2, float pa, float par, float lat, int JulDay, float *avn, float *avp, float *decfeedback, float fireinten, float leafrecovery, float plantfrac)
{
//cout<<"OK!1 avn "<<(*avn)<<" avp "<<(*avp)<<endl;

// Xiaofeng changed the algorithm from above one to the below one on August 21, 2008 based on the Haefner 2003 (O'Neil, 1989)
float potgpp;
float npimpact;
float ncr, pcr;

float leafnc = 1.0 / O_PlantPara.m_OptLeafCNratio;
float leafpc = 1.0 / O_PlantPara.m_OptLeafCPratio;

if(O_Leaf.m_C > 0)
{
ncr = O_Leaf.m_N / O_Leaf.m_C;
pcr = O_Leaf.m_P / O_Leaf.m_C;
}
else
{
ncr = 1.0;
pcr = 1.0;
}

if(ncr < 10e10 || pcr < 10e-10)       npimpact = 1.0;
else    npimpact = 4.0 / ((ncr + leafnc) / ncr + (pcr + leafpc) / pcr);

float photosynthesis;

// Use new function of photosynthesis
float leafr  =0.0;

float apar;
float foln;
float tv = tavg + 273.15;
//float tksoil = 5.0 + 273.15;     //SOIL TEMPERATURE (kelvin)
float ei = 1.0;
//float ea = dVpa[day];
float pgcm = 1.03e5; //air pressure at agcm reference height (pa)
float po2 = 0.209 * pgcm; //atmospheric o2 concentration (pa)
float pco2 = 375.0 * 1.e-06 * pgcm;
float tgcm = tv;
//float igs;
//if(tv > O_PlantPara.m_MinT_Phot) igs = 1.;
//else igs = 0.;                   //growing season index (0=off, 1=on)
float igs;
float mint, maxt, optt;
mint = O_PlantPara.m_MinT_Phot;
maxt = O_PlantPara.m_MaxT_Phot;
optt = O_PlantPara.m_OptT_Phot;

igs = (tavg - mint) * (tavg - maxt) / ((tavg - mint) * (tavg - maxt) - (tavg - optt)*(tavg - optt));
igs *= igs;
if(igs < 0.01)       igs = 0.01;

//igs = pow(2.0, (tavg - mint)/10.0);

float btrans = 1.0;

//btrans = Calbtran(year,day);

float rb = O_PlantPara.rb;    //BOUNDARY RESISTENCE

//foln = O_PlantPara.foln;        //nitrogen concentration

if(O_Leaf.m_C < 10e-10) foln = 1;
else    foln = 100. * O_Leaf.m_N / (O_Leaf.m_C / 0.45);

apar = par;

float totalbc = O_Leaf.m_C + O_ShootBase.m_C + O_Rhizome.m_C + O_FRoot.m_C + O_CRoot.m_C;

float scaler = 1.0;
if(totalbc > O_PlantPara.m_MaxBiomassC)
{
scaler = pow((O_PlantPara.m_MaxBiomassC / totalbc), float(2.0));
if(scaler < 0.1)       scaler = 0.1;
}
scaler = 1.0;

float laiscaler = 1.0;
if(m_LAI > O_PlantPara.m_MaxLAI * leafrecovery)
{
laiscaler = pow((O_PlantPara.m_MaxLAI * leafrecovery / m_LAI), float(2.0));
if(laiscaler < 0.1)       laiscaler = 0.1;
}
//laiscaler = 1.0;

if(npimpact > 1.0)    npimpact = 1.0;

photosynthesis = laiscaler * scaler * Stomata(O_PlantPara, &leafr, tv, ei, apar, po2, pco2, pgcm, tgcm, igs, btrans, foln, rb);
//cout<<" here1: "<<photosynthesis<<" lai "<<m_LAI;
potgpp = npimpact * photosynthesis * O_Leaf.m_C * O_PlantPara.m_SLA * m_DayLength(lat, JulDay) * 12.011 / 1000000.0;
//cout<<" here2: "<<potgpp;
float uptaken = 0.0;
float uptakep = 0.0;

float meandni = (m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI) / 5.0;
float meandpi = (m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI) / 5.0;

float totalc, totaln, totalp;

totalc = O_Leaf.m_C + O_ShootBase.m_C + O_Rhizome.m_C + O_FRoot.m_C + O_CRoot.m_C;
totaln = O_Leaf.m_N + O_ShootBase.m_N + O_Rhizome.m_N + O_FRoot.m_N + O_CRoot.m_N;
totalp = O_Leaf.m_P + O_ShootBase.m_P + O_Rhizome.m_P + O_FRoot.m_P + O_CRoot.m_P;

if(totalc < 10e-10 || totaln < 10e-10 || totalp < 10e-10)
        {
        m_GPPvalue = 0.0;
        uptaken = 0.0;
        uptakep = 0.0;
        }
else
        {
        if(meandni < 0.0)       meandni = 0.0;
        if(meandpi < 0.0)       meandpi = 0.0;

        float avneffect = O_PlantPara.m_NuptakeRate * (*avn) / ((*avn) + O_PlantPara.m_NuptakeKu);
        float avpeffect = O_PlantPara.m_PuptakeRate * (*avp) / ((*avp) + O_PlantPara.m_PuptakeKu);

        if(potgpp < 0)  potgpp = 0.0;

//cout<<"here "<<" totalc "<<totalc<<" totaln "<<totaln<<" totalp "<<totalp<<endl;

        uptaken = g_Max(potgpp * totaln / totalc * (0.5 + meandni) / 1., double(avneffect));
        uptakep = g_Max(potgpp * totalp / totalc * (0.5 + meandpi) / 1., double(avpeffect));

        if(npimpact < 1.0)
        {
        uptaken *= 1.0 / npimpact;
        uptakep *= 1.0 / npimpact;
        }
//uptaken = avneffect;
//uptakep = avpeffect;

//cout<<"here "<<" totalc "<<uptaken<<" totaln "<<uptakep<<endl;

        if(uptaken > (0.75 * (*avn))) uptaken = (0.75 * (*avn));
        if(uptakep > (0.75 * (*avp))) uptakep = (0.75 * (*avp));

        if(uptaken < 0.0) uptaken = 0.;
        if(uptakep < 0.0) uptakep = 0.;

//        float temp = g_Min((uptaken / (potgpp * totaln / totalc)), (uptakep / (potgpp * totalp / totalc)));
//        if(temp > 1.0)  temp = 1.0;
//        if(temp < 0.5)  temp = 0.75;
//        potgpp *= temp;
//cout<<"Test2 nuptake "<<uptaken<<" p uptake "<<uptakep<<endl;
        }
//cout<<"Test2 nuptake "<<uptaken<<" p uptake "<<uptakep<<endl;
//cout<<"OK! avn "<<(*avn)<<" avp "<<(*avp)<<endl;

m_GPPvalue = potgpp;


// Re-allocation of N and P


float extran = 0.0;

if(O_Leaf.m_N > (1.5 * O_Leaf.m_C / O_PlantPara.m_OptLeafCNratio))
        {
        extran += (O_Leaf.m_N - 1.5 * O_Leaf.m_C / O_PlantPara.m_OptLeafCNratio);
        O_Leaf.m_N = 1.5 * O_Leaf.m_C / O_PlantPara.m_OptLeafCNratio;
        }

if(O_ShootBase.m_N > (1.5 * float(O_ShootBase.m_C / O_PlantPara.m_OptShootCNratio)))
        {
//        cout<<O_ShootBase.m_C<<"here1 O_ShootBase "<<O_ShootBase.m_N<<endl;
        extran += (O_ShootBase.m_N - 1.5 * O_ShootBase.m_C / O_PlantPara.m_OptShootCNratio);
        O_ShootBase.m_N = 1.5 * O_ShootBase.m_C / O_PlantPara.m_OptShootCNratio;
//        cout<<O_PlantPara.m_OptShootCNratio<<"here2 "<<O_ShootBase.m_N<<endl;
        }

if(O_Rhizome.m_N > (1.5 * float(O_Rhizome.m_C / O_PlantPara.m_OptRhizomeCNratio)))
        {
//        cout<<O_Rhizome.m_C<<"here1 O_Rhizome "<<O_Rhizome.m_N<<endl;
        extran += (O_Rhizome.m_N - 1.5 * O_Rhizome.m_C / O_PlantPara.m_OptRhizomeCNratio);
        O_Rhizome.m_N = 1.5 * O_Rhizome.m_C / O_PlantPara.m_OptRhizomeCNratio;
//        cout<<O_PlantPara.m_OptRhizomeCNratio<<"here2 "<<O_Rhizome.m_N<<endl;
        }

if(O_FRoot.m_N > (1.5 * float(O_FRoot.m_C / O_PlantPara.m_OptFRootCNratio)))
        {
//        cout<<O_FRoot.m_C<<"here1 O_FRoot "<<O_FRoot.m_N<<endl;
        extran += (O_FRoot.m_N - 1.5 * O_FRoot.m_C / O_PlantPara.m_OptFRootCNratio);
        O_FRoot.m_N = 1.5 * O_FRoot.m_C / O_PlantPara.m_OptFRootCNratio;
//        cout<<O_PlantPara.m_OptFRootCNratio<<"here2 "<<O_FRoot.m_N<<endl;
        }
if(O_CRoot.m_N > (1.5 * float(O_CRoot.m_C / O_PlantPara.m_OptCRootCNratio)))
        {
//        cout<<O_CRoot.m_C<<"here1 O_CRoot "<<O_CRoot.m_N<<endl;
        extran += (O_CRoot.m_N - 1.5 * O_CRoot.m_C / O_PlantPara.m_OptCRootCNratio);
        O_CRoot.m_N = 1.5 * O_CRoot.m_C / O_PlantPara.m_OptCRootCNratio;
//        cout<<O_PlantPara.m_OptCRootCNratio<<"here2 "<<O_CRoot.m_N<<endl;
        }
//cout<<"extran"<<extran<<endl;
m_AllocationN(extran, O_PlantPara);

float extrap = 0.0;

if(O_Leaf.m_P > (1.5 * O_Leaf.m_C / O_PlantPara.m_OptLeafCPratio))
        {
        m_RootExudation.m_P += (O_Leaf.m_P - 1.5 * O_Leaf.m_C / O_PlantPara.m_OptLeafCPratio);
        O_Leaf.m_P = 1.5 * O_Leaf.m_C / O_PlantPara.m_OptLeafCPratio;
        }

if(O_ShootBase.m_P > (1.5 * float(O_ShootBase.m_C / O_PlantPara.m_OptShootCPratio)))
        {
//        cout<<O_ShootBase.m_C<<"here1 O_ShootBase.m_P "<<O_ShootBase.m_P<<endl;
        extrap += (O_ShootBase.m_P - 1.50 * float(O_ShootBase.m_C / O_PlantPara.m_OptShootCPratio));
        O_ShootBase.m_P = 1.50 * O_ShootBase.m_C / O_PlantPara.m_OptShootCPratio;
//        cout<<O_PlantPara.m_OptShootCPratio<<"here2 "<<O_ShootBase.m_P<<endl;
        }

if(O_Rhizome.m_P > (1.5 * float(O_Rhizome.m_C / O_PlantPara.m_OptRhizomeCPratio)))
        {
//        cout<<O_Rhizome.m_C<<"here1 O_Rhizome.m_P "<<O_Rhizome.m_P<<endl;
        extrap += (O_Rhizome.m_P - 1.5 * O_Rhizome.m_C / O_PlantPara.m_OptRhizomeCPratio);
        O_Rhizome.m_P = 1.5 * O_Rhizome.m_C / O_PlantPara.m_OptRhizomeCPratio;
//        cout<<O_PlantPara.m_OptRhizomeCPratio<<"here2 "<<O_Rhizome.m_P<<endl;
        }

if(O_FRoot.m_P > (1.5 * float(O_FRoot.m_C / O_PlantPara.m_OptFRootCPratio)))
        {
//        cout<<O_FRoot.m_C<<"here1 O_FRoot.m_P "<<O_FRoot.m_P<<endl;
        extrap += (O_FRoot.m_P - 1.5 * O_FRoot.m_C / O_PlantPara.m_OptFRootCPratio);
        O_FRoot.m_P = 1.5 * O_FRoot.m_C / O_PlantPara.m_OptFRootCPratio;
//        cout<<O_PlantPara.m_OptFRootCPratio<<"here2 "<<O_FRoot.m_P<<endl;
        }
if(O_CRoot.m_P > (1.5 * float(O_CRoot.m_C / O_PlantPara.m_OptCRootCPratio)))
        {
//        cout<<O_CRoot.m_C<<"here1 O_CRoot.m_P "<<O_CRoot.m_P<<endl;
        extrap += (O_CRoot.m_P - 1.5 * O_CRoot.m_C / O_PlantPara.m_OptCRootCPratio);
        O_CRoot.m_P = 1.5 * O_CRoot.m_C / O_PlantPara.m_OptCRootCPratio;
//        cout<<O_PlantPara.m_OptCRootCPratio<<"here2 "<<O_CRoot.m_P<<endl;
        }
//cout<<"extrap"<<extrap<<endl;
m_AllocationP(extrap, O_PlantPara);



float scalern, scalerp;

if((m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI) < 2.5)
scalern = (2.5 - (m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI))/ 2.5;

if(scalern > 1) scalern = 1;

if((m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI) < 2.5)
scalerp = (2.5 - (m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI)) / 2.5;

if(scalerp > 1) scalerp = 1;

//uptaken *= scalern;
//uptakep *= scalerp;

*decfeedback = (m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI + m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI) / 15.0;

//if(totalplantn > O_PlantPara.m_MaxBiomassC * O_PlantPara.m_GPPtoStorage)

//cout<<" OK1: "<<(*avn)<<" "<<uptaken;
//cout<<" OK2: "<<(*avp)<<" "<<uptakep;

*avn -= uptaken;
*avp -= uptakep;

// End of re-allocation
//cout<<"OK1: "<<uptaken;
//cout<<"OK2: "<<uptakep;
m_AllocationN(uptaken, O_PlantPara);
m_AllocationP(uptakep, O_PlantPara);
//cout<<"OK3: "<<O_ShootBase.m_P;

m_AR(O_PlantPara, tavg, soilt, JulDay);

m_Allocation(O_PlantPara, m_GPPvalue, JulDay, fireinten, leafrecovery, plantfrac);

if(O_Leaf.m_C < 0.0)    O_Leaf.m_C = 0.0;
if(O_Leaf.m_N < 0.0)    O_Leaf.m_N = 0.0;
if(O_Leaf.m_P < 0.0)    O_Leaf.m_P = 0.0;
if(O_ShootBase.m_C < 0.0)    O_ShootBase.m_C = 0.0;
if(O_ShootBase.m_N < 0.0)    O_ShootBase.m_N = 0.0;
if(O_ShootBase.m_P < 0.0)    O_ShootBase.m_P = 0.0;
if(O_Rhizome.m_C < 0.0)    O_Rhizome.m_C = 0.0;
if(O_Rhizome.m_N < 0.0)    O_Rhizome.m_N = 0.0;
if(O_Rhizome.m_P < 0.0)    O_Rhizome.m_P = 0.0;
if(O_FRoot.m_C < 0.0)    O_FRoot.m_C = 0.0;
if(O_FRoot.m_N < 0.0)    O_FRoot.m_N = 0.0;
if(O_FRoot.m_P < 0.0)    O_FRoot.m_P = 0.0;
if(O_CRoot.m_C < 0.0)    O_CRoot.m_C = 0.0;
if(O_CRoot.m_N < 0.0)    O_CRoot.m_N = 0.0;
if(O_CRoot.m_P < 0.0)    O_CRoot.m_P = 0.0;
}

float WEMplant::m_AR(WEMplantparameter O_PlantPara, float airT, float soilT, int JulDay)
{
float LeafMR, ShootMR, RhizomeMR, FRootMR, CRootMR;
float GR;

if(O_PlantPara.m_Phenology[JulDay] == 0)
        {
        LeafMR = m_MR(O_Leaf.m_C, O_Leaf.m_N, airT, O_PlantPara.m_LeafResRate * O_PlantPara.m_DorResFraction);
        ShootMR = m_MR(O_ShootBase.m_C, O_ShootBase.m_N, soilT, (O_PlantPara.m_ShootResRate * O_PlantPara.m_DorResFraction));
        RhizomeMR = m_MR(O_Rhizome.m_C, O_Rhizome.m_N, soilT, (O_PlantPara.m_RhizomeResRate * O_PlantPara.m_DorResFraction));
        FRootMR = m_MR(O_FRoot.m_C, O_FRoot.m_N, soilT, (O_PlantPara.m_FRootResRate * O_PlantPara.m_DorResFraction));
        CRootMR = m_MR(O_CRoot.m_C, O_CRoot.m_N, soilT, (O_PlantPara.m_CRootResRate * O_PlantPara.m_DorResFraction));
        }
else
        {
        LeafMR = m_MR(O_Leaf.m_C, O_Leaf.m_N, airT, O_PlantPara.m_LeafResRate);
        ShootMR = m_MR(O_ShootBase.m_C, O_ShootBase.m_N, soilT, O_PlantPara.m_ShootResRate);
        RhizomeMR = m_MR(O_Rhizome.m_C, O_Rhizome.m_N, soilT, O_PlantPara.m_RhizomeResRate);
        FRootMR = m_MR(O_FRoot.m_C, O_FRoot.m_N, soilT, O_PlantPara.m_FRootResRate);
        CRootMR = m_MR(O_CRoot.m_C, O_CRoot.m_N, soilT, O_PlantPara.m_CRootResRate);
        }

        if(m_LAI < O_PlantPara.m_MinLAI)
        {
        LeafMR *= 0.3;
        ShootMR *= 0.3;
        RhizomeMR *= 0.3;
        FRootMR *= 0.3;
        CRootMR *= 0.3;
        }

O_Leaf.m_C -= LeafMR;
O_ShootBase.m_C -= ShootMR;
O_Rhizome.m_C -= RhizomeMR;
O_FRoot.m_C -= FRootMR;
O_CRoot.m_C -= CRootMR;

GR = m_GR(m_GPPvalue, (LeafMR + ShootMR + FRootMR + CRootMR + RhizomeMR));

m_ARvalue = GR + LeafMR + ShootMR + FRootMR + CRootMR + RhizomeMR;

m_NPPvalue = m_GPPvalue - m_ARvalue;

return (GR + LeafMR + ShootMR + FRootMR + CRootMR + RhizomeMR);
}

float WEMplant::m_MR(float m_C, float m_N, float temperature, float r)
{
float MR;
/* This one is based on the algorithm */
/*
        float ft = exp(308.56 * (1.0/56.02 - 1.0 / (temperature + 46.02)));
        MR = r * m_N * ft;
        if(MR >= 0.25 * m_C)
                {
                MR = 0.25 * m_C;
                }
*/
// Xiaofeng changed it to TEM's algorithm on August 21, 2008
if(temperature > 50) temperature = 50;
if(temperature < -10) temperature = -10;

MR = r * m_C * exp(0.0693 * temperature);
return MR;
}

float WEMplant::m_GR(float GPP, float MR)
{
float GR;
        if(GPP <= MR) GR = 0.0;
        else
        {
        GR = 0.2 * (GPP - MR);
        }
return GR;
}

void WEMplant::m_Allocation(WEMplantparameter O_PlantPara, float gpp, int JulDay, float fireinten, float leafrecovery, float plantfrac)
{
static int postday = 0;
if(fireinten > 0.1)       postday = 1;

//cout<<"here1"<<O_ShootBase.m_P<<endl;
// First allocate carbon to leaf for photosynthesis
//if(m_LAI < O_PlantPara.m_MaxLAI && O_PlantPara.m_Phenology[JulDay-1] == 1)
if(m_LAI < O_PlantPara.m_MaxLAI * leafrecovery && (O_PlantPara.m_Phenology[JulDay-1] == 1 || O_PlantPara.m_Phenology[JulDay-1] == 2 || O_PlantPara.m_Phenology[JulDay-1] == 3))
        {
        O_Leaf.m_C += gpp * (((O_PlantPara.m_MaxLAI * leafrecovery / O_PlantPara.m_SLA * plantfrac - O_Leaf.m_C) / (O_PlantPara.m_MaxLAI * leafrecovery / O_PlantPara.m_SLA * plantfrac)) * O_PlantPara.m_ToLeafC1 + O_PlantPara.m_ToLeafC2);
        gpp -= gpp * (((O_PlantPara.m_MaxLAI * leafrecovery / O_PlantPara.m_SLA * plantfrac - O_Leaf.m_C) / (O_PlantPara.m_MaxLAI * leafrecovery / O_PlantPara.m_SLA * plantfrac)) * O_PlantPara.m_ToLeafC1 + O_PlantPara.m_ToLeafC2);
        }
else
        {
        O_Leaf.m_C += gpp * O_PlantPara.m_ToLeafC2;
        gpp -= gpp * O_PlantPara.m_ToLeafC2;
        }


float totalc = O_Leaf.m_C + O_ShootBase.m_C + O_Rhizome.m_C + O_CRoot.m_C + O_FRoot.m_C;
float totaln = O_Leaf.m_N + O_ShootBase.m_N + O_Rhizome.m_N + O_CRoot.m_N + O_FRoot.m_N;
float totalp = O_Leaf.m_P + O_ShootBase.m_P + O_Rhizome.m_P + O_CRoot.m_P + O_FRoot.m_P;

        float minStorageC = 0.1 * totalc;
        float maxStorageC = 0.3 * totalc;

        float minStorageN = 0.1 * totaln;
        float maxStorageN = 0.3 * totaln;

        float minStorageP = 0.1 * totalp;
        float maxStorageP = 0.3 * totalp;

        if(O_ShootBase.m_C > maxStorageC)
        {
//        if(m_LAI < O_PlantPara.m_MaxLAI)
                O_Leaf.m_C += (O_ShootBase.m_C - maxStorageC) / 3.0;
                O_FRoot.m_C += (O_ShootBase.m_C - maxStorageC) / 3.0;
                O_CRoot.m_C += (O_ShootBase.m_C - maxStorageC) / 3.0;
//        else
//                O_Rhizome.m_C += (O_ShootBase.m_C - maxStorageC);

        O_ShootBase.m_C = maxStorageC;
        }

        if(O_ShootBase.m_N > maxStorageN)
        {
        //O_Leaf.m_N.m_Grid[row][col] += (O_Storage.m_N.m_Grid[row][col] - maxStorageN);
        float extran = (O_ShootBase.m_N - maxStorageN);
        m_AllocationN(extran, O_PlantPara);
        O_ShootBase.m_N = maxStorageN;
        }

        if(O_ShootBase.m_P > maxStorageP)
        {
        //O_Leaf.m_P.m_Grid[row][col] += (O_Storage.m_P.m_Grid[row][col] - maxStorageP);
        float extrap = (O_ShootBase.m_P - maxStorageP);
        m_AllocationP(extrap, O_PlantPara);
        O_ShootBase.m_P = maxStorageP;
        }

// Adjust the p concentration in leaf to make the photosynthesis maximum
        if((O_Leaf.m_C > 0) && (O_Leaf.m_P > 0) && (m_LAI < O_PlantPara.m_MaxLAI / 2.0))
       {
        float lpc = 31000.0 * O_Leaf.m_P / (O_Leaf.m_C * 12.0);
        if(lpc < (O_PlantPara.m_MaxLeafP + O_PlantPara.m_MinLeafP) / 2.0)
        {
                if(O_ShootBase.m_P > (((O_PlantPara.m_MaxLeafP + O_PlantPara.m_MinLeafP) / 2.0) - lpc) / ((O_PlantPara.m_MaxLeafP + O_PlantPara.m_MinLeafP) / 2.0) * O_Leaf.m_P)
                {
                        O_Leaf.m_P += (((O_PlantPara.m_MaxLeafP + O_PlantPara.m_MinLeafP) / 2.0) - lpc) / ((O_PlantPara.m_MaxLeafP + O_PlantPara.m_MinLeafP) / 2.0) * O_Leaf.m_P;
                        O_ShootBase.m_P -= (((O_PlantPara.m_MaxLeafP + O_PlantPara.m_MinLeafP) / 2.0) - lpc) / ((O_PlantPara.m_MaxLeafP + O_PlantPara.m_MinLeafP) / 2.0) * O_Leaf.m_P;
                }
                else
                {
                        O_Leaf.m_P += O_ShootBase.m_P * 0.9;
                        O_ShootBase.m_P = O_ShootBase.m_P * 0.1;
                }
        }
       }
//       cout<<"here2 "<<O_ShootBase.m_P<<endl;
//end
//Fill storage C pool with certain percentage

if(m_LAI > (O_PlantPara.m_MaxLAI / 2.0) && gpp > 0)
{
        if((gpp * O_PlantPara.m_GPPtoStorage) < (maxStorageC - O_ShootBase.m_C))
        {
        O_ShootBase.m_C += gpp * O_PlantPara.m_GPPtoStorage;
        gpp -= gpp * O_PlantPara.m_GPPtoStorage;
        }
        else
        {
        O_ShootBase.m_C = maxStorageC;
        gpp -= (maxStorageC - O_ShootBase.m_C);
        }
} // End of fucntion of filling storage C

        if(O_PlantPara.m_Phenology[JulDay-1] != 5) //O_PlantPara.m_Phenology[JulDay-1] != 1 &&
        {
                // fill stroage carbon pool
                if(O_ShootBase.m_C <= minStorageC)
                {
                O_CRoot.m_C -= (minStorageC - O_ShootBase.m_C);
                O_ShootBase.m_C = minStorageC;
                }
                else
                {
                        if(O_ShootBase.m_C >= maxStorageC)
                        {
                                if(m_LAI < O_PlantPara.m_MaxLAI)
                                {
                                if(postday > 0.01 && postday < 6)
                                        {
                                        O_Leaf.m_C += (O_ShootBase.m_C - maxStorageC);
                                        postday ++;
                                        }
                                else
                                        {
                                        O_CRoot.m_C += (O_ShootBase.m_C - maxStorageC);
                                        }

                                }
                                else
                                {
                                gpp -= gpp * O_PlantPara.m_GPPtoStorage;
                                O_ShootBase.m_C += gpp * O_PlantPara.m_GPPtoStorage;
                                }
                        }
                }

                // end of fill storage carbon pool

                // fill storage nitrogen pool
                if(O_ShootBase.m_N <= minStorageN)
                {
                O_CRoot.m_N -= (minStorageN - O_ShootBase.m_N);
                O_ShootBase.m_N = minStorageN;
                }
                else
                {
                        if(O_ShootBase.m_N >= maxStorageN)
                        {
                        float extran = O_ShootBase.m_N - maxStorageN;
                        m_AllocationN(extran, O_PlantPara);
                        O_ShootBase.m_N = maxStorageN;
                        }
                }
                // end of fill storage nitrogen pool

                // fill storage phosphorus pool
                if(O_ShootBase.m_P <= minStorageP)
                {
                        if(O_CRoot.m_P >= (minStorageP - O_ShootBase.m_P))
                        {
                        O_CRoot.m_P -= (minStorageP - O_ShootBase.m_P);
                        O_ShootBase.m_P = minStorageP;
                        }
                }
                else
                {
                        if(O_ShootBase.m_P >= maxStorageP)
                        {
                        float extrap = O_ShootBase.m_P - maxStorageP;   // To leaf, Xiaofeng change it to allocation based on DPI
                        m_AllocationP(extrap, O_PlantPara);
                        O_ShootBase.m_P = maxStorageP;
                        }
                }
                // end of fill storage phosphorus pool
        }

m_RootExudation.m_C = 0.0;

m_RootExudation.m_N = 0.0;

m_RootExudation.m_P = 0.0;

        m_RootExudation.m_C = exp(-5.0) * O_FRoot.m_C;// / g_Min(Nstatus, Pstatus);
        O_FRoot.m_C -= m_RootExudation.m_C;

        if((O_FRoot.m_N > 10e-5) && O_FRoot.m_C < (O_PlantPara.m_OptFRootCNratio * O_FRoot.m_N))
        m_RootExudation.m_N = exp(-5.0) * O_FRoot.m_N * (1.0 - O_FRoot.m_C / O_PlantPara.m_OptFRootCNratio / O_FRoot.m_N);// / Pstatus;
        else    m_RootExudation.m_N = 0.0;

        if(m_RootExudation.m_N > (0.8 * O_FRoot.m_N))
                {
                m_RootExudation.m_N = 0.8 * O_FRoot.m_N;
                O_FRoot.m_N = 0.2 * O_FRoot.m_N;
                }

        O_FRoot.m_N -= m_RootExudation.m_N;

//        cout<<O_FRoot.m_C<<" OKOK "<<O_FRoot.m_P<<endl;
        if((O_FRoot.m_P > 10e-5) && O_FRoot.m_C < (O_PlantPara.m_OptFRootCPratio * O_FRoot.m_P))
        m_RootExudation.m_P = exp(-5.0) * O_FRoot.m_P * (1.0 - O_FRoot.m_C / O_PlantPara.m_OptFRootCPratio / O_FRoot.m_P);// / Pstatus;
        else    m_RootExudation.m_P = 0.0;

        if(m_RootExudation.m_P > (0.8 * O_FRoot.m_P))
                {
                m_RootExudation.m_P = 0.8 * O_FRoot.m_P;
                O_FRoot.m_P = 0.2 * O_FRoot.m_P;
                }

        O_FRoot.m_P -= m_RootExudation.m_P;
//        cout<<O_FRoot.m_C<<" OKOK "<<O_FRoot.m_P<<endl;



        if(gpp < 0) gpp = 0.0;

        if((m_LeafDCI + m_ShootDCI + m_RhizomeDCI + m_FRootDCI + m_CRootDCI) == 0)
        {
//        O_Leaf.m_C.m_Grid[row][col] += gpp * O_PlantPara.m_GPPtoLeaf;
// Xiaofeng block the following on May 31, 2009
//        O_Rhizome.m_C += gpp * O_PlantPara.m_GPPtoShoot;
//        O_FRoot.m_C += gpp * O_PlantPara.m_GPPtoFRoot;
//        O_CRoot.m_C += gpp * O_PlantPara.m_GPPtoCRoot;
m_ARvalue += gpp;
        }
        else
        {
//                if(m_LAI > O_PlantPara.m_MaxLAI)
//                {
//                        if((m_RhizomeDCI + m_ShootDCI + m_FRootDCI + m_CRootDCI) <= 10e-5)
//                        {
//                        O_Rhizome.m_C += 0.0;
//                        O_ShootBase.m_C += 0.0;
//                        O_FRoot.m_C += 0.0;
//                        O_CRoot.m_C += 0.0;
//                        }
//                        else
//                        {
//                        O_Rhizome.m_C += gpp * O_PlantPara.m_GPPtoRhizome;
//                        gpp -= gpp * O_PlantPara.m_GPPtoRhizome;

//                        O_ShootBase.m_C += gpp * m_ShootDCI / (m_ShootDCI + m_FRootDCI + m_CRootDCI);
//                        O_FRoot.m_C += gpp * m_FRootDCI / (m_ShootDCI + m_FRootDCI + m_CRootDCI);
//                        O_CRoot.m_C += gpp * m_CRootDCI / (m_ShootDCI + m_FRootDCI + m_CRootDCI);

/*
                        O_Rhizome.m_C += gpp * m_RhizomeDCI / (m_RhizomeDCI + m_ShootDCI + m_FRootDCI + m_CRootDCI);
                        O_ShootBase.m_C += gpp * m_ShootDCI / (m_RhizomeDCI + m_ShootDCI + m_FRootDCI + m_CRootDCI);
                        O_FRoot.m_C += gpp * m_FRootDCI / (m_RhizomeDCI + m_ShootDCI + m_FRootDCI + m_CRootDCI);
                        O_CRoot.m_C += gpp * m_CRootDCI / (m_RhizomeDCI + m_ShootDCI + m_FRootDCI + m_CRootDCI);
*/
//                        }
//                }
//                else
                {
                        O_Rhizome.m_C += gpp * O_PlantPara.m_GPPtoRhizome;
                        gpp -= gpp * O_PlantPara.m_GPPtoRhizome;

                O_Leaf.m_C += gpp * m_LeafDCI / (m_LeafDCI + m_ShootDCI + m_FRootDCI + m_CRootDCI);
                O_ShootBase.m_C += gpp * m_ShootDCI / (m_LeafDCI + m_ShootDCI + m_FRootDCI + m_CRootDCI);
                O_FRoot.m_C += gpp * m_FRootDCI / (m_LeafDCI + m_ShootDCI + m_FRootDCI + m_CRootDCI);
                O_CRoot.m_C += gpp * m_CRootDCI / (m_LeafDCI + m_ShootDCI + m_FRootDCI + m_CRootDCI);

/*
                O_Leaf.m_C += gpp * m_LeafDCI / (m_LeafDCI + m_ShootDCI + m_RhizomeDCI + m_FRootDCI + m_CRootDCI);
                O_ShootBase.m_C += gpp * m_ShootDCI / (m_LeafDCI + m_ShootDCI + m_RhizomeDCI + m_FRootDCI + m_CRootDCI);
                O_Rhizome.m_C += gpp * m_RhizomeDCI / (m_LeafDCI + m_ShootDCI + m_RhizomeDCI + m_FRootDCI + m_CRootDCI);
                O_FRoot.m_C += gpp * m_FRootDCI / (m_LeafDCI + m_ShootDCI + m_RhizomeDCI + m_FRootDCI + m_CRootDCI);
                O_CRoot.m_C += gpp * m_CRootDCI / (m_LeafDCI + m_ShootDCI + m_RhizomeDCI + m_FRootDCI + m_CRootDCI);
*/                }
        }


// Re-allocation

// End of Re-allocation
}

void WEMplant::m_AllocationN(float nuptake, WEMplantparameter O_PlantPara)
{
if(O_Leaf.m_N < O_Leaf.m_C / O_PlantPara.m_OptLeafCNratio)
        {
        O_Leaf.m_N += nuptake * 0.05;
        nuptake -= nuptake * 0.05;
        }

if(O_ShootBase.m_N < O_ShootBase.m_C / O_PlantPara.m_OptShootCNratio)
        {
        O_ShootBase.m_N += nuptake * 0.05;
        nuptake -= nuptake * 0.05;
        }

        if((m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI) >= 2.5)
        {
                if(m_LeafDNI > (0.5))
                {
                O_Leaf.m_N += nuptake * 0.1;
                nuptake -= nuptake * 0.1;
                }
        O_Leaf.m_N += nuptake * (0.5 + m_LeafDNI) / (2.5 + m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
        O_ShootBase.m_N += nuptake * (0.5 + m_ShootDNI) / (2.5 + m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
        O_Rhizome.m_N += nuptake * (0.5 + m_RhizomeDNI) / (2.5 + m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
        O_FRoot.m_N += nuptake * (0.5 + m_FRootDNI) / (2.5 + m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
        O_CRoot.m_N += nuptake * (0.5 + m_CRootDNI) / (2.5 + m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
        }
        else
        {
        if((m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI) > 0.25)
                {
                O_Leaf.m_N += nuptake * 0.05;
                nuptake -= nuptake * 0.05;
                O_Leaf.m_N += nuptake * m_LeafDNI / (m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
                O_ShootBase.m_N += nuptake * m_ShootDNI / (m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
                O_Rhizome.m_N += nuptake * m_RhizomeDNI / (m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
                O_FRoot.m_N += nuptake * m_FRootDNI / (m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
                O_CRoot.m_N += nuptake * m_CRootDNI / (m_LeafDNI + m_ShootDNI + m_RhizomeDNI + m_FRootDNI + m_CRootDNI);
                }
                else
                {
                m_RootExudation.m_N += nuptake;
                nuptake = 0.0;
                }
        }
}


void WEMplant::m_AllocationP(float puptake, WEMplantparameter O_PlantPara)
{
//cout<<"puptake: "<<puptake<<endl;
//cout<<"before"<<O_Leaf.m_P + O_ShootBase.m_P + O_Rhizome.m_P + O_FRoot.m_P + O_CRoot.m_P<<endl;
//cout<<"before"<<m_LeafDPI<<" "<<m_ShootDPI<<" "<<m_RhizomeDPI<<" "<<m_FRootDPI<<" "<<m_CRootDPI<<endl;

if(O_Leaf.m_P < O_Leaf.m_C / O_PlantPara.m_OptLeafCPratio)
        {
        O_Leaf.m_P += puptake * 0.05;
        puptake -= puptake * 0.05;
        }

if(O_ShootBase.m_P < O_ShootBase.m_C / O_PlantPara.m_OptShootCPratio)
        {
        O_ShootBase.m_P += puptake * 0.05;
        puptake -= puptake * 0.05;
        }

        if((m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI) >= 2.5)
        {
                if(m_LeafDPI > (0.5))
                {
                O_Leaf.m_P += puptake * 0.1;
                puptake -= puptake * 0.1;
                }
        O_Leaf.m_P += puptake * (0.5 + m_LeafDPI) / (2.5 + m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
        O_ShootBase.m_P += puptake * (0.5 + m_ShootDPI) / (2.5 + m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
        O_Rhizome.m_P += puptake * (0.5 + m_RhizomeDPI) / (2.5 + m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
        O_FRoot.m_P += puptake * (0.5 + m_FRootDPI) / (2.5 + m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
        O_CRoot.m_P += puptake * (0.5 + m_CRootDPI) / (2.5 + m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
        }
        else
        {
        if((m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI) > 0.25)
                {
                O_Leaf.m_P += puptake * 0.05;
                puptake -= puptake * 0.05;
                O_Leaf.m_P += puptake * m_LeafDPI / (m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
                O_ShootBase.m_P += puptake * m_ShootDPI / (m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
                O_Rhizome.m_P += puptake * m_RhizomeDPI / (m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
                O_FRoot.m_P += puptake * m_FRootDPI / (m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
                O_CRoot.m_P += puptake * m_CRootDPI / (m_LeafDPI + m_ShootDPI + m_RhizomeDPI + m_FRootDPI + m_CRootDPI);
                }
                else
                {
                m_RootExudation.m_P += puptake;
                puptake = 0.0;
                }
        }

//cout<<"after"<<m_LeafDPI<<" "<<m_ShootDPI<<" "<<m_RhizomeDPI<<" "<<m_FRootDPI<<" "<<m_CRootDPI<<endl;
//cout<<"after"<<O_Leaf.m_P + O_ShootBase.m_P + O_Rhizome.m_P + O_FRoot.m_P + O_CRoot.m_P<<endl;
}


float WEMplant::m_PARcalculation(float lat, int JulDay)
{
//cout<<"Lat: "<<lat<<" JulDay: "<<JulDay<<endl;
float PAR;
float solarradiation;
float daylength, ampl, soldec1, solcosdec, solevev_sine, latrad, solaltcorr, soldec, solrisset_ha1, solrisset_ha;
latrad = lat * O_Cons.m_PI / 180.0;
//ampl = exp(7.42 + 0.045 * latrad * 180.0 / PI) / 3600.0;
//daylength = ampl * sin((JulDay - 79.0) * 0.001721) + 12.0;
soldec1 = 0.39875 * sin(4.868961 + 0.017203 * JulDay + 0.033446 * sin(6.224111 + 0.017202 * JulDay));
//solcosdec = sqrt(1.0 - soldec1 * soldec1);
//solevev_sine = sin(latrad) * soldec1 + cos(latrad) * solcosdec;
//solaltcorr = 1.0 - exp(-0.014 * (alt - 274.0) / (solevev_sine * 274.0));
soldec = atan(soldec1 / sqrt(1.0 - soldec1 * soldec1));
//cout<<"For Daylength! "<<soldec<<endl;
solrisset_ha1 = -tan(latrad) * tan(soldec);

solrisset_ha = (solrisset_ha1 == 0.0)?(O_Cons.m_PI * 0.5):((solrisset_ha1 < 0.0)?(O_Cons.m_PI + atan(sqrt(1.0 - solrisset_ha1 * solrisset_ha1)/solrisset_ha1)):(atan(sqrt(1.0 - solrisset_ha1 * solrisset_ha1)/solrisset_ha1)));
solarradiation = 458.37 * 2.0 * (1.0 + 0.033 * cos(360.0/365.0*O_Cons.m_PI/180.0*JulDay))*(cos(latrad)*cos(soldec)*sin(solrisset_ha) + solrisset_ha * 180.0 / (57.296 * O_Cons.m_PI) * sin(latrad) * sin(soldec));
//cout<<"Fro Par: "<<solrisset_ha<<endl;
PAR = 0.45 * solarradiation;
//cout<<PAR<<endl;
return PAR;
}

void WEMplant::m_CalDI(WEMplantparameter O_PlantPara)
{

if((O_Leaf.m_C < 10e-2) && (O_ShootBase.m_C + O_Rhizome.m_C + O_FRoot.m_C + O_CRoot.m_C) < 5)
m_LeafDCI = 0.5;
else
m_LeafDCI = log(O_PlantPara.m_MaxBiomassC / (O_Leaf.m_C + O_ShootBase.m_C + O_Rhizome.m_C + O_FRoot.m_C + O_CRoot.m_C));

if(m_LeafDCI < -0.5)  m_LeafDCI = -0.5;
if(m_LeafDCI > 0.5)  m_LeafDCI = 0.5;



if((O_Leaf.m_C < 10e-1) || (O_Leaf.m_N  < 10e-2))     m_LeafDNI = 0.5;
else
m_LeafDNI = log(O_Leaf.m_C / O_Leaf.m_N / O_PlantPara.m_OptLeafCNratio);

//cout<<O_Leaf.m_C<<" "<<O_Leaf.m_N<<" "<<O_PlantPara.m_OptLeafCNratio<<" "<<m_LeafDNI<<endl;

if(m_LeafDNI < -0.5)  m_LeafDNI = -0.5;
if(m_LeafDNI > 0.5)  m_LeafDNI = 0.5;

if((O_Leaf.m_C < 10e-1) || (O_Leaf.m_P  < 10e-2))     m_LeafDPI = 0.5;
else
m_LeafDPI = log(O_Leaf.m_C / O_Leaf.m_P / O_PlantPara.m_OptLeafCPratio);

if(m_LeafDPI < -0.5)  m_LeafDPI = -0.5;
if(m_LeafDPI > 0.5)  m_LeafDPI = 0.5;



if(O_ShootBase.m_C  < 10e-2)        m_ShootDCI = 0.5;
else
m_ShootDCI = log(O_PlantPara.m_MaxBiomassC * O_PlantPara.m_GPPtoShoot / O_ShootBase.m_C);

if(m_ShootDCI < -0.5)  m_ShootDCI = -0.5;
if(m_ShootDCI > 0.5)  m_ShootDCI = 0.5;


if((O_ShootBase.m_C < 10e-2) || (O_ShootBase.m_N  < 10e-2))     m_ShootDNI = 0.5;
else
m_ShootDNI = log(O_ShootBase.m_C / O_ShootBase.m_N / O_PlantPara.m_OptShootCNratio);


if(m_ShootDNI < -0.5)  m_ShootDNI = -0.5;
if(m_ShootDNI > 0.5)  m_ShootDNI = 0.5;



if((O_ShootBase.m_C < 10e-2) || (O_ShootBase.m_P  < 10e-2))     m_ShootDPI = 0.5;
else
m_ShootDPI = log(O_ShootBase.m_C / O_ShootBase.m_P / O_PlantPara.m_OptShootCPratio);

if(m_ShootDPI < -0.5)  m_ShootDPI = -0.5;
if(m_ShootDPI > 0.5)  m_ShootDPI = 0.5;




if(O_Rhizome.m_C  < 10e-2)        m_RhizomeDCI = 0.5;
else
m_RhizomeDCI = log(O_PlantPara.m_MaxBiomassC * O_PlantPara.m_GPPtoRhizome / O_Rhizome.m_C);

if(m_RhizomeDCI < -0.5)  m_RhizomeDCI = -0.5;
if(m_RhizomeDCI > 0.5)  m_RhizomeDCI = 0.5;



if((O_Rhizome.m_C  < 10e-2) || (O_Rhizome.m_N  < 10e-2))     m_RhizomeDNI = 0.5;
else
m_RhizomeDNI = log(O_Rhizome.m_C / O_Rhizome.m_N / O_PlantPara.m_OptRhizomeCNratio);

if(m_RhizomeDNI < -0.5)  m_RhizomeDNI = -0.5;
if(m_RhizomeDNI > 0.5)  m_RhizomeDNI = 0.5;




if((O_Rhizome.m_C  < 10e-2) || (O_Rhizome.m_P  < 10e-2))     m_RhizomeDPI = 0.5;
else
m_RhizomeDPI = log(O_Rhizome.m_C / O_Rhizome.m_P / O_PlantPara.m_OptRhizomeCPratio);

if(m_RhizomeDPI < -0.5)  m_RhizomeDPI = -0.5;
if(m_RhizomeDPI > 0.5)  m_RhizomeDPI = 0.5;




if(O_FRoot.m_C  < 10e-2)        m_FRootDCI = 0.5;
else
m_FRootDCI = log(O_PlantPara.m_MaxBiomassC * O_PlantPara.m_GPPtoFRoot / O_FRoot.m_C);


if(m_FRootDCI < -0.5)  m_FRootDCI = -0.5;
if(m_FRootDCI > 0.5)  m_FRootDCI = 0.5;




if((O_FRoot.m_C  < 10e-2) || (O_FRoot.m_N  < 10e-2))     m_FRootDNI = 0.5;
else
m_FRootDNI = log(O_FRoot.m_C / O_FRoot.m_N / O_PlantPara.m_OptFRootCNratio);

if(m_FRootDNI < -0.5)  m_FRootDNI = -0.5;
if(m_FRootDNI > 0.5)  m_FRootDNI = 0.5;



if((O_FRoot.m_C  < 10e-2) || (O_FRoot.m_P  < 10e-2))     m_FRootDPI = 0.5;
else
m_FRootDPI = log(O_FRoot.m_C / O_FRoot.m_P / O_PlantPara.m_OptFRootCPratio);

if(m_FRootDPI < -0.5)  m_FRootDPI = -0.5;
if(m_FRootDPI > 0.5)  m_FRootDPI = 0.5;



if(O_CRoot.m_C  < 10e-2)        m_CRootDCI = 0.5;
else
m_CRootDCI = log(O_PlantPara.m_MaxBiomassC * O_PlantPara.m_GPPtoCRoot / O_CRoot.m_C);


if(m_CRootDCI < -0.5)  m_CRootDCI = -0.5;
if(m_CRootDCI > 0.5)  m_CRootDCI = 0.5;


if((O_CRoot.m_C  < 10e-2) || (O_CRoot.m_N  < 10e-2))     m_CRootDNI = 0.5;
else
m_CRootDNI = log(O_CRoot.m_C / O_CRoot.m_N / O_PlantPara.m_OptCRootCNratio);

if(m_CRootDNI < -0.5)  m_CRootDNI = -0.5;
if(m_CRootDNI > 0.5)  m_CRootDNI = 0.5;



if((O_CRoot.m_C  < 10e-2) || (O_CRoot.m_P  < 10e-2))     m_CRootDPI = 0.5;
else
m_CRootDPI = log(O_CRoot.m_C / O_CRoot.m_P / O_PlantPara.m_OptCRootCPratio);

if(m_CRootDPI < -0.5)  m_CRootDPI = -0.5;
if(m_CRootDPI > 0.5)  m_CRootDPI = 0.5;

m_LeafDCI += 0.5;
m_LeafDNI += 0.5;
m_LeafDPI += 0.5;

m_ShootDCI += 0.5;
m_ShootDNI += 0.5;
m_ShootDPI += 0.5;

m_RhizomeDCI += 0.5;
m_RhizomeDNI += 0.5;
m_RhizomeDPI += 0.5;

m_FRootDCI += 0.5;
m_FRootDNI += 0.5;
m_FRootDPI += 0.5;

m_CRootDCI += 0.5;
m_CRootDNI += 0.5;
m_CRootDPI += 0.5;

m_ShootDCI *= 0.25;
m_RhizomeDCI *= 0.1;

if(m_LeafDCI > 0.05 || m_FRootDCI > 0.05 || m_CRootDCI > 0.05)
{
m_ShootDCI *= 0.15;
m_RhizomeDCI = 0.0;
}

}
float WEMplant::m_SeasonEffect(int startday, int peakday, int sceday, int JulDay, float minimum)
{
float phenology;
if(JulDay <= startday || JulDay >= sceday)        phenology = minimum;
else
        {
        if(JulDay <= peakday)
        phenology = minimum + 1. / (1. + exp((peakday + startday) / 2. - JulDay));
        else
        phenology = minimum + 1. / (1. + exp(JulDay - (sceday + peakday) / 2.));
        }
if(phenology < minimum) phenology = minimum;
if(phenology > 1) phenology = 1;

//cout<<"Julday"<<JulDay<<" season "<<phenology<<endl;
return phenology;
}

// Xiaofeng use this function to replace the following one on December 12, 2008
void WEMplant::m_LitterSeedUpdate(WEMplantparameter O_PlantPara, int JulDay, float waterdepth, float plantfrac)
{
float temp = (2.0 * waterdepth - 1.0) * O_PlantPara.m_WDonGerm;
float wdeffect = exp(-1.0 * temp) / (1.0 + exp(-1.0 * temp));

if(waterdepth < 0.0)      wdeffect = 1.0;
if(waterdepth > 1.0)      wdeffect = 0.0;

//float leftwdeffect = 1.0 - wdeffect;
float leftwdeffect = 0.;

float season = m_SeasonEffect(O_PlantPara.m_StartDay, O_PlantPara.m_PeakDay, O_PlantPara.m_SenesceDay, JulDay, O_PlantPara.m_SeasonMin);

if(JulDay < O_PlantPara.m_PeakDay && O_PlantPara.m_Phenology[JulDay] == 1)
        {
        if((O_Leaf.m_C + O_ShootBase.m_C + O_Rhizome.m_C + O_CRoot.m_C + O_FRoot.m_C) < (O_PlantPara.m_MaxBiomassC))
                {
                O_Leaf.m_C += wdeffect * O_Rhizome.m_C * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;
                O_Leaf.m_N += wdeffect * O_Rhizome.m_N * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;
                O_Leaf.m_P += wdeffect * O_Rhizome.m_P * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;

                O_Rhizome.m_C -= wdeffect * O_Rhizome.m_C * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;
                O_Rhizome.m_N -= wdeffect * O_Rhizome.m_N * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;
                O_Rhizome.m_P -= wdeffect * O_Rhizome.m_P * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;

                O_DeadBG.m_C += leftwdeffect * O_Rhizome.m_C * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;
                O_DeadBG.m_N += leftwdeffect * O_Rhizome.m_N * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;
                O_DeadBG.m_P += leftwdeffect * O_Rhizome.m_P * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;

                O_Rhizome.m_C -= O_Rhizome.m_C * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;
                O_Rhizome.m_N -= O_Rhizome.m_N * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;
                O_Rhizome.m_P -= O_Rhizome.m_P * (1. - season) * (1. - season) * O_PlantPara.m_MinToLeaf;

                }
        else
                {
                ;
                }
        }
/*
        if((O_Leaf.m_C < O_PlantPara.m_MaxLAI / O_PlantPara.m_SLA) && O_PlantPara.m_Phenology[JulDay] == 2)
        {
        float temp = ((O_PlantPara.m_MaxLAI / O_PlantPara.m_SLA - O_Leaf.m_C) / (O_PlantPara.m_MaxLAI / O_PlantPara.m_SLA));
        if(temp > 0.1)  temp = 0.1;
                O_Leaf.m_C += O_Rhizome.m_C * temp;
                O_Leaf.m_N += O_Rhizome.m_N * temp;
                O_Leaf.m_P += O_Rhizome.m_P * temp;

                O_Rhizome.m_C -= O_Rhizome.m_C * temp;
                O_Rhizome.m_N -= O_Rhizome.m_N * temp;
                O_Rhizome.m_P -= O_Rhizome.m_P * temp;
        }
*/
if(O_PlantPara.m_Phenology[JulDay] == 5)
        {
                O_Litter.m_C += O_Leaf.m_C * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf;

                O_ShootBase.m_N += O_Leaf.m_N * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf * O_PlantPara.m_ResorptionN;
                O_Leaf.m_N += O_Leaf.m_N * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf * O_PlantPara.m_ResorptionN;
                O_Litter.m_N += O_Leaf.m_N * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf * (1.0 - O_PlantPara.m_ResorptionN);

                O_ShootBase.m_P += O_Leaf.m_P * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf * O_PlantPara.m_ResorptionN;
                O_Leaf.m_P += O_Leaf.m_P * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf * O_PlantPara.m_ResorptionN;
                O_Litter.m_P += O_Leaf.m_P * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf * (1.0 - O_PlantPara.m_ResorptionN);

                O_Leaf.m_C -= O_Leaf.m_C * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf;
                O_Leaf.m_N -= O_Leaf.m_N * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf;
                O_Leaf.m_P -= O_Leaf.m_P * (1. - season) * (1. - season) * O_PlantPara.m_KToLeaf;
        }

if(JulDay > O_PlantPara.m_PeakDay)
        {
                if(m_LAI > O_PlantPara.m_MinLAI)
                {
                O_Litter.m_C += O_Leaf.m_C * 0.005;
                O_Litter.m_N += O_Leaf.m_N * 0.005;
                O_Litter.m_C += O_Leaf.m_P * 0.005;

                O_Leaf.m_C -= O_Leaf.m_C * 0.005;
                O_Leaf.m_N -= O_Leaf.m_N * 0.005;
                O_Leaf.m_P -= O_Leaf.m_P * 0.005;
                }

                // Dead Belowground biomass
/*
                if(O_PlantPara.m_Phenology[JulDay] == 5)
                {

                O_DeadBG.m_C += O_ShootBase.m_C * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_N += O_ShootBase.m_N * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_P += O_ShootBase.m_P * O_PlantPara.m_BGLtoD;
                O_ShootBase.m_C -= O_ShootBase.m_C * O_PlantPara.m_BGLtoD;
                O_ShootBase.m_N -= O_ShootBase.m_N * O_PlantPara.m_BGLtoD;
                O_ShootBase.m_P -= O_ShootBase.m_P * O_PlantPara.m_BGLtoD;

                O_DeadBG.m_C += O_Rhizome.m_C * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_N += O_Rhizome.m_N * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_P += O_Rhizome.m_P * O_PlantPara.m_BGLtoD;
                O_Rhizome.m_C -= O_Rhizome.m_C * O_PlantPara.m_BGLtoD;
                O_Rhizome.m_N -= O_Rhizome.m_N * O_PlantPara.m_BGLtoD;
                O_Rhizome.m_P -= O_Rhizome.m_P * O_PlantPara.m_BGLtoD;

                O_DeadBG.m_C += O_CRoot.m_C * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_N += O_CRoot.m_N * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_P += O_CRoot.m_P * O_PlantPara.m_BGLtoD;
                O_CRoot.m_C -= O_CRoot.m_C * O_PlantPara.m_BGLtoD;
                O_CRoot.m_N -= O_CRoot.m_N * O_PlantPara.m_BGLtoD;
                O_CRoot.m_P -= O_CRoot.m_P * O_PlantPara.m_BGLtoD;

                O_DeadBG.m_C += O_FRoot.m_C * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_N += O_FRoot.m_N * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_P += O_FRoot.m_P * O_PlantPara.m_BGLtoD;
                O_FRoot.m_C -= O_FRoot.m_C * O_PlantPara.m_BGLtoD;
                O_FRoot.m_N -= O_FRoot.m_N * O_PlantPara.m_BGLtoD;
                O_FRoot.m_P -= O_FRoot.m_P * O_PlantPara.m_BGLtoD;
                }
*/
                if(O_PlantPara.m_Phenology[JulDay] != 0)
                {
                O_DeadBG.m_C += O_ShootBase.m_C * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_N += O_ShootBase.m_N * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_P += O_ShootBase.m_P * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_ShootBase.m_C -= O_ShootBase.m_C * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_ShootBase.m_N -= O_ShootBase.m_N * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_ShootBase.m_P -= O_ShootBase.m_P * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;

                O_DeadBG.m_C += O_Rhizome.m_C * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_N += O_Rhizome.m_N * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_P += O_Rhizome.m_P * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_Rhizome.m_C -= O_Rhizome.m_C * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_Rhizome.m_N -= O_Rhizome.m_N * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_Rhizome.m_P -= O_Rhizome.m_P * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;

                O_DeadBG.m_C += O_CRoot.m_C * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_N += O_CRoot.m_N * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_P += O_CRoot.m_P * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_CRoot.m_C -= O_CRoot.m_C * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_CRoot.m_N -= O_CRoot.m_N * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_CRoot.m_P -= O_CRoot.m_P * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;

                O_DeadBG.m_C += O_FRoot.m_C * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_N += O_FRoot.m_N * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_DeadBG.m_P += O_FRoot.m_P * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_FRoot.m_C -= O_FRoot.m_C * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_FRoot.m_N -= O_FRoot.m_N * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                O_FRoot.m_P -= O_FRoot.m_P * (1. - season) * (1. - season) * O_PlantPara.m_BGLtoD;
                }
        }


if(JulDay > O_PlantPara.m_PeakDay && O_PlantPara.m_Phenology[JulDay] == 0)
//if(O_PlantPara.m_Phenology[JulDay] == 0)
        {
        float minleafc;
        minleafc = O_PlantPara.m_MinLAI / O_PlantPara.m_SLA * plantfrac;

        if(m_LAI > O_PlantPara.m_MinLAI)
                {
                float ratio = pow((1.0 - minleafc / O_Leaf.m_C), 2.0);

                O_ShootBase.m_C += ratio * O_Leaf.m_C * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_ShootBase.m_N += ratio * O_Leaf.m_N * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_ShootBase.m_P += ratio * O_Leaf.m_P * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Leaf.m_C -= ratio * O_Leaf.m_C * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Leaf.m_N -= ratio * O_Leaf.m_N * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Leaf.m_P -= ratio * O_Leaf.m_P * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;

/*
                O_Rhizome.m_C += ratio * O_Leaf.m_C * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Rhizome.m_N += ratio * O_Leaf.m_N * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Rhizome.m_P += ratio * O_Leaf.m_P * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Leaf.m_C -= ratio * O_Leaf.m_C * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Leaf.m_N -= ratio * O_Leaf.m_N * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Leaf.m_P -= ratio * O_Leaf.m_P * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
*/

                O_Litter.m_C += ratio * O_Leaf.m_C * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;

                O_ShootBase.m_N += ratio * O_Leaf.m_N * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit * O_PlantPara.m_ResorptionN * 0.75;
                O_Leaf.m_N += ratio * O_Leaf.m_N * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit * O_PlantPara.m_ResorptionN * 0.25;
                O_Litter.m_N += ratio * O_Leaf.m_N * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit * (1.0 - O_PlantPara.m_ResorptionN);

                O_ShootBase.m_P += ratio * O_Leaf.m_P * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit * O_PlantPara.m_ResorptionN * 0.75;
                O_Leaf.m_P += ratio * O_Leaf.m_P * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit * O_PlantPara.m_ResorptionN * 0.25;
                O_Litter.m_P += ratio * O_Leaf.m_P * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit * (1.0 - O_PlantPara.m_ResorptionN);

                O_Leaf.m_C -= ratio * O_Leaf.m_C * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Leaf.m_N -= ratio * O_Leaf.m_N * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                O_Leaf.m_P -= ratio * O_Leaf.m_P * (1. - season) / (O_PlantPara.m_KLeafToLit + (1. - season)) * O_PlantPara.m_MinLeafToLit;
                }
        else
                {
                ;
                }
        }
/*
        if(O_Leaf.m_C < (O_PlantPara.m_MinLAI / O_PlantPara.m_SLA) && O_PlantPara.m_Phenology[JulDay] == 1)
                {
                O_Leaf.m_C += wdeffect * O_ShootBase.m_C * O_PlantPara.m_MinToLeaf;
                O_Leaf.m_N += wdeffect * O_ShootBase.m_N * O_PlantPara.m_MinToLeaf;
                O_Leaf.m_P += wdeffect * O_ShootBase.m_P * O_PlantPara.m_MinToLeaf;
                O_ShootBase.m_C -= wdeffect * O_ShootBase.m_C * O_PlantPara.m_MinToLeaf;
                O_ShootBase.m_N -= wdeffect * O_ShootBase.m_N * O_PlantPara.m_MinToLeaf;
                O_ShootBase.m_P -= wdeffect * O_ShootBase.m_P * O_PlantPara.m_MinToLeaf;

//                O_Leaf.m_C += wdeffect * O_Rhizome.m_C * O_PlantPara.m_MinToLeaf;
//                O_Leaf.m_N += wdeffect * O_Rhizome.m_N * O_PlantPara.m_MinToLeaf;
//                O_Leaf.m_P += wdeffect * O_Rhizome.m_P * O_PlantPara.m_MinToLeaf;
//                O_Rhizome.m_C -= wdeffect * O_Rhizome.m_C * O_PlantPara.m_MinToLeaf;
//                O_Rhizome.m_N -= wdeffect * O_Rhizome.m_N * O_PlantPara.m_MinToLeaf;
//                O_Rhizome.m_P -= wdeffect * O_Rhizome.m_P * O_PlantPara.m_MinToLeaf;
                }
*/
}


void WEMplant::m_Initilizing(string initialstate)
{
ifstream ini;
ini.open(initialstate.c_str());
if(!ini)
        {
        cout<<"The initial data file is not exist! "<<endl;
        exit(1);
        }
else
        {
        ini>>O_Leaf.m_C>>O_Leaf.m_N>>O_Leaf.m_P>>O_ShootBase.m_C>>O_ShootBase.m_N>>O_ShootBase.m_P
           >>O_Rhizome.m_C>>O_Rhizome.m_N>>O_Rhizome.m_P>>O_CRoot.m_C>>O_CRoot.m_N>>O_CRoot.m_P
           >>O_FRoot.m_C>>O_FRoot.m_N>>O_FRoot.m_P>>O_Litter.m_C>>O_Litter.m_N>>O_Litter.m_P
           >>O_DeadBG.m_C>>O_DeadBG.m_N>>O_DeadBG.m_P;
        }

}


void WEMplant::m_Burning(WEMatmosphere &O_Atm, WEMplantparameter O_PlantPara, float fireintensity, int day, float waterdepth,  float leafrecovery)
{
static int postday = 0;
if(fireintensity > 0.1)       postday = 1;

float waterbelowfrac;
if(waterdepth > O_PlantPara.m_MaxHeight) waterbelowfrac = 1.0;
else waterbelowfrac = 2.0 * waterdepth / (waterdepth + O_PlantPara.m_MaxHeight);

float burnfrac = (1.0 - waterbelowfrac);

static float storeleafc = 0.0;
static float storeleafn = 0.0;
static float storeleafp = 0.0;

float leafc = 0.0;
leafc = O_Leaf.m_C * fireintensity * burnfrac * burnfrac;
if(storeleafc < 10e-10)
storeleafc = O_Leaf.m_C * (1.0 - fireintensity * burnfrac * burnfrac);
O_Leaf.m_C -= leafc;

O_Atm.m_AshC[day] += leafc * (1.0 - O_PlantPara.m_LeafCFireEfficiency);
O_Atm.m_COx[day] += leafc * O_PlantPara.m_LeafCFireEfficiency;

float leafn = 0.0;
leafn = O_Leaf.m_N * fireintensity * burnfrac;
if(storeleafn < 10e-10)
storeleafn = (1.0 - fireintensity) * O_Leaf.m_N * burnfrac;
O_Leaf.m_N -= leafn * burnfrac;


O_Atm.m_AshN[day] += leafn * (1.0 - O_PlantPara.m_LeafNFireEfficiency) * burnfrac;
O_Atm.m_NOx[day] += leafn * O_PlantPara.m_LeafNFireEfficiency * burnfrac;

O_Atm.m_AshP[day] += O_Leaf.m_P * fireintensity * burnfrac;
if(storeleafp < 10e-10)
storeleafp = (1.0 - fireintensity) * O_Leaf.m_P * burnfrac;
O_Leaf.m_P -= O_Leaf.m_P * fireintensity * burnfrac;

// Stand dead
float sdc = 0.0;
sdc = O_Litter.m_C * fireintensity * burnfrac;
O_Litter.m_C -= sdc;

O_Atm.m_AshC[day] += sdc * (1.0 - O_PlantPara.m_StandDeadCFireEfficiency);
O_Atm.m_COx[day] += sdc * O_PlantPara.m_StandDeadCFireEfficiency;

float sdn = 0.0;
sdn = O_Litter.m_N * fireintensity * burnfrac;
O_Litter.m_N -= sdn;

O_Atm.m_AshN[day] += sdn * (1.0 - O_PlantPara.m_StandDeadNFireEfficiency);
O_Atm.m_NOx[day] += sdn * O_PlantPara.m_StandDeadNFireEfficiency;


O_Atm.m_AshP[day] += O_Litter.m_P * fireintensity * burnfrac;
O_Litter.m_P -= O_Litter.m_P * fireintensity * burnfrac;

static float fireeffect = 0.0;
if(fireintensity > fireeffect) fireeffect = fireintensity;

float temp = (2.0 * waterdepth - 1.0) * O_PlantPara.m_WDonGerm;
float wdeffect = exp(-1.0 * temp) / (1.0 + exp(-1.0 * temp));

if(postday > 0.01 && postday < 10)
        {
        O_Litter.m_C += O_Leaf.m_C * exp(-1.5);
        O_Leaf.m_C -= O_Leaf.m_C * exp(-1.5);

        O_Litter.m_N += O_Leaf.m_N * exp(-1.5);
        O_Leaf.m_N -= O_Leaf.m_N * exp(-1.5);

        O_Litter.m_P += O_Leaf.m_P * exp(-1.5);
        O_Leaf.m_P -= O_Leaf.m_P * exp(-1.5);

        O_DeadBG.m_C += O_CRoot.m_C * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_DeadBG.m_N += O_CRoot.m_N * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_DeadBG.m_P += O_CRoot.m_P * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_CRoot.m_C -= O_CRoot.m_C * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_CRoot.m_N -= O_CRoot.m_N * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_CRoot.m_P -= O_CRoot.m_P * O_PlantPara.m_Fire_BGBiomass * fireeffect;

        O_DeadBG.m_C += O_FRoot.m_C * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_DeadBG.m_N += O_FRoot.m_N * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_DeadBG.m_P += O_FRoot.m_P * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_FRoot.m_C -= O_FRoot.m_C * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_FRoot.m_N -= O_FRoot.m_N * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_FRoot.m_P -= O_FRoot.m_P * O_PlantPara.m_Fire_BGBiomass * fireeffect;

        O_DeadBG.m_C += O_Rhizome.m_C * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_DeadBG.m_N += O_Rhizome.m_N * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_DeadBG.m_P += O_Rhizome.m_P * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_Rhizome.m_C -= O_Rhizome.m_C * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_Rhizome.m_N -= O_Rhizome.m_N * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_Rhizome.m_P -= O_Rhizome.m_P * O_PlantPara.m_Fire_BGBiomass * fireeffect;

        O_DeadBG.m_C += O_ShootBase.m_C * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_DeadBG.m_N += O_ShootBase.m_N * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_DeadBG.m_P += O_ShootBase.m_P * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_ShootBase.m_C -= O_ShootBase.m_C * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_ShootBase.m_N -= O_ShootBase.m_N * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        O_ShootBase.m_P -= O_ShootBase.m_P * O_PlantPara.m_Fire_BGBiomass * fireeffect;
        postday ++;
        }
else    {

        storeleafc = 0.0;
        storeleafn = 0.0;
        storeleafp = 0.0;

        if((m_LAI < O_PlantPara.m_MaxLAI * leafrecovery) && O_PlantPara.m_Phenology[day] == 1)
        {
        float temp = ((O_PlantPara.m_MaxLAI * leafrecovery - m_LAI) / (O_PlantPara.m_MaxLAI * leafrecovery / O_PlantPara.m_SLA));
        if(temp > 0.1)  temp = 0.1;
                O_Leaf.m_C += O_Rhizome.m_C * temp;
                O_Leaf.m_N += O_Rhizome.m_N * temp;
                O_Leaf.m_P += O_Rhizome.m_P * temp;
                O_Rhizome.m_C -= O_Rhizome.m_C * temp;
                O_Rhizome.m_N -= O_Rhizome.m_N * temp;
                O_Rhizome.m_P -= O_Rhizome.m_P * temp;

//                O_DeadBG.m_C += O_Rhizome.m_C * temp;
//                O_DeadBG.m_N += O_Rhizome.m_N * temp;
//                O_DeadBG.m_P += O_Rhizome.m_P * temp;

//                O_Rhizome.m_C -= O_Rhizome.m_C * temp * 2.0;
//                O_Rhizome.m_N -= O_Rhizome.m_N * temp * 2.0;
//                O_Rhizome.m_P -= O_Rhizome.m_P * temp * 2.0;
        }

        if(m_LAI < (O_PlantPara.m_MinLAI) && O_PlantPara.m_Phenology[day] == 1)
                {
                O_Leaf.m_C += wdeffect * O_ShootBase.m_C * O_PlantPara.m_MinToLeaf;
                O_Leaf.m_N += wdeffect * O_ShootBase.m_N * O_PlantPara.m_MinToLeaf;
                O_Leaf.m_P += wdeffect * O_ShootBase.m_P * O_PlantPara.m_MinToLeaf;
                O_ShootBase.m_C -= wdeffect * O_ShootBase.m_C * O_PlantPara.m_MinToLeaf;
                O_ShootBase.m_N -= wdeffect * O_ShootBase.m_N * O_PlantPara.m_MinToLeaf;
                O_ShootBase.m_P -= wdeffect * O_ShootBase.m_P * O_PlantPara.m_MinToLeaf;

                O_Leaf.m_C += wdeffect * O_Rhizome.m_C * O_PlantPara.m_MinToLeaf;
                O_Leaf.m_N += wdeffect * O_Rhizome.m_N * O_PlantPara.m_MinToLeaf;
                O_Leaf.m_P += wdeffect * O_Rhizome.m_P * O_PlantPara.m_MinToLeaf;
                O_Rhizome.m_C -= wdeffect * O_Rhizome.m_C * O_PlantPara.m_MinToLeaf;
                O_Rhizome.m_N -= wdeffect * O_Rhizome.m_N * O_PlantPara.m_MinToLeaf;
                O_Rhizome.m_P -= wdeffect * O_Rhizome.m_P * O_PlantPara.m_MinToLeaf;
                }
                        
        }

}
