#include "WEMecosystem.h"

WEMecosystem::WEMecosystem()
{
m_SoilThick[0] = 0.05;
m_SoilThick[1] = 0.05;
m_SoilThick[2] = 0.2;
}

WEMecosystem::~WEMecosystem()
{
;
}

void WEMecosystem::m_Initialization()
{
cout<<" Set the parameters for plant, soil, and water!  "<<endl;
cout<<" Initializing cattail's parameters!! "<<endl;
O_PlantPara[0].m_Parameterization(1);
cout<<" Initializing sawgrass's parameters!! "<<endl;
O_PlantPara[1].m_Parameterization(2);

cout<<" Please input the parameter file which contains the parameter information for soil:  "<<endl;
O_SoilPara.m_Parameterization();
O_Geo.m_ReadGeoData();

cout<<" Please input the parameter file which contains the parameter information for water:  "<<endl;
O_WaterPara.m_Parameterization();

cout<<" Initializing periphyton's parameters!! "<<endl;
string perifile;
cout<<" Please input the file name which contain the parameter file for periphyton! "<<endl;
cin>>perifile;
ifstream inperi;
inperi.open(perifile.c_str());
string Pmax, Kr, Arrcons, Tref, Fresp, Km, Ktp, Cmax, Ik, Fprel, CN, CP, flocdec, floctosom, somtofloc;
if(!inperi)
        {
        cout<<" The parameter file for periphyton is not exist!! "<<endl;
        exit(1);
        }
else
        {
        inperi>>Pmax>>m_Pmax
              >>Kr>>m_Kr
              >>Arrcons>>m_Arrcons
              >>Tref>>m_Tref
              >>Fresp>>m_Fresp
              >>Km>>m_Km
              >>Ktp>>m_Ktp
              >>Cmax>>m_Cmax
              >>Ik>>m_Ik
              >>Fprel>>m_Fprel
              >>CN>>m_CNratioperi
              >>CP>>m_CPratioperi
              >>flocdec>>m_FlocDec
              >>floctosom>>m_FlocToSOM
              >>somtofloc>>m_SOMToFloc;
        }

cout<<"Input data reading!!......"<<endl;
cout<<"Climiate data reading  "<<endl;
O_Atm.m_ReadCLM();
cout<<"Climate data reading finished! "<<endl;

cout<<"Deposition data reading  "<<endl;
O_Atm.m_ReadNPdep();
cout<<"Deposition data reading finished! "<<endl;

cout<<"Hydrology data reading  "<<endl;
O_Flow.m_ReadHydrology();
cout<<"Hydrology data reading finished! "<<endl;
cout<<"Input data read done!!......"<<endl;

cout<<"Initializing!  "<<endl;
string plantfile1, plantfile2, periphyton;
cout<<"Please input the file name of the data file which contains the initial data for cattail: "<<endl;
cin>>plantfile1;
O_Plant[0].m_Initilizing(plantfile1);
cout<<"Please input the file name of the data file which contains the initial data for sawgrass: "<<endl;
cin>>plantfile2;
O_Plant[1].m_Initilizing(plantfile2);
cout<<"Please input the file name of the data file which contains the initial data for periphyton and floc: "<<endl;
cin>>periphyton;
ifstream ini;
ini.open(periphyton.c_str());
if(!ini)
        {
        cout<<"The data file contain the periphyton and floc is not exist!! "<<endl;
        exit(1);
        }
else
        {
        ini>>O_Periphyton.m_C>>O_Periphyton.m_N>>O_Periphyton.m_P>>
                O_Floc.m_C>>O_Floc.m_N>>O_Floc.m_P;
        }
ini.close();
cout<<"Initialization is DONE!  "<<endl;

cout<<" Initializing soil variables!! "<<endl;
cout<<" Please input the initil data for top layer soil (0-5cm)"<<endl;
O_Soil[0].m_Initialization();
cout<<" Please input the initil data for second layer soil (5-10cm)"<<endl;
O_Soil[1].m_Initialization();
cout<<" Please input the initil data for third layer soil (10-30cm)"<<endl;
O_Soil[2].m_Initialization();
cout<<"Soil intilization done!! "<<endl;

cout<<" Initializing water variables!! "<<endl;
cout<<" Please input the initil data for surface water"<<endl;
O_Water[0].m_Initialization();
cout<<" Please input the initil data for the pore water"<<endl;
O_Water[1].m_Initialization();
O_Water[2].m_Initialization();
O_Water[3].m_Initialization();
cout<<"Water intilization done!! "<<endl;

cout<<"Model initilization done!! "<<endl;
}


void WEMecosystem::m_Simulation(int Spin_number)
{

for(int spin = 0;  spin < Spin_number; spin++)
{
        cout<<"Spin up: "<<(spin+1)<<endl;
        for(int i = 0; i < 365; i++)
                {
                m_DaySimulation(i);
        cout<<setw(20);
        cout<<
                " cattailAGB "<<setw(20)<<O_Plant[0].O_Leaf.m_C<<" cattailBGB "<<(O_Plant[0].O_Rhizome.m_C + O_Plant[0].O_ShootBase.m_C + O_Plant[0].O_FRoot.m_C + O_Plant[0].O_CRoot.m_C)<<" cattailAGDM "<<O_Plant[0].O_Litter.m_C<<" cattailBGDM "<<O_Plant[0].O_DeadBG.m_C<<
                " cattail_leaf "<<setw(20)<<O_Plant[0].O_Leaf.m_C<<" "<<setw(20)<<O_Plant[0].O_Leaf.m_N<<" "<<setw(20)<<O_Plant[0].O_Leaf.m_P<<
                " cattail_shootbase "<<setw(20)<<O_Plant[0].O_ShootBase.m_C<<" "<<setw(20)<<O_Plant[0].O_ShootBase.m_N<<" "<<setw(20)<<O_Plant[0].O_ShootBase.m_P<<
                " cattail_rhizome "<<setw(20)<<O_Plant[0].O_Rhizome.m_C<<" "<<setw(20)<<O_Plant[0].O_Rhizome.m_N<<" "<<setw(20)<<O_Plant[0].O_Rhizome.m_P<<
                " cattail_croot "<<setw(20)<<O_Plant[0].O_CRoot.m_C<<" "<<setw(20)<<O_Plant[0].O_CRoot.m_N<<" "<<setw(20)<<O_Plant[0].O_CRoot.m_P<<
                " cattail_froot "<<setw(20)<<O_Plant[0].O_FRoot.m_C<<" "<<setw(20)<<O_Plant[0].O_FRoot.m_N<<" "<<setw(20)<<O_Plant[0].O_FRoot.m_P<<
                " cattail_litter "<<setw(20)<<O_Plant[0].O_Litter.m_C<<" "<<setw(20)<<O_Plant[0].O_Litter.m_N<<" "<<setw(20)<<O_Plant[0].O_Litter.m_P<<
                " cattail_DeadBG "<<setw(20)<<O_Plant[0].O_DeadBG.m_C<<" "<<setw(20)<<O_Plant[0].O_DeadBG.m_N<<" "<<setw(20)<<O_Plant[0].O_DeadBG.m_P<<
                " cattail_fluxes"<<setw(20)<<O_Plant[0].m_GPPvalue<<" "<<setw(20)<<O_Plant[0].m_NPPvalue<<" "<<setw(20)<<O_Plant[0].m_ARvalue<<
                " sawgrassAGB "<<setw(20)<<O_Plant[1].O_Leaf.m_C<<" sawgrassBGB "<<(O_Plant[1].O_Rhizome.m_C + O_Plant[1].O_ShootBase.m_C + O_Plant[1].O_FRoot.m_C + O_Plant[1].O_CRoot.m_C)<<" sawgrassAGDM "<<O_Plant[1].O_Litter.m_C<<" sawgrassBGDM "<<O_Plant[1].O_DeadBG.m_C<<
                " sawgrass_leaf "<<setw(20)<<O_Plant[1].O_Leaf.m_C<<" "<<setw(20)<<O_Plant[1].O_Leaf.m_N<<" "<<setw(20)<<O_Plant[1].O_Leaf.m_P<<
                " sawgrass_shootbase "<<setw(20)<<O_Plant[1].O_ShootBase.m_C<<" "<<setw(20)<<O_Plant[1].O_ShootBase.m_N<<" "<<setw(20)<<O_Plant[1].O_ShootBase.m_P<<
                " sawgrass_rhizome "<<setw(20)<<O_Plant[1].O_Rhizome.m_C<<" "<<setw(20)<<O_Plant[1].O_Rhizome.m_N<<" "<<setw(20)<<O_Plant[1].O_Rhizome.m_P<<
                " sawgrass_croot "<<setw(20)<<O_Plant[1].O_CRoot.m_C<<" "<<setw(20)<<O_Plant[1].O_CRoot.m_N<<" "<<setw(20)<<O_Plant[1].O_CRoot.m_P<<
                " sawgrass_froot "<<setw(20)<<O_Plant[1].O_FRoot.m_C<<" "<<setw(20)<<O_Plant[1].O_FRoot.m_N<<" "<<setw(20)<<O_Plant[1].O_FRoot.m_P<<
                " sawgrass_litter "<<setw(20)<<O_Plant[1].O_Litter.m_C<<" "<<setw(20)<<O_Plant[1].O_Litter.m_N<<" "<<setw(20)<<O_Plant[1].O_Litter.m_P<<
                " sawgrass_deadbg "<<setw(20)<<O_Plant[1].O_DeadBG.m_C<<" "<<setw(20)<<O_Plant[1].O_DeadBG.m_N<<" "<<setw(20)<<O_Plant[1].O_DeadBG.m_P<<
                " sawgrass_fluxes"<<setw(20)<<O_Plant[1].m_GPPvalue<<" "<<setw(20)<<O_Plant[1].m_NPPvalue<<" "<<setw(20)<<O_Plant[1].m_ARvalue<<
                " periphyton "<<setw(20)<<O_Periphyton.m_C<<" "<<setw(20)<<O_Periphyton.m_N<<" "<<setw(20)<<O_Periphyton.m_P<<
                " floc "<<setw(20)<<O_Floc.m_C<<" "<<setw(20)<<O_Floc.m_N<<" "<<setw(20)<<O_Floc.m_P<<
                " 1soil_SIN "<<setw(20)<<O_Soil[0].m_SINNH4<<" "<<setw(20)<<O_Soil[0].m_SINNO3<<" "<<setw(20)<<O_Soil[0].m_SINPO4<<
                " 1soil_abs "<<setw(20)<<O_Soil[0].m_AbsNH4<<" "<<setw(20)<<O_Soil[0].m_AbsNO3<<" "<<setw(20)<<O_Soil[0].m_AbsPO4<<
                " 1soil_SON "<<setw(20)<<O_Soil[0].O_SON.m_C<<" "<<setw(20)<<O_Soil[0].O_SON.m_N<<" "<<setw(20)<<O_Soil[0].O_SON.m_P<<
                " 1soil_LABSOM "<<setw(20)<<O_Soil[0].O_LabSOM.m_C<<" "<<setw(20)<<O_Soil[0].O_LabSOM.m_N<<" "<<setw(20)<<O_Soil[0].O_LabSOM.m_P<<
                " 1soil_MidSOM "<<setw(20)<<O_Soil[0].O_MidSOM.m_C<<" "<<setw(20)<<O_Soil[0].O_MidSOM.m_N<<" "<<setw(20)<<O_Soil[0].O_MidSOM.m_P<<
                " 1soil_RESSOM "<<setw(20)<<O_Soil[0].O_ResSOM.m_C<<" "<<setw(20)<<O_Soil[0].O_ResSOM.m_N<<" "<<setw(20)<<O_Soil[0].O_ResSOM.m_P<<
                " 2soil_SIN "<<setw(20)<<O_Soil[1].m_SINNH4<<" "<<setw(20)<<O_Soil[1].m_SINNO3<<" "<<setw(20)<<O_Soil[1].m_SINPO4<<
                " 2soil_abs "<<setw(20)<<O_Soil[1].m_AbsNH4<<" "<<setw(20)<<O_Soil[1].m_AbsNO3<<" "<<setw(20)<<O_Soil[1].m_AbsPO4<<
                " 2soil_SON "<<setw(20)<<O_Soil[1].O_SON.m_C<<" "<<setw(20)<<O_Soil[1].O_SON.m_N<<" "<<setw(20)<<O_Soil[1].O_SON.m_P<<
                " 2soil_LABSOM "<<setw(20)<<O_Soil[1].O_LabSOM.m_C<<" "<<setw(20)<<O_Soil[1].O_LabSOM.m_N<<" "<<setw(20)<<O_Soil[1].O_LabSOM.m_P<<
                " 2soil_MIDSOM "<<setw(20)<<O_Soil[1].O_MidSOM.m_C<<" "<<setw(20)<<O_Soil[1].O_MidSOM.m_N<<" "<<setw(20)<<O_Soil[1].O_MidSOM.m_P<<
                " 2soil_RESSOM "<<setw(20)<<O_Soil[1].O_ResSOM.m_C<<" "<<setw(20)<<O_Soil[1].O_ResSOM.m_N<<" "<<setw(20)<<O_Soil[1].O_ResSOM.m_P<<
                " 3soil_SIN "<<setw(20)<<O_Soil[2].m_SINNH4<<" "<<setw(20)<<O_Soil[2].m_SINNO3<<" "<<setw(20)<<O_Soil[2].m_SINPO4<<
                " 3soil_abs "<<setw(20)<<O_Soil[2].m_AbsNH4<<" "<<setw(20)<<O_Soil[2].m_AbsNO3<<" "<<setw(20)<<O_Soil[2].m_AbsPO4<<
                " 3soil_SON "<<setw(20)<<O_Soil[2].O_SON.m_C<<" "<<setw(20)<<O_Soil[2].O_SON.m_N<<" "<<setw(20)<<O_Soil[2].O_SON.m_P<<
                " 3soil_LABSOM "<<setw(20)<<O_Soil[2].O_LabSOM.m_C<<" "<<setw(20)<<O_Soil[2].O_LabSOM.m_N<<" "<<setw(20)<<O_Soil[2].O_LabSOM.m_P<<
                " 3soil_MIDSOM "<<setw(20)<<O_Soil[2].O_MidSOM.m_C<<" "<<setw(20)<<O_Soil[2].O_MidSOM.m_N<<" "<<setw(20)<<O_Soil[2].O_MidSOM.m_P<<
                " 3soil_RESSOM "<<setw(20)<<O_Soil[2].O_ResSOM.m_C<<" "<<setw(20)<<O_Soil[2].O_ResSOM.m_N<<" "<<setw(20)<<O_Soil[2].O_ResSOM.m_P<<
                " 1water_DIN "<<setw(20)<<O_Water[0].m_DNH4<<" "<<setw(20)<<O_Water[0].m_DNO3<<" "<<setw(20)<<O_Water[0].m_DPO4<<
                " 1water_DON "<<setw(20)<<O_Water[0].O_DON.m_C<<" "<<setw(20)<<O_Water[0].O_DON.m_N<<" "<<setw(20)<<O_Water[0].O_DON.m_P<<
                " 1water_PON "<<setw(20)<<O_Water[0].O_PON.m_C<<" "<<setw(20)<<O_Water[0].O_PON.m_N<<" "<<setw(20)<<O_Water[0].O_PON.m_P<<
                " 2water_DIN "<<setw(20)<<O_Water[1].m_DNH4<<" "<<setw(20)<<O_Water[1].m_DNO3<<" "<<setw(20)<<O_Water[1].m_DPO4<<
                " 2water_DON "<<setw(20)<<O_Water[1].O_DON.m_C<<" "<<setw(20)<<O_Water[1].O_DON.m_N<<" "<<setw(20)<<O_Water[1].O_DON.m_P<<
                " 2water_PON "<<setw(20)<<O_Water[1].O_PON.m_C<<" "<<setw(20)<<O_Water[1].O_PON.m_N<<" "<<setw(20)<<O_Water[1].O_PON.m_P<<
                " 3water_DIN "<<setw(20)<<O_Water[2].m_DNH4<<" "<<setw(20)<<O_Water[2].m_DNO3<<" "<<setw(20)<<O_Water[2].m_DPO4<<
                " 3water_DON "<<setw(20)<<O_Water[2].O_DON.m_C<<" "<<setw(20)<<O_Water[2].O_DON.m_N<<" "<<setw(20)<<O_Water[2].O_DON.m_P<<
                " 3water_PON "<<setw(20)<<O_Water[2].O_PON.m_C<<" "<<setw(20)<<O_Water[2].O_PON.m_N<<" "<<setw(20)<<O_Water[2].O_PON.m_P<<
                " 4water_DIN "<<setw(20)<<O_Water[3].m_DNH4<<" "<<setw(20)<<O_Water[3].m_DNO3<<" "<<setw(20)<<O_Water[3].m_DPO4<<
                " 4water_DON "<<setw(20)<<O_Water[3].O_DON.m_C<<" "<<setw(20)<<O_Water[3].O_DON.m_N<<" "<<setw(20)<<O_Water[3].O_DON.m_P<<
                " 4water_PON "<<setw(20)<<O_Water[3].O_PON.m_C<<" "<<setw(20)<<O_Water[3].O_PON.m_N<<" "<<setw(20)<<O_Water[3].O_PON.m_P<<
                " water_depth "<<setw(20)<<O_Water[0].m_WaterDepth<<" "<<setw(20)<<O_Water[1].m_WaterDepth<<" "<<setw(20)<<O_Water[2].m_WaterDepth<<" "<<setw(20)<<O_Water[3].m_WaterDepth<<
                " water_temp "<<setw(20)<<O_Water[0].m_WaterT<<" "<<setw(20)<<O_Water[1].m_WaterT<<" "<<setw(20)<<O_Water[2].m_WaterT<<" "<<setw(20)<<O_Water[3].m_WaterT<<
                endl;
                }
}

cout<<"Simulation: "<<endl;
for(int j = 0; j < g_ModelRunDay; j++)
        {
        m_DaySimulation(j);
        m_Output(j);
        cout<<
                " cattailAGB "<<setw(20)<<O_Plant[0].O_Leaf.m_C<<" cattailBGB "<<(O_Plant[0].O_Rhizome.m_C + O_Plant[0].O_ShootBase.m_C + O_Plant[0].O_FRoot.m_C + O_Plant[0].O_CRoot.m_C)<<" cattailAGDM "<<O_Plant[0].O_Litter.m_C<<" cattailBGDM "<<O_Plant[0].O_DeadBG.m_C<<
                " cattail_leaf "<<setw(20)<<O_Plant[0].O_Leaf.m_C<<" "<<setw(20)<<O_Plant[0].O_Leaf.m_N<<" "<<setw(20)<<O_Plant[0].O_Leaf.m_P<<
                " cattail_shootbase "<<setw(20)<<O_Plant[0].O_ShootBase.m_C<<" "<<setw(20)<<O_Plant[0].O_ShootBase.m_N<<" "<<setw(20)<<O_Plant[0].O_ShootBase.m_P<<
                " cattail_rhizome "<<setw(20)<<O_Plant[0].O_Rhizome.m_C<<" "<<setw(20)<<O_Plant[0].O_Rhizome.m_N<<" "<<setw(20)<<O_Plant[0].O_Rhizome.m_P<<
                " cattail_croot "<<setw(20)<<O_Plant[0].O_CRoot.m_C<<" "<<setw(20)<<O_Plant[0].O_CRoot.m_N<<" "<<setw(20)<<O_Plant[0].O_CRoot.m_P<<
                " cattail_froot "<<setw(20)<<O_Plant[0].O_FRoot.m_C<<" "<<setw(20)<<O_Plant[0].O_FRoot.m_N<<" "<<setw(20)<<O_Plant[0].O_FRoot.m_P<<
                " cattail_litter "<<setw(20)<<O_Plant[0].O_Litter.m_C<<" "<<setw(20)<<O_Plant[0].O_Litter.m_N<<" "<<setw(20)<<O_Plant[0].O_Litter.m_P<<
                " cattail_DeadBG "<<setw(20)<<O_Plant[0].O_DeadBG.m_C<<" "<<setw(20)<<O_Plant[0].O_DeadBG.m_N<<" "<<setw(20)<<O_Plant[0].O_DeadBG.m_P<<
                " cattail_fluxes"<<setw(20)<<O_Plant[0].m_GPPvalue<<" "<<setw(20)<<O_Plant[0].m_NPPvalue<<" "<<setw(20)<<O_Plant[0].m_ARvalue<<
                " sawgrassAGB "<<setw(20)<<O_Plant[1].O_Leaf.m_C<<" sawgrassBGB "<<(O_Plant[1].O_Rhizome.m_C + O_Plant[1].O_ShootBase.m_C + O_Plant[1].O_FRoot.m_C + O_Plant[1].O_CRoot.m_C)<<" sawgrassAGDM "<<O_Plant[1].O_Litter.m_C<<" sawgrassBGDM "<<O_Plant[1].O_DeadBG.m_C<<
                " sawgrass_leaf "<<setw(20)<<O_Plant[1].O_Leaf.m_C<<" "<<setw(20)<<O_Plant[1].O_Leaf.m_N<<" "<<setw(20)<<O_Plant[1].O_Leaf.m_P<<
                " sawgrass_shootbase "<<setw(20)<<O_Plant[1].O_ShootBase.m_C<<" "<<setw(20)<<O_Plant[1].O_ShootBase.m_N<<" "<<setw(20)<<O_Plant[1].O_ShootBase.m_P<<
                " sawgrass_rhizome "<<setw(20)<<O_Plant[1].O_Rhizome.m_C<<" "<<setw(20)<<O_Plant[1].O_Rhizome.m_N<<" "<<setw(20)<<O_Plant[1].O_Rhizome.m_P<<
                " sawgrass_croot "<<setw(20)<<O_Plant[1].O_CRoot.m_C<<" "<<setw(20)<<O_Plant[1].O_CRoot.m_N<<" "<<setw(20)<<O_Plant[1].O_CRoot.m_P<<
                " sawgrass_froot "<<setw(20)<<O_Plant[1].O_FRoot.m_C<<" "<<setw(20)<<O_Plant[1].O_FRoot.m_N<<" "<<setw(20)<<O_Plant[1].O_FRoot.m_P<<
                " sawgrass_litter "<<setw(20)<<O_Plant[1].O_Litter.m_C<<" "<<setw(20)<<O_Plant[1].O_Litter.m_N<<" "<<setw(20)<<O_Plant[1].O_Litter.m_P<<
                " sawgrass_deadbg "<<setw(20)<<O_Plant[1].O_DeadBG.m_C<<" "<<setw(20)<<O_Plant[1].O_DeadBG.m_N<<" "<<setw(20)<<O_Plant[1].O_DeadBG.m_P<<
                " sawgrass_fluxes"<<setw(20)<<O_Plant[1].m_GPPvalue<<" "<<setw(20)<<O_Plant[1].m_NPPvalue<<" "<<setw(20)<<O_Plant[1].m_ARvalue<<
                " periphyton "<<setw(20)<<O_Periphyton.m_C<<" "<<setw(20)<<O_Periphyton.m_N<<" "<<setw(20)<<O_Periphyton.m_P<<
                " floc "<<setw(20)<<O_Floc.m_C<<" "<<setw(20)<<O_Floc.m_N<<" "<<setw(20)<<O_Floc.m_P<<
                " 1soil_SIN "<<setw(20)<<O_Soil[0].m_SINNH4<<" "<<setw(20)<<O_Soil[0].m_SINNO3<<" "<<setw(20)<<O_Soil[0].m_SINPO4<<
                " 1soil_abs "<<setw(20)<<O_Soil[0].m_AbsNH4<<" "<<setw(20)<<O_Soil[0].m_AbsNO3<<" "<<setw(20)<<O_Soil[0].m_AbsPO4<<
                " 1soil_SON "<<setw(20)<<O_Soil[0].O_SON.m_C<<" "<<setw(20)<<O_Soil[0].O_SON.m_N<<" "<<setw(20)<<O_Soil[0].O_SON.m_P<<
                " 1soil_LABSOM "<<setw(20)<<O_Soil[0].O_LabSOM.m_C<<" "<<setw(20)<<O_Soil[0].O_LabSOM.m_N<<" "<<setw(20)<<O_Soil[0].O_LabSOM.m_P<<
                " 1soil_MidSOM "<<setw(20)<<O_Soil[0].O_MidSOM.m_C<<" "<<setw(20)<<O_Soil[0].O_MidSOM.m_N<<" "<<setw(20)<<O_Soil[0].O_MidSOM.m_P<<
                " 1soil_RESSOM "<<setw(20)<<O_Soil[0].O_ResSOM.m_C<<" "<<setw(20)<<O_Soil[0].O_ResSOM.m_N<<" "<<setw(20)<<O_Soil[0].O_ResSOM.m_P<<
                " 2soil_SIN "<<setw(20)<<O_Soil[1].m_SINNH4<<" "<<setw(20)<<O_Soil[1].m_SINNO3<<" "<<setw(20)<<O_Soil[1].m_SINPO4<<
                " 2soil_abs "<<setw(20)<<O_Soil[1].m_AbsNH4<<" "<<setw(20)<<O_Soil[1].m_AbsNO3<<" "<<setw(20)<<O_Soil[1].m_AbsPO4<<
                " 2soil_SON "<<setw(20)<<O_Soil[1].O_SON.m_C<<" "<<setw(20)<<O_Soil[1].O_SON.m_N<<" "<<setw(20)<<O_Soil[1].O_SON.m_P<<
                " 2soil_LABSOM "<<setw(20)<<O_Soil[1].O_LabSOM.m_C<<" "<<setw(20)<<O_Soil[1].O_LabSOM.m_N<<" "<<setw(20)<<O_Soil[1].O_LabSOM.m_P<<
                " 2soil_MIDSOM "<<setw(20)<<O_Soil[1].O_MidSOM.m_C<<" "<<setw(20)<<O_Soil[1].O_MidSOM.m_N<<" "<<setw(20)<<O_Soil[1].O_MidSOM.m_P<<
                " 2soil_RESSOM "<<setw(20)<<O_Soil[1].O_ResSOM.m_C<<" "<<setw(20)<<O_Soil[1].O_ResSOM.m_N<<" "<<setw(20)<<O_Soil[1].O_ResSOM.m_P<<
                " 3soil_SIN "<<setw(20)<<O_Soil[2].m_SINNH4<<" "<<setw(20)<<O_Soil[2].m_SINNO3<<" "<<setw(20)<<O_Soil[2].m_SINPO4<<
                " 3soil_abs "<<setw(20)<<O_Soil[2].m_AbsNH4<<" "<<setw(20)<<O_Soil[2].m_AbsNO3<<" "<<setw(20)<<O_Soil[2].m_AbsPO4<<
                " 3soil_SON "<<setw(20)<<O_Soil[2].O_SON.m_C<<" "<<setw(20)<<O_Soil[2].O_SON.m_N<<" "<<setw(20)<<O_Soil[2].O_SON.m_P<<
                " 3soil_LABSOM "<<setw(20)<<O_Soil[2].O_LabSOM.m_C<<" "<<setw(20)<<O_Soil[2].O_LabSOM.m_N<<" "<<setw(20)<<O_Soil[2].O_LabSOM.m_P<<
                " 3soil_MIDSOM "<<setw(20)<<O_Soil[2].O_MidSOM.m_C<<" "<<setw(20)<<O_Soil[2].O_MidSOM.m_N<<" "<<setw(20)<<O_Soil[2].O_MidSOM.m_P<<
                " 3soil_RESSOM "<<setw(20)<<O_Soil[2].O_ResSOM.m_C<<" "<<setw(20)<<O_Soil[2].O_ResSOM.m_N<<" "<<setw(20)<<O_Soil[2].O_ResSOM.m_P<<
                " 1water_DIN "<<setw(20)<<O_Water[0].m_DNH4<<" "<<setw(20)<<O_Water[0].m_DNO3<<" "<<setw(20)<<O_Water[0].m_DPO4<<
                " 1water_DON "<<setw(20)<<O_Water[0].O_DON.m_C<<" "<<setw(20)<<O_Water[0].O_DON.m_N<<" "<<setw(20)<<O_Water[0].O_DON.m_P<<
                " 1water_PON "<<setw(20)<<O_Water[0].O_PON.m_C<<" "<<setw(20)<<O_Water[0].O_PON.m_N<<" "<<setw(20)<<O_Water[0].O_PON.m_P<<
                " 2water_DIN "<<setw(20)<<O_Water[1].m_DNH4<<" "<<setw(20)<<O_Water[1].m_DNO3<<" "<<setw(20)<<O_Water[1].m_DPO4<<
                " 2water_DON "<<setw(20)<<O_Water[1].O_DON.m_C<<" "<<setw(20)<<O_Water[1].O_DON.m_N<<" "<<setw(20)<<O_Water[1].O_DON.m_P<<
                " 2water_PON "<<setw(20)<<O_Water[1].O_PON.m_C<<" "<<setw(20)<<O_Water[1].O_PON.m_N<<" "<<setw(20)<<O_Water[1].O_PON.m_P<<
                " 3water_DIN "<<setw(20)<<O_Water[2].m_DNH4<<" "<<setw(20)<<O_Water[2].m_DNO3<<" "<<setw(20)<<O_Water[2].m_DPO4<<
                " 3water_DON "<<setw(20)<<O_Water[2].O_DON.m_C<<" "<<setw(20)<<O_Water[2].O_DON.m_N<<" "<<setw(20)<<O_Water[2].O_DON.m_P<<
                " 3water_PON "<<setw(20)<<O_Water[2].O_PON.m_C<<" "<<setw(20)<<O_Water[2].O_PON.m_N<<" "<<setw(20)<<O_Water[2].O_PON.m_P<<
                " 4water_DIN "<<setw(20)<<O_Water[3].m_DNH4<<" "<<setw(20)<<O_Water[3].m_DNO3<<" "<<setw(20)<<O_Water[3].m_DPO4<<
                " 4water_DON "<<setw(20)<<O_Water[3].O_DON.m_C<<" "<<setw(20)<<O_Water[3].O_DON.m_N<<" "<<setw(20)<<O_Water[3].O_DON.m_P<<
                " 4water_PON "<<setw(20)<<O_Water[3].O_PON.m_C<<" "<<setw(20)<<O_Water[3].O_PON.m_N<<" "<<setw(20)<<O_Water[3].O_PON.m_P<<
                " water_depth "<<setw(20)<<O_Water[0].m_WaterDepth<<" "<<setw(20)<<O_Water[1].m_WaterDepth<<" "<<setw(20)<<O_Water[2].m_WaterDepth<<" "<<setw(20)<<O_Water[3].m_WaterDepth<<
                " water_temp "<<setw(20)<<O_Water[0].m_WaterT<<" "<<setw(20)<<O_Water[1].m_WaterT<<" "<<setw(20)<<O_Water[2].m_WaterT<<" "<<setw(20)<<O_Water[3].m_WaterT<<
                " ash "<<setw(20)<<O_Atm.m_AshC[j]<<" "<<setw(20)<<O_Atm.m_AshN[j]<<" "<<setw(20)<<O_Atm.m_AshP[j]<<
                " fire_gas "<<setw(20)<<O_Atm.m_COx[j]<<" "<<setw(20)<<O_Atm.m_NOx[j];

if(g_WaterOrOutflow == 1)
                {
                cout<<
                " outflow "<<setw(20)<<O_Flow.m_OutWater[j]<<" "<<setw(20)<<O_Flow.m_OutNH4[j]<<" "<<setw(20)<<O_Flow.m_OutNO3[j]<<" "<<setw(20)<<O_Flow.m_OutPO4[j]<<
                " outflow "<<setw(20)<<O_Flow.m_OutDOC[j]<<" "<<setw(20)<<O_Flow.m_OutDON[j]<<" "<<setw(20)<<O_Flow.m_OutDOP[j]<<
                " outflow "<<setw(20)<<O_Flow.m_OutPOC[j]<<" "<<setw(20)<<O_Flow.m_OutPON[j]<<" "<<setw(20)<<O_Flow.m_OutPOP[j]<<
                endl;
                }
else
                {
                cout<<" outflow "<<setw(20)<<O_Flow.m_WaterTable[j]<<
                endl;
                }
        }

}

