//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Apr 19 19:50:35 2019 by ROOT version 6.14/04
// from TTree Zeetree/Zeetree
// found on file: Zeetree.root
//////////////////////////////////////////////////////////

#ifndef Zeetree_h
#define Zeetree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Zeetree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

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

   Zeetree(TTree *tree=0);
   virtual ~Zeetree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Zeetree_cxx
Zeetree::Zeetree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Zeetree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Zeetree.root");
      }
      f->GetObject("Zeetree",tree);

   }
   Init(tree);
}

Zeetree::~Zeetree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Zeetree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Zeetree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Zeetree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("GammaPx", GammaPx, &b_GammaPx);
   fChain->SetBranchAddress("GammaPy", GammaPy, &b_GammaPy);
   fChain->SetBranchAddress("GammaPz", GammaPz, &b_GammaPz);
   fChain->SetBranchAddress("GammaE", GammaE, &b_Gamma);
   fChain->SetBranchAddress("GammaMother", GammaMother, &b_GammaMother);
   fChain->SetBranchAddress("GammaNumber", &GammaNumber, &b_GammaNumber);
   fChain->SetBranchAddress("ElectronPx", &ElectronPx, &b_ElectronPx);
   fChain->SetBranchAddress("ElectronPy", &ElectronPy, &b_ElectronPy);
   fChain->SetBranchAddress("ElectronPz", &ElectronPz, &b_ElectronPz);
   fChain->SetBranchAddress("ElectronE", &ElectronE, &b_ElectronE);
   fChain->SetBranchAddress("PositronPx", &PositronPx, &b_PositronPx);
   fChain->SetBranchAddress("PositronPy", &PositronPy, &b_PositronPy);
   fChain->SetBranchAddress("PositronPz", &PositronPz, &b_PositronPz);
   fChain->SetBranchAddress("PositronE", &PositronE, &b_PositronE);
   fChain->SetBranchAddress("ZPx", &ZPx, &b_ZPx);
   fChain->SetBranchAddress("ZPy", &ZPy, &b_ZPy);
   fChain->SetBranchAddress("ZPz", &ZPz, &b_ZPz);
   fChain->SetBranchAddress("ZE", &ZE, &b_ZE);
   fChain->SetBranchAddress("quark_flavour", quark_flavour, &b_quark_flavour);
   fChain->SetBranchAddress("QuarkPx", QuarkPx, &b_QuarkPx);
   fChain->SetBranchAddress("QuarkPy", QuarkPy, &b_QuarkPy);
   fChain->SetBranchAddress("QuarkPz", QuarkPz, &b_QuarkPz);
   fChain->SetBranchAddress("QuarkE", QuarkE, &b_QuarkE);
   Notify();
}

Bool_t Zeetree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Zeetree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Zeetree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Zeetree_cxx
