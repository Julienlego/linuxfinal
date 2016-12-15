#!/bin/bash

myCD=`./cd`
cD=`cd && pwd`

if [${myCD} == ${cD}]; then
  echo "same"
else
  echo "different"
fi
