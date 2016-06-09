#ifndef SELECTSINGLEPHOTON
#define SELECTSINGLEPHOTON

#include "AnalysisTools/src/processor.h"

#include "TH1F.h"
#include "TLorentzVector.h"

#include <iostream>

using namespace std;

template <class TreeType> class selectSinglePhoton : public processor<TreeType> {

public : 

  TH1F* histo;
  TreeType* ntuple;
  TString label;

  selectSinglePhoton()
    : processor<TreeType>("selectSinglePhoton")
  {
    ntuple = 0; 
  };
  selectSinglePhoton( TreeType *ntuple_ ,
		  TString label_ )
    : processor<TreeType>("selectSinglePhoton")
  {
    ntuple = ntuple_;
    label = label_;
    histo = new TH1F("selectSinglePhotonYields_"+label,"selectSinglePhotonYields_"+label,9,0.5,9.5);
  };

  bool process( ) override {

    // I am assuming that this has already been done!!!
    //ntuple->patchJetID();

    /*
    std::cout << "Leptons: " << ntuple->Leptons << endl;
    std::cout << "NumPhotons: " << ntuple->NumPhotons << endl;
    std::cout << "NJets: " << ntuple->NJets << endl;    
    std::cout << "HT: " << ntuple->HT << endl;
    std::cout << "MHT: " << ntuple->MHT << endl;
    std::cout << "DeltaPhi1: " << ntuple->DeltaPhi1 << endl;
    std::cout << "DeltaPhi2: " << ntuple->DeltaPhi2 << endl;    
    std::cout << "DeltaPhi3: " << ntuple->DeltaPhi3 << endl;
    std::cout << "DeltaPhi4: " << ntuple->DeltaPhi4 << endl;
    */

    histo->Fill(0);
    if( ntuple->Leptons == 0 ) histo->Fill(1);
    else return false;
    if( ntuple->MHTclean>200. ) histo->Fill(2); 
    else return false;
    if( ntuple->NumPhotons == 1 ) histo->Fill(3);
    else return false;
    if( ntuple->HTclean>500. ) histo->Fill(4);
    else return false;
    if( ntuple->NJetsclean>=4 ) histo->Fill(5);
    else return false;
    if( ntuple->DeltaPhi1clean>0.5 ) histo->Fill(6);
    else return false;
    if( ntuple->DeltaPhi2clean>0.5 ) histo->Fill(7);
    else return false;
    if( ntuple->DeltaPhi3clean>0.3 ) histo->Fill(8);
    else return false;
    if( ntuple->DeltaPhi4clean>0.3 ) histo->Fill(9);
    else return false;

    return true;

  };

  void postProcess( ) override {
    histo->Write();
  }

};

#endif
