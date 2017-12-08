#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>


#include "spvm_compiler.h"
#include "spvm_dumper.h"
#include "spvm_dynamic_array.h"
#include "spvm_hash.h"
#include "spvm_constant.h"
#include "spvm_field.h"
#include "spvm_sub.h"
#include "spvm_my.h"
#include "spvm_var.h"
#include "spvm_op.h"
#include "spvm_enumeration_value.h"
#include "spvm_type.h"
#include "spvm_enumeration.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_constant_pool.h"
#include "spvm_bytecode.h"
#include "spvm_our.h"
#include "spvm_package_var.h"
#include "spvm_bytecode.h"
#include "spvm_opcode_array.h"

void SPVM_DUMPER_dump_ast(SPVM_COMPILER* compiler, SPVM_OP* op_base) {
  int32_t depth = 0;
  
  // Run OPs
  SPVM_OP* op_cur = op_base;
  _Bool finish = 0;
  while (op_cur) {
    // [START]Preorder traversal position
    
    {
      int32_t i;
      for (i = 0; i < depth; i++) {
        printf(" ");
      }
    }
    int32_t code = op_cur->code;
    printf("%s", SPVM_OP_C_CODE_NAMES[code]);
    if (op_cur->code == SPVM_OP_C_CODE_CONSTANT) {
      SPVM_CONSTANT* constant = op_cur->uv.constant;
      printf(" %s", SPVM_TYPE_C_CODE_NAMES[constant->type->code]);
      switch (constant->type->code) {
        case SPVM_TYPE_C_CODE_BYTE:
          printf(" %" PRId8, constant->value.byte_value);
          break;
        case SPVM_TYPE_C_CODE_SHORT:
          printf(" %" PRId16, constant->value.short_value);
          break;
        case SPVM_TYPE_C_CODE_INT:
          printf(" %" PRId32, constant->value.int_value);
          break;
        case SPVM_TYPE_C_CODE_LONG:
          printf(" %" PRId64, constant->value.long_value);
          break;
        case SPVM_TYPE_C_CODE_FLOAT:
          printf(" %f", constant->value.float_value);
          break;
        case SPVM_TYPE_C_CODE_DOUBLE:
          printf(" %f", constant->value.double_value);
          break;
        case SPVM_TYPE_C_CODE_BYTE_ARRAY:
          printf(" \"%s\"", constant->value.string_value);
          break;
      }
      printf(" (index %" PRId32 ")", constant->id);
    }
    else if (code == SPVM_OP_C_CODE_MY) {
      SPVM_MY* my = op_cur->uv.my;
      printf(" \"%s\"", my->op_name->uv.name);
      printf(" (my->index:%d)", my->index);
    }
    else if (code == SPVM_OP_C_CODE_OUR) {
      SPVM_OUR* our = op_cur->uv.our;
      printf(" \"%s\"", our->op_package_var->uv.package_var->op_name->uv.name);
      printf(" (id :%d)", our->id);
    }
    else if (code == SPVM_OP_C_CODE_VAR) {
      SPVM_VAR* var = op_cur->uv.var;
      printf(" \"%s\"", var->op_name->uv.name);
      printf(" (my->index:%d)", var->op_my->uv.my->index);
    }
    else if (code == SPVM_OP_C_CODE_PACKAGE_VAR) {
      SPVM_PACKAGE_VAR* package_var = op_cur->uv.package_var;
      printf(" \"%s\"", package_var->op_name->uv.name);
      printf(" (id :%d)", package_var->op_our->uv.our->id);
    }
    else if (code == SPVM_OP_C_CODE_NAME) {
      printf(" \"%s\"", op_cur->uv.name);
    }
    else if (code == SPVM_OP_C_CODE_TYPE) {
      printf(" \"%s\"", op_cur->uv.type->name);
    }
    else if (code == SPVM_OP_C_CODE_PACKAGE) {
      if (strcmp(op_cur->uv.package->op_name->uv.name, "CORE") == 0) {
        printf(" std(omit)\n");
        op_cur = op_cur->sibparent;
        continue;
      }
    }
    printf("\n");
    
    // [END]Preorder traversal position
    
    if (op_cur->first) {
      op_cur = op_cur->first;
      depth++;
    }
    else {
      while (1) {
        // [START]Postorder traversal position
        
        // [END]Postorder traversal position
        
        if (op_cur == op_base) {
          finish = 1;
          break;
        }
        
        // Next sibling
        if (op_cur->moresib) {
          op_cur = SPVM_OP_sibling(compiler, op_cur);
          break;
        }
        // Next is parent
        else {
          op_cur = op_cur->sibparent;
          depth--;
        }
      }
      if (finish) {
        break;
      }
    }
  }
}

