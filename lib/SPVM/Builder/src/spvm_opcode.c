#include "spvm_opcode.h"
#include "spvm_compiler.h"
#include "spvm_allocator.h"





























































































const char* const* SPVM_OPCODE_C_ID_NAMES(void) {

  static const char* const id_names[] = {
    "end_method",
    "add_int",
    "add_long",
    "add_float",
    "add_double",
    "subtract_int",
    "subtract_long",
    "subtract_float",
    "subtract_double",
    "multiply_int",
    "multiply_long",
    "multiply_float",
    "multiply_double",
    "divide_int",
    "divide_long",
    "divide_float",
    "divide_double",
    "divide_unsigned_int",
    "divide_unsigned_long",
    "remainder_int",
    "remainder_long",
    "remainder_unsigned_int",
    "remainder_unsigned_long",
    "left_shift_int",
    "left_shift_long",
    "right_arithmetic_shift_int",
    "right_arithmetic_shift_long",
    "right_logical_shift_int",
    "right_logical_shift_long",
    "bit_and_int",
    "bit_and_long",
    "bit_or_int",
    "bit_or_long",
    "bit_xor_int",
    "bit_xor_long",
    "bit_omplement_int",
    "bit_not_long",
    "negate_int",
    "negate_long",
    "negate_float",
    "negate_double",
    "init_byte",
    "init_short",
    "init_int",
    "init_long",
    "init_float",
    "init_double",
    "init_undef",
    "init_mulnum_byte",
    "init_mulnum_short",
    "init_mulnum_int",
    "init_mulnum_long",
    "init_mulnum_float",
    "init_mulnum_double",
    "move_constant_byte",
    "move_constant_int",
    "move_constant_long",
    "move_constant_float",
    "move_constant_double",
    "move_byte",
    "move_short",
    "move_int",
    "move_long",
    "move_float",
    "move_double",
    "move_object",
    "move_object_check_assign",
    "move_object_check_read_only",
    "move_undef",
    "move_ref",
    "type_conversion_byte_to_short",
    "type_conversion_byte_to_int",
    "type_conversion_byte_to_long",
    "type_conversion_byte_to_float",
    "type_conversion_byte_to_double",
    "type_conversion_short_to_byte",
    "type_conversion_short_to_int",
    "type_conversion_short_to_long",
    "type_conversion_short_to_float",
    "type_conversion_short_to_double",
    "type_conversion_int_to_byte",
    "type_conversion_int_to_short",
    "type_conversion_int_to_long",
    "type_conversion_int_to_float",
    "type_conversion_int_to_double",
    "type_conversion_long_to_byte",
    "type_conversion_long_to_short",
    "type_conversion_long_to_int",
    "type_conversion_long_to_float",
    "type_conversion_long_to_double",
    "type_conversion_float_to_byte",
    "type_conversion_float_to_short",
    "type_conversion_float_to_int",
    "type_conversion_float_to_long",
    "type_conversion_float_to_double",
    "type_conversion_double_to_byte",
    "type_conversion_double_to_short",
    "type_conversion_double_to_int",
    "type_conversion_double_to_long",
    "type_conversion_double_to_float",
    "type_conversion_byte_to_string",
    "type_conversion_short_to_string",
    "type_conversion_int_to_string",
    "type_conversion_long_to_string",
    "type_conversion_float_to_string",
    "type_conversion_double_to_string",
    "type_conversion_string_to_byte_array",
    "type_conversion_byte_array_to_string",
    "type_conversion_byte_to_byte_object",
    "type_conversion_short_to_short_object",
    "type_conversion_int_to_int_object",
    "type_conversion_long_to_long_object",
    "type_conversion_float_to_float_object",
    "type_conversion_double_to_double_object",
    "type_conversion_byte_object_to_byte",
    "type_conversion_short_object_to_short",
    "type_conversion_int_object_to_int",
    "type_conversion_long_object_to_long",
    "type_conversion_float_object_to_float",
    "type_conversion_double_object_to_double",
    "type_conversion_conditinal_int",
    "type_conversion_conditinal_long",
    "type_conversion_conditinal_float",
    "type_conversion_conditinal_double",
    "type_conversion_conditinal_object",
    "type_conversion_conditinal_bool_object",
    "concat",
    "eq_int",
    "eq_long",
    "eq_float",
    "eq_double",
    "eq_object",
    "ne_int",
    "ne_long",
    "ne_float",
    "ne_double",
    "ne_object",
    "gt_int",
    "gt_long",
    "gt_float",
    "gt_double",
    "ge_int",
    "ge_long",
    "ge_float",
    "ge_double",
    "lt_int",
    "lt_long",
    "lt_float",
    "lt_double",
    "le_int",
    "le_long",
    "le_float",
    "le_double",
    "cmp_int",
    "cmp_long",
    "cmp_float",
    "cmp_double",
    "is_undef",
    "is_not_undef",
    "string_eq",
    "string_ne",
    "string_gt",
    "string_ge",
    "string_lt",
    "string_le",
    "string_cmp",
    "goto",
    "if_eq_zero",
    "if_ne_zero",
    "if_exception_catch",
    "if_exception_return",
    "lookup_switch",
    "case_info",
    "get_array_element_byte",
    "get_array_element_short",
    "get_array_element_int",
    "get_array_element_long",
    "get_array_element_float",
    "get_array_element_double",
    "get_array_element_object",
    "set_array_element_byte",
    "set_array_element_short",
    "set_array_element_int",
    "set_array_element_long",
    "set_array_element_float",
    "set_array_element_double",
    "set_array_element_object",
    "set_array_element_object_check_type",
    "set_array_element_undef",
    "array_length",
    "new_object",
    "new_object_array",
    "new_multi_array",
    "new_mulnum_array",
    "new_byte_array",
    "new_short_array",
    "new_int_array",
    "new_long_array",
    "new_float_array",
    "new_double_array",
    "new_string",
    "new_string_len",
    "is_read_only",
    "make_read_only",
    "get_field_byte",
    "get_field_short",
    "get_field_int",
    "get_field_long",
    "get_field_float",
    "get_field_double",
    "get_field_object",
    "set_field_byte",
    "set_field_short",
    "set_field_int",
    "set_field_long",
    "set_field_float",
    "set_field_double",
    "set_field_object",
    "set_field_undef",
    "isa",
    "has_impl",
    "enter_scope",
    "push_mortal",
    "leave_scope",
    "push_arg_byte",
    "push_arg_short",
    "push_arg_int",
    "push_arg_long",
    "push_arg_float",
    "push_arg_double",
    "push_arg_object",
    "push_arg_ref",
    "push_arg_undef",
    "push_arg_mulnum_byte",
    "push_arg_mulnum_short",
    "push_arg_mulnum_int",
    "push_arg_mulnum_long",
    "push_arg_mulnum_float",
    "push_arg_mulnum_double",
    "call_class_method_by_id",
    "call_instance_method_by_id",
    "call_instance_method_by_name",
    "get_arg_byte",
    "get_arg_short",
    "get_arg_int",
    "get_arg_long",
    "get_arg_float",
    "get_arg_double",
    "get_arg_object",
    "get_arg_ref",
    "get_arg_mulnum_byte",
    "get_arg_mulnum_short",
    "get_arg_mulnum_int",
    "get_arg_mulnum_long",
    "get_arg_mulnum_float",
    "get_arg_mulnum_double",
    "get_arg_optional_byte",
    "get_arg_optional_short",
    "get_arg_optional_int",
    "get_arg_optional_long",
    "get_arg_optional_float",
    "get_arg_optional_double",
    "get_arg_optional_object",
    "return_void",
    "return_byte",
    "return_short",
    "return_int",
    "return_long",
    "return_float",
    "return_double",
    "return_object",
    "return_undef",
    "return_mulnum_byte",
    "return_mulnum_short",
    "return_mulnum_int",
    "return_mulnum_long",
    "return_mulnum_float",
    "return_mulnum_double",
    "set_croak_flag_true",
    "die",
    "warn",
    "print",
    "ref",
    "ref_byte",
    "ref_short",
    "ref_int",
    "ref_long",
    "ref_float",
    "ref_double",
    "get_deref_byte",
    "get_deref_short",
    "get_deref_int",
    "get_deref_long",
    "get_deref_float",
    "get_deref_double",
    "set_deref_byte",
    "set_deref_short",
    "set_deref_int",
    "set_deref_long",
    "set_deref_float",
    "set_deref_double",
    "get_class_var_byte",
    "get_class_var_short",
    "get_class_var_int",
    "get_class_var_long",
    "get_class_var_float",
    "get_class_var_double",
    "get_class_var_object",
    "set_class_var_byte",
    "set_class_var_short",
    "set_class_var_int",
    "set_class_var_long",
    "set_class_var_float",
    "set_class_var_double",
    "set_class_var_object",
    "set_class_var_undef",
    "get_exception_var",
    "set_exception_var",
    "set_exception_undef",
    "weaken_field",
    "unweaken_field",
    "isweak_field",
    "refcnt",
    "refop",
    "dump",
    "copy",
    "get_mulnum_field_byte",
    "get_mulnum_field_short",
    "get_mulnum_field_int",
    "get_mulnum_field_long",
    "get_mulnum_field_float",
    "get_mulnum_field_double",
    "set_mulnum_field_byte",
    "set_mulnum_field_short",
    "set_mulnum_field_int",
    "set_mulnum_field_long",
    "set_mulnum_field_float",
    "set_mulnum_field_double",
    "move_mulnum_byte",
    "move_mulnum_short",
    "move_mulnum_int",
    "move_mulnum_long",
    "move_mulnum_float",
    "move_mulnum_double",
    "get_mulnum_array_byte",
    "get_mulnum_array_short",
    "get_mulnum_array_int",
    "get_mulnum_array_long",
    "get_mulnum_array_float",
    "get_mulnum_array_double",
    "set_mulnum_array_byte",
    "set_mulnum_array_short",
    "set_mulnum_array_int",
    "set_mulnum_array_long",
    "set_mulnum_array_float",
    "set_mulnum_array_double",
    "get_mulnum_array_field_byte",
    "get_mulnum_array_field_short",
    "get_mulnum_array_field_int",
    "get_mulnum_array_field_long",
    "get_mulnum_array_field_float",
    "get_mulnum_array_field_double",
    "set_mulnum_array_field_byte",
    "set_mulnum_array_field_short",
    "set_mulnum_array_field_int",
    "set_mulnum_array_field_long",
    "set_mulnum_array_field_float",
    "set_mulnum_array_field_double",
    "deref_mulnum_byte",
    "deref_mulnum_short",
    "deref_mulnum_int",
    "deref_mulnum_long",
    "deref_mulnum_float",
    "deref_mulnum_double",
    "get_mulnum_field_deref_byte",
    "get_mulnum_field_deref_short",
    "get_mulnum_field_deref_int",
    "get_mulnum_field_deref_long",
    "get_mulnum_field_deref_float",
    "get_mulnum_field_deref_double",
    "set_mulnum_field_deref_byte",
    "set_mulnum_field_deref_short",
    "set_mulnum_field_deref_int",
    "set_mulnum_field_deref_long",
    "set_mulnum_field_deref_float",
    "set_mulnum_field_deref_double",
    "get_class_id",
    "get_error_code",
    "set_error_code",
    "clear_eval_error",
    "get_eval_error",
  };
  
  return id_names;
}

SPVM_OPCODE* SPVM_OPCODE_new(SPVM_COMPILER* compiler) {
  SPVM_OPCODE* opcode = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_OPCODE));
  
  return opcode;
}

const char* SPVM_OPCODE_get_opcode_name(SPVM_COMPILER* compiler, int32_t opcode_id) {
  return (SPVM_OPCODE_C_ID_NAMES())[opcode_id];
}
