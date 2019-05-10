#check error scenarios  - when directory is passed as parameter for input file


printf "\n check error scenarios  - when directory is passed as parameter for input file \n\n"
make
sh install_module.sh

printf "\n Input is ./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/ /usr/src/hw1-vyelleswarap/CSE-506/output1.txt"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/ /usr/src/hw1-vyelleswarap/CSE-506/output1.txt
