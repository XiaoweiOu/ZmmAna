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
   if(ZYbin[turn_1[ii]]<2 && ZYbin[turn_1[ii]]>12) continue;
   if(ZYbin[turn_2[ii]]<2 && ZYbin[turn_2[ii]]>12) continue;

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
   if(num_data[turn_1[ii]]<200) continue;
   if(num_mc[turn_1[ii]]<200) continue;

//   if(err_data[turn_1[ii]]/num_data[turn_1[ii]] > 0.1) continue;
//   if(err_data[turn_2[ii]]/num_data[turn_2[ii]] > 0.1) continue;
//   if(err_mc[turn_1[ii]]/num_mc[turn_1[ii]] > 0.1) continue;
//   if(err_mc[turn_2[ii]]/num_mc[turn_2[ii]] > 0.1) continue;

   if((index_trigger_1[turn_1[ii]]+index_trigger_2[turn_1[ii]])/2.-ZYbin[turn_1[ii]] >= 3 ) continue; 
   if((index_trigger_1[turn_2[ii]]+index_trigger_2[turn_2[ii]])/2.-ZYbin[turn_2[ii]] >= 3 ) continue;

//   if(fabs(index_trigger_1[turn_1[ii]]-index_trigger_2[turn_1[ii]]) >= 8 ) continue; 
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
       index_cut_1.push_back((int)getvalue+14);
       infile>>getvalue;
       index_trigger_2.push_back((int)getvalue);
       index_cut_2.push_back((int)getvalue+14);
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
       index_cut_1_mc.push_back((int)getvalue+14);
       infile>>getvalue;
       index_trigger_2_mc.push_back((int)getvalue);
       index_cut_2_mc.push_back((int)getvalue+14);
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

//  double tmptrigger[14] = {1.06624, 0.710047, 0.613472, 0.596595, 0.664076, 0.693181, 0.74178, 0.709131, 0.778556, 0.597537, 0.598814, 0.559896, 0.560026, 0.813739};
//  double tmpselection[14] = {0.891625, 0.960753, 0.937837, 0.944304, 0.899915, 0.91107, 0.9, 0.898517, 0.857484, 0.895729, 0.920999, 0.93853, 0.990309, 0.927107};

  ofstream outfile_random;
   outfile_random.open("randomwalk.txt",ios::app);

  double tmptrigger[14];
  double tmpselection[14];
  for(int ii=0;ii<14;ii++)
   {
    tmptrigger[ii] = 0.7;
    tmpselection[ii] = 1.0;
   }

  double setpar[28];
  TRandom3 *MyR = new TRandom3(0);
