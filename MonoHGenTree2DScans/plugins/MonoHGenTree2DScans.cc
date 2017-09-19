// -*- C++ -*-
//
// Package:    MonoHGenTree/MonoHGenTree2DScans
// Class:      MonoHGenTree2DScans
// 
/**\class MonoHGenTree2DScans MonoHGenTree2DScans.cc MonoHGenTree/MonoHGenTree2DScans/plugins/MonoHGenTree2DScans.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Raman Khurana (CMS Tau; Saha Institute of Nuclear Physics
//         Created:  Wed, 28 Jun 2017 15:56:22 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class MonoHGenTree2DScans : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit MonoHGenTree2DScans(const edm::ParameterSet&);
  ~MonoHGenTree2DScans();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  edm::EDGetTokenT<reco::GenParticleCollection>     genParticleToken;
  edm::EDGetTokenT<LHEEventProduct>                 lheEventToken;
  //TFile* file;
  //TTree* tree;
  TTree* tree_;

  float HiggsPt;
  float trueMET;
  float HiggsEta;
   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

    
  // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MonoHGenTree2DScans::MonoHGenTree2DScans(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   lheEventToken            = consumes<LHEEventProduct>(edm::InputTag("externalLHEProducer"));
   genParticleToken         = consumes<reco::GenParticleCollection>(edm::InputTag("genParticles"));
   
   edm::Service<TFileService> fs;
   tree_ = fs->make<TTree>("tree_","tree");

}


MonoHGenTree2DScans::~MonoHGenTree2DScans()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MonoHGenTree2DScans::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
   using namespace edm;
   edm::Handle<reco::GenParticleCollection> genParticleHandle;
   if(not iEvent.getByToken(genParticleToken, genParticleHandle))
     {
       std::cout<<
	 "GenAnalyzer: Generator Level Information not found\n"
	        <<std::endl;
     }
   
   //auto Higgs=0;
   //auto vV=0;
   TLorentzVector Higgs;
   TLorentzVector vV;
   
   bool found_higgs = false;
   bool found_a0 = false;
   
   std::vector<const reco::Candidate*> cands;
   std::vector<std::vector<reco::GenParticle>::const_iterator> myParticles;
   int idm = 0;

   HiggsPt = -99.;
   trueMET = -99.;
   HiggsEta = -99.; 
   for( std::vector<reco::GenParticle>::const_iterator it_gen = genParticleHandle->begin(); it_gen != genParticleHandle->end(); it_gen++ )    {
     reco::GenParticle gen = *it_gen;
     
     //  std::cout<<" px = "<<gen.px()<<std::endl;
     if ( found_higgs && found_a0)    break;
     if (abs(gen.pdgId())==25){
       if (!found_higgs){
	 Higgs.SetPxPyPzE(gen.px(), gen.py(), gen.pz(), gen.energy());
	 found_higgs = true;
       }
     }
     
     if (abs(gen.pdgId())==18){
       if (!found_a0){
	 if (idm < 3){
	   TLorentzVector tmp_;
	   tmp_.SetPxPyPzE(gen.px(), gen.py(), gen.pz(), gen.energy());
	   vV += tmp_;
	   //vV.SetPxPyPzE(gen.px(), gen.py(), gen.pz(), gen.energy());
	   std::cout<<" inside dm"<<gen.pt()
	   <<" " <<gen.status()<<std::endl;
	 }
	 idm++;
       }
       if (idm == 2) found_a0 = true;
       /*
	 else{
	 TLorentzVector tmp_;
	 tmp_.SetPxPyPzE(gen.px(), gen.py(), gen.pz(), gen.energy());
	 vV += tmp_;
	 found_a0 = true;
       }
       */
     }
   }
   
   HiggsPt = Higgs.Pt();
   trueMET = vV.Pt();
   HiggsEta = Higgs.Eta();
   
     
   
   
   std::cout<<" Higgs pT = "<<Higgs.Pt()
	    <<" Ao pT = "<<vV.Pt()
	    <<std::endl;
   
   edm::Handle<LHEEventProduct> evt;
   if(iEvent.getByToken( lheEventToken, evt )){
     float sysLHEweight = evt->weights()[0].wgt/evt->weights()[0].wgt; 
     std::cout<< " sysLHEweight = "<<sysLHEweight<<std::endl;
   }
   
   tree_->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
MonoHGenTree2DScans::beginJob()
{
  
  //file = new TFile("output.root","RECREATE");
  //tree = new TTree("T","Signal Region");
  tree_->Branch("HiggsPt",&HiggsPt, "HiggsPt/f");
  tree_->Branch("HiggsEta",&HiggsEta, "HiggsEta/f");
  tree_->Branch("trueMET",&trueMET, "trueMET/f");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MonoHGenTree2DScans::endJob() 
{
  //  file->Write();
  //  file->Close();

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MonoHGenTree2DScans::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MonoHGenTree2DScans);
