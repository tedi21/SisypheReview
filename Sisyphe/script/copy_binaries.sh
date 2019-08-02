#!/bin/bash

files=(
../../CodeGeneration/bin_qt/Encoding64/libEncoding.so.1
../../CodeGeneration/bin_qt/Xerces64/libXercesEncoding.so.1
../../../../Libraries/boost_1_66_0/stage/lib64/libboost_filesystem.so.1.66.0
../../../../Libraries/boost_1_66_0/stage/lib64/libboost_system.so.1.66.0
../../../../Libraries/boost_1_66_0/stage/lib64/libboost_regex.so.1.66.0
../../../../Libraries/boost_1_66_0/stage/lib64/libboost_date_time.so.1.66.0
../../../../Libraries/log4cpp/lib64/liblog4cpp.so.5
../../../../Libraries/xerces-c-3.2.1/lib64/libxerces-c-3.2.so
../../../../Libraries/xalan-c-1.11/c/lib64/libxalan-c.so.111
../../../../Libraries/xalan-c-1.11/c/lib64/libxalanMsg.so.111
../cppbase/bin64/libcppbase.so.1
../libword/bin64/liblibword.so.1
../interpreter/bin/cppBasePlg64/libcppBasePlg.so.1
../interpreter/bin/libDiffPlg64/libLibDiffPlg.so.1
../interpreter/bin/libWordPlg64/libLibwordPlg.so.1
../interpreter/bin/libWebPlg64/libLibWebPlg.so.1
../interpreter/bin/libParsePlg64/libLibParsePlg.so.1
../interpreter/bin/Plugin64/libPlugin.so.1
../interpreter/bin/Script64/script
)

destination=./
rm $destination/*.so*
rm $destination/tdscript 2> /dev/null

for file in "${files[@]}"
do
    filename=$(basename $file)
    line=$filename............................................................
    line=`echo $line | cut -c 1-60`
    if cp $file $destination/$filename 2> /dev/null
    then 
        echo $line[OK]
    else
        echo $line[NOK]
        echo Not found : $file
    fi
done

mv script tdscript
