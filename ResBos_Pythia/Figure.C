#include"/lustre/AtlUser/xwou/plot_include/Figure.h"
int main()
{
 /*Figure *f1 = new Figure("diff_PDF_F.eps","Di-muon Rapidity","#frac{1}{#sigma}#frac{d#sigma}{dy^{Z}}");
 f1->SetMode("SIMPLE");
 f1->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAna/GeneLevel_eff/final_data.root","final_Zrapidity_F","data");
 f1->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_MMHT_F","MMHT");
 f1->SetInputFigure(3,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_NNPDF_F","NNPDF");
 f1->SetInputFigure(4,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_CT14_F","CT14");
 f1->SetXrange(-1.8,1.8);
 f1->SetHeaderName("DZero Internal");
 f1->SetNotNorm();
 f1->MoveLegendPosition(0.2,0.3);
 f1->DrawFigure();

 Figure *f2 = new Figure("diff_PDF_B.eps","Di-muon Rapidity","#frac{1}{#sigma}#frac{d#sigma}{dy^{Z}}");
 f2->SetMode("SIMPLE");
 f2->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAna/GeneLevel_eff/final_data.root","final_Zrapidity_B","data");
 f2->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_MMHT_B","MMHT");
 f2->SetInputFigure(3,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_NNPDF_B","NNPDF");
 f2->SetInputFigure(4,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_CT14_B","CT14");
 f2->SetXrange(-1.8,1.8);
 f2->SetHeaderName("DZero Internal");
 f2->SetNotNorm();
 f2->MoveLegendPosition(0.2,0.3);
 f2->DrawFigure();*/

 Figure *f3 = new Figure("diff_PDF.eps","Di-muon Rapidity","#frac{1}{#sigma}#frac{d#sigma}{dy^{Z}}");
 f3->SetMode("SIMPLE");
 f3->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV2/GeneLevel_eff/final_data.root","final_Zrapidity","data");
 f3->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_MMHT","MMHT");
 f3->SetInputFigure(3,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_NNPDF","NNPDF");
 f3->SetInputFigure(4,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_CT14","CT14");
 f3->SetInputFigure(5,"/lustre/AtlUser/xwou/ZmmAnaV2/ResBos_Pythia/diff_PDF.root","Zrapidity_old","CT6L1");
 f3->SetXrange(-1.8,1.8);
 f3->SetHeaderName("DZero Internal");
 f3->SetNotNorm();
 f3->MoveLegendPosition(0.2,0.3);
 f3->DrawFigure();
}
