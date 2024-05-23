#!/bin/bash
# Author: Alex Yelland

# source /afs/cern.ch/user/a/ayelland/.geant4rc_sh
source /afs/cern.ch/user/a/ayelland/.bashrc
# source /afs/cern.ch/user/a/ayelland/software/AMS02/amsvar_B550_cc534_2.sh

################################################################################

exeDir=$1
exeName=$2
macFiles=$3
rootDir=$4
rootName=$5

echo ""
echo "1=${exeDir}"
echo "2=${exeName}"
echo "3=${macFiles}"
echo "4=${rootDir}"
echo "5=${rootName}"
echo ""

cd ${exeDir}
./${exeName} ${macFiles} ${rootDir} ${rootName}
cd -