#!/bin/sh
#
#

path=/home/gwwilson/work/SUSYNANO-14_01_20/Fall17_102X
#path=/home/gwwilson/work/SUSYNANO-14_01_20/Fall17_102X_SMS

rlistfile=${path}/RootFiles.list

for rootfile in $(cat ${rlistfile})

do
   echo ' '
   name=$(echo "$rootfile" | cut -f 1 -d '.')
   echo $name
   listfile=${name}.list

   fullpathname=${path}/${rootfile}
   echo ${fullpathname}
   echo ${listfile}

# Write full path name to the root file in the list file in the datalists2 subdirectory

   echo ${fullpathname} >datalists2/${listfile}

done

exit