void WEMecosystem::m_Release()
{

}

void WEMecosystem::m_Inflow(int day)
{
O_Water[0].m_WaterVolume += O_Flow.m_InWater[day];
O_Water[0].m_DNH4 += O_Flow.m_InNH4[day];
O_Water[0].m_DNO3 += O_Flow.m_InNO3[day];
O_Water[0].m_DPO4 += O_Flow.m_InPO4[day];
O_Water[0].O_DON.m_C += O_Flow.m_InDOC[day];
O_Water[0].O_DON.m_N += O_Flow.m_InDON[day];
O_Water[0].O_DON.m_P += O_Flow.m_InDOP[day];
O_Water[0].O_PON.m_C += O_Flow.m_InPOC[day];
O_Water[0].O_PON.m_N += O_Flow.m_InPON[day];
O_Water[0].O_PON.m_P += O_Flow.m_InPOP[day];
}

void WEMecosystem::m_DaySimulation(int day)
{
static int postdayfire;
static float leafrecovery;

if(O_Fire.m_Fire[day] > 0.1)
        {
        postdayfire = 1;
        leafrecovery = 0.6;
        }

if(postdayfire > 0.1 && postdayfire < 730)
        {
        leafrecovery = (0.6 + postdayfire / (730 * 2.5)) * (0.6 + postdayfire / (730 * 2.5));
        postdayfire += 1;
        }
else
        {
        postdayfire = 0.0;
        leafrecovery = 1.0;
        }

m_Inflow(day);
/*
static int postday = 0;
static float storepondec;
static float PONDEC;
static float precipitation;

if(O_Fire.m_Fire[day] > 0.1)
        {
        postday = 1;
        storepondec = O_WaterPara.m_PToSDecom;
        O_WaterPara.m_PToSDecom = O_WaterPara.m_PToSDecom * 0.4;

        precipitation = O_WaterPara.m_PrecRate;
        O_WaterPara.m_PrecRate = O_WaterPara.m_PrecRate * 0.4;
        }

if(postday > 0.1 && postday < 61)
        {
        O_WaterPara.m_PToSDecom += storepondec / 100.0;
        O_WaterPara.m_PrecRate += precipitation / 100.;
        PONDEC = 0.0001;// + postday / 100. * postday / 100.;
        postday++;
        }
else
        {
        PONDEC = 1.0;
        postday = 0.0;
        }
*/
cout<<"day: "<<setw(12)<<day + 1<<" : ";
//cout<<"OK3 "<<O_Soil[0].m_SINNH4<<endl;
float avn = 0.0;
float avp = 0.0;

for(int layer = 1; layer < 4; layer++)
        {
        avn += O_Water[layer].m_DNH4 + O_Water[layer].m_DNO3 + O_Soil[layer-1].m_SINNH4 + O_Soil[layer-1].m_SINNO3;
//cout<<"1: "<<layer<<" layer "<<O_Water[layer].m_DPO4<<endl;
        avp += O_Water[layer].m_DPO4 + O_Soil[layer-1].m_SINPO4;
        }
//cout<<"avp here "<<avp<<endl;

float storavn = avn;
float storavp = avp;

float totalbiomass1 = O_Plant[0].O_Leaf.m_C + O_Plant[0].O_Rhizome.m_C + O_Plant[0].O_ShootBase.m_C + O_Plant[0].O_FRoot.m_C + O_Plant[0].O_CRoot.m_C;
float totalbiomass2 = O_Plant[1].O_Leaf.m_C + O_Plant[1].O_Rhizome.m_C + O_Plant[1].O_ShootBase.m_C + O_Plant[1].O_FRoot.m_C + O_Plant[1].O_CRoot.m_C;

if((O_Plant[0].O_Leaf.m_C * O_PlantPara[0].m_SLA + O_Plant[1].O_Leaf.m_C * O_PlantPara[1].m_SLA) > 0.05)
{
plant1frac = O_Plant[0].O_Leaf.m_C * O_PlantPara[0].m_SLA / (O_Plant[0].O_Leaf.m_C * O_PlantPara[0].m_SLA + O_Plant[1].O_Leaf.m_C * O_PlantPara[1].m_SLA);
plant2frac = O_Plant[1].O_Leaf.m_C * O_PlantPara[1].m_SLA / (O_Plant[0].O_Leaf.m_C * O_PlantPara[0].m_SLA + O_Plant[1].O_Leaf.m_C * O_PlantPara[1].m_SLA);
}
else
{
plant1frac = 0.0;
plant2frac = 0.0;
}

O_Plant[0].m_CalDI(O_PlantPara[0]);
if(totalbiomass1 <= 0) totalbiomass1 = 10e-5;
O_Plant[0].m_Height = pow(double(totalbiomass1 / O_PlantPara[0].m_MaxBiomassC), 0.33) * O_PlantPara[0].m_MaxHeight;
if(plant1frac > 0.05)
{
        O_Plant[0].m_LAI = O_Plant[0].O_Leaf.m_C * O_PlantPara[0].m_SLA / plant1frac;
}
else    O_Plant[0].m_LAI = 0.0;

O_Plant[1].m_CalDI(O_PlantPara[1]);
if(totalbiomass2 <= 0) totalbiomass2 = 10e-5;
O_Plant[1].m_Height = pow(double(totalbiomass2 / O_PlantPara[1].m_MaxBiomassC), 0.33) * O_PlantPara[1].m_MaxHeight;
if(plant2frac > 0.05)
{
        O_Plant[1].m_LAI = O_Plant[1].O_Leaf.m_C * O_PlantPara[1].m_SLA / plant2frac;
}
else    O_Plant[1].m_LAI = 0.0;

int JulDay = (day + 1) % 365;
float planth1 = O_Plant[0].m_Height;
float planth2 = O_Plant[1].m_Height;

float airt = O_Atm.m_AirT[day];
float ppt = O_Atm.m_PPT[day];
float par = O_Atm.m_PAR[day];
float totalsr = O_Atm.m_SR[day];

//cout<<airt<<" "<<ppt<<" "<<sr<<endl;
//float co2 = 380.0;   //ppm
float pa = 101325;  //pa
//float o2 = 0.21 * pa;  //partial pressure

float maxh = g_Max(planth1, planth2);
float mlai = g_Max(O_Plant[0].m_LAI, O_Plant[1].m_LAI);

//sr: net radiation (W/m2)
if(par > 0.0)    par = par;
if(par <= 0.0)    par = 0.0;

float ec1 = O_PlantPara[0].m_Extinct_Coef;
float ec2 = O_PlantPara[1].m_Extinct_Coef;

float decfeedback1, decfeedback2;

float soilt = (O_Soil[0].m_SoilT * m_SoilThick[0] + O_Soil[1].m_SoilT * m_SoilThick[1] + O_Soil[2].m_SoilT * m_SoilThick[2]) / (m_SoilThick[0] + m_SoilThick[1] + m_SoilThick[2]);

float storepar = par;

if(planth1 >= (planth2))
        {
//cout<<"1 storavn "<<storavn<<" storanp "<<storavp<<endl;
//cout<<"1 avn "<<avn<<" avp "<<avp<<endl;

        par = storepar * (1.0 - exp(-1.0 * ec1 * O_Plant[0].O_Leaf.m_C / O_PlantPara[0].m_SLA));
        if(totalbiomass1 > 1 && O_Plant[0].O_Leaf.m_C > 0.5) O_Plant[0].m_GPP(O_PlantPara[0], airt, soilt, 365, pa, (ec1 * par), O_Geo.m_Lati, JulDay, &avn, &avp, &decfeedback1, O_Fire.m_Fire[JulDay], leafrecovery, plant1frac);
        par = storepar * exp(-1.0 * ec1 * O_Plant[0].O_Leaf.m_C * O_PlantPara[0].m_SLA);

//cout<<"2 storavn "<<storavn<<" storanp "<<storavp<<endl;
//cout<<"2 avn "<<avn<<" avp "<<avp<<endl;
        float storepar1 = par;
        par = storepar1 * (1.0 - exp(-1.0 * ec2 * O_Plant[1].O_Leaf.m_C / O_PlantPara[1].m_SLA));
        if(totalbiomass2 > 1 && O_Plant[1].O_Leaf.m_C > 0.5) O_Plant[1].m_GPP(O_PlantPara[1], airt, soilt, 365, pa, (ec2 * par), O_Geo.m_Lati, JulDay, &avn, &avp, &decfeedback2, O_Fire.m_Fire[JulDay], leafrecovery, plant2frac);
        par = storepar1 * exp(-1.0 * ec2 * O_Plant[1].O_Leaf.m_C * O_PlantPara[1].m_SLA);

//cout<<"3 storavn "<<storavn<<" storanp "<<storavp<<endl;
//cout<<"3 avn "<<avn<<" avp "<<avp<<endl;
        }
else
        {
        if(planth2 > (planth1))
                {
                par = storepar * (1.0 - exp(-1.0 * ec2 * O_Plant[1].O_Leaf.m_C / O_PlantPara[1].m_SLA));
                if(totalbiomass2 > 1 && O_Plant[1].O_Leaf.m_C > 0.5) O_Plant[1].m_GPP(O_PlantPara[1], airt, soilt, 365, pa, (ec2 * par), O_Geo.m_Lati, JulDay, &avn, &avp, &decfeedback1, O_Fire.m_Fire[JulDay], leafrecovery, plant2frac);
                par = storepar * exp(-1.0 * ec2 * O_Plant[1].O_Leaf.m_C * O_PlantPara[1].m_SLA);
                float storepar1 = par;
                par = storepar1 * (1.0 - exp(-1.0 * ec1 * O_Plant[0].O_Leaf.m_C / O_PlantPara[0].m_SLA));
                if(totalbiomass1 > 1 && O_Plant[0].O_Leaf.m_C > 0.5) O_Plant[0].m_GPP(O_PlantPara[0], airt, soilt, 365, pa, (ec1 * par), O_Geo.m_Lati, JulDay, &avn, &avp, &decfeedback2, O_Fire.m_Fire[JulDay], leafrecovery, plant1frac);
                par = storepar1 * exp(-1.0 * ec1 * O_Plant[0].O_Leaf.m_C * O_PlantPara[0].m_SLA);
                }
        }

        int g_SLayer = 4;

//cout<<" here "<<storavp<<" "<<avp<<endl;
//                cout<<"OK4 "<<O_Soil[0].m_SINPO4<<endl;
for(int layer = 1; layer < g_SLayer; layer++)
        {
        O_Water[layer].m_DNH4 -= O_Water[layer].m_DNH4 * (storavn - avn) / storavn;
        O_Water[layer].m_DNO3 -= O_Water[layer].m_DNO3 * (storavn - avn) / storavn;
        O_Soil[layer-1].m_SINNH4 -= O_Soil[layer-1].m_SINNH4 * (storavn - avn) / storavn;
        O_Soil[layer-1].m_SINNH4 -= O_Soil[layer-1].m_SINNH4 * (storavn - avn) / storavn;

//cout<<"2: "<<O_Water[layer].m_DPO4<<endl;
        O_Water[layer].m_DPO4 -= O_Water[layer].m_DPO4 * (storavp - avp) / storavp;
        O_Soil[layer-1].m_SINPO4 -= O_Soil[layer-1].m_SINPO4 * (storavp - avp) / storavp;
        }
//                cout<<"OK5 "<<O_Soil[0].m_SINPO4<<endl;
m_Periphyton(par);

O_Plant[0].m_Burning(O_Atm, O_PlantPara[0], O_Fire.m_Fire[day], day, O_Water[0].m_WaterDepth, leafrecovery);
O_Plant[1].m_Burning(O_Atm, O_PlantPara[1], O_Fire.m_Fire[day], day, O_Water[0].m_WaterDepth, leafrecovery);

if(O_Fire.m_Fire[day] > 0)
{
        O_Floc.m_C += O_Periphyton.m_C;
        O_Floc.m_N += O_Periphyton.m_N;
        O_Floc.m_P += O_Periphyton.m_P;
        O_Periphyton.m_C = 0.0;
        O_Periphyton.m_N = 0.0;
        O_Periphyton.m_P = 0.0;
}


if(day >= 1)
        {
        O_Atm.m_AshC[day] += O_Atm.m_AshC[day-1];
        O_Atm.m_AshN[day] += O_Atm.m_AshN[day-1];
        O_Atm.m_AshP[day] += O_Atm.m_AshP[day-1];
        }

O_Plant[0].m_LitterSeedUpdate(O_PlantPara[0], (day + 1)%365, O_Water[0].m_WaterDepth, plant1frac);
O_Plant[1].m_LitterSeedUpdate(O_PlantPara[1], (day + 1)%365, O_Water[0].m_WaterDepth, plant2frac);

//O_Atm.m_AshFlow(day);

if(postdayfire > 0 & postdayfire < 10)
{
if(O_Water[0].m_WaterVolume > 0.05)
        {
        O_Water[0].O_PON.m_C += O_Atm.m_AshC[day] * O_Atm.m_AshDepositionRate;
        O_Water[0].O_PON.m_N += O_Atm.m_AshN[day] * O_Atm.m_AshDepositionRate;
        O_Water[0].O_PON.m_P += O_Atm.m_AshP[day] * O_Atm.m_AshDepositionRate;
        }
else
        {
        O_Water[1].O_PON.m_C += O_Atm.m_AshC[day] * O_Atm.m_AshDepositionRate;
        O_Water[1].O_PON.m_N += O_Atm.m_AshN[day] * O_Atm.m_AshDepositionRate;
        O_Water[1].O_PON.m_P += O_Atm.m_AshP[day] * O_Atm.m_AshDepositionRate;
        }

O_Atm.m_AshC[day] -= O_Atm.m_AshC[day] * O_Atm.m_AshDepositionRate;
O_Atm.m_AshN[day] -= O_Atm.m_AshN[day] * O_Atm.m_AshDepositionRate;
O_Atm.m_AshP[day] -= O_Atm.m_AshP[day] * O_Atm.m_AshDepositionRate;
}

O_Atm.m_AshFlow(day);

m_FlocUpdate();
//cout<<"OK4 "<<O_Soil[0].m_SINNH4<<endl;

float lightext = (1.0 - par / storepar);

m_SurfaceWaterT(airt, O_WaterPara, lightext);

if(O_Fire.m_Fire[day] > 0)
{
        O_Water[0].m_WaterT += 1.0;
}

m_SoilWaterT();

m_HeatTransfer(O_Water[0].m_WaterDepth, O_SoilPara.m_BottomT);
//cout<<"OK5 "<<O_Soil[0].m_SINNH4<<endl;
m_SoilWaterT();

float maxdecfeedback = g_Max(decfeedback1, decfeedback2);
if(maxdecfeedback < 1.0)         maxdecfeedback = 1.0;
//                cout<<"OK6 "<<O_Soil[0].m_SINPO4<<endl;
m_SoilBGC(O_PlantPara, O_SoilPara, O_WaterPara, airt, O_Water[2].m_WaterT, maxdecfeedback, day);
//                cout<<"OK7 "<<O_Soil[0].m_SINPO4<<endl;
//m_CalPET(O_Geo.m_Lati, ppt, airt, JulDay);
//m_CalAET(maxh, mlai, ppt, airt, JulDay, O_Geo.m_Lati);
m_WaterBalance(maxh, mlai, ppt, airt, totalsr, JulDay, O_Geo.m_Lati);
//cout<<"OK6"<<endl;
m_SoilWaterUpdate(day);
//cout<<"here2 "<<O_Water[0].m_WaterVolume<<endl;
for(int i = 0; i < 4; i++)
        {
        if(O_Water[i].m_DNH4 < 10e-10)  O_Water[i].m_DNH4 = 10e-10;
        if(O_Water[i].m_DNO3 < 10e-10)  O_Water[i].m_DNO3 = 10e-10;
        if(O_Water[i].m_DPO4 < 10e-10)  O_Water[i].m_DPO4 = 10e-10;
        if(O_Water[i].O_DON.m_C < 10e-10)  O_Water[i].O_DON.m_C = 10e-10;
        if(O_Water[i].O_DON.m_N < 10e-10)  O_Water[i].O_DON.m_N = 10e-10;
        if(O_Water[i].O_DON.m_P < 10e-10)  O_Water[i].O_DON.m_P = 10e-10;
        if(O_Water[i].O_PON.m_C < 10e-10)  O_Water[i].O_PON.m_C = 10e-10;
        if(O_Water[i].O_PON.m_N < 10e-10)  O_Water[i].O_PON.m_N = 10e-10;
        if(O_Water[i].O_PON.m_P < 10e-10)  O_Water[i].O_PON.m_P = 10e-10;
        }
for(int i = 0; i < 3; i++)
        {
        if(O_Soil[i].m_SINNH4 < 10e-10)  O_Soil[i].m_SINNH4 = 10e-10;
        if(O_Soil[i].m_SINNO3 < 10e-10)  O_Soil[i].m_SINNO3 = 10e-10;
        if(O_Soil[i].m_SINPO4 < 10e-10)  O_Soil[i].m_SINPO4 = 10e-10;
        if(O_Soil[i].O_SON.m_C < 10e-10)  O_Soil[i].O_SON.m_C = 10e-10;
        if(O_Soil[i].O_SON.m_N < 10e-10)  O_Soil[i].O_SON.m_N = 10e-10;
        if(O_Soil[i].O_SON.m_P < 10e-10)  O_Soil[i].O_SON.m_P = 10e-10;
        if(O_Soil[i].m_AbsNH4 < 10e-10)  O_Soil[i].m_AbsNH4 = 10e-10;
        if(O_Soil[i].m_AbsNO3 < 10e-10)  O_Soil[i].m_AbsNO3 = 10e-10;
        if(O_Soil[i].m_AbsPO4 < 10e-10)  O_Soil[i].m_AbsPO4 = 10e-10;
        }
}

