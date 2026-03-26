#include <stdint.h>

#include "mylib1_source1.h"
#include "mylib2_source1.h"

const char* mylib2_source1_func1 () {
  
  return mylib1_source1_func1();
}

const char* mylib2_source1_func2 () {
  
  return "Mylib2__mylib2_source1_func2";
}
