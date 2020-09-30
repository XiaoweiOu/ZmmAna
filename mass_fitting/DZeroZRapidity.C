#include "State.h"
#include "/lustre/AtlUser/xwou/include/plot/Figure.h"

BKGFittingPackage *PackageBKGFitting[100];
TMinuit *Minuit_Fitter[100];

int main(int argc, char **argv)
{
    fstream fit_result("fit_result.txt",ios::out);
    TFile *DataFile = new TFile("../muon_eff/result/data_result.root");
    TFile *BKGFile = new TFile("../muon_eff/EW_norm.root");
    TFile *MCFile = new TFile("../muon_eff/result/MC_0_result.root");

    TFile *WriteFile = new TFile("EfficiencyResult.root", "RECREATE");

    char name[100];

    TH1D *DataMass[100];
    TH1D *MCMass[100];
    TH1D *BKGMass[100];
    TF1 *SignalFunction = new TF1("SignalFunction", Convolution_Gaus_BKGFitting, 74, 110, 4);
    TF1 *BKGFunction = new TF1("BKGFunction", BackgroudFunction_DZero, 74, 110, 4);

    for (int i = 0; i < 9; i++)
    // For Eta Bin
    {
        for (int j = 0; j < 3; j++)
        // For Pt Bin
        {
            int FitterIndex = 3 * j + i;

            sprintf(name, "Id_ZMass_LeptonEta%d_Pt%d", i, j);
            DataMass[FitterIndex] = (TH1D *)DataFile->Get(name);
            MCMass[FitterIndex] = (TH1D *)MCFile->Get(name);
 	    BKGMass[FitterIndex] = (TH1D *)BKGFile->Get(name);
            fit_result<<name<<":  ";

            PackageBKGFitting[FitterIndex] = new BKGFittingPackage(DataMass[FitterIndex], MCMass[FitterIndex], BKGMass[FitterIndex], FitterIndex);
            PackageBKGFitting[FitterIndex]->SetSignalFunction(SignalFunction);

   	    //initial plots!
	    int BinNumber;
            BinNumber = DataMass[FitterIndex]->GetNbinsX();
            double *BinSet = new double[BinNumber+1];
            for(int ii=0;ii<BinNumber;ii++)
             BinSet[ii] = DataMass[FitterIndex]->GetXaxis()->GetBinLowEdge(ii+1);
            BinSet[BinNumber] = DataMass[FitterIndex]->GetXaxis()->GetBinUpEdge(BinNumber);

            sprintf(name, "TagProbe_Data_Signal_Mass_ProbeEtaBin%d_LeptonPtBin%d", i, j);
            PackageBKGFitting[FitterIndex]->DataSignal_Hist = new TH1D(name,name,BinNumber,BinSet);
            sprintf(name, "TagProbe_Data_BKG_Mass_ProbeEtaBin%d_LeptonPtBin%d", i, j);
            PackageBKGFitting[FitterIndex]->DataBKG_Hist = new TH1D(name,name,BinNumber,BinSet);

            //fitting!!!
            DZeroEfficiencyBackground_Fit_2(PackageBKGFitting[FitterIndex],fit_result);

            //draw plots!!!
            sprintf(name, "./figure/Mass_ProbeEtaBin%d_LeptonPtBin%d.eps", i, j);
            Figure *result = new Figure(name, "M_{ll}/GeV", "Number of Events");
            result->SetMode("HSTACK");         

	    sprintf(name, "Data_Mass_ProbeEtaBin%d_LeptonPtBin%d", i, j);
            result->SetInputFigure(1,DataMass[FitterIndex], name);
	    sprintf(name, "BKG_Mass_ProbeEtaBin%d_LeptonPtBin%d", i, j);
            result->SetInputFigure(2,PackageBKGFitting[FitterIndex]->DataBKG_Hist, name);
	    sprintf(name, "Signal_Mass_ProbeEtaBin%d_LeptonPtBin%d", i, j);
            result->SetInputFigure(3,PackageBKGFitting[FitterIndex]->DataSignal_Hist, name);

	    result->SetNotNorm();
            result->SetXrange(74, 110);
            result->SetRatiorange(0.4, 1.6);
            result->SetHeaderName("D0 Preliminary, 8.6 fb^{-1}");
            result->DrawFigure();
            delete result;
        }
    }

    WriteFile->Write();
    WriteFile->Close();
}