void WEMecosystem::m_Output(int day)
{
ofstream outflowsave;
outflowsave.open(outflowfile.c_str(), ios::app);

float agb1 = O_Plant[0].O_Leaf.m_C;
float agdm1 = O_Plant[0].O_Litter.m_C;
float bgb1 = O_Plant[0].O_Rhizome.m_C + O_Plant[0].O_ShootBase.m_C + O_Plant[0].O_FRoot.m_C + O_Plant[0].O_CRoot.m_C;
float bgdm1 = O_Plant[0].O_DeadBG.m_C;

float agb2 = O_Plant[1].O_Leaf.m_C;
float agdm2 = O_Plant[1].O_Litter.m_C;
float bgb2 = O_Plant[1].O_Rhizome.m_C + O_Plant[1].O_ShootBase.m_C + O_Plant[1].O_FRoot.m_C + O_Plant[1].O_CRoot.m_C;
float bgdm2 = O_Plant[1].O_DeadBG.m_C;

float swtp;
if(O_Water[0].m_WaterDepth < 0.05)      swtp = -99;
else    swtp = (O_Water[0].m_DPO4 + O_Water[0].O_DON.m_P + O_Water[0].O_PON.m_P) / O_Water[0].m_WaterDepth;

float pwtp = (O_Water[1].m_DPO4 + O_Water[1].O_DON.m_P + O_Water[1].O_PON.m_P + O_Water[2].m_DPO4 + O_Water[2].O_DON.m_P + O_Water[2].O_PON.m_P + O_Water[3].m_DPO4 + O_Water[3].O_DON.m_P + O_Water[3].O_PON.m_P) / (O_Water[1].m_WaterDepth + O_Water[2].m_WaterDepth + O_Water[3].m_WaterDepth);
float stp = (O_Soil[0].m_SINPO4 + O_Soil[0].m_AbsPO4 + O_Soil[0].O_SON.m_P + O_Soil[0].O_LabSOM.m_P + O_Soil[0].O_MidSOM.m_P + O_Soil[0].O_ResSOM.m_P +
             O_Soil[1].m_SINPO4 + O_Soil[1].m_AbsPO4 + O_Soil[1].O_SON.m_P + O_Soil[1].O_LabSOM.m_P + O_Soil[1].O_MidSOM.m_P + O_Soil[1].O_ResSOM.m_P +
             O_Soil[2].m_SINPO4 + O_Soil[2].m_AbsPO4 + O_Soil[2].O_SON.m_P + O_Soil[2].O_LabSOM.m_P + O_Soil[2].O_MidSOM.m_P + O_Soil[2].O_ResSOM.m_P) / 0.3;
float watertemp = O_Water[0].m_WaterT;
float soiltemp = O_Water[1].m_WaterT;
float watertable = O_Water[0].m_WaterDepth;

if(g_IsCalibration == 0)
        {
        ofstream outstream;
        outstream.open(outfilename.c_str(), ios::app);
                outstream<<
                " AGB "<<agb1<<" AGDM "<<agdm1<<" BGB "<<bgb1<<" BGDM "<<bgdm1<<
                " AGB "<<agb2<<" AGDM "<<agdm2<<" BGB "<<bgb2<<" BGDM "<<bgdm2<<
                " SWTP "<<swtp<<" PWTP "<<pwtp<<" SoilTP "<<stp<<" watertem "<<watertemp<<" soiltem "<<soiltemp<<" watertable "<<watertable<<
                " periphyton "<<setw(20)<<O_Periphyton.m_C<<" "<<setw(20)<<O_Periphyton.m_N<<" "<<setw(20)<<O_Periphyton.m_P<<endl;
/*                " cattail_leaf "<<setw(20)<<O_Plant[0].O_Leaf.m_C<<" "<<setw(20)<<O_Plant[0].O_Leaf.m_N<<" "<<setw(20)<<O_Plant[0].O_Leaf.m_P<<
                " cattail_shootbase "<<setw(20)<<O_Plant[0].O_ShootBase.m_C<<" "<<setw(20)<<O_Plant[0].O_ShootBase.m_N<<" "<<setw(20)<<O_Plant[0].O_ShootBase.m_P<<
                " cattail_rhizome "<<setw(20)<<O_Plant[0].O_Rhizome.m_C<<" "<<setw(20)<<O_Plant[0].O_Rhizome.m_N<<" "<<setw(20)<<O_Plant[0].O_Rhizome.m_P<<
                " cattail_croot "<<setw(20)<<O_Plant[0].O_CRoot.m_C<<" "<<setw(20)<<O_Plant[0].O_CRoot.m_N<<" "<<setw(20)<<O_Plant[0].O_CRoot.m_P<<
                " cattail_froot "<<setw(20)<<O_Plant[0].O_FRoot.m_C<<" "<<setw(20)<<O_Plant[0].O_FRoot.m_N<<" "<<setw(20)<<O_Plant[0].O_FRoot.m_P<<
                " cattail_litter "<<setw(20)<<O_Plant[0].O_Litter.m_C<<" "<<setw(20)<<O_Plant[0].O_Litter.m_N<<" "<<setw(20)<<O_Plant[0].O_Litter.m_P<<
                " cattail_deadbg "<<setw(20)<<O_Plant[0].O_DeadBG.m_C<<" "<<setw(20)<<O_Plant[0].O_DeadBG.m_N<<" "<<setw(20)<<O_Plant[0].O_DeadBG.m_P<<
                " cattail_fluxes"<<setw(20)<<O_Plant[0].m_GPPvalue<<" "<<setw(20)<<O_Plant[0].m_NPPvalue<<" "<<setw(20)<<O_Plant[0].m_ARvalue<<
                " sawgrass_AGB "<<setw(20)<<O_Plant[1].O_Leaf.m_C<<" sawgrass_BGB "<<(O_Plant[1].O_Rhizome.m_C + O_Plant[1].O_ShootBase.m_C + O_Plant[1].O_FRoot.m_C + O_Plant[1].O_CRoot.m_C)<<" sawgrass_ABDM "<<O_Plant[1].O_Litter.m_C<<" Sawgrass_BGDM "<<O_Plant[1].O_DeadBG.m_C<<
                " sawgrass_leaf "<<setw(20)<<O_Plant[1].O_Leaf.m_C<<" "<<setw(20)<<O_Plant[1].O_Leaf.m_N<<" "<<setw(20)<<O_Plant[1].O_Leaf.m_P<<
                " sawgrass_shootbase "<<setw(20)<<O_Plant[1].O_ShootBase.m_C<<" "<<setw(20)<<O_Plant[1].O_ShootBase.m_N<<" "<<setw(20)<<O_Plant[1].O_ShootBase.m_P<<
                " sawgrass_rhizome "<<setw(20)<<O_Plant[1].O_Rhizome.m_C<<" "<<setw(20)<<O_Plant[1].O_Rhizome.m_N<<" "<<setw(20)<<O_Plant[1].O_Rhizome.m_P<<
                " sawgrass_croot "<<setw(20)<<O_Plant[1].O_CRoot.m_C<<" "<<setw(20)<<O_Plant[1].O_CRoot.m_N<<" "<<setw(20)<<O_Plant[1].O_CRoot.m_P<<
                " sawgrass_froot "<<setw(20)<<O_Plant[1].O_FRoot.m_C<<" "<<setw(20)<<O_Plant[1].O_FRoot.m_N<<" "<<setw(20)<<O_Plant[1].O_FRoot.m_P<<
                " sawgrass_litter "<<setw(20)<<O_Plant[1].O_Litter.m_C<<" "<<setw(20)<<O_Plant[1].O_Litter.m_N<<" "<<setw(20)<<O_Plant[1].O_Litter.m_P<<
                " sawgrass_deadbg "<<setw(20)<<O_Plant[1].O_DeadBG.m_C<<" "<<setw(20)<<O_Plant[1].O_DeadBG.m_N<<" "<<setw(20)<<O_Plant[1].O_DeadBG.m_P<<
                " sawgrass_fluxes"<<setw(20)<<O_Plant[1].m_GPPvalue<<" "<<setw(20)<<O_Plant[1].m_NPPvalue<<" "<<setw(20)<<O_Plant[1].m_ARvalue<<
                " periphyton "<<setw(20)<<O_Periphyton.m_C<<" "<<setw(20)<<O_Periphyton.m_N<<" "<<setw(20)<<O_Periphyton.m_P<<
                " floc "<<setw(20)<<O_Floc.m_C<<" "<<setw(20)<<O_Floc.m_N<<" "<<setw(20)<<O_Floc.m_P<<
                " 1soil_SIN "<<setw(20)<<O_Soil[0].m_SINNH4<<" "<<setw(20)<<O_Soil[0].m_SINNO3<<" "<<setw(20)<<O_Soil[0].m_SINPO4<<
                " 1soil_abs "<<setw(20)<<O_Soil[0].m_AbsNH4<<" "<<setw(20)<<O_Soil[0].m_AbsNO3<<" "<<setw(20)<<O_Soil[0].m_AbsPO4<<
                " 1soil_SON "<<setw(20)<<O_Soil[0].O_SON.m_C<<" "<<setw(20)<<O_Soil[0].O_SON.m_N<<" "<<setw(20)<<O_Soil[0].O_SON.m_P<<
                " 1soil_LABSOM "<<setw(20)<<O_Soil[0].O_LabSOM.m_C<<" "<<setw(20)<<O_Soil[0].O_LabSOM.m_N<<" "<<setw(20)<<O_Soil[0].O_LabSOM.m_P<<
                " 1soil_MidSOM "<<setw(20)<<O_Soil[0].O_MidSOM.m_C<<" "<<setw(20)<<O_Soil[0].O_MidSOM.m_N<<" "<<setw(20)<<O_Soil[0].O_MidSOM.m_P<<
                " 1soil_RESSOM "<<setw(20)<<O_Soil[0].O_ResSOM.m_C<<" "<<setw(20)<<O_Soil[0].O_ResSOM.m_N<<" "<<setw(20)<<O_Soil[0].O_ResSOM.m_P<<
                " 2soil_SIN "<<setw(20)<<O_Soil[1].m_SINNH4<<" "<<setw(20)<<O_Soil[1].m_SINNO3<<" "<<setw(20)<<O_Soil[1].m_SINPO4<<
                " 2soil_abs "<<setw(20)<<O_Soil[1].m_AbsNH4<<" "<<setw(20)<<O_Soil[1].m_AbsNO3<<" "<<setw(20)<<O_Soil[1].m_AbsPO4<<
                " 2soil_SON "<<setw(20)<<O_Soil[1].O_SON.m_C<<" "<<setw(20)<<O_Soil[1].O_SON.m_N<<" "<<setw(20)<<O_Soil[1].O_SON.m_P<<
                " 2soil_LABSOM "<<setw(20)<<O_Soil[1].O_LabSOM.m_C<<" "<<setw(20)<<O_Soil[1].O_LabSOM.m_N<<" "<<setw(20)<<O_Soil[1].O_LabSOM.m_P<<
                " 2soil_MIDSOM "<<setw(20)<<O_Soil[1].O_MidSOM.m_C<<" "<<setw(20)<<O_Soil[1].O_MidSOM.m_N<<" "<<setw(20)<<O_Soil[1].O_MidSOM.m_P<<
                " 2soil_RESSOM "<<setw(20)<<O_Soil[1].O_ResSOM.m_C<<" "<<setw(20)<<O_Soil[1].O_ResSOM.m_N<<" "<<setw(20)<<O_Soil[1].O_ResSOM.m_P<<
                " 3soil_SIN "<<setw(20)<<O_Soil[2].m_SINNH4<<" "<<setw(20)<<O_Soil[2].m_SINNO3<<" "<<setw(20)<<O_Soil[2].m_SINPO4<<
                " 3soil_abs "<<setw(20)<<O_Soil[2].m_AbsNH4<<" "<<setw(20)<<O_Soil[2].m_AbsNO3<<" "<<setw(20)<<O_Soil[2].m_AbsPO4<<
                " 3soil_SON "<<setw(20)<<O_Soil[2].O_SON.m_C<<" "<<setw(20)<<O_Soil[2].O_SON.m_N<<" "<<setw(20)<<O_Soil[2].O_SON.m_P<<
                " 3soil_LABSOM "<<setw(20)<<O_Soil[2].O_LabSOM.m_C<<" "<<setw(20)<<O_Soil[2].O_LabSOM.m_N<<" "<<setw(20)<<O_Soil[2].O_LabSOM.m_P<<
                " 3soil_MIDSOM "<<setw(20)<<O_Soil[2].O_MidSOM.m_C<<" "<<setw(20)<<O_Soil[2].O_MidSOM.m_N<<" "<<setw(20)<<O_Soil[2].O_MidSOM.m_P<<
                " 3soil_RESSOM "<<setw(20)<<O_Soil[2].O_ResSOM.m_C<<" "<<setw(20)<<O_Soil[2].O_ResSOM.m_N<<" "<<setw(20)<<O_Soil[2].O_ResSOM.m_P<<
                " soil_temp "<<setw(20)<<O_Soil[0].m_SoilT<<" "<<setw(20)<<O_Soil[1].m_SoilT<<" "<<O_Soil[2].m_SoilT<<
                " 1water_DIN "<<setw(20)<<O_Water[0].m_DNH4<<" "<<setw(20)<<O_Water[0].m_DNO3<<" "<<setw(20)<<O_Water[0].m_DPO4<<
                " 1water_DON "<<setw(20)<<O_Water[0].O_DON.m_C<<" "<<setw(20)<<O_Water[0].O_DON.m_N<<" "<<setw(20)<<O_Water[0].O_DON.m_P<<
                " 1water_PON "<<setw(20)<<O_Water[0].O_PON.m_C<<" "<<setw(20)<<O_Water[0].O_PON.m_N<<" "<<setw(20)<<O_Water[0].O_PON.m_P<<
                " 2water_DIN "<<setw(20)<<O_Water[1].m_DNH4<<" "<<setw(20)<<O_Water[1].m_DNO3<<" "<<setw(20)<<O_Water[1].m_DPO4<<
                " 2water_DON "<<setw(20)<<O_Water[1].O_DON.m_C<<" "<<setw(20)<<O_Water[1].O_DON.m_N<<" "<<setw(20)<<O_Water[1].O_DON.m_P<<
                " 2water_PON "<<setw(20)<<O_Water[1].O_PON.m_C<<" "<<setw(20)<<O_Water[1].O_PON.m_N<<" "<<setw(20)<<O_Water[1].O_PON.m_P<<
                " 3water_DIN "<<setw(20)<<O_Water[2].m_DNH4<<" "<<setw(20)<<O_Water[2].m_DNO3<<" "<<setw(20)<<O_Water[2].m_DPO4<<
                " 3water_DON "<<setw(20)<<O_Water[2].O_DON.m_C<<" "<<setw(20)<<O_Water[2].O_DON.m_N<<" "<<setw(20)<<O_Water[2].O_DON.m_P<<
                " 3water_PON "<<setw(20)<<O_Water[2].O_PON.m_C<<" "<<setw(20)<<O_Water[2].O_PON.m_N<<" "<<setw(20)<<O_Water[2].O_PON.m_P<<
                " 4water_DIN "<<setw(20)<<O_Water[3].m_DNH4<<" "<<setw(20)<<O_Water[3].m_DNO3<<" "<<setw(20)<<O_Water[3].m_DPO4<<
                " 4water_DON "<<setw(20)<<O_Water[3].O_DON.m_C<<" "<<setw(20)<<O_Water[3].O_DON.m_N<<" "<<setw(20)<<O_Water[3].O_DON.m_P<<
                " 4water_PON "<<setw(20)<<O_Water[3].O_PON.m_C<<" "<<setw(20)<<O_Water[3].O_PON.m_N<<" "<<setw(20)<<O_Water[3].O_PON.m_P<<
                " water_depth "<<setw(20)<<O_Water[0].m_WaterDepth<<" "<<setw(20)<<O_Water[1].m_WaterDepth<<" "<<setw(20)<<O_Water[2].m_WaterDepth<<" "<<setw(20)<<O_Water[3].m_WaterDepth<<
                " water_temp "<<setw(20)<<O_Water[0].m_WaterT<<" "<<setw(20)<<O_Water[1].m_WaterT<<" "<<setw(20)<<O_Water[2].m_WaterT<<" "<<setw(20)<<O_Water[3].m_WaterT<<
                " ash "<<setw(20)<<O_Atm.m_AshC[day]<<" "<<setw(20)<<O_Atm.m_AshN[day]<<" "<<setw(20)<<O_Atm.m_AshP[day]<<
                " fire_gas "<<setw(20)<<O_Atm.m_COx[day]<<" "<<setw(20)<<O_Atm.m_NOx[day];
*/
if(g_WaterOrOutflow == 1)
                {
/*                outstream<<
                " outflow "<<setw(20)<<O_Flow.m_OutWater[day]<<" "<<setw(20)<<O_Flow.m_OutNH4[day]<<" "<<setw(20)<<O_Flow.m_OutNO3[day]<<" "<<setw(20)<<O_Flow.m_OutPO4[day]<<
                " outflow "<<setw(20)<<O_Flow.m_OutDOC[day]<<" "<<setw(20)<<O_Flow.m_OutDON[day]<<" "<<setw(20)<<O_Flow.m_OutDOP[day]<<
                " outflow "<<setw(20)<<O_Flow.m_OutPOC[day]<<" "<<setw(20)<<O_Flow.m_OutPON[day]<<" "<<setw(20)<<O_Flow.m_OutPOP[day]<<
                endl;
*/                outflowsave<<day<<" "<<day<<" "<<day<<" "<<O_Flow.m_InWater[day]<<" "<<setw(20)<<O_Flow.m_OutNH4[day]<<" "<<O_Flow.m_OutNO3[day]<<" "<<setw(20)<<O_Flow.m_OutPO4[day]<<" "
                <<O_Flow.m_OutDOC[day]<<" "<<O_Flow.m_OutDON[day]<<" "<<O_Flow.m_OutDOP[day]<<" "<<O_Flow.m_OutPOC[day]<<" "<<O_Flow.m_OutPON[day]<<" "<<O_Flow.m_OutPOP[day]<<" "<<O_Flow.m_WaterTable[day]<<endl;
                }
else
                {
                outstream<<" outflow "<<setw(20)<<O_Flow.m_WaterTable[day]<<
                endl;
                }
        outstream.close();
        }
else
        {
        cout<<"The output is done, the result is shown on the screen!  "<<endl;
        }
}



