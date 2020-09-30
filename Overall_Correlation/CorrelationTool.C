#ifndef CORRELATIONTOOL_SOURCE
#define CORRELATIONTOOL_SOURCE

#include "State.h"

CorrelationTool::CorrelationTool(bool RBKG, bool RTh, bool REff, bool RTag)
{
    RandomBKG = RBKG;
    RandomTheory = RTh;
    RandomEfficiency = REff;
    RandomTagAndProbeEff = RTag;
}

CorrelationTool::~CorrelationTool()
{
}

void CorrelationTool::Initialize()
{
    myRandom = new TRandom3(0);
    char name[100];
    double bindiv[6] = {0, 0.2, 0.6, 1.0, 1.4, 1.8};

    Data_Forward_B = new TH1D("Data_Forward_B", "Data_Forward_B", 9, -1.8, 1.8);
    Data_Forward_B->Sumw2();
    Data_Forward_O = new TH1D("Data_Forward_O", "Data_Forward_O", 5, bindiv);
    Data_Forward_O->Sumw2();
    Data_Forward_N = new TH1D("Data_Forward_N", "Data_Forward_N", 9, -1.8, 1.8);
    Data_Forward_N->Sumw2();
    Data_Backward_B = new TH1D("Data_Backward_B", "Data_Backward_B", 9, -1.8, 1.8);
    Data_Backward_B->Sumw2();
    Data_Backward_O = new TH1D("Data_Backward_O", "Data_Backward_O", 5, bindiv);
    Data_Backward_O->Sumw2();
    Data_Backward_N = new TH1D("Data_Backward_N", "Data_Backward_N", 9, -1.8, 1.8);
    Data_Backward_N->Sumw2();

    Data = new TH1D("Data", "Data", 9, -1.8, 1.8);
    Data->Sumw2();
    Data_Forward = new TH1D("Data_Forward", "Data_Forward", 9, -1.8, 1.8);
    Data_Forward->Sumw2();
    Data_Backward = new TH1D("Data_Backward", "Data_Backward", 9, -1.8, 1.8);
    Data_Backward->Sumw2();

    Data_B = new TH1D("Data_B", "Data_B", 9, -1.8, 1.8);
    Data_B->Sumw2();
    Data_O = new TH1D("Data_O", "Data_O", 5, bindiv);
    Data_O->Sumw2();

    MC_B = new TH1D("MC_B", "MC_B", 9, -1.8, 1.8);
    MC_B->Sumw2();
    MC_O = new TH1D("MC_O", "MC_O", 5, bindiv);
    MC_O->Sumw2();

    EWBKG_Forward_B = new TH1D("EWBKG_Forward_B", "EWBKG_Forward_B", 9, -1.8, 1.8);
    EWBKG_Forward_B->Sumw2();
    EWBKG_Forward_O = new TH1D("EWBKG_Forward_O", "EWBKG_Forward_O", 5, bindiv);
    EWBKG_Forward_O->Sumw2();
    EWBKG_Forward_N = new TH1D("EWBKG_Forward_N", "EWBKG_Forward_N", 9, -1.8, 1.8);
    EWBKG_Forward_N->Sumw2();
    EWBKG_Backward_B = new TH1D("EWBKG_Backward_B", "EWBKG_Backward_B", 9, -1.8, 1.8);
    EWBKG_Backward_B->Sumw2();
    EWBKG_Backward_O = new TH1D("EWBKG_Backward_O", "EWBKG_Backward_O", 5, bindiv);
    EWBKG_Backward_O->Sumw2();
    EWBKG_Backward_N = new TH1D("EWBKG_Backward_N", "EWBKG_Backward_N", 9, -1.8, 1.8);
    EWBKG_Backward_N->Sumw2();

    EWBKG = new TH1D("EWBKG", "EWBKG", 9, -1.8, 1.8);
    EWBKG->Sumw2();
    EWBKG_Forward = new TH1D("EWBKG_Forward", "EWBKG_Forward", 9, -1.8, 1.8);
    EWBKG_Forward->Sumw2();
    EWBKG_Backward = new TH1D("EWBKG_Backward", "EWBKG_Backward", 9, -1.8, 1.8);
    EWBKG_Backward->Sumw2();

    EWBKG_B = new TH1D("EWBKG_B", "EWBKG_B", 9, -1.8, 1.8);
    EWBKG_B->Sumw2();
    EWBKG_O = new TH1D("EWBKG_O", "EWBKG_O", 5, bindiv);
    EWBKG_O->Sumw2();

    QCDBKG_B = new TH1D("QCDBKG_B", "QCDBKG_B", 9, -1.8, 1.8);
    QCDBKG_B->Sumw2();
    QCDBKG_O = new TH1D("QCDBKG_O", "QCDBKG_O", 5, bindiv);
    QCDBKG_O->Sumw2();
    QCDBKG_N = new TH1D("QCDBKG_N", "QCDBKG_N", 9, -1.8, 1.8);
    QCDBKG_N->Sumw2();

    QCDBKG = new TH1D("QCDBKG", "QCDBKG", 9, -1.8, 1.8);
    QCDBKG->Sumw2();

    TFile *data_file = new TFile("../muon_eff/result/data_result.root");
    Eff_TagAndProbe_deno = (TH2D *)data_file->Get("Id_LeptonEta_Pt_deno");
    Eff_TagAndProbe_nume = (TH2D *)data_file->Get("Id_LeptonEta_Pt_nume");

    TFile *MC_file = new TFile("../mass_fitting/cal_eff.root");
    Eff_TagAndProbe_MC = (TH2D *)MC_file->Get("MC_Id_LeptonEta_Pt_eff");
    bkg_MC = (TH2D *)MC_file->Get("bkg");

    fstream bkg_file("../mass_fitting/help.txt");
    bkg_fit = (TH2D *)Eff_TagAndProbe_deno->Clone("bkg_fit");
    for(int i=1;i<=9;i++)
    for(int j=1;j<=3;j++)
    {
     string skip;
     bkg_file >> skip;
     double number;
     bkg_file >> number;
     bkg_fit->SetBinContent(i,j,number);
    }

    Eff_TagAndProbe_scale = new TH2D("Eff_TagAndProbe_scale","Eff_TagAndProbe_scale",9,-1.8,1.8,9,-1.8,1.8);

    TFile *file_MC = new TFile("../for_Correlation/MC_result/MC_Normal.root");
    for(int u=0;u<9;u++)
     for(int v=0;v<9;v++)
      for(int p=0;p<3;p++)
       for(int q=0;q<3;q++)
       {
        sprintf(name,"Forward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_MC_Forward_B[u][v][p][q] = (TH1D *)file_MC->Get(name);
        sprintf(name,"Forward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_MC_Forward_O[u][v][p][q] = (TH1D *)file_MC->Get(name);
        sprintf(name,"Backward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_MC_Backward_B[u][v][p][q] = (TH1D *)file_MC->Get(name);
        sprintf(name,"Backward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_MC_Backward_O[u][v][p][q] = (TH1D *)file_MC->Get(name);
       }

    TFile *file_MC_Matrix = new TFile("../for_Correlation/MC_result/MC_Matrix.root");
    for(int u=0;u<9;u++)
     for(int v=0;v<9;v++)
      for(int p=0;p<3;p++)
       for(int q=0;q<3;q++)
       {
        sprintf(name,"num_true_reco_eta%d%d_Pt%d%d",u,v,p,q);
        num_true_reco_keep[u][v][p][q] = (TH2D *)file_MC_Matrix->Get(name);
        sprintf(name,"num_true_eta%d%d_Pt%d%d",u,v,p,q);
        num_true_keep[u][v][p][q] = (TH1D *)file_MC_Matrix->Get(name);
       }

    DataUnfold = new TH1D("DataUnfold", "DataUnfold", 9, -1.8, 1.8);
    DataUnfold->Sumw2();
    DataUnfold_Forward = new TH1D("DataUnfold_Forward", "DataUnfold_Forward", 9, -1.8, 1.8);
    DataUnfold_Forward->Sumw2();
    DataUnfold_Backward = new TH1D("DataUnfold_Backward", "DataUnfold_Backward", 9, -1.8, 1.8);
    DataUnfold_Backward->Sumw2();

    OverallEfficiency = new TH1D("OverallEfficiency", "OverallEfficiency", 9, -1.8, 1.8);
    OverallEfficiency->Sumw2();

    EfficiencyReweight = new TH1D("EfficiencyReweight", "EfficiencyReweight", 9, -1.8, 1.8);
    EfficiencyReweight->Sumw2();

    TFile *file_MC_foreff = new TFile("../for_Correlation/MC_result/MC_foreff.root");
    for(int u=0;u<9;u++)
     for(int v=0;v<9;v++)
      for(int p=0;p<3;p++)
       for(int q=0;q<3;q++)
       {
        sprintf(name,"num_true_eta%d%d_Pt%d%d",u,v,p,q);
        MC_Zrapidity_foreff_keep[u][v][p][q] = (TH1D *)file_MC_foreff->Get(name);
       }

    PassTruePassReco_TrueZRapidity = new TH1D("PassTruePassReco_TrueZRapidity", "PassTruePassReco_TrueZRapidity", 9, -1.8, 1.8);
    PassTruePassReco_TrueZRapidity->Sumw2();
    TFile *passtruefile = new TFile("../../ZmmAnaV3/GeneLevel_eff/MC_result.root");
    PassTrue_TrueZRapidity = (TH1D *)passtruefile->Get("Zmumu_Zrapidity");
    PassTrue_TrueZRapidity->Rebin(4);

    Result = new TFile("FinalCorrelationResult.root", "RECREATE");
    Correlation = new TH2D("Correlation", "Correlation", 9, -1.8, 1.8, 9, -1.8, 1.8);
    Correlation->Sumw2();
    Correlation_FB = new TH2D("Correlation_FB", "Correlation_FB", 18, 0, 18, 18, 0, 18);
    Correlation_FB->Sumw2();

    Covariance = new TH2D("Covariance", "Covariance", 9, -1.8, 1.8, 9, -1.8, 1.8);
    Covariance->Sumw2();
    Covariance_FB = new TH2D("Covariance_FB", "Covariance_FB", 18, 0, 18, 18, 0, 18);
    Covariance_FB->Sumw2();

    FinalResult = new TH1D("FinalResult","FinalResult",9,-1.8,1.8);
    FinalResult->Sumw2();
    Forward_FinalResult = new TH1D("Forward_FinalResult","Forward_FinalResult",9,-1.8,1.8);
    Forward_FinalResult->Sumw2();
    Backward_FinalResult = new TH1D("Backward_FinalResult","Backward_FinalResult",9,-1.8,1.8);
    Backward_FinalResult->Sumw2();

    for (int i = 0; i < 9; i++)
    {
        sumXi[i] = 0;
        sumXi2[i] = 0;
        for (int j = 0; j < 9; j++)
            sumXiXj[i][j] = 0;
    }

    for (int i = 0; i < 18; i++)
    {
        sumFBXi[i] = 0;
        sumFBXi2[i] = 0;
        for (int j = 0; j < 18; j++)
            sumFBXiXj[i][j] = 0;
    }

    TFile *file_data = new TFile("../Zmm/data_Normal/data_result.root");
    TH1D *data_F = (TH1D *)file_data->Get("Zrapidity_F");
    TH1D *data_B = (TH1D *)file_data->Get("Zrapidity_B");
    data_F->Rebin(4);
    data_B->Rebin(4);
    for(int i=0;i<9;i++)
    {
	Num_Data_Forward_N[i] = data_F->GetBinContent(i+4);//total!
  	Num_Data_Backward_N[i] = data_B->GetBinContent(i+4);
        if(i==4)
        {
                for(int j=0;j<5;j++)
		{
    			Num_Data_Forward_N[i] -= Num_Data_Forward_O[j] ;
	 		Num_Data_Backward_N[i] -= Num_Data_Backward_O[j] ;
		}
        }
        else
        {
		Num_Data_Forward_N[i] -= Num_Data_Forward_B[i];	
		Num_Data_Backward_N[i] -= Num_Data_Backward_B[i];
	}
    }

    TFile *file_EWMC = new TFile("../for_Correlation/EW_norm.root");
    for(int u=0;u<9;u++)
     for(int v=0;v<9;v++)
      for(int p=0;p<3;p++)
       for(int q=0;q<3;q++)
       {
        sprintf(name,"Forward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_EWBKG_Forward_B[u][v][p][q] = (TH1D *)file_EWMC->Get(name);
        sprintf(name,"Forward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_EWBKG_Forward_O[u][v][p][q] = (TH1D *)file_EWMC->Get(name);
        sprintf(name,"Backward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_EWBKG_Backward_B[u][v][p][q] = (TH1D *)file_EWMC->Get(name);
        sprintf(name,"Backward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_EWBKG_Backward_O[u][v][p][q] = (TH1D *)file_EWMC->Get(name);

        sprintf(name,"Forward_Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_EWBKG_Forward_N[u][v][p][q] = (TH1D *)file_EWMC->Get(name);//total!
        sprintf(name,"Backward_Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_EWBKG_Backward_N[u][v][p][q] = (TH1D *)file_EWMC->Get(name);

        for(int i=1;i<=Plot_EWBKG_Forward_N[u][v][p][q]->GetNbinsX();i++)
        {
         double content_F = Plot_EWBKG_Forward_N[u][v][p][q]->GetBinContent(i);
         double content_B = Plot_EWBKG_Backward_N[u][v][p][q]->GetBinContent(i);
         if(i==5)
          for(int j=1;j<=Plot_EWBKG_Forward_O[u][v][p][q]->GetNbinsX();j++)
          {
           content_F -= Plot_EWBKG_Forward_O[u][v][p][q]->GetBinContent(j);
           content_B -= Plot_EWBKG_Backward_O[u][v][p][q]->GetBinContent(j);
          }
         else
         {
          content_F -= Plot_EWBKG_Forward_B[u][v][p][q]->GetBinContent(i);
          content_B -= Plot_EWBKG_Backward_B[u][v][p][q]->GetBinContent(i);
         }
         Plot_EWBKG_Forward_N[u][v][p][q]->SetBinContent(i,content_F);
         Plot_EWBKG_Backward_N[u][v][p][q]->SetBinContent(i,content_B);
        }
       }
 
    TFile *file_QCD = new TFile("../for_Correlation/QCD_spectrum.root");
    TH1D *Forward_B,*Forward_O,*Forward_N,*Backward_B,*Backward_O,*Backward_N;
    for(int u=0;u<9;u++)
     for(int v=0;v<9;v++)
      for(int p=0;p<3;p++)
       for(int q=0;q<3;q++)
       {
        sprintf(name,"Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_QCDBKG_B[u][v][p][q] = (TH1D *)file_QCD->Get(name);
        sprintf(name,"Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_QCDBKG_O[u][v][p][q] = (TH1D *)file_QCD->Get(name);
    
        sprintf(name,"Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
        Plot_QCDBKG_N[u][v][p][q] = (TH1D *)file_QCD->Get(name);//total!

        for(int i=1;i<=Plot_QCDBKG_N[u][v][p][q]->GetNbinsX();i++)
        {
         double content = Plot_QCDBKG_N[u][v][p][q]->GetBinContent(i);
         if(i==5)
          for(int j=1;j<=Plot_QCDBKG_O[u][v][p][q]->GetNbinsX();j++)
           content -=Plot_QCDBKG_O[u][v][p][q]->GetBinContent(j);
         else 
           content -= Plot_QCDBKG_B[u][v][p][q]->GetBinContent(i);
         Plot_QCDBKG_N[u][v][p][q]->SetBinContent(i,content);
        }
       }

    double Pythia_rwt;
    Pythia_rwt = Num_Pythia_O[0] / Num_ResBos_O[0];
    for(int i=0;i<9;i++)
    	Num_Pythia_B[i] /= Pythia_rwt;
    for(int i=0;i<5;i++)
	Num_Pythia_O[i] /= Pythia_rwt;
    
    for(int i=0;i<9;i++)
	TheoryReweight_B[i] = Num_Pythia_B[i] / Num_ResBos_B[i];
    for(int i=0;i<5;i++)
	TheoryReweight_O[i] = Num_Pythia_O[i] / Num_ResBos_O[i];

    double array[6]={0,0.2,0.6,1.0,1.4,1.8};

    T_Plot_MC_Forward_B = new TH1D("T_Plot_MC_Forward_B","T_Plot_MC_Forward_B",9,-1.8,1.8);
    T_Plot_MC_Backward_B = new TH1D("T_Plot_MC_Backward_B","T_Plot_MC_Backward_B",9,-1.8,1.8);
    T_Plot_MC_Forward_O = new TH1D("T_Plot_MC_Forward_O","T_Plot_MC_Forward_O",5,array);
    T_Plot_MC_Backward_O = new TH1D("T_Plot_MC_Backward_O","T_Plot_MC_Backward_O",5,array);
    T_Plot_MC_Forward_B->Sumw2();
    T_Plot_MC_Backward_B->Sumw2();
    T_Plot_MC_Forward_O->Sumw2();
    T_Plot_MC_Backward_O->Sumw2();

    T_Plot_EWBKG_Forward_B = new TH1D("T_Plot_EWBKG_Forward_B","T_Plot_EWBKG_Forward_B",9,-1.8,1.8);
    T_Plot_EWBKG_Backward_B = new TH1D("T_Plot_EWBKG_Backward_B","T_Plot_EWBKG_Backward_B",9,-1.8,1.8);
    T_Plot_EWBKG_Forward_O = new TH1D("T_Plot_EWBKG_Forward_O","T_Plot_EWBKG_Forward_O",5,array);
    T_Plot_EWBKG_Backward_O = new TH1D("T_Plot_EWBKG_Backward_O","T_Plot_EWBKG_Backward_O",5,array);
    T_Plot_EWBKG_Forward_N = new TH1D("T_Plot_EWBKG_Forward_N","T_Plot_EWBKG_Forward_N",9,-1.8,1.8);
    T_Plot_EWBKG_Backward_N = new TH1D("T_Plot_EWBKG_Backward_N","T_Plot_EWBKG_Backward_N",9,-1.8,1.8);

    T_num_true_reco = new TH2D("T_num_true_reco","T_num_true_reco",9,-1.8,1.8,9,-1.8,1.8);
    T_num_true = new TH1D("T_num_true","T_num_true",9,-1.8,1.8);

    T_Plot_EWBKG_Forward_B->Sumw2();
    T_Plot_EWBKG_Backward_B->Sumw2();
    T_Plot_EWBKG_Forward_O->Sumw2();
    T_Plot_EWBKG_Backward_O->Sumw2();
    T_Plot_EWBKG_Forward_N->Sumw2();
    T_Plot_EWBKG_Backward_N->Sumw2();

    T_Plot_QCDBKG_B = new TH1D("T_Plot_QCDBKG_B","T_Plot_QCDBKG_B",9,-1.8,1.8);
    T_Plot_QCDBKG_O = new TH1D("T_Plot_QCDBKG_O","T_Plot_QCDBKG_O",5,array);
    T_Plot_QCDBKG_N = new TH1D("T_Plot_QCDBKG_N","T_Plot_QCDBKG_N",9,-1.8,1.8);

    T_Plot_QCDBKG_B->Sumw2();
    T_Plot_QCDBKG_O->Sumw2();
    T_Plot_QCDBKG_N->Sumw2();
  
    T_num_true_reco->Sumw2();
    T_num_true->Sumw2();
}

void myfcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    CorrelationTool *subtool = (CorrelationTool *)myMinuit->GetObjectFit();

    Int_t i_truth, j_reco;
    Double_t R = 0; //matrix element
    Double_t content = 0, error = 0;

    char name[100];

    double predict_Forward[9];
    double predict_Backward[9];

    TH1D *reco_Forward = subtool->DataRemoveBKG_Forward;
    TH1D *reco_Backward = subtool->DataRemoveBKG_Backward;
    TH2D *matrix = subtool->Matrix;

    //calculate predict:(sigma i)Rij x N_truth_i
    for (j_reco = 1; j_reco <= 9; j_reco++)
    {
        content = 0;
        for (i_truth = 1; i_truth <= 9; i_truth++)
        {
            R = matrix->GetBinContent(i_truth, j_reco); //true in ith bin, reco in jth bin(probability)
            content += R * par[i_truth - 1];                    //Ntruth[ith bin] -->> par[i-1]
        }
        predict_Forward[j_reco - 1] = content;
    }
    for (j_reco = 1; j_reco <= 9; j_reco++)
    {
        content = 0;
        for (i_truth = 1; i_truth <= 9; i_truth++)
        {
            R = matrix->GetBinContent(i_truth, j_reco); //true in ith bin, reco in jth bin(probability)
            content += R * par[i_truth - 1 + 9];                //Ntruth[ith bin] -->> par[i-1]
        }
        predict_Backward[j_reco - 1] = content;
    }

    //calculate chisquare
    Double_t chisq = 0;
    Double_t num_reco, num_predict;
    for (int i = 1; i <= 9; i++)
    {
        num_reco = reco_Forward->GetBinContent(i);
        num_predict = predict_Forward[i - 1];

        chisq += pow(num_reco - num_predict, 2) / num_reco;

        num_reco = reco_Backward->GetBinContent(i);
        num_predict = predict_Backward[i - 1];

        chisq += pow(num_reco - num_predict, 2) / num_reco;
    }

    f = chisq;
}

void CorrelationTool::Unfold()
{
    //calculate matrix!
    double nume=0,deno=0,error_nume=0,error_deno=0,error;
    Matrix = (TH2D *)T_num_true_reco->Clone("Matrix");

    for(int i=1;i<=T_num_true_reco->GetNbinsX();i++)
    {
     for(int j=1;j<=T_num_true_reco->GetNbinsY();j++)
     {
      nume = T_num_true_reco->GetBinContent(i,j);
      deno = T_num_true->GetBinContent(i);
      error_nume = T_num_true_reco->GetBinError(i,j);
      error_deno = T_num_true->GetBinError(i);

      if(deno!=0)
       Matrix->SetBinContent(i,j,nume/deno);
      if(nume/deno<1e-5)Matrix->SetBinContent(i,j,0);
     }
    }

    //fitting!!
    myMinuit = new TMinuit(18);
    myMinuit->SetMaxIterations(100000);
    myMinuit->SetFCN(myfcn);
    myMinuit->SetObjectFit((TObject *)(ZRapidityOverall));
    myMinuit->SetPrintLevel(-1);
    myMinuit->SetErrorDef(1.0);
    myMinuit->mncler();

    Int_t ierflg;
    Double_t arglist[10];
    arglist[0] = 1.0;
    myMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

    char name[100];
    double StepSize = 1;

    for (int ipar = 0; ipar < 9; ipar++)
    {
        sprintf(name, "%s%d", "Forward_par_", ipar);
        myMinuit->mnparm(ipar, name, Data_Forward->GetBinContent(ipar + 1), StepSize, 0, Data_Forward->GetBinContent(ipar + 1) * 3, ierflg);
        sprintf(name, "%s%d", "Backward_par_", ipar);
        myMinuit->mnparm(ipar + 9, name, Data_Backward->GetBinContent(ipar + 1), StepSize, 0, Data_Backward->GetBinContent(ipar + 1) * 3, ierflg);
    }

    arglist[0] = 10000;
    arglist[1] = 0.01;

    myMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);

    for (int i = 0; i < 9; i++)
    {
        double value, error;
        myMinuit->GetParameter(i, value, error);
        DataUnfold_Forward->SetBinContent(i + 1, value);
        DataUnfold_Forward->SetBinError(i + 1, 0);

        myMinuit->GetParameter(i + 9, value, error);
        DataUnfold_Backward->SetBinContent(i + 1, value);
        DataUnfold_Backward->SetBinError(i + 1, 0);

        DataUnfold->SetBinContent(i + 1, DataUnfold_Forward->GetBinContent(i + 1) + DataUnfold_Backward->GetBinContent(i + 1));
        DataUnfold->SetBinError(i + 1, 0);
    }

    if (count_num % timeperdisplay == 0)
    {
        cout << count_num << "   After Matrix:   ";
        for (int i = 0; i < 9; i++)
            cout << DataUnfold->GetBinContent(i + 1) << "   ";
        cout << endl;

        cout << count_num << "   After Matrix Forward:   ";
        for (int i = 0; i < 9; i++)
            cout << DataUnfold_Forward->GetBinContent(i + 1) << "   ";
        cout << endl;

        cout << count_num << "   After Matrix Backward:   ";
        for (int i = 0; i < 9; i++)
            cout << DataUnfold_Backward->GetBinContent(i + 1) << "   ";
        cout << endl;
    }

    delete myMinuit;
}

void CorrelationTool::ApplyTagAndProbe()//add changable weight into MC!!!
{
 //sample needing this eff:
 //
 //Num_MC_Forward_B,O
 //Num_EWBKG_Forward_B,O,N
 //Num_QCDBKG_B,O,N
 //MC_Matrix
 //MC_foreff

 for(int j=0;j<9;j++)//muon_eta
  for(int k=0;k<9;k++)//anti_muon_eta
   for(int w=0;w<3;w++)//muon_Pt
    for(int v=0;v<3;v++)//anti_muon_Pt
    {
     //tag-and-probe
     double muon_eff;
     double anti_muon_eff;
     if(RandomTagAndProbeEff)
     {
      muon_eff = Eff_TagAndProbe_scale->GetBinContent(j+1,w+1);
      anti_muon_eff = Eff_TagAndProbe_scale->GetBinContent(k+1,v+1);
     }
     else
     {
      muon_eff = 1;
      anti_muon_eff = 1;
     }

     //Num_MC_Forward_B...
     T_Plot_MC_Forward_B->Add(Plot_MC_Forward_B[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_MC_Backward_B->Add(Plot_MC_Backward_B[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_MC_Forward_O->Add(Plot_MC_Forward_O[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_MC_Backward_O->Add(Plot_MC_Backward_O[j][k][w][v],muon_eff*anti_muon_eff);
 
     //Num_EWBKG_Forward_B...
     T_Plot_EWBKG_Forward_B->Add(Plot_EWBKG_Forward_B[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_EWBKG_Backward_B->Add(Plot_EWBKG_Backward_B[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_EWBKG_Forward_O->Add(Plot_EWBKG_Forward_O[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_EWBKG_Backward_O->Add(Plot_EWBKG_Backward_O[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_EWBKG_Forward_N->Add(Plot_EWBKG_Forward_N[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_EWBKG_Backward_N->Add(Plot_EWBKG_Backward_N[j][k][w][v],muon_eff*anti_muon_eff);

     //Num_QCD_BKG_B...
     T_Plot_QCDBKG_B->Add(Plot_QCDBKG_B[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_QCDBKG_O->Add(Plot_QCDBKG_O[j][k][w][v],muon_eff*anti_muon_eff);
     T_Plot_QCDBKG_N->Add(Plot_QCDBKG_N[j][k][w][v],muon_eff*anti_muon_eff);

     MC_Zrapidity_foreff[j][k][w][v]->Scale(muon_eff*anti_muon_eff);//foreff
     num_true[j][k][w][v]->Scale(muon_eff*anti_muon_eff);//Matrix
     num_true_reco[j][k][w][v]->Scale(muon_eff*anti_muon_eff);
    }
}

void CorrelationTool::ApplyEffCorr()//add changable weight into MC!!!
{
 for(int j=0;j<9;j++)//muon_eta
  for(int k=0;k<9;k++)//anti_muon_eta
   for(int w=0;w<3;w++)//muon_Pt
    for(int v=0;v<3;v++)//anti_muon_Pt
    {
     //efficiency correction scale
     double rwt1, rwt2;
     if (RandomEfficiency)
     {
      rwt1 = EfficiencyReweight->GetBinContent(j + 1);
      rwt2 = EfficiencyReweight->GetBinContent(k + 1);
     }
     else
     {
      rwt1 = 1;
      rwt2 = 1;
     }
 
     //add
     PassTruePassReco_TrueZRapidity->Add(MC_Zrapidity_foreff[j][k][w][v],rwt1*rwt2);//foreff
     T_num_true->Add(num_true[j][k][w][v],rwt1*rwt2);//Matrix
     T_num_true_reco->Add(num_true_reco[j][k][w][v],rwt1*rwt2);//Matrix
    }
}

void CorrelationTool::RandomData()
{
    // Generate Random Scale
    if (RandomBKG)
    {
        EWScale = 1 + myRandom->Gaus(0, 0.25);
        QCDScale = 1 + myRandom->Gaus(0, 1);
        if (EWScale < 0)
            EWScale = 0;
        if (QCDScale < 0)
            QCDScale = 0;
    }
    else
    {
        EWScale = 1;
        QCDScale = 1;
    }

    if (RandomTheory)
        TheoryScale = myRandom->Uniform(0, 1);
    else
        TheoryScale = 0;

    // Generate Random Pseudo-data and MC and Background
    // random N,B
    for (int i = 0; i < 9; i++)
    {
        Data_Forward_N->SetBinContent(i + 1, myRandom->Poisson(Num_Data_Forward_N[i]));
        Data_Forward_N->SetBinError(i + 1, 0);
        Data_Backward_N->SetBinContent(i + 1, myRandom->Poisson(Num_Data_Backward_N[i]));
        Data_Backward_N->SetBinError(i + 1, 0);

        EWBKG_Forward_N->SetBinContent(i + 1, EWScale * T_Plot_EWBKG_Forward_N->GetBinContent(i+1));

        EWBKG_Forward_N->SetBinError(i + 1, 0);
        EWBKG_Backward_N->SetBinContent(i + 1, EWScale * T_Plot_EWBKG_Backward_N->GetBinContent(i+1));
        EWBKG_Backward_N->SetBinError(i + 1, 0);

        QCDBKG_N->SetBinContent(i + 1, QCDScale * T_Plot_QCDBKG_N->GetBinContent(i+1));
        QCDBKG_N->SetBinError(i + 1, 0);

        if (i == 4)
            continue;

        Data_Forward_B->SetBinContent(i + 1, myRandom->Poisson(Num_Data_Forward_B[i]));
        Data_Forward_B->SetBinError(i + 1, 0);
        Data_Backward_B->SetBinContent(i + 1, myRandom->Poisson(Num_Data_Backward_B[i]));
        Data_Backward_B->SetBinError(i + 1, 0);
        EWBKG_Forward_B->SetBinContent(i + 1, EWScale * T_Plot_EWBKG_Forward_B->GetBinContent(i+1));
        EWBKG_Forward_B->SetBinError(i + 1, 0);
        EWBKG_Backward_B->SetBinContent(i + 1, EWScale * T_Plot_EWBKG_Backward_B->GetBinContent(i+1));
        EWBKG_Backward_B->SetBinError(i + 1, 0);
        QCDBKG_B->SetBinContent(i + 1, QCDScale * T_Plot_QCDBKG_B->GetBinContent(i+1));
        QCDBKG_B->SetBinError(i + 1, 0);

        MC_B->SetBinContent(i + 1, (T_Plot_MC_Backward_B->GetBinContent(i+1) + T_Plot_MC_Forward_B->GetBinContent(i+1)) * (1 + TheoryScale * (TheoryReweight_B[i] - 1)));
        MC_B->SetBinError(i + 1, 0);

        Data_B->SetBinContent(i + 1, Data_Forward_B->GetBinContent(i + 1) + Data_Backward_B->GetBinContent(i + 1));
        Data_B->SetBinError(i + 1, 0);

        EWBKG_B->SetBinContent(i + 1, EWBKG_Forward_B->GetBinContent(i + 1) + EWBKG_Backward_B->GetBinContent(i + 1));
        EWBKG_B->SetBinError(i + 1, 0);
    }

    //random O
    for (int i = 0; i < 5; i++)
    {
        Data_Forward_O->SetBinContent(i + 1, myRandom->Poisson(Num_Data_Forward_O[i]));
        Data_Forward_O->SetBinError(i + 1, 0);
        Data_Backward_O->SetBinContent(i + 1, myRandom->Poisson(Num_Data_Backward_O[i]));
        Data_Backward_O->SetBinError(i + 1, 0);
        EWBKG_Forward_O->SetBinContent(i + 1, EWScale * T_Plot_EWBKG_Forward_O->GetBinContent(i+1));
        EWBKG_Forward_O->SetBinError(i + 1, 0);
        EWBKG_Backward_O->SetBinContent(i + 1, EWScale * T_Plot_EWBKG_Backward_O->GetBinContent(i+1));
        EWBKG_Backward_O->SetBinError(i + 1, 0);
        QCDBKG_O->SetBinContent(i + 1, QCDScale * T_Plot_QCDBKG_O->GetBinContent(i+1));
        QCDBKG_O->SetBinError(i + 1, 0);

        MC_O->SetBinContent(i + 1, (T_Plot_MC_Backward_O->GetBinContent(i+1) + T_Plot_MC_Forward_O->GetBinContent(i+1)) * (1 + TheoryScale * (TheoryReweight_O[i] - 1)));
        MC_O->SetBinError(i + 1, 0);

        Data_O->SetBinContent(i + 1, Data_Forward_O->GetBinContent(i + 1) + Data_Backward_O->GetBinContent(i + 1));
        Data_O->SetBinError(i + 1, 0);

        EWBKG_O->SetBinContent(i + 1, EWBKG_Forward_O->GetBinContent(i + 1) + EWBKG_Backward_O->GetBinContent(i + 1));
        EWBKG_O->SetBinError(i + 1, 0);
    }

    //add:N+B(i!=4) N+O0+O1+...+O4(i==4)
    for (int i = 0; i < 9; i++)
    {
        if (i == 4)
        {
            Data_Forward->SetBinContent(i + 1, Data_Forward_N->GetBinContent(i + 1) + Data_Forward_O->Integral(1, 5));
            Data_Backward->SetBinContent(i + 1, Data_Backward_N->GetBinContent(i + 1) + Data_Backward_O->Integral(1, 5));
            EWBKG_Forward->SetBinContent(i + 1, EWBKG_Forward_N->GetBinContent(i + 1) + EWBKG_Forward_O->Integral(1, 5));
            EWBKG_Backward->SetBinContent(i + 1, EWBKG_Backward_N->GetBinContent(i + 1) + EWBKG_Backward_O->Integral(1, 5));
            QCDBKG->SetBinContent(i + 1, QCDBKG_N->GetBinContent(i + 1) + QCDBKG_O->Integral(1, 5));
        }
        else
        {
            Data_Forward->SetBinContent(i + 1, Data_Forward_N->GetBinContent(i + 1) + Data_Forward_B->GetBinContent(i + 1));
            Data_Backward->SetBinContent(i + 1, Data_Backward_N->GetBinContent(i + 1) + Data_Backward_B->GetBinContent(i + 1));
            EWBKG_Forward->SetBinContent(i + 1, EWBKG_Forward_N->GetBinContent(i + 1) + EWBKG_Forward_B->GetBinContent(i + 1));
            EWBKG_Backward->SetBinContent(i + 1, EWBKG_Backward_N->GetBinContent(i + 1) + EWBKG_Backward_B->GetBinContent(i + 1));
            QCDBKG->SetBinContent(i + 1, QCDBKG_N->GetBinContent(i + 1) + QCDBKG_B->GetBinContent(i + 1));
        }

	Data->SetBinContent(i+1, Data_Forward->GetBinContent(i+1) + Data_Backward->GetBinContent(i+1));
        EWBKG->SetBinContent(i+1, EWBKG_Forward->GetBinContent(i+1) + EWBKG_Backward->GetBinContent(i+1));
        
	Data_Forward->SetBinError(i + 1, 0);
        Data_Backward->SetBinError(i + 1, 0);
        EWBKG_Forward->SetBinError(i + 1, 0);
        EWBKG_Backward->SetBinError(i + 1, 0);
        QCDBKG->SetBinError(i + 1, 0);
 	Data->SetBinError(i+1, 0);
        EWBKG->SetBinError(i+1, 0);
    }

    //output!
    if (count_num % timeperdisplay == 0)
    {
        cout << count_num << "   Random Data:   ";
        for (int i = 0; i < 9; i++)
            cout << Data->GetBinContent(i + 1) << "   ";
        cout << endl;

        cout << count_num << "   Random Data Forward:   ";
        for (int i = 0; i < 9; i++)
            cout << Data_Forward->GetBinContent(i + 1) << "   ";
        cout << endl;

        cout << count_num << "   Random Data Backward:   ";
        for (int i = 0; i < 9; i++)
            cout << Data_Backward->GetBinContent(i + 1) << "   ";
        cout << endl;
    }
}

void CorrelationTool::RemoveBKG()
{
    // Remove BKG from Data
    DataRemoveBKG = (TH1D *)Data->Clone("DataRemoveBKG");
    DataRemoveBKG->Add(EWBKG, -1);
    DataRemoveBKG->Add(QCDBKG, -1);

    DataRemoveBKG_Forward = (TH1D *)Data_Forward->Clone("DataRemoveBKG_Forward");
    DataRemoveBKG_Forward->Add(EWBKG_Forward, -1);
    DataRemoveBKG_Forward->Add(QCDBKG, -0.5);
    DataRemoveBKG_Backward = (TH1D *)Data_Backward->Clone("DataRemoveBKG_Backward");
    DataRemoveBKG_Backward->Add(EWBKG_Backward, -1);
    DataRemoveBKG_Backward->Add(QCDBKG, -0.5);

    // Remove BKG for Efficiency Measurement
    DataRemoveBKG_O = (TH1D *)Data_O->Clone("DataRemoveBKG_O");
    DataRemoveBKG_O->Add(EWBKG_O, -1);
    DataRemoveBKG_O->Add(QCDBKG_O, -1);
    DataRemoveBKG_B = (TH1D *)Data_B->Clone("DataRemoveBKG_O");
    DataRemoveBKG_B->Add(EWBKG_B, -1);
    DataRemoveBKG_B->Add(QCDBKG_B, -1);

    if (count_num % timeperdisplay == 0)
    {
        cout << count_num << "   After BKG:   ";
        for (int i = 0; i < 9; i++)
            cout << DataRemoveBKG->GetBinContent(i + 1) << "   ";
        cout << endl;

        cout << count_num << "   After BKG Forward:   ";
        for (int i = 0; i < 9; i++)
            cout << DataRemoveBKG_Forward->GetBinContent(i + 1) << "   ";
        cout << endl;

        cout << count_num << "   After BKG Backward:   ";
        for (int i = 0; i < 9; i++)
            cout << DataRemoveBKG_Backward->GetBinContent(i + 1) << "   ";
        cout << endl;
    }
}

void CorrelationTool::EffCorr()
{
    // Ratio between Data and MC
    RO = (TH1D *)DataRemoveBKG_O->Clone("RO");
    RO->Divide(MC_O);

    RB = (TH1D *)DataRemoveBKG_B->Clone("RB");
    RB->Divide(MC_B);

    // Calculate Efficiency Reweighting Factor
    EfficiencyReweight->SetBinContent(5,1);
    EfficiencyReweight->SetBinError(5,0);
    double x,y;
    for (int i = 1; i <= 4; i++)
    {
	x = RO->GetBinContent(i+1) / RO->GetBinContent(1);
	y = RB->GetBinContent(i+5) / RB->GetBinContent(5-i);

  	EfficiencyReweight->SetBinContent(i+5,pow(x*x*y,0.25));
	EfficiencyReweight->SetBinError(i+5,0);
  	EfficiencyReweight->SetBinContent(5-i,pow(x*x/y,0.25));
	EfficiencyReweight->SetBinError(5-i,0);
    }

    if (count_num % timeperdisplay == 0)
    {
        cout << count_num << "   Efficiency Reweight:   ";
        for (int i = 0; i < 9; i++)
            cout << EfficiencyReweight->GetBinContent(i + 1) << "   ";
        cout << endl;
    }
}

void CorrelationTool::OverallEff()
{
    // Calculate Overall Efficiency
    PassTruePassReco_TrueZRapidity->Scale(5000000.0 / 1.08782e+07);
    for (int i = 0; i < 9; i++)
    {  
        OverallEfficiency->SetBinContent(i + 1, PassTruePassReco_TrueZRapidity->GetBinContent(i + 1) / PassTrue_TrueZRapidity->GetBinContent(i + 4));
        OverallEfficiency->SetBinError(i + 1, 0);
    }

    if (count_num % timeperdisplay == 0)
    {
        cout << count_num << "   Overall Efficiency:   ";
        for (int i = 0; i < 9; i++)
            cout << OverallEfficiency->GetBinContent(i + 1) << "   ";
        cout << endl;
    }

    // Get Final Result
    DataResult = (TH1D *)DataUnfold->Clone("DataResult");
    DataResult->Divide(OverallEfficiency);
    DataResult_Forward = (TH1D *)DataUnfold_Forward->Clone("DataResult_Forward");
    DataResult_Forward->Divide(OverallEfficiency);
    DataResult_Backward = (TH1D *)DataUnfold_Backward->Clone("DataResult_Backward");
    DataResult_Backward->Divide(OverallEfficiency);

    // Nomalization
    DataResult_Forward->Scale(1.0 / DataResult->Integral());
    DataResult_Backward->Scale(1.0 / DataResult->Integral());
    DataResult->Scale(1.0 / DataResult->Integral());

    if (count_num % timeperdisplay == 0)
    {
        cout << count_num << "   Result:   ";
        for (int i = 0; i < 9; i++)
            cout << DataResult->GetBinContent(i + 1) << "   ";
        cout << endl;

        cout << count_num << "   Result Forward:   ";
        for (int i = 0; i < 9; i++)
            cout << DataResult_Forward->GetBinContent(i + 1) << "   ";
        cout << endl;

        cout << count_num << "   Result Backward:   ";
        for (int i = 0; i < 9; i++)
            cout << DataResult_Backward->GetBinContent(i + 1) << "   ";
        cout << endl;
    }
}

void CorrelationTool::CallRandomExperiment()
{
    count_num = count_num + 1;
    ReSet();
    RandomTagAndProbe();
    ApplyTagAndProbe();
    RandomData();
    RemoveBKG();
    EffCorr();
    ApplyEffCorr();
    Unfold();
    OverallEff();

    // Sum up for correlation
    for (int i = 0; i < 9; i++)
    {
        sumXi[i] = sumXi[i] + DataResult->GetBinContent(i + 1);
        sumXi2[i] = sumXi2[i] + DataResult->GetBinContent(i + 1) * DataResult->GetBinContent(i + 1);
        for (int j = 0; j < 9; j++)
            sumXiXj[i][j] = sumXiXj[i][j] + DataResult->GetBinContent(i + 1) * DataResult->GetBinContent(j + 1);
    }

    for (int i = 0; i < 9; i++)
    {
        sumFBXi[i] = sumFBXi[i] + DataResult_Forward->GetBinContent(i + 1);
        sumFBXi2[i] = sumFBXi2[i] + DataResult_Forward->GetBinContent(i + 1) * DataResult_Forward->GetBinContent(i + 1);
        for (int j = 0; j < 9; j++)
            sumFBXiXj[i][j] = sumFBXiXj[i][j] + DataResult_Forward->GetBinContent(i + 1) * DataResult_Forward->GetBinContent(j + 1);
        for (int j = 0; j < 9; j++)
            sumFBXiXj[i][j + 9] = sumFBXiXj[i][j + 9] + DataResult_Forward->GetBinContent(i + 1) * DataResult_Backward->GetBinContent(j + 1);
    }
    for (int i = 0; i < 9; i++)
    {
        sumFBXi[i + 9] = sumFBXi[i + 9] + DataResult_Backward->GetBinContent(i + 1);
        sumFBXi2[i + 9] = sumFBXi2[i + 9] + DataResult_Backward->GetBinContent(i + 1) * DataResult_Backward->GetBinContent(i + 1);
        for (int j = 0; j < 9; j++)
            sumFBXiXj[i + 9][j] = sumFBXiXj[i + 9][j] + DataResult_Backward->GetBinContent(i + 1) * DataResult_Forward->GetBinContent(j + 1);
        for (int j = 0; j < 9; j++)
            sumFBXiXj[i + 9][j + 9] = sumFBXiXj[i + 9][j + 9] + DataResult_Backward->GetBinContent(i + 1) * DataResult_Backward->GetBinContent(j + 1);
    }

}

void CorrelationTool::CalculateCorrelation()
{
    cout << count_num << endl;
  
    //Final result
    for(int i=1;i<=9;i++)
    {
      FinalResult->SetBinContent(i,sumXi[i-1]/count_num);
      FinalResult->SetBinError(i,sqrt(sumXi2[i-1]*count_num-sumXi[i-1]*sumXi[i-1])/count_num);

      Forward_FinalResult->SetBinContent(i,sumFBXi[i-1]/count_num);
      Forward_FinalResult->SetBinError(i,sqrt(sumFBXi2[i-1]*count_num-sumFBXi[i-1]*sumFBXi[i-1])/count_num);

      Backward_FinalResult->SetBinContent(i,sumFBXi[i+8]/count_num);
      Backward_FinalResult->SetBinError(i,sqrt(sumFBXi2[i+8]*count_num-sumFBXi[i+8]*sumFBXi[i+8])/count_num);
    }

    FinalResult->Scale(1./FinalResult->Integral());
    Forward_FinalResult->Scale(1./FinalResult->Integral());
    Backward_FinalResult->Scale(1./FinalResult->Integral());

    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            cout << FinalResult->GetBinContent(i + 1, j + 1) << "\t";
        }
        cout << endl;
    }
    cout << endl;
    

    //correlation coefficient(X,Y) = covariance(X,Y)/sqrt(var(X)*var(Y))
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Correlation->SetBinContent(i + 1, j + 1, (sumXiXj[i][j] - sumXi[i] * sumXi[j] / count_num) / (sqrt((sumXi2[i] - sumXi[i] * sumXi[i] / count_num) * (sumXi2[j] - sumXi[j] * sumXi[j] / count_num))));
            Correlation->SetBinError(i + 1, j + 1, 0);

            cout << Correlation->GetBinContent(i + 1, j + 1) << "\t";
        }
        cout << endl;
    }
    cout << endl;

    //covariance(X,Y)=E(XY)-E(X)*E(Y)
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            Covariance->SetBinContent(i + 1, j + 1, (sumXiXj[i][j]*count_num - sumXi[i]*sumXi[j])/pow(count_num,2));
            Covariance->SetBinError(i + 1, j + 1, 0);
        }

    cout << "Relative Uncertainty:   ";
    
    //sigma(x)/E(x)

    for (int i = 0; i < 9; i++)
        cout << sqrt(sumXi2[i] / count_num - sumXi[i] * sumXi[i] / count_num / count_num) / (sumXi[i] / count_num) << "   ";
    cout << endl;

    //FB
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 18; j++)
        {
            Correlation_FB->SetBinContent(i + 1, j + 1, (sumFBXiXj[i][j] - sumFBXi[i] * sumFBXi[j] / count_num) / (sqrt((sumFBXi2[i] - sumFBXi[i] * sumFBXi[i] / count_num) * (sumFBXi2[j] - sumFBXi[j] * sumFBXi[j] / count_num))));
            Correlation_FB->SetBinError(i + 1, j + 1, 0);

            cout << Correlation_FB->GetBinContent(i + 1, j + 1) << "\t";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 18; j++)
        {
            Covariance_FB->SetBinContent(i + 1, j + 1, (sumFBXiXj[i][j]*count_num - sumFBXi[i]*sumFBXi[j])/pow(count_num,2));
            Covariance_FB->SetBinError(i + 1, j + 1, 0);
        }

    cout << "Forward Relative Uncertainty:   ";
    for (int i = 0; i < 9; i++)
        cout << sqrt(sumFBXi2[i] / count_num - sumFBXi[i] * sumFBXi[i] / count_num / count_num) / (sumFBXi[i] / count_num) << "   ";
    cout << endl;

    cout << "Backward Relative Uncertainty:   ";
    for (int i = 0; i < 9; i++)
        cout << sqrt(sumFBXi2[i + 9] / count_num - sumFBXi[i + 9] * sumFBXi[i + 9] / count_num / count_num) / (sumFBXi[i + 9] / count_num) << "   ";
    cout << endl;
}

void CorrelationTool::SaveFile()
{
    Result->Write();
    Result->Close();
}

void CorrelationTool::SaveFigure(const char *figurename)
{
    TH2D *A = Correlation;
    char name[100];
    TCanvas *c = new TCanvas("c", "canvas", 2000, 2000);

    gStyle->SetLineWidth(2);
    gStyle->SetGridWidth(0.01);
    gStyle->SetTextFont(72);

    Double_t bindiv_reco[10] = {-1.8, -1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4, 1.8};
    Double_t bindiv_true[10] = {-1.8, -1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4, 1.8};
    int binnum_reco = 9;
    int binnum_true = 9;

    TH2D *Slice = new TH2D("Slice", "Slice", binnum_true, bindiv_true, binnum_reco, bindiv_reco);
    for (int i = 0; i < binnum_true; i++)
    {
        for (int j = 0; j < binnum_reco; j++)
        {
            double asmb = A->GetBinContent(i + 1, j + 1);
            Slice->SetBinContent(i + 1, j + 1, ((int)(asmb * 1000)) / 1000.0);
            Slice->SetBinError(i + 1, j + 1, A->GetBinError(i + 1, j + 1));
        }
    }

    TGraph *vgrid[8];
    TGraph *pgrid[8];

    TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 1, 1.0);

    pad1->SetTopMargin(0.13);
    pad1->SetLeftMargin(0.10);
    pad1->SetRightMargin(0.13);
    pad1->SetBottomMargin(0.07);
    pad1->SetTicks();
    //pad1->SetGridx(); // Vertical grid
    //pad1->SetGridy();
    pad1->Draw();       // Draw the upper pad: pad1
    pad1->cd();         // pad1 becomes the current pad*/
    Slice->SetStats(0); // No statistics on upper plot
    Slice->GetYaxis()->SetTitleSize(55);
    Slice->GetYaxis()->SetTitleFont(73);
    Slice->GetYaxis()->SetTitleOffset(1.3);
    Slice->GetYaxis()->SetLabelSize(45);
    Slice->GetYaxis()->SetLabelFont(73);

    Slice->GetXaxis()->SetTitleSize(55);
    Slice->GetXaxis()->SetTitleFont(73);
    Slice->GetXaxis()->SetTitleOffset(1.3);
    Slice->GetXaxis()->SetLabelSize(45);
    Slice->GetXaxis()->SetLabelFont(73);

    Slice->GetZaxis()->SetLabelSize(45);
    Slice->GetZaxis()->SetLabelFont(73);

    //Slice->GetZaxis()->SetRangeUser(-0.1,1);

    Slice->GetYaxis()->SetTitle("Dilepton Rapidity");
    Slice->GetXaxis()->SetTitle("Dilepton Rapidity");
    Slice->SetTitle("");

    Slice->Draw("COLZ");
    Slice->Draw("TEXT same");

    c->Update();

    TLegend *legend = new TLegend(0.08, 0.90, 0.83, 0.95);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetLineColor(0);
    legend->SetLineWidth(0);
    legend->SetTextSize(0.05);
    legend->SetTextFont(72);
    sprintf(name, "Correlation Matrix");
    legend->SetHeader(name);
    legend->Draw("same");

    for (int i = 0; i < 8; i++)
    {
        double vgridx[10] = {
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
        };
        vgrid[i] = new TGraph(10, vgridx, bindiv_reco);
        double pgridy[10] = {
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
            -1.4 + i * 0.4,
        };
        pgrid[i] = new TGraph(10, bindiv_true, pgridy);

        vgrid[i]->SetLineColor(2);
        vgrid[i]->SetLineStyle(10);
        vgrid[i]->SetLineWidth(2);
        vgrid[i]->SetFillStyle(0);
        vgrid[i]->SetFillColor(0);

        pgrid[i]->SetLineColor(2);
        pgrid[i]->SetLineStyle(10);
        pgrid[i]->SetLineWidth(2);
        pgrid[i]->SetFillStyle(0);
        pgrid[i]->SetFillColor(0);

        vgrid[i]->Draw("C");
        pgrid[i]->Draw("C");
    }

    // h[1] settings
    //Slice->SetLineColor(kBlue + 1);
    //Slice->SetLineWidth(8);
    //Slice->SetMarkerColor(kBlue + 1);

    // Y axis h[1] plot settings

    c->Update();
    c->SaveAs(figurename);
}

void CorrelationTool::SaveFigureFB(const char *figurename)
{
    TH2D *A = Correlation_FB;
    char name[100];
    TCanvas *c = new TCanvas("c_FB", "canvas", 20000, 20000);

    gStyle->SetLineWidth(1);
    gStyle->SetGridWidth(0.01);
    gStyle->SetTextFont(72);

    Double_t bindiv_reco[10] = {-1.8, -1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4, 1.8};
    Double_t bindiv_true[10] = {-1.8, -1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4, 1.8};
    int binnum_reco = 18;
    int binnum_true = 18;

    TH2D *Slice = new TH2D("Slice_FB", "Slice_FB", 18, 0, 18, 18, 0, 18);
    for (int i = 0; i < binnum_true; i++)
    {
        for (int j = 0; j < binnum_reco; j++)
        {
            double asmb = A->GetBinContent(i + 1, j + 1);
            Slice->SetBinContent(i + 1, j + 1, ((int)(asmb * 1000)) / 1000.0);
            Slice->SetBinError(i + 1, j + 1, A->GetBinError(i + 1, j + 1));
        }
    }

    for (int i = 0; i < binnum_true; i++)
    {
        if (i < 9)
            sprintf(name, "Forward %03.1f < y^{Z} < %03.1f", bindiv_true[i], bindiv_true[i + 1]);
        else
            sprintf(name, "Backward %03.1f < y^{Z} < %03.1f", bindiv_true[i - 9], bindiv_true[i - 9 + 1]);

        Slice->GetXaxis()->SetBinLabel(i + 1, name);
        Slice->GetYaxis()->SetBinLabel(i + 1, name);
    }
    Slice->LabelsOption("v");

    TGraph *vgrid[8];
    TGraph *pgrid[8];

    TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 1, 1.0);

    pad1->SetTopMargin(0.10);
    pad1->SetLeftMargin(0.19);
    pad1->SetRightMargin(0.10);
    pad1->SetBottomMargin(0.19);
    pad1->SetTicks();
    //pad1->SetGridx(); // Vertical grid
    //pad1->SetGridy();
    pad1->Draw();       // Draw the upper pad: pad1
    pad1->cd();         // pad1 becomes the current pad*/
    Slice->SetStats(0); // No statistics on upper plot
    Slice->GetYaxis()->SetTitleSize(55);
    Slice->GetYaxis()->SetTitleFont(73);
    Slice->GetYaxis()->SetTitleOffset(1.3);
    Slice->GetYaxis()->SetLabelSize(300);
    Slice->GetYaxis()->SetLabelFont(73);

    Slice->GetXaxis()->SetTitleSize(55);
    Slice->GetXaxis()->SetTitleFont(73);
    Slice->GetXaxis()->SetTitleOffset(1.3);
    Slice->GetXaxis()->SetLabelSize(300);
    Slice->GetXaxis()->SetLabelFont(73);

    Slice->GetZaxis()->SetLabelSize(300);
    Slice->GetZaxis()->SetLabelFont(73);

    //Slice->GetZaxis()->SetRangeUser(-0.1,1);

    Slice->GetYaxis()->SetTitle("");
    Slice->GetXaxis()->SetTitle("");
    Slice->SetTitle("");

    Slice->Draw("COLZ");
    Slice->Draw("TEXT same");

    c->Update();

    TLegend *legend = new TLegend(0.18, 0.92, 0.83, 0.97);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetLineColor(0);
    legend->SetLineWidth(0);
    legend->SetTextSize(0.05);
    legend->SetTextFont(72);
    sprintf(name, "Correlation Matrix");
    legend->SetHeader(name);
    legend->Draw("same");

    double gridanother[19] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

    for (int i = 0; i < 17; i++)
    {
        double vgridx[19];
        for (int j = 0; j < 19; j++)
            vgridx[j] = i + 1;
        vgrid[i] = new TGraph(19, vgridx, gridanother);
        double pgridy[19];
        for (int j = 0; j < 19; j++)
            pgridy[j] = i + 1;
        pgrid[i] = new TGraph(19, gridanother, pgridy);

        vgrid[i]->SetLineColor(2);
        vgrid[i]->SetLineStyle(10);
        vgrid[i]->SetLineWidth(1);
        vgrid[i]->SetFillStyle(0);
        vgrid[i]->SetFillColor(0);

        pgrid[i]->SetLineColor(2);
        pgrid[i]->SetLineStyle(10);
        pgrid[i]->SetLineWidth(1);
        pgrid[i]->SetFillStyle(0);
        pgrid[i]->SetFillColor(0);

        vgrid[i]->Draw("C");
        pgrid[i]->Draw("C");
    }

    // h[1] settings
    //Slice->SetLineColor(kBlue + 1);
    //Slice->SetLineWidth(8);
    Slice->SetMarkerSize(0.6);

    // Y axis h[1] plot settings

    c->Update();
    c->SaveAs(figurename);
}

void CorrelationTool::RandomTagAndProbe()
{
 for(int i=1;i<=bkg_fit->GetNbinsX();i++)
  for(int j=1;j<=bkg_fit->GetNbinsY();j++)
  {
   //EW bkg in tag-and-probe denominator!
   double sigma = (bkg_fit->GetBinContent(i,j) - bkg_MC->GetBinContent(i,j))/2;
   double content = (bkg_fit->GetBinContent(i,j) + bkg_MC->GetBinContent(i,j))/2;
   double bkg_use = myRandom->Gaus(content,sigma);
   
   double deno = Eff_TagAndProbe_deno->GetBinContent(i,j)-bkg_use;
   double nume = Eff_TagAndProbe_nume->GetBinContent(i,j);
   double eff_MC = Eff_TagAndProbe_MC->GetBinContent(i,j);
   
   //calculate tag-and-probe efficiency
   Eff_TagAndProbe_scale->SetBinContent(i,j,nume/deno/eff_MC);
  }
}

void CorrelationTool::ReSet()
{
 T_Plot_MC_Forward_B->Reset("M");
 T_Plot_MC_Backward_B->Reset("M");
 T_Plot_MC_Forward_O->Reset("M");
 T_Plot_MC_Backward_O->Reset("M");

 T_Plot_EWBKG_Forward_B->Reset("M");
 T_Plot_EWBKG_Backward_B->Reset("M");
 T_Plot_EWBKG_Forward_O->Reset("M");
 T_Plot_EWBKG_Backward_O->Reset("M");
 T_Plot_EWBKG_Forward_N->Reset("M");
 T_Plot_EWBKG_Backward_N->Reset("M");
 
 T_Plot_QCDBKG_B->Reset("M");
 T_Plot_QCDBKG_O->Reset("M");
 T_Plot_QCDBKG_N->Reset("M");

 T_num_true_reco->Reset("M");
 T_num_true->Reset("M");
 PassTruePassReco_TrueZRapidity->Reset("M");

 for(int j=0;j<9;j++)//muon_eta
  for(int k=0;k<9;k++)//anti_muon_eta
   for(int w=0;w<3;w++)//muon_Pt
    for(int v=0;v<3;v++)//anti_muon_Pt
    {
     num_true_reco[j][k][w][v] = (TH2D *)num_true_reco_keep[j][k][w][v]->Clone();
     num_true[j][k][w][v] = (TH1D *)num_true_keep[j][k][w][v]->Clone();
     MC_Zrapidity_foreff[j][k][w][v] = (TH1D *)MC_Zrapidity_foreff_keep[j][k][w][v]->Clone();
    }
}

#endif
