#ifndef SPVM_EXTENTION_H
#define SPVM_EXTENTION_H

#include "spvm_base.h"
#include "spvm_api.h"

int32_t SPVM_EXTENTION_std__sum_int(SPVM_API* api);
int32_t SPVM_EXTENTION_std__test1(SPVM_API* api);
int32_t SPVM_EXTENTION_std__test2(SPVM_API* api);

void SPVM_EXTENTION_std__println(SPVM_API* api);
void SPVM_EXTENTION_std__println_byte(SPVM_API* api);
void SPVM_EXTENTION_std__println_short(SPVM_API* api);
void SPVM_EXTENTION_std__println_int(SPVM_API* api);
void SPVM_EXTENTION_std__println_long(SPVM_API* api);
void SPVM_EXTENTION_std__println_float(SPVM_API* api);
void SPVM_EXTENTION_std__println_double(SPVM_API* api);

void SPVM_EXTENTION_std__print_byte(SPVM_API* api);
void SPVM_EXTENTION_std__print_short(SPVM_API* api);
void SPVM_EXTENTION_std__print_int(SPVM_API* api);
void SPVM_EXTENTION_std__print_long(SPVM_API* api);
void SPVM_EXTENTION_std__print_float(SPVM_API* api);
void SPVM_EXTENTION_std__print_double(SPVM_API* api);

#endif
