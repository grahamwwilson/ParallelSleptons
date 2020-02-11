#!/bin/sh
#
# Put together background jobs
#

VALUE=${1-Bkgd}
NTHREADS=${2-16}

echo $VALUE

flistfile=datalists2/${VALUE}.flist

for lfile in $(cat ${flistfile})

do
   echo ' '
   name=$(echo "$lfile" | cut -f 1 -d '.')
   echo $name
#   listfile=${name}.list

   sbatch --cpus-per-task=${NTHREADS} job_launch.sh ${name} KUAnalysis BKG ${NTHREADS}

done

exit
