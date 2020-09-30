#ifndef BKGFITTER_SOURCE
#define BKGFITTER_SOURCE

#include "State.h"

extern BKGFittingPackage *PackageBKGFitting[100];

BKGFittingPackage::BKGFittingPackage(TH1D *datahist, TF1 *sig, TF1 *bkg, int index)
{
    //the first constructor:use signal and background functions!
    Datahist = datahist;
    SignalFunction = sig;
    BKGFunction = bkg;
    FitterIndex = index;
}

BKGFittingPackage::BKGFittingPackage(TH1D *datahist, TH1D *signalhist, TH1D *fixedbkg, int index)
{
    //the second constructor:use signal and background histagrams!
    Datahist = datahist;
    Signalhist = signalhist;
    FixedBKG = fixedbkg;
    FitterIndex = index;
}

void BKGFittingPackage::SetSignalHist(TH1D *signalhist)
{
    Signalhist = signalhist;
}

void BKGFittingPackage::SetSignalFunction(TF1 *sig)
{
    SignalFunction = sig;
}

BKGFittingPackage::~BKGFittingPackage()
{
}

Double_t Convolution_Gaus_BKGFitting(Double_t *x, Double_t *par)
{
    double sum = 0;

    BKGFittingPackage *Package = PackageBKGFitting[(int)(par[3])];

    for (int ibin = 1; ibin <= (Package->Signalhist->GetNbinsX()); ibin++)
    {
        double inum = Package->Signalhist->GetBinContent(ibin);
        double bin_low = Package->Signalhist->GetXaxis()->GetBinLowEdge(ibin);
        double bin_up = Package->Signalhist->GetXaxis()->GetBinUpEdge(ibin);
        double mi = (bin_low + bin_up) / 2;
        double di = bin_up - bin_low;
        double ProGaus = TMath::Gaus(x[0] - mi, par[1], par[2]);
        sum = sum + ProGaus * di * inum;
    }

    double SignalValue;
    SignalValue = sum * par[0];
    return SignalValue;
}

Double_t BackgroudFunction_DZero(Double_t *x, Double_t *par)
{
    double val = par[3] * TMath::Exp(par[0] * (x[0] - 91.18)) * TMath::Erfc(par[1] * (par[2] - x[0]));

    if (val == val)
        return val;
    else
        return 0;
}

void Fit_DZeroEfficiencyBackground_Function(int &npar, double *gin, double &f, double *par, int iflag)
{
    BKGFittingPackage *Package = (BKGFittingPackage *)Minuit_Fitter[(int)(par[3])]->GetObjectFit();

    Package->CalledTimes = Package->CalledTimes + 1;

    //Assign the values of the parameters to be fitted to the parameters in the function
    Package->SignalFunction->SetParameter(0, par[0]);
    Package->SignalFunction->SetParameter(1, par[1]);
    Package->SignalFunction->SetParameter(2, par[2]);
    Package->SignalFunction->SetParameter(3, par[3]);

    Package->BKGFunction->SetParameter(0, par[4]);
    Package->BKGFunction->SetParameter(1, par[5]);
    Package->BKGFunction->SetParameter(2, par[6]);
    Package->BKGFunction->SetParameter(3, par[7]);

    double Chi2 = 0;
    for (int ibin = 0; ibin < (Package->Datahist->GetNbinsX()); ibin++)
    {
        double DataNum = Package->Datahist->GetBinContent(ibin + 1);
        double DataNumErr = Package->Datahist->GetBinError(ibin + 1);
        double binx = Package->Datahist->GetBinCenter(ibin + 1);
        double TruthNum = Package->SignalFunction->Eval(binx) + Package->BKGFunction->Eval(binx);

        if (DataNumErr == 0)
            continue;

        Chi2 = Chi2 + (DataNum - TruthNum) * (DataNum - TruthNum) / (DataNumErr * DataNumErr);

        cout << "Data Number: " << DataNum << endl
             << "BKG Number: " << Package->BKGFunction->Eval(binx) << endl
             << "Signal Number: " << Package->SignalFunction->Eval(binx) << endl
             << "BKG+Signal: "<< TruthNum << endl << endl;
    } 

    f = Chi2;

    cout << endl << endl;

    //information for this calling
    cout << "Called Times: " << Package->CalledTimes << endl
         << "Signal Parameter:  " << par[0] << "   " << par[1] << "   " << par[2] << endl
         << "BKG Parameter:  " << par[4] << "   " << par[5] << "   " << par[6] << "   " << par[7] << endl
         << "Chi2: " << Chi2 << "   Min_Chi2: " << Package->Min_Chi2 << endl << endl;

    //update result!
    if (Chi2 < Package->Min_Chi2)
    {
        Package->Min_Chi2 = Chi2;
        for (int ibin = 0; ibin < Package->Datahist->GetNbinsX(); ibin++)
        {
            double DataNumErr = Package->Datahist->GetBinError(ibin + 1);
            double binx = Package->Datahist->GetBinCenter(ibin + 1);

            Package->DataSignal_Hist->SetBinContent(ibin + 1, Package->SignalFunction->Eval(binx));
            Package->DataSignal_Hist->SetBinError(ibin + 1, 0);
            Package->DataBKG_Hist->SetBinContent(ibin + 1, Package->BKGFunction->Eval(binx));

            Package->DataBKG_Hist->SetBinError(ibin + 1, 0);
        }
    }
    if (Package->First_Chi2 < 0)
        Package->First_Chi2 = Chi2;
}

