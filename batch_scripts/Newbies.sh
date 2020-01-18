#!/bin/sh
#
#

path=/home/gwwilson/work/SUSYNANO/Hadd

rlistfile=Newfiles.rlist

for rootfile in $(cat ${rlistfile})

do
   echo ' '
   name=$(echo "$rootfile" | cut -f 1 -d '.')
   echo $name
   listfile=${name}.list

   fullpathname=${path}/${rootfile}
   echo ${fullpathname}
   echo ${listfile}

# Write full path name to the root file in the list file in the datalists subdirectory

   echo ${fullpathname} >datalists/${listfile}

done

exit
