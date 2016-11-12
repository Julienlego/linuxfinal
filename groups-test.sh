#!/bin/bash

users=(`cat /etc/passwd | awk -F: '{ print $1 }' | egrep -v "(^#.*|^$)"`)

echo "\n<=========    Call with 0 args   ============>";
echo "User: `whoami`";
./groups
echo "\n<========= Call with valid users ============>";
echo "Users: ${users[0]}, ${users[1]}, ${users[2]}"
./groups ${users[0]} ${users[1]} ${users[2]}
echo "\n<=========Call with invalid users============> ";
echo "Users: ${users[0]}, asdfzxcvqwe"
./groups ${users[0]} asdfzxcvqwe

echo "\n <=========Check if output is same===============>";
custom_gr1=`./groups ${users[0]}`
custom_gr2=`./groups ${users[1]}`
custom_gr3=`./groups ${users[2]}`
gr1=`groups ${users[0]}`
gr2=`groups ${users[1]}`
gr3=`groups ${users[2]}`

if [[ ${custom_gr1[*]} == ${gr1[*]} ]]; then
  echo "same for first user"
else
  echo "different for first user"
fi

if [[ ${custom_gr2[*]} == ${gr2[*]} ]]; then
  echo "same for second user"
else
  echo "different for second user"
fi

if [[ ${custom_gr3[*]} == ${gr3[*]} ]]; then
  echo "same for third user"
else
  echo "different for third user"
fi
