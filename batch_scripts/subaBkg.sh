#!/bin/sh
#
# Put together background jobs
#

VALUE=${1-Bkgd}

echo $VALUE

flistfile=datalists2/${VALUE}.flist

for lfile in $(cat ${flistfile})

do
   echo ' '
   name=$(echo "$lfile" | cut -f 1 -d '.')
   echo $name
#   listfile=${name}.list

   sbatch job_launch.sh ${name} KUAnalysis BKG 

done

exit
