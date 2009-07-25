#include <iostream>
//

#include "Validation/RecoEgamma/interface/PhotonPostprocessing.h"


//#define TWOPI 6.283185308
// 

/** \class PhotonPostprocessing
 **  
 **
 **  $Id: PhotonPostprocessing
 **  $Date: 2009/07/24 18:39:18 $ 
 **  author: 
 **   Nancy Marinelli, U. of Notre Dame, US  
 **   
 **     
 ***/



using namespace std;

 
PhotonPostprocessing::PhotonPostprocessing(const edm::ParameterSet& pset) 
{

  dbe_ = 0;
  dbe_ = edm::Service<DQMStore>().operator->();
  dbe_->setVerbose(0);
  parameters_ = pset;


  standAlone_ = pset.getParameter<bool>("standAlone");
  batch_ = pset.getParameter<bool>("batch");
  outputFileName_ = pset.getParameter<string>("OutputFileName");
  inputFileName_  = pset.getParameter<std::string>("InputFileName");



 

}



PhotonPostprocessing::~PhotonPostprocessing()
{}

void PhotonPostprocessing::beginJob( const edm::EventSetup& setup)
{

}

void PhotonPostprocessing::analyze(const edm::Event& e, const edm::EventSetup& esup)
{}


void PhotonPostprocessing::endJob()
{

  double etMin = parameters_.getParameter<double>("etMin");
  double etMax = parameters_.getParameter<double>("etMax");
  int etBin = parameters_.getParameter<int>("etBin");


  double etaMin = parameters_.getParameter<double>("etaMin");
  double etaMax = parameters_.getParameter<double>("etaMax");
  int etaBin = parameters_.getParameter<int>("etaBin");
  int etaBin2 = parameters_.getParameter<int>("etaBin2");

  double phiMin = parameters_.getParameter<double>("phiMin");
  double phiMax = parameters_.getParameter<double>("phiMax");
  int    phiBin = parameters_.getParameter<int>("phiBin");

  double rMin = parameters_.getParameter<double>("rMin");
  double rMax = parameters_.getParameter<double>("rMax");
  int    rBin = parameters_.getParameter<int>("rBin");

  double zMin = parameters_.getParameter<double>("zMin");
  double zMax = parameters_.getParameter<double>("zMax");
  int    zBin = parameters_.getParameter<int>("zBin");


  std::string simInfoPathName = "EgammaV/PhotonValidator/SimulationInfo/";
  std::string convPathName    = "EgammaV/PhotonValidator/ConversionInfo/";
  std::string effPathName     = "EgammaV/PhotonValidator/Efficiencies/";


  if(batch_)  dbe_->open(inputFileName_);

  dbe_->setCurrentFolder(effPathName);
  //  Photon reconstruction efficiencies
  string histname = "recoEffVsEta";
  phoRecoEffEta_ =  dbe_->book1D(histname,"Photon reconstruction efficiency vs simulated #eta",etaBin,etaMin, etaMax);
  histname = "recoEffVsPhi";
  phoRecoEffPhi_ =  dbe_->book1D(histname,"Photon reconstruction efficiency vs simulated #phi",phiBin,phiMin, phiMax);
  histname = "recoEffVsEt";
  phoRecoEffEt_ =  dbe_->book1D(histname,"Photon reconstruction efficiency vs simulated Et",etBin,etMin, etMax) ;
  // Fraction of photons with at least one dead channel
  histname = "deadChVsEta";
  phoDeadChEta_ =  dbe_->book1D(histname,"Fraction of photons with >=1 dead Xtal vs simulated #eta",etaBin,etaMin, etaMax);
  histname = "deadChVsPhi";
  phoDeadChPhi_ =  dbe_->book1D(histname,"Fraction of photons with >=1 dead Xtal vs simulated #phi",phiBin,phiMin, phiMax);
  histname = "deadChVsEt";
  phoDeadChEt_ =  dbe_->book1D(histname,"Fraction of photons with >=1 dead Xtal vs simulated Et",etBin,etMin, etMax) ;

  // Conversion reconstruction efficiency
  histname = "convEffVsEtaTwoTracks";
  convEffEtaTwoTracks_ =  dbe_->book1D(histname,histname,etaBin2,etaMin, etaMax);

  histname = "convEffVsPhiTwoTracks";
  convEffPhiTwoTracks_ =  dbe_->book1D(histname,histname,phiBin,phiMin,phiMax);

  histname = "convEffVsRTwoTracks";
  convEffRTwoTracks_ =  dbe_->book1D(histname,histname,rBin,rMin, rMax);

  histname = "convEffVsZTwoTracks";
  convEffZTwoTracks_ =  dbe_->book1D(histname,histname,zBin,zMin,zMax);

  histname = "convEffVsEtTwoTracks";
  convEffEtTwoTracks_ =  dbe_->book1D(histname,histname,etBin,etMin, etMax);
  // 
  histname = "convEffVsEtaTwoTracksAndVtxProbGT0";
  convEffEtaTwoTracksAndVtxProbGT0_ =  dbe_->book1D(histname,histname,etaBin2,etaMin, etaMax);
  histname = "convEffVsEtaTwoTracksAndVtxProbGT005";
  convEffEtaTwoTracksAndVtxProbGT005_ =  dbe_->book1D(histname,histname,etaBin2,etaMin, etaMax);
  histname = "convEffVsRTwoTracksAndVtxProbGT0";
  convEffRTwoTracksAndVtxProbGT0_ =  dbe_->book1D(histname,histname,rBin,rMin,rMax);
  histname = "convEffVsRTwoTracksAndVtxProbGT005";
  convEffRTwoTracksAndVtxProbGT005_ =  dbe_->book1D(histname,histname,rBin,rMin,rMax);
  //
  histname = "convEffVsEtaOneTrack";
  convEffEtaOneTrack_ =  dbe_->book1D(histname,histname,etaBin2,etaMin, etaMax);
  histname = "convEffVsROneTrack";
  convEffROneTrack_ =  dbe_->book1D(histname,histname,rBin,rMin, rMax);
  histname = "convEffVsEtOneTrack";
  convEffEtOneTrack_ =  dbe_->book1D(histname,histname,etBin,etMin, etMax);
  // Fake rate
  histname = "convFakeRateVsEtaTwoTracks";
  convFakeRateEtaTwoTracks_ =  dbe_->book1D(histname,histname,etaBin2,etaMin, etaMax);
  histname = "convFakeRateVsPhiTwoTracks";
  convFakeRatePhiTwoTracks_ =  dbe_->book1D(histname,histname,phiBin,phiMin,phiMax);
  histname = "convFakeRateVsRTwoTracks";
  convFakeRateRTwoTracks_ =  dbe_->book1D(histname,histname,rBin,rMin, rMax);
  histname = "convFakeRateVsZTwoTracks";
  convFakeRateZTwoTracks_ =  dbe_->book1D(histname,histname,zBin,zMin,zMax);
  histname = "convFakeRateVsEtTwoTracks";
  convFakeRateEtTwoTracks_ =  dbe_->book1D(histname,histname,etBin,etMin, etMax);

  
  // efficiencies
  dividePlots(dbe_->get(effPathName+"recoEffVsEta"),dbe_->get(simInfoPathName+"h_MatchedSimPhoEta"),dbe_->get(simInfoPathName+"h_SimPhoEta"), "effic");
  dividePlots(dbe_->get(effPathName+"recoEffVsPhi"),dbe_->get(simInfoPathName+"h_MatchedSimPhoPhi"),dbe_->get(simInfoPathName+"h_SimPhoPhi"),"effic");
  dividePlots(dbe_->get(effPathName+"recoEffVsEt"),dbe_->get(simInfoPathName+"h_MatchedSimPhoEt"),dbe_->get(simInfoPathName+"h_SimPhoEt"),"effic");
  // fraction of photons with at least one dead channel
  dividePlots(dbe_->get(effPathName+"deadChVsEta"),dbe_->get(simInfoPathName+"h_MatchedSimPhoBadChEta"),dbe_->get(simInfoPathName+"h_MatchedSimPhoEta"), "effic");
  dividePlots(dbe_->get(effPathName+"deadChVsPhi"),dbe_->get(simInfoPathName+"h_MatchedSimPhoBadChPhi"),dbe_->get(simInfoPathName+"h_MatchedSimPhoPhi"),"effic");
  dividePlots(dbe_->get(effPathName+"deadChVsEt"), dbe_->get(simInfoPathName+"h_MatchedSimPhoBadChEt"),dbe_->get(simInfoPathName+"h_MatchedSimPhoEt"),"effic");
  //
  dividePlots(dbe_->get(effPathName+"convEffVsEtaTwoTracks"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksEta"),dbe_->get(simInfoPathName+"h_VisSimConvEta"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsPhiTwoTracks"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksPhi"),dbe_->get(simInfoPathName+"h_VisSimConvPhi"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsRTwoTracks"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksR"),dbe_->get(simInfoPathName+"h_VisSimConvR"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsZTwoTracks"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksZ"),dbe_->get(simInfoPathName+"h_VisSimConvZ"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsEtTwoTracks"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksEt"),dbe_->get(simInfoPathName+"h_VisSimConvEt"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsEtaTwoTracksAndVtxProbGT0"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksEtaAndVtxPGT0"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksEta"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsEtaTwoTracksAndVtxProbGT005"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksEtaAndVtxPGT005"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksEta"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsRTwoTracksAndVtxProbGT0"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksRAndVtxPGT0"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksR"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsRTwoTracksAndVtxProbGT005"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksRAndVtxPGT005"),dbe_->get(simInfoPathName+"h_SimConvTwoMTracksR"),"effic");
  //
  dividePlots(dbe_->get(effPathName+"convEffVsEtaOneTrack"),dbe_->get(simInfoPathName+"h_SimConvOneMTracksEta"),dbe_->get(simInfoPathName+"h_VisSimConvEta"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsROneTrack"),dbe_->get(simInfoPathName+"h_SimConvOneMTracksR"),dbe_->get(simInfoPathName+"h_VisSimConvR"),"effic");
  dividePlots(dbe_->get(effPathName+"convEffVsEtOneTrack"),dbe_->get(simInfoPathName+"h_SimConvOneMTracksEt"),dbe_->get(simInfoPathName+"h_VisSimConvEt"),"effic");
  // fake rate
  dividePlots(dbe_->get(effPathName+"convFakeRateVsEtaTwoTracks"),dbe_->get(convPathName+"h_RecoConvTwoMTracksEta"),dbe_->get(convPathName+"h_RecoConvTwoTracksEta"),"fakerate");
  dividePlots(dbe_->get(effPathName+"convFakeRateVsPhiTwoTracks"),dbe_->get(convPathName+"h_RecoConvTwoMTracksPhi"),dbe_->get(convPathName+"h_RecoConvTwoTracksPhi"),"fakerate");
  dividePlots(dbe_->get(effPathName+"convFakeRateVsRTwoTracks"),dbe_->get(convPathName+"h_RecoConvTwoMTracksR"),dbe_->get(convPathName+"h_RecoConvTwoTracksR"),"fakerate");
  dividePlots(dbe_->get(effPathName+"convFakeRateVsZTwoTracks"),dbe_->get(convPathName+"h_RecoConvTwoMTracksZ"),dbe_->get(convPathName+"h_RecoConvTwoTracksZ"),"fakerate");
  dividePlots(dbe_->get(effPathName+"convFakeRateVsEtTwoTracks"),dbe_->get(convPathName+"h_RecoConvTwoMTracksEt"),dbe_->get(convPathName+"h_RecoConvTwoTracksEt"),"fakerate");
  


  if(standAlone_) dbe_->save(outputFileName_);
  else if(batch_) dbe_->save(inputFileName_);
}


void PhotonPostprocessing::endLuminosityBlock(const edm::LuminosityBlock& lumi, const edm::EventSetup& setup)
{

 
}



void  PhotonPostprocessing::dividePlots(MonitorElement* dividend, MonitorElement* numerator, MonitorElement* denominator, std::string type ){
  double value,err;
  for (int j=1; j<=numerator->getNbinsX(); j++){

    if (denominator->getBinContent(j)!=0){
      if (type=="effic")
	value = ((double) numerator->getBinContent(j))/((double) denominator->getBinContent(j));
      else if (type=="fakerate")
	value = 1-((double) numerator->getBinContent(j))/((double) denominator->getBinContent(j));
      else return; 
      err = sqrt( value*(1-value) / ((double) denominator->getBinContent(j)) );
      dividend->setBinContent(j, value);
      if ( err !=0 ) dividend->setBinError(j,err);
    }
    else {
      dividend->setBinContent(j, 0);
      dividend->setBinError(j,0);
    }

  }


}


void  PhotonPostprocessing::dividePlots(MonitorElement* dividend, MonitorElement* numerator, double denominator){
  double value,err;

  for (int j=1; j<=numerator->getNbinsX(); j++){
    if (denominator!=0){
      value = ((double) numerator->getBinContent(j))/denominator;
      err = sqrt( value*(1-value) / denominator);
      dividend->setBinContent(j, value);
      dividend->setBinError(j,err);
    }
    else {
      dividend->setBinContent(j, 0);
    }
  }

}

