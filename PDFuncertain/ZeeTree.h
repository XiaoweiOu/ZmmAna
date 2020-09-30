//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Dec  8 10:45:05 2019 by ROOT version 6.14/04
// from TTree ZeeTree/ZeeTree
// found on file: Pythia8_CT14nnlo_50W_0.root
//////////////////////////////////////////////////////////

#ifndef ZeeTree_h
#define ZeeTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ZeeTree {
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
   Double_t        Electron_px;
   Double_t        Electron_py;
   Double_t        Electron_pz;
   Double_t        Electron_E;
   Double_t        Positron_px;
   Double_t        Positron_py;
   Double_t        Positron_pz;
   Double_t        Positron_E;
   Double_t        Zparticle_px;
   Double_t        Zparticle_py;
   Double_t        Zparticle_pz;
   Double_t        Zparticle_E;
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
   TBranch        *b_Electron_px;   //!
   TBranch        *b_Electron_py;   //!
   TBranch        *b_Electron_pz;   //!
   TBranch        *b_Electron_E;   //!
   TBranch        *b_Positron_px;   //!
   TBranch        *b_Positron_py;   //!
   TBranch        *b_Positron_pz;   //!
   TBranch        *b_Positron_E;   //!
   TBranch        *b_Zparticle_px;   //!
   TBranch        *b_Zparticle_py;   //!
   TBranch        *b_Zparticle_pz;   //!
   TBranch        *b_Zparticle_E;   //!
   TBranch        *b_quark_flavour;   //!
   TBranch        *b_QuarkPx;   //!
   TBranch        *b_QuarkPy;   //!
   TBranch        *b_QuarkPz;   //!
   TBranch        *b_QuarkE;   //!

   ZeeTree(TTree *tree=0);
   virtual ~ZeeTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ZeeTree_cxx
ZeeTree::ZeeTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Pythia8_CT14nnlo_50W_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Pythia8_CT14nnlo_50W_0.root");
      }
      f->GetObject("ZeeTree",tree);

   }
   Init(tree);
}

ZeeTree::~ZeeTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ZeeTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ZeeTree::LoadTree(Long64_t entry)
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

void ZeeTree::Init(TTree *tree)
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
   fChain->SetBranchAddress("Electron_px", &Electron_px, &b_Electron_px);
   fChain->SetBranchAddress("Electron_py", &Electron_py, &b_Electron_py);
   fChain->SetBranchAddress("Electron_pz", &Electron_pz, &b_Electron_pz);
   fChain->SetBranchAddress("Electron_E", &Electron_E, &b_Electron_E);
   fChain->SetBranchAddress("Positron_px", &Positron_px, &b_Positron_px);
   fChain->SetBranchAddress("Positron_py", &Positron_py, &b_Positron_py);
   fChain->SetBranchAddress("Positron_pz", &Positron_pz, &b_Positron_pz);
   fChain->SetBranchAddress("Positron_E", &Positron_E, &b_Positron_E);
   fChain->SetBranchAddress("Zparticle_px", &Zparticle_px, &b_Zparticle_px);
   fChain->SetBranchAddress("Zparticle_py", &Zparticle_py, &b_Zparticle_py);
   fChain->SetBranchAddress("Zparticle_pz", &Zparticle_pz, &b_Zparticle_pz);
   fChain->SetBranchAddress("Zparticle_E", &Zparticle_E, &b_Zparticle_E);
   fChain->SetBranchAddress("quark_flavour", quark_flavour, &b_quark_flavour);
   fChain->SetBranchAddress("QuarkPx", QuarkPx, &b_QuarkPx);
   fChain->SetBranchAddress("QuarkPy", QuarkPy, &b_QuarkPy);
   fChain->SetBranchAddress("QuarkPz", QuarkPz, &b_QuarkPz);
   fChain->SetBranchAddress("QuarkE", QuarkE, &b_QuarkE);
   Notify();
}

Bool_t ZeeTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ZeeTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ZeeTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ZeeTree_cxx
