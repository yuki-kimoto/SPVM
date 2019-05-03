#include "spvm_native.h"

#include <sys/types.h>
#include <sys/time.h>
#include <math.h>

// Module file name
static const char* MFILE = "SPVM/IO/Select.c";

int32_t SPNATIVE__SPVM__IO__Select__can_read(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // Self
  void* obj_self = stack[0].oval;
  
  // Timeout
  double timeout = stack[1].dval;
  double timeout_int;
  
  double timeout_fraction;
  timeout_fraction = modf(timeout, &timeout_int);
  struct timeval tv;
  tv.tv_sec = (int32_t)timeout_int;
  tv.tv_usec = (int32_t)(timeout_fraction * 1000000);
  
  fd_set fds;
  FD_ZERO(&fds);
  
  void* obj_handles;
  SPVM_OFIELD(env, obj_handles, obj_self, "SPVM::IO::Select", "handles", "SPVM::List", MFILE, __LINE__);
  
  {
    stack[0].oval = obj_handles;
    stack[1].ival = 0;
    SPVM_CALL_METHOD(env, "get", "object(self,int)", stack, MFILE, __LINE__);
    void* obj_handle = stack[0].oval;
  }
  
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
