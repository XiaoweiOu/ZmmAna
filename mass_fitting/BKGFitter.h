#ifndef BKGFITTER_HEADER
#define BKGFITTER_HEADER

#include "State.h"

//package used for template fitting
class BKGFittingPackage
{
public:
    TH1D *Datahist;
    TH1D *Signalhist;
    TF1 *SignalFunction;
    TF1 *BKGFunction;

    TH1D *DataSignal_Hist;
    TH1D *DataBKG_Hist;

    TH1D *FixedBKG;

    int FitterIndex;

    int CalledTimes = 0;
    double First_Chi2 = -999;//original chi square
    double Min_Chi2 = 2e8;//minimum chi2
    double norm_signal = 4559374.5;

    double Parameter[10];
    double Parameter_Err[10];

    BKGFittingPackage(TH1D *datahist, TF1 *sig, TF1 *bkg, int index);
    BKGFittingPackage(TH1D *datahist, TH1D *signalhist, TH1D *fixedbkg, int index);
    virtual void SetSignalHist(TH1D *signalhist);
    virtual void SetSignalFunction(TF1 *signalfunction);
    virtual ~BKGFittingPackage();
};

Double_t Convolution_Gaus_BKGFitting(Double_t *x, Double_t *par);//x:variable vector
Double_t BackgroudFunction_DZero(Double_t *x, Double_t *par);//par:parameter vector

void Fit_DZeroEfficiencyBackground_Function(int &npar, double *gin, double &f, double *par, int iflag);
void DZeroEfficiencyBackground_Fit(void *ptr,std::fstream &str);

void Fit_DZeroEfficiencyBackground_Function_2(int &npar, double *gin, double &f, double *par, int iflag);
void DZeroEfficiencyBackground_Fit_2(void *ptr,std::fstream &str);
#endif
