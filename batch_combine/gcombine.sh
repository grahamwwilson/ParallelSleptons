#!/bin/sh
#
# Add the various ROOT files specified.
# Also need to track errors.   TODO
#
echo $ROOTSYS
echo $USER

fl=${1-ZJets}
echo ' '
echo 'fl  = ' ${fl}
echo ' '

path=/home/${USER}/slepton/ParallelSleptons/batch_scripts/datalists2
flistfile=${path}/${fl}.flist

rpath=/home/${USER}/slepton/ParallelSleptons/ExecutionDirectory

ofile=${fl}.root
rm ${ofile}

for lfile in $(cat ${flistfile})

do
   name=$(echo "$lfile" | cut -f 1 -d '.')
#   echo $name
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

   cp ${rfile} specific.root

# Add some diagnostics related to event counts for this sample
   root -l -b -q 'getbkg2.C()'
   echo ${name}

done

# Diagnostics related to event counts for all subsamples
root -l -b -q 'getbkg.C()'

mv tmp.root ${ofile}

rm specific.root

echo '==================================='${fl}

exit
