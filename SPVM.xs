#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <stdint.h>
#include "spvm_parser.h"
#include "spvm_hash.h"
#include "spvm_array.h"
#include "spvm_util_allocator.h"
#include "spvm_constant_pool.h"
#include "spvm_bytecode_array.h"
#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_data_api.h"

MODULE = SPVM::Compiler		PACKAGE = SPVM::Compiler

void
compile(...)
  PPCODE:
{

  XSRETURN(0);
}

void
bar(...)
  PPCODE:
{
  PerlIO_printf(PerlIO_stdout(), "bar\n");
  XSRETURN(0);
}

MODULE = SPVM		PACKAGE = SPVM
