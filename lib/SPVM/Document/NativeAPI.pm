=head1 Name

SPVM::Document::NativeAPI - SPVM Native APIs

=head1 Description

The SPVM native APIs are public APIs that are used in native language sources such as C<C/C++>.

The native APIs are writen in C<C language>, but the languages that have compatibility of C<C language> such as <C++>, C<CUDA/nvcc> can call the native APIs.

The native APIs is used when L<native methods|SPVM::Document::NativeModule> are implemented.

=head1 Native APIs

Native APIs have its IDs. These IDs are permanently same for the binary compatibility after the future release C<v1.0>.

  0 class_vars_heap
  1 object_header_size
  2 object_weaken_backref_head_offset
  3 object_ref_count_offset
  4 object_basic_type_id_offset
  5 object_type_dimension_offset
  6 object_type_category_offset
  7 object_flag_offset
  8 object_length_offset
  9 api
  10 allocator
  11 new_env_raw
  12 free_env_raw
  13 isa
  14 elem_isa
  15 runtime
  16 reserved16
  17 reserved17
  18 reserved18
  19 reserved19
  20 get_basic_type_id
  21 get_field_id
  22 get_field_offset
  23 get_class_var_id
  24 get_class_method_id
  25 get_instance_method_id
  26 new_object_raw
  27 new_object
  28 new_byte_array_raw
  29 new_byte_array
  30 new_short_array_raw
  31 new_short_array
  32 new_int_array_raw
  33 new_int_array
  34 new_long_array_raw
  35 new_long_array
  36 new_float_array_raw
  37 new_float_array
  38 new_double_array_raw
  39 new_double_array
  40 new_object_array_raw
  41 new_object_array
  42 new_muldim_array_raw
  43 new_muldim_array
  44 new_mulnum_array_raw
  45 new_mulnum_array
  46 new_string_nolen_raw
  47 new_string_nolen
  48 new_string_raw
  49 new_string
  50 new_pointer_raw
  51 new_pointer
  52 concat_raw
  53 concat
  54 new_stack_trace_raw
  55 new_stack_trace
  56 length
  57 get_elems_byte
  58 get_elems_short
  59 get_elems_int
  60 get_elems_long
  61 get_elems_float
  62 get_elems_double
  63 get_elem_object
  64 set_elem_object
  65 get_field_byte
  66 get_field_short
  67 get_field_int
  68 get_field_long
  69 get_field_float
  70 get_field_double
  71 get_field_object
  72 set_field_byte
  73 set_field_short
  74 set_field_int
  75 set_field_long
  76 set_field_float
  77 set_field_double
  78 set_field_object
  79 get_class_var_byte
  80 get_class_var_short
  81 get_class_var_int
  82 get_class_var_long
  83 get_class_var_float
  84 get_class_var_double
  85 get_class_var_object
  86 set_class_var_byte
  87 set_class_var_short
  88 set_class_var_int
  89 set_class_var_long
  90 set_class_var_float
  91 set_class_var_double
  92 set_class_var_object
  93 get_pointer
  94 set_pointer
  95 call_method
  96 get_exception
  97 set_exception
  98 get_ref_count
  99 inc_ref_count
  100 dec_ref_count
  101 enter_scope
  102 push_mortal
  103 leave_scope
  104 remove_mortal
  105 is_type
  106 is_object_array
  107 get_object_basic_type_id
  108 get_object_type_dimension
  109 weaken
  110 isweak
  111 unweaken
  112 alloc_memory_block_zero
  113 free_memory_block
  114 get_memory_blocks_count
  115 get_type_name_raw
  116 get_type_name
  117 new_env
  118 free_env
  119 memory_blocks_count
  120 get_chars
  121 die
  122 new_object_by_name
  123 new_pointer_by_name
  124 set_field_byte_by_name
  125 set_field_short_by_name
  126 set_field_int_by_name
  127 set_field_long_by_name
  128 set_field_float_by_name
  129 set_field_double_by_name
  130 set_field_object_by_name
  131 get_field_byte_by_name
  132 get_field_short_by_name
  133 get_field_int_by_name
  134 get_field_long_by_name
  135 get_field_float_by_name
  136 get_field_double_by_name
  137 get_field_object_by_name
  138 set_class_var_byte_by_name
  139 set_class_var_short_by_name
  140 set_class_var_int_by_name
  141 set_class_var_long_by_name
  142 set_class_var_float_by_name
  143 set_class_var_double_by_name
  144 set_class_var_object_by_name
  145 get_class_var_byte_by_name
  146 get_class_var_short_by_name
  147 get_class_var_int_by_name
  148 get_class_var_long_by_name
  149 get_class_var_float_by_name
  150 get_class_var_double_by_name
  151 get_class_var_object_by_name
  152 call_class_method_by_name
  153 call_instance_method_by_name
  154 get_field_string_chars_by_name
  155 free_env_prepared
  156 dump_raw
  157 dump
  158 reserved158
  159 reserved159
  160 get_instance_method_id_static
  161 get_bool_object_value
  162 cleanup_global_vars
  163 make_read_only
  164 is_read_only
  165 is_array
  166 is_string
  167 is_numeric_array
  168 is_mulnum_array
  169 get_elem_size
  170 new_array_proto_raw
  171 new_array_proto
  172 copy_raw
  173 copy
  174 shorten
  175 has_interface
  176 reserved176
  177 reserved177
  178 reserved178
  179 print
  180 print_stderr
  181 init_env,
  182 call_init_blocks
  183 get_class_id
  184 new_stack
  185 free_stack
  186 reserved186
  187 new_memory_env
  188 free_memory_env
  189 get_memory_blocks_count_env
  190 new_memory_stack
  191 free_memory_stack
  192 get_memory_blocks_count_stack
  193 set_command_info_program_name
  194 set_command_info_argv
  195 get_class_id_by_name
  196 strerror
  197 new_string_array
  198 get_args_stack_length
  199 set_args_stack_length
  200 dumpc
  201 new_pointer_object_raw
  202 new_pointer_object
  203 new_pointer_object_by_name
  204 reserved204
  205 reserved205
  206 reserved206
  207 reserved207
  208 is_class
  209 is_pointer_class
  210 reserved201
  211 reserved211
  212 reserved212
  213 reserved213
  214 reserved214
  215 reserved215
  216 reserved216
  217 reserved217
  218 reserved218
  219 reserved219
  220 reserved220
  221 reserved221
  222 reserved222
  223 reserved223
  224 reserved224
  225 strerror_string
  226 get_basic_type_id_by_name
  227 get_field_id_static
  228 get_args_stack_length
  229 call_instance_method_static_by_name
  230 get_method_id
  231 strerror_nolen
  232 strerror_string_nolen
  233 get_compile_type_name_raw
  234 get_compile_type_name

