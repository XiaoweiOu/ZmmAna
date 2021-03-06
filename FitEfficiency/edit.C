#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "TH1F.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "TH3F.h"
#include <TRandom3.h>
#include <TMinuit.h>
#include <TApplication.h>
#include "TEnv.h"
#include <TComplex.h>
#include "TH2D.h"
#include "TLegend.h"
#include <TGraphErrors.h>
#include <TF1.h>
#include <iomanip>
#include "TMatrixD.h"
#include <string>
#include <sstream>

using namespace std;
vector<double> num_data;
vector<double> err_data;
vector<double> num_mc;
vector<double> err_mc;
vector<int> index_trigger_1;
vector<int> index_trigger_2;
vector<int> index_cut_1;
vector<int> index_cut_2;
vector<int> ZYbin;
vector<int> turn_1;
vector<int> turn_2;
vector<int> index_trigger_1_mc;
vector<int> index_trigger_2_mc;
vector<int> index_cut_1_mc;
vector<int> index_cut_2_mc;
vector<int> ZYbin_mc;
vector<int> turn_1_mc;
vector<int> turn_2_mc;

void fit_trigger_eta(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 double chi2_sum=0;
 double chi2_cal=0;

 ofstream outfile;
  outfile.open("record_trigger.txt",ios::app);

 outfile<<"Start a fitting !"<<endl;
 double data_calculate;
 double ratio_1, ratio_2;
 double obs_calculate;
 double obs_data;
 double obs_err;
 double err_1,err_2;

 double n_count=0;
 for(int ii=0;ii<num_data.size();ii++)
  {
   if(ZYbin[turn_1[ii]]<2 && ZYbin[turn_1[ii]]>41) continue;
   if(ZYbin[turn_2[ii]]<2 && ZYbin[turn_2[ii]]>41) continue;

//   if(index_trigger_1[turn_1[ii]]<10 || index_trigger_1[turn_1[ii]]>35) continue;
//   if(index_trigger_1[turn_2[ii]]<10 || index_trigger_1[turn_2[ii]]>35) continue;
//   if(index_trigger_2[turn_1[ii]]<10 || index_trigger_2[turn_1[ii]]>35) continue;
//   if(index_trigger_2[turn_2[ii]]<10 || index_trigger_2[turn_2[ii]]>35) continue;

/*
   if( (index_trigger_1[turn_1[ii]]>=10 && index_trigger_1[turn_1[ii]]<=35) &&
       (index_trigger_1[turn_2[ii]]>=10 && index_trigger_1[turn_2[ii]]<=35) &&
       (index_trigger_2[turn_1[ii]]>=10 && index_trigger_2[turn_1[ii]]<=35) &&
       (index_trigger_2[turn_2[ii]]>=10 && index_trigger_2[turn_2[ii]]<=35) )
    continue;
*/
   if(num_data[turn_1[ii]]==0) continue;
   if(num_mc[turn_1[ii]]==0) continue;

   if(err_data[turn_1[ii]]/num_data[turn_1[ii]] > 0.05) continue;
   if(err_data[turn_2[ii]]/num_data[turn_2[ii]] > 0.05) continue;
   if(err_mc[turn_1[ii]]/num_mc[turn_1[ii]] > 0.05) continue;
   if(err_mc[turn_2[ii]]/num_mc[turn_2[ii]] > 0.05) continue;

   if((index_trigger_1[turn_1[ii]]+index_trigger_2[turn_1[ii]])/2.-ZYbin[turn_1[ii]] >= 2 ) continue; 
   if((index_trigger_1[turn_2[ii]]+index_trigger_2[turn_2[ii]])/2.-ZYbin[turn_2[ii]] >= 2 ) continue;

   if(fabs(index_trigger_1[turn_1[ii]]-index_trigger_2[turn_1[ii]]) >= 10 ) continue; 
   if(turn_1[ii]==turn_2[ii]) continue;
//   if(index_trigger_1[turn_1[ii]]<10 || index_trigger_1[turn_1[ii]]>35) continue;
//   if(index_trigger_1[turn_2[ii]]<10 || index_trigger_1[turn_2[ii]]>35) continue;

 
   if(turn_1[ii]!=ii) cout<<" !!! BIG ERROR !!!! "<<turn_1[ii]<<"   "<<ii<<endl; 
   ratio_1 = num_data[turn_1[ii]] / num_mc[turn_1[ii]];
   err_1 = ratio_1 * sqrt(err_mc[turn_1[ii]]*err_mc[turn_1[ii]]/(num_mc[turn_1[ii]]*num_mc[turn_1[ii]]) + err_data[turn_1[ii]]*err_data[turn_1[ii]]/(num_data[turn_1[ii]]*num_data[turn_1[ii]]));
   ratio_2 = num_data[turn_2[ii]] / num_mc[turn_2[ii]];
   err_2 = ratio_2 * sqrt(err_mc[turn_2[ii]]*err_mc[turn_2[ii]]/(num_mc[turn_2[ii]]*num_mc[turn_2[ii]]) + err_data[turn_2[ii]]*err_data[turn_2[ii]]/(num_data[turn_2[ii]]*num_data[turn_2[ii]]));
   obs_data = ratio_1/ratio_2;
   obs_err = sqrt((err_1/ratio_1)*(err_1/ratio_1) + (err_2/ratio_2)*(err_2/ratio_2))*obs_data;
   obs_calculate = ( ( 1-(1-par[index_trigger_1[turn_1[ii]]])*(1-par[index_trigger_2[turn_1[ii]]]) )
       * par[index_cut_1[turn_1[ii]]] * par[index_cut_2[turn_1[ii]]] ) / 
       ( ( 1-(1-par[index_trigger_1[turn_2[ii]]])*(1-par[index_trigger_2[turn_2[ii]]]) )
       * par[index_cut_1[turn_2[ii]]] * par[index_cut_2[turn_2[ii]]] );
   chi2_cal = (obs_data-obs_calculate)*(obs_data-obs_calculate)/(obs_err*obs_err);
   chi2_sum = chi2_sum + chi2_cal;
//   outfile<<"  chi2 for constraint "<<ii<<"  "<<chi2_cal<<"  "<<index_trigger_1[turn_1[ii]]<<"  "<<index_trigger_2[turn_1[ii]]<<"  "<<index_trigger_1[turn_2[ii]]<<"  "<<index_trigger_2[turn_2[ii]]<<endl;
//   outfile<<"  chi2 for constraint: "<<ii<<"  "<<chi2_cal<<"  "<<ratio_1<<"  "<<err_1<<"  "<<ratio_2<<"  "<<err_2<<"  "<<obs_data<<"  "<<obs_err<<endl;
   n_count++;
  }

 outfile<<" *** total chi2: "<<chi2_sum<<"   "<<n_count<<endl;
 f = chi2_sum;
 outfile.close();

}

