// Copyright (c) 2023 Yuki Kimoto
// MIT License

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
#include "spvm_var_decl.h"
#include "spvm_var.h"
#include "spvm_op.h"
#include "spvm_check.h"
#include "spvm_type.h"
#include "spvm_type.h"
#include "spvm_opcode.h"
#include "spvm_class_var.h"
#include "spvm_class_var_access.h"
#include "spvm_opcode_list.h"
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
        fprintf(stderr, " ");
      }
    }
    int32_t id = op_cur->id;
    fprintf(stderr, "%s", (SPVM_OP_C_ID_NAMES())[id]);
    if (op_cur->id == SPVM_OP_C_ID_CONSTANT) {
      SPVM_CONSTANT* constant = op_cur->uv.constant;
      if (constant->type->dimension == 0) {
        fprintf(stderr, " %s", (SPVM_BASIC_TYPE_C_ID_NAMES())[constant->type->basic_type->id]);
        switch (constant->type->basic_type->id) {
          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
            fprintf(stderr, " %" PRId8, constant->value.bval);
            break;
          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
            fprintf(stderr, " %" PRId16, constant->value.sval);
            break;
          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
            fprintf(stderr, " %" PRId32, constant->value.ival);
            break;
          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
            fprintf(stderr, " %" PRId64, constant->value.lval);
            break;
          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
            fprintf(stderr, " %f", constant->value.fval);
            break;
          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
            fprintf(stderr, " %f", constant->value.dval);
            break;
        }
      }
      else if (constant->type->dimension == 1 && constant->type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
        fprintf(stderr, " string \"%s\"\n", (char*)constant->value.oval);
        break;
      }
    }
    else if (id == SPVM_OP_C_ID_CLASS_VAR) {
      SPVM_CLASS_VAR* class_var = op_cur->uv.class_var;
      fprintf(stderr, " \"%s\"", class_var->name);
      fprintf(stderr, " (index :%d)", class_var->index);
    }
    else if (id == SPVM_OP_C_ID_VAR) {
      SPVM_VAR* var = op_cur->uv.var;
      fprintf(stderr, " \"%s\"", var->name);
      if (var->var_decl) {
        fprintf(stderr, " (var_decl->index:%d) declaration : %d", var->var_decl->index, op_cur->uv.var->is_declaration);
      }
      else {
        fprintf(stderr, " (var_decl->index:not yet resolved)");
      }
    }
    else if (id == SPVM_OP_C_ID_CLASS_VAR_ACCESS) {
      SPVM_CLASS_VAR_ACCESS* class_var_access = op_cur->uv.class_var_access;
      fprintf(stderr, " \"%s\"", class_var_access->op_name->uv.name);
      fprintf(stderr, " (index :%d)", class_var_access->class_var->index);
    }
    else if (id == SPVM_OP_C_ID_FIELD_ACCESS) {
      SPVM_FIELD_ACCESS* field_access = op_cur->uv.field_access;
      if (field_access->op_name) {
        fprintf(stderr, " \"%s\"", field_access->op_name->uv.name);
      }
      if (field_access->field) {
        fprintf(stderr, " (index :%d)", field_access->field->index);
      }
    }
    else if (id == SPVM_OP_C_ID_NAME) {
      fprintf(stderr, " \"%s\"", op_cur->uv.name);
    }
    else if (id == SPVM_OP_C_ID_TYPE) {
      if (op_cur->uv.type) {
        fprintf(stderr, " ");
        fprintf(stderr, "%s", SPVM_TYPE_new_type_name(compiler, op_cur->uv.type->basic_type->id, op_cur->uv.type->dimension, op_cur->uv.type->flag));
      }
      else {
        fprintf(stderr, " \"Unknown\"");
      }
    }
    else if (id == SPVM_OP_C_ID_BLOCK) {
      if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_IF) {
        fprintf(stderr, " IF");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_ELSE) {
        fprintf(stderr, " ELSE");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_INIT) {
        fprintf(stderr, " LOOP_INIT");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
        fprintf(stderr, " LOOP_STATEMENTS");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_SWITCH) {
        fprintf(stderr, " SWITCH");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_METHOD) {
        fprintf(stderr, " METHOD");
      }
      else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
        fprintf(stderr, " EVAL");
      }
    }
    fprintf(stderr, "\n");
    
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

