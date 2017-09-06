#ifndef SPVM_STD_H
#define SPVM_STD_H

#include "spvm_base.h"
#include "spvm_api.h"

int32_t SPVM__std__sum_int(SPVM_API* api, SPVM_API_VALUE* args);
int32_t SPVM__std__test1(SPVM_API* api, SPVM_API_VALUE* args);
int32_t SPVM__std__test2(SPVM_API* api, SPVM_API_VALUE* args);

void SPVM__std__println(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__println_byte(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__println_short(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__println_int(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__println_long(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__println_float(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__println_double(SPVM_API* api, SPVM_API_VALUE* args);

void SPVM__std__print_byte(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__print_short(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__print_int(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__print_long(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__print_float(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM__std__print_double(SPVM_API* api, SPVM_API_VALUE* args);

#endif
