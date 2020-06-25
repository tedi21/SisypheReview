#!/bin/bash
EM_PATH=/home/teddy/emsdk

#Environnement
source $EM_PATH/emsdk_env.sh

#Copie fichiers
SISYPHE=/media/teddy/66B6F47BB6F44D55/linux/sisyphe3/sisyphe/Review
cp $(SISYPHE)/Parse.td data/Parse.td
cp $(SISYPHE)/FileData.td data/FileData.td
cp $(SISYPHE)/Pattern.td data/Pattern.td
cp $(SISYPHE)/DataBase.td data/DataBase.td
cp $(SISYPHE)/Report.td data/Report.td
cp $(SISYPHE)/CodingRules/Nexter/Rules.td data/Rules.td
cp $(SISYPHE)/Test/cppbase.db data/cppbase.db

#Compilation
make