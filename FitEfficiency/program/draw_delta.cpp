void draw_delta()
{
  double tmptrigger[44] = {0.971846, 0.956062, 0.72655, 0.652283, 0.673568, 0.615904, 0.681824, 0.930574, 0.82709, 0.812831, 0.838218, 0.982524, 0.985806, 0.784771, 0.861271, 0.969495, 0.899563, 0.749568, 0.861428, 0.661989, 0.899086, 0.956937, 0.984523, 0.610716, 0.603355, 0.716601, 0.642578, 0.759498, 0.719481, 0.922915, 0.862564, 0.850838, 0.923925, 0.96317, 0.94887, 0.822559, 0.985859, 0.935968, 0.889474, 0.620195, 0.85699, 0.922494, 0.886981, 0.972326};
  double tmpselection[44] = {1.08592, 1.07803, 0.963275, 0.926141, 0.936784, 0.907952, 0.940912, 1.06529, 1.01355, 1.00642, 1.01911, 1.09126, 1.0929, 0.992385, 1.03064, 1.08475, 1.04978, 0.974784, 1.03071, 0.930995, 1.04954, 1.07847, 1.09226, 0.905358, 0.901678, 0.9583, 0.921289, 0.979749, 0.959741, 1.06146, 1.03128, 1.02542, 1.06196, 1.08158, 1.07444, 1.01128, 1.09293, 1.06798, 1.04474, 0.910098, 1.0285, 1.06125, 1.04349, 1.08616};

 double fit_trigger_eff[44];
 double fit_trigger_err[44];
 double fit_cut_eff[44];
 double fit_cut_err[44];

 ifstream infile;
  infile.open("../fit_trigger_eta.txt",ios::in);

 for(int ii=0;ii<44;ii++)
  {
   infile>>fit_trigger_eff[ii];
   infile>>fit_trigger_err[ii];
  }
 for(int ii=0;ii<44;ii++)
  {
   infile>>fit_cut_eff[ii];
   infile>>fit_cut_err[ii];
  }

  double etabin[45] = {-2.5, -2.2, -2.0, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.2, 2.5};

 TH1D *delta_trigger = new TH1D("delta_trigger","delta_trigger",44,etabin);
 TH1D *delta_cut = new TH1D("delta_cut","delta_cut",44,etabin);

 for(int ii=0;ii<44;ii++)
  {
   delta_trigger->SetBinContent(ii+1, fit_trigger_eff[ii]-tmptrigger[ii]);
   delta_trigger->SetBinError(ii+1, fit_trigger_err[ii]);

   delta_cut->SetBinContent(ii+1, fit_cut_eff[ii]-tmpselection[ii]);
   delta_cut->SetBinError(ii+1, fit_cut_err[ii]);
  }

 delta_trigger->SetLineColor(2);
 delta_trigger->SetMarkerColor(2);
 delta_trigger->Draw("E0");
 delta_cut->Draw("E0 same");

  TLegend *legend = new TLegend(0.75, 0.80, 0.95, 0.95);
  legend->AddEntry(delta_trigger, "trigger");
  legend->AddEntry(delta_cut, "selection");
  legend->Draw("same");


}
