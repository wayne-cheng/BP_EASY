
## C++模块for Python封装方法
1. 定义要封装的接口
swig -c++ -python Bp.i
2. 编译
g++ -c -fPIC -D MS_WIN64 --std=c++11 Bp.cpp Bp_wrap.cxx -I 'D:/Program Files/Python37/include'
3. 链接为动态库
g++ -shared Bp.o Bp_wrap.o -L 'D:/Program Files/Python37/libs' -lPython37 -o _Bp.pyd
