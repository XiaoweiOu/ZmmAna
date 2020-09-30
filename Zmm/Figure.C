#include"/lustre/AtlUser/xwou/include/plot/Figure.h"
int main()
{
 Figure *f7 = new Figure("Zrapidity_compare.eps","Di-muon rapidity","Number of Events");
 f7->SetMode("RATIO");
 f7->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV4/Zmm/data_Normal/data_result.root","Zrapidity","data");
 f7->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV4/Zmm/MC_result/MC_EffSystWeight.root","Zrapidity","MC");
 f7->SetRatiorange(0.92,1.08);
 f7->SetXrange(-1.8,1.8);
 f7->SetHeaderName("DZero Internal");
 f7->SetNorm();
 f7->MoveLegendPosition(0.2,0.3);
 f7->DrawFigure();

 /*Figure *f2 = new Figure("bkg.eps","Di-muon rapidity","Number of Events");
 f2->SetMode("SIMPLE");
 f2->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV4/Zmm/data_Normal/data_result.root","Zrapidity_F","data");
// f2->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV4/Zmm/MC_result/MC_EffSystWeight.root","Zrapidity","MC");
 f2->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV4/Zmm/EW_norm.root","Zrapidity_F","EWbkg");
 f2->SetInputFigure(3,"/lustre/AtlUser/xwou/ZmmAnaV4/Zmm/QCD_spectrum.root","Zrapidity_F","QCD");
// f2->SetRatiorange(0.92,1.08);
 f2->SetXrange(-1.8,1.8);
 f2->SetHeaderName("DZero Internal");
 f2->Set_Yaxis_Log();
 f2->MoveLegendPosition(0.2,0.3);
 f2->DrawFigure();*/
}
