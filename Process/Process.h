#ifndef PROCESS_HEADER
#define PROCESS_HEADER

#include"State.h"

class Process
{
public:
 TH1D *Data_Forward;//promitive
 TH1D *Data_Backward;
 TH1D *DataBKG_Forward;//removed bkg
 TH1D *DataBKG_Backward;
 TH1D *DataMatrix_Forward;//pased matrix
 TH1D *DataMatrix_Backward;
 TH1D *DataEff_Forward;//pased overall efficiency
 TH1D *DataEff_Backward;
 TH1D *DataFinal_Forward;
 TH1D *DataFinal_Backward;

 TH1D *EW_Forward;
 TH1D *EW_Backward;
 TH1D *QCD_Forward;
 TH1D *QCD_Backward;

 TH2D *num_true_reco;
 TH1D *num_true;
 TH2D *Matrix;
 TH2D *Matrix_uncertain;

 TH1D *eff;
 TH1D *plot_true;
 TH1D *plot_reco;

 int tag_eff_num;
 TString str;

 Process();
 Process(int eff_num);//for Id,Trk,Iso efficiency(bkg*1,bkg*2,bkg*3)
 ~Process();
 void Initial();
 void BkgSubtract();
 void Migration();
 void OverEff();
 void Output();
};

#endif
