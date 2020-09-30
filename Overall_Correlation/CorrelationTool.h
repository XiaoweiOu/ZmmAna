#ifndef CORRELATIONTOOL_HEADER
#define CORRELATIONTOOL_HEADER

#include "State.h"

class CorrelationTool
{
public:
  double Num_Data_Forward_B[9]={853,4320,3393,3536,0,3348,3359,4273,823};
  double Num_Data_Backward_B[9]={807,4226,3357,3431,0,3360,3333,4162,802};
  double Num_Data_Forward_O[5]={3685,6694,5156,4100,465};
  double Num_Data_Backward_O[5]={3601,5968,4559,3631,377};
  double Num_Data_Forward_N[9];
  double Num_Data_Backward_N[9];

/*  double Num_MC_Forward_B[9]={5015.97,26532.6,21339.2,22534.6,0,22255.3,21102.2,26852.3,5053.09};
  double Num_MC_Backward_B[9]={5069.24,26496.9,20927.3,22351.9,0,21614,21023.7,26775.3,5073.71};
  double Num_MC_Forward_O[5]={24584.5,43798.4,32672.3,26628,3098.3};
  double Num_MC_Backward_O[5]={24087.5,40243.2,29325.8,23387.8,2618.35};
  double Num_MC_Forward_N[9];
  double Num_MC_Backward_N[9];*/

  //Plot_*:not change!
  TH1D *Plot_MC_Forward_B[9][9][3][3];//muon_eta:anti_muon_eta:muon_Pt:anti_muon_Pt
  TH1D *Plot_MC_Backward_B[9][9][3][3];
  TH1D *Plot_MC_Forward_O[9][9][3][3];
  TH1D *Plot_MC_Backward_O[9][9][3][3];
  TH1D *T_Plot_MC_Forward_B;
  TH1D *T_Plot_MC_Backward_B;
  TH1D *T_Plot_MC_Forward_O;
  TH1D *T_Plot_MC_Backward_O;

/*  double Num_EWBKG_Forward_B[9]={0.455979,5.17639,6.92268,7.50555,0,6.93838,6.62533,4.1531,0.391584};
  double Num_EWBKG_Backward_B[9]={0.888359,5.84633,7.19004,7.0578,0,5.94502,6.88617,3.93773,0.872646};
  double Num_EWBKG_Forward_O[5]={7.08814,11.1449,8.20005,4.28262,0.0694266};
  double Num_EWBKG_Backward_O[5]={7.75226,12.8724,8.2333,5.28579,0.0544676};
  double Num_EWBKG_Forward_N[9];
  double Num_EWBKG_Backward_N[9];*/

  TH1D *Plot_EWBKG_Forward_B[9][9][3][3];//muon_eta:anti_muon_eta:muon_Pt:anti_muon_Pt
  TH1D *Plot_EWBKG_Backward_B[9][9][3][3];
  TH1D *Plot_EWBKG_Forward_O[9][9][3][3];
  TH1D *Plot_EWBKG_Backward_O[9][9][3][3];
  TH1D *Plot_EWBKG_Forward_N[9][9][3][3];
  TH1D *Plot_EWBKG_Backward_N[9][9][3][3];
  TH1D *T_Plot_EWBKG_Forward_B;
  TH1D *T_Plot_EWBKG_Backward_B;
  TH1D *T_Plot_EWBKG_Forward_O;
  TH1D *T_Plot_EWBKG_Backward_O;
  TH1D *T_Plot_EWBKG_Forward_N;
  TH1D *T_Plot_EWBKG_Backward_N;

/*  double Num_QCDBKG_B[9]={0,6.36348,12.727,19.0904,0,44.5443,19.0904,6.36348,0};
  double Num_QCDBKG_O[5]={38.1809,38.1809,89.0887,146.36,19.0904};
  double Num_QCDBKG_N[9];*/

  TH1D *Plot_QCDBKG_B[9][9][3][3];
  TH1D *Plot_QCDBKG_O[9][9][3][3];
  TH1D *Plot_QCDBKG_N[9][9][3][3];
  TH1D *T_Plot_QCDBKG_B;
  TH1D *T_Plot_QCDBKG_O;
  TH1D *T_Plot_QCDBKG_N;

  // Ratio between Pythia and ResBos with O0_Pythia = O0_ResBos
  double Num_ResBos_B[9]={0.385952,1.78907,1.98709,2.08232,0,2.08329,1.98042,1.78609,0.386491};
  double Num_ResBos_O[5]={2.11677,3.92416,2.9234,1.66599,0.239647};
  double Num_Pythia_B[9]={105496,495554,557788,585923,0,584941,557372,495760,104940};
  double Num_Pythia_O[5]={594159,1.1189e+06,842089,478592,68258};
  double TheoryReweight_B[9];
  double TheoryReweight_O[5];

  // -------------------------------------------------------------------------------------------------------------------------- //
  // Number Definition                                                                                                          //
  // -------------------------------------------------------------------------------------------------------------------------- //
  // Z Rapidity Bin | -1.8~-1.4 | -1.4~-1.0 | -1.0~-0.6 | -0.6~-0.2 | -0.2~ 0.2 |  0.2~ 0.6 |  0.6~ 1.0 |  1.0~ 1.4 |  1.4~ 1.8 //
  // -------------------------------------------------------------------------------------------------------------------------- //
  // Both Lepton    |     B0    |     B1    |     B2    |     B3    |     -     |     B5    |     B6    |     B7    |     B8    //
  // in the i th    |           |           |           |           |     -     |           |           |           |           //
  // -------------------------------------------------------------------------------------------------------------------------- //
  // With two lepton in Opposite Eta bin                            |   O0~O4   |                                               //
  // -------------------------------------------------------------------------------------------------------------------------- //
  // Other Events   |     N0    |     N1    |     N2    |     N3    |     N4    |     N5    |     N6    |     N7    |     N8    //
  // -------------------------------------------------------------------------------------------------------------------------- //
  // O0: ZY in -0.2 ~ 0.2 One Lepton Eta -0.2 ~ 0.2, The other Lepton Eta -0.2 ~ 0.2
  // O1: ZY in -0.2 ~ 0.2 One Lepton Eta -0.6 ~-0.2, The other Lepton Eta  0.2 ~ 0.6
  // .........
  // O4: ZY in -0.2 ~ 0.2 One Lepton Eta -1.8 ~-1.4, The other Lepton Eta  1.4 ~ 1.8

