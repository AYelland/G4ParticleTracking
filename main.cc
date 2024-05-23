#include "Globals.hh"

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"

// User Headers
#include "MyDetectorConstruction.hh"
#include "MyPhysicsList.hh"
#include "MyActionInitialization.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int main(int argc, char** argv)
{

    devLog << "main.cc" << std::endl;
    devLog << "" << std::endl;

    // Current Date and Time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::ostringstream oss_date;
    oss_date << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon
             << std::setw(2) << std::setfill('0') << ltm->tm_mday
             << std::setw(4) << std::setfill('0') << 1900 + ltm->tm_year;
    runDate = oss_date.str();

    std::ostringstream oss_time;
    oss_time << std::setw(2) << std::setfill('0') << ltm->tm_hour
             << std::setw(2) << std::setfill('0') << ltm->tm_min;
             // << std::setw(2) << std::setfill('0') << ltm->tm_sec;
    runTime = oss_time.str();

    // Reading in Arguments
    if (argc == 1) {
        #if HTCONDOR
            outputDirectory = workDirectory+"/output_condor/root/"+runDate+"_"+runTime;
        #else
            outputDirectory = workDirectory+"/output_local/root/"+runDate+"_"+runTime;
        #endif
        if (!std::filesystem::exists(outputDirectory)) {
            std::filesystem::create_directories(outputDirectory);
        }
        outputFile = runDate+"_"+runTime;

        // devLog << "\t Visual Mode" << std::endl;
        // devLog << "\t Output Directory: " << outputDirectory << std::endl;
        // devLog << "\t Output File: " << outputFile << std::endl;
    }
    else if (argc == 2) {
        macroFile = argv[1];

        #if HTCONDOR
            outputDirectory = workDirectory+"/output_condor/root/"+runDate+"_"+runTime+"_"+macroFile.substr(0, macroFile.find_last_of('.'));
        #else
            outputDirectory = workDirectory+"/output_local/root/"+runDate+"_"+runTime+"_"+macroFile.substr(0, macroFile.find_last_of('.'));
        #endif
        if (!std::filesystem::exists(outputDirectory)) {
            std::filesystem::create_directories(outputDirectory);
        }
        outputFile = runDate+"_"+runTime+"_"+macroFile.substr(0, macroFile.find_last_of('.'));

        // devLog << "\t Batch Mode" << std::endl;
        // devLog << "\t Macro File: " << macroFile << std::endl;
        // devLog << "\t Output Directory: " << outputDirectory << std::endl;
        // devLog << "\t Output File: " << outputFile << std::endl;
    }
    else if (argc == 3) {
        macroFile = argv[1];
        std::string fullPathStr = argv[2];

        size_t lastSlashPos = fullPathStr.find_last_of('/');
        if (lastSlashPos != std::string::npos) {
            outputDirectory = fullPathStr.substr(0, lastSlashPos);
            outputFile = fullPathStr.substr(lastSlashPos + 1);
        } else {
            #if HTCONDOR
                outputDirectory = workDirectory+"/output_condor/root/"+runDate+"_"+runTime+"_"+macroFile.substr(0, macroFile.find_last_of('.'));
            #else
                outputDirectory = workDirectory+"/output_local/root/"+runDate+"_"+runTime+"_"+macroFile.substr(0, macroFile.find_last_of('.'));
            #endif
            outputFile = fullPathStr;
        }
        if (!std::filesystem::exists(outputDirectory)) {
            std::filesystem::create_directories(outputDirectory);
        }

        // devLog << "\t Batch Mode" << std::endl;
        // devLog << "\t Macro File: " << macroFile << std::endl;
        // devLog << "\t Output Directory: " << outputDirectory << std::endl;
        // devLog << "\t Output File: " << outputFile << std::endl;
    }
    else if (argc == 4) {
        macroFile = argv[1];
        outputDirectory = argv[2];
        outputFile = argv[3];

        if (!std::filesystem::exists(outputDirectory)) {
            std::filesystem::create_directories(outputDirectory);
        }

        // devLog << "\t Batch Mode" << std::endl;
        // devLog << "\t Macro File: " << macroFile << std::endl;
        // devLog << "\t Output Directory: " << outputDirectory << std::endl;
        // devLog << "\t Output File: " << outputFile << std::endl;
    }
    else {
        // devLog << "\t ERROR: Too Many Arguments" << std::endl;
        // devLog << "\t Exiting..." << std::endl;
        return 1;
    }

    // The Run Manager
    #if MULTITHREADING
        G4MTRunManager *runManager = new G4MTRunManager();
        // devLog << "\t Multi Threaded" << std::endl;
    #else
        G4RunManager *runManager = new G4RunManager();
        // devLog << "\t Single Threaded" << std::endl;
    #endif
    runManager -> SetUserInitialization(new MyDetectorConstruction());
    runManager -> SetUserInitialization(new MyPhysicsList());
    runManager -> SetUserInitialization(new MyActionInitialization());

    // #if ATMOSPHERE_CONSTRUCTION
    //   G4VModularPhysicsList *physics = new QGSP_BERT(); // (Hadronic PhysicsList from QGSP_BERT.hh)
    //   physics -> RegisterPhysics(new G4DecayPhysics());
    //   runManager -> SetUserInitialization(physics);
    // #endif

    // UI Manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (argc == 1 ) { // "Interactive (UI) Mode"
        // Visualization Manager
        G4VisManager *visManager = new G4VisExecutive();
        visManager -> Initialize();

        G4UIExecutive *UIExecutive = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        UIExecutive -> SessionStart();

        delete visManager;
        delete UIExecutive;
    }
    else { // "Batch Mode"
        UImanager->ApplyCommand("/control/execute "+macroFile);
    }

    // Job termination
    delete runManager;

    return 0;
}