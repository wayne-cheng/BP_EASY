%module Bp
%{
#define SWIG_FILE_WITH_INIT
#include "Bp.h"
%}

%array_class(double, doubleArray);

%include "Bp.h"
