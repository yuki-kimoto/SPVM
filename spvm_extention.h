#ifndef SPVM_EXTENTION_H
#define SPVM_EXTENTION_H

#include "spvm_base.h"
#include "spvm_sni.h"

int32_t SPVM_EXTENTION_stdout__sum_int(SPVM_SNI* sni);
int32_t SPVM_EXTENTION_stdout__test1(SPVM_SNI* sni);
int32_t SPVM_EXTENTION_stdout__test2(SPVM_SNI* sni);

void SPVM_EXTENTION_stdout__println(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__println_byte(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__println_short(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__println_int(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__println_long(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__println_float(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__println_double(SPVM_SNI* sni);

void SPVM_EXTENTION_stdout__print_byte(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__print_short(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__print_int(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__print_long(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__print_float(SPVM_SNI* sni);
void SPVM_EXTENTION_stdout__print_double(SPVM_SNI* sni);

#endif