float WEMecosystem::m_CalPET(float lat, float ppt, float temperature, int JulDay)
{
int daynumber = JulDay;
float daylength, Decline, yeardaylength;

float lat_r =  lat * O_Cons.m_PI / 180.0;

	Decline = O_Cons.m_MINDECL * cos((daynumber + O_Cons.m_DAYSOFF) * O_Cons.m_RADPERDAY);

	daylength = 2 * acos(-sin(lat_r) * sin(Decline) / cos(lat_r) / cos(Decline)) * O_Cons.m_SPECPERRAD;

	yeardaylength = 0;
	for(int i = 0; i < 365; i++)
	{
	Decline = O_Cons.m_MINDECL * cos(((daynumber+1) + O_Cons.m_DAYSOFF) * O_Cons.m_RADPERDAY);
	yeardaylength += 2 * acos(-sin(lat_r) * sin(Decline) / cos(lat_r) / cos(Decline)) * O_Cons.m_SPECPERRAD;
	}

m_PET = 1.2 * ((-1.7 + 1.1 * 100.0 * daylength / yeardaylength * (0.46 * temperature + 8.0))) / 1000.0;

float maxrain = 500.0; // Assume 100 mm rain in one day will last whole day, the et will be decline substaintially

float raineffect;
if(ppt > maxrain)       raineffect = 1.0;
else            raineffect = ppt / maxrain;
m_PET *= exp(-1.0 * raineffect);

return m_PET;
}

float WEMecosystem::m_CalAET(float height, float LAI, float ppt, float temperature, int JulDay, float lat)
{
float fLAI, LAI_effect;

if(height <= 0) LAI_effect = 0.0;
else    LAI_effect = g_Max(1.0 - O_Water[0].m_WaterDepth / height, 0.0) * LAI / 10.;

if(fLAI >= 0.1)	fLAI = 0.1;     // Xiaofeng Add this condition which is different from ELM

fLAI = exp(-LAI_effect);
m_AET = fLAI * m_CalPET(lat, ppt, temperature, JulDay);

return (m_AET);
}


float WEMecosystem::m_CalAETNew(float totalsr)
{
float aet;
aet = totalsr * 0.53 / 2440.0;
return aet;
}


void WEMecosystem::m_WaterBalance(float maxh, float maxLAI, float ppt, float temperature, float totalsr, int JulDay, float lat)
{
//cout<<"waterbalance: "<<O_Water[0].m_WaterVolume<<" "<<ppt<<endl;

O_Water[0].m_WaterVolume += ppt / 1000.0;

if((O_Water[1].m_WaterVolume < (O_Soil[0].m_SoilPoro * m_SoilThick[0])) && (O_Water[0].m_WaterVolume >= 10e-5))
{
        if(O_Water[0].m_WaterVolume < ((O_Soil[0].m_SoilPoro * m_SoilThick[0]) - O_Water[1].m_WaterVolume))
        {
        O_Water[1].m_WaterVolume += O_Water[0].m_WaterVolume;
        O_Water[0].m_WaterVolume = 0.0;
        }
        else
        {
        O_Water[0].m_WaterVolume -= ((O_Soil[0].m_SoilPoro * m_SoilThick[0]) - O_Water[1].m_WaterVolume);
        O_Water[1].m_WaterVolume = (O_Soil[0].m_SoilPoro * m_SoilThick[0]);
        }
}

m_AET = m_CalAETNew(totalsr);
float temaet = m_AET;
//float temaet = m_CalAET(maxh, maxLAI, ppt, temperature, JulDay, lat);
//cout<<"AET: "<<temaet<<endl;

if(O_Water[0].m_WaterVolume <= temaet)
        {
        O_Water[1].m_WaterVolume -= (temaet - O_Water[0].m_WaterVolume);
        O_Water[0].m_WaterVolume = 0.0;
        }
else    O_Water[0].m_WaterVolume -= temaet;

//cout<<O_Water[0].m_WaterVolume<<endl;

if(O_Water[0].m_WaterVolume < 0.)      O_Water[0].m_WaterVolume = 0.;
if(O_Water[1].m_WaterVolume < 0.001)      O_Water[1].m_WaterVolume = 0.001;
//O_Water[0].m_WaterDepth = O_Water[0].m_WaterVolume;

O_Water[0].m_WaterDepth = O_Water[0].m_WaterVolume;

for(int i = 1; i < (3 + 1); i++)
        {
        if(O_Water[0].m_WaterVolume > 0)
        O_Water[i].m_WaterVolume = O_Soil[i-1].m_SoilPoro * m_SoilThick[i-1];
        O_Water[i].m_WaterDepth = O_Water[i].m_WaterVolume;
        }
//cout<<"water volume: "<<O_Water[6].m_WaterVolume<<" "<<O_Water[6].m_WaterDepth<<endl;
//m_Eh = -197.39 + pow(299.69, (-9.95 * O_Water[0].m_WaterDepth));

//cout<<"waterbalance: "<<m_AET<<endl;

}


void WEMecosystem::m_SurfaceWaterT(float airt, WEMwaterparameter O_WaterPara, float lighext)
{
// Computation of the temperature of surface water based on air temperature
// Charles E. Adams, Jr. (1976) Estimating water temperture and time of ice formation on the Saint Lawrence River
// Limnology and Oceanography 21(1): 128-137.
//T1 = T0 - (1/po * Cp * h) * Q*t
// T0 is the initial water temperature, p0 is the water density, Cp is the speicfic heat of water
// h is the water depth, Q is the surface heat loss rate, T1 is the water temperature at time t.
float temp = pow((1.0 - lighext), 0.5);

if(O_Water[0].m_WaterDepth < 0.01)      O_Water[0].m_WaterT = airt;
else
        {
                for(int h = 0; h < 1140; h++)
                O_Water[0].m_WaterT += temp * (1.0 / O_WaterPara.m_WBulkD) * O_WaterPara.m_HeatSpecific * O_Water[0].m_WaterDepth * O_WaterPara.m_AirWaterK * (airt - O_Water[0].m_WaterT);
        }
}

void WEMecosystem::m_HeatTransfer(float swdepth, float bottomt)
{
//cout<<"Before: "<<O_Soil[0].m_SoilT<<" "<<O_Soil[1].m_SoilT<<" "<<O_Soil[2].m_SoilT<<endl;
// Distriubte the bulk density along the soil profile,
//so if the soil is divided into six layers,
//the bulk densities for six layers are 2.0 * B, 1.0 * B, B + (2.65 - B) / 5; B + (2.65 - B) * 2.0 / 5; B + 3.0 * (2.65 - B) / 5; B + 4.0 * (2.65 - B) / 5;
float temperature = O_Water[0].m_WaterT;
O_Soil[0].m_SoilBulkD = O_Geo.m_BulkD;
for(int l = 1; l < 3; l++)
        {
        O_Soil[l].m_SoilBulkD = O_Geo.m_BulkD + (2.65 - O_Geo.m_BulkD) * (l - 1) / (3 - 1);
        }

        for(int layer = 0; layer < 3; layer++)
        {
                O_Soil[layer].m_SoilPoro = 1.0 - O_Soil[layer].m_SoilBulkD / 2.65;
                float fo = (O_Soil[layer].O_LabSOM.m_C + O_Soil[layer].O_MidSOM.m_C + O_Soil[layer].O_ResSOM.m_C) * 1.724 / (O_Cons.m_OrgBD * m_SoilThick[layer]);
                float fw = O_Soil[layer].m_SoilPoro;
                O_Soil[layer].m_TotalC = fo * O_Cons.m_OrgC +  fw * O_Cons.m_WaterC;

                O_Soil[layer].m_TotalK = O_Soil[layer].m_SoilPoro * O_Cons.m_WaterK + (1.0 - O_Soil[layer].m_SoilPoro) * O_Cons.m_OrgK * fo/(fo + fw);
        }

        float heatflux[4] = {0};

        float timestep = 1.0 / 24.0 / 60.0;   // Time step for heat transfer is minute

        for(float initial = 0.0; initial <= 1.0;)
        {
                heatflux[0] = O_Soil[0].m_TotalK * (temperature - O_Soil[0].m_SoilT) * 2.0 / (m_SoilThick[0]) * 60.0 * 24.0;
                for(int sl = 1; sl < (3); sl++)
                {
                heatflux[sl] = O_Soil[sl].m_TotalK * (O_Soil[sl-1].m_SoilT - O_Soil[sl].m_SoilT) * 2.0 / (m_SoilThick[sl - 1] + m_SoilThick[sl]) * 60.0 * 24.0;
                }
                heatflux[3] = O_Soil[3-1].m_TotalK * (O_Soil[3-1].m_SoilT - bottomt) / 2.0 / m_SoilThick[3-1] * 60.0 * 24.0;


                O_Soil[0].m_SoilT += heatflux[0] / (O_Soil[0].m_TotalC * m_SoilThick[0]);

                for(int sl = 1; sl < 3; sl++)
                {
                O_Soil[sl-1].m_SoilT -= heatflux[sl] / (O_Soil[sl-1].m_TotalC * m_SoilThick[sl-1]);

                O_Soil[sl].m_SoilT += heatflux[sl] / (O_Soil[sl].m_TotalC * m_SoilThick[sl]);
                }

                O_Soil[3-1].m_SoilT -= heatflux[3] / (O_Soil[3-1].m_TotalC * m_SoilThick[3-1]);

        initial += timestep;
        }
}

