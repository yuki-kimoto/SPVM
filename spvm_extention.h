#ifndef SPVM_EXTENTION_H
#define SPVM_EXTENTION_H

#include "spvm_base.h"

void SPVM_EXTENTION_std__sum_int(SPVM_* spvm, SPVM_RUNTIME* runtime);

void SPVM_EXTENTION_std__println(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_byte(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_short(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_int(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_long(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_float(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_double(SPVM_* spvm, SPVM_RUNTIME* runtime);

void SPVM_EXTENTION_std__print_byte(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_short(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_int(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_long(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_float(SPVM_* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_double(SPVM_* spvm, SPVM_RUNTIME* runtime);

#endif
