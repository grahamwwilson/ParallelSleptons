#!/bin/sh
# runmyanalysis.sh

USER=gwwilson

date

CODEDIR=/home/${USER}/slepton/ParallelSleptons/sleptonAnalysis

INPUT=${1-dataHPC}
TREE=$2 
TAG=$3
echo ${INPUT} ${TREE} ${TAG}

INPUTLIST=/home/${USER}/slepton/ParallelSleptons/batch_scripts/datalists/${INPUT}.list

#Execute this from execution directory, so that we can have several output files in parallel

EXEDIR=/home/${USER}/slepton/ParallelSleptons/ExecutionDirectory/${INPUT}
rm -r ${EXEDIR}
# Check if it exists. If not make it.
mkdir ${EXEDIR}

cd ${EXEDIR}
pwd

#input is: num files, numthreads,  yourdata.list
# Note any change to the thread count needs to also be in the job description file ..
python2 ${CODEDIR}/runmacro.py 0 24 ${INPUTLIST} ${TREE} ${TAG} "susyHists.root" "RECREATE"

date

exit