void WEMecosystem::m_SoilBGC(WEMplantparameter *plantpara, WEMsoilparameter soilpara, WEMwaterparameter waterpara, float airT, float soilT, float maxdecfeedback, int day)
{
static int postday;
static float storepondec;
static float pondec;
static float precipitation;

if(O_Fire.m_Fire[day] > 0.1)
        {
        postday = 1;
        storepondec = 0.7;
        precipitation = 0.8;
        pondec = 0.7;
        }

if(postday > 0.1 && postday < 61)
        {
        storepondec = pow((0.7 + postday / 200.0), 3);
        precipitation = pow((0.8 + postday / 300.), 2.5);
        pondec = pow((0.7 + postday / 200.), 3);
        postday += 1;
        }
else
        {
        pondec = 1.0;
        postday = 0.0;
        storepondec = 1.0;
        precipitation = 1.0;
        }

// reallocation the som in three  layers
float totallabc, totalmidc, totalresc, totallabn, totalmidn, totalresn, totallabp, totalmidp, totalresp;

totallabc = O_Soil[0].O_LabSOM.m_C + O_Soil[1].O_LabSOM.m_C + O_Soil[2].O_LabSOM.m_C;
O_Soil[0].O_LabSOM.m_C = totallabc * soilpara.m_FirstLayer;
O_Soil[1].O_LabSOM.m_C = totallabc * soilpara.m_SecondLayer;
O_Soil[2].O_LabSOM.m_C = totallabc * soilpara.m_ThirdLayer;

totalmidc = O_Soil[0].O_MidSOM.m_C + O_Soil[1].O_MidSOM.m_C + O_Soil[2].O_MidSOM.m_C;
O_Soil[0].O_MidSOM.m_C = totalmidc * soilpara.m_FirstLayer;
O_Soil[1].O_MidSOM.m_C = totalmidc * soilpara.m_SecondLayer;
O_Soil[2].O_MidSOM.m_C = totalmidc * soilpara.m_ThirdLayer;

totalresc = O_Soil[0].O_ResSOM.m_C + O_Soil[1].O_ResSOM.m_C + O_Soil[2].O_ResSOM.m_C;
O_Soil[0].O_ResSOM.m_C = totalresc * soilpara.m_FirstLayer;
O_Soil[1].O_ResSOM.m_C = totalresc * soilpara.m_SecondLayer;
O_Soil[2].O_ResSOM.m_C = totalresc * soilpara.m_ThirdLayer;

totallabn = O_Soil[0].O_LabSOM.m_N + O_Soil[1].O_LabSOM.m_N + O_Soil[2].O_LabSOM.m_N;
O_Soil[0].O_LabSOM.m_N = totallabn * soilpara.m_FirstLayer;
O_Soil[1].O_LabSOM.m_N = totallabn * soilpara.m_SecondLayer;
O_Soil[2].O_LabSOM.m_N = totallabn * soilpara.m_ThirdLayer;

totalmidn = O_Soil[0].O_MidSOM.m_N + O_Soil[1].O_MidSOM.m_N + O_Soil[2].O_MidSOM.m_N;
O_Soil[0].O_MidSOM.m_N = totalmidn * soilpara.m_FirstLayer;
O_Soil[1].O_MidSOM.m_N = totalmidn * soilpara.m_SecondLayer;
O_Soil[2].O_MidSOM.m_N = totalmidn * soilpara.m_ThirdLayer;

totalresn = O_Soil[0].O_ResSOM.m_N + O_Soil[1].O_ResSOM.m_N + O_Soil[2].O_ResSOM.m_N;
O_Soil[0].O_ResSOM.m_N = totalresn * soilpara.m_FirstLayer;
O_Soil[1].O_ResSOM.m_N = totalresn * soilpara.m_SecondLayer;
O_Soil[2].O_ResSOM.m_N = totalresn * soilpara.m_ThirdLayer;

totallabp = O_Soil[0].O_LabSOM.m_P + O_Soil[1].O_LabSOM.m_P + O_Soil[2].O_LabSOM.m_P;
O_Soil[0].O_LabSOM.m_P = totallabp * soilpara.m_FirstLayer;
O_Soil[1].O_LabSOM.m_P = totallabp * soilpara.m_SecondLayer;
O_Soil[2].O_LabSOM.m_P = totallabp * soilpara.m_ThirdLayer;

totalmidp = O_Soil[0].O_MidSOM.m_P + O_Soil[1].O_MidSOM.m_P + O_Soil[2].O_MidSOM.m_P;
O_Soil[0].O_MidSOM.m_P = totalmidp * soilpara.m_FirstLayer;
O_Soil[1].O_MidSOM.m_P = totalmidp * soilpara.m_SecondLayer;
O_Soil[2].O_MidSOM.m_P = totalmidp * soilpara.m_ThirdLayer;

totalresp = O_Soil[0].O_ResSOM.m_P + O_Soil[1].O_ResSOM.m_P + O_Soil[2].O_ResSOM.m_P;
O_Soil[0].O_ResSOM.m_P = totalresp * soilpara.m_FirstLayer;
O_Soil[1].O_ResSOM.m_P = totalresp * soilpara.m_SecondLayer;
O_Soil[2].O_ResSOM.m_P = totalresp * soilpara.m_ThirdLayer;
// End of the reallocation of SOM


//cout<<"here1"<<endl;
float totaldoc = 0.0;
float totaldon = 0.0;
float totaldop = 0.0;

for(int i = 1; i < 4; i++)
        {
        totaldoc += O_Water[i].O_DON.m_C;
        totaldon += O_Water[i].O_DON.m_N;
        totaldop += O_Water[i].O_DON.m_P;
        }

for(int p = 0; p < 2; p++)
        {
        for(int i = 1; i < 4; i++)
                {
                O_Water[i].O_DON.m_C += O_Water[i].O_DON.m_C / totaldoc * O_Plant[p].m_RootExudation.m_C;
                O_Water[i].O_DON.m_N += O_Water[i].O_DON.m_N / totaldon * O_Plant[p].m_RootExudation.m_N;
                O_Water[i].O_DON.m_P += O_Water[i].O_DON.m_P / totaldop * O_Plant[p].m_RootExudation.m_P;
                }
        }

m_RH = 0.0;

float watereffect = 0.0;
if(O_Water[0].m_WaterDepth < 0.1) watereffect = 1.0;
else
        {
        if(O_Water[0].m_WaterDepth < 1.0)       watereffect = pow((1.1 - O_Water[0].m_WaterDepth), 2);
        else    watereffect = 0.25;
        }
if(watereffect < 0.25)  watereffect = 0.25;

float airtemeffect = pow(2.0, exp((airT - 10.0) / 10.0));
float soiltemeffect = pow(2.0, exp((soilT - 10.0) / 10.0));

float totalo2consum = 0.0;

for(int p = 0; p < 2; p++)
        {
        float mortality;

        if(O_Plant[p].O_Leaf.m_C > plantpara[p].m_MinLAI / plantpara[p].m_SLA)
        mortality = plantpara[p].m_Mortality;
        else    mortality = plantpara[p].m_Mortality * 0.5;

// October 27, 2009, Xiaofeng added a coefficient to adjust the mortality to follow a seasonal pattern
//        float adjust = 1.0;
//        adjust = cos(3.47 * ((day + 1) % 365));
//        if(adjust < 0.5)        adjust = 0.5;
//        if(adjust > 1.) adjust = 1.0;
//        mortality = adjust * mortality;

//        float maxbiomass = plantpara[p].m_MaxBiomassC;
//        float biomass = O_Plant[p].O_Leaf.m_C + O_Plant[p].O_ShootBase.m_C + O_Plant[p].O_Rhizome.m_C + O_Plant[p].O_FRoot.m_C + O_Plant[p].O_CRoot.m_C;
//        mortality = mortality * (maxbiomass - biomass) / maxbiomass;
//        if(mortality < 0) mortality = 0.0;

        // Litter increase from plant mortality
        O_Plant[p].O_Litter.m_C += O_Plant[p].O_Leaf.m_C * mortality;
        O_Plant[p].O_Litter.m_N += O_Plant[p].O_Leaf.m_N * mortality * (1.0 - plantpara[p].m_ResorptionN);
        O_Plant[p].O_Leaf.m_N += O_Plant[p].O_Leaf.m_N * mortality * plantpara[p].m_ResorptionN;

        O_Plant[p].O_Litter.m_P += O_Plant[p].O_Leaf.m_P * mortality * (1.0 - plantpara[p].m_ResorptionP);
        O_Plant[p].O_Leaf.m_P += O_Plant[p].O_Leaf.m_P * mortality * plantpara[p].m_ResorptionP;

        O_Plant[p].O_Leaf.m_C -= O_Plant[p].O_Leaf.m_C * mortality;
        O_Plant[p].O_Leaf.m_N -= O_Plant[p].O_Leaf.m_N * mortality;
        O_Plant[p].O_Leaf.m_P -= O_Plant[p].O_Leaf.m_P * mortality;

        O_Plant[p].O_DeadBG.m_C += mortality * (O_Plant[p].O_ShootBase.m_C + O_Plant[p].O_Rhizome.m_C + O_Plant[p].O_FRoot.m_C + O_Plant[p].O_CRoot.m_C);
        O_Plant[p].O_DeadBG.m_N += mortality * (O_Plant[p].O_ShootBase.m_N + O_Plant[p].O_Rhizome.m_N + O_Plant[p].O_FRoot.m_N + O_Plant[p].O_CRoot.m_N);
        O_Plant[p].O_DeadBG.m_P += mortality * (O_Plant[p].O_ShootBase.m_P + O_Plant[p].O_Rhizome.m_P + O_Plant[p].O_FRoot.m_P + O_Plant[p].O_CRoot.m_P);

        O_Plant[p].O_ShootBase.m_C -= O_Plant[p].O_ShootBase.m_C * mortality;
        O_Plant[p].O_ShootBase.m_N -= O_Plant[p].O_ShootBase.m_N * mortality;
        O_Plant[p].O_ShootBase.m_P -= O_Plant[p].O_ShootBase.m_P * mortality;

        O_Plant[p].O_Rhizome.m_C -= O_Plant[p].O_Rhizome.m_C * mortality;
        O_Plant[p].O_Rhizome.m_N -= O_Plant[p].O_Rhizome.m_N * mortality;
        O_Plant[p].O_Rhizome.m_P -= O_Plant[p].O_Rhizome.m_P * mortality;

        O_Plant[p].O_FRoot.m_C -= O_Plant[p].O_FRoot.m_C * mortality;
        O_Plant[p].O_FRoot.m_N -= O_Plant[p].O_FRoot.m_N * mortality;
        O_Plant[p].O_FRoot.m_P -= O_Plant[p].O_FRoot.m_P * mortality;

        O_Plant[p].O_CRoot.m_C -= O_Plant[p].O_CRoot.m_C * mortality;
        O_Plant[p].O_CRoot.m_N -= O_Plant[p].O_CRoot.m_N * mortality;
        O_Plant[p].O_CRoot.m_P -= O_Plant[p].O_CRoot.m_P * mortality;


        float sumlabsomc = O_Soil[0].O_LabSOM.m_C + O_Soil[1].O_LabSOM.m_C + O_Soil[2].O_LabSOM.m_C;
        float sumlabsomn = O_Soil[0].O_LabSOM.m_N + O_Soil[1].O_LabSOM.m_N + O_Soil[2].O_LabSOM.m_N;
        float sumlabsomp = O_Soil[0].O_LabSOM.m_P + O_Soil[1].O_LabSOM.m_P + O_Soil[2].O_LabSOM.m_P;
        float summidsomc = O_Soil[0].O_MidSOM.m_C + O_Soil[1].O_MidSOM.m_C + O_Soil[2].O_MidSOM.m_C;
        float summidsomn = O_Soil[0].O_MidSOM.m_N + O_Soil[1].O_MidSOM.m_N + O_Soil[2].O_MidSOM.m_N;
        float summidsomp = O_Soil[0].O_MidSOM.m_P + O_Soil[1].O_MidSOM.m_P + O_Soil[2].O_MidSOM.m_P;
        float sumressomc = O_Soil[0].O_ResSOM.m_C + O_Soil[1].O_ResSOM.m_C + O_Soil[2].O_ResSOM.m_C;
        float sumressomn = O_Soil[0].O_ResSOM.m_N + O_Soil[1].O_ResSOM.m_N + O_Soil[2].O_ResSOM.m_N;
        float sumressomp = O_Soil[0].O_ResSOM.m_P + O_Soil[1].O_ResSOM.m_P + O_Soil[2].O_ResSOM.m_P;

        float deadc = O_Plant[p].O_DeadBG.m_C * plantpara[p].m_DeadBGToSOM;
        float deadn = O_Plant[p].O_DeadBG.m_N * plantpara[p].m_DeadBGToSOM;
        float deadp = O_Plant[p].O_DeadBG.m_P * plantpara[p].m_DeadBGToSOM;

        O_Soil[0].O_LabSOM.m_C += deadc * O_Soil[0].O_LabSOM.m_C / sumlabsomc * 0.1;
        O_Soil[1].O_LabSOM.m_C += deadc * O_Soil[1].O_LabSOM.m_C / sumlabsomc * 0.1;
        O_Soil[2].O_LabSOM.m_C += deadc * O_Soil[2].O_LabSOM.m_C / sumlabsomc * 0.1;

        O_Soil[0].O_LabSOM.m_N += deadn * O_Soil[0].O_LabSOM.m_N / sumlabsomn * 0.1;
        O_Soil[1].O_LabSOM.m_N += deadn * O_Soil[1].O_LabSOM.m_N / sumlabsomn * 0.1;
        O_Soil[2].O_LabSOM.m_N += deadn * O_Soil[2].O_LabSOM.m_N / sumlabsomn * 0.1;

        O_Soil[0].O_LabSOM.m_P += deadp * O_Soil[0].O_LabSOM.m_P / sumlabsomp * 0.1;
        O_Soil[1].O_LabSOM.m_P += deadp * O_Soil[1].O_LabSOM.m_P / sumlabsomp * 0.1;
        O_Soil[2].O_LabSOM.m_P += deadp * O_Soil[2].O_LabSOM.m_P / sumlabsomp * 0.1;


        O_Soil[0].O_MidSOM.m_C += deadc * O_Soil[0].O_MidSOM.m_C / summidsomc * 0.2;
        O_Soil[1].O_MidSOM.m_C += deadc * O_Soil[1].O_MidSOM.m_C / summidsomc * 0.2;
        O_Soil[2].O_MidSOM.m_C += deadc * O_Soil[2].O_MidSOM.m_C / summidsomc * 0.2;

        O_Soil[0].O_MidSOM.m_N += deadn * O_Soil[0].O_MidSOM.m_N / summidsomn * 0.2;
        O_Soil[1].O_MidSOM.m_N += deadn * O_Soil[1].O_MidSOM.m_N / summidsomn * 0.2;
        O_Soil[2].O_MidSOM.m_N += deadn * O_Soil[2].O_MidSOM.m_N / summidsomn * 0.2;

        O_Soil[0].O_MidSOM.m_P += deadp * O_Soil[0].O_MidSOM.m_P / summidsomp * 0.2;
        O_Soil[1].O_MidSOM.m_P += deadp * O_Soil[1].O_MidSOM.m_P / summidsomp * 0.2;
        O_Soil[2].O_MidSOM.m_P += deadp * O_Soil[2].O_MidSOM.m_P / summidsomp * 0.2;

        O_Soil[0].O_ResSOM.m_C += deadc * O_Soil[0].O_ResSOM.m_C / sumressomc * 0.7;
        O_Soil[1].O_ResSOM.m_C += deadc * O_Soil[1].O_ResSOM.m_C / sumressomc * 0.7;
        O_Soil[2].O_ResSOM.m_C += deadc * O_Soil[2].O_ResSOM.m_C / sumressomc * 0.7;

        O_Soil[0].O_ResSOM.m_N += deadn * O_Soil[0].O_ResSOM.m_N / sumressomn * 0.7;
        O_Soil[1].O_ResSOM.m_N += deadn * O_Soil[1].O_ResSOM.m_N / sumressomn * 0.7;
        O_Soil[2].O_ResSOM.m_N += deadn * O_Soil[2].O_ResSOM.m_N / sumressomn * 0.7;

        O_Soil[0].O_ResSOM.m_P += deadp * O_Soil[0].O_ResSOM.m_P / sumressomp * 0.7;
        O_Soil[1].O_ResSOM.m_P += deadp * O_Soil[1].O_ResSOM.m_P / sumressomp * 0.7;
        O_Soil[2].O_ResSOM.m_P += deadp * O_Soil[2].O_ResSOM.m_P / sumressomp * 0.7;

        O_Plant[p].O_DeadBG.m_C -= deadc;
        O_Plant[p].O_DeadBG.m_N -= deadn;
        O_Plant[p].O_DeadBG.m_P -= deadp;

        // litter will enter the soil organic matter pool inthe first soil layer
        O_Soil[0].O_LabSOM.m_C += soiltemeffect * O_Plant[p].O_Litter.m_C * plantpara[p].m_LittoSOM * plantpara[p].m_ToLabLit;
        O_Soil[0].O_MidSOM.m_C += soiltemeffect * O_Plant[p].O_Litter.m_C * plantpara[p].m_LittoSOM * plantpara[p].m_ToMidLit;
        O_Soil[0].O_ResSOM.m_C += soiltemeffect * O_Plant[p].O_Litter.m_C * plantpara[p].m_LittoSOM * plantpara[p].m_ToResLit;
        O_Plant[p].O_Litter.m_C -= soiltemeffect * O_Plant[p].O_Litter.m_C * plantpara[p].m_LittoSOM;

        O_Soil[0].O_LabSOM.m_N += soiltemeffect * O_Plant[p].O_Litter.m_N * plantpara[p].m_LittoSOM * plantpara[p].m_ToLabLit;
        O_Soil[0].O_MidSOM.m_N += soiltemeffect * O_Plant[p].O_Litter.m_N * plantpara[p].m_LittoSOM * plantpara[p].m_ToMidLit;
        O_Soil[0].O_ResSOM.m_N += soiltemeffect * O_Plant[p].O_Litter.m_N * plantpara[p].m_LittoSOM * plantpara[p].m_ToResLit;
        O_Plant[p].O_Litter.m_N -= soiltemeffect * O_Plant[p].O_Litter.m_N * plantpara[p].m_LittoSOM;

        O_Soil[0].O_LabSOM.m_P += soiltemeffect * O_Plant[p].O_Litter.m_P * plantpara[p].m_LittoSOM * plantpara[p].m_ToLabLit;
        O_Soil[0].O_MidSOM.m_P += soiltemeffect * O_Plant[p].O_Litter.m_P * plantpara[p].m_LittoSOM * plantpara[p].m_ToMidLit;
        O_Soil[0].O_ResSOM.m_P += soiltemeffect * O_Plant[p].O_Litter.m_P * plantpara[p].m_LittoSOM * plantpara[p].m_ToResLit;

        O_Plant[p].O_Litter.m_P -= soiltemeffect * O_Plant[p].O_Litter.m_P * plantpara[p].m_LittoSOM;
        // End of litter to first layer SOM
        //cout<<"after "<<O_Plant[p].O_Litter.m_C<<" "<<O_Plant[p].O_Litter.m_N<<" "<<O_Plant[p].O_Litter.m_P<<endl;

        float leaflitdecompc = 0.0;
        float leaflitdecompn = 0.0;
        float leaflitdecompp = 0.0;

        // Leaf litter Carbon decomposition
        leaflitdecompc += airtemeffect * O_Plant[p].O_Litter.m_C *  plantpara[p].m_LabLitDecom * watereffect;
        O_Plant[p].O_Litter.m_C -= airtemeffect * O_Plant[p].O_Litter.m_C *  plantpara[p].m_LabLitDecom * watereffect;

        totalo2consum += leaflitdecompc * 0.25 / 12.0;          //convert from g/m2 to mol/m2

        m_RH += leaflitdecompc * 0.25;
        leaflitdecompc -= leaflitdecompc * 0.25;

        // Leaf litter Nitrogen decomposition
        leaflitdecompn += airtemeffect * O_Plant[p].O_Litter.m_N *  plantpara[p].m_LabLitDecom * watereffect;
        O_Plant[p].O_Litter.m_N -= airtemeffect * O_Plant[p].O_Litter.m_N *  plantpara[p].m_LabLitDecom * watereffect;

        // Leaf litter Phosphorus decomposition
        leaflitdecompp += airtemeffect * O_Plant[p].O_Litter.m_P *  plantpara[p].m_LabLitDecom * watereffect;
        O_Plant[p].O_Litter.m_P -= airtemeffect * O_Plant[p].O_Litter.m_P *  plantpara[p].m_LabLitDecom * watereffect;

        if(O_Water[0].m_WaterVolume > 0.1)
                {
                O_Water[0].O_PON.m_C += leaflitdecompc * 0.5;
                O_Water[0].O_PON.m_N += leaflitdecompn * 0.5;
                O_Water[0].O_PON.m_P += leaflitdecompp * 0.5;

                O_Water[0].O_DON.m_C += leaflitdecompc * 0.5;
                O_Water[0].O_DON.m_N += leaflitdecompn * 0.5;
                O_Water[0].O_DON.m_P += leaflitdecompp * 0.5;
                }
        else
                {
                O_Soil[0].O_SON.m_C += leaflitdecompc;
                O_Soil[0].O_SON.m_N += leaflitdecompn;
                O_Soil[0].O_SON.m_P += leaflitdecompp;
                }

        float bgdeaddecompc = 0.0;
        float bgdeaddecompn = 0.0;
        float bgdeaddecompp = 0.0;

        // Bead Belowground biomass decomposition
        // Xiaofeng change 1.05 to 1.5 on Oct 26, 2009
        float soiltemeffectbgdm = pow(1.5, exp((soilT - 10.0) / 10.0));

        bgdeaddecompc += soiltemeffectbgdm * O_Plant[p].O_DeadBG.m_C * plantpara[p].m_BGDeadDecom;
        O_Plant[p].O_DeadBG.m_C -= soiltemeffectbgdm * O_Plant[p].O_DeadBG.m_C * plantpara[p].m_BGDeadDecom;

        m_RH += bgdeaddecompc * 0.25;
        bgdeaddecompc -= bgdeaddecompc * 0.25;

        bgdeaddecompn += soiltemeffectbgdm * O_Plant[p].O_DeadBG.m_N *  plantpara[p].m_BGDeadDecom;
        O_Plant[p].O_DeadBG.m_N -= soiltemeffectbgdm * O_Plant[p].O_DeadBG.m_N *  plantpara[p].m_BGDeadDecom;

        bgdeaddecompp += soiltemeffectbgdm * O_Plant[p].O_DeadBG.m_P *  plantpara[p].m_BGDeadDecom;
        O_Plant[p].O_DeadBG.m_P -= soiltemeffectbgdm * O_Plant[p].O_DeadBG.m_P *  plantpara[p].m_BGDeadDecom;

        float totalpoc = O_Water[1].O_PON.m_C + O_Water[2].O_PON.m_C + O_Water[3].O_PON.m_C;
        float totalpon = O_Water[1].O_PON.m_N + O_Water[2].O_PON.m_N + O_Water[3].O_PON.m_N;
        float totalpop = O_Water[1].O_PON.m_P + O_Water[2].O_PON.m_P + O_Water[3].O_PON.m_P;

        for(int ll = 1; ll < 4; ll++)
        {
                O_Water[ll].O_PON.m_C += O_Water[ll].O_PON.m_C / totalpoc * bgdeaddecompc * 0.5;
                O_Water[ll].O_PON.m_N += O_Water[ll].O_PON.m_N / totalpon * bgdeaddecompn * 0.5;
                O_Water[ll].O_PON.m_P += O_Water[ll].O_PON.m_P / totalpop * bgdeaddecompp * 0.5;
        }
        float totaldoc = O_Water[1].O_DON.m_C + O_Water[2].O_DON.m_C + O_Water[3].O_DON.m_C;
        float totaldon = O_Water[1].O_DON.m_N + O_Water[2].O_DON.m_N + O_Water[3].O_DON.m_N;
        float totaldop = O_Water[1].O_DON.m_P + O_Water[2].O_DON.m_P + O_Water[3].O_DON.m_P;

        for(int lll = 1; lll < 4; lll++)
        {
                O_Water[lll].O_DON.m_C += O_Water[lll].O_DON.m_C / totaldoc * bgdeaddecompc * 0.5;
                O_Water[lll].O_DON.m_N += O_Water[lll].O_DON.m_N / totaldon * bgdeaddecompn * 0.5;
                O_Water[lll].O_DON.m_P += O_Water[lll].O_DON.m_P / totaldop * bgdeaddecompp * 0.5;
        }

        }
        // End of plant function


//cout<<"here3"<<endl;
        // Start of soil layer conversion between different status

for(int i = 0; i < 3; i++)
        {
        float somdecom;

        somdecom = O_Soil[i].O_LabSOM.m_C * soilpara.m_LabSOMK * maxdecfeedback;
        if((somdecom / 2.0) > (0.9 * O_Water[i+1].m_DO * 12.0 / 32.0 * m_SoilThick[i]))
                {
                somdecom = 2.0 * O_Water[i+1].m_DO * 0.9 * 12.0 / 32.0 * m_SoilThick[i];

                m_RH += O_Water[i+1].m_DO * 0.9 / 32.0 * 12.0 * m_SoilThick[i];

                O_Soil[i].O_SON.m_C += somdecom / 2.0;

                O_Soil[i].O_LabSOM.m_C -= somdecom;

                O_Soil[i].O_SON.m_N += somdecom / 2.0 / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_N;
                O_Water[i+1].O_DON.m_N += somdecom / 2.0 / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_N;
                O_Soil[i].O_LabSOM.m_N -= somdecom / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_N;

                O_Soil[i].O_SON.m_P += somdecom / 2.0 / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_P;
                O_Water[i+1].O_DON.m_P += somdecom / 2.0 / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_P;
                O_Soil[i].O_LabSOM.m_P -= somdecom / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_P;

                O_Water[i+1].m_DO *= 0.1;
                }
        else
                {
                m_RH += somdecom / 2.0;
                O_Soil[i].O_SON.m_C += somdecom / 2.0;
                O_Water[i+1].m_DO -= somdecom / 2.0;

                O_Soil[i].O_LabSOM.m_C -= somdecom;

                O_Soil[i].O_SON.m_N += somdecom / 2.0 / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_N;
                O_Water[i+1].O_DON.m_N += somdecom / 2.0 / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_N;
                O_Soil[i].O_LabSOM.m_N -= somdecom / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_N;

                O_Soil[i].O_SON.m_P += somdecom / 2.0 / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_P;
                O_Water[i+1].O_DON.m_P += somdecom / 2.0 / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_P;
                O_Soil[i].O_LabSOM.m_P -= somdecom / O_Soil[i].O_LabSOM.m_C * O_Soil[i].O_LabSOM.m_P;

                O_Water[i+1].m_DO -= somdecom / 2.0 / 12.0 * 32.0 * m_SoilThick[i];
                }


        somdecom = O_Soil[i].O_MidSOM.m_C * soilpara.m_MidSOMK * maxdecfeedback;
        if((somdecom / 2.0) > (0.9 * O_Water[i+1].m_DO * 12.0 / 32.0 * m_SoilThick[i]))
                {
                somdecom = 2.0 * O_Water[i+1].m_DO * 0.9 * 12.0 / 32.0 * m_SoilThick[i];

                m_RH += O_Water[i+1].m_DO * 0.9 / 32.0 * 12.0 * m_SoilThick[i];

                O_Soil[i].O_SON.m_C += somdecom / 2.0;

                O_Soil[i].O_LabSOM.m_C -= somdecom;

                O_Soil[i].O_SON.m_N += somdecom / 2.0 / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_N;
                O_Water[i+1].O_DON.m_N += somdecom / 2.0 / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_N;
                O_Soil[i].O_MidSOM.m_N -= somdecom / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_N;

                O_Soil[i].O_SON.m_P += somdecom / 2.0 / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_P;
                O_Water[i+1].O_DON.m_P += somdecom / 2.0 / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_P;
                O_Soil[i].O_MidSOM.m_P -= somdecom / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_P;

                O_Water[i+1].m_DO *= 0.1;
                }
        else
                {
                m_RH += somdecom / 2.0;
                O_Soil[i].O_SON.m_C += somdecom / 2.0;
                O_Water[i+1].m_DO -= somdecom / 2.0;


                O_Soil[i].O_SON.m_N += somdecom / 2.0 / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_N;
                O_Water[i+1].O_DON.m_N += somdecom / 2.0 / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_N;

                O_Soil[i].O_MidSOM.m_N -= somdecom / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_N;

                O_Soil[i].O_SON.m_P += somdecom / 2.0 / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_P;
                O_Water[i+1].O_DON.m_P += somdecom / 2.0 / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_P;

                O_Soil[i].O_MidSOM.m_P -= somdecom / O_Soil[i].O_MidSOM.m_C * O_Soil[i].O_MidSOM.m_P;

                O_Soil[i].O_MidSOM.m_C -= somdecom;

                O_Water[i+1].m_DO -= somdecom / 2.0 / 12.0 * 32.0 * m_SoilThick[i];
                }


        somdecom = O_Soil[i].O_ResSOM.m_C * soilpara.m_ResSOMK * maxdecfeedback;
        if((somdecom / 2.0) > (O_Water[i+1].m_DO * 0.9 * 12.0 / 32.0 * m_SoilThick[i]))
                {
                somdecom = 2.0 * O_Water[i+1].m_DO * 0.9 * 12.0 / 32.0 * m_SoilThick[i];

                m_RH += O_Water[i+1].m_DO * 0.9 / 32.0 * 12.0 * m_SoilThick[i];

                O_Soil[i].O_SON.m_C += somdecom / 2.0;

                O_Soil[i].O_ResSOM.m_C -= somdecom;

                O_Soil[i].O_SON.m_N += somdecom / 2.0 / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_N;
                O_Water[i+1].O_DON.m_N += somdecom / 2.0 / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_N;
                O_Soil[i].O_ResSOM.m_N -= somdecom / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_N;

                O_Soil[i].O_SON.m_P += somdecom / 2.0 / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_P;
                O_Water[i+1].O_DON.m_P += somdecom / 2.0 / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_P;
                O_Soil[i].O_ResSOM.m_P -= somdecom / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_P;

                O_Water[i+1].m_DO *= 0.1;
                }
        else
                {
                m_RH += somdecom / 2.0;
                O_Soil[i].O_SON.m_C += somdecom / 2.0;
                O_Water[i+1].m_DO -= somdecom / 2.0;


                O_Soil[i].O_SON.m_N += somdecom / 2.0 / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_N;
                O_Water[i+1].O_DON.m_N += somdecom / 2.0 / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_N;

                O_Soil[i].O_ResSOM.m_N -= somdecom / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_N;

                O_Soil[i].O_SON.m_P += somdecom / 2.0 / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_P;
                O_Water[i+1].O_DON.m_P += somdecom / 2.0 / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_P;

                O_Soil[i].O_ResSOM.m_P -= somdecom / O_Soil[i].O_ResSOM.m_C * O_Soil[i].O_ResSOM.m_P;

                O_Soil[i].O_ResSOM.m_C -= somdecom;

                O_Water[i+1].m_DO -= somdecom / 2.0 / 12.0 * 32.0 * m_SoilThick[i];
                }
        // End of decomposition of soil organic matter

        O_Soil[i].m_SINNH4 += O_Soil[i].O_SON.m_N * soilpara.m_SON_to_SIN * 0.5;
        O_Soil[i].m_SINNO3 += O_Soil[i].O_SON.m_N * soilpara.m_SON_to_SIN * 0.5;
        O_Soil[i].m_SINPO4 += O_Soil[i].O_SON.m_P * soilpara.m_SON_to_SIN;

        m_RH += O_Soil[i].O_SON.m_C * soilpara.m_SON_to_SIN;

        O_Soil[i].O_SON.m_C -= O_Soil[i].O_SON.m_C * soilpara.m_SON_to_SIN;
        O_Soil[i].O_SON.m_N -= O_Soil[i].O_SON.m_N * soilpara.m_SON_to_SIN;
        O_Soil[i].O_SON.m_P -= O_Soil[i].O_SON.m_P * soilpara.m_SON_to_SIN;


//  From SON to SOM

        O_Soil[i].O_LabSOM.m_C += O_Soil[i].O_SON.m_C * 0.0015;
        O_Soil[i].O_SON.m_C -= O_Soil[i].O_SON.m_C * 0.0015;

        O_Soil[i].O_LabSOM.m_N += O_Soil[i].O_SON.m_N * 0.0015;
        O_Soil[i].O_SON.m_N -= O_Soil[i].O_SON.m_N * 0.0015;

        O_Soil[i].O_LabSOM.m_P += O_Soil[i].O_SON.m_P * 0.0015;
        O_Soil[i].O_SON.m_P -= O_Soil[i].O_SON.m_P * 0.0015;

// End of conversion of SON to SOM

//  From lab som to mid SOM

        O_Soil[i].O_MidSOM.m_C += O_Soil[i].O_LabSOM.m_C * 0.0005;
        O_Soil[i].O_LabSOM.m_C -= O_Soil[i].O_LabSOM.m_C * 0.0005;

        O_Soil[i].O_MidSOM.m_N += O_Soil[i].O_LabSOM.m_N * 0.0005;
        O_Soil[i].O_LabSOM.m_N -= O_Soil[i].O_LabSOM.m_N * 0.0005;

        O_Soil[i].O_MidSOM.m_P += O_Soil[i].O_LabSOM.m_P * 0.0005;
        O_Soil[i].O_LabSOM.m_P -= O_Soil[i].O_LabSOM.m_P * 0.0005;

        O_Soil[i].O_MidSOM.m_N += O_Soil[i].m_SINNH4 * 0.5 * soilpara.m_SIN_to_SOM;
        O_Soil[i].O_MidSOM.m_N += O_Soil[i].m_SINNO3 * 0.5 * soilpara.m_SIN_to_SOM;
        O_Soil[i].O_MidSOM.m_P += O_Soil[i].m_SINPO4 * soilpara.m_SIN_to_SOM;

        O_Soil[i].m_SINNH4 -= O_Soil[i].m_SINNH4 * 0.5 * soilpara.m_SIN_to_SOM;
        O_Soil[i].m_SINNO3 -= O_Soil[i].m_SINNO3 * 0.5 * soilpara.m_SIN_to_SOM;
        O_Soil[i].m_SINPO4 -= O_Soil[i].m_SINPO4 * soilpara.m_SIN_to_SOM;

// End of conversion of lab SOM to mid SOM

//  From mid SON to res SOM
//                cout<<"OK12 "<<O_Soil[0].m_SINPO4<<endl;
        O_Soil[i].O_ResSOM.m_C += O_Soil[i].O_MidSOM.m_C * 0.0005;
        O_Soil[i].O_MidSOM.m_C -= O_Soil[i].O_MidSOM.m_C * 0.0005;

        O_Soil[i].O_ResSOM.m_N += O_Soil[i].O_MidSOM.m_N * 0.0005;
        O_Soil[i].O_MidSOM.m_N -= O_Soil[i].O_MidSOM.m_N * 0.0005;

        O_Soil[i].O_ResSOM.m_P += O_Soil[i].O_MidSOM.m_P * 0.0005;
        O_Soil[i].O_MidSOM.m_P -= O_Soil[i].O_MidSOM.m_P * 0.0005;

        O_Soil[i].O_ResSOM.m_N += O_Soil[i].m_SINNH4 * 0.5 * soilpara.m_SIN_to_SOM;
        O_Soil[i].O_ResSOM.m_N += O_Soil[i].m_SINNO3 * 0.5 * soilpara.m_SIN_to_SOM;
        O_Soil[i].O_ResSOM.m_P += O_Soil[i].m_SINPO4 * soilpara.m_SIN_to_SOM;

        O_Soil[i].m_SINNH4 -= O_Soil[i].m_SINNH4 * 0.5 * soilpara.m_SIN_to_SOM;
        O_Soil[i].m_SINNO3 -= O_Soil[i].m_SINNO3 * 0.5 * soilpara.m_SIN_to_SOM;
        O_Soil[i].m_SINPO4 -= O_Soil[i].m_SINPO4 * soilpara.m_SIN_to_SOM;
// End of conversion of mid SON to res SOM


        // For NH4 absorption and desorption
//cout<<"OK3 "<<O_Soil[i].m_SINNH4<<endl;
//cout<<endl<<i<<endl;
//if(O_Soil[i].m_SINNH4 < 0)    cout<<"before soil: "<<O_Soil[i].m_SINNH4<<endl;
//cout<<"before water: "<<O_Water[i+1].m_DNH4<<endl;
//cout<<"OK3 "<<endl;
//cout<<"here4"<<endl;
//                cout<<"OK12 "<<O_Soil[0].m_SINPO4<<endl;
if(O_Water[i+1].m_WaterVolume < 10e-5)  continue;
else
{
        if((O_Soil[i].m_AbsNH4 / m_SoilThick[i]) < soilpara.m_AbsMaxNH4)
        {
        float totalnh4, exchangenh4;
        float anh4, bnh4, cnh4, Ksnh4, Smaxnh4, deltnh4;
        Ksnh4 = soilpara.m_AbsKNH4;
        Smaxnh4 = soilpara.m_AbsMaxNH4;

        totalnh4 = O_Soil[i].m_AbsNH4 / (1.0 - O_Soil[i].m_SoilPoro) / m_SoilThick[i] + O_Water[i+1].m_DNH4 / O_Water[i+1].m_WaterVolume;
        float sumnh4 = O_Soil[i].m_AbsNH4 + O_Water[i+1].m_DNH4;
//cout<<"totalnh4 "<<totalnh4<<endl;
//        float temtotalnh4 = O_Soil[i].m_SINNH4 + O_Water[i+1].m_DNH4;

        anh4 = -1.0;
        bnh4 = totalnh4 + Ksnh4 + Smaxnh4;
        cnh4 = -Smaxnh4 * totalnh4;
//cout<<"bnh4 "<<bnh4<<endl;
        deltnh4 = pow(bnh4, 2) - 4.0 * anh4 * cnh4;

        if(deltnh4 > 0)
                exchangenh4 = (-bnh4 + sqrt(deltnh4)) / 2.0 /anh4;
        else
                {
                if(deltnh4 == 0)
                exchangenh4 = -bnh4 / 2.0 / anh4;
                else
                        {
                        exit(1);
                        }
                }
//cout<<exchangenh4<<endl;

        if(exchangenh4 < 1e-10)   exchangenh4 = 0.0;

        if(exchangenh4 <= (0.00001 * totalnh4))
        exchangenh4 = 0.00001 * totalnh4;

        if(exchangenh4 > (0.99999 * totalnh4))
        exchangenh4 = 0.99999 * totalnh4;

        float soilnh, waternh;
        soilnh = exchangenh4;
        waternh = totalnh4 - exchangenh4;

//cout<<"sumnh4 "<<sumnh4<<endl;

        if((soilnh - O_Soil[i].m_AbsNH4 / (1.0 - O_Soil[i].m_SoilPoro) / m_SoilThick[i]) <= 0)
                {
                O_Soil[i].m_AbsNH4 = exchangenh4 * (1.0 - O_Soil[i].m_SoilPoro) * m_SoilThick[i];
                O_Water[i+1].m_DNH4 = sumnh4 - O_Soil[i].m_AbsNH4;
                }
        else
                {
                O_Water[i+1].m_DNH4 = waternh * O_Water[i+1].m_WaterVolume;
                O_Soil[i].m_AbsNH4 = sumnh4 - O_Water[i+1].m_DNH4;
                }
        }

        if(O_Soil[i].m_AbsNH4 < 10e-10) O_Soil[i].m_AbsNH4 = 10e-10;
        if(O_Water[i+1].m_DNH4 < 10e-10) O_Water[i+1].m_DNH4 = 10e-10;

        // For NO3 absorption and desorption
        if(O_Soil[i].m_AbsNO3 / m_SoilThick[i] < soilpara.m_AbsMaxNO3)
        {
        float totalno3, exchangeno3;
        float ano3, bno3, cno3, Ksno3, Smaxno3, deltno3;
        Ksno3 = soilpara.m_AbsKNO3;
        Smaxno3 = soilpara.m_AbsMaxNO3;

        totalno3 = O_Soil[i].m_AbsNO3 / (1.0 - O_Soil[i].m_SoilPoro) / m_SoilThick[i] + O_Water[i+1].m_DNO3 / O_Water[i+1].m_WaterVolume;
        float sumno3 = O_Soil[i].m_AbsNO3 + O_Water[i+1].m_DNO3;

        ano3 = -1.0;
        bno3 = totalno3 + Ksno3 + Smaxno3;
        cno3 = -Smaxno3 * totalno3;
//cout<<"bno3 "<<bno3<<endl;
        deltno3 = pow(bno3, 2) - 4.0 * ano3 * cno3;

        if(deltno3 > 0)
                exchangeno3 = (-bno3 + sqrt(deltno3)) / 2.0 /ano3;
        else
                {
                if(deltno3 == 0)
                        exchangeno3 = -bno3 / 2.0 / ano3;
                else
                        {
                        exit(1);
                        }
                }

        if(exchangeno3 < 1e-10)   exchangeno3 = 0.0;

        if(exchangeno3 <= (0.00001 * totalno3))
        exchangeno3 = 0.00001 * totalno3;

        if(exchangeno3 > (0.99999 * totalno3))
        exchangeno3 = 0.99999 * totalno3;

        float soilno, waterno;
        soilno = exchangeno3;
        waterno = totalno3 - exchangeno3;
        if(soilno - O_Soil[i].m_AbsNO3 / (1.0 - O_Soil[i].m_SoilPoro) / m_SoilThick[i] <= 0)
                {
                O_Soil[i].m_AbsNO3 = exchangeno3 * (1.0 - O_Soil[i].m_SoilPoro) * m_SoilThick[i];
                O_Water[i+1].m_DNO3 = sumno3 - O_Soil[i].m_AbsNO3;
                }
        else
                {
                O_Water[i+1].m_DNO3 = waterno * O_Water[i+1].m_WaterVolume;
                O_Soil[i].m_AbsNO3 = sumno3 - O_Water[i+1].m_DNO3;
                }

        }

        if(O_Soil[i].m_AbsNO3 < 10e-10) O_Soil[i].m_AbsNO3 = 10e-10;
        if(O_Water[i+1].m_DNO3 < 10e-10) O_Water[i+1].m_DNO3 = 10e-10;
        // End of NO3 absorption and desorption


//cout<<"here5"<<endl;
//cout<<O_Soil[i].m_AbsPO4<<endl;
//cout<<m_SoilThick[i]<<endl;
//cout<<O_Soil[i].m_SoilPoro<<endl;
//cout<<O_Water[i+1].m_DPO4<<endl;
//                cout<<"OK12 "<<O_Soil[0].m_SINPO4<<endl;
        // For PO4 absorption and desorption
        if((O_Soil[i].m_AbsPO4 / m_SoilThick[i]) < soilpara.m_AbsMaxPO4)
        {
        float totalpo4, exchangepo4;
        float apo4, bpo4, cpo4, Kspo4, Smaxpo4, deltpo4;
        Kspo4 = soilpara.m_AbsKPO4;
        Smaxpo4 = soilpara.m_AbsMaxPO4;

        totalpo4 = O_Soil[i].m_AbsPO4 / m_SoilThick[i] / (1.0 - O_Soil[i].m_SoilPoro)+ O_Water[i+1].m_DPO4 / O_Water[i+1].m_WaterVolume;

        float sumpo4 = O_Soil[i].m_AbsPO4 + O_Water[i+1].m_DPO4;

        apo4 = -1.0;
        bpo4 = totalpo4 + Kspo4 + Smaxpo4;
        cpo4 = -Smaxpo4 * totalpo4;
//        cout<<"here1 "<<bpo4<<" "<<totalpo4<<" "<<Kspo4<<" "<<Smaxpo4;
        deltpo4 = pow(bpo4, 2) - 4.0 * apo4 * cpo4;
//        cout<<"here2 "<<bpo4<<" "<<totalpo4<<" "<<Kspo4<<" "<<Smaxpo4;
        if(deltpo4 > 0)
                exchangepo4 = (-bpo4 + sqrt(deltpo4)) / 2.0 /apo4;
        else
                {
                if(deltpo4 == 0)
                        exchangepo4 = -bpo4 / 2.0 / apo4;
                else
                        {
                        exit(1);
                        }
                }

        if(exchangepo4 < 1e-10)   exchangepo4 = 0.0;

        if(exchangepo4 <= (0.00001 * totalpo4))
        exchangepo4 = 0.00001 * totalpo4;

        if(exchangepo4 > (0.99999 * totalpo4))
        exchangepo4 = 0.99999 * totalpo4;

        float soilpo, waterpo;
        soilpo = exchangepo4;
        waterpo = totalpo4 - exchangepo4;
        if(soilpo - O_Soil[i].m_AbsPO4 / m_SoilThick[i] / (1.0 - O_Soil[i].m_SoilPoro) <= 0)
                {
                O_Soil[i].m_AbsPO4 = exchangepo4 * (1.0 - O_Soil[i].m_SoilPoro) * m_SoilThick[i];
                O_Water[i+1].m_DPO4 = sumpo4 - O_Soil[i].m_AbsPO4;
                }
        else
                {
                O_Water[i+1].m_DPO4 = waterpo * O_Water[i+1].m_WaterVolume;
                O_Soil[i].m_AbsPO4 = sumpo4 - O_Water[i+1].m_DPO4;
                }
        }

        if(O_Soil[i].m_AbsPO4 < 10e-10) O_Soil[i].m_AbsPO4 = 10e-10;
        if(O_Water[i+1].m_DPO4 < 10e-10) O_Water[i+1].m_DPO4 = 10e-10;
//                cout<<"OK12 "<<O_Soil[0].m_SINPO4<<endl;
//cout<<"here6"<<endl;
//cout<<O_Soil[i].m_AbsPO4<<endl;
//cout<<m_SoilThick[i]<<endl;
//cout<<O_Soil[i].m_SoilPoro<<endl;
//cout<<O_Water[i+1].m_DPO4<<endl;
//cout<<O_Water[i+1].m_WaterVolume<<endl;
//cout<<"3: "<<O_Water[i+1].m_DPO4<<endl;
        // End of PO4 absorption and desorption

//cout<<"here6"<<endl;
// Equilibrium between absored Nutrient and sin nutrient
//cout<<"OK12 "<<O_Soil[i].m_SINNH4<<endl;

if(O_Soil[i].m_SINNH4 < soilpara.m_MaxNH4)
{
float a_sin_nh = pow((soilpara.m_MaxNH4 - O_Soil[i].m_SINNH4) / soilpara.m_MaxNH4, float(4.0)) * O_Soil[i].m_AbsNH4;

O_Soil[i].m_SINNH4 += a_sin_nh;
O_Soil[i].m_AbsNH4 -= a_sin_nh;
}
else
{
O_Soil[i].m_AbsNH4 += (O_Soil[i].m_SINNH4 - soilpara.m_MaxNH4);
O_Soil[i].m_SINNH4 = soilpara.m_MaxNH4;
}
O_Soil[i].m_AbsNH4 += O_Soil[i].m_SINNH4 * soilpara.m_AbsToSINNH4;
O_Soil[i].m_SINNH4 -= O_Soil[i].m_SINNH4 * soilpara.m_AbsToSINNH4;


if(O_Soil[i].m_SINNO3 < soilpara.m_MaxNO3)
{
float a_sin_no = pow((soilpara.m_MaxNO3 - O_Soil[i].m_SINNO3) / soilpara.m_MaxNO3, float(4.0)) * O_Soil[i].m_AbsNO3;

O_Soil[i].m_SINNO3 += a_sin_no;
O_Soil[i].m_AbsNO3 -= a_sin_no;
}
else
{
O_Soil[i].m_AbsNO3 += (O_Soil[i].m_SINNO3 - soilpara.m_MaxNO3);
O_Soil[i].m_SINNO3 = soilpara.m_MaxNO3;
}
O_Soil[i].m_AbsNO3 += O_Soil[i].m_SINNO3 * soilpara.m_AbsToSINNO3;
O_Soil[i].m_SINNO3 -= O_Soil[i].m_SINNO3 * soilpara.m_AbsToSINNO3;

//                cout<<"OK13 "<<O_Soil[0].m_SINPO4<<endl;
if(O_Soil[i].m_SINPO4 < soilpara.m_MaxPO4)
{
float a_sin_po = pow((soilpara.m_MaxPO4 - O_Soil[i].m_SINPO4) / soilpara.m_MaxPO4, float(4.0)) * O_Soil[i].m_AbsPO4;

O_Soil[i].m_SINPO4 += a_sin_po;
O_Soil[i].m_AbsPO4 -= a_sin_po;
}
else
{
O_Soil[i].m_AbsPO4 += (O_Soil[i].m_SINPO4 - soilpara.m_MaxPO4);
O_Soil[i].m_SINPO4 = soilpara.m_MaxPO4;
}

O_Soil[i].m_AbsPO4 += O_Soil[i].m_SINPO4 * soilpara.m_AbsToSINPO4;
O_Soil[i].m_SINPO4 -= O_Soil[i].m_SINPO4 * soilpara.m_AbsToSINPO4;

}
// End of the if else
//cout<<"OK13 "<<O_Soil[i].m_SINNH4<<endl;
        // From DON to SON
        O_Soil[0].O_SON.m_C += O_Water[0].O_DON.m_C * O_WaterPara.m_DONdec * O_WaterPara.m_DON_to_SON;
        m_RH += O_Water[0].O_DON.m_C * O_WaterPara.m_DONdec * (1.0 - O_WaterPara.m_DON_to_SON);
        O_Water[0].O_DON.m_C -= O_Water[0].O_DON.m_C * O_WaterPara.m_DONdec;

        O_Soil[0].O_SON.m_N += O_Water[0].O_DON.m_N * O_WaterPara.m_DONdec * O_WaterPara.m_DON_to_SON;
        O_Water[0].m_DNH4 += O_Water[0].O_DON.m_N * O_WaterPara.m_DONdec * (1.0 - O_WaterPara.m_DON_to_SON) / 2.0;
        O_Water[0].m_DNO3 += O_Water[0].O_DON.m_N * O_WaterPara.m_DONdec * (1.0 - O_WaterPara.m_DON_to_SON) / 2.0;
        O_Water[0].O_DON.m_N -= O_Water[0].O_DON.m_N * O_WaterPara.m_DONdec;

        O_Soil[0].O_SON.m_P += O_Water[0].O_DON.m_P * O_WaterPara.m_DONdec * O_WaterPara.m_DON_to_SON;
        O_Water[0].m_DPO4 += O_Water[0].O_DON.m_P * O_WaterPara.m_DONdec * (1.0 - O_WaterPara.m_DON_to_SON);
        O_Water[0].O_DON.m_P -= O_Water[0].O_DON.m_P * O_WaterPara.m_DONdec;
        // End of converion from DON to SON

        // From PON to DON
        O_Water[0].O_DON.m_C += O_Water[0].O_PON.m_C * O_WaterPara.m_PON_to_DON * O_WaterPara.m_PONdec;
        m_RH += O_Water[0].O_PON.m_C * (1.0 - O_WaterPara.m_PON_to_DON) * O_WaterPara.m_PONdec;
        O_Water[0].O_PON.m_C -= O_Water[0].O_PON.m_C * O_WaterPara.m_PONdec;

        O_Water[0].O_DON.m_N += O_Water[0].O_PON.m_N * O_WaterPara.m_PONdec * O_WaterPara.m_PON_to_DON;
        O_Water[0].m_DNH4 += O_Water[0].O_PON.m_N * O_WaterPara.m_PONdec * (1.0 - O_WaterPara.m_PON_to_DON) / 2.0;
        O_Water[0].m_DNO3 += O_Water[0].O_PON.m_N * O_WaterPara.m_PONdec * (1.0 - O_WaterPara.m_PON_to_DON) / 2.0;
        O_Water[0].O_PON.m_N -= O_Water[0].O_PON.m_N * O_WaterPara.m_PONdec;

        O_Water[0].O_DON.m_P += O_Water[0].O_PON.m_P * O_WaterPara.m_PONdec * O_WaterPara.m_PON_to_DON;
        O_Water[0].m_DPO4 += O_Water[0].O_PON.m_P * O_WaterPara.m_PONdec * (1.0 - O_WaterPara.m_PON_to_DON);
        O_Water[0].O_PON.m_P -= O_Water[0].O_PON.m_P * O_WaterPara.m_PONdec;
        // End of PON to DON
//                cout<<"OK14 "<<O_Soil[0].m_SINPO4<<endl;
for(int i = 1; i < 3; i++)
        {
        // From DON to SON
        O_Soil[i-1].O_SON.m_C += O_Water[i].O_DON.m_C * O_WaterPara.m_DONdec * O_WaterPara.m_DON_to_SON * O_WaterPara.m_PToSDecom * storepondec;
        m_RH += O_Water[i].O_DON.m_C * O_WaterPara.m_DONdec * (1.0 - O_WaterPara.m_DON_to_SON) * O_WaterPara.m_PToSDecom * storepondec;
        O_Water[i].O_DON.m_C -= O_Water[i].O_DON.m_C * O_WaterPara.m_DONdec * O_WaterPara.m_PToSDecom * storepondec;

        O_Soil[i-1].O_SON.m_N += O_Water[i].O_DON.m_N * O_WaterPara.m_DONdec * O_WaterPara.m_DON_to_SON * O_WaterPara.m_PToSDecom * storepondec;
        O_Water[i].m_DNH4 += O_Water[i].O_DON.m_N * O_WaterPara.m_DONdec * (1.0 - O_WaterPara.m_DON_to_SON) / 2.0 * O_WaterPara.m_PToSDecom * storepondec;
        O_Water[i].m_DNO3 += O_Water[i].O_DON.m_N * O_WaterPara.m_DONdec * (1.0 - O_WaterPara.m_DON_to_SON) / 2.0 * O_WaterPara.m_PToSDecom * storepondec;
        O_Water[i].O_DON.m_N -= O_Water[i].O_DON.m_N * O_WaterPara.m_DONdec * O_WaterPara.m_PToSDecom * storepondec;

        O_Soil[i-1].O_SON.m_P += O_Water[i].O_DON.m_P * O_WaterPara.m_DONdec * O_WaterPara.m_DON_to_SON * O_WaterPara.m_PToSDecom * storepondec;
        O_Water[i].m_DPO4 += O_Water[i].O_DON.m_P * O_WaterPara.m_DONdec * (1.0 - O_WaterPara.m_DON_to_SON) * O_WaterPara.m_PToSDecom * storepondec;
        O_Water[i].O_DON.m_P -= O_Water[i].O_DON.m_P * O_WaterPara.m_DONdec * O_WaterPara.m_PToSDecom * storepondec;
        // End of converion from DON to SON

        // From PON to DON
        O_Water[i].O_DON.m_C += O_Water[i].O_PON.m_C * O_WaterPara.m_PON_to_DON * O_WaterPara.m_PONdec * O_WaterPara.m_PToSDecom * pondec * storepondec;
        m_RH += O_Water[i].O_PON.m_C * (1.0 - O_WaterPara.m_PON_to_DON) * O_WaterPara.m_PONdec * O_WaterPara.m_PToSDecom * pondec * storepondec;
        O_Water[i].O_PON.m_C -= O_Water[i].O_PON.m_C * O_WaterPara.m_PONdec * O_WaterPara.m_PToSDecom * pondec * storepondec;

        O_Water[i].O_DON.m_N += O_Water[i].O_PON.m_N * O_WaterPara.m_PONdec * O_WaterPara.m_PON_to_DON * O_WaterPara.m_PToSDecom * pondec * storepondec;
        O_Water[i].m_DNH4 += O_Water[i].O_PON.m_N * O_WaterPara.m_PONdec * (1.0 - O_WaterPara.m_PON_to_DON) / 2.0 * O_WaterPara.m_PToSDecom * pondec * storepondec;
        O_Water[i].m_DNO3 += O_Water[i].O_PON.m_N * O_WaterPara.m_PONdec * (1.0 - O_WaterPara.m_PON_to_DON) / 2.0 * O_WaterPara.m_PToSDecom * pondec * storepondec;
        O_Water[i].O_PON.m_N -= O_Water[i].O_PON.m_N * O_WaterPara.m_PONdec * O_WaterPara.m_PToSDecom * pondec * storepondec;

        O_Water[i].O_DON.m_P += O_Water[i].O_PON.m_P * O_WaterPara.m_PONdec * O_WaterPara.m_PON_to_DON * O_WaterPara.m_PToSDecom * pondec * storepondec;
        O_Water[i].m_DPO4 += O_Water[i].O_PON.m_P * O_WaterPara.m_PONdec * (1.0 - O_WaterPara.m_PON_to_DON) * O_WaterPara.m_PToSDecom * pondec * storepondec;
        O_Water[i].O_PON.m_P -= O_Water[i].O_PON.m_P * O_WaterPara.m_PONdec * O_WaterPara.m_PToSDecom * pondec * storepondec;
        // End of PON to DON
        }

        O_Soil[i].O_ResSOM.m_C -= O_Soil[i].O_ResSOM.m_C * soilpara.m_ResSOMK / 2.0;
        O_Soil[i].O_ResSOM.m_N -= O_Soil[i].O_ResSOM.m_N * soilpara.m_ResSOMK / 2.0;
        O_Soil[i].O_ResSOM.m_P -= O_Soil[i].O_ResSOM.m_P * soilpara.m_ResSOMK / 2.0;


        O_Soil[i].O_ResSOM.m_C += O_Soil[i].O_MidSOM.m_C * soilpara.m_MidSOMK / 2.0;
        O_Soil[i].O_ResSOM.m_N += O_Soil[i].O_MidSOM.m_N * soilpara.m_MidSOMK / 2.0;
        O_Soil[i].O_ResSOM.m_P += O_Soil[i].O_MidSOM.m_P * soilpara.m_MidSOMK / 2.0;

        O_Soil[i].O_MidSOM.m_C -= O_Soil[i].O_MidSOM.m_C * soilpara.m_MidSOMK / 2.0;
        O_Soil[i].O_MidSOM.m_N -= O_Soil[i].O_MidSOM.m_N * soilpara.m_MidSOMK / 2.0;
        O_Soil[i].O_MidSOM.m_P -= O_Soil[i].O_MidSOM.m_P * soilpara.m_MidSOMK / 2.0;


        O_Soil[i].O_MidSOM.m_C += O_Soil[i].O_LabSOM.m_C * soilpara.m_LabSOMK / 2.0;
        O_Soil[i].O_MidSOM.m_N += O_Soil[i].O_LabSOM.m_N * soilpara.m_LabSOMK / 2.0;
        O_Soil[i].O_MidSOM.m_P += O_Soil[i].O_LabSOM.m_P * soilpara.m_LabSOMK / 2.0;

        O_Soil[i].O_LabSOM.m_C -= O_Soil[i].O_LabSOM.m_C * soilpara.m_LabSOMK / 2.0;
        O_Soil[i].O_LabSOM.m_N -= O_Soil[i].O_LabSOM.m_N * soilpara.m_LabSOMK / 2.0;
        O_Soil[i].O_LabSOM.m_P -= O_Soil[i].O_LabSOM.m_P * soilpara.m_LabSOMK / 2.0;
        }
        // End of nutrient cycling in every soil layer

//                        cout<<"OK15 "<<O_Soil[0].m_SINPO4<<endl;
//Xiaofeng Change the following 6 lines code to others
/*
        O_Soil[0].O_SON.m_C += O_Water[0].O_PON.m_C * waterpara.m_PrecRate;
        O_Soil[0].O_SON.m_N += O_Water[0].O_PON.m_N * waterpara.m_PrecRate;
        O_Soil[0].O_SON.m_P += O_Water[0].O_PON.m_P * waterpara.m_PrecRate;

        O_Water[0].O_PON.m_C -= O_Water[0].O_PON.m_C * waterpara.m_PrecRate;
        O_Water[0].O_PON.m_N -= O_Water[0].O_PON.m_N * waterpara.m_PrecRate;
        O_Water[0].O_PON.m_P -= O_Water[0].O_PON.m_P * waterpara.m_PrecRate;
*/

        O_Water[1].O_PON.m_C += O_Water[0].O_PON.m_C * waterpara.m_PrecRate * precipitation;
        O_Water[1].O_PON.m_N += O_Water[0].O_PON.m_N * waterpara.m_PrecRate * precipitation;
        O_Water[1].O_PON.m_P += O_Water[0].O_PON.m_P * waterpara.m_PrecRate * precipitation;

        O_Water[0].O_PON.m_C -= O_Water[0].O_PON.m_C * waterpara.m_PrecRate * precipitation;
        O_Water[0].O_PON.m_N -= O_Water[0].O_PON.m_N * waterpara.m_PrecRate * precipitation;
        O_Water[0].O_PON.m_P -= O_Water[0].O_PON.m_P * waterpara.m_PrecRate * precipitation;

        O_Water[2].O_PON.m_C += O_Water[1].O_PON.m_C * waterpara.m_PrecRate * precipitation;
        O_Water[2].O_PON.m_N += O_Water[1].O_PON.m_N * waterpara.m_PrecRate * precipitation;
        O_Water[2].O_PON.m_P += O_Water[1].O_PON.m_P * waterpara.m_PrecRate * precipitation;

        O_Water[1].O_PON.m_C -= O_Water[1].O_PON.m_C * waterpara.m_PrecRate * precipitation;
        O_Water[1].O_PON.m_N -= O_Water[1].O_PON.m_N * waterpara.m_PrecRate * precipitation;
        O_Water[1].O_PON.m_P -= O_Water[1].O_PON.m_P * waterpara.m_PrecRate * precipitation;

        O_Water[3].O_PON.m_C += O_Water[2].O_PON.m_C * waterpara.m_PrecRate * precipitation;
        O_Water[3].O_PON.m_N += O_Water[2].O_PON.m_N * waterpara.m_PrecRate * precipitation;
        O_Water[3].O_PON.m_P += O_Water[2].O_PON.m_P * waterpara.m_PrecRate * precipitation;

        O_Water[2].O_PON.m_C -= O_Water[2].O_PON.m_C * waterpara.m_PrecRate * precipitation;
        O_Water[2].O_PON.m_N -= O_Water[2].O_PON.m_N * waterpara.m_PrecRate * precipitation;
        O_Water[2].O_PON.m_P -= O_Water[2].O_PON.m_P * waterpara.m_PrecRate * precipitation;

        O_Soil[0].O_SON.m_C += O_Water[3].O_PON.m_C * waterpara.m_PrecRate * precipitation;
        O_Soil[0].O_SON.m_N += O_Water[3].O_PON.m_N * waterpara.m_PrecRate * precipitation;
        O_Soil[0].O_SON.m_P += O_Water[3].O_PON.m_P * waterpara.m_PrecRate * precipitation;

        O_Water[3].O_PON.m_C -= O_Water[3].O_PON.m_C * waterpara.m_PrecRate * precipitation;
        O_Water[3].O_PON.m_N -= O_Water[3].O_PON.m_N * waterpara.m_PrecRate * precipitation;
        O_Water[3].O_PON.m_P -= O_Water[3].O_PON.m_P * waterpara.m_PrecRate * precipitation;

        //O_Plant

//cout<<"here7"<<endl;
//cout<<"OK15 "<<O_Soil[0].m_SINNH4<<endl;
for(int teml = 0; teml < 3; teml++)
        {
        if(O_Soil[teml].O_SON.m_C < 1e-10) O_Soil[teml].O_SON.m_C = 1e-10;
        if(O_Soil[teml].O_SON.m_N < 1e-10) O_Soil[teml].O_SON.m_N = 1e-10;
        if(O_Soil[teml].O_SON.m_P < 1e-10) O_Soil[teml].O_SON.m_P = 1e-10;

        if(O_Soil[teml].m_SINNH4 < 1e-10) O_Soil[teml].m_SINNH4 = 1e-10;
        if(O_Soil[teml].m_SINNO3< 1e-10) O_Soil[teml].m_SINNO3 = 1e-10;
        if(O_Soil[teml].m_SINPO4 < 1e-10) O_Soil[teml].m_SINPO4 = 1e-10;
        }
//cout<<"OK16 "<<O_Soil[0].m_SINPO4<<endl;
for(int i = 0; i < 3;i ++)
        {
        O_Soil[i].m_SOMupdate(O_SoilPara);
        }
//cout<<"OK16 "<<O_Soil[0].m_SINPO4<<endl;
}
// End of soil biogeochemical function


