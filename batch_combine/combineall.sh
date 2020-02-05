#!/bin/sh

date

. ~/setenv.sh

./gcombine.sh DY_All
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
