swig -c++ -python Bp.i

g++ -c -fPIC -D MS_WIN64 --std=c++11 Bp.cpp Bp_wrap.cxx -I D:/Python27/include

g++ -shared Bp.o Bp_wrap.o -LD:/Python27/libs -lPython27 -o _Bp.pyd
