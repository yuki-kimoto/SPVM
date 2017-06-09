#ifndef SPVM_EXTENTION_H
#define SPVM_EXTENTION_H

#include "spvm_base.h"

void SPVM_EXTENTION_std__sum_int(SPVM* spvm, SPVM_RUNTIME* runtime);

void SPVM_EXTENTION_std__println(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_byte(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_short(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_int(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_long(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_float(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_double(SPVM* spvm, SPVM_RUNTIME* runtime);

void SPVM_EXTENTION_std__print_byte(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_short(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_int(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_long(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_float(SPVM* spvm, SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_double(SPVM* spvm, SPVM_RUNTIME* runtime);

#endif
