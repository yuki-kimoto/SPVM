=head1 Name

SPVM::Document::NativeAPI - Native APIs

=head1 Description

The native APIs in L<SPVM> are the APIs written by the C language for SPVM operations.

These APIs are available in L<native classes|SPVM::Document::NativeClass>.

=head1 Native APIs

=head2 runtime

L<void* runtime|SPVM::Document::NativeAPI::Runtime>;

The runtime for this L<runtime environment|SPVM::Document::NativeClass/"Runtime Environment">.

Examples:

  void* runtime = env->runtime;

=head2 api

C<SPVM_ENV_API* api;>

Returns C<SPVM_ENV_API> object. This object have the following fields for other native APIs.

=over 2

=item * L<SPVM_API_ALLOCATOR* allocator|SPVM::Document::NativeAPI::Allocator>

=item * L<SPVM_API_STRING_BUFFER* string_buffer|SPVM::Document::NativeAPI::StringBuffer>

=item * L<SPVM_API_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>

=item * L<SPVM_API_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>

=item * L<SPVM_API_RUNTIME* runtime|SPVM::Document::NativeAPI::Runtime>

=item * L<SPVM_API_BASIC_TYPE* basic_type|SPVM::Document::NativeAPI::BasicType>

=item * L<SPVM_API_CLASS_VAR* class_var|SPVM::Document::NativeAPI::ClassVariable>

=item * L<SPVM_API_FIELD* field|SPVM::Document::NativeAPI::Field>

=item * L<SPVM_API_METHOD* method|SPVM::Document::NativeAPI::Method>

=item * L<SPVM_API_ARG* arg|SPVM::Document::NativeAPI::Argument>

=item * L<SPVM_API_TYPE* type|SPVM::Document::NativeAPI::Type>

=item * L<SPVM_API_INTERNAL* internal|SPVM::Document::NativeAPI::Internal>

=item * L<SPVM_API_MUTEX* mutex|SPVM::Document::NativeAPI::Mutex>

=back

Examples:

  SPVM_API_BASIC_TYPE* api_basic_type = env->api->basic_type;

=head2 new_env

C<SPVM_ENV* (*new_env)();>

Creates a new L<runtime environment|SPVM::Document::NativeClass/"Runtime Environment">.

This native API should not be used unless special purposes are intended.

=head2 free_env

C<void (*free_env)(SPVM_ENV* env);>

Frees the L<runtime environment|SPVM::Document::NativeClass/"Runtime Environment"> I<env>.

This native API should not be used unless special purposes are intended.

=head2 call_init_methods
  
C<int32_t (*call_init_methods)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Calls C<INIT> blocks of all classes.

If an exception is thrown, returns a non-zero value. Otherwise, returns 0.

This native API should not be used unless special purposes are intended.

=head2 set_command_info_program_name

C<int32_t (*set_command_info_program_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* obj_program_name);>

Sets the program name I<obj_program_name> to L<CommandInfo#PROGRAM_NAME|SPVM::CommandInfo/"PROGRAM_NAME"> class variable.

If an exception is thrown, returns a non-zero value. Otherwise, returns 0.

This native API should not be used unless special purposes are intended.

=head2 set_command_info_argv

C<int32_t (*set_command_info_argv)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* obj_argv);>

Sets the command line arguments I<obj_argv> to L<CommandInfo#ARGV|SPVM::CommandInfo/"ARGV"> class variable.

If an exception is thrown, returns a non-zero value. Otherwise, returns 0.

This native API should not be used unless special purposes are intended.

=head2 set_command_info_base_time

C<int32_t (*set_command_info_base_time)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int64_t base_time);>

Sets the base time I<base_time> to L<CommandInfo#BASE_TIME|SPVM::CommandInfo/"BASE_TIME"> class variable.

If an exception is thrown, returns a non-zero value. Otherwise, returns 0.

This native API should not be used unless special purposes are intended.

=head2 destroy_class_vars
  
C<void (*destroy_class_vars)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Destroys the class variables of all classes.

This native API should not be used unless special purposes are intended.

=head2 args_width

C<int32_t (*args_width)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Returns the L<width of the arguments|SPVM::Document::NativeClass/"Arguments Width"> given by the caller. 

Examples:

  int32_t args_width = env->args_width(env, stack);

=head2 get_object_basic_type

C<void* (*get_object_basic_type)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the object I<object>.

=head2 get_object_basic_type_id

C<int32_t (*get_object_basic_type_id)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Returns the basic type ID of the object I<object>.

=head2 get_object_basic_type_name

C<const char* (*get_object_basic_type_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Returns the basic type name of the object I<object>.

=head2 get_object_type_dimension

C<int32_t (*get_object_type_dimension)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Returns the type dimension of the object I<object>.

=head2 get_basic_type

C<void* (*get_basic_type)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name);>

Searches a L<basic type|SPVM::Document::NativeAPI::BasicType> given the basic type name I<basic_type_name>.

If it is found, returns it. Otherwise, returns C<NULL>.

=head2 get_basic_type_by_name

C<void* (*get_basic_type_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a L<basic type|SPVM::Document::NativeAPI::BasicType> given the basic type name I<basic_type_name>.

If it is found, returns it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If an exception is thrown, C<error_id> is set to a non-zero value. Otherwise, it is set to 0.

=head2 get_basic_type_by_id

C<void* (*get_basic_type_by_id)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t basic_type_id);>

Searches a L<basic type|SPVM::Document::NativeAPI::BasicType> given the  basic type ID I<basic_type_id>.

If it is found, returns it. Otherwise, returns C<NULL>.

=head2 get_basic_type_id

C<int32_t (*get_basic_type_id)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name);>

Searches a basic type given the basic type name I<basic_type_name>.

If it is found, returns the basic type id of it. Otherwise, returns a negative value.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, stack, "Int");

=head2 get_basic_type_id_by_name

C<int32_t (*get_basic_type_id_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a basic type ID given the basic type name I<basic_type_name>.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If an exception is thrown, C<error_id> is set to a non-zero value. Otherwise, it is set to 0.

=head2 get_class_var

C<void* (*get_class_var)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name);>

Searches a L<class variable|SPVM::Document::NativeAPI::ClassVariable> given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, returns it. Otherwise, returns C<NULL>.

Examples:

  void* class_var = env->get_class_var(env, stack, "MyClass", "$VAR");

=head2 get_class_var_byte

C<int8_t (*get_class_var_byte)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the value of the class variable I<class_var> interpreting its type is byte type.

=head2 get_class_var_short

C<int16_t (*get_class_var_short)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the value of the class variable I<class_var> interpreting its type is short type.

=head2 get_class_var_int

C<int32_t (*get_class_var_int)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the value of the class variable I<class_var> interpreting its type is int type.

=head2 get_class_var_long

C<int64_t (*get_class_var_long)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the value of the class variable I<class_var> interpreting its type is long type.

=head2 get_class_var_float

C<float (*get_class_var_float)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the value of the class variable I<class_var> interpreting its type is float type.

=head2 get_class_var_double

C<double (*get_class_var_double)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the value of the class variable I<class_var> interpreting its type is double type.

=head2 get_class_var_object

C<void* (*get_class_var_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the value of the class variable I<class_var> interpreting its type is an object type.

=head2 get_class_var_string

C<void* (*get_class_var_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the value of the class variable I<class_var> interpreting its type is string type.

=head2 set_class_var_byte

C<void (*set_class_var_byte)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>, int8_t value);>

Sets I<value> to the class variable I<class_var> interpreting its type is byte type.

=head2 set_class_var_short

C<void (*set_class_var_short)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>, int16_t value);>

Sets I<value> to the class variable I<class_var> interpreting its type is short type.

=head2 set_class_var_int

C<void (*set_class_var_int)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>, int32_t value);>

Sets I<value> to the class variable I<class_var> interpreting its type is int type.

