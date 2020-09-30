#ifndef ZMMANA_HEADER
#define ZMMANA_HEADER

#include"State.h"

using namespace std;

//define class
class ZmmAna
{
 public:
  TTree *fChain;
  
  //declaration of leaf types
   Float_t         Px_d1;
   Float_t         Py_d1;
   Float_t         Pz_d1;
   Float_t         E_d1;
   Float_t         Px_d2;
   Float_t         Py_d2;
   Float_t         Pz_d2;
   Float_t         E_d2;
   Float_t         Px_V;
   Float_t         Py_V;
   Float_t         Pz_V;
   Float_t         E_V;
   Float_t         WT00;

   // List of branches
   TBranch        *b_Px_d1;   //!
   TBranch        *b_Py_d1;   //!
   TBranch        *b_Pz_d1;   //!
   TBranch        *b_E_d1;   //!
   TBranch        *b_Px_d2;   //!
   TBranch        *b_Py_d2;   //!
   TBranch        *b_Pz_d2;   //!
   TBranch        *b_E_d2;   //!
   TBranch        *b_Px_V;   //!
   TBranch        *b_Py_V;   //!
   TBranch        *b_Pz_V;   //!
   TBranch        *b_E_V;   //!
   TBranch        *b_WT00;   //!

   // Declaration of leaf types
   Double_t        GammaPx[10];
   Double_t        GammaPy[10];
   Double_t        GammaPz[10];
   Double_t        GammaE[10];
   Int_t           GammaMother[10];
   Int_t           GammaNumber;
   Double_t        ElectronPx;
   Double_t        ElectronPy;
   Double_t        ElectronPz;
   Double_t        ElectronE;
   Double_t        PositronPx;
   Double_t        PositronPy;
   Double_t        PositronPz;
   Double_t        PositronE;
   Double_t        ZPx;
   Double_t        ZPy;
   Double_t        ZPz;
   Double_t        ZE;
   Int_t           quark_flavour[2];
   Double_t        QuarkPx[2];
   Double_t        QuarkPy[2];
   Double_t        QuarkPz[2];
   Double_t        QuarkE[2];

      // List of branches
   TBranch        *b_GammaPx;   //!
   TBranch        *b_GammaPy;   //!
   TBranch        *b_GammaPz;   //!
   TBranch        *b_Gamma;   //!
   TBranch        *b_GammaMother;   //!
   TBranch        *b_GammaNumber;   //!
   TBranch        *b_ElectronPx;   //!
   TBranch        *b_ElectronPy;   //!
   TBranch        *b_ElectronPz;   //!
   TBranch        *b_ElectronE;   //!
   TBranch        *b_PositronPx;   //!
   TBranch        *b_PositronPy;   //!
   TBranch        *b_PositronPz;   //!
   TBranch        *b_PositronE;   //!
   TBranch        *b_ZPx;   //!
   TBranch        *b_ZPy;   //!
   TBranch        *b_ZPz;   //!
   TBranch        *b_ZE;   //!
   TBranch        *b_quark_flavour;   //!
   TBranch        *b_QuarkPx;   //!
   TBranch        *b_QuarkPy;   //!
   TBranch        *b_QuarkPz;   //!
   TBranch        *b_QuarkE;   //!

   
  //function
  ZmmAna(const char *FileList, const char *TypeName, const char *BagNo);
  virtual ~ZmmAna();
  virtual void Initial(const char *RootName,int RootNumber,const char *TypeName);
  virtual void Loop(const char *TypeName);
  virtual void End(int RootNumber);
  virtual void Finish(int RootNumber);
  virtual void Output();

  //control variable
  bool isRead;
 
  //counting number
  Double_t Sta_total_number;

  //plots
  MakeHist *myHist;

};//class defination

inline ZmmAna::ZmmAna(const char *FileList,const char *TypeName, const char *BagNo)
{//func_ZmmAna

 //Initialize histograms
 myHist = new MakeHist();
 TString histName;
 histName = "./result_CT14nnlo/" + (TString)TypeName + "_" + (TString)BagNo + "_result.root";
 myHist->BookHist(histName);

 //Initialize counting number
 Sta_total_number=0;
}//func_ZmmAna

inline ZmmAna::~ZmmAna()
{
}

