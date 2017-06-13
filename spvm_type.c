#include <stdlib.h>
#include <string.h>


#include "spvm_parser.h"
#include "spvm_type.h"
#include "spvm_type_component_name.h"
#include "spvm_type_component_array.h"
#include "spvm_array.h"
#include "spvm_type_part.h"
#include "spvm_op.h"
#include "spvm_parser_allocator.h"
#include "spvm_hash.h"
#include "spvm_resolved_type.h"
#include "spvm_yacc_util.h"
#include "spvm_package.h"
#include "spvm_limit.h"

const char* const SPVM_TYPE_C_CODE_NAMES[] = {
  "name",
  "array",
};

// Resolve type and index type
_Bool SPVM_TYPE_resolve_type(SPVM_PARSER* parser, SPVM_OP* op_type, int32_t name_length) {
  
  SPVM_HASH* op_package_symtable = parser->op_package_symtable;
  SPVM_TYPE* type = op_type->uv.type;
  
  if (type->resolved_type) {
    return 1;
  }
  else {
    SPVM_ARRAY* resolved_type_part_names = SPVM_PARSER_ALLOCATOR_alloc_array(parser, parser->allocator, 0);
    
    SPVM_ARRAY* parts = SPVM_PARSER_ALLOCATOR_alloc_array(parser, parser->allocator, 0);
    SPVM_TYPE_build_parts(parser, type, parts);
    
    for (int32_t i = 0; i < parts->length; i++) {
      SPVM_TYPE_PART* part = SPVM_ARRAY_fetch(parts, i);
      if (part->code == SPVM_TYPE_PART_C_CODE_SUB) {
        name_length += 3;
        SPVM_ARRAY_push(resolved_type_part_names, "sub");
      }
      else if (part->code == SPVM_TYPE_PART_C_CODE_BYTE) {
        name_length++;
        SPVM_ARRAY_push(resolved_type_part_names, (void*)part->uv.char_name);
      }
      else {
        const char* part_name = part->uv.op_name->uv.name;
        
        // Core type
        if (strcmp(part_name, "boolean") == 0 || strcmp(part_name, "byte") == 0 || strcmp(part_name, "short") == 0 || strcmp(part_name, "int") == 0
          || strcmp(part_name, "long") == 0 || strcmp(part_name, "float") == 0 || strcmp(part_name, "double") == 0 || strcmp(part_name, "string") == 0)
        {
          SPVM_ARRAY_push(resolved_type_part_names, (void*)part_name);
        }
        else {
          // Package
          SPVM_OP* op_found_package = SPVM_HASH_search(op_package_symtable, part_name, strlen(part_name));
          if (op_found_package) {
            SPVM_ARRAY_push(resolved_type_part_names, (void*)part_name);
          }
          else {
            SPVM_yyerror_format(parser, "unknown package \"%s\" at %s line %d\n", part_name, op_type->file, op_type->line);
            return 0;
          }
        }
        name_length += strlen(part_name);
      }
    }
    char* resolved_type_name = SPVM_PARSER_ALLOCATOR_alloc_string(parser, parser->allocator, name_length);
    
    int32_t cur_pos = 0;
    for (int32_t i = 0; i < resolved_type_part_names->length; i++) {
      const char* resolved_type_part_name = (const char*) SPVM_ARRAY_fetch(resolved_type_part_names, i);
      int32_t resolved_type_part_name_length = (int32_t)strlen(resolved_type_part_name);
      memcpy(resolved_type_name + cur_pos, resolved_type_part_name, resolved_type_part_name_length);
      cur_pos += resolved_type_part_name_length;
    }
    resolved_type_name[cur_pos] = '\0';
    
    // Create resolved type id
    SPVM_RESOLVED_TYPE* found_resolved_type = SPVM_HASH_search(parser->resolved_type_symtable, resolved_type_name, strlen(resolved_type_name));
    if (found_resolved_type) {
      type->resolved_type = found_resolved_type;
    }
    else {
      SPVM_RESOLVED_TYPE* resolved_type = SPVM_RESOLVED_TYPE_new(parser);
      resolved_type->id = parser->resolved_types->length;
      resolved_type->name = resolved_type_name;
      SPVM_ARRAY_push(parser->resolved_types, resolved_type);
      SPVM_HASH_insert(parser->resolved_type_symtable, resolved_type_name, strlen(resolved_type_name), resolved_type);
      type->resolved_type = resolved_type;
    }
  }
  
  return 1;
}

SPVM_TYPE* SPVM_TYPE_new(SPVM_PARSER* parser) {
  SPVM_TYPE* type = SPVM_PARSER_ALLOCATOR_alloc_memory_pool(parser, parser->allocator, sizeof(SPVM_TYPE));
  
  return type;
}

void SPVM_TYPE_build_parts(SPVM_PARSER* parser, SPVM_TYPE* type, SPVM_ARRAY* parts) {
  
  if (type->code == SPVM_TYPE_C_CODE_NAME) {
    SPVM_TYPE_PART* part = SPVM_TYPE_PART_new(parser);
    part->code = SPVM_TYPE_PART_C_CODE_NAME;
    part->uv.op_name = type->uv.type_component_name->op_name;
    SPVM_ARRAY_push(parts, part);
  }
  else if (type->code == SPVM_TYPE_C_CODE_ARRAY) {
    SPVM_TYPE_COMPONENT_ARRAY* type_component_array = type->uv.type_component_array;
    
    SPVM_TYPE_build_parts(parser, type_component_array->type, parts);
    
    SPVM_TYPE_PART* type_part_openbracket = SPVM_TYPE_PART_new(parser);
    type_part_openbracket->code = SPVM_TYPE_PART_C_CODE_BYTE;
    type_part_openbracket->uv.char_name = "[";
    SPVM_ARRAY_push(parts, type_part_openbracket);
    
    SPVM_TYPE_PART* type_part_closebracket = SPVM_TYPE_PART_new(parser);
    type_part_closebracket->code = SPVM_TYPE_PART_C_CODE_BYTE;
    type_part_closebracket->uv.char_name = "]";
    SPVM_ARRAY_push(parts, type_part_closebracket);
  }
}

