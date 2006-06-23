#ifndef SimMuon_RPCDigiReader_h
#define SimMuon_RPCDigiReader_h

/** \class RPCDigiReader
 *  Analyse the RPC digitizer (derived from R. Bellan DTDigiReader. 
 *  
 *  $Date: 2006/05/22 20:21:58 $
 *  $Revision: 1.2 $
 *  \authors: M. Maggi -- INFN Bari
 */

#include <FWCore/Framework/interface/EDAnalyzer.h>
#include <FWCore/Framework/interface/Event.h>
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <FWCore/Framework/interface/ESHandle.h>

#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"

#include <iostream>


class RPCDigiReader: public edm::EDAnalyzer{
  
public:
  explicit RPCDigiReader(const edm::ParameterSet& pset){
    label = pset.getUntrackedParameter<std::string>("label");
  }
  
  virtual ~RPCDigiReader(){
  }
  
  void analyze(const edm::Event & event, const edm::EventSetup& eventSetup){
   std:: cout << "--- Run: " << event.id().run()
	      << " Event: " << event.id().event() << std::endl;
   
   edm::Handle<RPCDigiCollection> rpcDigis;
   //   event.getByLabel(label, rpcDigis);
   //   event.getByLabel("MuonRPCDigi", rpcDigis);
   event.getByType(rpcDigis);
   edm::Handle<edm::PSimHitContainer> simHits; 
   event.getByLabel("SimG4Object","MuonRPCHits",simHits);    

   edm::ESHandle<RPCGeometry> pDD;
   eventSetup.get<MuonGeometryRecord>().get( pDD );
   
   RPCDigiCollection::DigiRangeIterator detUnitIt;
   for (detUnitIt=rpcDigis->begin();
	detUnitIt!=rpcDigis->end();
	++detUnitIt){
     
     const RPCDetId& id = (*detUnitIt).first;
     const RPCRoll* roll = dynamic_cast<const RPCRoll* >( pDD->roll(id));
     const RPCDigiCollection::Range& range = (*detUnitIt).second;
     
      // RPCDetId print-out
      std::cout<<"--------------"<<std::endl;
      std::cout<<"id: "<<id<<" number of strip "<<roll->nstrips()<<std::endl;
      
      // Loop over the digis of this DetUnit
      for (RPCDigiCollection::const_iterator digiIt = range.first;
	   digiIt!=range.second;
	   ++digiIt){
	std::cout<<" digi "<<*digiIt<<std::endl;
	if (digiIt->strip() < 1 || digiIt->strip() > roll->nstrips() ){
	  std::cout <<" XXXXXXXXXXXXX Problemt with "<<id<<std::endl;
	} 
	for(std::vector<PSimHit>::const_iterator simHit = 
	      simHits->begin();
	    simHit != simHits->end(); simHit++){
	  RPCDetId rpcId((*simHit).detUnitId());
	    if (rpcId==id && abs((*simHit).particleType())==13){
	      std::cout<<"entry: "<<(*simHit).entryPoint()<<std::endl
		       <<"exit: "<<(*simHit).exitPoint()<<std::endl
		       <<"TOF: "<<(*simHit).timeOfFlight()<<std::endl;
	    }
	}
      }// for digis in layer
    }// for layers
   std::cout<<"--------------"<<std::endl;
  }
  
private:
  std::string label;
};
#endif    
#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(RPCDigiReader)