void set_trigger_eta()
{      
 double skip;
 double skip_ZY;
 double getvalue;
 int countings=0;
 int start_count;
 int end_count;
 int index_reference;
 int eta1_reference;
 int eta2_reference;

 ifstream infile;
  infile.open("Inputfiles/trigger_selection_data.txt",ios::in);
 while(infile>>skip_ZY)
  {
   start_count = 0;
   while(infile>>skip)
    {
     if(skip!=999111)
      {
       ZYbin.push_back((int)skip_ZY);
       turn_1.push_back((int)skip);
       infile>>getvalue;
       index_trigger_1.push_back((int)getvalue);
       index_cut_1.push_back((int)getvalue+44);
       infile>>getvalue;
       index_trigger_2.push_back((int)getvalue);
       index_cut_2.push_back((int)getvalue+44);
       infile>>getvalue;
       num_data.push_back(getvalue);
       infile>>getvalue;
       err_data.push_back(getvalue);
       countings = countings+1;
       start_count = start_count+1;
      }
     if(skip==999111)
      {
       infile>>skip;
       infile>>index_reference;
       infile>>eta1_reference;
       infile>>eta2_reference;
       break;
      }
    }
   for(int ibin=0;ibin<start_count;ibin++)
    {
     turn_2.push_back((int)index_reference);
    }
  }
 infile.close();

 countings = 0;
  infile.open("Inputfiles/trigger_selection_mc.txt",ios::in);
 while(infile>>skip_ZY)
  {
   start_count = 0;
   while(infile>>skip)
    {
     if(skip!=999111)
      {
       ZYbin_mc.push_back((int)skip_ZY);
       turn_1_mc.push_back((int)skip);
       infile>>getvalue;
       index_trigger_1_mc.push_back((int)getvalue);
       index_cut_1_mc.push_back((int)getvalue+44);
       infile>>getvalue;
       index_trigger_2_mc.push_back((int)getvalue);
       index_cut_2_mc.push_back((int)getvalue+44);
       infile>>getvalue;
       num_mc.push_back(getvalue);
       infile>>getvalue;
       err_mc.push_back(getvalue);
       countings = countings+1;
       start_count = start_count+1;
      }
     if(skip==999111)
      {
       infile>>skip;
       infile>>index_reference;
       infile>>eta1_reference;
       infile>>eta2_reference;
       break;
      }
    }
   for(int ibin=0;ibin<start_count;ibin++)
    {
     turn_2_mc.push_back((int)index_reference);
    }
  }
 infile.close();

 //checks!!
 for(int ii=0;ii<num_data.size();ii++)
  {
   if(index_trigger_1[ii] != index_trigger_1_mc[ii]) cout<<"Fuck!: index trigger 1:  "<<index_trigger_1[ii]<<"  "<<index_trigger_1_mc[ii]<<endl;
   if(index_trigger_2[ii] != index_trigger_2_mc[ii]) cout<<"Fuck!: index trigger 2:  "<<index_trigger_2[ii]<<"  "<<index_trigger_2_mc[ii]<<endl;
   if(index_cut_1[ii] != index_cut_1_mc[ii]) cout<<"Fuck!: index cut 1:  "<<index_cut_1[ii]<<"  "<<index_cut_1_mc[ii]<<endl;
   if(index_cut_2[ii] != index_cut_2_mc[ii]) cout<<"Fuck!: index cit 2:  "<<index_cut_2[ii]<<"  "<<index_cut_2_mc[ii]<<endl;
   if(ZYbin[ii]!=ZYbin_mc[ii]) cout<<"Fuck!: ZY bin:  "<<ZYbin[ii]<<"  "<<ZYbin_mc[ii]<<endl;
   if(turn_1[ii]!=turn_1_mc[ii]) cout<<"Fuck!: turn 1:  "<<turn_1[ii]<<"  "<<turn_1_mc[ii]<<endl;
//   if(turn_2[ii]!=turn_2_mc[ii]) cout<<"Fuck!: turn 2:  "<<turn_2[ii]<<"  "<<turn_2_mc[ii]<<endl;
  }

//*****************************************************//
//********* Randomly Selecting Starting Point *********//
//*****************************************************//

  double tmptrigger[44] = {0.971846, 0.956062, 0.72655, 0.652283, 0.673568, 0.615904, 0.681824, 0.930574, 0.82709, 0.812831, 0.838218, 0.982524, 0.985806, 0.784771, 0.861271, 0.969495, 0.899563, 0.749568, 0.861428, 0.661989, 0.899086, 0.956937, 0.984523, 0.610716, 0.603355, 0.716601, 0.642578, 0.759498, 0.719481, 0.922915, 0.862564, 0.850838, 0.923925, 0.96317, 0.94887, 0.822559, 0.985859, 0.935968, 0.889474, 0.620195, 0.85699, 0.922494, 0.886981, 0.972326};
  double tmpselection[44] = {1.08592, 1.07803, 0.963275, 0.926141, 0.936784, 0.907952, 0.940912, 1.06529, 1.01355, 1.00642, 1.01911, 1.09126, 1.0929, 0.992385, 1.03064, 1.08475, 1.04978, 0.974784, 1.03071, 0.930995, 1.04954, 1.07847, 1.09226, 0.905358, 0.901678, 0.9583, 0.921289, 0.979749, 0.959741, 1.06146, 1.03128, 1.02542, 1.06196, 1.08158, 1.07444, 1.01128, 1.09293, 1.06798, 1.04474, 0.910098, 1.0285, 1.06125, 1.04349, 1.08616};

  double setpar_trigger[44];
  double setpar_selection[44];
  TRandom3 *MyR = new TRandom3(0);

  double chi2_threshold = 800;
  double chi2_sum;
  for(int iloop=0;iloop<1000000;iloop++)
   {
    chi2_sum = 0;
   }



//*****************************************************//
//********* Randomly Selecting Starting Point *********//
//*****************************************************//

       TMinuit *myMinuit = new TMinuit(88);
       myMinuit->SetMaxIterations(100000);
       myMinuit->SetFCN(fit_trigger_eta);
       myMinuit->SetPrintLevel(3);
       myMinuit->SetErrorDef(1.0);//1 for chi2, 0.5 for likelihood
       myMinuit->mncler();
       
       Int_t ierflg;
       Double_t arglist[10];
       arglist[0] = 1.0;
       myMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
       char name[50];
       double setmean;
 
       for(int ibin=0;ibin<44;ibin++)
        {
         sprintf(name, "%s%d", "scale_trigger_",ibin);
        if(ibin<15 || ibin>30) 
         {
          double settrigger = MyR->Gaus(1, 0.03)*tmptrigger[ibin];
          if(settrigger<1)
           myMinuit->mnparm(ibin, name, settrigger, 0.01, 0, 1, ierflg);
          else
           myMinuit->mnparm(ibin, name, 1, 0.01, 0, 1, ierflg);
//          myMinuit->FixParameter(ibin);
         }
         if(ibin>=15 && ibin<=30)
          {
          double settrigger = MyR->Gaus(1, 0.03)*tmptrigger[ibin];
          if(settrigger<1)
           myMinuit->mnparm(ibin, name, settrigger, 0.01, 0, 1, ierflg);
          else
           myMinuit->mnparm(ibin, name, 1, 0.01, 0, 1, ierflg);

//           myMinuit->FixParameter(ibin);
          }
        }
       for(int ibin=0;ibin<44;ibin++)
        {
         sprintf(name, "%s%d", "scale_cut_",ibin);
         if(ibin<15 || ibin>35) 
          myMinuit->mnparm(ibin+44, name, MyR->Gaus(1, 0.05)*tmpselection[ibin], 0.01, 0.0, 1.5, ierflg);
//          myMinuit->mnparm(ibin+44, name, 1.0, 0.01, 0.0, 1.5, ierflg);
         if(ibin>=15 && ibin<=35)
          {
           myMinuit->mnparm(ibin+44, name, tmpselection[ibin]*MyR->Gaus(1, 0.01), 0.01, 0.0, 1.5, ierflg);
           myMinuit->FixParameter(ibin+44);       
          }
/*
         if(ibin>=10 && ibin<=35 && ibin!=19) 
          {
           myMinuit->mnparm(ibin+44, name, MyR->Gaus(1, 0.0001)*tmpselection[ibin], 0.1, 0.0, 1.5, ierflg);
           myMinuit->FixParameter(ibin+44);
          }
         if(ibin<10 || ibin>35)
          myMinuit->mnparm(ibin+44, name, MyR->Gaus(1, 0.03)*tmpselection[ibin], 0.1, 0.0, 1.5, ierflg);
//          myMinuit->mnparm(ibin+44, name, 1.0, 0.1, 0.0, 1.5, ierflg);
*/
//         if(ibin<10 || ibin>35) 
//           myMinuit->FixParameter(ibin+44);       
        }

       arglist[0] = 1000; // number of function calls
       arglist[1] = 0.01;  // tolerance(x10^3)
//       myMinuit->mnexcm("SIMPLEX", arglist, 2, ierflg);
       myMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
//       myMinuit->mnexcm("HESSE", arglist, 1, ierflg);

       myMinuit->mnmatu(1);
       double GetPar[88],GetErr[88];
       ofstream global_EC_out;
        global_EC_out.open("fit_trigger_eta.txt",ios::out);
       for(int ipar=0;ipar<88;ipar++)
        {
          myMinuit->GetParameter(ipar, GetPar[ipar], GetErr[ipar]);
          global_EC_out<<GetPar[ipar]<<"   "<<GetErr[ipar]<<endl;
        }
       global_EC_out.close();
     delete myMinuit;
}


int main(int argc, char** argv)
{
//usage output
  if(argc != 3){
    //output: usage
    std::cout<<"usage : "<<argv[0]<<" eff "<<std::endl;
    return 0;
  }

  TString InputRoot;
  TString ModeName,TypeName;
  ModeName=argv[1];
  TypeName=argv[2];

  if(ModeName=="trigger")
   {
    if(TypeName=="eta") set_trigger_eta();
   }

  return 1;
}

