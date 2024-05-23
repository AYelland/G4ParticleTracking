README File for G4ParticleTracking_v1.x

This is a verison fo the Geant4 Particle Tracking simulation used to develop the
larger Earth simulation with a dipole magnetic field. There are a couple of 
different version of this Geant4 CMake project. This one specifically has the 
following properties that differentiate it from the other versions.

  - Creates "devlogs" used for debugging (may lead to memory issues, so they are 
    commented out for larger runs)
  - Currently being developed to track down memory leak (TDirectory() -> ls)