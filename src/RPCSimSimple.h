#ifndef RPCDigitizer_RPCSimSimple_h
#define RPCDigitizer_RPCSimSimple_h

/** \class RPCSimSimple
 *   Class for the RPC strip response simulation based
 *   on a very simple model
 *
 *  \author Marcello Maggi -- INFN Bari
 */
#include "SimMuon/RPCDigitizer/src/RPCSim.h"

class RPCSimSimple : public RPCSim
{
 public:
  RPCSimSimple(){}
  ~RPCSimSimple(){}
  void simulate(const RPCRoll* roll,
			const edm::PSimHitContainer& rpcHits );
  void fillDigis(int rollDetId, RPCDigiCollection& digis);
 private:
  void init(){};
};
#endif
