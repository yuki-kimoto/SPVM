#include "spvm_native.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static const char* MFILE = "SPVM/IO/File.c";

int32_t SPNATIVE__SPVM__CORE__gets_chomp(SPVM_ENV* env, SPVM_VALUE* stack) {
  // File handle
  void* ofh = stack[0].oval;
  if (ofh == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  
  void* fh = (FILE*)env->pointer(env, ofh);

  if (fh == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  
  int32_t scope_id = env->enter_scope(env);
  
  int32_t capacity = 80;
  void* obuffer = env->new_barray(env, capacity);
  int8_t* buffer = env->belems(env, obuffer);
  
  int32_t pos = 0;
  int32_t end_is_eof = 0;
  while (1) {
    int32_t ch = fgetc(fh);
    if (ch == EOF) {
      end_is_eof = 1;
      break;
    }
    else {
      if (pos >= capacity) {
        // Extend buffer capacity
        int32_t new_capacity = capacity * 2;
        void* new_obuffer = env->new_barray(env, new_capacity);
        int8_t* new_buffer = env->belems(env, new_obuffer);
        memcpy(new_buffer, buffer, capacity);

        int32_t removed = env->remove_mortal(env, scope_id, obuffer);
        assert(removed);
        
        capacity = new_capacity;
        obuffer = new_obuffer;
        buffer = new_buffer;
      }
      
      if (ch == '\n') {
        break;
      }
      else {
        buffer[pos] = ch;
        pos++;
      }
    }
  }
  
  if (pos > 0 || !end_is_eof) {
    void* oline;
    if (pos == 0) {
      oline = env->new_barray(env, 0);
    }
    else {
      oline = env->new_barray(env, pos);
      int8_t* line = env->belems(env, oline);
      memcpy(line, buffer, pos);
    }
    
    stack[0].oval = oline;
  }
  else {
    stack[0].oval = NULL;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__gets(SPVM_ENV* env, SPVM_VALUE* stack) {
  // File handle
  void* ofh = stack[0].oval;
  if (ofh == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  
  void* fh = (FILE*)env->pointer(env, ofh);

  if (fh == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  
  int32_t scope_id = env->enter_scope(env);
  
  int32_t capacity = 80;
  void* obuffer = env->new_barray(env, capacity);
  int8_t* buffer = env->belems(env, obuffer);
  
  int32_t pos = 0;
  int32_t end_is_eof = 0;
  while (1) {
    int32_t ch = fgetc(fh);
    if (ch == EOF) {
      end_is_eof = 1;
      break;
    }
    else {
      if (pos >= capacity) {
        // Extend buffer capacity
        int32_t new_capacity = capacity * 2;
        void* new_obuffer = env->new_barray(env, new_capacity);
        int8_t* new_buffer = env->belems(env, new_obuffer);
        memcpy(new_buffer, buffer, capacity);
        
        int32_t removed = env->remove_mortal(env, scope_id, obuffer);
        assert(removed);
        
        capacity = new_capacity;
        obuffer = new_obuffer;
        buffer = new_buffer;
      }
      
      if (ch == '\n') {
        buffer[pos] = ch;
        pos++;
        break;
      }
      else {
        buffer[pos] = ch;
        pos++;
      }
    }
  }
  
  if (pos > 0 || !end_is_eof) {
    void* oline;
    if (pos == 0) {
      oline = env->new_barray(env, 0);
    }
    else {
      oline = env->new_barray(env, pos);
      int8_t* line = env->belems(env, oline);
      memcpy(line, buffer, pos);
    }
    
    stack[0].oval = oline;
  }
  else {
    stack[0].oval = NULL;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__seek(SPVM_ENV* env, SPVM_VALUE* stack) {

  // File handle
  void* ofh = stack[0].oval;
  if (ofh == NULL) {
    stack[0].ival = EOF;
    return SPVM_SUCCESS;
  }
  FILE* fh = (FILE*)env->pointer(env, ofh);

  // Offset
  int64_t offset = stack[1].lval;
  
  // origin
  int32_t origin = stack[2].ival;
  
  int32_t ret = fseek(fh, offset, origin);
  
  stack[0].ival = ret;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__close(SPVM_ENV* env, SPVM_VALUE* stack) {
  // File handle
  void* ofh = stack[0].oval;
  if (ofh == NULL) {
    stack[0].ival = EOF;
    return SPVM_SUCCESS;
  }
  FILE* fh = (FILE*)env->pointer(env, ofh);
  
  if (fh) {
    int32_t ret = fclose(fh);
    
    env->set_pointer(env, ofh, NULL);
    
    stack[0].ival = ret;
  }
  else {
    stack[0].ival = EOF;
  }

  return SPVM_SUCCESS;
}


int32_t SPNATIVE__SPVM__CORE__read(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // Buffer
  void* obuffer = stack[0].oval;
  if (obuffer == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  char* buffer = (char*)env->belems(env, obuffer);
  int32_t buffer_length = env->len(env, obuffer);
  if (buffer_length == 0) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }
  
  // File handle
  void* ofh = stack[1].oval;
  if (ofh == NULL) {
    stack[0].ival = EOF;
    return SPVM_SUCCESS;
  }
  FILE* fh = (FILE*)env->pointer(env, ofh);
  
  int32_t read_length = fread(buffer, 1, buffer_length, fh);
  
  stack[0].ival = read_length;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__write(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Buffer
  void* obuffer = stack[0].oval;
  if (obuffer == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  char* buffer = (char*)env->belems(env, obuffer);
  int32_t length = env->len(env, obuffer);
  
  // File handle
  void* ofh = stack[1].oval;
  if (ofh == NULL) {
    stack[0].ival = EOF;
    return SPVM_SUCCESS;
  }
  FILE* fh = (FILE*)env->pointer(env, ofh);
  
  int32_t read_length = fwrite(buffer, 1, length, fh);
  
  stack[0].ival = read_length;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__putc(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // Char
  int32_t ch = stack[0].ival;
  
  // File handle
  void* ofh = stack[1].oval;
  if (ofh == NULL) {
    stack[0].ival = EOF;
    return SPVM_SUCCESS;
  }
  
  void* fh = (FILE*)env->pointer(env, ofh);
  
  int32_t ret = fputc(ch, ofh);
  
  stack[0].ival = ret;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__open(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // File name
  void* ofile_name = stack[0].oval;
  if (ofile_name == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  const char* file_name = (const char*)env->belems(env, ofile_name);
  
  // Mode
  void* omode = stack[1].oval;
  if (omode == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  const char* mode = (const char*)env->belems(env, omode);
  
  // Check mode
  int32_t valid_mode;
  if (strcmp(mode, "r") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "w") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "a") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "rb") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "wb") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "ab") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "r+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "w+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "a+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "r+b") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "rb+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "w+b") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "wb+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "a+b") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "ab+") == 0) {
    valid_mode = 1;
  }
  else {
    valid_mode = 0;
  }
  if (!valid_mode) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  
  FILE* fh = fopen(file_name, mode);
  
  void* obj_io_file;
  SPVM_NEW_OBJ(env, obj_io_file, "SPVM::IO::File", MFILE, __LINE__);
  
  if (fh) {
    void* obj_file_handle;
    SPVM_NEW_POINTER(env, obj_file_handle, "SPVM::FileHandle", fh, MFILE, __LINE__);
    SPVM_SET_OFIELD(env, obj_io_file, "SPVM::IO::File", "handle", "SPVM::FileHandle", obj_file_handle, MFILE, __LINE__);
    
    stack[0].oval = obj_io_file;
  }
  else {
    stack[0].oval = NULL;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_RDONLY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_RDONLY
  stack[0].ival = O_RDONLY;
#else
  SPVM_DIE("Errno O_RDONLY is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_WRONLY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_WRONLY
  stack[0].ival = O_WRONLY;
#else
  SPVM_DIE("Errno O_WRONLY is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_RDWR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_RDWR
  stack[0].ival = O_RDWR;
#else
  SPVM_DIE("Errno O_RDWR is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_APPEND(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_APPEND
  stack[0].ival = O_APPEND;
#else
  SPVM_DIE("Errno O_APPEND is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_CREAT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_CREAT
  stack[0].ival = O_CREAT;
#else
  SPVM_DIE("Errno O_CREAT is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_TRUNC(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_TRUNC
  stack[0].ival = O_TRUNC;
#else
  SPVM_DIE("Errno O_TRUNC is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__SEEK_SET(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef SEEK_SET
  stack[0].ival = SEEK_SET;
#else
  SPVM_DIE("Errno SEEK_SET is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__SEEK_CUR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef SEEK_CUR
  stack[0].ival = SEEK_CUR;
#else
  SPVM_DIE("Errno SEEK_CUR is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__SEEK_END(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef SEEK_END
  stack[0].ival = SEEK_END;
#else
  SPVM_DIE("Errno SEEK_END is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__EOF(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EOF
  stack[0].ival = EOF;
#else
  SPVM_DIE("Errno EOF is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__STDIN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef STDIN
  stack[0].ival = STDIN;
#else
  SPVM_DIE("Errno STDIN is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__STDOUT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef STDOUT
  stack[0].ival = STDOUT;
#else
  SPVM_DIE("Errno STDOUT is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}
