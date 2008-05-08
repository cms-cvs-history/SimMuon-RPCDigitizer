#ifndef RPCSimSetUp_h
#define RPCSimSetUp_h

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include<cstring>
#include<string>
#include<stdlib.h>
#include <utility>

class RPCDigitizer;
class RPCGeometry;
class RPCDetId;

class RPCSimSetUp
{
public:

  explicit RPCSimSetUp(const edm::ParameterSet& ps);
  virtual ~RPCSimSetUp();

  std::vector<float> getNoise(uint32_t id);
  std::vector<float> getEff(uint32_t id);
  float getTime(uint32_t id);
  std::map< int, std::vector<double> > getClsMap();

  /// sets geometry
  void setGeometry(const RPCGeometry * geom) {theGeometry = geom;}
  const RPCGeometry * getGeometry() { return theGeometry; }

  const RPCGeometry * theGeometry;
private:

  std::map<uint32_t, std::vector<float> > _mapDetIdNoise;
  std::map<uint32_t, std::vector<float> > _mapDetIdEff;
  std::map<RPCDetId, float> _bxmap;
  std::map< int, std::vector<double> > _clsMap;

  std::ifstream *_infile1;
  std::ifstream *_infile2;
  std::ifstream *_infile3;
  std::ifstream *_infile4;

};

#endif