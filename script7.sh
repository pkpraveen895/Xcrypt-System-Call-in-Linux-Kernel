# check base functionality - if invalid input file is passed

printf "\nCheck base functionality - if invalid input file is passed \n\n"
make
sh install_module.sh

printf "\nInput is ./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input10.txt /usr/src/hw1-vyelleswarap/CSE-506/output1.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input10.txt /usr/src/hw1-vyelleswarap/CSE-506/output1.txt
