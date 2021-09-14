#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>


#include "spvm_compiler.h"
#include "spvm_dumper.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_constant.h"
#include "spvm_field.h"
#include "spvm_method.h"
#include "spvm_my.h"
#include "spvm_var.h"
#include "spvm_op.h"
#include "spvm_enumeration_value.h"
#include "spvm_type.h"
#include "spvm_enumeration.h"
#include "spvm_class.h"
#include "spvm_type.h"
#include "spvm_opcode.h"
#include "spvm_class_var.h"
#include "spvm_class_var_access.h"
#include "spvm_opcode_array.h"
#include "spvm_block.h"
#include "spvm_basic_type.h"
#include "spvm_field_access.h"

void SPVM_DUMPER_dump_ast(SPVM_COMPILER* compiler, SPVM_OP* op_base) {
  int32_t indent = 8;
  
  // Run OPs
  SPVM_OP* op_cur = op_base;
  int32_t finish = 0;
  while (op_cur) {
    // [START]Preorder traversal position
    {
      int32_t i;
      for (i = 0; i < indent; i++) {
        printf(" ");
      }
    }
    int32_t id = op_cur->id;
    printf("%s", (SPVM_OP_C_ID_NAMES())[id]);
    if (op_cur->id == SPVM_OP_C_ID_CONSTANT) {
      SPVM_CONSTANT* constant = op_cur->uv.constant;
      if (constant->type->dimension == 0) {
        printf(" %s", (SPVM_BASIC_TYPE_C_ID_NAMES())[constant->type->basic_type->id]);
        switch (constant->type->basic_type->id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE:
            printf(" %" PRId8, constant->value.bval);
            break;
          case SPVM_BASIC_TYPE_C_ID_SHORT:
            printf(" %" PRId16, constant->value.sval);
            break;
          case SPVM_BASIC_TYPE_C_ID_INT:
            printf(" %" PRId32, constant->value.ival);
            break;
          case SPVM_BASIC_TYPE_C_ID_LONG:
            printf(" %" PRId64, constant->value.lval);
            break;
          case SPVM_BASIC_TYPE_C_ID_FLOAT:
            printf(" %f", constant->value.fval);
            break;
          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
            printf(" %f", constant->value.dval);
            break;
        }
      }
      else if (constant->type->dimension == 1 && constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
        printf(" string \"%s\"\n", (char*)constant->value.oval);
        break;
      }
    }
    else if (id == SPVM_OP_C_ID_CLASS_VAR) {
      SPVM_CLASS_VAR* class_var = op_cur->uv.class_var;
      printf(" \"%s\"", class_var->name);
      printf(" (id :%d)", class_var->id);
    }
    else if (id == SPVM_OP_C_ID_VAR) {
      SPVM_VAR* var = op_cur->uv.var;
      printf(" \"%s\"", var->op_name->uv.name);
      if (var->my) {
        printf(" (my->id:%d) declaration : %d", var->my->id, op_cur->uv.var->is_declaration);
      }
      else {
        printf(" (my->id:not yet resolved)");
      }
    }
    else if (id == SPVM_OP_C_ID_CLASS_VAR_ACCESS) {
      SPVM_CLASS_VAR_ACCESS* class_var_access = op_cur->uv.class_var_access;
      printf(" \"%s\"", class_var_access->op_name->uv.name);
      printf(" (id :%d)", class_var_access->class_var->id);
    }
    else if (id == SPVM_OP_C_ID_FIELD_ACCESS) {
      SPVM_FIELD_ACCESS* field_access = op_cur->uv.field_access;
      printf(" \"%s\"", field_access->op_name->uv.name);
      printf(" (id :%d)", field_access->field->id);
    }
    else if (id == SPVM_OP_C_ID_NAME) {
      printf(" \"%s\"", op_cur->uv.name);
    }
    else if (id == SPVM_OP_C_ID_TYPE) {
      if (op_cur->uv.type) {
        printf(" ");
        printf("%s", SPVM_TYPE_new_type_name(compiler, op_cur->uv.type->basic_type->id, op_cur->uv.type->dimension, op_cur->uv.type->flag));
      }
      else {
        printf(" \"Unknown\"");
      }
    }
    else if (id == SPVM_OP_C_ID_BLOCK) {
      if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_IF) {
        printf(" IF");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_ELSE) {
        printf(" ELSE");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_INIT) {
        printf(" LOOP_INIT");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
        printf(" LOOP_STATEMENTS");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_SWITCH) {
        printf(" SWITCH");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_METHOD) {
        printf(" METHOD");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
        printf(" EVAL");
      }
    }
    printf("\n");
    
    // [END]Preorder traversal position
    
    if (op_cur->first) {
      op_cur = op_cur->first;
      indent++;
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
          indent--;
        }
      }
      if (finish) {
        break;
      }
    }
  }
}

