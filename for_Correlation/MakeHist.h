#ifndef MAKEHIST_HEADER
#define MAKEHIST_HEADER

#include"State.h"

class MakeHist
{
 public:
 //file for histgram saving
 TFile *result;

  //for Correlation calculation
  TH1D *Forward_Both_muon_eta_Pt[9][9][3][3];//muon_eta:anti_muon_eta:muon_Pt:anti_muon_Pt
  TH1D *Backward_Both_muon_eta_Pt[9][9][3][3];
  TH1D *Forward_Oppo_muon_eta_Pt[9][9][3][3];
  TH1D *Backward_Oppo_muon_eta_Pt[9][9][3][3];

  TH1D *Forward_Zrapidity_eta_Pt[9][9][3][3];
  TH1D *Backward_Zrapidity_eta_Pt[9][9][3][3];

  //about muon eta
  //Forward_Zrapidity_eta
  //00
  //10 11
  //20 21 22
  //30 31 32 33
  //40 41 42 43 44
  //50 51 52 53 54 55
  //60 61 62 63 64 65 66
  //70 71 72 73 74 75 76 77
  //80 81 82 83 84 85 86 87 88
  //
  //Backward_Zrapidity_eta
  //00 01 02 03 04 05 06 07 08
  //   11 12 13 14 15 16 17 18
  //      22 23 24 25 26 27 28
  //         33 34 35 36 37 38
  //            44 45 46 47 48
  //               55 56 57 58
  //                  66 67 68
  //                     77 78
  //                        88

  TH1D *num_true_eta_Pt[9][9][3][3];
  TH2D *num_true_reco_eta_Pt[9][9][3][3];

 //function
 void BookHist(const char *fName);
 void SaveHist();
};

#endif
