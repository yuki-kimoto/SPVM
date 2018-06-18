
all:


solo/%.o: %.c | solo solo/solo solo/t
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra $(DEFINE) -std=c99 -O -c -o $@ $<

# libspvm
libspvm_SRCS := spvm_basic_type.c spvm_block.c spvm_call_sub.c spvm_compiler.c spvm_compiler_allocator.c spvm_constant.c spvm_core_func.c spvm_core_func_bind.c spvm_csource_builder.c spvm_descriptor.c spvm_dumper.c spvm_enumeration.c spvm_enumeration_value.c spvm_field.c spvm_field_access.c spvm_hash.c spvm_hash_func.c spvm_list.c spvm_my.c spvm_op.c spvm_op_checker.c spvm_opcode.c spvm_opcode_array.c spvm_opcode_builder.c spvm_our.c spvm_package.c spvm_package_var.c spvm_runtime.c spvm_runtime_allocator.c spvm_runtime_api.c spvm_string_buffer.c spvm_sub.c spvm_switch_info.c spvm_toke.c spvm_type.c spvm_use.c spvm_util_allocator.c spvm_var.c spvm_yacc.c spvm_yacc_util.c
libspvm_OBJS := $(libspvm_SRCS:%.c=solo/%.o)
solo/spvm_toke.o: spvm_toke.c spvm_yacc.h
solo/spvm_yacc_util.o: spvm_yacc_util.c spvm_yacc.h
libspvm.a: $(libspvm_OBJS)
	$(AR) crs $@ $(libspvm_OBJS)
all: libspvm.a

# spvm
spvm_SRCS    := solo/spvm_main.c
spvm_OBJS    := $(spvm_SRCS:%.c=solo/%.o)
spvm: $(spvm_OBJS) libspvm.a
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra $(DEFINE) -std=c99 -O -o $@  -L . $(spvm_OBJS) -lspvm -lm
all: spvm


test:
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra $(DEFINE) -std=c99 -O -o solo/t/spvm_t_list solo/t/spvm_t_list.c spvm_list.o spvm_util_allocator.o -lm
	solo/t/spvm_t_list
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra $(DEFINE) -std=c99 -O -o solo/t/spvm_t_hash solo/t/spvm_t_hash.c spvm_hash.o spvm_util_allocator.o spvm_hash_func.o -lm
	solo/t/spvm_t_hash

clean:
	find solo -name *.o | xargs rm -rf
	rm -rf libspvm.a