//  ofstream outfile_rndm;
//   outfile_rndm.open("random_starting.txt",ios::out);
  double iter_trigger[14];
  double iter_selection[14];

  double lowedge_trigger = 0.7;
  double step_trigger = 0.6;
  double lowedge_selection = 0.8;
  double step_selection = 0.4;

  double min_trigger_par[14];
  double min_selection_par[14];
  double min_fix_chi2 = 10000;

  for(int ix=0;ix<14;ix++)
   {
    tmptrigger[ix] = tmptrigger[ix]*(lowedge_trigger + step_trigger*MyR->Rndm());
    if(tmptrigger[ix]>1) tmptrigger[ix] = 1;
    tmpselection[ix] = tmpselection[ix]*(lowedge_selection + step_selection*MyR->Rndm());
//    tmpselection[ix] = 0.85;
//    if(ix==20) tmpselection[ix] = tmpselection[ix]*(0.99 + 0.02*MyR->Rndm());
   }

  for(int ix=0;ix<14;ix++)
   {
    iter_trigger[ix]=tmptrigger[ix];
    iter_selection[ix] = tmpselection[ix];
   }

  double chi2_threshold = 200;
  double chi2_sum;
  double min_chi2 = 500000;

  double last_lowedge_trigger;
  double last_step_trigger;
  double last_lowedge_selection;
  double last_step_selection;
  double last_iter_trigger[14];
  double last_iter_selection[14];

  double current_iter_trigger[14];
  double current_iter_selection[14];
  double current_step_trigger;
  double current_step_selection;
  double current_min_chi2;

  double last_min_chi2;
  double singleloop=0;
  double gotmin_loop;

  bool isInSingleLoop=false;
  bool isGlobalMinUpdate=true;
  double noupdateloop=0;

  for(int iloop=0;iloop<250000;iloop++)
   {//try starting point
    if(singleloop>800)
     {
      for(int ix=0;ix<14;ix++)
       {
//        iter_trigger[ix] = current_iter_trigger[ix];
//        iter_selection[ix] = current_iter_selection[ix];
        iter_trigger[ix] = last_iter_trigger[ix];
        iter_selection[ix] = last_iter_selection[ix];
       }
//      min_chi2 = current_min_chi2;
      min_chi2 = 500000;
      singleloop = 0;

//      step_trigger = current_step_trigger * 3 *(min_chi2/min_fix_chi2);
//      step_selection = current_step_selection * 3 *(min_chi2/min_fix_chi2);
//      step_trigger = last_step_trigger * 3 *(min_chi2/min_fix_chi2);
//      step_selection = last_step_selection * 3 *(min_chi2/min_fix_chi2);
      step_trigger = 0.3;
      step_selection = 0.2;

/*
      if(step_trigger>0.3) step_trigger = 0.3;
      if(step_selection>0.3) step_selection = 0.3;
      if(step_trigger<0.1) step_trigger = 0.1;
      if(step_selection<0.1) step_selection = 0.1;
*/
      lowedge_trigger = 1 - step_trigger/2.0;
      lowedge_selection = 1 - step_selection/2.0;
     }
    if(noupdateloop>8000 && isGlobalMinUpdate==false)
     {
      for(int ix=0;ix<14;ix++)
       {
        iter_trigger[ix]=tmptrigger[ix];
        iter_selection[ix] = tmpselection[ix];
       }
      step_trigger = 0.6;
      step_selection = 0.4;
      lowedge_trigger = 0.7;
      lowedge_selection = 0.8;
      noupdateloop=0;
      singleloop=0;
     }

    for(int ix=0;ix<14;ix++)
     {
      setpar[ix] = iter_trigger[ix]*(lowedge_trigger+step_trigger*MyR->Rndm());
      if(setpar[ix]>1) setpar[ix]=1;
      setpar[ix+14] = iter_selection[ix]*(lowedge_selection+step_selection*MyR->Rndm());;
/*
      setpar[ix] = iter_trigger[ix]*MyR->Gaus(1, 0.05);
      if(setpar[ix]>1) setpar[ix]=1;
      setpar[ix+14] = iter_selection[ix]*MyR->Gaus(1, 0.05);
*/
     }

    chi2_sum = 0;
    double data_calculate;
    double ratio_1, ratio_2;
    double obs_calculate;
    double obs_data;
    double obs_err;
    double err_1,err_2;
    double chi2_cal=0;

    double n_count=0;
    for(int ii=0;ii<num_data.size();ii++)
     {
      if(ZYbin[turn_1[ii]]<2 && ZYbin[turn_1[ii]]>12) continue;
      if(ZYbin[turn_2[ii]]<2 && ZYbin[turn_2[ii]]>12) continue;

      if(num_data[turn_1[ii]]<200) continue;
      if(num_mc[turn_1[ii]]<200) continue;

//      if(err_data[turn_1[ii]]/num_data[turn_1[ii]] > 0.1) continue;
//      if(err_data[turn_2[ii]]/num_data[turn_2[ii]] > 0.1) continue;
//      if(err_mc[turn_1[ii]]/num_mc[turn_1[ii]] > 0.1) continue;
//      if(err_mc[turn_2[ii]]/num_mc[turn_2[ii]] > 0.1) continue;

      if((index_trigger_1[turn_1[ii]]+index_trigger_2[turn_1[ii]])/2.-ZYbin[turn_1[ii]] >= 3 ) continue;
      if((index_trigger_1[turn_2[ii]]+index_trigger_2[turn_2[ii]])/2.-ZYbin[turn_2[ii]] >= 3 ) continue;

//      if(fabs(index_trigger_1[turn_1[ii]]-index_trigger_2[turn_1[ii]]) >= 8 ) continue;
      if(turn_1[ii]==turn_2[ii]) continue;

      if(turn_1[ii]!=ii) cout<<" !!! BIG ERROR !!!! "<<turn_1[ii]<<"   "<<ii<<endl;
      ratio_1 = num_data[turn_1[ii]] / num_mc[turn_1[ii]];
      err_1 = ratio_1 * sqrt(err_mc[turn_1[ii]]*err_mc[turn_1[ii]]/(num_mc[turn_1[ii]]*num_mc[turn_1[ii]]) + err_data[turn_1[ii]]*err_data[turn_1[ii]]/(num_data[turn_1[ii]]*num_data[turn_1[ii]]));
      ratio_2 = num_data[turn_2[ii]] / num_mc[turn_2[ii]];
      err_2 = ratio_2 * sqrt(err_mc[turn_2[ii]]*err_mc[turn_2[ii]]/(num_mc[turn_2[ii]]*num_mc[turn_2[ii]]) + err_data[turn_2[ii]]*err_data[turn_2[ii]]/(num_data[turn_2[ii]]*num_data[turn_2[ii]]));
      obs_data = ratio_1/ratio_2;
      obs_err = sqrt((err_1/ratio_1)*(err_1/ratio_1) + (err_2/ratio_2)*(err_2/ratio_2))*obs_data;
      obs_calculate = ( ( 1-(1-setpar[index_trigger_1[turn_1[ii]]])*(1-setpar[index_trigger_2[turn_1[ii]]]) )
          * setpar[index_cut_1[turn_1[ii]]] * setpar[index_cut_2[turn_1[ii]]] ) /
          ( ( 1-(1-setpar[index_trigger_1[turn_2[ii]]])*(1-setpar[index_trigger_2[turn_2[ii]]]) )
          * setpar[index_cut_1[turn_2[ii]]] * setpar[index_cut_2[turn_2[ii]]] );
      chi2_cal = (obs_data-obs_calculate)*(obs_data-obs_calculate)/(obs_err*obs_err);
      chi2_sum = chi2_sum + chi2_cal;
      n_count++;
     }
// a protection
    for(int ix=0;ix<13;ix++)
     {
      if(fabs(setpar[ix]-setpar[ix+1])>0.25) chi2_sum = chi2_sum + 10000;
      if(fabs(setpar[ix+14] - setpar[ix+14+1])>0.25) chi2_sum = chi2_sum + 10000;
     }

    singleloop = singleloop + 1;

//    if(chi2_sum<8000 && chi2_sum<min_chi2)
    if(chi2_sum<min_chi2)
     {
      isInSingleLoop=true;

      last_min_chi2 = min_chi2;
      last_lowedge_trigger = lowedge_trigger;
      last_lowedge_selection = lowedge_selection;
      last_step_trigger = step_trigger;
      last_step_selection = step_selection;

      for(int ix=0;ix<14;ix++)
       {
        last_iter_trigger[ix] = iter_trigger[ix];
        last_iter_selection[ix] = iter_selection[ix];

        iter_trigger[ix] = setpar[ix];
        iter_selection[ix] = setpar[ix+14];
       }

      double diff;
//      diff = 0.3*chi2_sum/min_chi2;
      diff = 0.8 * chi2_sum/min_chi2;
      if(diff<0.1) diff = 0.1;
      if(diff>1) diff=1;//just a protection
//      if(iloop<10 && diff<0.8) diff = 0.8;
//      if(diff<0.8) diff = 0.5;
      step_trigger = step_trigger * diff;
      step_selection = step_selection * diff;

      if(step_trigger<0.005) step_trigger = 0.005;
      if(step_selection<0.005) step_selection = 0.005;
      lowedge_trigger = 1 - step_trigger/2.0;
      lowedge_selection = 1 - step_selection/2.0;

      min_chi2 = chi2_sum;
      cout<<"***** starting chi2:   "<<chi2_sum<<"  iter:   "<<iloop<<"  single loop:  "<<singleloop<<"  global minimal chi2:  "<<min_fix_chi2<<"  at:  "<<gotmin_loop<<endl;
      cout<<"      lowedge trigger:     "<<lowedge_trigger<<"  step trigger:    "<<step_trigger<<endl;
      cout<<"      lowedge selection:   "<<lowedge_selection<<"  step selection:  "<<step_selection<<endl;
      cout<<"      not updating loop:   "<<noupdateloop<<endl;
      singleloop = 0;
     }
//    cout<<iloop<<"   "<<singleloop<<"\r";
//    if(iloop%10000==0)
//     cout<<iloop<<"   "<<singleloop<<endl;

    if(chi2_sum<min_fix_chi2)
     {
      for(int ix=0;ix<14;ix++)
       {
        min_trigger_par[ix] = setpar[ix];
        min_selection_par[ix] = setpar[ix+14];
       }
      min_fix_chi2 = chi2_sum;
      gotmin_loop = iloop;
      isGlobalMinUpdate=true;
     }
    else
     {
      isGlobalMinUpdate=false;
      noupdateloop = noupdateloop+1;
     }

    if(chi2_sum<chi2_threshold) break;

   }//try starting point

  outfile_random<<"***** starting chi2:   "<<chi2_sum<<"  single loop:  "<<singleloop<<"  global minimal chi2:  "<<min_fix_chi2<<"  at:  "<<gotmin_loop<<endl;
  outfile_random<<"      lowedge trigger:     "<<lowedge_trigger<<"  step trigger:    "<<step_trigger<<endl;
  outfile_random<<"      lowedge selection:   "<<lowedge_selection<<"  step selection:  "<<step_selection<<endl;
  outfile_random<<"      not updating loop:   "<<noupdateloop<<endl;
  for(int ix=0;ix<14;ix++)
   {
    outfile_random<<min_trigger_par[ix]<<endl;
   }
  for(int ix=0;ix<14;ix++)
   {
    outfile_random<<min_selection_par[ix]<<endl;
   }
  outfile_random<<endl<<endl;

  cout<<endl;
  cout<<endl;


