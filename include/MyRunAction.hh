#ifndef RUN_HH
#define RUN_HH

#include "Globals.hh"

#include <ctime>

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MyRunAction : public G4UserRunAction
{
  public:
    MyRunAction();
    ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

};

#endif