void SPVM_DUMPER_dump_all(SPVM_COMPILER* compiler) {
  
  printf("\n[AST]\n");
  SPVM_DUMPER_dump_ast(compiler, compiler->op_grammar);
  
  printf("\n[Types]\n");
  SPVM_DUMPER_dump_types(compiler, compiler->types);
  
  printf("\n[Constant pool]\n");
  SPVM_DUMPER_dump_constant_pool(compiler, compiler->constant_pool);
  
  printf("\n[Packages]\n");
  SPVM_DUMPER_dump_packages(compiler, compiler->op_packages);

  printf("\n[Subroutines]\n");
  SPVM_DUMPER_dump_subs(compiler, compiler->op_subs);
}

void SPVM_DUMPER_dump_constants(SPVM_COMPILER* compiler, SPVM_DYNAMIC_ARRAY* op_constants) {
  {
    int32_t i;
    for (i = 0; i < op_constants->length; i++) {
      SPVM_OP* op_constant = SPVM_DYNAMIC_ARRAY_fetch(op_constants, i);
      SPVM_CONSTANT* constant = op_constant->uv.constant;
      printf("    constant[%" PRId32 "]\n", i);
      SPVM_DUMPER_dump_constant(compiler, constant);
    }
  }
}

void SPVM_DUMPER_dump_subs(SPVM_COMPILER* compiler, SPVM_DYNAMIC_ARRAY* op_subs) {
  {
    int32_t j;
    for (j = 0; j < op_subs->length; j++) {
      SPVM_OP* op_sub = SPVM_DYNAMIC_ARRAY_fetch(op_subs, j);
      SPVM_SUB* sub = op_sub->uv.sub;
      printf("  sub[%" PRId32 "]\n", j);
      SPVM_DUMPER_dump_sub(compiler, sub);
    }
  }
}

void SPVM_DUMPER_dump_packages(SPVM_COMPILER* compiler, SPVM_DYNAMIC_ARRAY* op_packages) {
  {
    int32_t i;
    for (i = 0; i < op_packages->length; i++) {
      printf("package[%" PRId32 "]\n", i);
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, i);
      SPVM_PACKAGE* package = op_package->uv.package;
      
      printf("  name => \"%s\"\n", package->op_name->uv.name);
      
      if (package->op_type) {
        SPVM_TYPE* type = package->op_type->uv.type;
        printf("  type => \"%s\"\n", type->name);
      }
      
      printf("  byte_size => %" PRId32 "\n", package->op_fields->length);
      
      // Field information
      printf("  fields\n");
      SPVM_DYNAMIC_ARRAY* op_fields = package->op_fields;
      {
        int32_t j;
        for (j = 0; j < op_fields->length; j++) {
          SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields, j);
          SPVM_FIELD* field = op_field->uv.field;
          printf("    field%" PRId32 "\n", j);
          SPVM_DUMPER_dump_field(compiler, field);
        }
      }
    }
  }
}

void SPVM_DUMPER_dump_types(SPVM_COMPILER* compiler, SPVM_DYNAMIC_ARRAY* types) {
  (void)compiler;
  
  {
    int32_t i;
    for (i = 0; i < types->length; i++) {
      printf("type[%" PRId32 "]\n", i);
      SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(types, i);
      printf("    name => \"%s\"\n", type->name);
      printf("    id => \"%" PRId32 "\"\n", type->code);
    }
  }
}

