#ifndef ACTION_HH
#define ACTION_HH

#include "Globals.hh"

#include "G4VUserActionInitialization.hh"

// User Headers
#include "MyPrimaryGeneratorAction.hh"
#include "MyRunAction.hh"
#include "MyEventAction.hh"
#include "MySteppingAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MyActionInitialization : public G4VUserActionInitialization
{
  public:
    MyActionInitialization();
    ~MyActionInitialization();

    virtual void Build() const;
    virtual void BuildForMaster() const;
};

#endif 