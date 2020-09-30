void fiducial()
{
 TFile *f_Normal = new TFile("MC_EffSystWeight.root");
 TFile *f_fiducial = new TFile("MC_fiducial.root");

 TH1D *p_ratio = new TH1D("ratio","ratio",15,-3,3); 
 TH1D *p_Normal = (TH1D *)f_Normal->Get("Zrapidity");
 TH1D *p_fiducial = (TH1D *)f_fiducial->Get("Zrapidity");

 p_Normal->Rebin(4);
 p_fiducial->Rebin(4);

 p_ratio->Add(p_fiducial);
 p_ratio->Divide(p_Normal);

 p_ratio->Draw();
}
