#include <string.h>

#include "spvm_extention_bind.h"
#include "spvm_sub.h"
#include "spvm_extention.h"

void SPVM_EXTENTION_BIND_bind_core_extentions(SPVM_COMPILER* compiler, SPVM_SUB* sub, const char* sub_abs_name) {
  (void)compiler;
  
  if (strcmp(sub_abs_name, "stdout::println_byte") == 0) {
    sub->native_address = SPVM_EXTENTION_std__println_byte;
  }
  else if (strcmp(sub_abs_name, "stdout::println_short") == 0) {
    sub->native_address = SPVM_EXTENTION_std__println_short;
  }
  else if (strcmp(sub_abs_name, "stdout::println_int") == 0) {
    sub->native_address = SPVM_EXTENTION_std__println_int;
  }
  else if (strcmp(sub_abs_name, "stdout::println_long") == 0) {
    sub->native_address = SPVM_EXTENTION_std__println_long;
  }
  else if (strcmp(sub_abs_name, "stdout::println_float") == 0) {
    sub->native_address = SPVM_EXTENTION_std__println_float;
  }
  else if (strcmp(sub_abs_name, "stdout::println_double") == 0) {
    sub->native_address = SPVM_EXTENTION_std__println_double;
  }
  else if (strcmp(sub_abs_name, "stdout::print_byte") == 0) {
    sub->native_address = SPVM_EXTENTION_std__print_byte;
  }
  else if (strcmp(sub_abs_name, "stdout::print_short") == 0) {
    sub->native_address = SPVM_EXTENTION_std__print_short;
  }
  else if (strcmp(sub_abs_name, "stdout::print_int") == 0) {
    sub->native_address = SPVM_EXTENTION_std__print_int;
  }
  else if (strcmp(sub_abs_name, "stdout::print_long") == 0) {
    sub->native_address = SPVM_EXTENTION_std__print_long;
  }
  else if (strcmp(sub_abs_name, "stdout::print_float") == 0) {
    sub->native_address = SPVM_EXTENTION_std__print_float;
  }
  else if (strcmp(sub_abs_name, "stdout::print_double") == 0) {
    sub->native_address = SPVM_EXTENTION_std__print_double;
  }
  else if (strcmp(sub_abs_name, "stdout::println") == 0) {
    sub->native_address = SPVM_EXTENTION_std__println;
  }
  else if (strcmp(sub_abs_name, "stdout::sum_int") == 0) {
    sub->native_address = SPVM_EXTENTION_std__sum_int;
  }
  else if (strcmp(sub_abs_name, "stdout::test1") == 0) {
    sub->native_address = SPVM_EXTENTION_std__test1;
  }
  else if (strcmp(sub_abs_name, "stdout::test2") == 0) {
    sub->native_address = SPVM_EXTENTION_std__test2;
  }
}
