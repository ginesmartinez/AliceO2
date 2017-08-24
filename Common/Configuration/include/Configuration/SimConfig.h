// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#ifndef O2_SIM_CONFIGURATION
#define O2_SIM_CONFIGURATION

#include <Rtypes.h>

namespace o2
{
namespace conf
{
// A singleton class which can be used
// to centrally parse command line arguments and which can be queried
// from the various algorithms that need access to this information
// This is a quick/dirty solution allowing for some external configurability; A proper configuration scheme is currently
// being worked out;
class SimConfig
{
 private:
  SimConfig()
  {
    // activate from default parameters
    char* argv[] = {};
    resetFromArguments(1, argv);
  };

 public:
  static SimConfig& Instance()
  {
    static SimConfig conf;
    return conf;
  }

  // initializes the configuration from command line arguments
  // returns true if correctly initialized and not --help called
  bool resetFromArguments(int argc, char* argv[]);

  // get MC engine
  std::string getMCEngine() const { return mMCEngine; }
  // get selected active detectors
  std::vector<std::string> const& getActiveDetectors() const { return mActiveDetectors; }
  // get selected generator (to be used to select a genconfig)
  std::string getGenerator() const { return mGenerator; }
  unsigned int getNEvents() const { return mNEvents; }

  std::string getExtKinematicsFileName() const { return mExtKinFileName; }
  unsigned int getStartEvent() const { return mStartEvent; }

  bool isWithMagField() const { return mWithMagField; }
  bool isWithPhysicsProcs() const { return mWithPhysicsProcs; }
  
 private:
  std::vector<std::string> mActiveDetectors; //!< list active detectord
  std::string mMCEngine;                     //!< chosen VMC engine
  std::string mGenerator;                    //!< chosen VMC generator
  unsigned int mNEvents;                     //!< number of events to be simulated
  std::string mExtKinFileName;               //!< file name of external kinematics file (needed for ext kinematics generator)
  unsigned int mStartEvent;                  //!< index of first event to be taken

  bool mWithMagField = true; //!< switch on/off mag field (default on)
  bool mWithPhysicsProcs = true; //!< switch on/off physics processes (default on)
  
  ClassDefNV(SimConfig, 1);
};
}
}

#endif