void SPVM_DUMPER_dump_constant_pool(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool) {
  (void)compiler;
  
  {
    int32_t i;
    for (i = 0; i < constant_pool->length; i++) {
      printf("      constant_pool[%" PRId32 "] %" PRId32 "\n", i, constant_pool->values[i]);
    }
  }
}

void SPVM_DUMPER_dump_opcode_array(SPVM_COMPILER* compiler, SPVM_OPCODE_ARRAY* opcode_array, int32_t start_pos, int32_t length) {
  (void)compiler;
  
  int32_t end_pos = start_pos + length - 1;
  
  {
    int32_t i;
    for (i = start_pos; i <= end_pos; i++) {
      
      SPVM_OPCODE opcode = opcode_array->values[i];
      printf("        [%" PRId32 "] %-20s", i, SPVM_BYTECODE_C_CODE_NAMES[opcode.code]);
      
      // Operand
      switch (opcode.code) {
        case SPVM_BYTECODE_C_CODE_TABLE_SWITCH: {
          printf("\n");
          
          printf(" %d %d %d %d %d %d %d\n", opcode.operand0, opcode.operand1, opcode.operand2, opcode.operand3, opcode.operand4, opcode.operand5, opcode.operand6);
          
          int32_t max = opcode.operand2;
          
          int32_t min = opcode.operand3;
          
          // Addresses
          int32_t length = max - min + 1;
          
          int32_t offset_opcode_length;
          if (length % 8 == 0) {
            offset_opcode_length = length / 8;
          }
          else {
            offset_opcode_length = (length / 8) + 1;
          }
          
          {
            int32_t j;
            for (j = 0; j < offset_opcode_length; j++) {
              i++;
              SPVM_OPCODE opcode = opcode_array->values[i];
              printf("[%" PRId32 "] %d %d %d %d %d %d %d %d\n", i, opcode.code, opcode.operand0, opcode.operand1, opcode.operand2, opcode.operand3, opcode.operand4, opcode.operand5, opcode.operand6);
            }
          }
          
          break;
        }
        case SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH: {
          printf("\n");
          
          printf(" %d %d %d %d %d %d %d\n", opcode.operand0, opcode.operand1, opcode.operand2, opcode.operand3, opcode.operand4, opcode.operand5, opcode.operand6);
          
          int32_t count = opcode.operand2;
          
          int32_t offset_opcode_length;
          if (count % 8 == 0) {
            offset_opcode_length = (count * 2) / 8;
          }
          else {
            offset_opcode_length = ((count * 2) / 8) + 1;
          }
          
          // Match - offset
          {
            int32_t j;
            for (j = 0; j < offset_opcode_length; j++) {
              i++;
              SPVM_OPCODE opcode = opcode_array->values[i];
              printf("[%" PRId32 "] %d %d %d %d %d %d %d %d\n", i, opcode.code, opcode.operand0, opcode.operand1, opcode.operand2, opcode.operand3, opcode.operand4, opcode.operand5, opcode.operand6);
            }
          }
          
          break;
        }
        default :
        // Have seven operands
        {
          printf(" %d %d %d %d %d %d %d\n", opcode.operand0, opcode.operand1, opcode.operand2, opcode.operand3, opcode.operand4, opcode.operand5, opcode.operand6);
          break;
        }
      }
    }
  }
}

void SPVM_DUMPER_dump_constant(SPVM_COMPILER* compiler, SPVM_CONSTANT* constant) {
  (void)compiler;
  
  switch(constant->type->code) {
    case SPVM_TYPE_C_CODE_BYTE:
      printf("      int %" PRId8 "\n", constant->value.byte_value);
      break;
    case SPVM_TYPE_C_CODE_SHORT:
      printf("      int %" PRId16 "\n", constant->value.short_value);
      break;
    case SPVM_TYPE_C_CODE_INT:
      printf("      int %" PRId32 "\n", constant->value.int_value);
      break;
    case SPVM_TYPE_C_CODE_LONG:
      printf("      long %" PRId64 "\n", constant->value.long_value);
      break;
    case SPVM_TYPE_C_CODE_FLOAT:
      printf("      float %f\n", constant->value.float_value);
      break;
    case SPVM_TYPE_C_CODE_DOUBLE:
      printf("      double %f\n", constant->value.double_value);
      break;
    case SPVM_TYPE_C_CODE_BYTE_ARRAY:
      printf("      byte[] \"%s\"\n", constant->value.string_value);
      break;
  }
  printf("      address => %" PRId32 "\n", constant->id);
}

