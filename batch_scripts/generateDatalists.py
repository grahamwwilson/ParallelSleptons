
#This script looks in the workspace where all the Ntuples are stored
#it finds a list of all the directories
#a datalist for each directory is created, the list contents are all the files in the associated directory
#each datalist is inteded for 1 batch job

#path to datasets
#read Dirs.list

import sys 
import os
import subprocess

def bash( bashCommand ):
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        return output ,error

#PATH="/home/gwwilson/work/SUSYNANO/"
PATH=""
dirList = "Dirs.list"
MAXNUMFILESPERLIST = 500


#go to the each directory and LS the contents (with full path) into a file
#save the file in a directory of the same name

f = open(PATH+dirList,"r")
lines = f.readlines()


for line in lines:
	dirname = line.rstrip()
	print dirname
	listname = dirname.split("/")
	listname = listname[-1]
	print listname
	cmd = "ls "+PATH+dirname
	LS = bash(cmd)
	LS = LS[0].split('\n')
	LS = [f for f in LS if ".root" in f]

	out = open("datalists/"+listname+"_0.list", "w+")
	#count how many files we write to list, do not exceed max
	listcounter = 0
	filecounter = 1
	for rootf in LS:
		if listcounter > MAXNUMFILESPERLIST:
			out.close()
			out = open("datalists/"+listname+"_"+str(filecounter)+".list", "w+")
			filecounter = filecounter + 1
			listcounter = 0
			
        	out.write(PATH+dirname+"/"+rootf+"\n")
		listcounter = listcounter + 1
	
	out.close()
	


