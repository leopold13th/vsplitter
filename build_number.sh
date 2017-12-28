#!/bin/bash

number=`cat ../vsplitter/build_number`
let "number += 1"
echo "$number" | tee ../vsplitter/build_number
echo "#define BUILD ""$number" | tee ../vsplitter/build_number.h