void SPVM_DUMPER_dump_constants(SPVM_COMPILER* compiler, SPVM_LIST* op_constants) {
  {
    int32_t i;
    for (i = 0; i < op_constants->length; i++) {
      SPVM_OP* op_constant = SPVM_LIST_fetch(op_constants, i);
      SPVM_CONSTANT* constant = op_constant->uv.constant;
      printf("    constant[%" PRId32 "]\n", i);
      SPVM_DUMPER_dump_constant(compiler, constant);
    }
  }
}

void SPVM_DUMPER_dump_classes(SPVM_COMPILER* compiler, SPVM_LIST* classes) {
  {
    int32_t i;
    for (i = 0; i < classes->length; i++) {
      printf("class[%" PRId32 "]\n", i);
      SPVM_CLASS* class = SPVM_LIST_fetch(classes, i);
      
      if (class->op_name) {
        printf("  name => \"%s\"\n", class->op_name->uv.name);
      }
      else {
        printf("  name => \"ANON\"\n");
      }

      if (strncmp(class->name, "SPVM", 4) == 0) {
        printf("  (omit)\n");
        continue;
      }
      
      // Field information
      printf("  fields\n");
      SPVM_LIST* fields = class->fields;
      {
        int32_t j;
        for (j = 0; j < fields->length; j++) {
          SPVM_FIELD* field = SPVM_LIST_fetch(fields, j);
          printf("    field%" PRId32 "\n", j);
          SPVM_DUMPER_dump_field(compiler, field);
        }
      }
      {
        int32_t j;
        for (j = 0; j < class->methods->length; j++) {
          SPVM_METHOD* method = SPVM_LIST_fetch(class->methods, j);
          printf("  sub[%" PRId32 "]\n", j);
          SPVM_DUMPER_dump_method(compiler, method);
        }
      }
    }
  }
}

void SPVM_DUMPER_dump_classes_opcode_array(SPVM_COMPILER* compiler, SPVM_LIST* classes) {
  {
    int32_t i;
    for (i = 0; i < classes->length; i++) {
      printf("class[%" PRId32 "]\n", i);
      SPVM_CLASS* class = SPVM_LIST_fetch(classes, i);
      
      if (class->op_name) {
        printf("  name => \"%s\"\n", class->op_name->uv.name);
      }
      else {
        printf("  name => \"ANON\"\n");
      }
      
      if (strncmp(class->name, "SPVM", 4) == 0) {
        printf("  (omit)\n");
        continue;
      }
      
      {
        int32_t j;
        for (j = 0; j < class->methods->length; j++) {
          SPVM_METHOD* method = SPVM_LIST_fetch(class->methods, j);
          printf("  sub[%" PRId32 "]\n", j);
          SPVM_DUMPER_dump_method_opcode_array(compiler, method);
        }
      }
    }
  }
}

void SPVM_DUMPER_dump_basic_types(SPVM_COMPILER* compiler, SPVM_LIST* basic_types) {
  (void)compiler;
  
  {
    int32_t i;
    for (i = 0; i < basic_types->length; i++) {
      printf("basic_type[%" PRId32 "]\n", i);
      SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(basic_types, i);
      printf("    name => %s\n", basic_type->name);
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
      printf("        [%" PRId32 "] %-20s", i, (SPVM_OPCODE_C_ID_NAMES())[opcode.id]);
      printf(" %d %d %d %d\n", opcode.operand0, opcode.operand1, opcode.operand2, opcode.operand3);
    }
    
  }
}

void SPVM_DUMPER_dump_constant(SPVM_COMPILER* compiler, SPVM_CONSTANT* constant) {
  (void)compiler;
  
  if (constant->type->dimension == 0) {
    switch(constant->type->basic_type->id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE:
        printf("      int %" PRId8 "\n", constant->value.bval);
        break;
      case SPVM_BASIC_TYPE_C_ID_SHORT:
        printf("      int %" PRId16 "\n", constant->value.sval);
        break;
      case SPVM_BASIC_TYPE_C_ID_INT:
        printf("      int %" PRId32 "\n", constant->value.ival);
        break;
      case SPVM_BASIC_TYPE_C_ID_LONG:
        printf("      long %" PRId64 "\n", constant->value.lval);
        break;
      case SPVM_BASIC_TYPE_C_ID_FLOAT:
        printf("      float %f\n", constant->value.fval);
        break;
      case SPVM_BASIC_TYPE_C_ID_DOUBLE:
        printf("      double %f\n", constant->value.dval);
        break;
    }
  }
  else if (constant->type->dimension == 1) {
    if (constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
      printf("      String \"%s\"\n", (char*)constant->value.oval);
    }
  }
}

