# check error scenarios  - without an output file

printf "\nCheck error scenario - without output file \n\n"
make
sh install_module.sh

printf "\n Input is ./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input1.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input1.txt
