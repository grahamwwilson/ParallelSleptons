#!/bin/sh
#
# Add the various ROOT files specified.
#
echo $ROOTSYS

fl=${1-ZJets}

path=/home/gwwilson/slepton/ParallelSleptons/batch_scripts/datalists2
flistfile=${path}/${fl}.flist

rpath=/home/gwwilson/slepton/ParallelSleptons/ExecutionDirectory

ofile=${fl}.root
rm ${ofile}

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
      hadd -v 0 out.root ${rfile} tmp.root
   fi

   mv out.root tmp.root

# Add some diagnostics related to event counts?
   root -l -b -q 'getbkg.C()'

done

mv tmp.root ${ofile}

exit
