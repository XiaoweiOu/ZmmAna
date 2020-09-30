void theory()
{
 TFile *f_MMHT = new TFile("ResBos_MMHT_result.root");
 TFile *f_NNPDF = new TFile("ResBos_NNPDF_result.root");
 TFile *f_CT14 = new TFile("ResBos_CT14_result.root");
 TFile *f_old = new TFile("/lustre/AtlUser/xwou/ZmmAna/GeneLevel_eff/MC_result.root");
 TFile *f_result = new TFile("diff_PDF.root","RECREATE");

 Double_t inte;

 TH1D *p_old = (TH1D *)f_old->Get("Zmumu_Zrapidity");
 TH1D *p2_old = new TH1D("Zrapidity_old","Zrapidity_old",15,-3,3);
 inte = p_old->Integral();
 p_old->Scale(1/inte);
 p_old->Rebin(4);
 p2_old->Add(p_old);
 
 TH1D *p_MMHT_F = (TH1D *)f_MMHT->Get("Zrapidity_F");
 TH1D *p_MMHT_B = (TH1D *)f_MMHT->Get("Zrapidity_B");
 TH1D *p2_MMHT_F = new TH1D("Zrapidity_MMHT_F","Zrapidity_MMHT_F",15,-3,3);
 TH1D *p2_MMHT_B = new TH1D("Zrapidity_MMHT_B","Zrapidity_MMHT_B",15,-3,3);

 TH1D *p2_MMHT = new TH1D("Zrapidity_MMHT","Zrapidity_MMHT",15,-3,3);

 inte = p_MMHT_F->Integral() + p_MMHT_B->Integral();
 p_MMHT_F->Scale(1/inte);
 p_MMHT_B->Scale(1/inte);
 p_MMHT_F->Rebin(4);
 p_MMHT_B->Rebin(4);
 p2_MMHT_F->Add(p_MMHT_F);
 p2_MMHT_B->Add(p_MMHT_B);

 p2_MMHT->Add(p2_MMHT_F);
 p2_MMHT->Add(p2_MMHT_B);

 TH1D *p_NNPDF_F = (TH1D *)f_NNPDF->Get("Zrapidity_F");
 TH1D *p_NNPDF_B = (TH1D *)f_NNPDF->Get("Zrapidity_B");
 TH1D *p2_NNPDF_F = new TH1D("Zrapidity_NNPDF_F","Zrapidity_NNPDF_F",15,-3,3);
 TH1D *p2_NNPDF_B = new TH1D("Zrapidity_NNPDF_B","Zrapidity_NNPDF_B",15,-3,3);

 TH1D *p2_NNPDF = new TH1D("Zrapidity_NNPDF","Zrapidity_NNPDF",15,-3,3);

 inte = p_NNPDF_F->Integral() + p_NNPDF_B->Integral();
 p_NNPDF_F->Scale(1/inte);
 p_NNPDF_B->Scale(1/inte);
 p_NNPDF_F->Rebin(4);
 p_NNPDF_B->Rebin(4);
 p2_NNPDF_F->Add(p_NNPDF_F);
 p2_NNPDF_B->Add(p_NNPDF_B);
 
 p2_NNPDF->Add(p2_NNPDF_F);
 p2_NNPDF->Add(p2_NNPDF_B);

 TH1D *p_CT14_F = (TH1D *)f_CT14->Get("Zrapidity_F");
 TH1D *p_CT14_B = (TH1D *)f_CT14->Get("Zrapidity_B");
 TH1D *p2_CT14_F = new TH1D("Zrapidity_CT14_F","Zrapidity_CT14_F",15,-3,3);
 TH1D *p2_CT14_B = new TH1D("Zrapidity_CT14_B","Zrapidity_CT14_B",15,-3,3);
 
 TH1D *p2_CT14 = new TH1D("Zrapidity_CT14","Zrapidity_CT14",15,-3,3);
 
 inte = p_CT14_F->Integral() + p_CT14_B->Integral();
 p_CT14_F->Scale(1/inte);
 p_CT14_B->Scale(1/inte);
 p_CT14_F->Rebin(4);
 p_CT14_B->Rebin(4);
 p2_CT14_F->Add(p_CT14_F);
 p2_CT14_B->Add(p_CT14_B);

 p2_CT14->Add(p2_CT14_F);
 p2_CT14->Add(p2_CT14_B);

 f_result->Write();
 f_result->Close();
}
