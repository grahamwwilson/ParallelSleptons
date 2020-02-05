#!/bin/sh
#
# 
#
echo $ROOTSYS
path=/home/gwwilson/slepton/ParallelSleptons/batch_scripts/datalists2
fl=ZJets
flistfile=${path}/${fl}.flist

rpath=/home/gwwilson/slepton/ParallelSleptons/ExecutionDirectory

ofile=${fl}.root

for lfile in $(cat ${flistfile})

do
   name=$(echo "$lfile" | cut -f 1 -d '.')
   echo $name
   rfile=${rpath}/${name}/susyHists.root

   if [ ! -f tmp.root ]
   then
# first file
      cp ${rfile} out.root
   else
# subsequent files
      hadd out.root ${rfile} tmp.root
   fi
   mv out.root tmp.root

done

mv tmp.root ${ofile}

exit