void DZeroEfficiencyBackground_Fit(void *ptr, fstream &str)
{
    BKGFittingPackage *Package = (BKGFittingPackage *)ptr;

    int FitterIndex = Package->FitterIndex;

    Minuit_Fitter[FitterIndex] = new TMinuit(8);

    Minuit_Fitter[FitterIndex]->SetMaxIterations(1000000);
    Minuit_Fitter[FitterIndex]->SetFCN(Fit_DZeroEfficiencyBackground_Function);
    Minuit_Fitter[FitterIndex]->SetObjectFit((TObject *)ptr);
    Minuit_Fitter[FitterIndex]->SetPrintLevel(1);
    Minuit_Fitter[FitterIndex]->SetErrorDef(1.0);
    Minuit_Fitter[FitterIndex]->mncler();

    Int_t ierflg = 0;
    Double_t arglist[10];
    arglist[0] = 1.0;
    Minuit_Fitter[FitterIndex]->mnexcm("SET ERR", arglist, 1, ierflg);

    arglist[0] = 2;
    Minuit_Fitter[FitterIndex]->mnexcm("SET STR", arglist, 1, ierflg);

    Minuit_Fitter[FitterIndex]->mnparm(0, "Signal-Norm-Parameter", 0.0149151, 0.5, 0, 10, ierflg);
    Minuit_Fitter[FitterIndex]->mnparm(1, "Gaus-Scale-Parameter", 2.79, 2, -10, 10, ierflg);
    Minuit_Fitter[FitterIndex]->mnparm(2, "Gaus-Resolution-Parameter", 5.78, 0.5, 0, 10, ierflg);
    Minuit_Fitter[FitterIndex]->mnparm(3, "Fixed Index", FitterIndex + 0.02, 0.01, FitterIndex + 0.01, FitterIndex + 0.03, ierflg);
     
    Minuit_Fitter[FitterIndex]->FixParameter(3);

    Minuit_Fitter[FitterIndex]->mnparm(4, "BKGParameter-P0", -0.1, 0.05, -1, 1, ierflg);
    Minuit_Fitter[FitterIndex]->mnparm(5, "BKGParameter-P1", 0.01, 0.01, -1, 0.3, ierflg);
    Minuit_Fitter[FitterIndex]->mnparm(6, "BKGParameter-P2", 90, 2, 70, 110, ierflg);
    Minuit_Fitter[FitterIndex]->mnparm(7, "BKGParameter-P3", 0, 0.5, 0, 10, ierflg); 

    arglist[0] = 1000; // number of function calls
    arglist[1] = 0.1;  // tolerance(x10^3)
    Minuit_Fitter[FitterIndex]->mnexcm("SIMPLEX", arglist, 2, ierflg);
    Minuit_Fitter[FitterIndex]->mnexcm("MIGRAD", arglist, 2, ierflg);
    Minuit_Fitter[FitterIndex]->mnexcm("HESSE", arglist, 1, ierflg);

    str << Package->DataBKG_Hist->Integral(15,50)<<endl;

    double Par[8], ParErr[8];
    for(int i=0;i<8;i++)Minuit_Fitter[FitterIndex]->GetParameter(i, Par[i], ParErr[i]);
    str << "Signal Parameter:  " << Par[0] << "   " << Par[1] << "   " << Par[2] << endl
        << "BKG Parameter:  " << Par[4] << "   " << Par[5] << "   " << Par[6] << "   " << Par[7] << endl<<endl;

    delete Minuit_Fitter[FitterIndex];
}

