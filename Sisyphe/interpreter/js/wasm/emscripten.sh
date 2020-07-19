#!/bin/bash
EM_PATH=/home/teddy/emsdk

#Environnement
source $EM_PATH/emsdk_env.sh

#Copie fichiers
#SISYPHE=/media/teddy/66B6F47BB6F44D55/linux/sisyphe3/sisyphe/Review
#SISYPHE=/home/teddy/developpement/repositories/SisypheReview/Sisyphe/script/Review
SISYPHE=/media/teddy/F4708BC9708B90D2/Users/teddy/Development/Projects/Iridium/applications/Sisyphe/script/Review
cp ${SISYPHE}/Parse.td data/Parse.td
cp ${SISYPHE}/FileData.td data/FileData.td
cp ${SISYPHE}/Pattern.td data/Pattern.td
cp ${SISYPHE}/DataBase.td data/DataBase.td
cp ${SISYPHE}/Report.td data/Report.td
cp ${SISYPHE}/CodingRules/Nexter/Rules.td data/Rules.td
cp ${SISYPHE}/Test/cppbase.db data/cppbase.db

#Compilation
make
