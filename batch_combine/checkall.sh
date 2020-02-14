#!/bin/sh
#
# Run over all root files
#

echo $USER

path=/home/${USER}/slepton/ParallelSleptons/batch_scripts/datalists2
flistfile=${path}/All.flist

rpath=/home/${USER}/slepton/ParallelSleptons/ExecutionDirectory

for lfile in $(cat ${flistfile})

do
#   echo ' '
   name=$(echo "$lfile" | cut -f 1 -d '.')
#   echo $name
#   listfile=${name}.list

   rootfile=${rpath}/${name}/susyHists.root
   echo ${rootfile}

#   root -l -b -q 'mismatch.C("\$rootfile")'

#   root -l -b -q 'mismatch.C("/home/graham/slepton/ParallelSleptons/ExecutionDirectory/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X/susyHists.root")'

#OK make this simple by making a local symbolic link

   ln -s ${rootfile} MyFile.root

   root -l -b -q 'mismatch.C("MyFile.root")'

   rm MyFile.root

#   cmd="/home/graham/slepton/ParallelSleptons/batch_combine/mismatch.C(\"${rootfile}\")"
#   echo $cmd

#   pwd

#   cmd2="root -l -b -q '$cmd'"
#   echo $cmd2

#   $cmd2

#   root -l -b -q "mismatch.C(\"All.root\")"

    echo ' '
    echo ' '

done

exit
