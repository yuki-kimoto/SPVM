#ifndef SPVM_EXTENTION_H
#define SPVM_EXTENTION_H

#include "spvm_base.h"

void SPVM_EXTENTION_std__sum_int(SPVM_RUNTIME* runtime);

void SPVM_EXTENTION_std__println(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_byte(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_short(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_int(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_long(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_float(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__println_double(SPVM_RUNTIME* runtime);

void SPVM_EXTENTION_std__print_byte(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_short(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_int(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_long(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_float(SPVM_RUNTIME* runtime);
void SPVM_EXTENTION_std__print_double(SPVM_RUNTIME* runtime);

#endif