void SPVM_DUMPER_dump_basic_types(SPVM_COMPILER* compiler, SPVM_LIST* basic_types) {
  for (int32_t i = 0; i < basic_types->length; i++) {
    fprintf(stderr, "basic_types[%" PRId32 "]\n", i);
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(basic_types, i);
    
    fprintf(stderr, "  name => \"%s\"\n", basic_type->name);
    
    if (strncmp(basic_type->name, "SPVM", 4) == 0) {
      fprintf(stderr, "  (omit)\n");
      continue;
    }
    
    // Field information
    fprintf(stderr, "  fields\n");
    SPVM_LIST* fields = basic_type->unmerged_fields;
    {
      int32_t j;
      for (j = 0; j < fields->length; j++) {
        SPVM_FIELD* field = SPVM_LIST_get(fields, j);
        fprintf(stderr, "    fields[%" PRId32 "]\n", j);
        SPVM_DUMPER_dump_field(compiler, field);
      }
    }
    {
      int32_t j;
      for (j = 0; j < basic_type->methods->length; j++) {
        SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, j);
        fprintf(stderr, "  methods[%" PRId32 "]\n", j);
        SPVM_DUMPER_dump_method(compiler, method);
      }
    }
  }
}

void SPVM_DUMPER_dump_basic_types_opcode_list(SPVM_COMPILER* compiler, SPVM_LIST* basic_types) {
  for (int32_t i = 0; i < basic_types->length; i++) {
    fprintf(stderr, "basic_types[%" PRId32 "]\n", i);
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(basic_types, i);
    
    fprintf(stderr, "  name => \"%s\"\n", basic_type->name);
    
    if (strncmp(basic_type->name, "SPVM", 4) == 0) {
      fprintf(stderr, "  (omit)\n");
      continue;
    }
    
    {
      int32_t j;
      for (j = 0; j < basic_type->methods->length; j++) {
        SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, j);
        fprintf(stderr, "  methods[%" PRId32 "]\n", j);
        SPVM_DUMPER_dump_method_opcode_list(compiler, method);
      }
    }
  }
}

void SPVM_DUMPER_dump_opcode_list(SPVM_COMPILER* compiler, SPVM_OPCODE_LIST* opcode_list) {
  
  for (int32_t i = 0; i <= opcode_list->length; i++) {
    
    SPVM_OPCODE opcode = opcode_list->values[i];
    fprintf(stderr, "        [%" PRId32 "] %-20s", i, (SPVM_OPCODE_C_ID_NAMES())[opcode.id]);
    fprintf(stderr, " %d %d %d %d\n", opcode.operand0, opcode.operand1, opcode.operand2, opcode.operand3);
  }
}

void SPVM_DUMPER_dump_constant(SPVM_COMPILER* compiler, SPVM_CONSTANT* constant) {
  
  if (constant->type->dimension == 0) {
    switch(constant->type->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
        fprintf(stderr, "      int %" PRId8 "\n", constant->value.bval);
        break;
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
        fprintf(stderr, "      int %" PRId16 "\n", constant->value.sval);
        break;
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
        fprintf(stderr, "      int %" PRId32 "\n", constant->value.ival);
        break;
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
        fprintf(stderr, "      long %" PRId64 "\n", constant->value.lval);
        break;
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
        fprintf(stderr, "      float %f\n", constant->value.fval);
        break;
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
        fprintf(stderr, "      double %f\n", constant->value.dval);
        break;
    }
  }
  else if (constant->type->dimension == 1) {
    if (constant->type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
      fprintf(stderr, "      String \"%s\"\n", (char*)constant->value.oval);
    }
  }
}