inline void ZmmAna::Initial(const char *RootName,int RootNumber,const char *TypeName)
{//func_Initial
 TFile *file = new TFile(RootName);
 TTree *orgTree = NULL;
 if((string)TypeName=="ResBos")
  orgTree = (TTree *)gDirectory->Get("h10");
 if((string)TypeName=="Pythia")
  orgTree = (TTree *)gDirectory->Get("ZeeTree");

 fChain = orgTree;

 //tips for begin reading
 cout<<"Running:Starting Rootfile"<<RootNumber<<endl;

 //whether an empty tree
 isRead = true;
 double entryNumber;
 if(fChain==NULL)
 {
  isRead = false;
  cout<<"****** this file has no Ztree, skip to next!!! ******"<<endl;
  return;
 }
 if(fChain!=NULL)
  entryNumber = fChain->GetEntries();

 cout<<"entryNumber = "<<entryNumber<<endl;

 if(entryNumber==0)
 {
  isRead = false;
  cout<<"****** this tree has no event, skip to next!!! ******"<<endl;
  return;
 }
 
 //Set address of the tree
  if((string)TypeName=="ResBos")
  {
   fChain->SetBranchAddress("Px_d1", &Px_d1, &b_Px_d1);
   fChain->SetBranchAddress("Py_d1", &Py_d1, &b_Py_d1);
   fChain->SetBranchAddress("Pz_d1", &Pz_d1, &b_Pz_d1);
   fChain->SetBranchAddress("E_d1", &E_d1, &b_E_d1);
   fChain->SetBranchAddress("Px_d2", &Px_d2, &b_Px_d2);
   fChain->SetBranchAddress("Py_d2", &Py_d2, &b_Py_d2);
   fChain->SetBranchAddress("Pz_d2", &Pz_d2, &b_Pz_d2);
   fChain->SetBranchAddress("E_d2", &E_d2, &b_E_d2);
   fChain->SetBranchAddress("Px_V", &Px_V, &b_Px_V);
   fChain->SetBranchAddress("Py_V", &Py_V, &b_Py_V);
   fChain->SetBranchAddress("Pz_V", &Pz_V, &b_Pz_V);
   fChain->SetBranchAddress("E_V", &E_V, &b_E_V);
   fChain->SetBranchAddress("WT00", &WT00, &b_WT00);
  }
  if((string)TypeName=="Pythia")
  {
   fChain->SetBranchAddress("GammaPx", GammaPx, &b_GammaPx);
   fChain->SetBranchAddress("GammaPy", GammaPy, &b_GammaPy);
   fChain->SetBranchAddress("GammaPz", GammaPz, &b_GammaPz);
   fChain->SetBranchAddress("GammaE", GammaE, &b_Gamma);
   fChain->SetBranchAddress("GammaMother", GammaMother, &b_GammaMother);
   fChain->SetBranchAddress("GammaNumber", &GammaNumber, &b_GammaNumber);
   fChain->SetBranchAddress("Electron_px", &ElectronPx, &b_ElectronPx);
   fChain->SetBranchAddress("Electron_py", &ElectronPy, &b_ElectronPy);
   fChain->SetBranchAddress("Electron_pz", &ElectronPz, &b_ElectronPz);
   fChain->SetBranchAddress("Electron_E", &ElectronE, &b_ElectronE);
   fChain->SetBranchAddress("Positron_px", &PositronPx, &b_PositronPx);
   fChain->SetBranchAddress("Positron_py", &PositronPy, &b_PositronPy);
   fChain->SetBranchAddress("Positron_pz", &PositronPz, &b_PositronPz);
   fChain->SetBranchAddress("Positron_E", &PositronE, &b_PositronE);
   fChain->SetBranchAddress("Zparticle_px", &ZPx, &b_ZPx);
   fChain->SetBranchAddress("Zparticle_py", &ZPy, &b_ZPy);
   fChain->SetBranchAddress("Zparticle_pz", &ZPz, &b_ZPz);
   fChain->SetBranchAddress("Zparticle_E", &ZE, &b_ZE);
   fChain->SetBranchAddress("quark_flavour", quark_flavour, &b_quark_flavour);
   fChain->SetBranchAddress("QuarkPx", QuarkPx, &b_QuarkPx);
   fChain->SetBranchAddress("QuarkPy", QuarkPy, &b_QuarkPy);
   fChain->SetBranchAddress("QuarkPz", QuarkPz, &b_QuarkPz);
   fChain->SetBranchAddress("QuarkE", QuarkE, &b_QuarkE);
  }
 return;
}//func_Initial

//finish analysis one rootfile
inline void ZmmAna::End(int RootNumber)
{//func_End
 if(isRead==false)
 {
  return;
 }

//output:free the current tree
 cout<<"Running: Free Rootfile"<<RootNumber<<endl;

 if(!fChain)
 {
  cout<<"!!!!!!!!!Big Error"<<RootNumber<<"!!!!!!!!"<<endl;
  return;
 }

 delete fChain->GetCurrentFile();
 }//func_End

//finish analysis all rootfiles
inline void ZmmAna::Finish(int RootNumber)
{//func_Finish
 cout<<endl;
 cout<<"Running:"<<RootNumber<<"files in total readed!"<<endl;

 //save histgram
 if(myHist)
 {
   myHist->SaveHist();
   delete myHist;
 }

 cout<<"Running: histgrams saved!"<<endl;
}//func_Finish

//output some statistic variables
inline void ZmmAna::Output(void)
{//func_Output
 cout<<endl;
 cout<<"total event number:"<<Sta_total_number<<endl;
 
}//func_Output
#endif