=head2 class_vars_heap

  void* class_vars_heap;

The pointer to the storage area of the class variables. This is used internally.

=head2 object_header_size

  void* object_header_size;

The byte size of the object's header. This is used internally.

=head2 object_weaken_backref_head_offset

  void* object_weaken_backref_head_offset;

The offset to a pointer to the back reference of the weak reference in the object structure. This is used internally.

=head2 object_ref_count_offset

  void* object_ref_count_offset;

The reference count offset in the object structure. This is used internally.

=head2 object_basic_type_id_offset

  void* object_basic_type_id_offset;

The offset of basic type ID in object structure. This is used internally.

=head2 object_type_dimension_offset

  void* object_type_dimension_offset;

The offset of type dimension in object structure. This is used internally.

=head2 object_type_category_offset

  void* object_type_category_offset;

The offset of runtime type category in object structure. This is used internally.

This value is always C<NULL>, because SPVM 0.9511+, this value is any more used.

=head2 object_flag_offset

  void* object_flag_offset;

The offset of flag in object structure. This is used internally.

=head2 object_length_offset

  void* object_length_offset;

The length offset in the object structure. This is used internally.

=head2 api

  void* api;

The environment of APIs such as L<compiler native APIs|SPVM::Document::NativeAPI::Compiler>, L<precompile native APIs|SPVM::Document::NativeAPI::Precompile>, L<runtime native APIs|SPVM::Document::NativeAPI::Runtime>, L<string buffer native APIs|SPVM::Document::NativeAPI::StringBuffer>, L<allocator native APIs|SPVM::Document::NativeAPI::Allocator>.

Examples:
  
  // Compiler native APIs
  void* compiler_api = env->api->compiler;
  
  // Precompile native APIs
  void* precompile_api = env->api->precompile;
  
  // Runtime native APIs
  void* runtime_api = env->api->runtime;
  
  // String buffer native APIs
  void* string_buffer_api = env->api->string_buffer;
  
  // Allocator native APIs
  void* allocator_api = env->api->allocator;

=head2 allocator

  void* allocator;

The memory allocator for this environment.

=head2 new_env_raw

  SPVM_ENV* (*new_env_raw)();

Creates a new raw envriment.

=head2 free_env_raw

  void (*free_env_raw)(SPVM_ENV* env);

Frees the raw environemt that is created by L</"new_env_raw">.

=head2 isa

  int32_t (*isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t cast_basic_type_id, int32_t cast_type_dimension);

Performs C<isa> operation.

=head2 elem_isa

  int32_t (*elem_isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, void* element);

Checks the runtime type assignability of an array element.

=head2 runtime

  void* runtime;

A pointer to the runtime information. This is used internally.

=head2 reserved16

  void* reserved16;

Reserved.

=head2 reserved17

  void* reserved17;

Reserved.

=head2 reserved18

  void* reserved18;

Reserved.

=head2 reserved19

  void* reserved19;

Reserved.

=head2 get_basic_type_id

  int32_t (*get_basic_type_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);

Gets the ID of the base type given the name of the base type. If it does not exist, a value less than 0 is returned.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, "Int");

=head2 get_field_id

  int32_t (*get_field_id)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name);

Gets the ID of the field given an object and field name. If the field does not exist, a value less than 0 is returned.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");

=head2 get_field_offset

  int32_t (*get_field_offset)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t field_id);

Gets the offset of the field given the field ID. The field ID must be a valid field ID obtained with the field_id function.

=head2 get_class_var_id

  int32_t (*get_class_var_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name);

Gets the class variable ID given the class name, class variable name. If the class variable does not exist, a value less than 0 is returned.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");

=head2 get_class_method_id

  int32_t (*get_class_method_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name);

Gets a class method ID by the class name, the method name. If the class method does not exists, a negative value is returned.

This ID is used by L<"call_method">.

Examples:

  int32_t method_id = env->get_class_method_id(env, "Foo", "get");

=head2 get_instance_method_id

  int32_t (*get_instance_method_id)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* method_name);

Gets a instance method ID by the object, the method name. If the instance method does not exist, a negative value is returned.

This ID is used by L<"call_method">.

Examples:

  int32_t method_id = env->get_instance_method_id(env, object, "get");

=head2 new_object_raw

  void* (*new_object_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id);

Creates a new object with a basic type ID. The basic type ID must be the correct base type ID return by C<get_basic_type_id> function.

=head2 new_object

  void* (*new_object)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id);

The same as C<new_object_raw>, and add the created object to the mortal stack of the environment. Use this function in normal use instead of C<new_object_raw>.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, "Int");
  void* object = env->new_object(env, stack, basic_type_id);

