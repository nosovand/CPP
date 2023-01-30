Readme

How to compile:
g++ -g main.cpp doprava.cpp -o main.exe -std=c++17 -Wall -Wpedantic

How to test:
.\main.exe --schedule "Petrackovo namesti" "Vitkov" "U Bufetu"  > out1.txt
.\main.exe --line-routing  > out2.txt
.\main.exe --driver-delays  > out3.txt
.\main.exe --driver-duty  > out4.txt
.\main.exe --line-stats  > out5.txt


