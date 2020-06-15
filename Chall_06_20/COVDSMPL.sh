rm fifo0 fifo1
mkfifo fifo0 fifo1
g++ COVDSMPLgen.cpp -o gen.out
g++ COVDSMPL.cpp
./gen.out > fifo0 < fifo1 &
./a.out < fifo0 > fifo1