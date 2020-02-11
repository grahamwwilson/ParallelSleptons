#!/bin/sh
#
# Put together signal jobs
#

VALUE=${1-Sleptons}

echo $VALUE

flistfile=datalists2/${VALUE}.flist

for lfile in $(cat ${flistfile})

do
#   echo ' '
   name=$(echo "$lfile" | cut -f 1 -d '.')
   echo $name
#   listfile=${name}.list

   sbatch job_launch.sh ${name} SMS SS

done

exit
