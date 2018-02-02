all:
	swig -c++ -python Bp.i
	g++ -c -fPIC -D MS_WIN64 --std=c++11 Bp.cpp Bp_wrap.cxx -I 'D:\ProgramData\Anaconda3\include'
	g++ -shared Bp.o Bp_wrap.o -L 'D:\ProgramData\Anaconda3\libs' -lPython36 -o _Bp.pyd