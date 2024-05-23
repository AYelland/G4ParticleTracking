#include "MyActionInitialization.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyActionInitialization::MyActionInitialization()
{
    devLog << "MyActionInitialization.cc" << std::endl;
    devLog << "\t Output Directory: " << outputDirectory << std::endl;
    devLog << "\t Output File: " << outputFile << std::endl;
    devLog << "" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyActionInitialization::~MyActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyActionInitialization::Build() const
{
    // Initialize Particle Gun Generator
    devLog << "MyPrimaryGeneratorAction.cc" << std::endl;
    devLog << "\t Worker Thread: Primary Generator Action" << std::endl;
    MyPrimaryGeneratorAction *generatorAction = new MyPrimaryGeneratorAction();
    SetUserAction(generatorAction);

    // Initialize Thread Local Run Action
    devLog << "MyRunAction.cc" << std::endl;
    devLog << "\t Worker Thread: Run Action" << std::endl;
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);

    devLog << "MyEventAction.cc" << std::endl;
    devLog << "\t Worker Thread: Event Action" << std::endl;
    MyEventAction *eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);

    devLog << "MySteppingAction.cc" << std::endl;
    devLog << "\t Worker Thread: Stepping Action" << std::endl;
    MySteppingAction *steppingAction = new MySteppingAction(eventAction);
    SetUserAction(steppingAction);

    devLog << "" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyActionInitialization::BuildForMaster() const
{
    #if MULTITHREADING
        // Initialize Thread Local Run Action
        devLog << "MyRunAction.cc" << std::endl;
        devLog << "\t Master Thread: Run Action" << std::endl;
        devLog << "" << std::endl;

        MyRunAction *runAction = new MyRunAction();
        SetUserAction(runAction);
    #endif
}