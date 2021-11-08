#!/bin/bash

echo "constant sourcePath = \"./Sources/\";" > Project.td
echo "constant excludePath = \"Ex\";" >> Project.td
echo "constant docPath = \"./Doc/\";" >> Project.td
echo "constant projectName = \"project\";" >> Project.td
echo "constant infoReview = \"\";" >> Project.td
echo "constant jsonPath = \"./Html/client/json/\";" >> Project.td
echo "constant dbFile = \"cppbase.db\";" >> Project.td
echo "constant referenceDB = \"./Reference/cppbase.db\";" >> Project.td
echo "constant forceClean = true;" >> Project.td

echo "include(\"Include.td\");" >> Project.td
echo "include(\"Main.td\");" >> Project.td
echo "include(\"DBConvert.td\");" >> Project.td
echo "include(\"DbDiff.td\");" >> Project.td

if [ -e ./reference/cppbase.db ]
then
    cp ./reference/cppbase.db ./
fi

LD_LIBRARY_PATH=../ ../tdscript Project.td -module cppBase cppbase.db -v 6

