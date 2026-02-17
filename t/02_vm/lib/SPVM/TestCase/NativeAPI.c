#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>

#include <spvm_native.h>

static const char* FILE_NAME = "TestCase/NativeAPI.c";

int32_t SPVM__TestCase__NativeAPI__check_native_api_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;

  const char* func_name = __func__;
  
  void** env_array = (void**)env;
  
  if ((void*)&env->runtime!= &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api!= &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_env != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_env != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_init_methods != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_command_info_program_name != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_command_info_argv != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_command_info_basetime != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->destroy_class_vars != &env_array[8]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->args_width != &env_array[9]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_object_basic_type != &env_array[10]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_object_basic_type_id != &env_array[11]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_object_basic_type_name != &env_array[12]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_object_type_dimension != &env_array[13]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_basic_type != &env_array[14]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_basic_type_by_name != &env_array[15]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_basic_type_by_id != &env_array[16]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_basic_type_id != &env_array[17]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_basic_type_id_by_name != &env_array[18]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var != &env_array[19]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_byte != &env_array[20]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_short != &env_array[21]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_int != &env_array[22]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_long != &env_array[23]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_float != &env_array[24]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_double != &env_array[25]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_object != &env_array[26]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_string != &env_array[27]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_byte != &env_array[28]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_short != &env_array[29]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_int != &env_array[30]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_long != &env_array[31]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_float != &env_array[32]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_double != &env_array[33]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_object != &env_array[34]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_string != &env_array[35]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_object_ref != &env_array[36]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_byte_by_name != &env_array[37]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_short_by_name != &env_array[38]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_int_by_name != &env_array[39]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_long_by_name != &env_array[40]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_float_by_name != &env_array[41]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_double_by_name != &env_array[42]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_object_by_name != &env_array[43]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_var_string_by_name != &env_array[44]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_byte_by_name != &env_array[45]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_short_by_name != &env_array[46]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_int_by_name != &env_array[47]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_long_by_name != &env_array[48]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_float_by_name != &env_array[49]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_double_by_name != &env_array[50]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_object_by_name != &env_array[51]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_class_var_string_by_name != &env_array[52]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field != &env_array[53]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_static != &env_array[54]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_byte != &env_array[55]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_short != &env_array[56]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_int != &env_array[57]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_long != &env_array[58]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_float != &env_array[59]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_double != &env_array[60]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_object != &env_array[61]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_string != &env_array[62]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_byte != &env_array[63]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_short != &env_array[64]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_int != &env_array[65]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_long != &env_array[66]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_float != &env_array[67]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_double != &env_array[68]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_object != &env_array[69]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_string != &env_array[70]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_byte_by_name != &env_array[71]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_short_by_name != &env_array[72]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_int_by_name != &env_array[73]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_long_by_name != &env_array[74]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_float_by_name != &env_array[75]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_double_by_name != &env_array[76]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_object_by_name != &env_array[77]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_string_by_name != &env_array[78]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_byte_by_name != &env_array[79]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_short_by_name != &env_array[80]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_int_by_name != &env_array[81]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_long_by_name != &env_array[82]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_float_by_name != &env_array[83]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_double_by_name != &env_array[84]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_object_by_name != &env_array[85]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_field_string_by_name != &env_array[86]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_string_chars_by_name != &env_array[87]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_method != &env_array[88]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_class_method != &env_array[89]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_instance_method_static != &env_array[90]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_instance_method != &env_array[91]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_method_no_mortal != &env_array[92]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_method != &env_array[93]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_class_method_by_name != &env_array[94]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_instance_method_static_by_name != &env_array[95]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_instance_method_by_name != &env_array[96]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object_no_mortal != &env_array[97]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object != &env_array[98]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object_by_name != &env_array[99]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_pointer_object_no_mortal != &env_array[100]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_pointer_object != &env_array[101]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_pointer_object_by_name != &env_array[102]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_pointer != &env_array[103]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_pointer != &env_array[104]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string_nolen_no_mortal != &env_array[105]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string_nolen != &env_array[106]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string_no_mortal != &env_array[107]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string != &env_array[108]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_byte_array_no_mortal != &env_array[109]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_byte_array != &env_array[110]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_short_array_no_mortal != &env_array[111]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_short_array != &env_array[112]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_int_array_no_mortal != &env_array[113]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_int_array != &env_array[114]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_long_array_no_mortal != &env_array[115]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_long_array != &env_array[116]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_float_array_no_mortal != &env_array[117]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_float_array != &env_array[118]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_double_array_no_mortal != &env_array[119]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_double_array != &env_array[120]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object_array_no_mortal != &env_array[121]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object_array != &env_array[122]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_object_array_by_name != &env_array[123]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string_array != &env_array[124]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_muldim_array_no_mortal != &env_array[125]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_muldim_array != &env_array[126]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_muldim_array_by_name != &env_array[127]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_mulnum_array_no_mortal != &env_array[128]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_mulnum_array != &env_array[129]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_mulnum_array_by_name != &env_array[130]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_array_proto_no_mortal != &env_array[131]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_array_proto != &env_array[132]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->length != &env_array[133]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_byte != &env_array[134]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_short != &env_array[135]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_int != &env_array[136]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_long != &env_array[137]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_float != &env_array[138]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elems_double != &env_array[139]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elem_object != &env_array[140]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elem_string != &env_array[141]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_elem_object != &env_array[142]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_elem_string != &env_array[143]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_chars != &env_array[144]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_bool_object_value != &env_array[145]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->concat_no_mortal != &env_array[146]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->concat != &env_array[147]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->shorten != &env_array[148]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->make_read_only != &env_array[149]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_read_only != &env_array[150]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->print != &env_array[151]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->print_stderr != &env_array[152]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->dump_no_mortal != &env_array[153]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->dump != &env_array[154]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->dumpc != &env_array[155]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->copy_no_mortal != &env_array[156]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->copy != &env_array[157]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_spvm_version_string != &env_array[158]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_spvm_version_number != &env_array[159]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_version_string != &env_array[160]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_version_number != &env_array[161]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->die != &env_array[162]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_exception != &env_array[163]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_exception != &env_array[164]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_stack_trace_no_mortal != &env_array[165]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_stack_trace != &env_array[166]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_string != &env_array[167]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_class != &env_array[168]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_pointer_class != &env_array[169]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_array != &env_array[170]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_object_array != &env_array[171]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_numeric_array != &env_array[172]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_mulnum_array != &env_array[173]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->isa != &env_array[174]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->isa_by_name != &env_array[175]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_type != &env_array[176]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_type_by_name != &env_array[177]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->elem_isa != &env_array[178]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_elem_size != &env_array[179]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_type_name_no_mortal != &env_array[180]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_type_name != &env_array[181]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_compile_type_name_no_mortal != &env_array[182]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_compile_type_name != &env_array[183]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->enter_scope != &env_array[184]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->leave_scope != &env_array[185]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->push_mortal != &env_array[186]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->weaken != &env_array[187]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->isweak != &env_array[188]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->unweaken != &env_array[189]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->strerror_string != &env_array[190]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->strerror_string_nolen != &env_array[191]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->strerror != &env_array[192]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->strerror_nolen != &env_array[193]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_binary_compatible_object != &env_array[194]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_binary_compatible_stack != &env_array[195]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_stack != &env_array[196]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_stack != &env_array[197]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_object_defined_and_has_pointer_by_name != &env_array[198]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_object_ref != &env_array[199]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_field_object_ref_by_name != &env_array[200]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->check_bootstrap_method != &env_array[201]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->assign_object != &env_array[202]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_string_array_no_mortal != &env_array[203]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_memory_block != &env_array[204]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->free_memory_block != &env_array[205]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_memory_blocks_count != &env_array[206]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->say != &env_array[207]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->warn != &env_array[208]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->spvm_stdin != &env_array[209]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->spvm_stdout != &env_array[210]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->spvm_stderr != &env_array[211]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_array_proto_element_no_mortal != &env_array[212]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_array_proto_element != &env_array[213]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_byte_object_value != &env_array[214]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_short_object_value != &env_array[215]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_int_object_value != &env_array[216]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_long_object_value != &env_array[217]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_float_object_value != &env_array[218]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_double_object_value != &env_array[219]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->no_free != &env_array[220]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_no_free != &env_array[221]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_stack_tmp_buffer != &env_array[222]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->print_exception_to_stderr != &env_array[223]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->dump_object_internal != &env_array[224]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_seed != &env_array[225]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_seed != &env_array[226]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->seed_initialized != &env_array[227]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_basic_type_name_in_version_from != &env_array[228]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_command_info_warning != &env_array[229]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->destroy_cache_class_vars != &env_array[230]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->new_stack_with_all_method_call_permitted != &env_array[231]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_instance_method_no_mortal != &env_array[232]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_instance_method != &env_array[233]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_method_no_mortal_no_check_args != &env_array[234]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_instance_method_no_mortal_less_check_args != &env_array[235]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->enable_options != &env_array[236]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->disable_options != &env_array[237]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_options != &env_array[238]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_any_object_array != &env_array[239]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->exists_field != &env_array[240]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->exists_field_by_name != &env_array[241]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->delete_field != &env_array[242]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->delete_field_by_name != &env_array[243]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->make_fixed_length != &env_array[244]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_fixed_length != &env_array[245]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_length != &env_array[246]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->capacity != &env_array[247]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_capacity != &env_array[248]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->numeric_object_to_byte != &env_array[249]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->numeric_object_to_short != &env_array[250]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->numeric_object_to_int != &env_array[251]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->numeric_object_to_long != &env_array[252]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->numeric_object_to_float != &env_array[253]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->numeric_object_to_double != &env_array[254]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->numeric_object_to_string_no_mortal != &env_array[255]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->numeric_object_to_string != &env_array[256]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_numeric_object != &env_array[257]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->say_stderr != &env_array[258]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_call_depth != &env_array[259]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_caller_info_stack != &env_array[260]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_caller_info_stack_record_size != &env_array[261]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->get_current_method != &env_array[262]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->caller_no_mortal != &env_array[263]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->caller != &env_array[264]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->die_with_string != &env_array[265]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->build_exception_message_no_mortal != &env_array[266]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->build_exception_message != &env_array[267]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->call_end_methods != &env_array[268]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->is_utf8 != &env_array[269]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_byte_object_value != &env_array[270]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_short_object_value != &env_array[271]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_int_object_value != &env_array[272]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_long_object_value != &env_array[273]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_float_object_value != &env_array[274]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->set_double_object_value != &env_array[275]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_allocator_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->allocator;
  
  if ((void*)&env->api->allocator->new_instance != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->allocator->free_instance != &env_array[1]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_arg_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->arg;
  
  if ((void*)&env->api->arg->get_name != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->arg->get_index != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->arg->get_basic_type != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->arg->get_type_dimension != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->arg->get_type_flag != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->arg->get_stack_index != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->arg->get_current_method != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->arg->is_optional != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->arg->get_default_value != &env_array[8]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_basic_type_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->basic_type;
  
  if ((void*)&env->api->basic_type->get_name != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_id != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_category != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_parent != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_version_string != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_class_dir != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_class_rel_file != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->is_pointer != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->is_anon != &env_array[8]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_class_var_by_index != &env_array[9]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_class_var_by_name != &env_array[10]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_class_vars_length != &env_array[11]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_field_by_index != &env_array[12]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_field_by_name != &env_array[13]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_fields_length != &env_array[14]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_method_by_index != &env_array[15]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_method_by_name != &env_array[16]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_methods_length != &env_array[17]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_anon_basic_type_by_index != &env_array[18]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_anon_basic_types_length != &env_array[19]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->has_interface != &env_array[20]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->is_super_class != &env_array[21]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_file != &env_array[22]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_current_runtime != &env_array[23]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_basic_type_in_version_from != &env_array[24]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_fields_size != &env_array[25]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->get_monitor_var_type != &env_array[26]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->basic_type->has_monitor_var != &env_array[27]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_class_file_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->class_file;
  
  if ((void*)&env->api->class_file->get_class_name != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->get_file != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->set_file != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->get_dir != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->set_dir != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->get_rel_file != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->set_rel_file != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->get_content != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->set_content != &env_array[8]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->get_content_length != &env_array[9]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_file->set_content_length != &env_array[10]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_class_var_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->class_var;
  
  if ((void*)&env->api->class_var->get_name != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_var->get_index != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_var->get_basic_type != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_var->get_type_dimension != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_var->get_type_flag != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_var->get_current_basic_type != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->class_var->is_cache != &env_array[6]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_compiler_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->compiler;
  
  if ((void*)&env->api->compiler->new_instance != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->free_instance != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_start_line != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->set_start_line != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_start_file != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->set_start_file != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_include_dirs_length != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_include_dir != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->add_include_dir != &env_array[8]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->clear_include_dirs != &env_array[9]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->add_class_file != &env_array[10]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->delete_class_file != &env_array[11]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_class_file != &env_array[12]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->compile != &env_array[13]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_error_message != &env_array[14]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_error_messages_length != &env_array[15]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->get_runtime != &env_array[16]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->prepend_include_dir != &env_array[17]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->compile_anon_class != &env_array[18]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->compiler->compile_script != &env_array[19]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_field_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->field;
  
  if ((void*)&env->api->field->get_name != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->field->get_index != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->field->get_offset != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->field->get_basic_type != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->field->get_type_dimension != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->field->get_type_flag != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->field->get_current_basic_type != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->field->get_exists_offset != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->field->get_exists_bit != &env_array[8]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_internal_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->internal;
  
  if ((void*)&env->api->internal->get_ref_count != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->internal->inc_ref_count != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->internal->dec_ref_count != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->internal->removed3 != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->internal->get_stack_tmp_buffer != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->internal->leave_scope_local != &env_array[5]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_method_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->method;
  
  if ((void*)&env->api->method->get_name != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_index != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_return_basic_type != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_return_type_dimension != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_return_type_flag != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_arg_by_index != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_args_length != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_required_args_length != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_current_basic_type != &env_array[8]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_opcode_by_index != &env_array[9]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_opcodes_length != &env_array[10]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->is_class_method != &env_array[11]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->is_anon != &env_array[12]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->is_native != &env_array[13]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->is_precompile != &env_array[14]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->is_enum != &env_array[15]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_byte_vars_width != &env_array[16]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_short_vars_width != &env_array[17]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_int_vars_width != &env_array[18]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_long_vars_width != &env_array[19]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_float_vars_width != &env_array[20]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_double_vars_width != &env_array[21]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_object_vars_width != &env_array[22]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_ref_vars_width != &env_array[23]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_mortal_stack_length != &env_array[24]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_native_address != &env_array[25]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->set_native_address != &env_array[26]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_precompile_address != &env_array[27]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->set_precompile_address != &env_array[28]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->is_precompile_fallback != &env_array[29]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->set_is_precompile_fallback != &env_array[30]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->removed31 != &env_array[31]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->removed32 != &env_array[32]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_args_signature != &env_array[33]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->method->get_abs_name != &env_array[34]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_mutex_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->mutex;
  
  if ((void*)&env->api->mutex->new_instance != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->mutex->free_instance != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->mutex->lock != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->mutex->unlock != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->mutex->reader_lock != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->mutex->reader_unlock != &env_array[5]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_runtime_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->runtime;
  
  if ((void*)&env->api->runtime->get_object_data_offset != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_object_ref_count_offset != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_object_length_offset != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_basic_type_by_id != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_basic_type_by_name != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_basic_types_length != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->build_precompile_class_source != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->build_precompile_method_source != &env_array[7]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_compiler != &env_array[8]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->set_compiler != &env_array[9]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_spvm_stdin != &env_array[10]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_spvm_stdout != &env_array[11]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_spvm_stderr != &env_array[12]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_env != &env_array[13]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->get_object_capacity_offset != &env_array[14]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->method_begin_cb != &env_array[15]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->method_end_cb != &env_array[16]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_data_offset != &env_array[17]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_length_offset != &env_array[18]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->object_capacity_offset != &env_array[19]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->stack_index_call_depth != &env_array[20]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->stack_index_caller_info_stack != &env_array[21]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->runtime->stack_index_caller_info_stack_record_size != &env_array[22]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_string_buffer_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->string_buffer;
  
  if ((void*)&env->api->string_buffer->new_instance != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->string_buffer->free_instance != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->string_buffer->get_string != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->string_buffer->get_length != &env_array[3]) { stack[0].ival = 0; return 0; }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_type_ids(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void** env_array = (void**)env->api->type;
  
  if ((void*)&env->api->type->can_assign != &env_array[0]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->type->get_type_width != &env_array[1]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->type->is_object_type != &env_array[2]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->type->is_any_object_type != &env_array[3]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->type->is_object_array_type != &env_array[4]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->type->is_any_object_array_type != &env_array[5]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->type->is_numeric_type != &env_array[6]) { stack[0].ival = 0; return 0; }
  if ((void*)&env->api->type->is_class_type != &env_array[7]) { stack[0].ival = 0; return 0; }
  
  {
    void* basic_type = env->get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_INT);
    
    int32_t ret = env->api->type->is_numeric_type(env->runtime, basic_type, 0, 0);
    
    if (!ret) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    void* basic_type = env->get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS);
    
    int32_t ret = env->api->type->is_class_type(env->runtime, basic_type, 0, 0);
    
    if (!ret) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    void* basic_type = env->get_basic_type(env, stack, "Complex_2d");
    
    {
      int32_t can_assign = env->api->type->can_assign(env->runtime, basic_type, 1, SPVM_NATIVE_C_TYPE_FLAG_REF, basic_type, 1, SPVM_NATIVE_C_TYPE_FLAG_REF);
      
      if (!can_assign) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
    {
      int32_t can_assign = env->api->type->can_assign(env->runtime, basic_type, 1, SPVM_NATIVE_C_TYPE_FLAG_REF, basic_type, 1, 0);
      
      if (can_assign) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__check_native_api_constant_values(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
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
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS != 19) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS != 20) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_COMMAND_INFO_CLASS != 21) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ADDRESS_CLASS != 22) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_COMPILE_CLASS != 23) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_SPVM_CLASS != 24) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_METHOD_CALL_NOT_PERMITTED_CLASS != 25) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_STRINGABLE_CLASS != 26) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_COUNTABLE_CLASS != 27) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_CALLER_INFO_CLASS != 28) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_ID_CLONEABLE_CLASS != 29) { stack[0].ival = 0; return 0; }
  }

  // Basic Type Category IDs
  {
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN != 0) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNDEF != 1) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID != 2) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC != 3) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM != 4) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING != 5) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS != 6) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE != 7) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT != 8) { stack[0].ival = 0; return 0; }
  }
  
  // Type Flag IDs
  {
    if (SPVM_NATIVE_C_TYPE_FLAG_REF != 1) { stack[0].ival = 0; return 0; }
    if (SPVM_NATIVE_C_TYPE_FLAG_MUTABLE != 2) { stack[0].ival = 0; return 0; }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__spvm_warn(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  spvm_warn("[Test Output]spvm_warn: %s %d", "aaa", 3);
  spvm_warn("[Test Output]spvm_warn:Foo");
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__spvm_warnf(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  spvm_warnf(env->spvm_stderr(env, stack), "[Test Output]spvm_warnf: %s %d", "aaa", 3);
  spvm_warnf(env->spvm_stderr(env, stack), "[Test Output]spvm_warnf:Foo");
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* class_var = env->get_class_var(env, stack, "TestCase::NativeAPI", "$INT_VALUE");
  
  if (!class_var) {
    stack[0].ival = 0;
    return 0;
  }
  
  env->set_class_var_int(env, stack, class_var, INT32_MIN);
  
  int32_t value = env->get_class_var_int(env, stack, class_var);
  
  if (!(value == INT32_MIN)) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_byte_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* class_var = env->get_class_var(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE");
  
  if (!class_var) {
    stack[0].ival = 0;
    return 0;
  }
  
  int8_t value = env->get_class_var_byte(env, stack, class_var);
  
  if (!(value == 0x0F)) {
    stack[0].ival = 0;
    return 0;
  }

  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_int_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* class_var = env->get_class_var(env, stack, "TestCase::NativeAPI", "$INT_VALUE");
 
  if (!class_var) {
    stack[0].ival = 0;
    return 0;
  }
  
  int32_t value = env->get_class_var_int(env, stack, class_var);
  
  if (!(value == -2147483648)) {
    stack[0].ival = 0;
    return 0;
  }

  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_short_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* class_var = env->get_class_var(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE");
  
  if (!class_var) {
    stack[0].ival = 0;
    return 0;
  }
  
  int16_t value = env->get_class_var_short(env, stack, class_var);
  
  if (!(value == -32768)) {
    stack[0].ival = 0;
    return 0;
  }

  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_long_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* class_var = env->get_class_var(env, stack, "TestCase::NativeAPI", "$LONG_VALUE");
  
  if (!class_var) {
    stack[0].ival = 0;
    return 0;
  }
  
  long value = env->get_class_var_long(env, stack, class_var);
  
  if (!(value == 2147483647)) {
    stack[0].ival = 0;
    return 0;
  }

  stack[0].ival = 1;
  return 0;
}


int32_t SPVM__TestCase__NativeAPI__get_class_var_float_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* class_var = env->get_class_var(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE");
  
  if (!class_var) {
    stack[0].ival = 0;
    return 0;
  }
  
  float value = env->get_class_var_float(env, stack, class_var);
  
  if (!(value == 3.402823e+38f)) {
    stack[0].ival = 0;
    return 0;
  }

  stack[0].ival = 1;
  return 0;
}


int32_t SPVM__TestCase__NativeAPI__get_class_var_double_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* class_var = env->get_class_var(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE");
  
  if (!class_var) {
    stack[0].ival = 0;
    return 0;
  }
  
  double value = env->get_class_var_double(env, stack, class_var);
  
  if (!(value == 1.79769e+308)) {
    stack[0].ival = 0;
    return 0;
  }

  stack[0].ival = 1;
  return 0;
}


int32_t SPVM__TestCase__NativeAPI__get_class_var_byte_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    int8_t value = env->get_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_byte_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int8_t value = env->get_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].bval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_short_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    int16_t value = env->get_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int16_t value = env->get_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_short_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int16_t value = env->get_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].sval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_int_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    int32_t value = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int32_t value = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int32_t value = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_int_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t value = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].ival = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_long_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT64_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_long_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].lval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_float_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == FLT_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_float_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].fval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_double_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == FLT_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == DBL_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_double_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].dval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_object_test(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  
  void* value = env->get_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_class_var_object_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* value = env->get_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = value;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_byte_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_byte_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;

  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_short_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_short_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;

  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_int_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_int_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;

  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_long_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  env->set_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", INT64_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_long_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  env->set_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", INT64_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_float_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  env->set_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_float_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;

  env->set_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_double_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;

  env->set_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", DBL_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_double_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;

  env->set_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", DBL_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_object_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* minimal = env->new_object_by_name(env, stack, "TestCase::Minimal", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", minimal, &error_id, __func__, FILE_NAME, __LINE__);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__set_class_var_object_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  void* minimal = env->new_object_by_name(env, stack, "TestCase::Minimal", &error_id, __func__, FILE_NAME, __LINE__);
  
  env->set_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$NOT_FOUND", minimal, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  void* minimal = env->new_object_by_name(env, stack, "TestCase::Minimal", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = minimal;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_new_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {  
  int32_t error_id = 0;
  void* minimal = env->new_object_by_name(env, stack, "NotFound", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = minimal;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_new_pointer_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* pointer;
  int32_t error_id = 0;
  void* minimal = env->new_pointer_object_by_name(env, stack, "TestCase::NotFound", pointer, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = minimal;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__is_type_test_minimals(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::Minimal");
  if (!basic_type) {
    assert(0);
  }
  
  int32_t match = env->is_type(env, stack, object, basic_type, 1);
  
  stack[0].ival = match;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_byte_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int8_t x_in1 = stack[0].bval;
  int8_t x_in2 = stack[1].bval;
  
  *(stack[2].bref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_short_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int16_t x_in1 = stack[0].sval;
  int16_t x_in2 = stack[1].sval;
  
  *(stack[2].sref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_int_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t x_in1 = stack[0].ival;
  int32_t x_in2 = stack[1].ival;
  
  *(stack[2].iref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_long_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int64_t x_in1 = stack[0].lval;
  int64_t x_in2 = stack[1].lval;
  
  *(stack[2].lref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_float_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  float x_in1 = stack[0].fval;
  float x_in2 = stack[1].fval;
  
  *(stack[2].fref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__ref_double_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  double x_in1 = stack[0].dval;
  double x_in2 = stack[1].dval;
  
  *(stack[2].dref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  env->set_field_byte_by_name(env, stack, object, "byte_value", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_byte_by_name(env, stack, object, "short_value", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_byte_by_name(env, stack, object, "int_value", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_byte_by_name(env, stack, object, "long_value", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_byte_by_name(env, stack, object, "float_value", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_byte_by_name(env, stack, object, "double_value", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_byte_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  env->set_field_byte_by_name(env, stack, object, "not_found", INT8_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_short_by_name(env, stack, object, "byte_value", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_short_by_name(env, stack, object, "short_value", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_short_by_name(env, stack, object, "int_value", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_short_by_name(env, stack, object, "long_value", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_short_by_name(env, stack, object, "float_value", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_short_by_name(env, stack, object, "double_value", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_short_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_short_by_name(env, stack, object, "not_found", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_int_by_name(env, stack, object, "byte_value", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_int_by_name(env, stack, object, "short_value", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_int_by_name(env, stack, object, "int_value", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_int_by_name(env, stack, object, "long_value", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_int_by_name(env, stack, object, "float_value", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_int_by_name(env, stack, object, "double_value", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_int_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_int_by_name(env, stack, object, "not_found", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_long_by_name(env, stack, object, "byte_value", INT64_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_long_by_name(env, stack, object, "short_value", INT64_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_long_by_name(env, stack, object, "int_value", INT64_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_long_by_name(env, stack, object, "long_value", INT64_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_long_by_name(env, stack, object, "float_value", INT16_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_long_by_name(env, stack, object, "double_value", INT32_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_long_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_long_by_name(env, stack, object, "not_found", INT64_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_float_by_name(env, stack, object, "byte_value", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_float_by_name(env, stack, object, "short_value", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_float_by_name(env, stack, object, "int_value", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_float_by_name(env, stack, object, "long_value", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_float_by_name(env, stack, object, "float_value", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_float_by_name(env, stack, object, "double_value", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_float_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_float_by_name(env, stack, object, "not_found", FLT_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_double_by_name(env, stack, object, "byte_value", DBL_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_double_by_name(env, stack, object, "short_value", DBL_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_double_by_name(env, stack, object, "int_value", DBL_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_double_by_name(env, stack, object, "long_value", DBL_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_double_by_name(env, stack, object, "double_value", DBL_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_double_by_name(env, stack, object, "double_value", DBL_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_double_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  env->set_field_double_by_name(env, stack, object, "not_found", DBL_MIN, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  void* object_simple = stack[0].oval;
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::Minimal");
  if (!basic_type) {
    return 1;
  }
  void* object_minimal = env->new_object(env, stack, basic_type);
  
  void* field_minimal_x = env->get_field(env, stack, object_minimal, "x");
  if (!field_minimal_x) {
    return 1;
  }
  env->set_field_int(env, stack, object_minimal, field_minimal_x, 3);
  
  env->set_field_object_by_name(env, stack, object_simple, "object_value", object_minimal, &error_id, __func__, FILE_NAME, __LINE__);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_set_field_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  void* object_simple = stack[0].oval;
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::Minimal");
  if (!basic_type) {
    return 1;
  }
  void* object_minimal = env->new_object(env, stack, basic_type);
  
  void* field_minimal_x = env->get_field(env, stack, object_minimal, "x");
  if (!field_minimal_x) {
    return 1;
  }
  env->set_field_int(env, stack, object_minimal, field_minimal_x, 3);
  
  env->set_field_object_by_name(env, stack, object_simple, "not_found", object_minimal, &error_id, __func__, FILE_NAME, __LINE__);
  
  if (error_id) {
    return error_id;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  {
    int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(byte_value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(byte_value == (int8_t)INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(byte_value == (int8_t)INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(byte_value == (int8_t)INT64_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(byte_value == (int8_t)FLT_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(byte_value == (int8_t)DBL_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_byte_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  void* object = stack[0].oval;
  
  int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "not_found", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    int16_t short_value = env->get_field_short_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(short_value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int16_t short_value = env->get_field_short_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(short_value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int16_t short_value = env->get_field_short_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(short_value == (int16_t)INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int16_t short_value = env->get_field_short_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(short_value == (int16_t)INT64_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int16_t short_value = env->get_field_short_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(short_value == (int16_t)FLT_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int16_t short_value = env->get_field_short_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(short_value == (int16_t)DBL_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_short_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    int32_t int_value = env->get_field_short_by_name(env, stack, object, "not_found", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    int32_t int_value = env->get_field_int_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(int_value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int32_t int_value = env->get_field_int_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(int_value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int32_t int_value = env->get_field_int_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(int_value == INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int32_t int_value = env->get_field_int_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(int_value == (int32_t)INT64_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int32_t int_value = env->get_field_int_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(int_value == (int32_t)FLT_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int32_t int_value = env->get_field_int_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(int_value == (int32_t)DBL_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_int_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    int32_t int_value = env->get_field_int_by_name(env, stack, object, "not_found", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    int64_t long_value = env->get_field_long_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(long_value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int64_t long_value = env->get_field_long_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(long_value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int64_t long_value = env->get_field_long_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(long_value == INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int64_t long_value = env->get_field_long_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(long_value == INT64_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int64_t long_value = env->get_field_long_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(long_value == (int64_t)FLT_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    int64_t long_value = env->get_field_long_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(long_value == (int64_t)DBL_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_long_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    int64_t long_value = env->get_field_long_by_name(env, stack, object, "not_found", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    float float_value = env->get_field_float_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(float_value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    float float_value = env->get_field_float_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(float_value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    float float_value = env->get_field_float_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(float_value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    float float_value = env->get_field_float_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(float_value == INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    float float_value = env->get_field_float_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(float_value == FLT_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    float float_value = env->get_field_float_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(float_value == (float)DBL_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_float_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    float float_value = env->get_field_float_by_name(env, stack, object, "not_found", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    double double_value = env->get_field_double_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(double_value == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double double_value = env->get_field_double_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(double_value == INT16_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double double_value = env->get_field_double_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(double_value == INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double double_value = env->get_field_double_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(double_value == INT32_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double double_value = env->get_field_double_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(double_value == FLT_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    double double_value = env->get_field_double_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(double_value == DBL_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_double_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object = stack[0].oval;
  
  {
    double double_value = env->get_field_double_by_name(env, stack, object, "not_found", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object_simple = stack[0].oval;
  
  void* object_minimal = env->get_field_object_by_name(env, stack, object_simple, "object_value", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* field_minimal_x = env->get_field(env, stack, object_minimal, "x");
  if (!field_minimal_x) {
    return 1;
  }
  
  int32_t x = env->get_field_int(env, stack, object_minimal, field_minimal_x);
  
  if (!(x == 5)) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* string_chars_simple = stack[0].oval;
  
  const char* string_chars = env->get_field_string_chars_by_name(env, stack, string_chars_simple, "string_value", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; };
  
  if (!(strcmp(string_chars, "abc") == 0)) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_string_chars_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* string_chars_simple = stack[0].oval;
  
  const char* string_chars = env->get_field_string_chars_by_name(env, stack, string_chars_simple, "not_found", &error_id, __func__, FILE_NAME, __LINE__);
  if (!error_id) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_get_field_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* object_simple = stack[0].oval;
  
  void* object_minimal = env->get_field_object_by_name(env, stack, object_simple, "not_found", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* field_minimal_x = env->get_field(env, stack, object_minimal, "x");
  if (!field_minimal_x) {
    return 1;
  }
  
  int32_t x = env->get_field_int(env, stack, object_minimal, field_minimal_x);
  
  if (!(x == 5)) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_use_strlen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* string = stack[0].oval;
  
  int8_t* bytes = env->get_elems_byte(env, stack, string);
  
  int32_t length = (int32_t)strlen((char*)bytes);
  
  stack[0].ival = length;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* test_case = stack[0].oval;
  
  void* field = env->get_field(env, stack, test_case, "x_byte");
  if (!field) {
    return 1;
  }
  
  int8_t value = env->get_field_byte(env, stack, test_case, field);
  
  stack[0].bval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* test_case = stack[0].oval;
  
  void* field = env->get_field(env, stack, test_case, "x_short");
  if (!field) {
    return 1;
  }
  
  int16_t value = env->get_field_short(env, stack, test_case, field);
  
  stack[0].sval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* test_case = stack[0].oval;
  
  void* field = env->get_field(env, stack, test_case, "x_int");
  if (!field) {
    return 1;
  }
  
  int32_t value = env->get_field_int(env, stack, test_case, field);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* test_case = stack[0].oval;
  
  void* field = env->get_field(env, stack, test_case, "x_long");
  if (!field) {
    return 1;
  }
  
  int64_t value = env->get_field_long(env, stack, test_case, field);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* test_case = stack[0].oval;
  
  void* field = env->get_field(env, stack, test_case, "x_float");
  if (!field) {
    return 1;
  }
  
  float value = env->get_field_float(env, stack, test_case, field);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* test_case = stack[0].oval;
  
  void* field = env->get_field(env, stack, test_case, "x_double");
  if (!field) {
    return 1;
  }
  
  double value = env->get_field_double(env, stack, test_case, field);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_env_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* test_case = stack[0].oval;
  
  void* field = env->get_field(env, stack, test_case, "minimal");
  if (!field) {
    return 1;
  }
  
  void* value = env->get_field_object(env, stack, test_case, field);
  
  stack[0].oval = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t total = stack[0].ival + stack[1].ival;
  
  stack[0].ival = total;
  
  return 0;
}


int32_t SPVM__TestCase__NativeAPI__add_int_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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
  
  return env->die(env, stack, "Exception %s", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__, "ppp.");
}

int32_t SPVM__TestCase__NativeAPI__call_byte_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return env->die(env, stack, "Exception.", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_short_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Exception.", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_int_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return env->die(env, stack, "Exception.", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_long_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return env->die(env, stack, "Exception.", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

float SPVM__TestCase__NativeAPI__call_float_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return (float)env->die(env, stack, "Exception.", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_double_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {  
  return env->die(env, stack, "Exception.", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__call_object_method_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {  
  return env->die(env, stack, "Exception.", __func__, "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPVM__TestCase__NativeAPI__mortal_api(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // Check if object count is zero in extension.t
  int32_t ref_count = 0;
  
  int32_t length = 10;
  // 1
  {
    void* obj_values = env->new_byte_array(env, stack, length);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_values);
  }
  // 2
  {
    void* obj_values = env->new_short_array(env, stack, length);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_values);
  }
  // 3
  {
    void* obj_values = env->new_int_array(env, stack, length);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_values);
  }
  // 4
  {
    void* obj_values = env->new_long_array(env, stack, length);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_values);
  }
  // 5
  {
    void* obj_values = env->new_float_array(env, stack, length);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_values);
  }
  // 6
  {
    void* obj_values = env->new_long_array(env, stack, length);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_values);
  }
  // 7
  {
    void* obj_values = env->new_string(env, stack, "foo", (int32_t)strlen("foo"));
    ref_count += env->api->internal->get_ref_count(env, stack, obj_values);
  }
  // 8
  {
    void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::Minimal");
    if (!basic_type) {
      return 1;
    }
    void* obj_object = env->new_object(env, stack, basic_type);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_object);
  }
  // 9
  {
    void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::Minimal");
    if (!basic_type) {
      return 1;
    }
    void* obj_objects = env->new_object_array(env, stack, basic_type, 3);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_objects);
  }
  // 10
  {
    void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::Minimal");
    if (!basic_type) {
      return 1;
    }
    void* obj_objects = env->new_object_array(env, stack, basic_type, 3);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_objects);
  }
  // 11
  {
    void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::Pointer");
    if (!basic_type) {
      return 1;
    }
    void* obj_objects = env->new_pointer_object(env, stack, basic_type, NULL);
    ref_count += env->api->internal->get_ref_count(env, stack, obj_objects);
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
  
  int32_t length = 10;
  int32_t start_memory_blocks_count = env->get_memory_blocks_count(env, stack);
  env->new_int_array(env, stack, length);
  env->new_int_array(env, stack, length);
  int32_t before_enter_memory_blocks_count = env->get_memory_blocks_count(env, stack);
  int32_t before_leave_memory_blocks_count;
  {
    int32_t mortal_stack_top = env->enter_scope(env, stack);

    env->new_int_array(env, stack, length);
    env->new_int_array(env, stack, length);
    env->new_int_array(env, stack, length);
    
    before_leave_memory_blocks_count = env->get_memory_blocks_count(env, stack);
    env->leave_scope(env, stack, mortal_stack_top);
  }
  
  int32_t after_leave_memory_blocks_counts = env->get_memory_blocks_count(env, stack);
  
  stack[0].ival = 0;
  if ((before_enter_memory_blocks_count - start_memory_blocks_count) == 4) {
    if (before_enter_memory_blocks_count == after_leave_memory_blocks_counts) {
      if ((before_leave_memory_blocks_count - before_enter_memory_blocks_count) == 6) {
        stack[0].ival = 1;
      }
    }
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_call_method_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::NativeAPI");
  void* method = env->api->basic_type->get_method_by_name(env->runtime, basic_type, "my_value");
  if (!method) {
    return 1;
  }
  int32_t output;
  {
    int32_t args_width = 1;
    stack[0].ival = 5;
    int32_t error_id = env->call_method_no_mortal(env, stack, method, args_width, __func__, __FILE__, __LINE__);
    if (error_id) {
      return 1;
    }
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_call_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "Point");
  void* method = env->api->basic_type->get_method_by_name(env->runtime, basic_type, "new");
  if (!method) {
    return 1;
  }
  void* obj_point = NULL;
  {
    int32_t args_width = 2;
    stack[0].ival = 1;
    stack[1].ival = 2;
    error_id = env->call_method(env, stack, method, args_width, __func__, __FILE__, __LINE__);
    if (error_id) { return error_id; }
    obj_point = stack[0].oval;
  }
  
  int32_t x = env->get_field_int_by_name(env, stack, obj_point, "x", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  int32_t y = env->get_field_int_by_name(env, stack, obj_point, "y", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (!(x == 1)) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(y == 2)) {
    stack[0].ival = 0;
    return 0;
  }
  
  // Too few arguments
  env->call_class_method_by_name(env, stack, "TestCase::Operator::MethodCall", "optional_args_byte_one_required_tow_optional", 0, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    stack[0].ival = 0;
    return 0;
  }
  
  // Too many arguments. This is OK.
  env->call_class_method_by_name(env, stack, "TestCase::Operator::MethodCall", "optional_args_byte_one_required_tow_optional", 4, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_call_class_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  {
    int32_t error_id = 0;
    
    int32_t output;
    {
      int32_t args_width = 1;
      stack[0].ival = 5;
      env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "my_value", args_width, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) {
        return error_id;
      }
      output = stack[0].ival;
    }
    
    stack[0].ival = 0;
    
    if (!(output == 5)) {
      stack[0].ival = 0;
      return 0;
    }
    
    stack[0].ival = 1;
  }
  
  // Exceptions
  {
    {
      int32_t error_id = 0;
      
      stack[0].ival = 5;
      
      env->call_class_method_by_name(env, stack, "NotFound", "foo", 0, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "NotFound class is not found.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
    {
      int32_t error_id = 0;
      
      stack[0].ival = 5;
      
      env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "not_found", 0, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "TestCase::NativeAPI#not_found method is not found.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
    {
      int32_t error_id = 0;
      
      stack[0].ival = 5;
      
      env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "instance_method", 0, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "TestCase::NativeAPI#instance_method method must be a class method.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
    {
      int32_t error_id = 0;
      
      stack[0].oval = env->new_string_nolen(env, stack, "a");
      
      env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "arg_int_object", 1, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "The 1th argument must be assigned to the type of 1th argument of TestCase::NativeAPI#arg_int_object method.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__native_call_class_method_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t output;
  {
    int32_t args_width = 1;
    stack[0].ival = 5;
    env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "not_found", args_width, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) {
      return error_id;
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
  
  // Exceptions
  {
    {
      int32_t error_id = 0;
      
      env->call_instance_method_static_by_name(env, stack, "NotFound", "foo", 1, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "NotFound class is not found.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
    {
      int32_t error_id = 0;
      
      env->call_instance_method_static_by_name(env, stack, "TestCase::NativeAPI", "not_found", 1, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "TestCase::NativeAPI#not_found method is not found.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
    {
      int32_t error_id = 0;
      
      env->call_instance_method_static_by_name(env, stack, "TestCase::NativeAPI", "class_method", 1, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "TestCase::NativeAPI#class_method method must be an instance method.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_instance_method_static_by_name_native_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* minimal = stack[0].oval;
  
  int32_t output;
  {
    int32_t args_width = 1;
    stack[0].oval = minimal;
    env->call_instance_method_static_by_name(env, stack, "TestCase::Minimal", "x", args_width, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    output = stack[0].ival;
  }
  
  stack[0].ival = output;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_instance_method_static_by_name_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;

  void* minimal = stack[0].oval;
  
  int32_t output;
  {
    int32_t args_width = 1;
    stack[0].oval = minimal;
    env->call_instance_method_static_by_name(env, stack, "TestCase::Minimal", "not_found", args_width, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; };
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_instance_method_by_name_native(SPVM_ENV* env, SPVM_VALUE* stack) {  
  
  // Exceptions
  {
    {
      int32_t error_id = 0;
      
      env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "new", 0, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      void* object = stack[0].oval;
      
      stack[0].oval = object;
      env->call_instance_method_by_name(env, stack, "not_found", 1, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "n instance method call failed. TestCase::NativeAPI#not_found method is not found.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
    {
      int32_t error_id = 0;
      
      env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "new", 0, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      void* object = stack[0].oval;
      
      stack[0].oval = object;
      stack[1].oval = NULL;
      env->call_instance_method_by_name(env, stack, "arg_int_object_instance", 2, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      void* obj_ret = stack[0].oval;
      if (obj_ret) {
        stack[0].ival = 0;
        return 0;
      }
    }
      
    {
      int32_t error_id = 0;
      
      env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "new", 0, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      void* object = stack[0].oval;
      
      stack[0].oval = env->new_string_nolen(env, stack, "a");
      stack[1].oval = NULL;
      env->call_instance_method_by_name(env, stack, "arg_int_object_instance", 2, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "An instance method call failed. string#arg_int_object_instance method is not found.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
    {
      int32_t error_id = 0;
      
      env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "new", 0, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      void* object = stack[0].oval;
      
      stack[0].oval = object;
      stack[1].oval = env->new_string_nolen(env, stack, "a");
      env->call_instance_method_by_name(env, stack, "arg_int_object_instance", 2, &error_id, __func__, FILE_NAME, __LINE__);
      
      if (!error_id) {
        stack[0].ival = 0;
        return 0;
      }
      
      if(!strstr(env->get_chars(env, stack, env->get_exception(env, stack)), "The 1th argument must be assigned to the type of 1th argument of TestCase::NativeAPI#arg_int_object_instance method.")) {
        stack[0].ival = 0;
        return 0;
      }
    }
    
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_instance_method_by_name_native_value(SPVM_ENV* env, SPVM_VALUE* stack) {  
  int32_t error_id = 0;
  
  void* minimal = stack[0].oval;
  
  int32_t output;
  {
    int32_t args_width = 1;
    stack[0].oval = minimal;
    env->call_instance_method_by_name(env, stack, "x", args_width, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    output = stack[0].ival;
  }
  
  stack[0].ival = output;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__call_instance_method_by_name_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;

  void* minimal = stack[0].oval;
  
  int32_t output;
  {
    int32_t args_width = 1;
    stack[0].oval = minimal;
    env->call_instance_method_by_name(env, stack, "not_found", args_width, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; };
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__push_mortal_multi(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* iarray = env->new_int_array_no_mortal(env, stack, 10);
  
  env->push_mortal(env, stack, iarray);
  env->push_mortal(env, stack, iarray);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_instance_method_static_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* minimal = stack[0].oval;
  void* method = env->get_instance_method_static(env, stack, "TestCase::Minimal", "x");
  if (!method) { return 0; }
  
  int32_t ret;
  {
    int32_t args_width = 1;
    env->call_method(env, stack, method, args_width, __func__, __FILE__, __LINE__);
    if (error_id) { return error_id; }
    ret = stack[0].ival;
  }
  
  stack[0].ival = ret;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_bool_object_value_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* bool_object = stack[0].oval;
  
  int32_t value = env->get_bool_object_value(env, stack, bool_object);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_byte_object_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // Test get_byte_object_value (using INT8_MIN)
  {
    stack[0].ival = INT8_MIN;
    env->call_class_method_by_name(env, stack, "Byte", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }
    
    int32_t ret = env->get_byte_object_value(env, stack, obj_num);
    
    if (!(ret == INT8_MIN)) {
      stack[0].ival = 0;
      return 0;
    }
  }

  // Test set_byte_object_value (using INT8_MAX)
  {
    stack[0].ival = 0;
    env->call_class_method_by_name(env, stack, "Byte", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }

    env->set_byte_object_value(env, stack, obj_num, INT8_MAX);
    
    int8_t value = env->get_field_byte_by_name(env, stack, obj_num, "value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    if (!(value == INT8_MAX)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_short_object_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    stack[0].ival = INT16_MIN;
    env->call_class_method_by_name(env, stack, "Short", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }
    
    int32_t ret = env->get_short_object_value(env, stack, obj_num);
    if (!(ret == INT16_MIN)) { return 0; }
  }

  {
    stack[0].ival = 0;
    env->call_class_method_by_name(env, stack, "Short", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }

    env->set_short_object_value(env, stack, obj_num, INT16_MAX);
    int16_t value = env->get_field_short_by_name(env, stack, obj_num, "value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id || value != INT16_MAX) { stack[0].ival = 0; return 0; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_int_object_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    stack[0].ival = INT32_MIN;
    env->call_class_method_by_name(env, stack, "Int", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }
    
    int32_t ret = env->get_int_object_value(env, stack, obj_num);
    if (!(ret == INT32_MIN)) { return 0; }
  }

  {
    stack[0].ival = 0;
    env->call_class_method_by_name(env, stack, "Int", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }

    env->set_int_object_value(env, stack, obj_num, INT32_MAX);
    int32_t value = env->get_field_int_by_name(env, stack, obj_num, "value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id || value != INT32_MAX) { stack[0].ival = 0; return 0; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_long_object_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    stack[0].lval = INT64_MIN;
    env->call_class_method_by_name(env, stack, "Long", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }
    
    int64_t ret = env->get_long_object_value(env, stack, obj_num);
    if (!(ret == INT64_MIN)) { return 0; }
  }

  {
    stack[0].lval = 0L;
    env->call_class_method_by_name(env, stack, "Long", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }

    env->set_long_object_value(env, stack, obj_num, INT64_MAX);
    int64_t value = env->get_field_long_by_name(env, stack, obj_num, "value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id || value != INT64_MAX) { stack[0].ival = 0; return 0; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_float_object_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    stack[0].fval = -FLT_MAX;
    env->call_class_method_by_name(env, stack, "Float", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }
    
    float ret = env->get_float_object_value(env, stack, obj_num);
    if (!(ret == -FLT_MAX)) { return 0; }
  }

  {
    stack[0].fval = 0.0f;
    env->call_class_method_by_name(env, stack, "Float", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }

    env->set_float_object_value(env, stack, obj_num, FLT_MAX);
    float value = env->get_field_float_by_name(env, stack, obj_num, "value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id || value != FLT_MAX) { stack[0].ival = 0; return 0; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_double_object_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    stack[0].dval = -DBL_MAX;
    env->call_class_method_by_name(env, stack, "Double", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }
    
    double ret = env->get_double_object_value(env, stack, obj_num);
    if (!(ret == -DBL_MAX)) { return 0; }
  }

  {
    stack[0].dval = 0.0;
    env->call_class_method_by_name(env, stack, "Double", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
    void* obj_num = stack[0].oval;
    if (error_id) { return error_id; }

    env->set_double_object_value(env, stack, obj_num, DBL_MAX);
    double value = env->get_field_double_by_name(env, stack, obj_num, "value", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id || value != DBL_MAX) { stack[0].ival = 0; return 0; }
  }
  
  stack[0].ival = 1;
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_string_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // Basic
  {
    void* string = env->new_string_no_mortal(env, stack, "abc", 3);

    const char* string_basic_type_name = env->get_object_basic_type_name(env, stack, string);
    int32_t string_type_dimension = env->get_object_type_dimension(env, stack, string);
    if (!(strcmp(string_basic_type_name, "string") == 0 && string_type_dimension == 0)) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }

    if (env->length(env, stack, string) != 3) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "abc") != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    // Assign and destroy
    void* referent = NULL;
    env->assign_object(env, stack, &referent, string);
    env->assign_object(env, stack, &referent, NULL);
  }

  // Length is shorten than the string
  {
    void* string = env->new_string_no_mortal(env, stack, "abc", 1);

    if (env->length(env, stack, string) != 1) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "a") != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    // Assign and destroy
    void* referent = NULL;
    env->assign_object(env, stack, &referent, string);
    env->assign_object(env, stack, &referent, NULL);
  }

  // Length is shorten than the string 0
  {
    void* string = env->new_string_no_mortal(env, stack, "abc", 0);

    if (env->length(env, stack, string) != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "") != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    // Assign and destroy
    void* referent = NULL;
    env->assign_object(env, stack, &referent, string);
    env->assign_object(env, stack, &referent, NULL);
  }

  // Length is longer than the string
  {
    void* string = env->new_string_no_mortal(env, stack, "abc", 4);

    if (env->length(env, stack, string) != 4) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strncmp(string_chars, "abc\0\0", 5) != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    // Assign and destroy
    void* referent = NULL;
    env->assign_object(env, stack, &referent, string);
    env->assign_object(env, stack, &referent, NULL);
  }

  // NULL
  {
    void* string = env->new_string_no_mortal(env, stack, NULL, 4);

    if (env->length(env, stack, string) != 4) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strncmp(string_chars, "\0\0\0\0\0", 5) != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    // Assign and destroy
    void* referent = NULL;
    env->assign_object(env, stack, &referent, string);
    env->assign_object(env, stack, &referent, NULL);
  }

  // NULL 0
  {
    void* string = env->new_string_no_mortal(env, stack, NULL, 0);

    if (env->length(env, stack, string) != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strncmp(string_chars, "\0", 1) != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    // Assign and destroy
    void* referent = NULL;
    env->assign_object(env, stack, &referent, string);
    env->assign_object(env, stack, &referent, NULL);
  }


  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // Basic
  {
    void* string = env->new_string(env, stack, "abc", 3);

    const char* string_basic_type_name = env->get_object_basic_type_name(env, stack, string);
    int32_t string_type_dimension = env->get_object_type_dimension(env, stack, string);
    if (!(strcmp(string_basic_type_name, "string") == 0 && string_type_dimension == 0)) {
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

int32_t SPVM__TestCase__NativeAPI__new_string_nolen_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // Basic
  {
    void* string = env->new_string_nolen_no_mortal(env, stack, "abc");

    const char* string_basic_type_name = env->get_object_basic_type_name(env, stack, string);
    int32_t string_type_dimension = env->get_object_type_dimension(env, stack, string);
    if (!(strcmp(string_basic_type_name, "string") == 0 && string_type_dimension == 0)) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }

    if (env->length(env, stack, string) != 3) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "abc") != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    // Assign and destroy
    void* referent = NULL;
    env->assign_object(env, stack, &referent, string);
    env->assign_object(env, stack, &referent, NULL);
  }

  // ""
  {
    void* string = env->new_string_nolen_no_mortal(env, stack, "");

    if (env->length(env, stack, string) != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    const char* string_chars = env->get_chars(env, stack, string);
    if (strcmp(string_chars, "") != 0) {
      stack[0].ival = 0;
      // Assign and destroy
      void* referent = NULL;
      env->assign_object(env, stack, &referent, string);
      env->assign_object(env, stack, &referent, NULL);
      return 0;
    }
    
    // Assign and destroy
    void* referent = NULL;
    env->assign_object(env, stack, &referent, string);
    env->assign_object(env, stack, &referent, NULL);
  }

  stack[0].ival = 1;

  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // Basic
  {
    void* string = env->new_string_nolen(env, stack, "abc");

    const char* string_basic_type_name = env->get_object_basic_type_name(env, stack, string);
    int32_t string_type_dimension = env->get_object_type_dimension(env, stack, string);
    if (!(strcmp(string_basic_type_name, "string") == 0 && string_type_dimension == 0)) {
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

int32_t SPVM__TestCase__NativeAPI__new_memory_apis(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    int32_t memory_blocks_count_start = env->get_memory_blocks_count(env, stack);
    
    void* memory_block = env->new_memory_block(env, stack, sizeof(SPVM_ENV));
    
    if (!(env->get_memory_blocks_count(env, stack) == memory_blocks_count_start + 1)) {
      stack[0].ival = 0;
      return 0;
    }
    
    env->free_memory_block(env, stack, memory_block);
    
    if (!(env->get_memory_blocks_count(env, stack) == memory_blocks_count_start)) {
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
    
    int32_t memory_blocks_count_start = env->get_memory_blocks_count(env, stack);
    
    void* memory_block_new_stack = env->new_memory_block(env, new_stack, 8);
    
    if (!(env->get_memory_blocks_count(env, new_stack) == memory_blocks_count_start + 1)) {
      stack[0].ival = 0;
      return 0;
    }
    
    env->free_memory_block(env, new_stack, memory_block_new_stack);
    
    if (!(env->get_memory_blocks_count(env, stack) == memory_blocks_count_start)) {
      stack[0].ival = 0;
      return 0;
    }
    
    env->free_stack(env, new_stack);
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  {
    int32_t int_basic_type_id = env->get_basic_type_id(env, stack, "int");
    
    if (!(int_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT)) {
      stack[0].ival = 0;
      return 0;
    }
  }

  {
    int32_t not_found_basic_type_id = env->get_basic_type_id(env, stack, "NotFoundBasicType");
    
    if (!(not_found_basic_type_id < 0)) {
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

int32_t SPVM__TestCase__NativeAPI__strerror_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t errno_value = -1;
  
  void* strerror_string_value = env->strerror_string(env, stack, errno_value, 0);
  
  spvm_warn("[Test Output]strerr_string:%s", env->get_chars(env, stack, strerror_string_value));
  
  stack[0].ival = 1;
  
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

int32_t SPVM__TestCase__NativeAPI__new_object_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_object_array = env->new_object_array_no_mortal(env, stack, env->get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING), 2);
  
  if (!(env->is_type(env, stack, obj_object_array, env->get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING), 1))) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->api->internal->get_ref_count(env, stack, obj_object_array) == 0)) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->length(env, stack, obj_object_array) == 2)) {
    stack[0].ival = 0;
    return 0;
  }
  
  // Assign and destroy
  void* referent = NULL;
  env->assign_object(env, stack, &referent, obj_object_array);
  env->assign_object(env, stack, &referent, NULL);
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__new_object_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_object_array = env->new_object_array(env, stack, env->get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING), 2);
  
  if (!(env->is_type(env, stack, obj_object_array, env->get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING), 1))) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->api->internal->get_ref_count(env, stack, obj_object_array) == 1)) {
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
  
  if (!(env->is_type(env, stack, obj_string_array, env->get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING), 1))) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(env->api->internal->get_ref_count(env, stack, obj_string_array) == 1)) {
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


int32_t SPVM__TestCase__NativeAPI__args_width_0(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->args_width(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__args_width_1(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->args_width(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__args_width_2(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->args_width(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__args_width_4(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = env->args_width(env, stack);
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__default_all_types_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t args_width = env->args_width(env, stack);
  
  int8_t value_byte = stack[0].bval;
  int16_t value_short = stack[1].sval;
  int32_t value_int = stack[2].ival;
  int64_t value_long = stack[3].lval;
  float value_float = stack[4].fval;
  double value_double = stack[5].dval;
  void* value_object = stack[6].oval;
  
  if (args_width >= 1) {
    if (!(value_byte == 1)) {
      stack[0].ival = 0;
      spvm_warn("%d", value_byte);
      return 0;
    }
  }
  else {
    if (!(value_byte == -128)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  
  if (args_width >= 2) {
    if (!(value_short == 2)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  else {
    if (!(value_short == -32768)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  
  if (args_width >= 3) {
    if (!(value_int == 3)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  else {
    if (!(value_int == -2147483648)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  
  if (args_width >= 4) {
    if (!(value_long == 4)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  else {
    if (!(value_long == -9223372036854775808LU)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  
  if (args_width >= 5) {
    if (!(value_float == 5.5f)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  else {
    if (!(value_float == 1.5f)) {
      
      spvm_warn("%.20f %.20f", value_float, 1.5f);
      
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  
  if (args_width >= 6) {
    if (!(value_double == 6.5)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  else {
    if (!(value_double == -2147483648.5)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  
  if (args_width >= 7) {
    if (!(value_object != NULL)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  else {
    if (!(value_object == NULL)) {
      stack[0].ival = 0;
      spvm_warn("");
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
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

int32_t SPVM__TestCase__NativeAPI__check_stdio_binary_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  FILE* spvm_stdin = env->api->runtime->get_spvm_stdin(env->runtime);
  
  FILE* spvm_stdout = env->api->runtime->get_spvm_stdout(env->runtime);
  
  FILE* spvm_stderr = env->api->runtime->get_spvm_stderr(env->runtime);
  
#if defined(_WIN32)  
  int32_t stdin_old_mode = setmode(fileno(spvm_stdin), _O_BINARY);
  
  if (!(stdin_old_mode == _O_BINARY)) {
    stack[0].ival = 0;
    return 0;
  }
  
  int32_t stdout_old_mode = setmode(fileno(spvm_stdout), _O_BINARY);
  if (!(stdout_old_mode == _O_BINARY)) {
    stack[0].ival = 0;
    return 0;
  }
  
  int32_t stderr_old_mode = setmode(fileno(spvm_stderr), _O_BINARY);
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
    void* allocator = env->api->allocator->new_instance();
    
    // New string buffer
    void* string_buffer = env->api->string_buffer->new_instance(allocator, 0);

    void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::NativeAPI");
    
    void* method = env->api->basic_type->get_method_by_name(env->runtime, basic_type, "get_class_var_byte_by_name");
    
    env->api->runtime->build_precompile_method_source(env->runtime, string_buffer, method);
    
    const char* string_buffer_value = env->api->string_buffer->get_string(string_buffer);
    int32_t string_buffer_length = env->api->string_buffer->get_length(string_buffer);
    
    if (!strstr(string_buffer_value, "TestCase::NativeAPI")) {
      success = 0;
    }

    if (!strstr(string_buffer_value, "get_class_var_byte_by_name")) {
      success = 0;
    }
    
    // Free string buffer
    env->api->string_buffer->free_instance(string_buffer);

    // Free allocator
    env->api->allocator->free_instance(allocator);
  }
  
  stack[0].ival = success;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_compile_type_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = 1;
  
  {
    const char* basic_type_name = "int";
    int32_t type_dimension = 0;
    int32_t type_flag = 0;
    void* obj_compile_type_name = env->get_compile_type_name(env, stack, basic_type_name, type_dimension, type_flag);
    const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
    if (!(strcmp(compile_type_name, "int") == 0)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    const char* basic_type_name = "int";
    int32_t type_dimension = 2;
    int32_t type_flag = 0;
    void* obj_compile_type_name = env->get_compile_type_name(env, stack, basic_type_name, type_dimension, type_flag);
    const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
    if (!(strcmp(compile_type_name, "int[][]") == 0)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    const char* basic_type_name = "int";
    int32_t type_dimension = 0;
    int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_REF;
    void* obj_compile_type_name = env->get_compile_type_name(env, stack, basic_type_name, type_dimension, type_flag);
    const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
    if (!(strcmp(compile_type_name, "int*") == 0)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    const char* basic_type_name = "string";
    int32_t type_dimension = 0;
    int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_MUTABLE;
    void* obj_compile_type_name = env->get_compile_type_name(env, stack, basic_type_name, type_dimension, type_flag);
    const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
    if (!(strcmp(compile_type_name, "mutable string") == 0)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__runtime_get_method_is_enum(SPVM_ENV* env, SPVM_VALUE* stack) {

  stack[0].ival = 1;
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::NativeAPI");
  void* method = env->api->basic_type->get_method_by_name(env->runtime, basic_type, "VALUE0");
  assert(method);
  
  int32_t is_enum = env->api->method->is_enum(env->runtime, method);
  if (!is_enum) {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__method_native_api(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // is_precompile_fallback, set_is_precompile_fallback
  {
    void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, "TestCase::NativeAPI");
    void* method = env->api->basic_type->get_method_by_name(env->runtime, basic_type, "precompile_sum");
    assert(method);
    
    if (!(env->api->method->is_precompile_fallback(env->runtime, method) == 0)) {
      stack[0].ival = 0;
      return 0;
    }
    
    env->api->method->set_is_precompile_fallback(env->runtime, method, 1);
    
    if (!(env->api->method->is_precompile_fallback(env->runtime, method) == 1)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_string_field_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_self = stack[0].oval;
  
  int32_t error_id = 0;
  
  void* sv_text = env->get_field_object_by_name(env, stack, sv_self, "text", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
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

int32_t SPVM__TestCase__NativeAPI__floating_point_constant_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  float float_value1 = stack[0].fval;
  double double_value1 = stack[1].dval;

  if (!(float_value1 == strtof("1.02", NULL))) {
    spvm_warn("Got:%.20f,Expected:%.20f line %d", float_value1, strtof("1.02", NULL), __LINE__);
    stack[0].ival = 0;
    return 0;
  }
  
  if (!(float_value1 == 1.02f)) {
    spvm_warn("Warning:SPVM floating point literal is differenct from C floatin point literal. Got:%.20f,Expected:%.20f line %d", float_value1, 1.02f, __LINE__);
  }
  
  if (!(double_value1 == strtod("1.5e+300", NULL))) {
    spvm_warn("Got:%.20f,Expected:%.20f line %d", double_value1, strtod("1.5e+300", NULL), __LINE__);
    stack[0].ival = 0;
    return 0;
  }
  
  
  if (!(double_value1 == 1.5e+300)) {
    spvm_warn("Warning:SPVM floating point literal is differenct from C floatin point literal. Got:%.20f,Expected:%.20f line %d", double_value1, 1.5e+300, __LINE__);
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__get_object_basic_type_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    void* string = env->new_string_nolen(env, stack, "abc");
    
    const char* string_basic_type_name = env->get_object_basic_type_name(env, stack, string);
    if (!(strcmp(string_basic_type_name, "string") == 0)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__save_stdout_windows_binary_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
#if defined(_WIN32)
  int32_t stdout_mode_current = setmode(fileno(stdout), _O_BINARY);
  if (!(stdout_mode_current == _O_BINARY)) {
    return env->die(env, stack, "stdout mode must be _O_BINARY.", NULL, NULL, 0);
  }
  
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$STDOUT_WINDOWS_BINARY_MODE", stdout_mode_current, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
#endif
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__save_stderr_windows_binary_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
#if defined(_WIN32)
  int32_t stderr_mode_current = setmode(fileno(stderr), _O_BINARY);
  if (!(stderr_mode_current == _O_BINARY)) {
    return env->die(env, stack, "stderr mode must be _O_BINARY.", NULL, NULL, 0);
  }
  
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$STDERR_WINDOWS_BINARY_MODE", stderr_mode_current, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
#endif
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__save_stdin_windows_binary_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
#if defined(_WIN32)
  int32_t stdin_mode_current = setmode(fileno(stdin), _O_BINARY);
  if (!(stdin_mode_current == _O_BINARY)) {
    return env->die(env, stack, "stdin mode must be _O_BINARY.", NULL, NULL, 0);
  }
  
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$STDIN_WINDOWS_BINARY_MODE", stdin_mode_current, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
#endif
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__freopen_stdout(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", NULL, NULL, 0);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  FILE* fp = freopen(path, "w", stdout);
  
  if (!fp) {
    return env->die(env, stack, "freopen failed.", NULL, NULL, 0);
  }
  
#if defined(_WIN32)
  int32_t stdout_mode_current = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$STDOUT_WINDOWS_BINARY_MODE", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  setmode(fileno(fp), stdout_mode_current);
#endif
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__close_stdout(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t status = fclose(stdout);
  
  if (!(status == 0)) {
    return env->die(env, stack, "fclose failed.", NULL, NULL, 0);
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__freopen_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", NULL, NULL, 0);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  FILE* fp = freopen(path, "w", stderr);
  
  if (!fp) {
    return env->die(env, stack, "freopen failed.", NULL, NULL, 0);
  }
  
#if defined(_WIN32)
  int32_t stderr_mode_current = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$STDERR_WINDOWS_BINARY_MODE", &error_id, __func__, FILE_NAME, __LINE__);
  setmode(fileno(fp), stderr_mode_current);
#endif
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__close_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t status = fclose(stderr);
  
  if (!(status == 0)) {
    return env->die(env, stack, "fclose failed.", NULL, NULL, 0);
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__spvm_stdin(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  if (!(env->spvm_stdin(env, stack) == env->api->runtime->get_spvm_stdin(env->runtime))) {
    
    stack[0].ival = 0;
    
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__spvm_stdout(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  if (!(env->spvm_stdout(env, stack) == env->api->runtime->get_spvm_stdout(env->runtime))) {
    
    stack[0].ival = 0;
    
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__spvm_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  if (!(env->spvm_stderr(env, stack) == env->api->runtime->get_spvm_stderr(env->runtime))) {
    
    stack[0].ival = 0;
    
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__no_free(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* object = env->new_string_nolen(env, stack, "abc");
  
  // Check no effect SPVM_OBJECT_C_FLAG_IS_READ_ONLY
  env->make_read_only(env, stack, object);
  if (!env->is_read_only(env, stack, object)) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (env->no_free(env, stack, object)) {
    stack[0].ival = 0;
    return 0;
  }
  
  env->set_no_free(env, stack, object, 1);
  
  if (!env->no_free(env, stack, object)) {
    stack[0].ival = 0;
    return 0;
  }
  
  env->set_no_free(env, stack, object, 0);
  
  if (env->no_free(env, stack, object)) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!env->is_read_only(env, stack, object)) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__die(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    // ˆø”‚Ì‡˜‚ðC³: format, func, file, line, ...args
    int32_t error_id = env->die(env, stack, "Error %s.", __func__, __FILE__, __LINE__, "abc"); int32_t line = __LINE__;
    
    if (!(error_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS)) {
      stack[0].ival = 0;
      return 0;
    }
    
    void* obj_exception = env->build_exception_message(env, stack, 0);
    const char* exception = env->get_chars(env, stack, obj_exception);
    
    if (!strstr(exception, "abc")) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!strstr(exception, "SPVM__TestCase__NativeAPI__die")) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!strstr(exception, "NativeAPI.c")) {
      stack[0].ival = 0;
      return 0;
    }
    
    char tmp_line[255] = {0};
    sprintf(tmp_line, "%d", line);
    
    if (!strstr(exception, tmp_line)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  {
    char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
    sprintf(tmp_buffer, "%s", "abcd");
    // ˆø”‚Ì‡˜‚ðC³: tmp_buffer ‚ðÅŒã‚ÉˆÚ“®
    int32_t error_id = env->die(env, stack, "Error %s.", __func__, __FILE__, __LINE__, tmp_buffer); int32_t line = __LINE__;
    
    if (!(error_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS)) {
      stack[0].ival = 0;
      return 0;
    }
    
    void* obj_exception = env->build_exception_message(env, stack, 0);
    const char* exception = env->get_chars(env, stack, obj_exception);
    
    if (!strstr(exception, "abcd")) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!strstr(exception, "SPVM__TestCase__NativeAPI__die")) {
      stack[0].ival = 0;
      return 0;
    }
    
    if (!strstr(exception, "NativeAPI.c")) {
      stack[0].ival = 0;
      return 0;
    }
    
    char tmp_line[255] = {0};
    sprintf(tmp_line, "%d", line);
    
    if (!strstr(exception, tmp_line)) {
      stack[0].ival = 0;
      return 0;
    }
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__print_exception_to_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  {
    // ˆø”‚Ì‡˜‚ðC³: format, func, file, line, ...args
    int32_t error_id = env->die(env, stack, "[Test Output]Error %s.", __func__, __FILE__, __LINE__, "abc");
    
    env->print_exception_to_stderr(env, stack);
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__extra(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // sprintf("%s", NULL);
  {
    const char* string = NULL;
    fprintf(env->spvm_stderr(env, stack), "[Test Output][sprintf string NULL]%s\n", string);
  }
  
  stack[0].ival = 1;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI__field_exists(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* object = env->new_object_by_name(env, stack, "TestCase::Simple", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  {
    {
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->set_field_byte_by_name(env, stack, object, "byte_value", 2, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int8_t value = env->get_field_byte_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 2)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 1)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->delete_field_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int8_t value = env->get_field_byte_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
    }
    
    {
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->set_field_short_by_name(env, stack, object, "short_value", 2, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int8_t value = env->get_field_short_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 2)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 1)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->delete_field_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int8_t value = env->get_field_short_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
    }
    
    {
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->set_field_int_by_name(env, stack, object, "int_value", 2, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int8_t value = env->get_field_int_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 2)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 1)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->delete_field_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int8_t value = env->get_field_int_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
    }
    
    {
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->set_field_long_by_name(env, stack, object, "long_value", 2, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int8_t value = env->get_field_long_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 2)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 1)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->delete_field_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int8_t value = env->get_field_long_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
    }
    
    {
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->set_field_float_by_name(env, stack, object, "float_value", 2, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int8_t value = env->get_field_float_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 2)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 1)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->delete_field_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int8_t value = env->get_field_float_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
    }
    
    {
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->set_field_double_by_name(env, stack, object, "double_value", 2, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int8_t value = env->get_field_double_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 2)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 1)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->delete_field_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int8_t value = env->get_field_double_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
    }
    
    {
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "object_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      void* obj_minimal = env->new_object_by_name(env, stack, "TestCase::Minimal", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      env->set_field_object_by_name(env, stack, object, "object_value", obj_minimal, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        void* value = env->get_field_object_by_name(env, stack, object, "object_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == obj_minimal)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "object_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 1)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      env->delete_field_by_name(env, stack, object, "object_value", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      
      {
        int32_t exists = env->exists_field_by_name(env, stack, object, "object_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(exists == 0)) {
          stack[0].ival = 0;
          return 0;
        }
      }
      
      {
        void* value = env->get_field_object_by_name(env, stack, object, "object_value", &error_id, __func__, FILE_NAME, __LINE__);
        if (error_id) { return error_id; }
        
        if (!(value == NULL)) {
          stack[0].ival = 0;
          return 0;
        }
      }
    }
    
  }
  
  stack[0].ival = 1;
  
  return 0;
}

// static variables to store detected method information
static int32_t method_begin_call_count = 0;
static int32_t method_end_call_count = 0;
static void* last_begin_method = NULL;
static void* last_end_method = NULL;

// callback for method begin
static void test_method_begin_cb(SPVM_ENV* env, SPVM_VALUE* stack) {
  method_begin_call_count++;
  int32_t error_id = 0;
  // level 0 means the current method
  last_begin_method = env->get_current_method(env, stack, 0, &error_id);
}

// callback for method end
static void test_method_end_cb(SPVM_ENV* env, SPVM_VALUE* stack) {
  method_end_call_count++;
  int32_t error_id = 0;
  // level 0 means the current method
  last_end_method = env->get_current_method(env, stack, 0, &error_id);
}

int32_t SPVM__TestCase__NativeAPI__method_begin_and_end_cb(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;

  // 1. Setup
  method_begin_call_count = 0;
  method_end_call_count = 0;
  last_begin_method = NULL;
  last_end_method = NULL;
  
  // Directly set callbacks to the runtime fields
  env->api->runtime->method_begin_cb = test_method_begin_cb;
  env->api->runtime->method_end_cb = test_method_end_cb;

  // 2. Execution: Call Fn#INT_MAX using call_class_method_by_name
  env->call_class_method_by_name(env, stack, "Fn", "INT_MAX", 0, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

  // 3. Verification
  // Check if each callback was called exactly once
  if (method_begin_call_count != 1) {
    stack[0].ival = 0;
    goto CLEANUP;
  }
  if (method_end_call_count != 1) {
    stack[0].ival = 0;
    goto CLEANUP;
  }

  // Check if get_current_method successfully returned the method pointer
  if (last_begin_method == NULL) {
    stack[0].ival = 0;
    goto CLEANUP;
  }
  if (last_end_method == NULL) {
    stack[0].ival = 0;
    goto CLEANUP;
  }

  // Verify that the captured method pointers are consistent
  if (last_begin_method != last_end_method) {
    stack[0].ival = 0;
    goto CLEANUP;
  }

  // Verify the method absolute name
  const char* method_abs_name = env->api->method->get_abs_name(env->runtime, last_begin_method);
  if (strcmp(method_abs_name, "Fn#INT_MAX") != 0) {
    stack[0].ival = 0;
    goto CLEANUP;
  }

  // Verify the return value of Fn#INT_MAX is preserved and correct
  if (stack[0].ival != INT32_MAX) {
    stack[0].ival = 0;
    goto CLEANUP;
  }
  
  stack[0].ival = 1;

CLEANUP:
  // 4. Cleanup
  // Directly clear the runtime fields
  env->api->runtime->method_begin_cb = NULL;
  env->api->runtime->method_end_cb = NULL;
  
  return 0;
}
