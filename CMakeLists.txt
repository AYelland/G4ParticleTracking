#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.16...3.21)
project(my_simulation)

#----------------------------------------------------------------------------
# User Defined Variables
#
add_compile_definitions(MULTITHREADING=1)
add_compile_definitions(N2ATMOSPHERE=1)
add_compile_definitions(USATMOSPHERE=0)
add_compile_definitions(HTCONDOR=0)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Find ROOT package
#
# find_package(ROOT REQUIRED COMPONENTS Core RIO Tree)

#----------------------------------------------------------------------------
# Setup Geant4 and ROOT include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
# include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Locate sources, headers, macros, & data files for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB MACRO_FILES ${PROJECT_SOURCE_DIR}/macro/*.mac)
file(GLOB DATA_FILES ${PROJECT_SOURCE_DIR}/data/*.dat)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(main main.cc ${sources} ${headers})
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, the executable directly
# relies on these scripts being in the current working directory.

# foreach(_script ${UISOURCE_SCRIPTS})
#   configure_file(
#     ${PROJECT_SOURCE_DIR}/${_script}
#     ${PROJECT_BINARY_DIR}/${_script}
#     COPYONLY
#     )
# endforeach()

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

#----------------------------------------------------------------------------
# For internal Geant4 use
#
add_custom_target(my_simulation DEPENDS main)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS main DESTINATION bin )





