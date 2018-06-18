
all:
	make
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra -DSPVM_DEBUG_DUMP -DSPVM_DEBUG_OBJECT_COUNT -std=c99 -O3 -o solo/spvm_main solo/spvm_main.c spvm_basic_type.o spvm_block.o spvm_call_sub.o spvm_compiler.o spvm_compiler_allocator.o spvm_constant.o spvm_core_func.o spvm_core_func_bind.o spvm_csource_builder.o spvm_descriptor.o spvm_dumper.o spvm_enumeration.o spvm_enumeration_value.o spvm_field.o spvm_field_access.o spvm_hash.o spvm_hash_func.o spvm_list.o spvm_my.o spvm_op.o spvm_op_checker.o spvm_opcode.o spvm_opcode_array.o spvm_opcode_builder.o spvm_our.o spvm_package.o spvm_package_var.o spvm_runtime.o spvm_runtime_allocator.o spvm_runtime_api.o spvm_string_buffer.o spvm_sub.o spvm_switch_info.o spvm_toke.o spvm_type.o spvm_use.o spvm_util_allocator.o spvm_var.o spvm_yacc.o spvm_yacc_util.o -lm

test:
	make
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra -DSPVM_DEBUG_DUMP -DSPVM_DEBUG_OBJECT_COUNT -std=c99 -O3 -o solo/t/spvm_t_list solo/t/spvm_t_list.c spvm_list.o spvm_util_allocator.o -lm
	solo/t/spvm_t_list
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra -DSPVM_DEBUG_DUMP -DSPVM_DEBUG_OBJECT_COUNT -std=c99 -O3 -o solo/t/spvm_t_hash solo/t/spvm_t_hash.c spvm_hash.o spvm_util_allocator.o spvm_hash_func.o -lm
	solo/t/spvm_t_hash

clean:
	rm -rf solo/spvm_main