=head2 new_byte_array_raw

  void* (*new_byte_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

Creates a new byte[] type array by specifying the length.

=head2 new_byte_array

  void* (*new_byte_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

The same as C<new_byte_array_raw>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_byte_array_raw>.

Examples:

  void* byte_array = env->new_byte_array(env, stack, 100);

=head2 new_short_array_raw

  void* (*new_short_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

Creates a new short[] type array by specifying the length.

=head2 new_short_array

  void* (*new_short_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

The same as C<new_short_array_raw>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_short_array_raw>.

Examples:

  void* short_array = env->new_short_array(env, stack, 100);

=head2 new_int_array_raw

  void* (*new_int_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

Creates a new int[] type array by specifying the length.

=head2 new_int_array

  void* (*new_int_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

The same as C<new_int_array_raw>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_int_array_raw>.

Examples:

  void* int_array = env->new_int_array(env, stack, 100);

=head2 new_long_array_raw

  void* (*new_long_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

Creates a new long[] type array by specifying the length.

=head2 new_long_array

  void* (*new_long_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

The same as C<new_long_array_raw>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_long_array_raw>.

Examples:

  void* long_array = env->new_long_array(env, stack, 100);

=head2 new_float_array_raw

  void* (*new_float_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

Creates a new float[] type array by specifying the length.

=head2 new_float_array

  void* (*new_float_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

The same as C<new_float_array_raw>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_float_array_raw>.

Examples:

  void* float_array = env->new_float_array(env, stack, 100);

=head2 new_double_array_raw

  void* (*new_double_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

Creates a new double[] type array by specifying the length.

=head2 new_double_array

  void* (*new_double_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

The same as C<new_double_array_raw>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_double_array_raw>.

Examples:

  void* double_array = env->new_double_array(env, stack, 100);

=head2 new_object_array_raw

  void* (*new_object_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);

Creates a new object type array by specifying the basic type ID and the array length. The basic type ID must be the correct basic type ID got by C<get_basic_type_id> function.

=head2 new_object_array

  void* (*new_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);

The same as C<new_object_array_raw>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_object_array_raw>.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, "Int");
  void* object_array = env->new_object_array(env, stack, basic_type_id, 100);

=head2 new_muldim_array_raw

  void* (*new_muldim_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t element_dimension, int32_t length);

Creates a new multi dimension array by specifying the basic type ID, the type dimension of the element, and the array length. The basic type ID must be the correct basic type ID got bu C<get_basic_type_id> function. the type dimension of the element must be less than or equals to 255.

=head2 new_muldim_array

  void* (*new_muldim_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t element_dimension, int32_t length);

The same as C<new_muldim_array_raw>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_muldim_array_raw>.

Examples:

  // new Int[][][100]
  int32_t basic_type_id = env->get_basic_type_id(env, "Int");
  void* multi_array = env->new_muldim_array(env, stack, basic_type_id, 2, 100);

=head2 new_mulnum_array_raw

  void* (*new_mulnum_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);

Creates a new multi-numeric array by specifying the basic type ID and the array length. The basic type ID must be the correct basic type ID got by C<basic_type_id> function.

=head2 new_mulnum_array

  void* (*new_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);

The same as C<new_mulnum_array_raw>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_mulnum_array_raw>.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, "Complex_2d");
  void* value_array = env->new_mulnum_array(env, stack, basic_type_id, 100);

=head2 new_string_nolen_raw

  void* (*new_string_nolen_raw)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);

Creates a new string object by specifying C language char* type value. this value must end with "\0".

=head2 new_string_nolen

  void* (*new_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);

The same as C<new_string_nolen_raw>, and push the created object to the mortal stack. Use this function in normal use instead of C<new_string_nolen_raw>.

Examples:

  void* str_obj = env->new_string_nolen(env, stack, "Hello World");

=head2 new_string_raw

  void* (*new_string_raw)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);

Creates a new string object with the bytes and the length.

If the length of bytes is lower than the specified length or the bytes is NULL, The part that longer than the length of bytes will be filled with C<\0>. 

=head2 new_string

  void* (*new_string)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);

The same as C<new_string_raw>, and push the created object to the mortal stack. Usually use this function instead of C<new_string_raw>.

Examples:

  void* str_obj = env->new_string(env, stack, "Hello \0World", 11);

=head2 new_pointer_raw

  void* (*new_pointer_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer);

Creates a pointer object by specifying a basic type ID and a C language pointer. The basic type ID must be the correct basic type ID got by C<get_basic_type_id> function.

The same as the L</"new_pointer_raw">, but this is deprecagted and will be removed.

=head2 new_pointer

  void* (*new_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer);

The same as the L</"new_pointer_object">, but this is deprecagted and will be removed.

=head2 concat_raw

  void* (*concat_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);

Concats two strings.

=head2 concat

  void* (*concat)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);

The same as C<concat_raw>, and push the created object to the mortal stack. Use this function in normal use instead of C<concat_raw>.

=head2 new_stack_trace_raw

  void* (*new_stack_trace_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, int32_t method_id, int32_t line);

Creates a string object that represents a stack trace by adding the file and line the method is called to the end of the exception message.

=head2 new_stack_trace

  void* (*new_stack_trace)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, int32_t method_id, int32_t line);

The same as L</"new_stack_trace_raw">, and push the created object to the mortal stack.

=head2 length

  int32_t (*length)(SPVM_ENV*, void* array);

If you specify an array, the length of the array is returned.

Examples:

  int32_t length = env->length(env, stack, array);

=head2 get_elems_byte

  int8_t* (*get_elems_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);

If you specify a byte[] type array, the pointer at the beginning of the internally stored C language int8_t[] type array is returned.  

Examples:

  int8_t* values = env->get_elems_byte(env, stack, array);
  values[3] = 5;

=head2 get_elems_short

  int16_t* (*get_elems_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);

If a short[] type array is specified, the pointer at the beginning of the internally stored C language int16_t[] type array is returned.

Examples:

  int16_t* values = env->get_elems_short(env, stack, array);
  values[3] = 5;

=head2 get_elems_int

  int32_t* (*get_elems_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);

When an int[] type array is specified, the pointer at the beginning of the internally stored C language int32_t[] type array is returned.

Examples:

  int32_t* values = env->get_elems_int(env, stack, array);
  values[3] = 5;

=head2 get_elems_long

  int64_t* (*get_elems_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);

When a long[] type array is specified, the pointer at the beginning of the internally stored C language int64_t[] type array is returned.

Examples:

  int64_t* values = env->get_elems_long(env, stack, array);
  values[3] = 5;

=head2 get_elems_float

  float* (*get_elems_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);

When a float[] type array is specified, the pointer at the beginning of the C language float[] type array internally held is returned.

Examples:

  float* values = env->get_elems_float(env, stack, array);
  values[3] = 1.5f;

=head2 get_elems_double

  double* (*get_elems_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);

If a double[] type array is specified, the pointer at the beginning of the internally stored C double[] type array is returned.

Examples:

  double* values = env->get_elems_double(env, stack, array);
  values[3] = 1.5;

=head2 get_elem_object

  void* (*get_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index);

Gets an object of an element given an array of object types and a methodscript. If the element is a weak reference, the weak reference is removed.

Examples:

  void* object = env->get_elem_object(env, stack, array, 3);

=head2 set_elem_object

  void (*set_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* value);

If you specify an array of object type and methodscript and element objects, the element object is assigned to the corresponding methodscript position. If the element's object has a weak reference, the weak reference is removed. The reference count of the originally assigned object is decremented by 1.

Examples:

  env->get_elem_object(env, stack, array, 3, object);

=head2 get_field_byte

  int8_t (*get_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);

If an object and field ID are specified, the byte field value will be returned as a C language int8_t type value. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  int8_t field_value = env->get_field_byte(env, stack, object, field_id);

=head2 get_field_short

  int16_t (*get_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);

If you specify the object and field ID, the value of the short type field will be returned as the int16_t type value of C language. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  int16_t field_value = env->get_field_short(env, stack, object, field_id);

=head2 get_field_int

  int32_t (*get_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);

If an object and a field ID are specified, the value of the int type field will be returned as a C language int32_t type value. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  int32_t field_value = env->get_field_int(env, stack, object, field_id);

=head2 get_field_long

  int64_t (*get_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);

If you specify the object and field ID, the value of the long type field will be returned as the value of int64_t type of C language. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  int64_t field_value = env->get_field_long(env, stack, object, field_id);

=head2 get_field_float

  float (*get_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);

If you specify the object and field ID, the value of the float type field will be returned as a C language float type value. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  float field_value = env->get_field_float(env, stack, object, field_id);

=head2 get_field_double

  double (*get_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);

If you specify the object and field ID, the value of the double type field will be returned as a double type value in C language. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  double field_value = env->get_field_double(env, stack, object, field_id);

=head2 get_field_object

  void* (*get_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);

If you specify the object and field ID, the value of the object type field is returned as a void* type value in C language. The field ID must be a valid field ID obtained with the field_id function. If the field is a weak reference, it will be removed.

  int32_t field_id = env->get_field_id(env, object, "x");
  void* field_value = env->get_field_object(env, stack, object, field_id);

=head2 set_field_byte

  void (*set_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int8_t value);

If you specify the object and field ID and the value of the field, the value is set to the byte type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  int8_t field_value = 5;
  env->set_field_byte(env, stack, object, field_id, field_value);

=head2 set_field_short

  void (*set_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int16_t value);

If you specify the object and field ID and the value of the field, the value is set to the short type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  int16_t field_value = 5;
  env->set_field_short(env, stack, object, field_id, field_value);

=head2 set_field_int

  void (*set_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int32_t value);

If you specify the object and field ID and the value of the field, the value is set to the int type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  int32_t field_value = 5;
  env->set_field_int(env, stack, object, field_id, field_value);

=head2 set_field_long

  void (*set_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int64_t value);

If you specify the object and field ID and the value of the field, the value is set to the long type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  int64_t field_value = 5;
  env->set_field_long(env, stack, object, field_id, field_value);

=head2 set_field_float

  void (*set_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, float value);

If you specify the object and field ID and the value of the field, the value is set to the float type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  float field_value = 1.5f;
  env->set_field_float(env, stack, object, field_id, field_value);

=head2 set_field_double

  void (*set_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, double value);

If you specify the object and field ID and the value of the field, the value is set to the double type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  double field_value = 1.55;
  env->set_field_double(env, stack, object, field_id, field_value);

=head2 set_field_object

  void (*set_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, void* value);

The object and field Specifies the ID and the value of the field and set the value to the object type field. The field ID must be a valid field ID obtained with the field_id function. After setting, the reference count is incremented by 1. The original value has the reference count decremented by 1.

Examples:

  int32_t field_id = env->get_field_id(env, object, "x");
  int32_t basic_type_id = env->get_basic_type_id(env, "Int");
  void* object = env->new_object(env, stack, basic_type_id);
  env->set_field_object(env, stack, object, field_id, object);

=head2 get_class_var_byte

  int8_t (*get_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);

If an object and a class variable ID are specified, the value of the byte type class variable is returned as a C language int8_t type value. The class variable ID must be a valid class variable ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  int8_t class_var_value = env->get_class_var_byte(env, stack, object, class_var_id);

=head2 get_class_var_short

  int16_t (*get_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);

If an object and a class variable ID are specified, the value of the short type class variable will be returned as a C language int16_t type value. The class variable ID must be a valid class variable ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  int16_t class_var_value = env->get_class_var_short(env, stack, object, class_var_id);

=head2 get_class_var_int

  int32_t (*get_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);

If an object and a class variable ID are specified, the value of the int type class variable will be returned as a C language int32_t type value. The class variable ID must be a valid class variable ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  int32_t class_var_value = env->get_class_var_int(env, stack, object, class_var_id);

=head2 get_class_var_long

  int64_t (*get_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);

If an object and a class variable ID are specified, the value of the long type class variable will be returned as a C language int64_t type value. The class variable ID must be a valid class variable ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  int64_t class_var_value = env->get_class_var_long(env, stack, object, class_var_id);

=head2 get_class_var_float

  float (*get_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);

If an object and a class variable ID are specified, the value of the float type class variable will be returned as a C language float type value. The class variable ID must be a valid class variable ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  float class_var_value = env->get_class_var_float(env, stack, object, class_var_id);

=head2 get_class_var_double

  double (*get_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);

If you specify an object and a class variable ID, the value of the double type class variable is returned as a C type double type value. The class variable ID must be a valid class variable ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  double class_var_value = env->get_class_var_double(env, stack, object, class_var_id);

=head2 get_class_var_object

  void* (*get_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);

When an object and a class variable ID are specified, the value of the object type class variable is returned as a C language void* type value. The class variable ID must be a valid class variable ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  void* class_var_value = env->get_class_var_byte(env, stack, object, class_var_id);

=head2 set_class_var_byte

  void (*set_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, int8_t value);

If you specify the object and field ID and the value of the field, the value is set to the byte type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  int8_t class_var_value = 5;
  env->set_class_var_byte(env, stack, class_var_id, class_var_value);

=head2 set_class_var_short

  void (*set_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, int16_t value);

If you specify the object and field ID and the value of the field, the value is set to the short type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  int16_t class_var_value = 5;
  env->set_class_var_short(env, stack, class_var_id, class_var_value);

=head2 set_class_var_int

  void (*set_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, int32_t value);

If you specify the object and field ID and the value of the field, the value is set to the int type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  int32_t class_var_value = 5;
  env->set_class_var_int(env, stack, class_var_id, class_var_value);

=head2 set_class_var_long

  void (*set_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, int64_t value);

If you specify the object and field ID and the value of the field, the value is set to the long type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  int64_t class_var_value = 5;
  env->set_class_var_long(env, stack, class_var_id, class_var_value);

=head2 set_class_var_float

  void (*set_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, float value);

If you specify the object and field ID and the value of the field, the value is set to the float type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  float class_var_value = 5;
  env->set_class_var_float(env, stack, class_var_id, class_var_value);

=head2 set_class_var_double

  void (*set_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, double value);

If you specify the object and field ID and the value of the field, the value is set to the double type field. The field ID must be a valid field ID obtained with the field_id function.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  double class_var_value = 5;
  env->set_class_var_double(env, stack, class_var_id, class_var_value);

=head2 set_class_var_object

  void (*set_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, void* value);

The object and field Specifies the ID and the value of the field and set the value to the object type field. The field ID must be a valid field ID obtained with the field_id function. After setting, the reference count is incremented by 1. The original value has the reference count decremented by 1.

Examples:

  int32_t class_var_id = env->get_class_var_id(env, "Foo", "$VAR");
  int32_t basic_type_id = env->get_basic_type_id(env, "Int");
  void* object = env->new_object(env, stack, basic_type_id);
  env->set_class_var_object(env, stack, class_var_id, class_var_value);

=head2 get_pointer

  void* (*get_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object);

Specifies a pointer object and return the C language pointer stored inside the object.

Examples:

  strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, stack, tm_obj);

=head2 set_pointer

  void (*set_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object, void* pointer);

If you specify a pointer object and a C language pointer, the C language pointer is saved in the internal data of the pointer type object.

=head2 call_method

  int32_t (*call_method)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length);

Call a method by specifying the method ID and the stack length of the argument. If an exception occurs in the method, The return value is 1. If not, return 0.

The return value of the method is set to args[0].

=head2 get_exception

  void* (*get_exception)(SPVM_ENV* env, SPVM_VALUE* stack);

Gets a exception message which type is byte[].

=head2 set_exception

  void (*set_exception)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception);

Sets a exception message which type is byte[].

=head2 get_ref_count

  int32_t (*get_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Gets the refernce count of the object.

=head2 inc_ref_count

  void (*inc_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Specifying an object increments the reference count of the object.

Use this method only if you have a specific reason to use it. Normally, the reference count is managed automatically.

=head2 dec_ref_count

  void (*dec_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Specifying an object decrements the object's reference count by 1. When the reference count reaches 0, the object is released.

Use this method only if you have a specific reason to use it. Normally, the reference count is managed automatically.

=head2 enter_scope

  int32_t (*enter_scope)(SPVM_ENV* env, SPVM_VALUE* stack);

Creates a new scope and return the scope ID.

=head2 push_mortal

  int32_t (*push_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Add an object to the mortal stack.

If this method succeed, return 0.

If this method don't alloc memory for new mortal information, return 1.

=head2 leave_scope

  void (*leave_scope)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t scope_id);

Specifies a scope ID to exit that scope and decrement the object's reference count stored in the mortal stack. Objects with a reference count of 0 are released. The scope ID must be the ID obtained by the enter_scope function.

=head2 remove_mortal

  int32_t (*remove_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t scope_id, void* remove_object);

Given a scope ID and an object, delete the specified object from the mortal stack.

=head2 is_type

  int32_t (*is_type)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t basic_type_id, int32_t type_dimension);

Given an object and a base type ID and a type dimension, returns a nonzero value if the object matches both the base type ID and the type dimension, and 0 otherwise.

=head2 is_object_array

  int32_t (*is_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

If the object is a object array, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 get_object_basic_type_id

  int32_t (*get_object_basic_type_id)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Gets the base type ID of the object.

=head2 get_object_type_dimension

  int32_t (*get_object_type_dimension)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Gets the dimension of the type of object.

=head2 weaken

  int32_t (*weaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_address);

Creates weak reference to the object which is specified by object address.

The reference count of the object is decrimented by 1 and weaken flag is added to the object address.

If the reference count is 1, "dec_ref_count" is called to the object.

If object_address is NULL, this method do nothing.

If the object is already weaken, this method do nothing.

This method allocate memory internally to add the back reference from the object to the object address.

This method success return 0.

If failing memory allocation of back reference, return 1.

=head2 isweak 

  int32_t (*isweak()SPVM_ENV* env, void** object);

Given the address of an object, returns non-zero if the object is a weak reference, 0 otherwise.

=head2 unweaken

  void (*unweaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_address);

Specifying the address of the object releases the weak reference to the object.

=head2 alloc_memory_block_zero

  void* (*alloc_memory_block_zero)(SPVM_ENV* env, size_t size);

Creates a new memory block that is managed by the environment with the byte size and return the address. If it fails, return C<NULL>.

The count of the memory block that is managed by the environment is incremented by C<1>.

=head2 free_memory_block

  void (*free_memory_block)(SPVM_ENV* env, void* block);

Frees the memory block that is managed by the environment.

The count of the memory block that is managed by the environment is decremented by C<1>.

=head2 get_memory_blocks_count

  int32_t (*get_memory_blocks_count)(SPVM_ENV* env);

Returns the count of the memory blocks on the environment.

=head2 get_type_name_raw

  void* (*get_type_name_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Gets a new C<string> object that is the type name of the object.

This function does not add the returned object to the mortal stack, so use the L<get_type_name> Native API for normal use to avoid memory leaks.

=head2 get_type_name

  void* (*get_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Gets a new C<string> object that is the type name of the object.

=head2 new_env

  SPVM_ENV* (*new_env)(SPVM_ENV* env);

Creates a new environment that is ready to call methods.

1. Create a new environment using the L<"new_env_raw"> native API.

2. Set the current compiler to the new enviroment.

3. Initialize the environment using the L<"init_env"> native API

The number of memory blocks is shared with the original execution environment.

If this method can't allocate memory for the new environment, return NULL.

Note that L</"call_init_blocks"> need to be called before calling user methods by yourself.

=head2 free_env

  void (*free_env)(SPVM_ENV* env);

Frees an environment that is created by the L<"new_env"> native API.

=head2 memory_blocks_count

  void* memory_blocks_count;

Unused from v0.9508+. The count of memory blocks is managed in L<"runtime">.

=head2 get_chars

  const char* (*get_chars)(SPVM_ENV* env, SPVM_VALUE* stack, void* string_object);

Gets characters in the string object.

Examples:

  const char* bytes = env->get_chars(env, stack, string_object);

=head2 die

  int32_t (*die)(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...);

Creates a C<sprintf> formatted message with file name and line number and set it to the exception.

Last two arguments are file name and line number.

Returns value is always 1;

Examples:

  return env->die(env, stack, "Value must be %d", 3, __FILE__, __LINE__);

=head2 new_object_by_name

  void* (*new_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, int32_t* error, const char* file, int32_t line);

This is same as C<new_object> function, but you can specify class name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

Examples:

  int32_t e;
  void* minimal = env->new_object_by_name(env, stack, "TestCase::Minimal", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 new_pointer_by_name

  void* (*new_pointer_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, void* pointer, int32_t* error, const char* file, int32_t line);

The same as the L</"new_pointer_object_by_name">, but this is deprecagted and will be removed.

=head2 set_field_byte_by_name

  void (*set_field_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name, int8_t value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_field_byte> function, but you can specify field name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

Examples:

  int32_t e;
  env->set_field_byte_by_name(env, stack, object, "byte_value", 13, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_field_short_by_name

  void (*set_field_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name, int16_t value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_field_short> function, but you can specify field name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

Examples:

  int32_t e;
  env->set_field_short_by_name(env, stack, object, "short_value", 13, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_field_int_by_name

  void (*set_field_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name, int32_t value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_field_int> function, but you can specify field name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

Examples:

  int32_t e;
  env->set_field_int_by_name(env, stack, object, "int_value", 13, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_field_long_by_name

  void (*set_field_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name, int64_t value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_field_long> function, but you can specify field name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

Examples:

  int32_t e;
  env->set_field_long_by_name(env, stack, object, "long_value", 13, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_field_float_by_name

  void (*set_field_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name, float value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_field_float> function, but you can specify field name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

Examples:

  int32_t e;
  env->set_field_float_by_name(env, stack, object, "float_value", 13, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_field_double_by_name

  void (*set_field_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name, double value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_field_double> function, but you can specify field name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

Examples:

  int32_t e;
  env->set_field_double_by_name(env, stack, object, "double_value", 13, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_field_object_by_name

  void (*set_field_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name, void* value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_field_object> function, but you can specify field name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

Examples:

  int32_t e;
  env->set_field_object_by_name(env, stack, object_simple, "object_value", object_minimal, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_field_byte_by_name

  int8_t (*get_field_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_field_byte> function, but you can specify field name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "byte_value", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_field_short_by_name

  int16_t (*get_field_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_field_short> function, but you can specify field name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int8_t short_value = env->get_field_short_by_name(env, stack, object, "short_value", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_field_int_by_name

  int32_t (*get_field_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_field_int> function, but you can specify field name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int8_t int_value = env->get_field_int_by_name(env, stack, object, "int_value", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_field_long_by_name

  int64_t (*get_field_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_field_long> function, but you can specify field name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int8_t long_value = env->get_field_long_by_name(env, stack, object, "long_value", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_field_float_by_name

  float (*get_field_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_field_float> function, but you can specify field name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int8_t float_value = env->get_field_float_by_name(env, stack, object, "float_value", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_field_double_by_name

  double (*get_field_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_field_double> function, but you can specify field name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int8_t double_value = env->get_field_double_by_name(env, stack, object, "double_value", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_field_object_by_name

  void* (*get_field_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_field_object> function, but you can specify field name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  void* object_minimal = env->get_field_object_by_name(env, stack, object_simple, "object_value", "TestCase::Minimal", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_class_var_byte_by_name

  void (*set_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name, int8_t value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_class_var_byte> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", 15, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_class_var_short_by_name

  void (*set_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name, int16_t value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_class_var_short> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", 15, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_class_var_int_by_name

  void (*set_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name, int32_t value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_class_var_int> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", 15, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_class_var_long_by_name

  void (*set_class_var_long_by_name)(SPVM_ENV* env
    const char* class_name, const char* class_var_name, int64_t value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_class_var_long> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  env->set_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", 15, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_class_var_float_by_name

  void (*set_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name, float value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_class_var_float> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  env->set_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", 15, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_class_var_double_by_name

  void (*set_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name, double value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_class_var_double> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  env->set_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", 15, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 set_class_var_object_by_name

  void (*set_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name, void* value,
    int32_t* error, const char* file, int32_t line);

This is same as C<set_class_var_object> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  env->set_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", "TestCase::Minimal", minimal, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_class_var_byte_by_name

  int8_t (*get_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_class_var_byte> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int8_t value = env->get_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_class_var_short_by_name

  int16_t (*get_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_class_var_short> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int16_t value = env->get_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_class_var_int_by_name

  int32_t (*get_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_class_var_int> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int8_t value = env->get_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_class_var_long_by_name

  int64_t (*get_class_var_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_class_var_long> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_class_var_float_by_name

  float (*get_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_class_var_float> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_class_var_double_by_name

  double (*get_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_class_var_double> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:

  int32_t e;
  double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 get_class_var_object_by_name

  void* (*get_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* class_var_name,
    int32_t* error, const char* file, int32_t line);

This is same as C<get_class_var_object> function, but you can specify the class name directly.

If function is succeeded, C<error> is get to 0. If a exception occurs, C<error> is get to 1. 

Examples:
  
  int32_t e;
  void* value = env->get_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 call_class_method_by_name

  int32_t (*call_class_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* method_name, int32_t args_stack_length,
    const char* file, int32_t line);

This is same as C<call_method> function, but you can specify the class name and method name directly.

Examples:

  int32_t output;
  {
    int32_t args_stack_length = 1;
    stack[0].ival = 5;
    int32_t error = env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "my_value", args_stack_length, __FILE__, __LINE__);
    if (error) {
      return error;
    }
    output = stack[0].ival;
  }

=head2 call_instance_method_by_name

  int32_t (*call_instance_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* method_name, int32_t args_stack_length,
    const char* file, int32_t line);

=head2 get_field_string_chars_by_name

  const char* (*get_field_string_chars_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    void* object, const char* field_name,
    int32_t* error, const char* file, int32_t line);

Examples:

=head2 free_env_prepared
  
  void (*free_env_prepared)(SPVM_ENV* env);

Frees the environment prepared by C<SPVM_NATIVE_new_env_prepared> function.

=head2 dump_raw

  void* (*dump_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Gets the string which dump the object. The string is the same as the return value of C<dump> operator.

=head2 dump

  void* (*dump)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

The same as C<dump_raw>, and push the created object to the mortal stack. Use this function in normal use instead of C<dump_raw>.

=head2 get_instance_method_id_static

  int32_t (*get_instance_method_id_static)(SPVM_ENV* env, const char* class_name, const char* method_name);

Gets a instance method ID by the class name, the method name. If the instance method does not exists, a negative value is returned.

This ID is used by L<"call_method">.

Examples:

  int32_t method_id = env->get_instance_method_id_static(env, "Foo", "get");

=head2 get_bool_object_value

  int32_t (*get_bool_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* bool_object);

Gets the value of a L<Bool|SPVM::Bool> object. If the Bool object is true, return 1, otherwise return 0.

Examples:

  int32_t bool_value = env->get_bool_object_value(env, stack, bool_object);

=head2 cleanup_global_vars
  
  void (*cleanup_global_vars)(SPVM_ENV* env);

Cleanup gloval variable, such as class variables and the exception variable.

=head2 make_read_only

  void (*make_read_only)(SPVM_ENV* env, SPVM_VALUE* stack, void* string)

Make the string read-only.

=head2 is_read_only

  void (*make_read_only)(SPVM_ENV* env, SPVM_VALUE* stack, void* string)

If the string is read-only, returns C<1>, otherwise returns C<0>.

=head2 is_array

  int32_t (*is_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

If the object is an array, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 is_string

  int32_t (*is_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

If the object is a string, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 is_numeric_array

  int32_t (*is_numeric_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

If the object is a numeric array, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 is_mulnum_array

  int32_t (*is_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

If the object is a multi numeric array, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 get_elem_size

  int32_t (*get_elem_size)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);

Gets the byte size of the element of the array.

=head2 new_array_proto

  void* (*new_array_proto)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t length);

Creates a new array that have the type of the given array and the given length.

The given array must be the object that is an array type.

If the given array is L<NULL>, returns C<NULL>.

If the given length is lower than C<0>, returns C<NULL>.

=head2 copy

  void* (*copy)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Copy the object. The type of the object must be a string type, a numeric array, or a multi numeric array.

If the given object is L<NULL>, returns L<NULL>.

=head2 shorten

  void (*shorten)(SPVM_ENV* env, SPVM_VALUE* stack, void* string, int32_t new_length);

Shorten the string with the given length.

If the string is null, does nothing.

If the given length is greater than the length of the string, does nothing.

If the given length is lower than C<0>, the given length become C<0>.

The charaters of the after the given length are filled with C<\0>.

=head2 has_interface

  int32_t (*has_interface)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t interface_basic_type_id);

Check the type of the object has the interface.

=head2 print

  void (*print)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);

Prints the characters of the string to stdout.

If the string is C<NULL>, nothing is printed.

=head2 print_stderr

  void (*print_stderr)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);

Prints the characters of the string to stderr.

If the string is C<NULL>, nothing is printed.

=head2 init_env

  int32_t (*init_env)(SPVM_ENV* env);

Initialize the environment.

=head2 call_init_blocks
  
  void (*call_init_blocks)(SPVM_ENV* env);

Call C<INIT> blocks.

=head2 get_class_id

  int32_t (*get_class_id)(SPVM_ENV* env, const char* class_name);

=head2 new_stack

  SPVM_VALUE* (*new_stack)(SPVM_ENV* env);

=head2 free_stack

  void (*free_stack)(SPVM_ENV* env, SPVM_VALUE* stack);

=head2 new_memory_env

  void* (*new_memory_env)(SPVM_ENV* env, size_t size);

Creates a new memory block that is managed by the environment with the byte size and return the address. If it fails, return C<NULL>.

The count of the memory block that is managed by the environment is incremented by C<1>.

This is the same as L</"alloc_memory_block_zero">. This is more understandable name that memories are managed by the environment.

=head2 free_memory_env

  void (*free_memory_env)(SPVM_ENV* env, void* block);

Frees the memory block that is managed by the environment.

The count of the memory block that is managed by the environment is decremented by C<1>.

This is the same as L</"free_memory_block">. This is more understandable name that memories are managed by the environment.

=head2 get_memory_blocks_count_env

  int32_t (*get_memory_blocks_count_env)(SPVM_ENV* env);

Returns the count of the memory blocks on the environment.

This is the same as L</"get_memory_blocks_count">. This is more understandable name that memories are managed by the environment.

=head2 new_memory_stack

  void* (*new_memory_stack)(SPVM_ENV* env, SPVM_VALUE* stack, size_t size);

Creates a new memory block that is managed by the stack of the environment with the byte size and return the address. If it fails, return C<NULL>.

The count of the memory block that is managed by the stack is incremented by C<1>.

The count of the memory block that is managed by the environment is incremented by C<1>.

=head2 free_memory_stack

  void (*free_memory_stack)(SPVM_ENV* env, SPVM_VALUE* stack, void* block);

Frees the memory block that is managed by the environment.

The count of the memory block that is managed by the stack is decremented by C<1>.

The count of the memory block that is managed by the environment is decremented by C<1>.

=head2 get_memory_blocks_count_stack

  int32_t (*get_memory_blocks_count_stack)(SPVM_ENV* env, SPVM_VALUE* stack);

Returns the count of the memory blocks on the stack.

=head2 set_command_info_program_name

  int32_t (*set_command_info_program_name)(SPVM_ENV* env, void* obj_program_name);

Sets the program name. This value is got by L<CommandInfo->PROGRAM_NAME|SPVM::CommandInfo/"PROGRAM_NAME">.

If it succeed, return C<0>.

The program name must be a C<string> object. Otherwise return non-zero value.

=head2 set_command_info_argv

  int32_t (*set_command_info_argv)(SPVM_ENV* env, void* obj_argv);

Sets the argv. This value is got by L<CommandInfo->ARGV|SPVM::CommandInfo/"ARGV">.

If it succeed, return C<0>.

The argv must be a C<string[]> object. Otherwise return non-zero value.

=head2 get_class_id_by_name

  int32_t (*get_class_id_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, int32_t* error, const char* file, int32_t line);

Gets the class id by the class name.

If the class is not loaded, The C<error> is set to C<1>. Otherwise set to C<0>.

=head2 strerror

  const char* (*strerror)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);

Gets the value of C<strerror> of C<C language> on thread-safely.

If the length is C<0>, the length is set to C<64>.

=head2 new_string_array

  void* (*new_string_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);

Creates a new string array. This is alias for the following code using L</"new_object_array">.

  void* obj_string_array = env->new_object_array(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, length);

=head2 get_args_stack_length

  int32_t (*get_args_stack_length)(SPVM_ENV* env, SPVM_VALUE* stack);

Gets the stack length of the arguments specified by the caller.

=head2 set_args_stack_length

  void (*set_args_stack_length)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t args_length);

Sets the stack length of the arguments for a method call.

=head2 dumpc

  const char* (*dumpc)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

The alias for the following code using L</"dump">.

  const char* ret = env->get_chars(env, stack, SPVM_API_dump(env, stack, object));

=head2 new_pointer_object_raw

  void* (*new_pointer_object_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer);

Creates a pointer object by specifying a basic type ID and a C language pointer. The basic type ID must be the correct basic type ID got by C<get_basic_type_id> function.

=head2 new_pointer_object

  void* (*new_pointer_object)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer);

The same as L</"new_pointer_raw">, and push the created object to the mortal stack. Use this function in normal use instead of C<new_pointer_raw>.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, "MyTime");
  void* pointer = malloc(sizeof (struct tm));
  void* pointer_obj = env->new_pointer(env, stack, basic_type_id, pointer);

=head2 new_pointer_object_by_name

  void* (*new_pointer_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, void* pointer, int32_t* error, const char* file, int32_t line);

This is same as L</"new_pointer"> function, but you can specify class name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

  int32_t e;
  void* minimal = env->new_pointer_by_name(env, stack, "TestCase::Pointer", pointer, &e, __FILE__, __LINE__);
  if (e) { return e; }

=head2 is_class

  int32_t (*is_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

If the object is a instance of a class, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 is_pointer_class

  int32_t (*is_pointer_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

If the object is a instance of a pointer class, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 strerror_string

  void* (*strerror_string)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);

The same as the L</"strerror"> function, but return a C<string> object.

=head2 get_basic_type_id_by_name

  int32_t (*get_basic_type_id_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error, const char* file, int32_t line);

Gets the basic_type id by the basic_type name.

If the basic_type is not loaded, The C<error> is set to C<1>. Otherwise set to C<0>.

=head2 get_field_id_static

  int32_t (*get_field_id_static)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* field_name);

Gets the ID of the field given an class name and field name. If the field does not exist, a value less than 0 is returned.

Examples:

  int32_t field_id = env->get_field_id_static(env, stack, "Point", "x");

=head2 items

  int32_t (*items)(SPVM_ENV* env, SPVM_VALUE* stack);

The alias for the L</"get_args_stack_length">.

Examples:

  int32_t items = env->items(env, stack);

=head2 call_instance_method_static_by_name

  int32_t (*call_instance_method_static_by_name)(SPVM_ENV* env, SPVM_VALUE* stack,
    const char* class_name, const char* method_name, int32_t args_stack_length,
    const char* file, int32_t line);

Calls a instance method by the class name and the method name.

Examples:

  int32_t output;
  {
    int32_t args_stack_length = 1;
    stack[0].oval = obj_point;
    int32_t error = env->call_instance_method_static_by_name(env, stack, "Point", "x", args_stack_length, __FILE__, __LINE__);
    if (error) {
      return error;
    }
    output = stack[0].ival;
  }

=head2 get_method_id

  int32_t (*get_method_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name);

Gets a method ID by the class name and the method name. If the method does not exists, a negative value is returned.

This ID is used by L<"call_method">.

Examples:

  int32_t method_id = env->get_method_id(env, "Foo", "get");

=head2 strerror_nolen

  const char* (*strerror_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);

The same as L</"strerror"> given the length to C<0>.

=head2 strerror_string_nolen

  void* (*strerror_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);

The same as L</"strerror_string"> given the length to C<0>.

=head2 get_compile_type_name_raw

  void* (*get_compile_type_name_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t type_dimension, int32_t type_flag);

Gets a new C<string> object that is the compile-time type name with a basic type id, a type dimension, a type flag.

This function does not add the returned object to the mortal stack, so use the L<get_compile_type_name> Native API for normal use to avoid memory leaks.

=head2 get_compile_type_name

  void* (*get_compile_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t type_dimension, int32_t type_flag);

Gets a new C<string> object that is the compile-time type name with a basic type id, a type dimension, a type flag.

=head1 Compiler Native API

L<SPVM::Document::NativeAPI::Compiler>

=head1 Precompile Native API

L<SPVM::Document::NativeAPI::Precompile>

=head1 Runtime Native API

L<SPVM::Document::NativeAPI::Runtime>

=head1 String Buffer Native API

L<SPVM::Document::NativeAPI::StringBuffer>

=head1 Allocator Native API

L<SPVM::Document::NativeAPI::Allocator>

=head1 Constant Values

=head2 Basic Type IDs

  0  SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN
  1  SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF
  2  SPVM_NATIVE_C_BASIC_TYPE_ID_VOID
  3  SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE
  4  SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT
  5  SPVM_NATIVE_C_BASIC_TYPE_ID_INT
  6  SPVM_NATIVE_C_BASIC_TYPE_ID_LONG
  7  SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT
  8  SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE
  9  SPVM_NATIVE_C_BASIC_TYPE_ID_STRING
  10 SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT
  11 SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS
  12 SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS
  13 SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS
  14 SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS
  15 SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS
  16 SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS
  17 SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS
  18 SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS
  19 SPVM_NATIVE_C_BASIC_TYPE_ID_COMMAND_INFO_CLASS
  20 SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS
  21 SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS

These IDs are permanently same for the binary compatibility after the future release C<v1.0>.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN

The basic type is unknown.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF

The basic type ID of C<undef> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_VOID

The basic type ID of C<void> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE

The basic type ID of C<byte> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT

The basic type ID of C<short> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_INT

The basic type ID of C<int> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_LONG

The basic type ID of C<long> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT

The basic type ID of C<float> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE

The basic type ID of C<double> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_STRING

The basic type ID of C<string> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT

The basic type ID of C<object> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS

The basic type ID of L<Byte|SPVM::Byte> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS

The basic type ID of L<Short|SPVM::Short> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS

The basic type ID of L<Int|SPVM::Int> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS

The basic type ID of L<Long|SPVM::Long> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS

The basic type ID of L<Float|SPVM::Float> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS

The basic type ID of L<Double|SPVM::Double> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS

The basic type ID of L<BOOL|SPVM::BOOL> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS

The basic type ID of L<Error|SPVM::Error> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS

The basic type ID of L<Error::System|SPVM::Error::System> type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS

The basic type ID of L<Error::NotSupported|SPVM::Error::NotSupported> type.

=head2 Constant Values of Basic Type Categories

  0 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN
  1 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NOT_FOUND_CLASS
  2 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNDEF
  3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID
  4 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC
  5 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM
  6 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING
  7 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS
  8 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE
  9 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT

These IDs are permanently same for the binary compatibility after the future release C<v1.0>.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN

The basic type category for unknown types.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NOT_FOUND_CLASS

The basic type category for not found class types.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNDEF

The basic type category for the undefined type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID

The basic type category for the void type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC

The basic type category for the numeric types.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM

The basic type category for the multi-numeric types.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING

The basic type category for the string type.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS

The basic type category for the class types.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE

The basic type category for the interface types.

=head3 SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT

The basic type category for the any object type.

=head2 Type Flags

  1 SPVM_NATIVE_C_TYPE_FLAG_REF
  2 SPVM_NATIVE_C_TYPE_FLAG_MUTABLE

The type flags.

=head2 Class IDs

  1  SPVM_NATIVE_C_CLASS_ID_ERROR
  2  SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM
  3  SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED

These IDs are permanently same for the binary compatibility after the future release C<v1.0>.

=head3 SPVM_NATIVE_C_CLASS_ID_ERROR

The class id of L<Error|SPVM::Error> class.

=head3 SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM

The class id of L<Error::System|SPVM::Error::System> class.

=head3 SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED

The class id of L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head1 Utility Functions

=head2 spvm_warn

  void spvm_warn(const char* format, ...)

Prints the formatted message to C<stderr> with a new line.

Examples:

  spvm_warn("Hello");
  spvm_warn("Hello %s%d", "Foo", 3);

=head1 Examples

=over 2

=item * L<Examples using SPVM native APIs|https://github.com/yuki-kimoto/SPVM/tree/master/examples/native>

=back

