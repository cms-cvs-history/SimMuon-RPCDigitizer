#include "FWCore/Framework/interface/EDProducer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "SimMuon/RPCDigitizer/src/RPCSimSetUp.h"
#include "SimMuon/RPCDigitizer/src/RPCDigiProducer.h"
#include "SimMuon/RPCDigitizer/src/RPCDigitizer.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimMuon/RPCDigitizer/src/RPCSynchronizer.h"
#include <sstream>
#include <string>

#include <map>
#include <vector>

#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"

RPCDigiProducer::RPCDigiProducer(const edm::ParameterSet& ps) {

  theRPCSimSetUp =  new RPCSimSetUp(ps);
  theDigitizer = new RPCDigitizer(ps);

  produces<RPCDigiCollection>();
  produces<RPCDigitizerSimLinks>("RPCDigiSimLink");

<<<<<<< RPCDigiProducer.cc
  //Name of Collection used for create the XF 
  collection_for_XF = ps.getParameter<std::string>("InputCollection");
=======
  //Name of Collection used for create the XF
  collection_for_XF = ps.getParameter<std::string>("InputCollection");
>>>>>>> 1.17
}

RPCDigiProducer::~RPCDigiProducer() {
  delete theDigitizer;
  delete theRPCSimSetUp;
}

void RPCDigiProducer::produce(edm::Event& e, const edm::EventSetup& eventSetup) {

  edm::Handle<CrossingFrame<PSimHit> > cf;
<<<<<<< RPCDigiProducer.cc
  e.getByLabel("mix", collection_for_XF, cf);
=======
  e.getByLabel("mix", collection_for_XF, cf);

  // test access to SimHits
  //  const std::string hitsName("MuonRPCHits");
>>>>>>> 1.17

  std::auto_ptr<MixCollection<PSimHit> > 
    hits( new MixCollection<PSimHit>(cf.product()) );

  // find the geometry & conditions for this event
  edm::ESHandle<RPCGeometry> hGeom;
  eventSetup.get<MuonGeometryRecord>().get( hGeom );
  const RPCGeometry *pGeom = &*hGeom;

  edm::ESHandle<RPCStripNoises> noiseRcd;
  eventSetup.get<RPCStripNoisesRcd>().get(noiseRcd);

  theRPCSimSetUp->setRPCSetUp(noiseRcd->getVNoise(), noiseRcd->getCls());

  theDigitizer->setGeometry( pGeom );
  theRPCSimSetUp->setGeometry( pGeom );
  theDigitizer->setRPCSimSetUp( theRPCSimSetUp );

  // Create empty output
  std::auto_ptr<RPCDigiCollection> pDigis(new RPCDigiCollection());
  std::auto_ptr<RPCDigitizerSimLinks> RPCDigitSimLink(new RPCDigitizerSimLinks() );

  // run the digitizer
  theDigitizer->doAction(*hits, *pDigis, *RPCDigitSimLink);

  // store them in the event
  e.put(pDigis);
  e.put(RPCDigitSimLink,"RPCDigiSimLink");
}

