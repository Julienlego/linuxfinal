#!/bin/bash

users=(`cat /etc/passwd | awk -F: '{ print $1 }' | egrep -v "(^#.*|^$)"`)

echo "\n<=========    Call with 0 args   ============>";
echo "User: `whoami`";
./groups
echo "\n<========= Call with valid users ============>";
echo "Users: ${users[0]} ${users[1]} ${users[2]}"
./groups ${users[0]} ${users[1]} ${users[2]}
echo "\n<=========Call with invalid users============> ";
echo "Users: ${users[0]} asdfzxcvqwe"
./groups ${users[0]} asdfzxcvqwe

echo "\n <=========Built in groups call===============>";
custom_gr1=`./groups ${users[0]}`
custom_gr2=`./groups ${users[1]}`
custom_gr3=`./groups ${users[2]}`
gr1=`groups ${users[0]}`
gr2=`groups ${users[1]}`
gr3=`groups ${users[2]}`

if [ gr1 == custom_gr1 ]; then
  echo "Same group"
fi
echo $custom_gr1;
echo $custom_gr2;
echo $custom_gr3;

echo $gr1;
echo $gr2;
echo $gr3;
