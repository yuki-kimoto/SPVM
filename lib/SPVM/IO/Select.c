#include "spvm_native.h"

// Module file name
static const char* MFILE = "SPVM/IO/Select.c";

int32_t SPNATIVE__SPVM__IO__Select__can_read(SPVM_ENV* env, SPVM_VALUE* stack) {


  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Select__can_write(SPVM_ENV* env, SPVM_VALUE* stack) {


  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Select__has_exception(SPVM_ENV* env, SPVM_VALUE* stack) {


  return SPVM_SUCCESS;
}

/*
sub can_read
{
 my $vec = shift;
 my $timeout = shift;
 my $r = $vec->[VEC_BITS];
 
 defined($r) && (select($r,undef,undef,$timeout) > 0)
    ? handles($vec, $r)
    : ();
}
 
sub can_write
{
 my $vec = shift;
 my $timeout = shift;
 my $w = $vec->[VEC_BITS];
 
 defined($w) && (select(undef,$w,undef,$timeout) > 0)
    ? handles($vec, $w)
    : ();
}
 
sub has_exception
{
 my $vec = shift;
 my $timeout = shift;
 my $e = $vec->[VEC_BITS];
 
 defined($e) && (select(undef,undef,$e,$timeout) > 0)
    ? handles($vec, $e)
    : ();
}
*/
