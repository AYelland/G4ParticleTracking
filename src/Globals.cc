#include "Globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

std::string runDate = "";
std::string runTime = "";

std::string workDirectory = "/afs/cern.ch/work/a/ayelland/geant4/particleTracking";

std::string macroFile = "";
std::string outputDirectory = "";
std::string outputFile = "";

#if HTCONDOR
    const std::string devlog_dir = workDirectory+"/output_condor/devlog";
#else 
    const std::string devlog_dir = workDirectory+"/output_local/devlog";
#endif

std::ofstream devLog(devlog_dir+"/execution.log");

