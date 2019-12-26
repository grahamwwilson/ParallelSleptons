

#input is: num files, numthreads,  yourdata.list, Treename, DataTag (A unique identifier for a specific dataset), outputfile name, outputfile option
#0 is all files, optimal threads is 8 at t3.unl
python runmacro.py 0 8 "datalists/DYJetsToLL_HT.list" "KUAnalysis" "DY" "susyHists.root" "RECREATE"
python runmacro.py 0 8 "datalists/WJetsToLNu_HT.list" "KUAnalysis" "WJET" "susyHists.root" "UPDATE"
python runmacro.py 0 8 "datalists/QCD_HT.list" "KUAnalysis" "QCD" "susyHists.root" "UPDATE"
python runmacro.py 0 8 "datalists/TTJets_HT.list" "KUAnalysis" "TTJ" "susyHists.root" "UPDATE"
python runmacro.py 0 8 "datalists/ZJetsToNuNu_HT.list" "KUAnalysis" "ZNUNU" "susyHists.root" "UPDATE"
python runmacro.py 0 8 "datalists/SMS_TChiWZ_ZToLL.list" "SMS_300_75" "WZ_300_75" "susyHists.root" "UPDATE"
python runmacro.py 0 8 "datalists/SMS_TChiWZ_ZToLL.list" "SMS_175_135" "WZ_175_135" "susyHists.root" "UPDATE"