void WEMecosystem::m_SoilWaterT()
{
for(int i = 1; i < (3 + 1); i++)
        {
        if(O_Soil[i - 1].m_SoilT > 40)  O_Soil[i - 1].m_SoilT = 40;
        if(O_Soil[i - 1].m_SoilT <-10)  O_Soil[i - 1].m_SoilT = -10;

        O_Water[i].m_WaterT = O_Soil[i - 1].m_SoilT;
        }
}

void WEMecosystem::m_Periphyton(float par)
{

float cperi = O_Periphyton.m_C;

float tp;
if(O_Water[0].m_WaterVolume < 0.05)     tp = 0.0;
else tp = 1000.0 * (O_Water[0].O_DON.m_P + O_Water[0].m_DPO4) / (O_Water[0].m_WaterVolume);

m_ARperi = 0.0;
m_NPPperi = 0.0;

if(par < 50)    par = 0.0;
else    par -= 50.0;

m_GPPperi = cperi * m_Pmax * pow(m_Arrcons, (O_Water[0].m_WaterT - m_Tref)) * (par / (m_Ik + par) * tp / (tp + m_Ktp)) * (1 - cperi / m_Cmax);

m_ARperi += cperi * m_Kr;

O_Periphyton.m_C -= cperi * m_Kr;
m_ARperi += m_GPPperi * m_Fresp;
m_ARperi += cperi * m_Km;
O_Periphyton.m_C -= cperi * m_Km;

m_NPPperi = m_GPPperi - m_ARperi;

O_Periphyton.m_C += m_NPPperi;

if(O_Periphyton.m_C < 0.0)      O_Periphyton.m_C = 0.0;

float perin, perip, tem;
perin = O_Periphyton.m_N;
if(perin > O_Periphyton.m_C / m_CNratioperi)
        {
        O_Periphyton.m_N = O_Periphyton.m_C / m_CNratioperi;
        tem = perin - O_Periphyton.m_N;
        O_Water[0].O_PON.m_N += tem;
        }
if(perin < O_Periphyton.m_C / m_CNratioperi)
        {
        O_Periphyton.m_N = O_Periphyton.m_C / m_CNratioperi;
        tem = O_Periphyton.m_N - perin;
        if(O_Water[0].O_PON.m_N > tem)
                {
                O_Water[0].O_PON.m_N -= tem;
                }
        else
                {
                O_Water[0].O_PON.m_N = 0.0;
                O_Periphyton.m_N += O_Water[0].O_PON.m_N;
                }
        }

perip = O_Periphyton.m_P;
if(perip > O_Periphyton.m_C / m_CPratioperi)
        {
        O_Periphyton.m_P = O_Periphyton.m_C / m_CPratioperi;
        tem = perip - O_Periphyton.m_P;
        O_Water[0].O_PON.m_P += tem;
        }
if(perip < O_Periphyton.m_C / m_CPratioperi)
        {
        O_Periphyton.m_P = O_Periphyton.m_C / m_CPratioperi;
        tem = O_Periphyton.m_P - perip;
        if(O_Water[0].O_PON.m_P > tem)
                {
                O_Water[0].O_PON.m_P -= tem;
                }
        else
                {
                O_Water[0].O_PON.m_P = 0.0;
                O_Periphyton.m_P += O_Water[0].O_PON.m_P;
                }
        }

if(O_Periphyton.m_C > 0.01)
        {
        O_Floc.m_C += O_Periphyton.m_C * m_Fprel;
        O_Floc.m_N += O_Periphyton.m_N * m_Fprel;
        O_Floc.m_P += O_Periphyton.m_P * m_Fprel;
        }
else
        {
        if(O_Water[0].m_WaterVolume > 0.05)
        O_Periphyton.m_C = 0.01;
        else    O_Periphyton.m_C = 0.0;
        }

}