=head2 set_class_var_long

C<void (*set_class_var_long)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>, int64_t value);>

Sets I<value> to the class variable I<class_var> interpreting its type is long type.

=head2 set_class_var_float

C<void (*set_class_var_float)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>, float value);>

Sets I<value> to the class variable I<class_var> interpreting its type is float type.

=head2 set_class_var_double

C<void (*set_class_var_double)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>, double value);>

Sets I<value> to the class variable I<class_var> interpreting its type is double type.

=head2 set_class_var_object

C<void (*set_class_var_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>, void* value);>

Sets I<value> to the class variable I<class_var> interpreting its type is an object type.

=head2 set_class_var_string

C<void (*set_class_var_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>, void* value);>

Sets I<value> to the class variable I<class_var> interpreting its type is string type.

=head2 get_class_var_object_ref

C<void** (*get_class_var_object_ref)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the address where the value of the class variable I<class_var> is stored.

=head2 get_class_var_byte_by_name

C<int8_t (*get_class_var_byte_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as byte type and returns its value. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the class variable given by I<class_var_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int8_t value = env->get_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_short_by_name

C<int16_t (*get_class_var_short_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as short type and returns its value. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the class variable given by I<class_var_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int16_t value = env->get_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_int_by_name

C<int32_t (*get_class_var_int_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as int type and returns its value. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the class variable given by I<class_var_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int8_t value = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_long_by_name

C<int64_t (*get_class_var_long_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as long type and returns its value. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the class variable given by I<class_var_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_float_by_name

C<float (*get_class_var_float_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as float type and returns its value. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the class variable given by I<class_var_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_double_by_name

C<double (*get_class_var_double_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as double type and returns its value. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the class variable given by I<class_var_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_object_by_name

C<void* (*get_class_var_object_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as an object type and returns its value. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the class variable given by I<class_var_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:
  
  int32_t error_id = 0;
  void* value = env->get_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_string_by_name

C<void* (*get_class_var_string_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as string type and returns its value. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the class variable given by I<class_var_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

=head2 set_class_var_byte_by_name

C<void (*set_class_var_byte_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as byte type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", 15, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_short_by_name

C<void (*set_class_var_short_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable I<class_var> given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as short type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", 15, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_int_by_name

C<void (*set_class_var_int_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable I<class_var> given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as int type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", 15, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_long_by_name

C<void (*set_class_var_long_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>
Searches a class variable I<class_var> given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as long type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", 15, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_float_by_name

C<void (*set_class_var_float_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable I<class_var> given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as float type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", 15, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_double_by_name

C<void (*set_class_var_double_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a class variable I<class_var> given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as double type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", 15, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_object_by_name

C<void (*set_class_var_object_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>
Searches a class variable I<class_var> given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as an object type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", minimal, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_string_by_name

C<void (*set_class_var_string_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* class_var_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>
Searches a class variable I<class_var> given the basic type name I<basic_type_name> and the class variable name I<class_var_name>.

If it is found, interprets it as string type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

=head2 get_field

C<void* (*get_field_by_index)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name);>

Searches a L<field|SPVM::Document::NativeAPI::Field> object given the object I<object> and the field name I<field_name>.

If it is found, returns it. Otherwise, returns C<NULL>.

Examples:

  void* field = env->get_field(env, stack, object, "x");

=head2 get_field_static

C<void* (*get_field_static)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* field_name);>

Searches a L<field|SPVM::Document::NativeAPI::Field> object given the basic type name I<basic_type_name> and the field name I<field_name>.

If it is found, returns it. Otherwise, returns C<NULL>.

Examples:

  void* field = env->get_field_static(env, stack, "Point", "x");

=head2 get_field_byte

C<int8_t (*get_field_byte)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the value of the field I<field> of the object I<object> interpreting its type is byte type.

=head2 get_field_short

C<int16_t (*get_field_short)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the value of the field I<field> of the object I<object> interpreting its type is short type.

=head2 get_field_int

C<int32_t (*get_field_int)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the value of the field I<field> of the object I<object> interpreting its type is int type.

=head2 get_field_long

C<int64_t (*get_field_long)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the value of the field I<field> of the object I<object> interpreting its type is long type.

=head2 get_field_float

C<float (*get_field_float)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the value of the field I<field> of the object I<object> interpreting its type is float type.

=head2 get_field_double

C<double (*get_field_double)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the value of the field I<field> of the object I<object> interpreting its type is double type.

=head2 get_field_object

C<void* (*get_field_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the value of the field I<field> of the object I<object> interpreting its type is an object type.

=head2 get_field_string

C<void* (*get_field_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the value of the field I<field> of the object I<object> interpreting its type is string type.

=head2 set_field_byte

C<void (*set_field_byte)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>, int8_t value);>

Sets I<value> to the field I<field> of the object I<object> interpreting its type is byte type.

=head2 set_field_short

C<void (*set_field_short)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>, int16_t value);>

Sets I<value> to the field I<field> of the object I<object> interpreting its type is short type.

=head2 set_field_int

C<void (*set_field_int)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>, int32_t value);>

Sets I<value> to the field I<field> of the object I<object> interpreting its type is int type.

=head2 set_field_long

C<void (*set_field_long)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>, int64_t value);>

Sets I<value> to the field I<field> of the object I<object> interpreting its type is long type.

=head2 set_field_float

C<void (*set_field_float)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>, float value);>

Sets I<value> to the field I<field> of the object I<object> interpreting its type is float type.

=head2 set_field_double

C<void (*set_field_double)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>, double value);>

Sets I<value> to the field I<field> of the object I<object> interpreting its type is double type.

=head2 set_field_object

C<void (*set_field_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>, void* value);>

Sets I<value> to the field I<field> of the object I<object> interpreting its type is an object type.

=head2 set_field_string

C<void (*set_field_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>, void* value);>

Sets I<value> to the field I<field> interpreting its type is string type.

=head2 get_field_byte_by_name

C<int8_t (*get_field_byte_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as byte type and returns the value of it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the field given by I<field_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "byte_value", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_short_by_name

C<int16_t (*get_field_short_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as short type and returns the value of it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the field given by I<field_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int8_t short_value = env->get_field_short_by_name(env, stack, object, "short_value", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_int_by_name

C<int32_t (*get_field_int_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as int type and returns the value of it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the field given by I<field_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int8_t int_value = env->get_field_int_by_name(env, stack, object, "int_value", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_long_by_name

C<int64_t (*get_field_long_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as long type and returns the value of it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the field given by I<field_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int8_t long_value = env->get_field_long_by_name(env, stack, object, "long_value", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_float_by_name

C<float (*get_field_float_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as float type and returns the value of it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the field given by I<field_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int8_t float_value = env->get_field_float_by_name(env, stack, object, "float_value", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_double_by_name

C<double (*get_field_double_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as double type and returns the value of it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the field given by I<field_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  int8_t double_value = env->get_field_double_by_name(env, stack, object, "double_value", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_object_by_name

C<void* (*get_field_object_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as an object type and returns the value of it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the field given by I<field_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  void* object_minimal = env->get_field_object_by_name(env, stack, object_simple, "object_value", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_string_by_name

C<void* (*get_field_string_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as string type and returns the value of it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the field given by I<field_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

=head2 set_field_byte_by_name

C<void (*set_field_byte_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as byte type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_byte_by_name(env, stack, object, "byte_value", 13, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_short_by_name

C<void (*set_field_short_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as short type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_short_by_name(env, stack, object, "short_value", 13, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_int_by_name

C<void (*set_field_int_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as int type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_int_by_name(env, stack, object, "int_value", 13, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_long_by_name

C<void (*set_field_long_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as long type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_long_by_name(env, stack, object, "long_value", 13, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_float_by_name

C<void (*set_field_float_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as float type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_float_by_name(env, stack, object, "float_value", 13, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_double_by_name

C<void (*set_field_double_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as double type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_double_by_name(env, stack, object, "double_value", 13, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_object_by_name

C<void (*set_field_object_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as an object type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_object_by_name(env, stack, object_simple, "object_value", object_minimal, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_string_by_name

C<void (*set_field_string_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field I<field> given the object I<object> and the field name I<field_name>.

If it is found, interprets it as string type and sets I<value> to it. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

=head2 get_field_string_chars_by_name

C<const char* (*get_field_string_chars_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Calls the L</"get_field_string_by_name">. If the return value is C<NULL>, returns C<NULL>. Otherwise, calls the L</"get_chars"> given the return value, and returns the return value of L</"get_chars"> native API.

=head2 get_method

C<void* (*get_method)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* method_name);>

Searches a L<method|SPVM::Document::NativeAPI::Method> given the basic type name I<basic_type_name> and the method name I<method_name>.

If it is found, returns it. Otherwise, returns C<NULL>.

Examples:

  void* method = env->get_method(env, stack, "Foo", "get");

=head2 get_class_method

C<void* (*get_class_method)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* method_name);>

Searches a class L<method|SPVM::Document::NativeAPI::Method> given the basic type name I<basic_type_name> and the method name I<method_name>.

If it is found, returns it. Otherwise, returns C<NULL>.

Examples:

  void* method = env->get_class_method(env, stack, "Foo", "get");

=head2 get_instance_method_static

C<void* (*get_instance_method_static)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* method_name);>

Searches an instance method given the basic type name I<basic_type_name> and the method name I<method_name>.

If found, returns it. Otherwise, returns C<NULL>.

Examples:
  
  void* method = env->get_instance_method_static(env, stack, "Foo", "get");

=head2 get_instance_method

C<void* (*get_instance_method)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* method_name);>

Searches an instance L<method|SPVM::Document::NativeAPI::Method> given the object I<object> and the method name I<method_name>.

If it is found, returns it. Otherwise, returns C<NULL>.

Examples:

  void* method = env->get_instance_method(env, stack, object, "get");

=head2 call_method_no_mortal

C<int32_t (*call_method_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* method|SPVM::Document::NativeAPI::Method>, int32_t args_width);>

Calls the method I<method> given the L<width of the argument|SPVM::Document::NativeClass/"Arguments Width"> I<args_width>.

If the method throws an exception, returns a basic type ID of an error class. Otherwise, returns 0.

C<stack[0]> is set to the return value of the method.

This native API should not be used unless special purposes are intended. Normally, use L</"call_method"> native API.

=head2 call_method

C<int32_t (*call_method)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* method|SPVM::Document::NativeAPI::Method>, int32_t args_width);>

Calls L</"call_method_no_mortal"> native API and if the type of the its return value is an object type, it is push to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 call_class_method_by_name

C<void (*call_class_method_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Calls a class method given the basic type name I<basic_type_name> and the method name I<method_name>.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the method given by I<method_name> is not found, an exception is thrown.

If the found method is not a class method, an exception is thrown.

If an exception is thrown, C<error_id> is set to a non-zero value. Otherwise, it is set to 0.

Examples:
  
  // Call a class method
  int32_t error_id = 0;
  int32_t total;
  {
    int32_t args_width = 2;
    stack[0].ival = 5;
    stack[1].ival = 10;
    env->call_class_method_by_name(env, stack, "MyClass", "sum", args_width, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    total = stack[0].ival;
  }

=head2 call_instance_method_static_by_name

C<void (*call_instance_method_static_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Calls an instance method by the basic type name I<basic_type_name> and the method name I<method_name>.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the method given by I<method_name> is not found, an exception is thrown.

If the found method is not an instance method, an exception is thrown.

If C<stack[0].oval> is C<NULL>, an exception is thrown.

If C<stack[0].oval> cannot be assigned to the class given by I<basic_type_name>, an exception is thrown.

If an exception is thrown, C<error_id> is set to a non-zero value. Otherwise, it is set to 0.

Examples:
  
  int32_t error_id = 0;
  int32_t output;
  {
    int32_t args_width = 1;
    stack[0].oval = obj_point;
    env->call_instance_method_static_by_name(env, stack, "Point", "x", args_width, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    output = stack[0].ival;
  }

=head2 call_instance_method_by_name

C<void (*call_instance_method_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Calls an instance method given the method name I<method_name>.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If C<stack[0].oval> is C<NULL>, an exception is thrown.

The type dimension of C<stack[0].oval> must be 0. Otherwise, an exception is thrown.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the instance method given by I<method_name> is not found in the class or super classes, an exception is thrown.

If an exception is thrown, C<error_id> is set to a non-zero value. Otherwise, it is set to 0.

=head2 new_object_no_mortal

C<void* (*new_object_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Creates a new object given the basic type I<basic_type>.

I<basic_type> must not be C<NULL>.

I<basic_type> must be a class type.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_object"> native API.

=head2 new_object

C<void* (*new_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Calls C<new_object_no_mortal> and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* basic_type = env->get_basic_type(env, stack, "Int");
  void* object = env->new_object(env, stack, basic_type);

=head2 new_object_by_name

C<void* (*new_object_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Creates a new object given the basic type name I<basic_type_name>, and returns it.

The create object is pushed to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the creation of the object failed, an exception is thrown.

If an exception is thrown, C<error_id> is set to a non-zero value. Otherwise, it is set to 0.

Examples:

  int32_t error_id = 0;
  void* obj_point = env->new_object_by_name(env, stack, "Point", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 new_pointer_object_no_mortal

C<void* (*new_pointer_object_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, void* pointer);>

Calls L</"new_object_no_mortal"> native API and sets the pointer I<pointer> to a native data to the created object, and returns it.

This native API should not be used unless special purposes are intended. Normally, use L</"new_pointer_object"> native API.

=head2 new_pointer_object

C<void* (*new_pointer_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, void* pointer);>

Calls L</"new_pointer_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* basic_type = env->get_basic_type(env, stack, "MyTm");
  void* st_tm = env->new_memory_block(env, stack, sizeof (struct tm));
  void* obj_st_tm = env->new_pointer(env, stack, basic_type, st_tm);

=head2 new_pointer_object_by_name

C<void* (*new_pointer_object_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, void* pointer, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Calls L</"new_object_by_name"> native API and sets the pointer I<pointer> to a native data to the created object, and returns it.

  int32_t error_id = 0;
  void* minimal = env->new_pointer_object_by_name(env, stack, "TestCase::Pointer", pointer, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

=head2 get_pointer

C<void* (*get_pointer)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* pointer_object);>

Returns the value of the C<pointer> field of the object I<pointer_object>.

Examples:

  strcut tm* tm = (struct tm*)env->get_pointer(env, stack, obj_tm);

=head2 set_pointer

C<void (*set_pointer)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* pointer_object, void* pointer);>

Sets I<pointer> to the C<pointer> field of the object I<pointer_object>.

=head2 new_string_nolen_no_mortal

C<void* (*new_string_nolen_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* bytes);>

Creates a new string object given a C string I<bytes>. I<bytes> must end with C<\0>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_string_nolen"> native API.

=head2 new_string_nolen

C<void* (*new_string_nolen)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* bytes);>

Calls L</"new_string_nolen_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* str_obj = env->new_string_nolen(env, stack, "Hello World");

=head2 new_string_no_mortal

C<void* (*new_string_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* bytes, int32_t length);>

Creates a new string object given the C string I<bytes> and the length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

If the length of I<bytes> is lower than I<length> or I<bytes> is NULL, The part that longer than the length of I<bytes> is filled with C<\0>. 

This native API should not be used unless special purposes are intended. Normally, use L</"new_string"> native API.

=head2 new_string

C<void* (*new_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* bytes, int32_t length);>

Calls L</"new_string_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* str_obj = env->new_string(env, stack, "Hello \0World", 11);

=head2 new_byte_array_no_mortal

C<void* (*new_byte_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Creates a new array of the byte[] type given the length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_byte_array"> native API.

=head2 new_byte_array

C<void* (*new_byte_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Calls L</"new_byte_array_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* byte_array = env->new_byte_array(env, stack, 100);

=head2 new_short_array_no_mortal

C<void* (*new_short_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Creates a new array of the short[] type given the length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_short_array"> native API.

=head2 new_short_array

C<void* (*new_short_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Calls L</"new_short_array_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* short_array = env->new_short_array(env, stack, 100);

=head2 new_int_array_no_mortal

C<void* (*new_int_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Creates a new array of the int[] type given the length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_int_array"> native API.

=head2 new_int_array

C<void* (*new_int_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Calls L</"new_int_array_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* int_array = env->new_int_array(env, stack, 100);

=head2 new_long_array_no_mortal

C<void* (*new_long_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Creates a new array of the long[] type given the length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_long_array"> native API.

=head2 new_long_array

C<void* (*new_long_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Calls L</"new_long_array_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* long_array = env->new_long_array(env, stack, 100);

=head2 new_float_array_no_mortal

C<void* (*new_float_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Creates a new array of float[] type given the length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_float_array"> native API.

=head2 new_float_array

C<void* (*new_float_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Calls L</"new_float_array_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* float_array = env->new_float_array(env, stack, 100);

=head2 new_double_array_no_mortal

C<void* (*new_double_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Creates a new array of double[] type given the length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_double_array"> native API.

=head2 new_double_array

C<void* (*new_double_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Calls L</"new_double_array_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  void* double_array = env->new_double_array(env, stack, 100);

=head2 new_object_array_no_mortal

C<void* (*new_object_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t length);>

Creates a new array of an object type given the basic type I<basic_type> and the array length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_object_array"> native API.

=head2 new_object_array

C<void* (*new_object_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t length);>

Calls L</"new_object_array_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, stack, "Int");
  void* object_array = env->new_object_array(env, stack, basic_type_id, 100);

=head2 new_object_array_by_name

C<void* (*new_object_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Creates a new object array given the basic type name I<basic_type_name> and the array length I<length>, and returns it.

The created array is pushed to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the creation of the array failed, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If an exception is thrown, C<error_id> is set to a non-zero value. Otherwise, it is set to 0.

=head2 new_string_array

C<void* (*new_string_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Calls L</"new_string_array_no_mortal"> native API and calls L</"push_mortal"> native API given the return value.

=head2 new_muldim_array_no_mortal

C<void* (*new_muldim_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t type_dimension, int32_t length);>

Creates a new multi-dimensional array given the basic type I<basic_type>, the type dimension I<type_dimension>, and the array length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

I<type_dimension> must be less than or equals to 255.

This native API should not be used unless special purposes are intended. Normally, use L</"new_muldim_array"> native API.

=head2 new_muldim_array

C<void* (*new_muldim_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t type_dimension, int32_t length);>

Calls L</"new_muldim_array_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  // Creates 2-dimensional array - new Int[][100].
  int32_t basic_type_id = env->get_basic_type_id(env, stack, "Int");
  void* multi_array = env->new_muldim_array(env, stack, basic_type_id, 2, 100);

=head2 new_muldim_array_by_name

C<void* (*new_muldim_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Creates a new multi-dimensional array given the basic type name I<basic_type_name>, the type dimension I<type_dimension>, and the array length I<length>, and returns it.

The created array is pushed to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the creation of the array failed, an exception is thrown.

If an exception is thrown, C<error_id> is set to a non-zero value. Otherwise, it is set to 0.

=head2 new_mulnum_array_no_mortal

C<void* (*new_mulnum_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t length);>

Creates a new multi-numeric array given the basic type I<basic_type> and the array length I<length>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_mulnum_array"> native API.

=head2 new_mulnum_array

C<void* (*new_mulnum_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t length);>

Calls L</"new_mulnum_array_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, stack, "Complex_2d");
  void* value_array = env->new_mulnum_array(env, stack, basic_type_id, 100);

=head2 new_mulnum_array_by_name

C<void* (*new_mulnum_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Creates a new multi-numeric array given the basic type name I<basic_type_name>, the type dimension I<type_dimension>, and the array length I<length>, and returns it.

The created array is pushed to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the basic type given by I<basic_type_name> is not found, an exception is thrown.

If the creation of the array failed, an exception is thrown.

If an exception is thrown, C<error_id> is set to a non-zero value. Otherwise, it is set to 0.

=head2 new_array_proto_no_mortal

C<void* (*new_array_proto_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t length);>

Creates a new array given the prototype array I<array> and the length I<length>, and returns it.

If I<array> is C<NULL>, returns C<NULL>.

If the type of I<array> is not an array type, returns C<NULL>.

If I<length> is lower than 0, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_array_proto"> native API.

=head2 new_array_proto

C<void* (*new_array_proto)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array, int32_t length);>

Calls L</"new_array_proto_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 length

C<int32_t (*length)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Returns the value of C<length> member variable in L</"SPVM_OBJECT"> struct given the object I<object>.

I<object> must be defined.

If I<object> is an array, C<length> is its array length.

If I<object> is a string, C<length> is its string length.

Otherwise C<length> is 0.

Examples:

  int32_t length = env->length(env, stack, object);

=head2 get_elems_byte

C<int8_t* (*get_elems_byte)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array);>

Returns the pointer to the elements of the byte array I<array>.

Examples:

  int8_t* values = env->get_elems_byte(env, stack, array);
  values[3] = 5;

=head2 get_elems_short

C<int16_t* (*get_elems_short)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array);>

Returns the pointer to the elements of the short array I<array>.

Examples:

  int16_t* values = env->get_elems_short(env, stack, array);
  values[3] = 5;

=head2 get_elems_int

C<int32_t* (*get_elems_int)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array);>

Returns the pointer to the elements of the int array I<array>.

Examples:

  int32_t* values = env->get_elems_int(env, stack, array);
  values[3] = 5;

=head2 get_elems_long

C<int64_t* (*get_elems_long)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array);>

Returns the pointer to the elements of the long array I<array>.

Examples:

  int64_t* values = env->get_elems_long(env, stack, array);
  values[3] = 5;

=head2 get_elems_float

C<float* (*get_elems_float)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array);>

Returns the pointer to the elements of the float array I<array>.

Examples:

  float* values = env->get_elems_float(env, stack, array);
  values[3] = 1.5f;

=head2 get_elems_double

C<double* (*get_elems_double)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array);>

Returns the pointer to the elements of the double array I<array>.

Examples:

  double* values = env->get_elems_double(env, stack, array);
  values[3] = 1.5;

=head2 get_elem_object

C<void* (*get_elem_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array, int32_t index);>

Returns the element of the array I<array> at the index I<index>.

Examples:

  void* object = env->get_elem_object(env, stack, array, 3);

=head2 get_elem_string

C<void* (*get_elem_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array, int32_t index);>

Calls L</"get_elem_object"> native API, and returns its return value.

=head2 set_elem_object

C<void (*set_elem_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array, int32_t index, void* object);>

Sets I<object> to the element of the array I<array> at the index I<index>.

Examples:

  env->get_elem_object(env, stack, array, 3, object);

=head2 set_elem_string

C<void (*set_elem_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array, int32_t index, void* string);>

Calls L</"set_elem_object"> native API.

=head2 get_chars

C<const char* (*get_chars)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string_object);>

Returns the pointer to the characters stored in the string C<string_object>.

Examples:

  const char* chars = env->get_chars(env, stack, obj_string);

=head2 get_bool_object_value

C<int32_t (*get_bool_object_value)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* bool_object);>

Returns the value stored in L<Bool|SPVM::Bool> object I<bool_object>.

I<bool_object> must not be C<NULL>.

Examples:

  int32_t bool_value = env->get_bool_object_value(env, stack, bool_object);

=head2 concat_no_mortal

C<void* (*concat_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string1, void* string2);>

Creates a new string concating two strings I<string1> and I<string2>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"concat"> native API.

=head2 concat

C<void* (*concat)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string1, void* string2);>

Calls L</"concat_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 shorten

C<void (*shorten)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string, int32_t new_length);>

Shorten the string C<string> to the length I<length>.

Characters whose index is greater than I<length> are are filled with C<\0>.

If the string C<string> is C<NULL>, nothing is performed.

If the type of C<string> is not string type, nothing is performed.

If C<string> is read-only, nothing is performed.

If I<length> is not greater than or equal to 0, nothing is performed.

If I<length> is less than the length of I<string>, nothing is performed.

=head2 make_read_only

C<void (*make_read_only)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string)>

Makes the string I<string> read-only.

If I<string> is C<NULL>, no operation is performed.

=head2 is_read_only

C<void (*make_read_only)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string)>

If the string  I<string> is not C<NULL> and it is read-only, returns 1, otherwise returns 0.

=head2 print

C<void (*print)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string);>

Prints the string I<string> to L<SPVM's standard output|SPVM::Document::Language::System/"Standard Streams">.

=head2 print_stderr

C<void (*print_stderr)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string);>

Prints the string I<string> to L<SPVM's standard error|SPVM::Document::Language::System/"Standard Streams">.

If I<string> is NULL, this method produces no output.

=head2 dump_no_mortal

C<void* (*dump_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Performs the L<dump|SPVM::Document::Language::Operators/"dump"> operation, and returns its return value.

This native API should not be used unless special purposes are intended. Normally, use L</"dump"> native API.

=head2 dump

C<void* (*dump)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Calls L</"dump_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 dumpc

C<const char* (*dumpc)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Calls L</"dump"> native API and calls L</"get_chars"> native API given the return value of C<dump> to I<string>, and returns the return value of C<get_chars>.

=head2 copy_no_mortal

C<void* (*copy_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

The type of the object I<object> must be a string type, a numeric array type, or a multi-numeric array type.

If the type of the object I<object> is string type, creates a string and copies the characters stored in I<object> to the created string, and returns the created object.

If the type of the object I<object> is a numeric array type or a multi-numeric array type, creates an array using type of I<object> as a prototype and copies the elements stored in I<object> to the created array, and returns the created array.

If I<object> is C<NULL>, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"copy"> native API.

=head2 copy

C<void* (*copy)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Calls L</"copy_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 get_spvm_version_string

C<const char* (*get_spvm_version_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Returns the L<version string|SPVM::Document::Language::Class/"Version String"> of the SPVM language.

=head2 get_spvm_version_number

C<double (*get_spvm_version_number)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Calls L</"get_spvm_version_string"> native API and converts its return value to a double value.

=head2 get_version_string

C<const char* (*get_version_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the L<version string|SPVM::Document::Language::Class/"Version String"> of the basic type I<basic_type>.

If the version string is not defined, returns C<NULL>.

=head2 get_version_number

C<double (*get_version_number)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Calls L</"get_version_string"> native API and converts its return value to a double value.

If the version string is not defined, returns -1.

=head2 die

C<int32_t (*die)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* message, ...);>

Creates a string from a C<sprintf> formatted message I<message> given its parameters corresponding to its format specifiers, a function name, a file name, and a line number for an exception call stack.

And sets the created string to the L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable">, and return the basic type ID of L<Error|SPVM::Error> class. 

Examples:

  return env->die(env, stack, "The value must be %d.", 3, __func__, FILE_NAME, __LINE__);

=head2 get_exception

C<void* (*get_exception)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Returns the value of the L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable">.

The return value is a SVPM string.

=head2 set_exception

C<void (*set_exception)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* exception);>

Sets I<exception> to the L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable">.

I<exception> is an SPVM string.

=head2 new_stack_trace_no_mortal

C<void* (*new_stack_trace_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* exception, L<void* method|SPVM::Document::NativeAPI::Method>, int32_t line);>

Creates a new string adding a string line of a stack trace given the file I<file> and the line I<line> to the end of the exception I<exception>, and returns it.

If its memory allocation failed, returns C<NULL>.

I<exception> is an SPVM string. The return value is an SPVM string.

This native API should not be used unless special purposes are intended. Normally, use L</"new_stack_trace"> native API.

=head2 new_stack_trace

C<void* (*new_stack_trace)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* exception, L<void* method|SPVM::Document::NativeAPI::Method>, int32_t line);>

Calls L</"new_stack_trace_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 is_string

C<int32_t (*is_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

If the object I<object> is not C<NULL> and its type is string type, returns 1, otherwise returns 0.

=head2 is_class

C<int32_t (*is_class)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

If the object I<object> is not C<NULL> and its type is a class type, returns 1, otherwise returns 0.

=head2 is_pointer_class

C<int32_t (*is_pointer_class)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

If the object I<object> is not C<NULL> and the class of I<object> has the C<pointer> attribute, returns 1, otherwise returns 0.

=head2 is_array

C<int32_t (*is_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

If the object I<object> is not C<NULL> and its type is an array type, returns 1, otherwise returns 0.

=head2 is_object_array

C<int32_t (*is_object_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

If the object I<object> is not C<NULL> and its type is an object array type, returns 1, otherwise returns 0.

=head2 is_numeric_array

C<int32_t (*is_numeric_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

If the object I<object> is not C<NULL> and its type is a numeric array type, returns 1, otherwise returns 0.

=head2 is_mulnum_array

C<int32_t (*is_mulnum_array)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

If the object I<object> is not C<NULL> and its type is a multi-numeric array type, returns 1, otherwise returns 0.

=head2 isa

C<int32_t (*isa)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, void* basic_type, int32_t type_dimension);>

If the object I<object> satisfies the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> without data conversion to the type given by the basic type C<basic_type> and the type dimension C<type_dimension>, returns 1, otherwise returns 0.

=head2 isa_by_name

C<int32_t (*isa_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* basic_type_name, int32_t type_dimension);>

If the basic type given by the basic type name I<basic_type_name> is not found, returns 0.

If the object I<object> satisfies the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> without data conversion to the type given by the basic type name C<basic_type_name> and the type dimension C<type_dimension>, returns 1, otherwise returns 0.

=head2 is_type

C<int32_t (*is_type)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t type_dimension);>

If the type of the object I<object> is equal to the type given by the basic type I<basic_type> and the type dimension I<type_dimension>, returns 1, otherwise returns 0.

I<object> must not be C<NULL>.

=head2 is_type_by_name

C<int32_t (*is_type_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* basic_type_name, int32_t type_dimension);>

If the basic type given by the basic type name I<basic_type_name> is not found, returns 0.

If the object I<object> is not C<NULL> and its type of the object I<object> is equal to the basic type given by the basic type name I<basic_type_name> and the type dimension I<type_dimension>, returns 1, otherwise returns 0.

=head2 elem_isa

C<int32_t (*elem_isa)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array, void* element);>

If the element I<element> satisfies the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> without data conversion to the element type of the array I<array>, returns 1, otherwise returns 0.

=head2 get_elem_size

C<int32_t (*get_elem_size)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* array);>

Returns the byte size of the element of the array I<array>.

=head2 get_type_name_no_mortal

C<void* (*get_type_name_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Creates a new string that is the type name of the object I<object>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"get_type_name"> native API.

=head2 get_type_name

C<void* (*get_type_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Calls L</"get_type_name_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 get_compile_type_name_no_mortal

C<void* (*get_compile_type_name_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, int32_t type_dimension, int32_t type_flag);>

Creates a new string that is the the compile-time type name of the type given by the basic type name I<basic_type_name>, the type dimension I<type_dimension>, the type flag I<type_flag>, and returns it.

If its memory allocation failed, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"get_compile_type_name"> native API.

=head2 get_compile_type_name

C<void* (*get_compile_type_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name, int32_t type_dimension, int32_t type_flag);>

Calls L</"get_compile_type_name_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 enter_scope

C<int32_t (*enter_scope)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Performs an L<enterring scope|SPVM::Document::Language::GarbageCollection/"Entering Scope"> operation and returns the top position of the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">. This value is used as an argument to L</"leave_scope"> native API.

=head2 leave_scope

C<void (*leave_scope)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t mortal_stack_top);>

Performs a L<leaving scope operation|SPVM::Document::Language::GarbageCollection/"Leaving Scope"> given the top position of the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack"> I<mortal_stack_top>.

Normally, I<mortal_stack_top> is a return value from L</"enter_scope"> native API.

=head2 push_mortal

C<int32_t (*push_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Pushes the object I<object> to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">.

If I<object> is NULL, no operation is performed.

If successful, returns 0. Otherwise, returns a non-zero value.

=head2 weaken

C<int32_t (*weaken)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void** ref);>

Weakens the reference C<ref>.

I<ref> must not be C<NULL>.

If the object referenced by I<ref> is C<NULL>, no operation is performed.

If I<ref> is already weakened, no operation is performed.

See the doc of L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference"> about weak references.

=head2 isweak 

C<int32_t (*isweak()SPVM_ENV* env, void** ref);>

If the reference C<ref> is weakened, returns 1, otherwise returns 0.

I<ref> must not be C<NULL>.

If the object referenced by I<ref> is C<NULL>, returns 0.

See the doc of L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference"> about weak references.

=head2 unweaken

C<void (*unweaken)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void** ref);>

Unweakens the reference C<ref>.

I<ref> must not be C<NULL>.

If the object referenced by I<ref> is C<NULL>, no operation is performed.

If I<ref> is not weakened, no operation is performed.

See the doc of L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference"> about weak references.

=head2 strerror_string

C<void* (*strerror_string)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t errno_value, int32_t length);>

Calls the L</"strerror"> function and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 strerror_string_nolen

C<void* (*strerror_string_nolen)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t errno_value);>

Calls the L</"strerror_string"> function given 0 to I<length>, and returns its return value.

=head2 strerror

C<const char* (*strerror)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t errno_value, int32_t length);>

Returns the return value of the L<strerror|https://linux.die.net/man/3/strerror> function in the C language.

If the length is 0, the length is set to 128.

If the C<strerror> function failed, C<errno> is set to the a positive value.

This native API is thread-safe.

This native API is implemented by the following functions:

Windows:

L<strerror_s|https://learn.microsoft.com/ja-jp/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s?view=msvc-170>

Linux and UNIX:

L<strerror_r - XSI-compliant|https://linux.die.net/man/3/strerror_r>

=head2 strerror_nolen

C<const char* (*strerror_nolen)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t errno_value);>

Calls the L</"strerror"> function given 0 to I<length>, and returns its return value.

=head2 is_binary_compatible_object

C<int32_t (*is_binary_compatible_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

If the object I<object> is binary compatible with the runtime environment I<runtime> and the runtime stack I<stack>, returns 1, otherwise returns 0.

=head2 reserved195

C<void* reserved195;>

Reserved for the future use.

=head2 new_stack

C<SPVM_VALUE* (*new_stack)(SPVM_ENV* env);>

Creates a new L<runtime stack|SPVM::Document::NativeClass/"Runtime Stack">, and returns it.

=head2 free_stack

C<void (*free_stack)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Frees the L<runtime stack|SPVM::Document::NativeClass/"Runtime Stack"> I<stack>.

=head2 get_field_object_defined_and_has_pointer_by_name

C<void* (*get_field_object_defined_and_has_pointer_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Calls L</"get_field_object_by_name"> native API, and returns its return value.

If the return value is C<NULL>, an exception is thrown.

If the pointer stored in the return value is C<NULL>, an exception is thrown.

=head2 get_field_object_ref

C<void** (*get_field_object_ref)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the address where the value of the field I<field> is stored.

=head2 get_field_object_ref_by_name

C<void** (*get_field_object_ref_by_name)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Searches a field field given the object I<object> and the field name I<field_name>.

If it is found, the address where the value of the field I<field> is stored. Otherwise, an exception is thrown.

The function name I<func_name>, the file path I<file>, and the line number I<line> must be given for the exception stack trace.

If the field given by I<field_name> is not found, an exception is thrown.

If an excetpion is thrown, the value referenced by C<error_id> is set to a non-zero value. Otherwise, set to 0.

=head2 is_binary_compatible_stack

C<int32_t (*is_binary_compatible_stack)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

If the runtime stack I<stack> is binary compatible with the runtime environment I<runtime>, returns 1, otherwise returns 0.

=head2 assign_object

C<void (*assign_object)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void** ref, void* object);>

Assigns the object C<object> to the place referenced by the reference C<ref>.

This native API should not be used unless special purposes are intended.

=head2 new_string_array_no_mortal

C<void* (*new_string_array_no_mortal)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, int32_t length);>

Creates a new string array given the length I<length>, and returns it.

This native API should not be used unless special purposes are intended. Normally, use L</"new_string_array"> native API.

=head2 new_memory_block

C<void* (*new_memory_block)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, size_t size);>

Creates a new memory block given the byte size I<size> and returns its address.

If I<size> is 0, retunrs C<NULL>.

If I<size> is greater than C<SIZE_MAX> defined in the sysmte, returns C<NULL>.

If the system memory allocation function returns C<NULL>, this native API returns C<NULL>.

The count of the memory blocks managed by this runtime is incremented by 1.

=head2 free_memory_block

C<void (*free_memory_block)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* block);>

Frees the memory block I<block>.

If I<block> is C<NULL>, no operation is performed.

The count of the memory blocks managed by this runtime is decremented by 1.

=head2 get_memory_blocks_count

C<int32_t (*get_memory_blocks_count)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Returns the count of the memory blocks managed by this runtime.

=head2 say

C<void (*say)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string);>

Prints the string I<string> and C<\n> to L<SPVM's standard output|SPVM::Document::Language::System/"Standard Streams">.

=head2 warn

C<void (*warn)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* string, const char* basic_type_name, const char* method_name, const char* file, int32_t line);>

Performs the L<warn|SPVM::Document::Language::Operators/"warn"> operation given the string I<string>, the basic type name I<basic_type_name>, the method name I<method_name>, the file path I<file>, and the line number I<line>.

=head2 spvm_stdin

C<FILE* (*spvm_stdin)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Returns L<SPVM's standard input|SPVM::Document::Language::System/"Standard Streams">.

=head2 spvm_stdout

C<FILE* (*spvm_stdout)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Returns L<SPVM's standard output|SPVM::Document::Language::System/"Standard Streams">.

=head2 spvm_stderr

C<FILE* (*spvm_stderr)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Returns L<SPVM's standard error|SPVM::Document::Language::System/"Standard Streams">.

=head2 check_bootstrap_method

C<int32_t (*check_bootstrap_method)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* basic_type_name);>

Checks the definition of the L<bootstrap method|SPVM::Document::Language::Class/"Bootstrap Method">.

If it is invalid, an exception is thrown.

If an exception is thrown, returns a non-zero value. Otherwise, returns 0.

=head2 new_array_proto_element_no_mortal

C<void* (*new_array_proto_element_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* element, int32_t length);>

Creates a new array given the prototype element I<element> and the length I<length>, and returns it.

If I<element> is C<NULL>, returns C<NULL>.

If the type of I<element> must be an object type.

If I<length> is lower than 0, returns C<NULL>.

This native API should not be used unless special purposes are intended. Normally, use L</"new_array_proto_element"> native API.

=head2 new_array_proto_element

C<void* (*new_array_proto_element)(SPVM_ENV* env, SPVM_VALUE* stack, void* element, int32_t length);>

Calls L</"new_array_proto_element_no_mortal"> native API and push its return value to the L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">, and returns it.

=head2 get_byte_object_value

C<int32_t (*get_byte_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* byte_object);>

Returns the value of the C<value> field of L<Byte|SPVM::Byte> object I<byte_object>.

I<byte_object> must be a L<Byte|SPVM::Byte> object.

=head2 get_short_object_value

C<int32_t (*get_short_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* short_object);>

Returns the value of the C<value> field of L<Short|SPVM::Short> object I<short_object>.

I<short_object> must be a L<Short|SPVM::Short> object.

=head2 get_int_object_value

C<int32_t (*get_int_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* int_object);>

Returns the value of the C<value> field of L<Int|SPVM::Int> object I<int_object>.

I<int_object> must be an L<Int|SPVM::Int> object.

=head2 get_long_object_value

C<int64_t (*get_long_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* long_object);>

Returns the value of the C<value> field of L<Long|SPVM::Long> object I<long_object>.

I<long_object> must be a L<Long|SPVM::Long> object.

=head2 get_float_object_value

C<float (*get_float_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* float_object);>

Returns the value of the C<value> field of L<Float|SPVM::Float> object I<float_object>.

I<float_object> must be a L<Float|SPVM::Float> object.

=head2 get_double_object_value

C<double (*get_double_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* double_object);>

Returns the value of the C<value> field of L<Double|SPVM::Double> object I<double_object>.

I<double_object> must be a L<Double|SPVM::Double> object.

=head1 Native API IDs

Native APIs have its IDs.

  0 runtime
  1 api
  2 new_env,
  3 free_env,
  4 call_init_methods,
  5 set_command_info_program_name,
  6 set_command_info_argv,
  7 set_command_info_base_time,
  8 destroy_class_vars,
  9 args_width,
  10 get_object_basic_type,
  11 get_object_basic_type_id,
  12 get_object_basic_type_name,
  13 get_object_type_dimension,
  14 get_basic_type,
  15 get_basic_type_by_name,
  16 get_basic_type_by_id,
  17 get_basic_type_id,
  18 get_basic_type_id_by_name,
  19 get_class_var,
  20 get_class_var_byte,
  21 get_class_var_short,
  22 get_class_var_int,
  23 get_class_var_long,
  24 get_class_var_float,
  25 get_class_var_double,
  26 get_class_var_object,
  27 get_class_var_string,
  28 set_class_var_byte,
  29 set_class_var_short,
  30 set_class_var_int,
  31 set_class_var_long,
  32 set_class_var_float,
  33 set_class_var_double,
  34 set_class_var_object,
  35 set_class_var_string,
  36 get_class_var_object_ref,
  37 get_class_var_byte_by_name,
  38 get_class_var_short_by_name,
  39 get_class_var_int_by_name,
  40 get_class_var_long_by_name,
  41 get_class_var_float_by_name,
  42 get_class_var_double_by_name,
  43 get_class_var_object_by_name,
  44 get_class_var_string_by_name,
  45 set_class_var_byte_by_name,
  46 set_class_var_short_by_name,
  47 set_class_var_int_by_name,
  48 set_class_var_long_by_name,
  49 set_class_var_float_by_name,
  50 set_class_var_double_by_name,
  51 set_class_var_object_by_name,
  52 set_class_var_string_by_name,
  53 get_field,
  54 get_field_static,
  55 get_field_byte,
  56 get_field_short,
  57 get_field_int,
  58 get_field_long,
  59 get_field_float,
  60 get_field_double,
  61 get_field_object,
  62 get_field_string,
  63 set_field_byte,
  64 set_field_short,
  65 set_field_int,
  66 set_field_long,
  67 set_field_float,
  68 set_field_double,
  69 set_field_object,
  70 set_field_string,
  71 get_field_byte_by_name,
  72 get_field_short_by_name,
  73 get_field_int_by_name,
  74 get_field_long_by_name,
  75 get_field_float_by_name,
  76 get_field_double_by_name,
  77 get_field_object_by_name,
  78 get_field_string_by_name,
  79 set_field_byte_by_name,
  80 set_field_short_by_name,
  81 set_field_int_by_name,
  82 set_field_long_by_name,
  83 set_field_float_by_name,
  84 set_field_double_by_name,
  85 set_field_object_by_name,
  86 set_field_string_by_name,
  87 get_field_string_chars_by_name,
  88 get_method,
  89 get_class_method,
  90 get_instance_method_static,
  91 get_instance_method,
  92 call_method_no_mortal,
  93 call_method,
  94 call_class_method_by_name,
  95 call_instance_method_static_by_name,
  96 call_instance_method_by_name,
  97 new_object_no_mortal,
  98 new_object,
  99 new_object_by_name,
  100 new_pointer_object_no_mortal,
  101 new_pointer_object,
  102 new_pointer_object_by_name,
  103 get_pointer,
  104 set_pointer,
  105 new_string_nolen_no_mortal,
  106 new_string_nolen,
  107 new_string_no_mortal,
  108 new_string,
  109 new_byte_array_no_mortal,
  110 new_byte_array,
  111 new_short_array_no_mortal,
  112 new_short_array,
  113 new_int_array_no_mortal,
  114 new_int_array,
  115 new_long_array_no_mortal,
  116 new_long_array,
  117 new_float_array_no_mortal,
  118 new_float_array,
  119 new_double_array_no_mortal,
  120 new_double_array,
  121 new_object_array_no_mortal,
  122 new_object_array,
  123 new_object_array_by_name,
  124 new_string_array,
  125 new_muldim_array_no_mortal,
  126 new_muldim_array,
  127 new_muldim_array_by_name,
  128 new_mulnum_array_no_mortal,
  129 new_mulnum_array,
  130 new_mulnum_array_by_name,
  131 new_array_proto_no_mortal,
  132 new_array_proto,
  133 length,
  134 get_elems_byte,
  135 get_elems_short,
  136 get_elems_int,
  137 get_elems_long,
  138 get_elems_float,
  139 get_elems_double,
  140 get_elem_object,
  141 get_elem_string,
  142 set_elem_object,
  143 set_elem_string,
  144 get_chars,
  145 get_bool_object_value,
  146 concat_no_mortal,
  147 concat,
  148 shorten,
  149 make_read_only,
  150 is_read_only,
  151 print,
  152 print_stderr,
  153 dump_no_mortal,
  154 dump,
  155 dumpc,
  156 copy_no_mortal,
  157 copy,
  158 get_spvm_version_string,
  159 get_spvm_version_number,
  160 get_version_string,
  161 get_version_number,
  162 die,
  163 get_exception,
  164 set_exception,
  165 new_stack_trace_no_mortal,
  166 new_stack_trace,
  167 is_string,
  168 is_class,
  169 is_pointer_class,
  170 is_array,
  171 is_object_array,
  172 is_numeric_array,
  173 is_mulnum_array,
  174 isa,
  175 isa_by_name,
  176 is_type,
  177 is_type_by_name,
  178 elem_isa,
  179 get_elem_size,
  180 get_type_name_no_mortal,
  181 get_type_name,
  182 get_compile_type_name_no_mortal,
  183 get_compile_type_name,
  184 enter_scope,
  185 leave_scope,
  186 push_mortal,
  187 weaken,
  188 isweak,
  189 unweaken,
  190 strerror_string,
  191 strerror_string_nolen,
  192 strerror,
  193 strerror_nolen,
  194 is_binary_compatible_object,
  195 is_binary_compatible_stack,
  196 new_stack,
  197 free_stack,
  198 get_field_object_defined_and_has_pointer_by_name,
  199 get_field_object_ref,
  200 get_field_object_ref_by_name,
  201 check_bootstrap_method
  202 assign_object,
  203 new_string_array_no_mortal,
  204 new_memory_block,
  205 free_memory_block,
  206 get_memory_blocks_count,
  207 say,
  208 warn,
  209 spvm_stdin,
  210 spvm_stdout,
  211 spvm_stderr,
  212 new_array_proto_element_no_mortal
  213 new_array_proto_element
  214 get_byte_object_value
  215 get_short_object_value
  216 get_int_object_value
  217 get_long_object_value
  218 get_float_object_value
  219 get_double_object_value

=head1 Constant Values

=head2 Basic Type IDs

=begin html

<table>
  <tr>
    <th>ID</th><th>Name</th><th>Description</th>
  </tr>
  <tr>
    <td>0</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN</td><td>The basic type ID for unknown types</td>
  </tr>
  <tr>
    <td>1</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF</td><td>The basic type ID of the undef type</td>
  </tr>
  <tr>
    <td>2</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_VOID</td><td>The basic type ID of the void type</td>
  </tr>
  <tr>
    <td>3</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE</td><td>The basic type ID of byte type</td>
  </tr>
  <tr>
    <td>4</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT</td><td>The basic type ID of short type</td>
  </tr>
  <tr>
    <td>5</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_INT</td><td>The basic type ID of int type</td>
  </tr>
  <tr>
    <td>6</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_LONG</td><td>The basic type ID of long type</td>
  </tr>
  <tr>
    <td>7</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT</td><td>The basic type ID of float type</td>
  </tr>
  <tr>
    <td>8</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE</td><td>The basic type ID of double type</td>
  </tr>
  <tr>
    <td>9</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_STRING</td><td>The basic type ID of string type</td>
  </tr>
  <tr>
    <td>10</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT</td><td>The basic type ID of the any object type</td>
  </tr>
  <tr>
    <td>11</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Byte">Byte</a> class</td>
  </tr>
  <tr>
    <td>12</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Short">Short</a> class</td>
  </tr>
  <tr>
    <td>13</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Int">Int</a> class</td>
  </tr>
  <tr>
    <td>14</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Long">Long</a> class</td>
  </tr>
  <tr>
    <td>15</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Float">Float</a> class</td>
  </tr>
  <tr>
    <td>16</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Double">Double</a> class</td>
  </tr>
  <tr>
    <td>17</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Bool">Bool</a> class</td>
  </tr>
  <tr>
    <td>18</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Error">Error</a> class</td>
  </tr>
  <tr>
    <td>19</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Error::System">Error::System</a> class</td>
  </tr>
  <tr>
    <td>20</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Error::NotSupported">Error::NotSupported</a> class</td>
  </tr>
  <tr>
    <td>21</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_COMMAND_INFO_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::CommandInfo">CommandInfo</a> class</td>
  </tr>
  <tr>
    <td>22</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_ADDRESS_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Address">Address</a> class</td>
  </tr>
  <tr>
    <td>23</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_COMPILE_CLASS</td><td>The basic type ID of the <a href="https://metacpan.org/pod/SPVM::Error::Compile">Error::Compile</a> class</td>
  </tr>
</table>

=end html

=head2 Basic Type Category IDs

=begin html

<table>
  <tr>
    <th>ID</th><th>Name</th><th>Description</th>
  </tr>
  <tr>
    <td>0</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN</td><td>The basic type category for unknown types</td>
  </tr>
  <tr>
    <td>1</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNDEF</td><td>The basic type category for the undef type</td>
  </tr>
  <tr>
    <td>2</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID</td><td>The basic type category for the void type</td>
  </tr>
  <tr>
    <td>3</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC</td><td>The basic type category for numeric types</td>
  </tr>
  <tr>
    <td>4</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM</td><td>The basic type category for multi-numeric types</td>
  </tr>
  <tr>
    <td>5</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING</td><td>The basic type category for string type</td>
  </tr>
  <tr>
    <td>6</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS</td><td>The basic type category for class types</td>
  </tr>
  <tr>
    <td>7</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE</td><td>The basic type category for interface types</td>
  </tr>
  <tr>
    <td>8</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT</td><td>The basic type category for the any object type</td>
  </tr>
</table>

=end html

=head2 Type Flag IDs

=begin html

<table>
  <tr>
    <th>ID</th><th>Name</th><th>Description</th>
  </tr>
  <tr>
    <td>1</td><td>SPVM_NATIVE_C_TYPE_FLAG_REF</td><td>A flag indicating that it is a reference type</td>
  </tr>
  <tr>
    <td>2</td><td>SPVM_NATIVE_C_TYPE_FLAG_MUTABLE</td><td>A flag indicating that a mutable modifier is present</td>
  </tr>
</table>

=end html

=head2 SPVM_NATIVE_VERSION_NUMBER

C<SPVM_NATIVE_VERSION_NUMBER>

The version number of the SPVM language.

Examples:
  
  // 0.989062
  double spvm_version_number = SPVM_NATIVE_VERSION_NUMBER;

=head2 SPVM_NATIVE_VERSION_STRING

C<SPVM_NATIVE_VERSION_STRING>

The version string of the SPVM language. This is a constant string.

Examples:
  
  // "0.989062"
  const char* spvm_version_string = SPVM_NATIVE_VERSION_STRING;

=head1 Macro Functions

=head2 spvm_warn

C<#define spvm_warn(format, ...)>

Prints the formatted message I<format> to C<stderr> with the current function name, the current file name, and the current line number.

I<format> must be the C<char*> type.

Examples:

  spvm_warn("Hello");
  spvm_warn("Hello %s%d", "Foo", 3);

=head2 spvm_warnf

C<#define spvm_warnf(stream, format, ...)>

Prints the formatted message I<format> to the stream I<stream> with the current function name, the current file name, and the current line number.

I<format> must be the C<char*> type.

I<stream> must be C<FILE> type.

Examples:

  spvm_warnf(env->spvm_stderr(env, stack), "Hello");
  spvm_warnf(env->spvm_stderr(env, stack), "Hello %s%d", "Foo", 3);

=head2 SPVM_NATIVE_GET_POINTER

C<#define SPVM_NATIVE_GET_POINTER(object)>

Returns the pointer stored in the object I<object> and returns it.

The return type is the C<void*> type.

=head2 SPVM_NATIVE_SET_POINTER

C<#define SPVM_NATIVE_SET_POINTER(object, pointer)>

Sets the pointer I<pointer> of the object I<object>.

=head1 Data Structures

=head2 SPVM_OBJECT

C<SPVM_OBJECT> is an internal data structure for an SPVM object.

  typedef struct spvm_object SPVM_OBJECT
  struct spvm_object {
    void* pointer;
    SPVM_WEAKEN_BACKREF* weaken_backref_head;
    SPVM_RUNTIME_BASIC_TYPE* basic_type;
    int32_t ref_count;
    uint8_t type_dimension;
    uint8_t flag;
    int32_t length;
  };

=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI::Allocator>

=item * L<SPVM::Document::NativeAPI::StringBuffer>

=item * L<SPVM::Document::NativeAPI::Compiler>

=item * L<SPVM::Document::NativeAPI::ClassFile>

=item * L<SPVM::Document::NativeAPI::Runtime>

=item * L<SPVM::Document::NativeAPI::BasicType>

=item * L<SPVM::Document::NativeAPI::ClassVariable>

=item * L<SPVM::Document::NativeAPI::Field>

=item * L<SPVM::Document::NativeAPI::Method>

=item * L<SPVM::Document::NativeAPI::Argument>

=item * L<SPVM::Document::NativeAPI::Type>

=item * L<SPVM::Document::NativeAPI::Internal>

=item * L<SPVM::Document::NativeAPI::Mutex>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=item * L<Examples using SPVM native APIs|https://github.com/yuki-kimoto/SPVM/tree/master/examples/native>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
