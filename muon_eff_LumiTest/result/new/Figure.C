#include"/lustre/AtlUser/xwou/include/plot/Figure.h"
int main()
{
 Figure* f1 = new Figure("compare/lumi1_angleL_deno.eps","di-muon rapidity","Number of Events");
 f1->SetMode("RATIO");
 f1->SetInputFigure(1,"data_result.root","Iso_Zrapidity_lumi1_angleL_deno","data");
 f1->SetInputFigure(2,"MC_0_result.root","Iso_Zrapidity_lumi1_angleL_deno","MC");
 f1->SetXrange(-1.8,1.8);
 f1->SetRatiorange(0.92,1.08);
 f1->SetHeaderName("lumi1_angleL_deno");
 f1->SetNorm();
 f1->DrawFigure();

 f1 = new Figure("compare/lumi2_angleL_deno.eps","di-muon rapidity","Number of Events");
 f1->SetMode("RATIO");
 f1->SetInputFigure(1,"data_result.root","Iso_Zrapidity_lumi2_angleL_deno","data");
 f1->SetInputFigure(2,"MC_0_result.root","Iso_Zrapidity_lumi2_angleL_deno","MC");
 f1->SetXrange(-1.8,1.8);
 f1->SetRatiorange(0.92,1.08);
 f1->SetHeaderName("lumi2_angleL_deno");
 f1->SetNorm();
 f1->DrawFigure();

 f1 = new Figure("compare/lumi3_angleL_deno.eps","di-muon rapidity","Number of Events");
 f1->SetMode("RATIO");
 f1->SetInputFigure(1,"data_result.root","Iso_Zrapidity_lumi3_angleL_deno","data");
 f1->SetInputFigure(2,"MC_0_result.root","Iso_Zrapidity_lumi3_angleL_deno","MC");
 f1->SetXrange(-1.8,1.8);
 f1->SetRatiorange(0.92,1.08);
 f1->SetHeaderName("lumi3_angleL_deno");
 f1->SetNorm();
 f1->DrawFigure();

 f1 = new Figure("compare/lumi1_angleS_deno.eps","di-muon rapidity","Number of Events");
 f1->SetMode("RATIO");
 f1->SetInputFigure(1,"data_result.root","Iso_Zrapidity_lumi1_angleS_deno","data");
 f1->SetInputFigure(2,"MC_0_result.root","Iso_Zrapidity_lumi1_angleS_deno","MC");
 f1->SetXrange(-1.8,1.8);
 f1->SetRatiorange(0.92,1.08);
 f1->SetHeaderName("lumi1_angleS_deno");
 f1->SetNorm();
 f1->DrawFigure();

 f1 = new Figure("compare/lumi2_angleS_deno.eps","di-muon rapidity","Number of Events");
 f1->SetMode("RATIO");
 f1->SetInputFigure(1,"data_result.root","Iso_Zrapidity_lumi2_angleS_deno","data");
 f1->SetInputFigure(2,"MC_0_result.root","Iso_Zrapidity_lumi2_angleS_deno","MC");
 f1->SetXrange(-1.8,1.8);
 f1->SetRatiorange(0.92,1.08);
 f1->SetHeaderName("lumi2_angleS_deno");
 f1->SetNorm();
 f1->DrawFigure();

 f1 = new Figure("compare/lumi3_angleS_deno.eps","di-muon rapidity","Number of Events");
 f1->SetMode("RATIO");
 f1->SetInputFigure(1,"data_result.root","Iso_Zrapidity_lumi3_angleS_deno","data");
 f1->SetInputFigure(2,"MC_0_result.root","Iso_Zrapidity_lumi3_angleS_deno","MC");
 f1->SetXrange(-1.8,1.8);
 f1->SetRatiorange(0.92,1.08);
 f1->SetHeaderName("lumi3_angleS_deno");
 f1->SetNorm();
 f1->DrawFigure();
}
