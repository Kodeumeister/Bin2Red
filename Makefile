#
#	Name: Bin2Red Makefile
#	Author: William Kimberley (Kodeumeister)
#	Date Modified: 2019-12-07
#	Date Created: 2019-12-04
#

release:
	g++ -DBIGENDIAN -Wall -std=c++11 bin2red.cpp -o bin2red.exe
	strip -S bin2red.exe

debug:
	g++ -Wall --std=c++11 -DDEBUG bin2red.cpp -o bin2red.exe