//*****************************************************//
//********* Randomly Selecting Starting Point *********//
//*****************************************************//

       TMinuit *myMinuit = new TMinuit(28);
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
 
       for(int ibin=0;ibin<14;ibin++)
        {
         sprintf(name, "%s%d", "scale_trigger_",ibin);
         myMinuit->mnparm(ibin, name, min_trigger_par[ibin], 0.01, min_trigger_par[ibin]*0.99, min_trigger_par[ibin]*1.01, ierflg);
        }
       for(int ibin=0;ibin<14;ibin++)
        {
         sprintf(name, "%s%d", "scale_cut_",ibin);
         myMinuit->mnparm(ibin+14, name, min_selection_par[ibin], 0.01, min_selection_par[ibin]*0.99, min_selection_par[ibin]*1.01, ierflg);
        }

       arglist[0] = 1000; // number of function calls
       arglist[1] = 0.01;  // tolerance(x10^3)
//       myMinuit->mnexcm("SIMPLEX", arglist, 2, ierflg);
       myMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
//       myMinuit->mnexcm("HESSE", arglist, 1, ierflg);

       myMinuit->mnmatu(1);
       double GetPar[28],GetErr[28];
       ofstream global_EC_out;
        global_EC_out.open("fit_trigger_eta.txt",ios::out);
       for(int ipar=0;ipar<28;ipar++)
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