//bkg use histgram!!!
void DZeroEfficiencyBackground_Fit_2(void *ptr, fstream &str)
{
    BKGFittingPackage *Package = (BKGFittingPackage *)ptr;

    int FitterIndex = Package->FitterIndex;

    Minuit_Fitter[FitterIndex] = new TMinuit(5);

    Minuit_Fitter[FitterIndex]->SetMaxIterations(1000000);
    Minuit_Fitter[FitterIndex]->SetFCN(Fit_DZeroEfficiencyBackground_Function_2);
    Minuit_Fitter[FitterIndex]->SetObjectFit((TObject *)ptr);
    Minuit_Fitter[FitterIndex]->SetPrintLevel(1);
    Minuit_Fitter[FitterIndex]->SetErrorDef(1.0);
    Minuit_Fitter[FitterIndex]->mncler();

    Int_t ierflg = 0;
    Double_t arglist[10];
    arglist[0] = 1.0;
    Minuit_Fitter[FitterIndex]->mnexcm("SET ERR", arglist, 1, ierflg);

    arglist[0] = 2;
    Minuit_Fitter[FitterIndex]->mnexcm("SET STR", arglist, 1, ierflg);

    Minuit_Fitter[FitterIndex]->mnparm(0, "Signal-Norm-Parameter", 0.0149151, 0.5, 0, 10, ierflg);
    Minuit_Fitter[FitterIndex]->mnparm(1, "Gaus-Scale-Parameter", 2.79, 2, -10, 10, ierflg);
    Minuit_Fitter[FitterIndex]->mnparm(2, "Gaus-Resolution-Parameter", 5.78, 0.5, 0, 10, ierflg);
    Minuit_Fitter[FitterIndex]->mnparm(3, "Fixed Index", FitterIndex + 0.02, 0.01, FitterIndex + 0.01, FitterIndex + 0.03, ierflg);

    Minuit_Fitter[FitterIndex]->FixParameter(3);

    Minuit_Fitter[FitterIndex]->mnparm(4, "BKG-Norm", 1, 0.5, 0, 50, ierflg);

    arglist[0] = 1000; // number of function calls
    arglist[1] = 0.1;  // tolerance(x10^3)
    Minuit_Fitter[FitterIndex]->mnexcm("SIMPLEX", arglist, 2, ierflg);
    Minuit_Fitter[FitterIndex]->mnexcm("MIGRAD", arglist, 2, ierflg);
    Minuit_Fitter[FitterIndex]->mnexcm("HESSE", arglist, 1, ierflg);

    str << Package->DataBKG_Hist->Integral(15,50)<<endl;

    double Par[5], ParErr[5];
    for(int i=0;i<5;i++)Minuit_Fitter[FitterIndex]->GetParameter(i, Par[i], ParErr[i]);
    str << "Signal Parameter:  " << Par[0] << "   " << Par[1] << "   " << Par[2] << endl
        << "BKG Parameter:  " << Par[4] << endl<<endl;

    delete Minuit_Fitter[FitterIndex];
}

void Fit_DZeroEfficiencyBackground_Function_2(int &npar, double *gin, double &f, double *par, int iflag)
{
    BKGFittingPackage *Package = (BKGFittingPackage *)Minuit_Fitter[(int)(par[3])]->GetObjectFit();

    Package->CalledTimes = Package->CalledTimes + 1;

    //Assign the values of the parameters to be fitted to the parameters in the function
    Package->SignalFunction->SetParameter(0, par[0]);
    Package->SignalFunction->SetParameter(1, par[1]);
    Package->SignalFunction->SetParameter(2, par[2]);
    Package->SignalFunction->SetParameter(3, par[3]);

    double Chi2 = 0;
    for (int ibin = 0; ibin < (Package->Datahist->GetNbinsX()); ibin++)
    {
        double DataNum = Package->Datahist->GetBinContent(ibin + 1);
        double DataNumErr = Package->Datahist->GetBinError(ibin + 1);
        double binx = Package->Datahist->GetBinCenter(ibin + 1);
        double TruthNum = Package->SignalFunction->Eval(binx) + Package->FixedBKG->GetBinContent(ibin+1)*par[4];

        if (DataNumErr == 0)
            continue;

        Chi2 = Chi2 + (DataNum - TruthNum) * (DataNum - TruthNum) / (DataNumErr * DataNumErr);
        cout << "Data Number: " << DataNum << endl
             << "BKG Number: " << Package->FixedBKG->GetBinContent(ibin+1)*par[4] << endl
             << "Signal Number: " << Package->SignalFunction->Eval(binx) << endl
             << "BKG+Signal: "<< TruthNum << endl << endl;
    }

    f = Chi2;

    cout << endl << endl;

    //information for this calling
    cout << "Called Times: " << Package->CalledTimes << endl
         << "Signal Parameter:  " << par[0] << "   " << par[1] << "   " << par[2] << endl
         << "BKG Parameter:  " << par[4] << endl
         << "Chi2: " << Chi2 << "   Min_Chi2: " << Package->Min_Chi2 << endl << endl;

    //update result!
    if (Chi2 < Package->Min_Chi2)
    {
        Package->Min_Chi2 = Chi2;
        for (int ibin = 0; ibin < Package->Datahist->GetNbinsX(); ibin++)
        {
            double DataNumErr = Package->Datahist->GetBinError(ibin + 1);
            double binx = Package->Datahist->GetBinCenter(ibin + 1);

            Package->DataSignal_Hist->SetBinContent(ibin + 1, Package->SignalFunction->Eval(binx));
            Package->DataSignal_Hist->SetBinError(ibin + 1, 0);
            Package->DataBKG_Hist->SetBinContent(ibin + 1, Package->FixedBKG->GetBinContent(ibin+1)*par[4]);

            Package->DataBKG_Hist->SetBinError(ibin + 1, 0);
        }
    }
    if (Package->First_Chi2 < 0)
        Package->First_Chi2 = Chi2;
}

#endif
