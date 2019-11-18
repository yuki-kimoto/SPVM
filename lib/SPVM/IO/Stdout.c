#include "spvm_native.h"
#include <stdio.h>

// import _setmode and _O_BINARY
#ifdef _WIN32
#include <io.h>
#endif

static const char* MFILE = "SPVM/IO/Stdout.c";

int32_t SPNATIVE__SPVM__IO__Stdout__new(SPVM_ENV* env, SPVM_VALUE* stack) {

  FILE* fh = stdout;
  
  void* obj_io_file;
  SPVM_NEW_OBJECT(env, obj_io_file, "SPVM::IO::File", MFILE, __LINE__);

  void* obj_io_stdout;
  SPVM_NEW_OBJECT(env, obj_io_stdout, "SPVM::IO::Stdout", MFILE, __LINE__);

  void* obj_fh;
  SPVM_NEW_POINTER(env, obj_fh, "SPVM::IO::FileHandle", fh, MFILE, __LINE__);
  SPVM_SET_FIELD_OBJECT(env, obj_io_file, "SPVM::IO::File", "fh", "SPVM::IO::FileHandle", obj_fh, MFILE, __LINE__);
  
  SPVM_SET_FIELD_OBJECT(env, obj_io_stdout, "SPVM::IO::Stdout", "fh", "SPVM::IO::File", obj_io_file, MFILE, __LINE__);
  
  stack[0].oval = obj_io_stdout;
  
  return SPVM_SUCCESS;
}

