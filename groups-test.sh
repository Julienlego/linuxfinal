!#/bin/bash


users=`cat /etc/passwd | awk -F: '{print $1}'`;

echo "<=========Call with 0 args: ============> \n";
./groups
echo "<=========Call with valid users: ============> \n";
./groups mac Guest daemon
echo "<=========Call with invalid users: ============> \n";
./groups mac invaliduser1 invaliduser2