void WEMecosystem::m_FlocUpdate()
{
O_Floc.m_C += O_Plant[0].O_Litter.m_C * O_PlantPara[0].m_LitToFloc;
O_Plant[0].O_Litter.m_C -= O_Plant[0].O_Litter.m_C * O_PlantPara[0].m_LitToFloc;

O_Floc.m_C += O_Plant[1].O_Litter.m_C * O_PlantPara[1].m_LitToFloc;
O_Plant[1].O_Litter.m_C -= O_Plant[1].O_Litter.m_C * O_PlantPara[1].m_LitToFloc;

O_Soil[0].O_LabSOM.m_C += O_Floc.m_C * m_FlocToSOM;
O_Floc.m_C -= O_Floc.m_C * m_FlocToSOM;
O_Soil[0].O_LabSOM.m_N += O_Floc.m_N * m_FlocToSOM;
O_Floc.m_N -= O_Floc.m_N * m_FlocToSOM;
O_Soil[0].O_LabSOM.m_P += O_Floc.m_P * m_FlocToSOM;
O_Floc.m_P -= O_Floc.m_P * m_FlocToSOM;


/* Xiaofeng blocked the followng codes on June 2, 2009
O_Floc.m_C += O_Soil[0].O_LabSOM.m_C * m_FlocToSOM;
O_Soil[0].O_LabSOM.m_C -= O_Soil[0].O_LabSOM.m_C * m_SOMToFloc;
O_Floc.m_N += O_Soil[0].O_LabSOM.m_N * m_FlocToSOM;
O_Soil[0].O_LabSOM.m_N -= O_Soil[0].O_LabSOM.m_N * m_SOMToFloc;
O_Floc.m_P += O_Soil[0].O_LabSOM.m_P * m_FlocToSOM;
O_Soil[0].O_LabSOM.m_P -= O_Soil[0].O_LabSOM.m_P * m_SOMToFloc;
*/

m_RH += O_Floc.m_C * m_FlocDec;
O_Soil[0].m_SINNH4 += O_Floc.m_N * m_FlocDec / 2.0;
O_Soil[0].m_SINNO3 += O_Floc.m_N * m_FlocDec / 2.0;
O_Soil[0].m_SINPO4 += O_Floc.m_P * m_FlocDec;
O_Floc.m_C -= O_Floc.m_C * m_FlocDec;
O_Floc.m_N -= O_Floc.m_N * m_FlocDec;
O_Floc.m_P -= O_Floc.m_P * m_FlocDec;

if(O_Floc.m_C < 0)      O_Floc.m_C = 0.0;
if(O_Floc.m_N < 0)      O_Floc.m_N = 0.0;
if(O_Floc.m_P < 0)      O_Floc.m_P = 0.0;
}

