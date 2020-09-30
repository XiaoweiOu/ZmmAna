void draw_factors()
{
 ifstream infile;
  infile.open("../fit_trigger_eta.txt",ios::in);

 double trigger[14],cut[14];
 double trigger_err[14],cut_err[14];
 for(int ii=0;ii<14;ii++)
  {
   infile>>trigger[ii];
   infile>>trigger_err[ii];
  }

 for(int ii=0;ii<14;ii++)
  {
   infile>>cut[ii];
   infile>>cut_err[ii];
  }

 double etabin[15] = {-1.6,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.6};
 TH1D *plot_trigger = new TH1D("plot_trigger","plot_trigger",14,etabin);
 TH1D *plot_cut = new TH1D("plot_cut","plot_cut",14,etabin);

 for(int ii=0;ii<14;ii++)
  {
   plot_trigger->SetBinContent(ii+1, trigger[ii]);
   plot_trigger->SetBinError(ii+1, trigger_err[ii]);
   plot_cut->SetBinContent(ii+1, cut[ii]);
   plot_cut->SetBinError(ii+1, cut_err[ii]);
  }

 plot_trigger->Draw("E0");
 plot_cut->SetMarkerColor(2);
 plot_cut->SetLineColor(2);
 plot_cut->Draw("E0 same");
}