void SPVM_DUMPER_dump_method(SPVM_COMPILER* compiler, SPVM_METHOD* method) {
  
  if (method) {
    
    const char* name = "";
    if (method->op_name) {
      name = method->op_name->uv.name;
    }
    
    fprintf(stderr, "      name => \"%s\"\n", name);
    fprintf(stderr, "      return_type => ");
    fprintf(stderr, "%s", SPVM_TYPE_new_type_name(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag));
    fprintf(stderr, "\n");
    fprintf(stderr, "      is_enum => %d\n", method->is_enum);
    fprintf(stderr, "      is_native => %d\n", method->is_native);
    fprintf(stderr, "      is_precompile => %d\n", method->is_precompile);
    if (method->op_block) {
      fprintf(stderr, "      var_decls\n");
      SPVM_LIST* var_decls = method->var_decls;
      {
        int32_t i;
        for (i = 0; i < var_decls->length; i++) {
          SPVM_VAR_DECL* var_decl = SPVM_LIST_get(method->var_decls, i);
          fprintf(stderr, "        var_decls[%" PRId32 "] ", i);
          SPVM_DUMPER_dump_var_decl(compiler, var_decl);
        }
      }
      
      fprintf(stderr, "      AST\n");
      SPVM_DUMPER_dump_ast(compiler, method->op_block);
      fprintf(stderr, "\n");
    }
  }
  else {
    fprintf(stderr, "      None\n");
  }
}

void SPVM_DUMPER_dump_method_opcode_list(SPVM_COMPILER* compiler, SPVM_METHOD* method) {
  
  if (method) {
    fprintf(stderr, "      name => \"%s\"\n", method->name);
    if (method->op_block) {
      fprintf(stderr, "      var_decls\n");
      SPVM_LIST* var_decls = method->var_decls;
      {
        int32_t i;
        for (i = 0; i < var_decls->length; i++) {
          SPVM_VAR_DECL* var_decl = SPVM_LIST_get(method->var_decls, i);
          fprintf(stderr, "        var_decls[%" PRId32 "] ", i);
          SPVM_DUMPER_dump_var_decl(compiler, var_decl);
        }
      }
      
      fprintf(stderr, "      opcode_list\n");
      SPVM_DUMPER_dump_opcode_list(compiler, method->opcode_list);
    }
  }
  else {
    fprintf(stderr, "      None\n");
  }
}

void SPVM_DUMPER_dump_field(SPVM_COMPILER* compiler, SPVM_FIELD* field) {
  
  if (field) {
    fprintf(stderr, "      name => \"%s\"\n", field->name);
    
    fprintf(stderr, "      index => \"%" PRId32 "\"\n", field->index);
    
    SPVM_TYPE* type = field->type;
    fprintf(stderr, "      type => ");
    fprintf(stderr, "%s", SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag));
    fprintf(stderr, "\n");
    fprintf(stderr, "      offset => \"%" PRId32 "\"\n", field->offset);
  }
  else {
    fprintf(stderr, "        None\n");
  }
}


void SPVM_DUMPER_dump_var_decl(SPVM_COMPILER* compiler, SPVM_VAR_DECL* var_decl) {
  
  if (var_decl) {
    fprintf(stderr, "\n");
    fprintf(stderr, "          name => %s\n", var_decl->var->name);
    fprintf(stderr, "          type => ");
    SPVM_TYPE* type = var_decl->type;
    fprintf(stderr, "%s", SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag));
    fprintf(stderr, "\n");
    fprintf(stderr, "          id => %d\n", var_decl->index);
    fprintf(stderr, "          call_stack_index => ");
    
    if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      SPVM_TYPE* numeric_type = SPVM_CHECK_get_type(compiler, var_decl->op_var_decl);
      switch(numeric_type->basic_type->id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          fprintf(stderr, "byte");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          fprintf(stderr, "short");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          fprintf(stderr, "int");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          fprintf(stderr, "long");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          fprintf(stderr, "float");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          fprintf(stderr, "double");
          break;
        }
      }
    }
    else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      fprintf(stderr, "object");
    }
    else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      fprintf(stderr, "ref");
    }
    else if (SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      SPVM_FIELD* first_field = SPVM_LIST_get(type->basic_type->unmerged_fields, 0);
      assert(first_field);
      
      SPVM_TYPE* field_type = first_field->type;
      assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
      
      switch (field_type->basic_type->id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          fprintf(stderr, "byte");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          fprintf(stderr, "short");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          fprintf(stderr, "int");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          fprintf(stderr, "long");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          fprintf(stderr, "float");
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          fprintf(stderr, "double");
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    
    fprintf(stderr, " %d\n", var_decl->typed_var_index);
  }
  else {
    fprintf(stderr, "          (Unexpected)\n");
  }
}
