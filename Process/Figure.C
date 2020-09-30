#include"/lustre/AtlUser/xwou/include/plot/Figure.h"
int main()
{
 Figure *f1 = new Figure("Zrapidity_Forward.eps","Di-muon rapidity","");
 f1->SetMode("RATIO");
 f1->SetInputFigure(1,"Data_Final.root","DataFinal_Forward","data");
 f1->SetInputFigure(2,"../PDFuncertain/PDFuncertain.root","Zrapidity_F","CT14nnlo");
 f1->SetXrange(-1.8,1.8);
 f1->SetRatiorange(0.95,1.05);
 f1->SetHeaderName("DZero Internal");
 f1->DrawFigure();

 Figure *f2 = new Figure("Zrapidity_Backward.eps","Di-muon rapidity","");
 f2->SetMode("RATIO");
 f2->SetInputFigure(1,"Data_Final.root","DataFinal_Backward","data");
 f2->SetInputFigure(2,"../PDFuncertain/PDFuncertain.root","Zrapidity_B","CT14nnlo");
 f2->SetXrange(-1.8,1.8);
 f2->SetRatiorange(0.95,1.05);
 f2->SetHeaderName("DZero Internal");
 f2->DrawFigure();

/* Figure *f3 = new Figure("eff.eps","Di-muon rapidity","");
 f3->SetMode("SINGLE");
 f3->SetInputFigure(1,"Data_Final.root","eff","eff");
 f3->SetXrange(-1.8,1.8);
 f3->SetHeaderName("DZero Internal");
 f3->DrawFigure();*/
}
