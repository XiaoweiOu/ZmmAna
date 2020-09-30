void draw_compare()
{
 TH1D *plot_datatruth = new TH1D("plot_datatruth","plot_datatruth",15,-3,3);
 TH1D *plot_mctruth = new TH1D("plot_mctruth","plot_mctruth",15,-3,3);
 TH1D *plot_fitseed = new TH1D("plot_fitseed","plot_fitseed",15,-3,3);

 ifstream infile_input;
  infile_input.open("../Inputfiles/MCtruth.txt",ios::in);
 ifstream infile_output;
  infile_output.open("../fit_unfolding_zrapidity.txt",ios::in);

 double datainput[15],dataoutput[15],skip;

 for(int ibin=0;ibin<15;ibin++)
  {
   infile_input>>datainput[ibin];
   infile_output>>dataoutput[ibin];
   infile_output>>skip;

   plot_datatruth->SetBinContent(ibin+1, datainput[ibin]);
   plot_mctruth->SetBinContent(ibin+1, dataoutput[ibin]);
//   plot_fitseed->SetBinContent(ibin+1, datainput[ibin]*(0.5+ibin*0.02));
   plot_fitseed->SetBinContent(ibin+1, 200000);
  }

 plot_mctruth->SetMarkerColor(2);
 plot_mctruth->SetLineColor(2);
 plot_fitseed->SetMarkerColor(3);
 plot_fitseed->SetLineColor(3);


 double inte;
// inte = plot_datatruth->Integral();
// plot_datatruth->Scale(1/inte);
// inte = plot_mctruth->Integral();
// plot_mctruth->Scale(1./inte);
// inte = plot_fitseed->Integral();
// plot_fitseed->Scale(1./inte);

 plot_datatruth->Draw("E0");
 plot_mctruth->Draw("E0 same");
 plot_fitseed->Draw("E0 same");

  TLegend *legend = new TLegend(0.75, 0.80, 0.95, 0.95);
  legend->AddEntry(plot_datatruth, "MC truth");
  legend->AddEntry(plot_mctruth, "MC truth from unfolding");
  legend->AddEntry(plot_fitseed, "Input truth for fitting start");
  legend->Draw("same");
}
