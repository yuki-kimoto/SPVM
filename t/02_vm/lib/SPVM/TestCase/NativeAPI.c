#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include <fcntl.h>

#include <spvm_native.h>

static const char* FILE_NAME = "TestCase/NativeAPI.c";

int32_t SPVM__TestCase__NativeAPI__check_native_api_indexes(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;

  const char* func_name = __func__;
  
  void** env_array = (void**)env;
  
  if ((void*)&env->class_vars_heap != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->object_header_size != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->object_weaken_backref_head_offset != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->object_ref_count_offset != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->object_basic_type_id_offset != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->object_type_dimension_offset != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->object_flag_offset != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->object_length_offset != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api != &env_array[8]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->allocator != &env_array[9]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_env_raw != &env_array[10]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_env_raw != &env_array[11]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->isa != &env_array[12]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->elem_isa != &env_array[13]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->runtime != &env_array[14]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_basic_type_id != &env_array[15]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_id != &env_array[16]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_offset != &env_array[17]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_id != &env_array[18]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_method_id != &env_array[19]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_instance_method_id != &env_array[20]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object_raw != &env_array[21]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object != &env_array[22]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_byte_array_raw != &env_array[23]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_byte_array != &env_array[24]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_short_array_raw != &env_array[25]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_short_array != &env_array[26]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_int_array_raw != &env_array[27]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_int_array != &env_array[28]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_long_array_raw != &env_array[29]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_long_array != &env_array[30]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_float_array_raw != &env_array[31]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_float_array != &env_array[32]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_double_array_raw != &env_array[33]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_double_array != &env_array[34]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object_array_raw != &env_array[35]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object_array != &env_array[36]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_muldim_array_raw != &env_array[37]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_muldim_array != &env_array[38]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_mulnum_array_raw != &env_array[39]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_mulnum_array != &env_array[40]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string_nolen_raw != &env_array[41]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string_nolen != &env_array[42]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string_raw != &env_array[43]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string != &env_array[44]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->concat_raw != &env_array[45]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->concat != &env_array[46]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_stack_trace_raw != &env_array[47]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_stack_trace != &env_array[48]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->length != &env_array[49]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_byte != &env_array[50]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_short != &env_array[51]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_int != &env_array[52]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_long != &env_array[53]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_float != &env_array[54]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_double != &env_array[55]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elem_object != &env_array[56]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_elem_object != &env_array[57]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_byte != &env_array[58]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_short != &env_array[59]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_int != &env_array[60]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_long != &env_array[61]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_float != &env_array[62]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_double != &env_array[63]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_object != &env_array[64]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_byte != &env_array[65]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_short != &env_array[66]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_int != &env_array[67]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_long != &env_array[68]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_float != &env_array[69]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_double != &env_array[70]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_object != &env_array[71]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_byte != &env_array[72]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_short != &env_array[73]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_int != &env_array[74]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_long != &env_array[75]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_float != &env_array[76]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_double != &env_array[77]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_object != &env_array[78]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_byte != &env_array[79]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_short != &env_array[80]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_int != &env_array[81]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_long != &env_array[82]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_float != &env_array[83]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_double != &env_array[84]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_object != &env_array[85]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_pointer != &env_array[86]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_pointer != &env_array[87]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_method != &env_array[88]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_exception != &env_array[89]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_exception != &env_array[90]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_ref_count != &env_array[91]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->inc_ref_count != &env_array[92]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->dec_ref_count != &env_array[93]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->enter_scope != &env_array[94]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->push_mortal != &env_array[95]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->leave_scope != &env_array[96]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->remove_mortal != &env_array[97]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_type != &env_array[98]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_object_array != &env_array[99]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_object_basic_type_id != &env_array[100]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_object_type_dimension != &env_array[101]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->weaken != &env_array[102]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->isweak != &env_array[103]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->unweaken != &env_array[104]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->alloc_memory_block_zero != &env_array[105]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_memory_block != &env_array[106]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_memory_blocks_count != &env_array[107]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_type_name_raw != &env_array[108]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_type_name != &env_array[109]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_env != &env_array[110]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_env != &env_array[111]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->memory_blocks_count != &env_array[112]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_chars != &env_array[113]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->die != &env_array[114]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object_by_name != &env_array[115]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_byte_by_name != &env_array[116]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_short_by_name != &env_array[117]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_int_by_name != &env_array[118]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_long_by_name != &env_array[119]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_float_by_name != &env_array[120]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_double_by_name != &env_array[121]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_object_by_name != &env_array[122]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_byte_by_name != &env_array[123]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_short_by_name != &env_array[124]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_int_by_name != &env_array[125]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_long_by_name != &env_array[126]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_float_by_name != &env_array[127]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_double_by_name != &env_array[128]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_object_by_name != &env_array[129]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_byte_by_name != &env_array[130]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_short_by_name != &env_array[131]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_int_by_name != &env_array[132]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_long_by_name != &env_array[133]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_float_by_name != &env_array[134]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_double_by_name != &env_array[135]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_object_by_name != &env_array[136]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_byte_by_name != &env_array[137]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_short_by_name != &env_array[138]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_int_by_name != &env_array[139]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_long_by_name != &env_array[140]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_float_by_name != &env_array[141]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_double_by_name != &env_array[142]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_object_by_name != &env_array[143]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_class_method_by_name != &env_array[144]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_instance_method_by_name != &env_array[145]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_string_chars_by_name != &env_array[146]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_env_prepared != &env_array[147]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->dump_raw != &env_array[148]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->dump != &env_array[149]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_instance_method_id_static != &env_array[150]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_bool_object_value != &env_array[151]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->cleanup_global_vars != &env_array[152]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->make_read_only != &env_array[153]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_read_only != &env_array[154]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_array != &env_array[155]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_string != &env_array[156]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_numeric_array != &env_array[157]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_mulnum_array != &env_array[158]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elem_size != &env_array[159]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_array_proto_raw != &env_array[160]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_array_proto != &env_array[161]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->copy_raw != &env_array[162]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->copy != &env_array[163]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->shorten != &env_array[164]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->has_interface != &env_array[165]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->print != &env_array[166]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->print_stderr != &env_array[167]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->init_env != &env_array[168]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_init_blocks != &env_array[169]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_id != &env_array[170]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_stack != &env_array[171]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_stack != &env_array[172]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_memory_env != &env_array[173]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_memory_env != &env_array[174]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_memory_blocks_count_env != &env_array[175]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_memory_stack != &env_array[176]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_memory_stack != &env_array[177]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_memory_blocks_count_stack != &env_array[178]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_command_info_program_name != &env_array[179]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_command_info_argv != &env_array[180]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_id_by_name != &env_array[181]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->strerror != &env_array[182]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string_array != &env_array[183]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_args_stack_length != &env_array[184]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_args_stack_length != &env_array[185]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->dumpc != &env_array[186]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_pointer_object_raw != &env_array[187]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_pointer_object != &env_array[188]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_pointer_object_by_name != &env_array[189]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elem_string != &env_array[190]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_elem_string != &env_array[191]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_class != &env_array[192]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_pointer_class != &env_array[193]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->strerror_string != &env_array[194]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_basic_type_id_by_name != &env_array[195]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_id_static != &env_array[196]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->items != &env_array[197]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_instance_method_static_by_name != &env_array[198]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_method_id != &env_array[199]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->strerror_nolen != &env_array[200]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->strerror_string_nolen != &env_array[201]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_compile_type_name_raw != &env_array[202]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_compile_type_name != &env_array[203]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_command_info_base_time != &env_array[204]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_spvm_version_string != &env_array[205]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_spvm_version_number != &env_array[206]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_version_string != &env_array[207]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_version_number != &env_array[208]) { stack[0].ival = 0; return 0; }

  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_byte_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int8_t value = env->get_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].bval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_byte_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int8_t value = env->get_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].bval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_short_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int16_t value = env->get_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }

  stack[0].sval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_short_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int16_t value = env->get_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].sval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_int_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int32_t value = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].ival = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_int_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int32_t value = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].ival = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_long_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].lval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_long_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].lval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_float_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].fval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_float_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].fval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_double_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].dval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_double_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].dval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_object_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;

  void* value = env->get_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_object_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* value = env->get_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_byte_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", INT8_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_byte_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", INT8_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_short_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", INT16_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_short_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", INT16_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_int_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", INT32_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_int_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", INT32_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_long_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  env->set_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", INT64_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_long_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  env->set_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", INT64_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_float_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", FLT_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_float_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", FLT_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_double_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", DBL_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_double_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", DBL_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_object_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* minimal = env->new_object_by_name(env, stack, "TestCase::Minimal", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  env->set_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", minimal, &e, __func__, FILE_NAME, __LINE__);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_object_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* minimal = env->new_object_by_name(env, stack, "TestCase::Minimal", &e, __func__, FILE_NAME, __LINE__);
  
  env->set_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", minimal, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* minimal = env->new_object_by_name(env, stack, "TestCase::Minimal", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = minimal;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_new_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* minimal = env->new_object_by_name(env, stack, "NotFound", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = minimal;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_new_pointer_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* pointer;
  int32_t e;
  void* minimal = env->new_pointer_object_by_name(env, stack, "TestCase::NotFound", pointer, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = minimal;
  
  return 0;
}


int32_t SPVM__TestCase__NativeAPI__has_interface_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* object = stack[0].oval;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, "TestCase::Callback::Callback");
  if (basic_type_id < 0) {
    assert(0);
  }
  
  int32_t match = env->has_interface(env, stack, object, basic_type_id);
  
  stack[0].ival = match;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__is_type_test_minimals(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* object = stack[0].oval;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, "TestCase::Minimal");
  if (basic_type_id < 0) {
    assert(0);
  }
  
  int32_t match = env->is_type(env, stack, object, basic_type_id, 1);
  
  stack[0].ival = match;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_byte_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int8_t x_in1 = stack[0].bval;
  int8_t x_in2 = stack[1].bval;
  
  *(stack[2].bref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_short_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int16_t x_in1 = stack[0].sval;
  int16_t x_in2 = stack[1].sval;
  
  *(stack[2].sref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_int_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t x_in1 = stack[0].ival;
  int32_t x_in2 = stack[1].ival;
  
  *(stack[2].iref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_long_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int64_t x_in1 = stack[0].lval;
  int64_t x_in2 = stack[1].lval;
  
  *(stack[2].lref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_float_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float x_in1 = stack[0].fval;
  float x_in2 = stack[1].fval;
  
  *(stack[2].fref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_double_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double x_in1 = stack[0].dval;
  double x_in2 = stack[1].dval;
  
  *(stack[2].dref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* object = stack[0].oval;
  
  env->set_field_byte_by_name(env, stack, object, "byte_value", INT8_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_byte_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* object = stack[0].oval;
  
  env->set_field_byte_by_name(env, stack, object, "not_found", INT8_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_short_by_name(env, stack, object, "short_value", INT16_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_short_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_short_by_name(env, stack, object, "not_found", INT16_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_int_by_name(env, stack, object, "int_value", INT32_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_int_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_int_by_name(env, stack, object, "not_found", INT32_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_long_by_name(env, stack, object, "long_value", INT64_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_long_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_long_by_name(env, stack, object, "not_found", INT64_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_float_by_name(env, stack, object, "float_value", FLT_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_float_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_float_by_name(env, stack, object, "not_found", FLT_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_double_by_name(env, stack, object, "double_value", DBL_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_double_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_double_by_name(env, stack, object, "not_found", DBL_MIN, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* object_simple = stack[0].oval;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, "TestCase::Minimal");
  if (basic_type_id < 0) {
    return 1;
  }
  void* object_minimal = env->new_object(env, stack, basic_type_id);
  
  int32_t field_id_minimal_x = env->get_field_id(env, stack, object_minimal, "x");
  if (field_id_minimal_x < 0) {
    return 1;
  }
  env->set_field_int(env, stack, object_minimal, field_id_minimal_x, 3);
  
  env->set_field_object_by_name(env, stack, object_simple, "object_value", object_minimal, &e, __func__, FILE_NAME, __LINE__);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* object_simple = stack[0].oval;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, "TestCase::Minimal");
  if (basic_type_id < 0) {
    return 1;
  }
  void* object_minimal = env->new_object(env, stack, basic_type_id);
  
  int32_t field_id_minimal_x = env->get_field_id(env, stack, object_minimal, "x");
  if (field_id_minimal_x < 0) {
    return 1;
  }
  env->set_field_int(env, stack, object_minimal, field_id_minimal_x, 3);
  
  env->set_field_object_by_name(env, stack, object_simple, "not_found", object_minimal, &e, __func__, FILE_NAME, __LINE__);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "byte_value", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (byte_value == INT8_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_byte_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "not_found", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (byte_value == INT8_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int16_t short_value = env->get_field_short_by_name(env, stack, object, "short_value", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (short_value == INT16_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_short_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int16_t short_value = env->get_field_short_by_name(env, stack, object, "not_found", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (short_value == INT16_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int32_t int_value = env->get_field_int_by_name(env, stack, object, "int_value", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (int_value == INT32_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_int_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int32_t int_value = env->get_field_int_by_name(env, stack, object, "not_found", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (int_value == INT32_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int64_t long_value = env->get_field_long_by_name(env, stack, object, "long_value", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (long_value == INT64_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_long_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int64_t long_value = env->get_field_long_by_name(env, stack, object, "not_found", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (long_value == INT64_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  float float_value = env->get_field_float_by_name(env, stack, object, "float_value", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (float_value == FLT_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_float_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  float float_value = env->get_field_float_by_name(env, stack, object, "not_found", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (float_value == FLT_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  double double_value = env->get_field_double_by_name(env, stack, object, "double_value", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (double_value == DBL_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_double_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  double double_value = env->get_field_double_by_name(env, stack, object, "not_found", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  if (double_value == DBL_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* object_simple = stack[0].oval;
  
  void* object_minimal = env->get_field_object_by_name(env, stack, object_simple, "object_value", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  int32_t field_id_minimal_x = env->get_field_id(env, stack, object_minimal, "x");
  if (field_id_minimal_x < 0) {
    return 1;
  }
  
  int32_t x = env->get_field_int(env, stack, object_minimal, field_id_minimal_x);
  
  if (x == 5) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* string_chars_simple = stack[0].oval;
  
  const char* string_chars = env->get_field_string_chars_by_name(env, stack, string_chars_simple, "string_value", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; };
  
  if (strcmp(string_chars, "abc") == 0) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_string_chars_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* string_chars_simple = stack[0].oval;
  
  const char* string_chars = env->get_field_string_chars_by_name(env, stack, string_chars_simple, "not_found", &e, __func__, FILE_NAME, __LINE__);
  if (e) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* object_simple = stack[0].oval;
  
  void* object_minimal = env->get_field_object_by_name(env, stack, object_simple, "not_found", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  int32_t field_id_minimal_x = env->get_field_id(env, stack, object_minimal, "x");
  if (field_id_minimal_x < 0) {
    return 1;
  }
  
  int32_t x = env->get_field_int(env, stack, object_minimal, field_id_minimal_x);
  
  if (x == 5) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_use_strlen(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* string = stack[0].oval;
  
  int8_t* bytes = env->get_elems_byte(env, stack, string);
  
  int32_t length = (int32_t)strlen((char*)bytes);
  
  stack[0].ival = length;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, stack, test_case, "x_byte");
  if (field_id < 0) {
    return 1;
  }
  
  int8_t value = env->get_field_byte(env, stack, test_case, field_id);
  
  stack[0].bval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, stack, test_case, "x_short");
  if (field_id < 0) {
    return 1;
  }
  
  int16_t value = env->get_field_short(env, stack, test_case, field_id);
  
  stack[0].sval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, stack, test_case, "x_int");
  if (field_id < 0) {
    return 1;
  }
  
  int32_t value = env->get_field_int(env, stack, test_case, field_id);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, stack, test_case, "x_long");
  if (field_id < 0) {
    return 1;
  }
  
  int64_t value = env->get_field_long(env, stack, test_case, field_id);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, stack, test_case, "x_float");
  if (field_id < 0) {
    return 1;
  }
  
  float value = env->get_field_float(env, stack, test_case, field_id);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, stack, test_case, "x_double");
  if (field_id < 0) {
    return 1;
  }
  
  double value = env->get_field_double(env, stack, test_case, field_id);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, stack, test_case, "minimal");
  if (field_id < 0) {
    return 1;
  }
  
  void* value = env->get_field_object(env, stack, test_case, field_id);
  
  stack[0].oval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t total = stack[0].ival + stack[1].ival;
  
  stack[0].ival = total;
  
  return 0;
}


int32_t SPVM__TestCase__NativeAPI__add_int_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_nums1 = stack[0].oval;
  void* obj_nums2 = stack[1].oval;
  
  int32_t length = env->length(env, stack, obj_nums1);
  
  int32_t* nums1 = env->get_elems_int(env, stack, obj_nums1);
  int32_t* nums2 = env->get_elems_int(env, stack, obj_nums2);
  
  void* onums3 = env->new_int_array(env, stack, length);
  int32_t* nums3 = env->get_elems_int(env, stack, onums3);
  
  for (int32_t i = 0; i < length; i++) {
    nums3[i] = nums1[i] + nums2[i];
  }
  
  stack[0].oval = onums3;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_void_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, stack, "Exception %s", "ppp", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_byte_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, stack, "Exception", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_short_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  return env->die(env, stack, "Exception", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_int_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, stack, "Exception", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_long_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, stack, "Exception", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

float SPVM__TestCase__NativeAPI__call_float_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, stack, "Exception", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_double_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, stack, "Exception", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_object_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, stack, "Exception", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__mortal_api(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  // Check if object count is zero in extension.t
  int32_t ref_count = 0;
  
  int32_t length = 10;
  // 1
  {
    void* obj_values = env->new_byte_array(env, stack, length);
    ref_count += env->get_ref_count(env, stack, obj_values);
  }
  // 2
  {
    void* obj_values = env->new_short_array(env, stack, length);
    ref_count += env->get_ref_count(env, stack, obj_values);
  }
  // 3
  {
    void* obj_values = env->new_int_array(env, stack, length);
    ref_count += env->get_ref_count(env, stack, obj_values);
  }
  // 4
  {
    void* obj_values = env->new_long_array(env, stack, length);
    ref_count += env->get_ref_count(env, stack, obj_values);
  }
  // 5
  {
    void* obj_values = env->new_float_array(env, stack, length);
    ref_count += env->get_ref_count(env, stack, obj_values);
  }
  // 6
  {
    void* obj_values = env->new_long_array(env, stack, length);
    ref_count += env->get_ref_count(env, stack, obj_values);
  }
  // 7
  {
    void* obj_values = env->new_string(env, stack, "foo", (int32_t)strlen("foo"));
    ref_count += env->get_ref_count(env, stack, obj_values);
  }
  // 8
  {
    int32_t basic_type_id = env->get_basic_type_id(env, stack, "TestCase::Minimal");
    if (basic_type_id < 0) {
      return 1;
    }
    void* obj_object = env->new_object(env, stack, basic_type_id);
    ref_count += env->get_ref_count(env, stack, obj_object);
  }
  // 9
  {
    int32_t basic_type_id = env->get_basic_type_id(env, stack, "TestCase::Minimal");
    if (basic_type_id < 0) {
      return 1;
    }
    void* obj_objects = env->new_object_array(env, stack, basic_type_id, 3);
    ref_count += env->get_ref_count(env, stack, obj_objects);
  }
  // 10
  {
    int32_t basic_type_id = env->get_basic_type_id(env, stack, "TestCase::Minimal");
    if (basic_type_id < 0) {
      return 1;
    }
    void* obj_objects = env->new_object_array(env, stack, basic_type_id, 3);
    ref_count += env->get_ref_count(env, stack, obj_objects);
  }
  // 11
  {
    int32_t basic_type_id = env->get_basic_type_id(env, stack, "TestCase::Pointer");
    if (basic_type_id < 0) {
      return 1;
    }
    void* obj_objects = env->new_pointer_object(env, stack, basic_type_id, NULL);
    ref_count += env->get_ref_count(env, stack, obj_objects);
  }
  
  if (ref_count == 11) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__enter_scope_leave_scope(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t length = 10;
  int32_t start_memory_blocks_count = env->get_memory_blocks_count(env);
  env->new_int_array(env, stack, length);
  env->new_int_array(env, stack, length);
  int32_t before_enter_memory_blocks_count = env->get_memory_blocks_count(env);
  int32_t before_leave_memory_blocks_count;
  {
    int32_t scope_id = env->enter_scope(env, stack);

    env->new_int_array(env, stack, length);
    env->new_int_array(env, stack, length);
    env->new_int_array(env, stack, length);
    
    before_leave_memory_blocks_count = env->get_memory_blocks_count(env);
    env->leave_scope(env, stack, scope_id);
  }
  
  int32_t after_leave_memory_blocks_counts = env->get_memory_blocks_count(env);
  
  stack[0].ival = 0;
  if ((before_enter_memory_blocks_count - start_memory_blocks_count) == 2) {
    if (before_enter_memory_blocks_count == after_leave_memory_blocks_counts) {
      if ((before_leave_memory_blocks_count - before_enter_memory_blocks_count) == 3) {
        stack[0].ival = 1;
      }
    }
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_call_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t method_id = env->get_class_method_id(env, stack, "TestCase::NativeAPI", "my_value");
  if (method_id < 0) {
    return 1;
  }
  int32_t output;
  {
    int32_t args_stack_length = 1;
    stack[0].ival = 5;
    int32_t error = env->call_method(env, stack, method_id, args_stack_length);
    if (error) {
      return 1;
    }
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }

  int32_t method_id2 = env->get_method_id(env, stack, "TestCase::NativeAPI", "my_value");
  if (method_id2 != method_id) {
    return 1;
  }

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_call_class_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t output;
  {
    int32_t args_stack_length = 1;
    stack[0].ival = 5;
    int32_t error = env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "my_value", args_stack_length, __func__, FILE_NAME, __LINE__);
    if (error) {
      return error;
    }
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_call_class_method_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t output;
  {
    int32_t args_stack_length = 1;
    stack[0].ival = 5;
    int32_t error = env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "not_found", args_stack_length, __func__, FILE_NAME, __LINE__);
    if (error) {
      return error;
    }
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_instance_method_static_by_name_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* minimal = stack[0].oval;
  
  int32_t output;
  {
    int32_t args_stack_length = 1;
    stack[0].oval = minimal;
    int32_t error = env->call_instance_method_static_by_name(env, stack, "TestCase::Minimal", "x", args_stack_length, __func__, FILE_NAME, __LINE__);
    if (e) { return e; }
    output = stack[0].ival;
  }
  
  stack[0].ival = output;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_instance_method_static_by_name_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;

  void* minimal = stack[0].oval;
  
  int32_t output;
  {
    int32_t args_stack_length = 1;
    stack[0].oval = minimal;
    e = env->call_instance_method_static_by_name(env, stack, "TestCase::Minimal", "not_found", args_stack_length, __func__, FILE_NAME, __LINE__);
    if (e) { return e; };
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_instance_method_by_name_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* minimal = stack[0].oval;
  
  int32_t output;
  {
    int32_t args_stack_length = 1;
    stack[0].oval = minimal;
    int32_t error = env->call_instance_method_by_name(env, stack, "x", args_stack_length, __func__, FILE_NAME, __LINE__);
    if (e) { return e; }
    output = stack[0].ival;
  }
  
  stack[0].ival = output;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_instance_method_by_name_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;

  void* minimal = stack[0].oval;
  
  int32_t output;
  {
    int32_t args_stack_length = 1;
    stack[0].oval = minimal;
    e = env->call_instance_method_by_name(env, stack, "not_found", args_stack_length, __func__, FILE_NAME, __LINE__);
    if (e) { return e; };
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__push_mortal_multi(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* iarray = env->new_int_array_raw(env, stack, 10);
  
  env->push_mortal(env, stack, iarray);
  env->push_mortal(env, stack, iarray);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_instance_method_id_static_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* minimal = stack[0].oval;
  
  int32_t method_id = env->get_instance_method_id_static(env, stack, "TestCase::Minimal", "x");
  if (method_id < 0) { return 0; }
  
  int32_t ret;
  {
    int32_t args_stack_length = 0;
    env->call_method(env, stack, method_id, args_stack_length);
    if (e) { return e; }
    ret = stack[0].ival;
  }
  
  stack[0].ival = ret;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_bool_object_value_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* bool_object = stack[0].oval;
  
  int32_t value = env->get_bool_object_value(env, stack, bool_object);
  
  stack[0].ival = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_string_raw(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  // Basic
  {
    void* string = env->new_string_raw(env, stack, "abc", 3);

    int32_t string_basic_type_id = env->get_object_basic_type_id(env, stack, string);
    int32_t string_type_dimension = env->get_object_type_dimension(env, stack, string);
    if (!(string_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && string_type_dimension == 0)) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }

    if (env->length(env, stack, string) != 3) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "abc") != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    env->inc_ref_count(env, stack, string);
    env->dec_ref_count(env, stack, string);
  }

  // Length is shorten than the string
  {
    void* string = env->new_string_raw(env, stack, "abc", 1);

    if (env->length(env, stack, string) != 1) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "a") != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    env->inc_ref_count(env, stack, string);
    env->dec_ref_count(env, stack, string);
  }

  // Length is shorten than the string 0
  {
    void* string = env->new_string_raw(env, stack, "abc", 0);

    if (env->length(env, stack, string) != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "") != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    env->inc_ref_count(env, stack, string);
    env->dec_ref_count(env, stack, string);
  }

  // Length is longer than the string
  {
    void* string = env->new_string_raw(env, stack, "abc", 4);

    if (env->length(env, stack, string) != 4) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strncmp(string_chars, "abc\0\0", 5) != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    env->inc_ref_count(env, stack, string);
    env->dec_ref_count(env, stack, string);
  }

  // NULL
  {
    void* string = env->new_string_raw(env, stack, NULL, 4);

    if (env->length(env, stack, string) != 4) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strncmp(string_chars, "\0\0\0\0\0", 5) != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    env->inc_ref_count(env, stack, string);
    env->dec_ref_count(env, stack, string);
  }

  // NULL 0
  {
    void* string = env->new_string_raw(env, stack, NULL, 0);

    if (env->length(env, stack, string) != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strncmp(string_chars, "\0", 1) != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    env->inc_ref_count(env, stack, string);
    env->dec_ref_count(env, stack, string);
  }


  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  // Basic
  {
    void* string = env->new_string(env, stack, "abc", 3);

    int32_t string_basic_type_id = env->get_object_basic_type_id(env, stack, string);
    int32_t string_type_dimension = env->get_object_type_dimension(env, stack, string);
    if (!(string_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && string_type_dimension == 0)) {
      stack[0].ival = 0;
      return 0;
    }

    if (env->length(env, stack, string) != 3) {
      stack[0].ival = 0;
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "abc") != 0) {
      stack[0].ival = 0;
      return 0;
    }
  }

  // Length is shorten than the string
  {
    void* string = env->new_string(env, stack, "abc", 1);

    if (env->length(env, stack, string) != 1) {
      stack[0].ival = 0;
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "a") != 0) {
      stack[0].ival = 0;
      return 0;
    }
  }

  // Length is shorten than the string 0
  {
    void* string = env->new_string(env, stack, "abc", 0);

    if (env->length(env, stack, string) != 0) {
      stack[0].ival = 0;
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "") != 0) {
      stack[0].ival = 0;
      return 0;
    }
  }

  // Length is longer than the string
  {
    void* string = env->new_string(env, stack, "abc", 4);

    if (env->length(env, stack, string) != 4) {
      stack[0].ival = 0;
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strncmp(string_chars, "abc\0\0", 5) != 0) {
      stack[0].ival = 0;
      return 0;
    }
  }

  // NULL
  {
    void* string = env->new_string(env, stack, NULL, 4);

    if (env->length(env, stack, string) != 4) {
      stack[0].ival = 0;
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strncmp(string_chars, "\0\0\0\0\0", 5) != 0) {
      stack[0].ival = 0;
      return 0;
    }
  }

  // NULL 0
  {
    void* string = env->new_string(env, stack, NULL, 0);

    if (env->length(env, stack, string) != 0) {
      stack[0].ival = 0;
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strncmp(string_chars, "\0", 1) != 0) {
      stack[0].ival = 0;
      return 0;
    }
  }

  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_string_nolen_raw(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  // Basic
  {
    void* string = env->new_string_nolen_raw(env, stack, "abc");

    int32_t string_basic_type_id = env->get_object_basic_type_id(env, stack, string);
    int32_t string_type_dimension = env->get_object_type_dimension(env, stack, string);
    if (!(string_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && string_type_dimension == 0)) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }

    if (env->length(env, stack, string) != 3) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "abc") != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    env->inc_ref_count(env, stack, string);
    env->dec_ref_count(env, stack, string);
  }

  // ""
  {
    void* string = env->new_string_nolen_raw(env, stack, "");

    if (env->length(env, stack, string) != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "") != 0) {
      stack[0].ival = 0;
      env->inc_ref_count(env, stack, string);
      env->dec_ref_count(env, stack, string);
      return 0;
    }
    
    env->inc_ref_count(env, stack, string);
    env->dec_ref_count(env, stack, string);
  }

  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  // Basic
  {
    void* string = env->new_string_nolen(env, stack, "abc");

    int32_t string_basic_type_id = env->get_object_basic_type_id(env, stack, string);
    int32_t string_type_dimension = env->get_object_type_dimension(env, stack, string);
    if (!(string_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && string_type_dimension == 0)) {
      stack[0].ival = 0;
      return 0;
    }

    if (env->length(env, stack, string) != 3) {
      stack[0].ival = 0;
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "abc") != 0) {
      stack[0].ival = 0;
      return 0;
    }
  }

  // ""
  {
    void* string = env->new_string_nolen(env, stack, "");

    if (env->length(env, stack, string) != 0) {
      stack[0].ival = 0;
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "") != 0) {
      stack[0].ival = 0;
      return 0;
    }
  }

  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_constant_values(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void** env_array = (void**)env;
  
  // Constant Values of Basic Type IDs
  {
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN != 0) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF != 1) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_VOID != 2) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE != 3) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT != 4) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_INT != 5) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_LONG != 6) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT != 7) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE != 8) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_STRING != 9) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT != 10) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS != 11) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS != 12) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS != 13) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS != 14) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS != 15) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS != 16) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS != 17) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS != 18) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_COMMAND_INFO_CLASS != 19) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS != 20) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS != 21) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ADDRESS_CLASS != 22) { stack[0].ival = 0; return 0; }
  }

  // Constant Values of Basic Type Categories
  {
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN != 0) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NOT_FOUND_CLASS != 1) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNDEF != 2) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID != 3) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC != 4) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM != 5) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING != 6) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS != 7) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE != 8) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT != 9) { stack[0].ival = 0; return 0; }
  }

  // Constant Values of Class IDs
  {
    if (SPVM_NATIVE_C_CLASS_ID_ERROR != 1) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM != 2) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED != 3) { stack[0].ival = 0; return 0; }
  }

  // Type flags
  {
    if (SPVM_NATIVE_C_TYPE_FLAG_REF != 1) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_TYPE_FLAG_MUTABLE != 2) { stack[0].ival = 0; return 0; }
  }
  
  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_precompile_indexes(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void** env_array = (void**)env->api->precompile;

  if ((void*)&env->api->precompile->new_object != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->precompile->free_object != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->precompile->set_runtime != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->precompile->get_runtime != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->precompile->build_class_source != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->precompile->build_method_source != &env_array[5]) { stack[0].ival = 0; return 0; }

  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_string_buffer_indexes(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void** env_array = (void**)env->api->string_buffer;

  if ((void*)&env->api->string_buffer->new_object != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->string_buffer->free_object != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->string_buffer->get_value != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->string_buffer->get_length != &env_array[3]) { stack[0].ival = 0; return 0; }

  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_allocator_indexes(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void** env_array = (void**)env->api->allocator;

  if ((void*)&env->api->allocator->new_object != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->allocator->free_object != &env_array[1]) { stack[0].ival = 0; return 0; }

  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_compiler_indexes(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void** env_array = (void**)env->api->compiler;

  if ((void*)&env->api->compiler->new_object != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->free_object != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->set_start_line != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_start_line != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->set_start_file != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_start_file != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->add_class_path != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_class_paths_length != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_class_path != &env_array[8]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->compile != &env_array[9]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_error_messages_length != &env_array[10]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_error_message != &env_array[11]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->create_runtime_codes != &env_array[12]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->clear_class_paths != &env_array[13]) { stack[0].ival = 0; return 0; }

  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_runtime_indexes(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void** env_array = (void**)env->api->runtime;

  if ((void*)&env->api->runtime->new_object != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->free_object != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_opcodes != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_opcodes_length != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_runtime_codes != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_runtime_codes_length != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_classes_length != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_constant_string_id != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_constant_string_value != &env_array[8]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_name != &env_array[9]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_basic_type_id_by_name != &env_array[10]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_basic_type_name_id != &env_array[11]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_basic_type_class_id != &env_array[12]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_basic_type_category != &env_array[13]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_type_basic_type_id != &env_array[14]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_type_dimension != &env_array[15]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_type_stack_length != &env_array[16]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_type_is_object != &env_array[17]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_type_is_ref != &env_array[18]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_id_by_name != &env_array[19]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_name_id != &env_array[20]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_class_rel_file_id != &env_array[21]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_class_path_id != &env_array[22]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_is_anon != &env_array[23]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_fields_base_id != &env_array[24]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_fields_length != &env_array[25]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_methods_base_id != &env_array[26]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_methods_length != &env_array[27]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_class_vars_base_id != &env_array[28]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_class_vars_length != &env_array[29]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_anon_methods_base_id != &env_array[30]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_anon_methods_length != &env_array[31]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_var_id_by_index != &env_array[32]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_var_id_by_name != &env_array[33]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_var_name_id != &env_array[34]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_var_class_id != &env_array[35]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_field_id_by_index != &env_array[36]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_field_id_by_name != &env_array[37]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_field_name_id != &env_array[38]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_field_type_id != &env_array[39]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_field_class_id != &env_array[40]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_id_by_index != &env_array[41]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_id_by_name != &env_array[42]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_name_id != &env_array[43]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_return_type_id != &env_array[44]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_class_id != &env_array[45]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_is_class_method != &env_array[46]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_is_anon != &env_array[47]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_is_native != &env_array[48]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_is_precompile != &env_array[49]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_call_stack_byte_vars_length != &env_array[50]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_call_stack_short_vars_length != &env_array[51]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_call_stack_int_vars_length != &env_array[52]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_call_stack_long_vars_length != &env_array[53]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_call_stack_float_vars_length != &env_array[54]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_call_stack_double_vars_length != &env_array[55]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_call_stack_object_vars_length != &env_array[56]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_call_stack_ref_vars_length != &env_array[57]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_mortal_stack_length != &env_array[58]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_opcodes_base_id != &env_array[59]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_opcodes_length != &env_array[60]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_args_base_id != &env_array[61]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_args_length != &env_array[62]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_arg_type_id != &env_array[63]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_anon_method_method_id != &env_array[64]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_native_method_address != &env_array[65]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->set_native_method_address != &env_array[66]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_precompile_method_address != &env_array[67]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->set_precompile_method_address != &env_array[68]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_header_size != &env_array[69]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_weaken_backref_head_offset != &env_array[70]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_ref_count_offset != &env_array[71]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_basic_type_id_offset != &env_array[72]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_type_dimension_offset != &env_array[73]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_flag_offset != &env_array[74]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_length_offset != &env_array[75]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_allocator != &env_array[76]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->build != &env_array[77]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_parent_class_id != &env_array[78]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_required_args_length != &env_array[79]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_is_pointer != &env_array[80]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_method_is_enum != &env_array[81]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_type_flag != &env_array[82]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->is_object_type != &env_array[83]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_class_version_string_id != &env_array[84]) { stack[0].ival = 0; return 0; }
  
  spvm_warn("Foo %s %d", "aaa", 3);
  spvm_warn("Foo");
  
  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_memory_apis(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  {
    int32_t memory_blocks_count_env_start = env->get_memory_blocks_count(env);
    
    void* memory_block = env->alloc_memory_block_zero(env, sizeof(SPVM_ENV));
    
    if (!(env->get_memory_blocks_count(env) == memory_blocks_count_env_start + 1)) {
      stack[0].ival = 0;
      return 0;
    }
    
    env->free_memory_block(env, memory_block);
    
    if (!(env->get_memory_blocks_count(env) == memory_blocks_count_env_start)) {
      stack[0].ival = 0;
      return 0;
    }
  }

  {
    int32_t memory_blocks_count_env_start = env->get_memory_blocks_count_env(env);
    
    void* memory_block = env->new_memory_env(env, sizeof(SPVM_ENV));
    
    if (!(env->get_memory_blocks_count_env(env) == memory_blocks_count_env_start + 1)) {
      stack[0].ival = 0;
      return 0;
    }
    
    env->free_memory_env(env, memory_block);
    
    if (!(env->get_memory_blocks_count_env(env) == memory_blocks_count_env_start)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    void* new_stack = env->new_stack(env);
    env->free_stack(env, new_stack);
  }

  {
    void* new_stack = env->new_stack(env);

    int32_t memory_blocks_count_env_start = env->get_memory_blocks_count_env(env);
    
    int32_t memory_blocks_count_stack_start = env->get_memory_blocks_count_stack(env, stack);
    int32_t memory_blocks_count_new_stack_start = env->get_memory_blocks_count_stack(env, new_stack);
    
    void* memory_block_stack = env->new_memory_stack(env, stack, sizeof(SPVM_ENV));
    void* memory_block_new_stack = env->new_memory_stack(env, new_stack, sizeof(SPVM_ENV));

    if (!(env->get_memory_blocks_count_env(env) == memory_blocks_count_env_start + 2)) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!(env->get_memory_blocks_count_stack(env, stack) == memory_blocks_count_stack_start + 1)) {
      stack[0].ival = 0;
      return 0;
    }

    if (!(env->get_memory_blocks_count_stack(env, new_stack) == memory_blocks_count_new_stack_start + 1)) {
      stack[0].ival = 0;
      return 0;
    }
    
    
    env->free_memory_stack(env, stack, memory_block_stack);
    env->free_memory_stack(env, new_stack, memory_block_new_stack);

    if (!(env->get_memory_blocks_count_env(env) == memory_blocks_count_env_start)) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!(env->get_memory_blocks_count_stack(env, stack) == memory_blocks_count_stack_start)) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!(env->get_memory_blocks_count_stack(env, new_stack) == memory_blocks_count_new_stack_start)) {
      stack[0].ival = 0;
      return 0;
    }
    
    env->free_stack(env, new_stack);
  }
  
  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  {
    int32_t error_class_id = env->get_class_id(env, stack, "Error");
    if (!(error_class_id == 1)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int32_t error_class_id = env->get_class_id(env, stack, "NotFoundClass");
    if (!(error_class_id < 0)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_id_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t e;
  
  {
    int32_t error_class_id = env->get_class_id_by_name(env, stack, "Error", &e, __func__, FILE_NAME, __LINE__);
    
    if (!(error_class_id == 1)) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!(e == 0)) {
      stack[0].ival = 0;
      return 0;
    }
  }

  {
    int32_t error_class_id = env->get_class_id_by_name(env, stack, "NotFoundClass", &e, __func__, FILE_NAME, __LINE__);
    
    if (!(error_class_id < 0)) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!(e == 1)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}


int32_t SPVM__TestCase__NativeAPI__get_basic_type_id_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t e;
  
  {
    int32_t int_basic_type_id = env->get_basic_type_id_by_name(env, stack, "int", &e, __func__, FILE_NAME, __LINE__);
    
    if (!(int_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT)) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!(e == 0)) {
      stack[0].ival = 0;
      return 0;
    }
  }

  {
    int32_t not_found_basic_type_id = env->get_basic_type_id_by_name(env, stack, "NotFoundBasicType", &e, __func__, FILE_NAME, __LINE__);
    
    if (!(not_found_basic_type_id < 0)) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!(e == 1)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__strerror_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t errno_value = stack[0].ival;
  
  const char* strerror_value = env->strerror(env, stack, errno_value, 0);
  void* obj_strerror_value = env->new_string(env, stack, strerror_value, strlen(strerror_value));
  
  stack[0].oval = obj_strerror_value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__strerror_string_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t errno_value = stack[0].ival;
  
  void* strerror_string_value = env->strerror_string(env, stack, errno_value, 0);
  
  stack[0].oval = strerror_string_value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__strerror_nolen_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t errno_value = stack[0].ival;
  
  const char* strerror_value = env->strerror_nolen(env, stack, errno_value);
  void* obj_strerror_value = env->new_string(env, stack, strerror_value, strlen(strerror_value));
  
  stack[0].oval = obj_strerror_value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__strerror_string_nolen_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t errno_value = stack[0].ival;
  
  void* strerror_string_value = env->strerror_string_nolen(env, stack, errno_value);
  
  stack[0].oval = strerror_string_value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_object_array_raw(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_object_array = env->new_object_array_raw(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, 2);
  
  if (!(env->is_type(env, stack, obj_object_array, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, 1))) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->get_ref_count(env, stack, obj_object_array) == 0)) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->length(env, stack, obj_object_array) == 2)) {
    stack[0].ival = 0;
    return 0;
  }
  
  // Free
  env->inc_ref_count(env, stack, obj_object_array);
  env->dec_ref_count(env, stack, obj_object_array);
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_object_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_object_array = env->new_object_array(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, 2);
  
  if (!(env->is_type(env, stack, obj_object_array, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, 1))) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->get_ref_count(env, stack, obj_object_array) == 1)) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->length(env, stack, obj_object_array) == 2)) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_string_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string_array = env->new_string_array(env, stack, 2);
  
  if (!(env->is_type(env, stack, obj_string_array, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, 1))) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->get_ref_count(env, stack, obj_string_array) == 1)) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->length(env, stack, obj_string_array) == 2)) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_string_array_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string_array = env->new_string_array(env, stack, 2);
  env->set_elem_object(env, stack, obj_string_array, 0, env->new_string_nolen(env, stack, "abc"));
  env->set_elem_object(env, stack, obj_string_array, 1, env->new_string_nolen(env, stack, "def"));
  
  stack[0].oval = obj_string_array;
  return 0;
}


