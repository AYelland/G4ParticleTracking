#ifndef STEPPING_HH
#define STEPPING_HH

#include "Globals.hh"

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

// User Headers
#include "MyDetectorConstruction.hh"
#include "MyEventAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MySteppingAction : public G4UserSteppingAction 
{
  public:
    MySteppingAction(MyEventAction *eventAction);
    ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    MyEventAction *fEventAction;

    const G4Step *fStep;

    G4VPhysicalVolume* fPreviousVolume;
    G4VPhysicalVolume* fCurrentVolume;
};

#endif