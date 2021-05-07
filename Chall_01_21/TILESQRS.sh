mkfifo fifo0 fifo1
g++ TILESQRSgen.cpp -o gen.out
g++ TILESQRS.cpp
./gen.out > fifo0 < fifo1 &
./a.out < fifo0 > fifo1
rm fifo0 fifo1
rm gen.out