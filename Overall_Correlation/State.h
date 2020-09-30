#ifndef STATE_HEADER
#define STATE_HEADER

using namespace std;

// ROOT Header
#include "TChain.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TMinuit.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include "TLegend.h"

// Stream Header
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

// Multi Thread
#include <pthread.h>
#include <unistd.h>

#include "CorrelationTool.h"

extern CorrelationTool *ZRapidityOverall;
extern TMinuit *myMinuit;

#endif
