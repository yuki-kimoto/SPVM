
all:
	cc -DSPVM_DEBUG_DUMP -DSPVM_DEBUG_OBJECT_COUNT -I. -Ilib/SPVM/Build -fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -std=c99 -Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -lm  -O0 -g -o solo/spvm_main solo/spvm_main.c spvm_array_field_access.o spvm_basic_type.o spvm_block.o spvm_call_sub.o spvm_case_info.o spvm_compiler.o spvm_compiler_allocator.o spvm_constant.o spvm_core_func.o spvm_core_func_bind.o spvm_csource_builder.o spvm_descriptor.o spvm_dumper.o spvm_enumeration.o spvm_enumeration_value.o spvm_field.o spvm_field_access.o spvm_hash.o spvm_hash_func.o spvm_list.o spvm_my.o spvm_op.o spvm_op_checker.o spvm_opcode.o spvm_opcode_array.o spvm_opcode_builder.o spvm_package.o spvm_package_var.o spvm_package_var_access.o spvm_runtime.o spvm_runtime_allocator.o spvm_runtime_api.o spvm_string_buffer.o spvm_sub.o spvm_switch_info.o spvm_toke.o spvm_type.o spvm_use.o spvm_util_allocator.o spvm_var.o spvm_yacc.o spvm_yacc_util.o

test:
	cc -DSPVM_DEBUG_DUMP -DSPVM_DEBUG_OBJECT_COUNT -I. -Ilib/SPVM/Build -fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -std=c99 -Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -lm  -O0 -g -o solo/t/spvm_t_list solo/t/spvm_t_list.c spvm_list.o spvm_util_allocator.o
	solo/t/spvm_t_list
	cc -DSPVM_DEBUG_DUMP -DSPVM_DEBUG_OBJECT_COUNT -I. -Ilib/SPVM/Build -fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -std=c99 -Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -lm  -O0 -g -o solo/t/spvm_t_hash solo/t/spvm_t_hash.c spvm_hash.o spvm_util_allocator.o spvm_hash_func.o
	solo/t/spvm_t_hash

clean:
	rm -rf solo/spvm_main
