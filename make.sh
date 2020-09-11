echo Building pinmon
g++ -lwiringPi -o pinmon pinmon.cpp || exit
echo Done
