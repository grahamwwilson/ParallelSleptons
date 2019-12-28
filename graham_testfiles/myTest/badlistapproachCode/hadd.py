import sys 
import os
import subprocess

def bash( bashCommand ):
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
        #process = subprocess.Popen(bashCommand.split())
        output, error = process.communicate()
        return output ,error
#PathToBkgProcessingDir='/home/t3-ku/crogan/NTUPLES/Processing/All_Bkg_2017/'
#PathToSigProcessingDir='/home/t3-ku/crogan/NTUPLES/Processing/All_Sig/'


#PathToLocalSigSkims='/home/t3-ku/janguian/NTUPLES/LocalSkims/Sig_2017/'
#PathToLocalBkgSkims='/home/t3-ku/janguian/NTUPLES/LocalSkims/Bkg_2017/'

#PathToInput= '/home/t3-ku/janguian/storeUser/jsingera/DPG/PC/Run2018/SingleMuon/crab_SingleMu_Run2018D_AOD/190611_214910/0000/'
#PathToOutput= '/home/t3-ku/janguian/dpg/files/'
#OutputName='PC_SingleMu_Run2018D_AOD.root'

PathToInput= '/panfs/pfs.local/work/wilson/gwwilson/SUSYNANO/SMS-TSlepSlep_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_102X/'
PathToOutput = '/home/j342a201/work/SMS-TSlepSlep_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_102X/'
OutputName='SMS-TSlepSlep_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_102X'


cmd = "ls "+PathToInput
LS = bash(cmd)
LS = LS[0].split('\n')
LS = [f for f in LS if ".root" in f]
cmd = "hadd "+PathToOutput+OutputName
for f in LS:
        cmd = cmd + " "+PathToInput+f.rstrip()

print cmd
os.system(cmd)