int32_t SPVM__TestCase__NativeAPI__get_args_stack_length_0(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->get_args_stack_length(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_args_stack_length_1(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->get_args_stack_length(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_args_stack_length_2(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->get_args_stack_length(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_args_stack_length_4(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->get_args_stack_length(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__items_0(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->items(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__items_1(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->items(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__items_2(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->items(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__items_4(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->items(env, stack);
  
  return 0;
}


int32_t SPVM__TestCase__NativeAPI__dumpc(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  
  const char* dumpc = env->dumpc(env, stack, NULL);
  
  if (!(strcmp(dumpc, "undef") == 0)) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_stdin_stdout_stderr_binary_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32  
  int32_t stdin_old_mode = _setmode(0, _O_BINARY);
  
  if (!(stdin_old_mode == _O_BINARY)) {
    stack[0].ival = 0;
    return 0;
  }
  
  int32_t stdout_old_mode = _setmode(1, _O_BINARY);
  if (!(stdout_old_mode == _O_BINARY)) {
    stack[0].ival = 0;
    return 0;
  }
  
  int32_t stderr_old_mode = _setmode(2, _O_BINARY);
  if (!(stderr_old_mode == _O_BINARY)) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;

#else
  stack[0].ival = 1;
  
  return 0;
#endif
}

int32_t SPVM__TestCase__NativeAPI__precompile_build_methodd_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t success = 1;
  
  {
    // New allocator
    void* allocator = env->api->allocator->new_object();
    
    // New string buffer
    void* string_buffer = env->api->string_buffer->new_object(allocator, 0);

    void* precompile = env->api->precompile->new_object();
    
    env->api->precompile->set_runtime(precompile, env->runtime);
    
    env->api->precompile->build_method_source(precompile, string_buffer, "TestCase::NativeAPI", "get_class_var_byte_by_name");
    
    env->api->precompile->free_object(precompile);

    const char* string_buffer_value = env->api->string_buffer->get_value(string_buffer);
    int32_t string_buffer_length = env->api->string_buffer->get_length(string_buffer);
    
    if (!strstr(string_buffer_value, "TestCase::NativeAPI")) {
      success = 0;
    }

    if (!strstr(string_buffer_value, "get_class_var_byte_by_name")) {
      success = 0;
    }
    
    // Free string buffer
    env->api->string_buffer->free_object(string_buffer);

    // Free allocator
    env->api->allocator->free_object(allocator);
  }
  
  stack[0].ival = success;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_compile_type_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = 1;
  
  {
    int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_INT;
    int32_t type_dimension = 0;
    int32_t type_flag = 0;
    void* obj_compile_type_name = env->get_compile_type_name(env, stack, basic_type_id, type_dimension, type_flag);
    const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
    if (!(strcmp(compile_type_name, "int") == 0)) {
      stack[0].ival = 0;
    }
  }
  
  {
    int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_INT;
    int32_t type_dimension = 2;
    int32_t type_flag = 0;
    void* obj_compile_type_name = env->get_compile_type_name(env, stack, basic_type_id, type_dimension, type_flag);
    const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
    if (!(strcmp(compile_type_name, "int[][]") == 0)) {
      stack[0].ival = 0;
    }
  }
  
  {
    int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_INT;
    int32_t type_dimension = 0;
    int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_REF;
    void* obj_compile_type_name = env->get_compile_type_name(env, stack, basic_type_id, type_dimension, type_flag);
    const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
    if (!(strcmp(compile_type_name, "int*") == 0)) {
      stack[0].ival = 0;
    }
  }
  
  {
    int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_STRING;
    int32_t type_dimension = 0;
    int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_MUTABLE;
    void* obj_compile_type_name = env->get_compile_type_name(env, stack, basic_type_id, type_dimension, type_flag);
    const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
    if (!(strcmp(compile_type_name, "mutable string") == 0)) {
      stack[0].ival = 0;
    }
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__runtime_get_method_is_enum(SPVM_ENV* env, SPVM_VALUE* stack) {

  stack[0].ival = 1;
  
  int32_t method_id = env->get_method_id(env, stack, "TestCase::NativeAPI", "VALUE0");
  assert(method_id >= 0);
  
  int32_t is_enum = env->api->runtime->get_method_is_enum(env->runtime, method_id);
  if (!is_enum) {
      stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_string_field_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* sv_self = stack[0].oval;
  
  int32_t e = 0;
  
  void* sv_text = env->get_field_object_by_name(env, stack, sv_self, "text", &e, __func__, FILE_NAME, __LINE__);
  if (e) {
    stack[0].ival = 0;
    return 0;
  }
  
  int32_t length = env->length(env, stack, sv_text);
  
  if (length != 5) {
    stack[0].ival = 0;
    return 0;
  }

  const char* text_chars = env->get_chars(env, stack, sv_text);

  if (strcmp(text_chars, "Hello") != 0) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;
}
