#!/bin/sh

date

#. ~/setenv.sh

#./gcombine.sh LLVV
#./gcombine.sh Other
#./gcombine.sh VJets
#./gcombine.sh DY_All
#./gcombine.sh Top

#./gcombine.sh All

#./gcombine.sh DY_All
./gcombine.sh Higgs
./gcombine.sh WW
./gcombine.sh WZ
./gcombine.sh ZZ
./gcombine.sh ZJets
./gcombine.sh WJets
./gcombine.sh DY_Low
./gcombine.sh DY_High
./gcombine.sh DY_Other
./gcombine.sh TT
./gcombine.sh ST
./gcombine.sh ST_all

date

exit
