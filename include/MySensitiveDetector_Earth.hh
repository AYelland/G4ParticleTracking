#ifndef SENSITIVE_DETECTOR_EARTH_HH
#define SENSITIVE_DETECTOR_EARTH_HH

#include "Globals.hh"

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MySensitiveDetector_Earth : public G4VSensitiveDetector
{
  public:
      MySensitiveDetector_Earth(G4String);
      ~MySensitiveDetector_Earth();

  private:
    virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};

#endif