%module Bp
#可以包含swig库，后缀名.i,详情查官方文档
%include "carrays.i"
%{
#define SWIG_FILE_WITH_INIT
#include "Bp.h"
%}

%array_class(double, doubleArray);

%include "Bp.h"