void SPVM_DUMPER_dump_sub(SPVM_COMPILER* compiler, SPVM_SUB* sub) {
  (void)compiler;
  
  if (sub) {
    
    printf("      abs_name => \"%s\"\n", sub->abs_name);
    printf("      name => \"%s\"\n", sub->op_name->uv.name);
    printf("      return_type => \"%s\"\n", sub->op_return_type->uv.type->name);
    printf("      is_constant => %d\n", sub->is_constant);
    printf("      is_native => %d\n", sub->is_native);
    
    printf("      args\n");
    SPVM_DYNAMIC_ARRAY* op_args = sub->op_args;
    {
      int32_t i;
      for (i = 0; i < op_args->length; i++) {
        SPVM_OP* op_arg = SPVM_DYNAMIC_ARRAY_fetch(sub->op_args, i);
        SPVM_MY* my = op_arg->uv.my;
        printf("        arg[%" PRId32 "]\n", i);
        SPVM_DUMPER_dump_my(compiler, my);
      }
    }
    
    if (!sub->is_native) {
      printf("      mys\n");
      SPVM_DYNAMIC_ARRAY* op_mys = sub->op_mys;
      {
        int32_t i;
        for (i = 0; i < op_mys->length; i++) {
          SPVM_OP* op_my = SPVM_DYNAMIC_ARRAY_fetch(sub->op_mys, i);
          SPVM_MY* my = op_my->uv.my;
          printf("        my[%" PRId32 "]\n", i);
          SPVM_DUMPER_dump_my(compiler, my);
        }
      }
      
      printf("      call_sub_arg_stack_max => %" PRId32 "\n", sub->call_sub_arg_stack_max);
      
      printf("      opcode_array\n");
      SPVM_DUMPER_dump_opcode_array(compiler, compiler->opcode_array, sub->opcode_base, sub->opcode_length);
    }
  }
  else {
    printf("      None\n");
  }
}

void SPVM_DUMPER_dump_field(SPVM_COMPILER* compiler, SPVM_FIELD* field) {
  (void)compiler;
  
  if (field) {
    printf("      name => \"%s\"\n", field->op_name->uv.name);
    
    printf("      index => \"%" PRId32 "\"\n", field->index);
    
    SPVM_TYPE* type = field->op_type->uv.type;
    printf("      type => \"%s\"\n", type->name);
    printf("      byte_size => \"%" PRId32 "\"\n", SPVM_FIELD_get_byte_size(compiler, field));
    
    printf("      id => \"%" PRId32 "\"\n", field->id);
  }
  else {
    printf("        None\n");
  }
}


void SPVM_DUMPER_dump_enumeration_value(SPVM_COMPILER* compiler, SPVM_ENUMERATION_VALUE* enumeration_value) {
  (void)compiler;
  
  if (enumeration_value) {
    printf("      name => \"%s\"\n", enumeration_value->op_name->uv.name);
    // TODO add types
    printf("      value => %" PRId32 "\n", enumeration_value->op_constant->uv.constant->value.int_value);
  }
  else {
    printf("      None\n");
  }
}

void SPVM_DUMPER_dump_my(SPVM_COMPILER* compiler, SPVM_MY* my) {
  (void)compiler;

  if (my) {
    printf("          name => \"%s\"\n", my->op_name->uv.name);
    
    SPVM_TYPE* type = my->op_type->uv.type;
    printf("          type => \"%s\"\n", type->name);
    
  }
  else {
    printf("          None\n");
  }
}
