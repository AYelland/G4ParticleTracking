#ifndef SENSITIVE_DETECTOR_ATMOSPHERE_HH
#define SENSITIVE_DETECTOR_ATMOSPHERE_HH

#include "Globals.hh"

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MySensitiveDetector_Atmosphere : public G4VSensitiveDetector
{
  public:
      MySensitiveDetector_Atmosphere(G4String);
      ~MySensitiveDetector_Atmosphere();

  private:
    virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};

#endif