void SPVM_DUMPER_dump_method(SPVM_COMPILER* compiler, SPVM_METHOD* method) {
  (void)compiler;
  
  if (method) {
    
    printf("      name => \"%s\"\n", method->op_name->uv.name);
    printf("      return_type => ");
    printf("%s", SPVM_TYPE_new_type_name(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag));
    printf("\n");
    printf("      is_enum => %d\n", (method->flag & SPVM_METHOD_C_FLAG_ENUM) ? 1 : 0);
    printf("      have_native_desc => %d\n", (method->flag & SPVM_METHOD_C_FLAG_NATIVE) ? 1 : 0);
    printf("      var_alloc_length => %d\n", SPVM_METHOD_get_var_alloc_length(compiler, method));
    printf("      arg_alloc_length => %d\n", SPVM_METHOD_get_var_alloc_length(compiler, method));
    
    printf("      args\n");
    SPVM_LIST* args = method->args;
    {
      int32_t i;
      for (i = 0; i < args->length; i++) {
        SPVM_MY* my = SPVM_LIST_fetch(method->args, i);
        printf("        [%" PRId32 "] ", i);
        SPVM_DUMPER_dump_my(compiler, my);
      }
    }
    
    if (!(method->flag & SPVM_METHOD_C_FLAG_NATIVE)) {
      printf("      mys\n");
      SPVM_LIST* mys = method->mys;
      {
        int32_t i;
        for (i = 0; i < mys->length; i++) {
          SPVM_MY* my = SPVM_LIST_fetch(method->mys, i);
          printf("        mys[%" PRId32 "] ", i);
          SPVM_DUMPER_dump_my(compiler, my);
        }
      }
      
      printf("      call_method_arg_stack_max => %" PRId32 "\n", method->call_method_arg_stack_max);
      
      printf("      AST\n");
      SPVM_DUMPER_dump_ast(compiler, method->op_block);
      printf("\n");
    }
  }
  else {
    printf("      None\n");
  }
}

void SPVM_DUMPER_dump_method_opcode_array(SPVM_COMPILER* compiler, SPVM_METHOD* method) {
  (void)compiler;
  
  if (method) {
    
    printf("      name => \"%s\"\n", method->op_name->uv.name);
    printf("      var_alloc_length => %d\n", SPVM_METHOD_get_var_alloc_length(compiler, method));
    printf("      arg_alloc_length => %d\n", SPVM_METHOD_get_var_alloc_length(compiler, method));
    
    if (!(method->flag & SPVM_METHOD_C_FLAG_NATIVE)) {
      printf("      mys\n");
      SPVM_LIST* mys = method->mys;
      {
        int32_t i;
        for (i = 0; i < mys->length; i++) {
          SPVM_MY* my = SPVM_LIST_fetch(method->mys, i);
          printf("        mys[%" PRId32 "] ", i);
          SPVM_DUMPER_dump_my(compiler, my);
        }
      }
      
      printf("      opcode_array\n");
      SPVM_DUMPER_dump_opcode_array(compiler, compiler->opcode_array, method->opcodes_base, method->opcodes_length);
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
    
    SPVM_TYPE* type = field->type;
    printf("      type => ");
    printf("%s", SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag));
    printf("\n");
    printf("      offset => \"%" PRId32 "\"\n", field->offset);
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
    printf("      value => %" PRId32 "\n", enumeration_value->op_constant->uv.constant->value.ival);
  }
  else {
    printf("      None\n");
  }
}

void SPVM_DUMPER_dump_my(SPVM_COMPILER* compiler, SPVM_MY* my) {
  (void)compiler;

  if (my) {
    printf("\n");
    printf("          name => %s\n", my->op_name->uv.name);
    printf("          type => ");
    SPVM_TYPE* type = my->type;
    printf("%s", SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag));
    printf("\n");
    printf("          id => %d\n", my->id);
    printf("          mem_id => ");
    
    if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      SPVM_TYPE* numeric_type = SPVM_OP_get_type(compiler, my->op_my);
      switch(numeric_type->basic_type->id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          printf("byte");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          printf("short");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          printf("int");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          printf("long");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          printf("float");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          printf("double");
          break;
        }
      }
    }
    else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      printf("object");
    }
    else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      printf("ref");
    }
    else if (SPVM_TYPE_is_multi_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      SPVM_CLASS* value_class =  type->basic_type->class;
      
      SPVM_FIELD* first_field = SPVM_LIST_fetch(value_class->fields, 0);
      assert(first_field);
      
      SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
      assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
      
      switch (field_type->basic_type->id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          printf("byte");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          printf("short");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          printf("int");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          printf("long");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          printf("float");
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          printf("double");
          break;
        }
        default:
          assert(0);
      }
    }
    
    printf(" %d\n", my->mem_id);
  }
  else {
    printf("          (Unexpected)\n");
  }
}
