#!/bin/sh
#
# Put together signal jobs
#

flistfile=datalists2/Signals.flist

for lfile in $(cat ${flistfile})

do
#   echo ' '
   name=$(echo "$lfile" | cut -f 1 -d '.')
   echo $name
#   listfile=${name}.list

   sbatch job_launch.sh ${name} SMS SS

done

exit
