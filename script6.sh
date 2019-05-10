# check error functionality - both decrypt and encrypt are specified

printf "\n check error functionality - both decrypt and encrypt are specified\n\n"

make
sh install_module.sh

printf "\n Input is ./xhw1 -p "ABCDEFG" -d -e /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/output1.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -d -e /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/output1.txt