void WEMecosystem::m_SoilWaterUpdate(int day)
{
//cout<<"here3 "<<O_Water[0].m_WaterVolume<<endl;

for(int hour = 0; hour < 144; hour++)
        {

        float flux1, flux2, flux3;
        if(O_Water[0].m_WaterVolume <= 10e-10)  flux1 = 0.0;
        else        flux1 = O_WaterPara.m_DNHDiffusion * O_Water[0].m_WaterVolume * (O_Water[0].m_DNH4 / O_Water[0].m_WaterVolume - O_Water[1].m_DNH4 / O_Water[1].m_WaterVolume);

        flux2 = O_WaterPara.m_DNHDiffusion * O_Water[1].m_WaterVolume * (O_Water[1].m_DNH4 / O_Water[1].m_WaterVolume - O_Water[2].m_DNH4 / O_Water[2].m_WaterVolume);
        flux3 = O_WaterPara.m_DNHDiffusion * O_Water[2].m_WaterVolume * (O_Water[2].m_DNH4 / O_Water[2].m_WaterVolume - O_Water[3].m_DNH4 / O_Water[3].m_WaterVolume);

        if(flux1 > (O_Water[0].m_DNH4 * 0.5))   flux1 = (O_Water[0].m_DNH4 * 0.5);
        if(flux2 > (O_Water[1].m_DNH4 * 0.5))   flux2 = (O_Water[1].m_DNH4 * 0.5);
        if(flux3 > (O_Water[2].m_DNH4 * 0.5))   flux3 = (O_Water[2].m_DNH4 * 0.5);

        O_Water[0].m_DNH4 -= flux1;
        O_Water[1].m_DNH4 -= flux2;
        O_Water[2].m_DNH4 -= flux3;
        O_Water[1].m_DNH4 += flux1;
        O_Water[2].m_DNH4 += flux2;
        O_Water[3].m_DNH4 += flux3;

        if(O_Water[0].m_WaterVolume <= 10e-10)  flux1 = 0.0;
        else        flux1 = O_WaterPara.m_DNODiffusion * O_Water[0].m_WaterVolume * (O_Water[0].m_DNO3 / O_Water[0].m_WaterVolume - O_Water[1].m_DNO3 / O_Water[1].m_WaterVolume);
        flux2 = O_WaterPara.m_DNODiffusion * O_Water[1].m_WaterVolume * (O_Water[1].m_DNO3 / O_Water[1].m_WaterVolume - O_Water[2].m_DNO3 / O_Water[2].m_WaterVolume);
        flux3 = O_WaterPara.m_DNODiffusion * O_Water[2].m_WaterVolume * (O_Water[2].m_DNO3 / O_Water[2].m_WaterVolume - O_Water[3].m_DNO3 / O_Water[3].m_WaterVolume);

        if(flux1 > (O_Water[0].m_DNO3 * 0.5))   flux1 = (O_Water[0].m_DNO3 * 0.5);
        if(flux2 > (O_Water[1].m_DNO3 * 0.5))   flux2 = (O_Water[1].m_DNO3 * 0.5);
        if(flux3 > (O_Water[2].m_DNO3 * 0.5))   flux3 = (O_Water[2].m_DNO3 * 0.5);

        O_Water[0].m_DNO3 -= flux1;
        O_Water[1].m_DNO3 -= flux2;
        O_Water[2].m_DNO3 -= flux3;
        O_Water[1].m_DNO3 += flux1;
        O_Water[2].m_DNO3 += flux2;
        O_Water[3].m_DNO3 += flux3;

        if(O_Water[0].m_WaterVolume <= 10e-10)  flux1 = 0.0;
        else        flux1 = O_WaterPara.m_DPODiffusion * O_Water[0].m_WaterVolume * (O_Water[0].m_DPO4 / O_Water[0].m_WaterVolume - O_Water[1].m_DPO4 / O_Water[1].m_WaterVolume);
        flux2 = O_WaterPara.m_DPODiffusion * O_Water[1].m_WaterVolume * (O_Water[1].m_DPO4 / O_Water[1].m_WaterVolume - O_Water[2].m_DPO4 / O_Water[2].m_WaterVolume);
        flux3 = O_WaterPara.m_DPODiffusion * O_Water[2].m_WaterVolume * (O_Water[2].m_DPO4 / O_Water[2].m_WaterVolume - O_Water[3].m_DPO4 / O_Water[3].m_WaterVolume);

        if(flux1 > (O_Water[0].m_DPO4 * 0.5))   flux1 = (O_Water[0].m_DPO4 * 0.5);
        if(flux2 > (O_Water[1].m_DPO4 * 0.5))   flux2 = (O_Water[1].m_DPO4 * 0.5);
        if(flux3 > (O_Water[2].m_DPO4 * 0.5))   flux3 = (O_Water[2].m_DPO4 * 0.5);

        O_Water[0].m_DPO4 -= flux1;
        O_Water[1].m_DPO4 -= flux2;
        O_Water[2].m_DPO4 -= flux3;
        O_Water[1].m_DPO4 += flux1;
        O_Water[2].m_DPO4 += flux2;
        O_Water[3].m_DPO4 += flux3;

        if(O_Water[0].m_WaterVolume <= 10e-10)  flux1 = 0.0;
        else        flux1 = O_WaterPara.m_DOCDiffusion * O_Water[0].m_WaterVolume * (O_Water[0].O_DON.m_C / O_Water[0].m_WaterVolume - O_Water[1].O_DON.m_C / O_Water[1].m_WaterVolume);
        flux2 = O_WaterPara.m_DOCDiffusion * O_Water[1].m_WaterVolume * (O_Water[1].O_DON.m_C / O_Water[1].m_WaterVolume - O_Water[2].O_DON.m_C / O_Water[2].m_WaterVolume);
        flux3 = O_WaterPara.m_DOCDiffusion * O_Water[2].m_WaterVolume * (O_Water[2].O_DON.m_C / O_Water[2].m_WaterVolume - O_Water[3].O_DON.m_C / O_Water[3].m_WaterVolume);

        if(flux1 > (O_Water[0].O_DON.m_C * 0.5))   flux1 = (O_Water[0].O_DON.m_C * 0.5);
        if(flux2 > (O_Water[1].O_DON.m_C * 0.5))   flux2 = (O_Water[1].O_DON.m_C * 0.5);
        if(flux3 > (O_Water[2].O_DON.m_C * 0.5))   flux3 = (O_Water[2].O_DON.m_C * 0.5);

        if(flux1 < 0.) flux1 = 0;

        O_Water[0].O_DON.m_C -= flux1;
        O_Water[1].O_DON.m_C -= flux2;
        O_Water[2].O_DON.m_C -= flux3;
        O_Water[1].O_DON.m_C += flux1;
        O_Water[2].O_DON.m_C += flux2;
        O_Water[3].O_DON.m_C += flux3;

        if(O_Water[0].m_WaterVolume <= 10e-10)  flux1 = 0.0;
        else        flux1 = O_WaterPara.m_DONDiffusion * O_Water[0].m_WaterVolume * (O_Water[0].O_DON.m_N / O_Water[0].m_WaterVolume - O_Water[1].O_DON.m_N / O_Water[1].m_WaterVolume);
        flux2 = O_WaterPara.m_DONDiffusion * O_Water[1].m_WaterVolume * (O_Water[1].O_DON.m_N / O_Water[1].m_WaterVolume - O_Water[2].O_DON.m_N / O_Water[2].m_WaterVolume);
        flux3 = O_WaterPara.m_DONDiffusion * O_Water[2].m_WaterVolume * (O_Water[2].O_DON.m_N / O_Water[2].m_WaterVolume - O_Water[3].O_DON.m_N / O_Water[3].m_WaterVolume);

        if(flux1 > (O_Water[0].O_DON.m_N * 0.5))   flux1 = (O_Water[0].O_DON.m_N * 0.5);
        if(flux2 > (O_Water[1].O_DON.m_N * 0.5))   flux2 = (O_Water[1].O_DON.m_N * 0.5);
        if(flux3 > (O_Water[2].O_DON.m_N * 0.5))   flux3 = (O_Water[2].O_DON.m_N * 0.5);

        if(flux1 < 0.) flux1 = 0;

        O_Water[0].O_DON.m_N -= flux1;
        O_Water[1].O_DON.m_N -= flux2;
        O_Water[2].O_DON.m_N -= flux3;
        O_Water[1].O_DON.m_N += flux1;
        O_Water[2].O_DON.m_N += flux2;
        O_Water[3].O_DON.m_N += flux3;

        if(O_Water[0].m_WaterVolume <= 10e-10)  flux1 = 0.0;
        else        flux1 = O_WaterPara.m_DOPDiffusion * O_Water[0].m_WaterVolume * (O_Water[0].O_DON.m_P / O_Water[0].m_WaterVolume - O_Water[1].O_DON.m_P / O_Water[1].m_WaterVolume);
        flux2 = O_WaterPara.m_DOPDiffusion * O_Water[1].m_WaterVolume * (O_Water[1].O_DON.m_P / O_Water[1].m_WaterVolume - O_Water[2].O_DON.m_P / O_Water[2].m_WaterVolume);
        flux3 = O_WaterPara.m_DOPDiffusion * O_Water[2].m_WaterVolume * (O_Water[2].O_DON.m_P / O_Water[2].m_WaterVolume - O_Water[3].O_DON.m_P / O_Water[3].m_WaterVolume);

        if(flux1 > (O_Water[0].O_DON.m_P * 0.5))   flux1 = (O_Water[0].O_DON.m_P * 0.5);
        if(flux2 > (O_Water[1].O_DON.m_P * 0.5))   flux2 = (O_Water[1].O_DON.m_P * 0.5);
        if(flux3 > (O_Water[2].O_DON.m_P * 0.5))   flux3 = (O_Water[2].O_DON.m_P * 0.5);

        if(flux1 < 0.) flux1 = 0;

        O_Water[0].O_DON.m_P -= flux1;
        O_Water[1].O_DON.m_P -= flux2;
        O_Water[2].O_DON.m_P -= flux3;
        O_Water[1].O_DON.m_P += flux1;
        O_Water[2].O_DON.m_P += flux2;
        O_Water[3].O_DON.m_P += flux3;

        if(O_Water[0].m_WaterVolume <= 10e-10)  flux1 = 0.0;
        else        flux1 = O_WaterPara.m_POCDiffusion * O_Water[0].m_WaterVolume * (O_Water[0].O_PON.m_C / O_Water[0].m_WaterVolume - O_Water[1].O_PON.m_C / O_Water[1].m_WaterVolume);
        flux2 = O_WaterPara.m_POCDiffusion * O_Water[1].m_WaterVolume * (O_Water[1].O_PON.m_C / O_Water[1].m_WaterVolume - O_Water[2].O_PON.m_C / O_Water[2].m_WaterVolume);
        flux3 = O_WaterPara.m_POCDiffusion * O_Water[2].m_WaterVolume * (O_Water[2].O_PON.m_C / O_Water[2].m_WaterVolume - O_Water[3].O_PON.m_C / O_Water[3].m_WaterVolume);

        if(flux1 > (O_Water[0].O_PON.m_C * 0.5))   flux1 = (O_Water[0].O_PON.m_C * 0.5);
        if(flux2 > (O_Water[1].O_PON.m_C * 0.5))   flux2 = (O_Water[1].O_PON.m_C * 0.5);
        if(flux3 > (O_Water[2].O_PON.m_C * 0.5))   flux3 = (O_Water[2].O_PON.m_C * 0.5);

        if(flux1 < 0.) flux1 = 0;

        O_Water[0].O_PON.m_C -= flux1;
        O_Water[1].O_PON.m_C -= flux2;
        O_Water[2].O_PON.m_C -= flux3;
        O_Water[1].O_PON.m_C += flux1;
        O_Water[2].O_PON.m_C += flux2;
        O_Water[3].O_PON.m_C += flux3;

        if(O_Water[0].m_WaterVolume <= 10e-10)  flux1 = 0.0;
        else        flux1 = O_WaterPara.m_PONDiffusion * O_Water[0].m_WaterVolume * (O_Water[0].O_PON.m_N / O_Water[0].m_WaterVolume - O_Water[1].O_PON.m_N / O_Water[1].m_WaterVolume);
        flux2 = O_WaterPara.m_PONDiffusion * O_Water[1].m_WaterVolume * (O_Water[1].O_PON.m_N / O_Water[1].m_WaterVolume - O_Water[2].O_PON.m_N / O_Water[2].m_WaterVolume);
        flux3 = O_WaterPara.m_PONDiffusion * O_Water[2].m_WaterVolume * (O_Water[2].O_PON.m_N / O_Water[2].m_WaterVolume - O_Water[3].O_PON.m_N / O_Water[3].m_WaterVolume);

        if(flux1 > (O_Water[0].O_PON.m_N * 0.5))   flux1 = (O_Water[0].O_PON.m_N * 0.5);
        if(flux2 > (O_Water[1].O_PON.m_N * 0.5))   flux2 = (O_Water[1].O_PON.m_N * 0.5);
        if(flux3 > (O_Water[2].O_PON.m_N * 0.5))   flux3 = (O_Water[2].O_PON.m_N * 0.5);

        if(flux1 < 0.) flux1 = 0;

        O_Water[0].O_PON.m_N -= flux1;
        O_Water[1].O_PON.m_N -= flux2;
        O_Water[2].O_PON.m_N -= flux3;
        O_Water[1].O_PON.m_N += flux1;
        O_Water[2].O_PON.m_N += flux2;
        O_Water[3].O_PON.m_N += flux3;

        if(O_Water[0].m_WaterVolume <= 10e-10)  flux1 = 0.0;
        else        flux1 = O_WaterPara.m_POPDiffusion * O_Water[0].m_WaterVolume * (O_Water[0].O_PON.m_P / O_Water[0].m_WaterVolume - O_Water[1].O_PON.m_P / O_Water[1].m_WaterVolume);
        flux2 = O_WaterPara.m_POPDiffusion * O_Water[1].m_WaterVolume * (O_Water[1].O_PON.m_P / O_Water[1].m_WaterVolume - O_Water[2].O_PON.m_P / O_Water[2].m_WaterVolume);
        flux3 = O_WaterPara.m_POPDiffusion * O_Water[2].m_WaterVolume * (O_Water[2].O_PON.m_P / O_Water[2].m_WaterVolume - O_Water[3].O_PON.m_P / O_Water[3].m_WaterVolume);

        if(flux1 > (O_Water[0].O_PON.m_P * 0.5))   flux1 = (O_Water[0].O_PON.m_P * 0.5);
        if(flux2 > (O_Water[1].O_PON.m_P * 0.5))   flux2 = (O_Water[1].O_PON.m_P * 0.5);
        if(flux3 > (O_Water[2].O_PON.m_P * 0.5))   flux3 = (O_Water[2].O_PON.m_P * 0.5);

        if(flux1 < 0.) flux1 = 0;

        O_Water[0].O_PON.m_P -= flux1;
        O_Water[1].O_PON.m_P -= flux2;
        O_Water[2].O_PON.m_P -= flux3;
        O_Water[1].O_PON.m_P += flux1;
        O_Water[2].O_PON.m_P += flux2;
        O_Water[3].O_PON.m_P += flux3;

        }

/*
O_Water[0].m_WaterVolume += O_Flow.m_InWater[day];
O_Water[0].m_DNH4 += O_Flow.m_InNH4[day];
O_Water[0].m_DNO3 += O_Flow.m_InNO3[day];
O_Water[0].m_DPO4 += O_Flow.m_InPO4[day];
O_Water[0].O_DON.m_C += O_Flow.m_InDOC[day];
O_Water[0].O_DON.m_N += O_Flow.m_InDON[day];
O_Water[0].O_DON.m_P += O_Flow.m_InDOP[day];
O_Water[0].O_PON.m_C += O_Flow.m_InPOC[day];
O_Water[0].O_PON.m_N += O_Flow.m_InPON[day];
O_Water[0].O_PON.m_P += O_Flow.m_InPOP[day];
*/


if(g_WaterOrOutflow == 1)
        {
        float watertable = O_Flow.m_WaterTable[day];

        if(O_Water[0].m_WaterVolume < watertable)
                {
                O_Flow.m_OutWater[day] = 0.0;
                O_Water[0].m_WaterVolume = O_Water[0].m_WaterVolume;
                }
        else
                {
                if(watertable < 0)
                        {
                        O_Flow.m_OutWater[day] = 0.0;
                        O_Water[0].m_WaterVolume = 0.0;
                        }
                else
                        {
                        O_Flow.m_OutWater[day] = O_Water[0].m_WaterVolume - watertable;
                        O_Water[0].m_WaterVolume = watertable;
                        }
                }

                if(O_Water[0].m_WaterVolume < 10e-10)
                {
                O_Flow.m_OutNH4[day] = O_Water[0].m_DNH4;
                O_Flow.m_OutNO3[day] = O_Water[0].m_DNO3;
                O_Flow.m_OutPO4[day] = O_Water[0].m_DPO4;
                O_Flow.m_OutDOC[day] = O_Water[0].O_DON.m_C;
                O_Flow.m_OutDON[day] = O_Water[0].O_DON.m_N;
                O_Flow.m_OutDOP[day] = O_Water[0].O_DON.m_P;
                O_Flow.m_OutPOC[day] = O_Water[0].O_PON.m_C;
                O_Flow.m_OutPON[day] = O_Water[0].O_PON.m_N;
                O_Flow.m_OutPOP[day] = O_Water[0].O_PON.m_P;

                O_Water[0].m_DNH4 = 0.;
                O_Water[0].m_DNO3 = 0.;
                O_Water[0].m_DPO4 = 0.;
                O_Water[0].O_DON.m_C = 0.;
                O_Water[0].O_DON.m_N = 0.;
                O_Water[0].O_DON.m_P = 0.;
                O_Water[0].O_PON.m_C = 0.;
                O_Water[0].O_PON.m_N = 0.;
                O_Water[0].O_PON.m_P = 0.;
                }
                else
                {
                O_Flow.m_OutNH4[day] = O_Water[0].m_DNH4 * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutNO3[day] = O_Water[0].m_DNO3 * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutPO4[day] = O_Water[0].m_DPO4 * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutDOC[day] = O_Water[0].O_DON.m_C * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutDON[day] = O_Water[0].O_DON.m_N * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutDOP[day] = O_Water[0].O_DON.m_P * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutPOC[day] = O_Water[0].O_PON.m_C * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutPON[day] = O_Water[0].O_PON.m_N * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutPOP[day] = O_Water[0].O_PON.m_P * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                }
        O_Water[0].m_DNH4 -= O_Flow.m_OutNH4[day];
        O_Water[0].m_DNO3 -= O_Flow.m_OutNO3[day];
        O_Water[0].m_DPO4 -= O_Flow.m_OutPO4[day];
        O_Water[0].O_DON.m_C -= O_Flow.m_OutDOC[day];
        O_Water[0].O_DON.m_N -= O_Flow.m_OutDON[day];
        O_Water[0].O_DON.m_P -= O_Flow.m_OutDOP[day];
        O_Water[0].O_PON.m_C -= O_Flow.m_OutPOC[day];
        O_Water[0].O_PON.m_N -= O_Flow.m_OutPON[day];
        O_Water[0].O_PON.m_P -= O_Flow.m_OutPOP[day];

//        O_Water[0].m_WaterVolume = watertable;

        }
else
        {
        static outwaterstore = 0.0;
        float outwater = (O_Flow.m_OutWater[day] + outwaterstore);
                if(outwater < O_Water[0].m_WaterVolume)
                {
                O_Flow.m_OutWater[day] = outwater;
                O_Flow.m_OutNH4[day] = O_Water[0].m_DNH4 * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutNO3[day] = O_Water[0].m_DNO3 * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutPO4[day] = O_Water[0].m_DPO4 * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutDOC[day] = O_Water[0].O_DON.m_C * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutDON[day] = O_Water[0].O_DON.m_N * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutDOP[day] = O_Water[0].O_DON.m_P * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutPOC[day] = O_Water[0].O_PON.m_C * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutPON[day] = O_Water[0].O_PON.m_N * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;
                O_Flow.m_OutPOP[day] = O_Water[0].O_PON.m_P * O_Flow.m_OutWater[day] / O_Water[0].m_WaterVolume;

                O_Water[0].m_DNH4 -= O_Flow.m_OutNH4[day];
                O_Water[0].m_DNO3 -= O_Flow.m_OutNO3[day];
                O_Water[0].m_DPO4 -= O_Flow.m_OutPO4[day];
                O_Water[0].O_DON.m_C -= O_Flow.m_OutDOC[day];
                O_Water[0].O_DON.m_N -= O_Flow.m_OutDON[day];
                O_Water[0].O_DON.m_P -= O_Flow.m_OutDOP[day];
                O_Water[0].O_PON.m_C -= O_Flow.m_OutPOC[day];
                O_Water[0].O_PON.m_N -= O_Flow.m_OutPON[day];
                O_Water[0].O_PON.m_P -= O_Flow.m_OutPOP[day];
                O_Water[0].m_WaterVolume -= O_Flow.m_OutWater[day];
                }
                else
                {
                outwaterstore += (outwater - O_Water[0].m_WaterVolume);
                O_Water[0].m_WaterVolume = 0.0;
                O_Flow.m_OutNH4[day] = O_Water[0].m_DNH4;
                O_Flow.m_OutNO3[day] = O_Water[0].m_DNO3;
                O_Flow.m_OutPO4[day] = O_Water[0].m_DPO4;
                O_Flow.m_OutDOC[day] = O_Water[0].O_DON.m_C;
                O_Flow.m_OutDON[day] = O_Water[0].O_DON.m_N;
                O_Flow.m_OutDOP[day] = O_Water[0].O_DON.m_P;
                O_Flow.m_OutPOC[day] = O_Water[0].O_PON.m_C;
                O_Flow.m_OutPON[day] = O_Water[0].O_PON.m_N;
                O_Flow.m_OutPOP[day] = O_Water[0].O_PON.m_P;

                O_Water[0].m_DNH4 = 0.0;
                O_Water[0].m_DNO3 = 0.0;
                O_Water[0].m_DPO4 = 0.0;
                O_Water[0].O_DON.m_C = 0.0;
                O_Water[0].O_DON.m_N = 0.0;
                O_Water[0].O_DON.m_P = 0.0;
                O_Water[0].O_PON.m_C = 0.0;
                O_Water[0].O_PON.m_N = 0.0;
                O_Water[0].O_PON.m_P = 0.0;
                }

        }

}
