void com_TH1D()
{
  bool DoNorm = true;
  TFile *file1 = new TFile("data_results.root");
  TFile *file2 = new TFile("MC_results.root");

  TH1D *plot1 = (TH1D *)file1->Get("plot_select_Zboson_mass_passDQ");
  TH1D *plot2 = (TH1D *)file2->Get("plot_select_Zboson_mass_passDQ");

  plot1->Sumw2();
  plot2->Sumw2();
//  plot1->Rebin(10);
//  plot2->Rebin(10);

  plot1->SetMarkerSize(0.6);
  plot2->SetMarkerSize(0.6);

  double inte1,inte2;
  inte1 = plot1->Integral();
  inte2 = plot2->Integral();

  if(DoNorm)
   {
    cout<<"Normalize plot2 to plot1"<<endl;
    inte1 = plot1->Integral();
    cout<<"before norm:   "<<endl;
    cout<<"integral of plot1  "<<inte1<<endl;
    cout<<"integral of plot2  "<<inte2<<endl;
    cout<<"norm factor of plot2  "<<inte1/inte2<<endl;

    plot2->Scale(inte1/inte2);
//    plot2->Scale(0.0221158);
   }

  plot2->SetLineColor(2);
  plot2->SetMarkerColor(2);
 
  TCanvas *MyN_1 = new TCanvas("plots_com","plots_com",1);
  plot1->Draw("E0");
  plot2->Draw("E0 same");

  TLegend *legend = new TLegend(0.75, 0.80, 0.95, 0.95);
  legend->AddEntry(plot1, "data");
  legend->AddEntry(plot2, "MC");
  legend->Draw("same");

  int binNumber;
  binNumber = plot1->GetNbinsX();
  double *getBinSet = new double[binNumber+1];

  for(int ii=0;ii<binNumber;ii++)
    getBinSet[ii] = plot1->GetXaxis()->GetBinLowEdge(ii+1);

  getBinSet[binNumber] = plot1->GetXaxis()->GetBinUpEdge(binNumber);

  TH1D *chi_plot = new TH1D("chi_plot","chi_plot",binNumber,getBinSet);
  TH1D *ratio_plot = new TH1D("ratio_plot","ratio_plot",binNumber,getBinSet);

  double get_bin_1,get_bin_2,get_err_1,get_err_2,set_bin,set_err;
  for(int ii=0;ii<binNumber;ii++)
   {
    get_bin_1 = plot1->GetBinContent(ii+1);
    get_bin_2 = plot2->GetBinContent(ii+1);
    get_err_1 = plot1->GetBinError(ii+1);
    get_err_2 = plot2->GetBinError(ii+1);
      
    if(get_bin_2!=0)
     {
      set_bin = get_bin_1/get_bin_2;
      set_err = fabs(1.0/get_bin_2)*get_err_1 + fabs(get_bin_1/(get_bin_2*get_bin_2))*get_err_2;
     }
    else
     {
      set_bin = 0.0;
      set_err = 0.0;
     }
    ratio_plot->SetBinContent(ii+1,set_bin);
    ratio_plot->SetBinError(ii+1,set_err);
   }

  double chi,chi_err,sum_chi2=0;
  for(int ii=0;ii<binNumber;ii++)
   {
    get_bin_1 = plot1->GetBinContent(ii+1);
    get_bin_2 = plot2->GetBinContent(ii+1);
    get_err_1 = plot1->GetBinError(ii+1);
    get_err_2 = plot2->GetBinError(ii+1);

    if(get_bin_1!=0)
     {
      set_bin = (get_bin_1-get_bin_2)/sqrt(get_err_1*get_err_1+get_err_2*get_err_2);
      set_err = 1.0;
     }
    else
     {
      set_bin = 0.0;
      set_err = 0.0;
     }
    chi_plot->SetBinContent(ii+1,set_bin);
    chi_plot->SetBinError(ii+1,set_err);
//    if(ii>3 && ii<45) sum_chi2 = set_bin*set_bin+sum_chi2;
    sum_chi2 = set_bin*set_bin+sum_chi2;
   }
  cout<<sum_chi2 / binNumber<<endl;

  double kndof = sum_chi2/binNumber;
//  cout<<"total chi2/bin:   "<<sum_chi2<<" / "<<binNumber<<"  =  "<<kndof<<endl;

  TCanvas *MyN_2 = new TCanvas("plots_ratio","plots_ratio",1);
  ratio_plot->Draw("E0");
//  MyN_2->SaveAs(Form("ECctEta_ccec_zpt_10_20.cpp"));

//  TCanvas *MyN_3 = new TCanvas("plots_chi","plots_chi",1);
//  chi_plot->Draw("E0");

}
