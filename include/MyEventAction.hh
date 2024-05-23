#ifndef EVENT_HH
#define EVENT_HH

#include "Globals.hh"

// Unit Headers
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

// Geant4 Base Headers
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4Step.hh"

// User Defined Headers
#include "MyRunAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MyEventAction : public G4UserEventAction
{

  public:
    MyEventAction(MyRunAction*);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void SaveParticleData(const G4Step*);

  private:
  
};

#endif