  //calculate tag-and-probe weight
  TH2D *Eff_TagAndProbe_deno;//not change!
  TH2D *Eff_TagAndProbe_nume;//not change!
  TH2D *bkg_fit;//not change!
  TH2D *bkg_MC;//not change!
  TH2D *Eff_TagAndProbe_MC;//not change!
  TH2D *Eff_TagAndProbe_scale;

  //RandomData
  TH1D *Data_Forward_B;
  TH1D *Data_Forward_O;
  TH1D *Data_Forward_N;
  TH1D *Data_Forward;//Add:N+B(i!=4) N+O0+O1+...+O4(i==4)
  TH1D *Data_Backward_B;
  TH1D *Data_Backward_O;
  TH1D *Data_Backward_N;
  TH1D *Data_Backward;
  TH1D *Data;//Data_Forward + Data_Backward
  TH1D *Data_O;//Data_Forward_O + Data_Backward_O
  TH1D *Data_B;

  TH1D *MC_O;//Random MC_O:from Num_MC_Forward_O && Num_MC_Backward_O
  TH1D *MC_B;//Random MC_B

  TH1D *EWBKG_Forward_B;
  TH1D *EWBKG_Forward_O;
  TH1D *EWBKG_Forward_N;
  TH1D *EWBKG_Forward;
  TH1D *EWBKG_Backward_B;
  TH1D *EWBKG_Backward_O;
  TH1D *EWBKG_Backward_N;
  TH1D *EWBKG_Backward;
  TH1D *EWBKG;
  TH1D *EWBKG_O;
  TH1D *EWBKG_B;

  TH1D *QCDBKG_B;
  TH1D *QCDBKG_O;
  TH1D *QCDBKG_N;
  TH1D *QCDBKG;

  //RemoveBKG
  TH1D *DataRemoveBKG;
  TH1D *DataRemoveBKG_Forward;
  TH1D *DataRemoveBKG_Backward;

  //[9][9][3][3]: not change!

  //Calculate Matrix & Apply Matrix
  TH2D *num_true_reco[9][9][3][3];//muon_eta:anti_muon_eta:muon_Pt:anti_muon_Pt
  TH2D *num_true_reco_keep[9][9][3][3];
  TH1D *num_true[9][9][3][3];
  TH1D *num_true_keep[9][9][3][3];
  TH2D *T_num_true_reco;//T:total
  TH1D *T_num_true;
  TH2D *Matrix;
  TH1D *DataUnfold;
  TH1D *DataUnfold_Forward;
  TH1D *DataUnfold_Backward;

  //Overall Efficiency
  TH1D *MC_Zrapidity_foreff[9][9][3][3];////muon_eta:anti_muon_eta:muon_Pt:anti_muon_Pt
  TH1D *MC_Zrapidity_foreff_keep[9][9][3][3];
  TH1D *PassTrue_TrueZRapidity;//denominator
  TH1D *PassTruePassReco_TrueZRapidity;//numerator
  TH1D *OverallEfficiency;

  //Efficiency correction scale
  TH1D *DataRemoveBKG_O;
  TH1D *DataRemoveBKG_B;
  TH1D *RO;
  TH1D *RB;
  TH1D *EfficiencyReweight;

  //final result
  TH1D *DataResult;
  TH1D *DataResult_Forward;
  TH1D *DataResult_Backward;

  //after multiple cycles...
  TH1D *FinalResult;//多次循环的均值
  TH1D *Forward_FinalResult;
  TH1D *Backward_FinalResult;

  double EWScale;
  double QCDScale;
  double TheoryScale;
  double TagAndProbeScale;

  int timeperdisplay = 100;

  double sumXi[9];
  double sumXi2[9];
  double sumXiXj[9][9];
  double sumFBXi[18];
  double sumFBXi2[18];
  double sumFBXiXj[18][18];
  int count_num;

  bool RandomBKG = false;
  bool RandomTheory = false;
  bool RandomEfficiency = false;
  bool RandomTagAndProbeEff = false;

  TH2D *Correlation;
  TH2D *Correlation_FB;
  TH2D *Covariance;
  TH2D *Covariance_FB;

  TFile *Result;
  TRandom3 *myRandom;

  CorrelationTool(bool RBKG, bool RTh, bool REff, bool RTag);
  virtual ~CorrelationTool();
  virtual void Initialize();

  virtual void CallRandomExperiment();
  virtual void ReSet();
  virtual void RandomTagAndProbe();
  virtual void ApplyTagAndProbe();
  virtual void RandomData();
  virtual void RemoveBKG();
  virtual void EffCorr();//calculate efficiency correction scale
  virtual void ApplyEffCorr();
  virtual void Unfold();
  virtual void OverallEff();

  virtual void CalculateCorrelation();
  virtual void SaveFile();
  virtual void SaveFigure(const char *figurename);
  virtual void SaveFigureFB(const char *figurename);
};

#endif
