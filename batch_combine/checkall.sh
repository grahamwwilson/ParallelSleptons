#!/bin/sh
#
# Run over all specified root files 
# testing to see whether there is a mismatch in the event counts 
# that appears to be a symptom of a race condition.
#

echo $USER

path=/home/${USER}/slepton/ParallelSleptons/batch_scripts/datalists2
flistfile=${path}/Faults.flist

rpath=/home/${USER}/slepton/ParallelSleptons/ExecutionDirectory

for lfile in $(cat ${flistfile})

do
   name=$(echo "$lfile" | cut -f 1 -d '.')
   rootfile=${rpath}/${name}/susyHists.root
   echo ${rootfile}

#Make this simple by making a local symbolic link
   if [ -s ${rootfile} ]
   then
 
       ln -s ${rootfile} MyFile.root
       root -l -b -q 'mismatch.C("MyFile.root")'
       rm MyFile.root
   fi
   echo ' '
   echo ' '

done

exit
