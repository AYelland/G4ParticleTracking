#!/bin/bash
# Author: Alex Yelland

DATE=`date +%m%d%Y_%H%M`
SCRIPTDIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

##################################################

PROJECTDIR=/afs/cern.ch/user/a/ayelland/public/geant4/G4ParticleTracking_v1.0
WORKDIR=/afs/cern.ch/work/a/ayelland/geant4

##################################################

# Number of Runs per Batch Job (nrun)
nrun=10

# Allowed CPU Time - seconds (subqueue) 
subqueue=172800 #48 hours

# Number of CPUs per Job (request)
request=30 # YOU MUST ALSO CHANGE THIS IN THE MACROFILE!!!

# Error Catching & Reporting Script (protest)
protest=${PROJECTDIR}/subjobcondor/protest.sh

##################################################

# My Executable File & Directory (cfile, exeDir)
exeDir=${PROJECTDIR}/build
exeName=main

# My Input Files Directory (macDir)
macDir=${PROJECTDIR}/macro
macType="1e4proton"
macFiles=(`ls ${macDir} | grep ${macType}`)

# Output Directory (outputDir)
outputDir=${WORKDIR}/output_condor
[ ! -e  ${outputDir} ] && mkdir -p ${outputDir}

##################################################

## "*.out" Output Files (outName, outDir)
outName="${DATE}_${macType}_${nrun}runs"
outDir=${outputDir}/out/${outName}
[ ! -e  ${outDir} ] && mkdir -p ${outDir}
  # if ls ${outDir} | grep .out ; then
  #   rm ${outDir}/*.out
  # fi

## "*.root" Output Files (rootDir)
rootName=${outName}
rootDir=${outputDir}/root/${rootName}
[ ! -e  ${rootDir} ] && mkdir -p ${rootDir}
  # if ls ${rootDir} | grep .root ; then
  #   rm ${rootDir}/*.root
  # fi

## "*.txt" Output Files (txtName, txtDir)
txtName=${outName}
txtDir=${outputDir}/txt/${txtName}
[ ! -e  ${txtDir} ] && mkdir -p ${txtDir}
  # if ls ${txtDir} | grep .txt ; then
  #   rm ${txtDir}/*.txt
  # fi

## "*.log" Output Files (logName, logDir)
logName=${outName}
logDir=${outputDir}/log/${logName}
[ ! -e  ${logDir} ] && mkdir -p ${logDir}
  # if ls ${logDir} | grep log ; then
  #   rm ${logDir}/*.log
  # fi

## Developers Log File Directory (devlogDir)
devlogDir=${outputDir}/devlog
[ ! -e  ${devlogDir} ] && mkdir -p ${devlogDir}

## "*.err" Output Files (errName, errDir)
errName=${outName}
errDir=${outputDir}/err/${errName}
[ ! -e  ${errDir} ] && mkdir -p ${errDir}
  # if ls ${errDir} | grep err ; then
  #   rm ${errDir}/*.err
  # fi

##################################################
# Generate the Condor Submit File

function create_submit() {
  echo "##################################################"
  echo "# HTCondor Submit File, by Alex Yelland"
  echo "##################################################"
  echo "universe = vanilla"
  echo "+MaxRuntime = ${subqueue}"
  echo "RequestCpus = ${request}"
  echo "executable = ${protest}"
  echo "arguments = ${exeDir} ${exeName} ${macFiles} ${rootDir} ${rootName}" #${nrun} ${txtDir} ${outName} ${outDir}"
  echo 'ID = $(ClusterId).$(ProcId)'
  echo "output =${outDir}/${outName}_\$(ID).out"
  echo "error =${errDir}/${errName}_\$(ID).err"
  echo "log =${logDir}/${logName}_\$(ID).log"
  echo "should_transfer_files = YES"
  echo "when_to_transfer_output = ON_EXIT"
  echo "notify_user = alexander.michael.yelland@cern.ch"
  echo "notification = always"
  echo "queue ${nrun}"
}

[ ! -e  ${SCRIPTDIR}/submits ] && mkdir -p ${SCRIPTDIR}/submits
submitName=submits/${outName}
create_submit > ${submitName}.sh


##################################################
# Copy Macro Files & Submit Script to Txt Directory

echo "# -------------------------------------------------------------------- #" >> "${txtDir}/${txtName}.txt"
echo "" >> "${txtDir}/${txtName}.txt"
cat ${SCRIPTDIR}/${submitName}.sh >> "${txtDir}/${txtName}.txt"
echo "" >> "${txtDir}/${txtName}.txt"

for file in "${macFiles[@]}"
do
  echo "# -------------------------------------------------------------------- #" >> "${txtDir}/${txtName}.txt"
  echo "" >> "${txtDir}/${txtName}.txt"
  echo "# MACROFILE: '${file}':" >> "${txtDir}/${txtName}.txt"
  echo "" >> "${txtDir}/${txtName}.txt"
  cat "${macDir}/${file}" >> "${txtDir}/${txtName}.txt"
  echo "" >> "${txtDir}/${txtName}.txt"
done

##################################################
# Submit the Condor Job

condor_submit ${submitName}.sh -batch-name ${submitName}


##################################################
##################################################
# Artifact from Q. Yan's Condor Submit Script

# # Iterator through Condor Submit Files (begnam, endnam)
# begnam=1
# endnam=999999

# itxt=0 #iterator through txt files
# contrun=$(($nrun+1)) #number of runs in current txt file (starts at nrun+1 to force new txt file)
# # echo $contrun
# befrun=0 #previous run number (before current run number)

# for  ((i=0; i<${#macfile[@]}; i++ ))
#     do
#         ifile=${macfile[i]}
#         if ! echo "$ifile" | grep -q ".root" ; then
#             continue
#         fi
#         # echo $ifile
#         run=`echo $ifile| cut -f 2 -d "_"`
#         run=`echo $run| cut -f 1 -d "."`
#         if [ ${run:0:1} -eq '0' ]; then  #remove zero 
#             run=${run:1}
#         fi
#         [[ ${begnam} != 0 && ${run} < ${begnam} ]] && befrun=${run} && continue
#         [[ ${endnam} != 0 && ${run} > ${endnam} ]] && befrun=${run} && break
#     #  echo $run
#     #  echo $befrun 
#     if [ $contrun -ge $nrun ] && [ $run != $befrun ] ; then
#         txtfil[$itxt]="${txtDir}/${run}_${nrun}.in"
#         [ -e ${txtfil[$itxt]} ] && rm ${txtfil[$itxt]}
#         itxt=$(($itxt+1))
#         contrun=0
#     fi
#     echo -e "$macDir/$ifile" >> ${txtfil[$(($itxt-1))]}
#     if [ $run != $befrun ] ; then
#         contrun=$((${contrun}+1))
#     fi
#     befrun=$run
# done
