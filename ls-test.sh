#!/bin/bash

#built in LS
ls=(`ls`)
lsA=(`ls -a`)
lsL=(`ls -l`)
lsLA=(`ls -la`)

lsFile=(`ls ${lsA[0]}`)
lsAFile=(`ls -a ${lsA[0]}`)
lsLFile=(`ls -l ${lsA[0]}`)
lsLAFile=(`ls -la ${lsA[0]}`)


#custom ls
myls=(`./ls`)
mylsA=(`./ls -a`)
mylsL=(`./ls -l`)
mylsLA=(`./ls -la`)

mylsFile=(`./ls ${lsA[0]}`)
mylsAFile=(`./ls -a ${lsA[0]}`)
mylsLFile=(`./ls -l ${lsA[0]}`)
mylsLAFile=(`./ls -la ${lsA[0]}`)


if [[ ${ls[@]} == ${myls[@]} ]]; then
    echo "ls: same"
else
    echo "ls: different"
fi

if [[ ${lsA[@]} == ${mylsA[@]} ]]; then
    echo "ls -a: same"
else
    echo "ls -a: different"
fi

if [[ ${lsL[@]:2} == ${mylsL[@]} ]]; then
    echo "ls -l: same"
else
    echo "ls -l: different"
fi

if [[ ${lsLA[@]:2} == ${mylsLA[@]} ]]; then
    echo "ls -la: same"
else
    echo "ls -la: different"
fi

if [[ ${lsFile[@]} == ${mylsFile[@]} ]]; then
    echo "ls file: same"
else
    echo "ls file: different"
fi

if [[ ${lsAFile[@]} == ${mylsAFile[@]} ]]; then
    echo "ls -a file: same"
else
    echo "ls -a file: different"
fi

if [[ ${lsLFile[@]:2} == ${mylsLFile[@]} ]]; then
    echo "ls -l file: same"
else
    echo "ls -l file: different"
fi

if [[ ${lsLAFile[@]:2} == ${mylsLAFile[@]} ]]; then
    echo "ls -la file: same"
else
    echo "ls -la file: different"
fi

echo "\nTest invalid file output for equality:"
ls invalid_file_asdf
./ls invalid_file_asdf
