#!/bin/sh
#
# Put together background jobs
#

flistfile=datalists2/Bkgd.flist

for lfile in $(cat ${flistfile})

do
   echo ' '
   name=$(echo "$lfile" | cut -f 1 -d '.')
   echo $name
#   listfile=${name}.list

   sbatch job_launch.sh ${name} KUAnalysis BKG 

done

exit
