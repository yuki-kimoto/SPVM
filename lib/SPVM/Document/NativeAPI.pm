=head1 Name

SPVM::Document::NativeAPI - Native APIs

=head1 Description

The native APIs of L<SPVM> are the APIs written by the C language for various operations.

These APIs are used in L<native classes|SPVM::Document::NativeClass>.

=head1 Native APIs

=head2 runtime

C<void* runtime;>

The runtime object for this environment.

Examples:

  env->runtime;

=head2 api

C<void* api;>

Access to other native APIs.

=head3 Allocator Native API
  
  env->api->allocator;

L<SPVM::Document::NativeAPI::Allocator>

=head3 String Buffer Native API

  env->api->string_buffer;

L<SPVM::Document::NativeAPI::StringBuffer>

=head3 Compiler Native API

  env->api->compiler;

L<SPVM::Document::NativeAPI::Compiler>

=head3 Class File Native API

  env->api->class_file;

L<SPVM::Document::NativeAPI::ClassFile>

=head3 Runtime Native API

  env->api->runtime;

L<SPVM::Document::NativeAPI::Runtime>

=head3 Basic Type Native API

  env->api->basic_type;

L<SPVM::Document::NativeAPI::BasicType>

=head3 Class Variable Native API

  env->api->clsas_var;

L<SPVM::Document::NativeAPI::ClassVariable>

=head3 Field Native API

  env->api->field;

L<SPVM::Document::NativeAPI::Field>

=head3 Method Native API

  env->api->method;

L<SPVM::Document::NativeAPI::Method>

=head3 Argument Native API

  env->api->arg;

L<SPVM::Document::NativeAPI::Argument>

=head3 Type Native API

  env->api->type;

L<SPVM::Document::NativeAPI::Type>

=head3 Internal Native API

  env->api->internal;

L<SPVM::Document::NativeAPI::Internal>

=head3 Mutex Native API

  env->api->mutex;

L<SPVM::Document::NativeAPI::Mutex>

=head2 new_env

C<SPVM_ENV* (*new_env)();>

Creates a new environment.

=head2 free_env

C<void (*free_env)(SPVM_ENV* env);>

Frees an environment.

=head2 call_init_methods
  
C<int32_t (*call_init_methods)(SPVM_ENV* env, SPVM_VALUE* stack);>

Calls all C<INIT> methods defined by C<INIT> blocks.

If an exception is thrown, returns non-zero value. Otherwise returns 0.

=head2 set_command_info_program_name

C<int32_t (*set_command_info_program_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* obj_program_name);>

Sets the L<CommandInfo->PROGRAM_NAME|SPVM::CommandInfo/"PROGRAM_NAME"> class variable to the program name.

If an exception is thrown, returns non-zero value. Otherwise returns 0.

=head2 set_command_info_argv

C<int32_t (*set_command_info_argv)(SPVM_ENV* env, SPVM_VALUE* stack, void* obj_argv);>

Sets the L<CommandInfo->PROGRAM_NAME|SPVM::CommandInfo/"ARGV"> class variable to the command line arguments.

If an exception is thrown, returns non-zero value. Otherwise returns 0.

=head2 set_command_info_base_time

C<int32_t (*set_command_info_base_time)(SPVM_ENV* env, SPVM_VALUE* stack, int64_t base_time);>

Sets the L<CommandInfo->BASE_TIME|SPVM::CommandInfo/"BASE_TIME"> class variable to the time when the program starts.

If an exception is thrown, returns non-zero value. Otherwise returns 0.

=head2 destroy_class_vars
  
C<void (*destroy_class_vars)(SPVM_ENV* env, SPVM_VALUE* stack);>

Destroys all class variables.

=head2 args_width

C<int32_t (*args_width)(SPVM_ENV* env, SPVM_VALUE* stack);>

Returns the total width of the arguments given by the caller.

Examples:

  int32_t args_width = env->args_width(env, stack);

=head2 get_object_basic_type

C<void* (*get_object_basic_type)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the object.

=head2 get_object_basic_type_id

C<int32_t (*get_object_basic_type_id)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

Returns the basic type ID of the object.

=head2 get_object_basic_type_name

C<const char* (*get_object_basic_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

Returns the basic type name of the object.

=head2 get_object_type_dimension

C<int32_t (*get_object_type_dimension)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

Returns the type dimension of the object.

=head2 get_basic_type

C<void* (*get_basic_type)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);>

Gets a L<basic type|SPVM::Document::NativeAPI::BasicType> by a basic type name.

=head2 get_basic_type_by_name

C<void* (*get_basic_type_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets a L<basic type|SPVM::Document::NativeAPI::BasicType> by a basic type name.

If an exception is thrown, C<error_id> is set to non-zero value. Otherwise it is set to 0.

=head2 get_basic_type_by_id

C<void* (*get_basic_type_by_id)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id);>

Gets a L<basic type|SPVM::Document::NativeAPI::BasicType> by a basic type ID.

=head2 get_basic_type_id

C<int32_t (*get_basic_type_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);>

Gets a basic type ID by a basic type name.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, stack, "Int");

=head2 get_basic_type_id_by_name

C<int32_t (*get_basic_type_id_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets a basic type ID by a basic type name.

If an exception is thrown, C<error_id> is set to non-zero value. Otherwise it is set to 0.

=head2 get_class_var

C<void* (*get_class_var)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name);>

Gets a L<class variable|SPVM::Document::NativeAPI::ClassVariable> object by its basic type name and class variable name, and returns it.

If the class variable does not exist, returns NULL.

Examples:

  void* class_var = env->get_class_var(env, stack, "MyClass", "$VAR");

=head2 get_class_var_byte

C<int8_t (*get_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);>

Gets the value of a class variable of the byte type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_class_var_short

C<int16_t (*get_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);>

Gets the value of a class variable of the short type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_class_var_int

C<int32_t (*get_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);>

Gets the value of a class variable of the int type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_class_var_long

C<int64_t (*get_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);>

Gets the value of a class variable of the long type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_class_var_float

C<float (*get_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);>

Gets the value of a class variable of the float type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_class_var_double

C<double (*get_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);>

Gets the value of a class variable of the double type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_class_var_object

C<void* (*get_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);>

Gets the value of a class variable of the object type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_class_var_strig

The same as L</"get_class_var_object">.

=head2 get_class_var_object_ref

C<void** (*get_class_var_object_ref)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);>

Gets the address of the value of a class variable of the object type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 set_class_var_byte

C<void (*set_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int8_t value);>

Sets the value of a class variable of the byte type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 set_class_var_short

C<void (*set_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int16_t value);>

Sets the value of a class variable of the short type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 set_class_var_int

C<void (*set_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int32_t value);>

Sets the value of a class variable of the int type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 set_class_var_long

C<void (*set_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int64_t value);>

Sets the value of a class variable of the long type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 set_class_var_float

C<void (*set_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, float value);>

Sets the value of a class variable of the float type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 set_class_var_double

C<void (*set_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, double value);>

Sets the value of a class variable of the double type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 set_class_var_object

C<void (*set_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, void* value);>

Sets the value of a class variable of the object type.

The argument C<class_var> must be a valid L<class variable|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 set_class_var_string

The same as L</"set_class_var_object">.

=head2 get_class_var_byte_by_name

C<int8_t (*get_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a class variable of the byte type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int8_t value = env->get_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_short_by_name

C<int16_t (*get_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a class variable of the short type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int16_t value = env->get_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_int_by_name

C<int32_t (*get_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a class variable of the int type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int8_t value = env->get_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_long_by_name

C<int64_t (*get_class_var_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a class variable of the long type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int64_t value = env->get_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_float_by_name

C<float (*get_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a class variable of the float type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  float value = env->get_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_double_by_name

C<double (*get_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a class variable of the double type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  double value = env->get_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_object_by_name

C<void* (*get_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a class variable of the object type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:
  
  int32_t error_id = 0;
  void* value = env->get_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_class_var_string_by_name

The same as L</"get_class_var_object_by_name">.

=head2 set_class_var_byte_by_name

C<void (*set_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a class variable of the byte type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_byte_by_name(env, stack, "TestCase::NativeAPI", "$BYTE_VALUE", 15, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_short_by_name

C<void (*set_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a class variable of the short type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_short_by_name(env, stack, "TestCase::NativeAPI", "$SHORT_VALUE", 15, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_int_by_name

C<void (*set_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a class variable of the int type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_int_by_name(env, stack, "TestCase::NativeAPI", "$INT_VALUE", 15, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_long_by_name

C<void (*set_class_var_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a class variable of the long type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_long_by_name(env, stack, "TestCase::NativeAPI", "$LONG_VALUE", 15, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_float_by_name

C<void (*set_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a class variable of the float type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_float_by_name(env, stack, "TestCase::NativeAPI", "$FLOAT_VALUE", 15, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_double_by_name

C<void (*set_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a class variable of the double type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_double_by_name(env, stack, "TestCase::NativeAPI", "$DOUBLE_VALUE", 15, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_object_by_name

C<void (*set_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a class variable of the object type by its basic type name and class variable name.

If an excetpion is thrown because the class variable does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_class_var_object_by_name(env, stack, "TestCase::NativeAPI", "$MINIMAL_VALUE", minimal, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_class_var_string_by_name

The same as L</"set_class_var_object_by_name">.

=head2 get_field

C<void* (*get_field_by_index)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name);>

Gets a L<field|SPVM::Document::NativeAPI::Field> object by its basic type name of the object and field name, and returns it.

If the field does not exist, returns NULL.

Examples:

  void* field = env->get_field(env, stack, object, "x");

=head2 get_field_static

C<void* (*get_field_static)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name);>

Gets a L<field|SPVM::Document::NativeAPI::Field> object by its basic type name and field name, and returns it.

If the field does not exist, returns NULL.

Examples:

  void* field = env->get_field_static(env, stack, "Point", "x");

=head2 get_field_byte

C<int8_t (*get_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);>

Gets the value of a field of the byte type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_field_short

C<int16_t (*get_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);>

Gets the value of a field of the short type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_field_int

C<int32_t (*get_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);>

Gets the value of a field of the int type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_field_long

C<int64_t (*get_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);>

Gets the value of a field of the long type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_field_float

C<float (*get_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);>

Gets the value of a field of the float type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_field_double

C<double (*get_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);>

Gets the value of a field of the double type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_field_object

C<void* (*get_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);>

Gets the value of a field of the object type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_field_string

The same as L<"get_field_object">.

=head2 set_field_byte

C<void (*set_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int8_t value);>

Sets the value of a field of the byte type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 set_field_short

C<void (*set_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int16_t value);>

Sets the value of a field of the short type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 set_field_int

C<void (*set_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int32_t value);>

Sets the value of a field of the int type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 set_field_long

C<void (*set_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int64_t value);>

Sets the value of a field of the long type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 set_field_float

C<void (*set_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, float value);>

Sets the value of a field of the float type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 set_field_double

C<void (*set_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, double value);>

Sets the value of a field of the double type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 set_field_object

C<void (*set_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, void* value);>

Sets the value of a field of the object type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 set_field_string

The same as L<"set_field_object">.

=head2 get_field_byte_by_name

C<int8_t (*get_field_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a field of the byte type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int8_t byte_value = env->get_field_byte_by_name(env, stack, object, "byte_value", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_short_by_name

C<int16_t (*get_field_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a field of the short type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int8_t short_value = env->get_field_short_by_name(env, stack, object, "short_value", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_int_by_name

C<int32_t (*get_field_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a field of the int type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int8_t int_value = env->get_field_int_by_name(env, stack, object, "int_value", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_long_by_name

C<int64_t (*get_field_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a field of the long type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int8_t long_value = env->get_field_long_by_name(env, stack, object, "long_value", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_float_by_name

C<float (*get_field_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a field of the float type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int8_t float_value = env->get_field_float_by_name(env, stack, object, "float_value", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_double_by_name

C<double (*get_field_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a field of the double type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  int8_t double_value = env->get_field_double_by_name(env, stack, object, "double_value", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_object_by_name

C<void* (*get_field_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the value of a field of the object type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  void* object_minimal = env->get_field_object_by_name(env, stack, object_simple, "object_value", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_field_string_by_name

The same as L</"get_field_object_by_name">.

=head2 set_field_byte_by_name

C<void (*set_field_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a field of the byte type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_byte_by_name(env, stack, object, "byte_value", 13, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_short_by_name

C<void (*set_field_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a field of the short type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_short_by_name(env, stack, object, "short_value", 13, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_int_by_name

C<void (*set_field_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a field of the int type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_int_by_name(env, stack, object, "int_value", 13, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_long_by_name

C<void (*set_field_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a field of the long type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_long_by_name(env, stack, object, "long_value", 13, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_float_by_name

C<void (*set_field_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a field of the float type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_float_by_name(env, stack, object, "float_value", 13, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_double_by_name

C<void (*set_field_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a field of the double type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_double_by_name(env, stack, object, "double_value", 13, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_object_by_name

C<void (*set_field_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Sets the value of a field of the object type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

Examples:

  int32_t error_id = 0;
  env->set_field_object_by_name(env, stack, object_simple, "object_value", object_minimal, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 set_field_string_by_name

The same as L</"set_field_object_by_name">.

=head2 get_method

C<void* (*get_method)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);>

Returns a method given a basic type name and a method name. If the method does not exists, returns NULL.

Examples:

  void* method = env->get_method(env, stack, "Foo", "get");

=head2 get_class_method

C<void* (*get_class_method)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);>

Returns a class method given a basic type name and a method name. If the class method does not exists, returns NULL.

Examples:

  void* method = env->get_class_method(env, stack, "Foo", "get");

=head2 get_instance_method

C<void* (*get_instance_method)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* method_name);>

Gets an instance method address by the object and the method name. If the instance method does not exist, a negative value is returned.

Examples:

  void* method = env->get_instance_method(env, stack, object, "get");

=head2 new_object_no_mortal

C<void* (*new_object_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);>

Creates a new object with a basic type. The basic type must be the correct basic type ID return by the L</"get_basic_type_id"> Native API.

=head2 new_object

C<void* (*new_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);>

The same as C<new_object_no_mortal>, and add the created object to the mortal stack of the environment. Use this function in normal use instead of C<new_object_no_mortal>.

Examples:

  void* basic_type = env->get_basic_type(env, stack, "Int");
  void* object = env->new_object(env, stack, basic_type);

=head2 new_byte_array_no_mortal

C<void* (*new_byte_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

Creates a new byte[] type array by specifying the length.

=head2 new_byte_array

C<void* (*new_byte_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

The same as C<new_byte_array_no_mortal>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_byte_array_no_mortal>.

Examples:

  void* byte_array = env->new_byte_array(env, stack, 100);

=head2 new_short_array_no_mortal

C<void* (*new_short_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

Creates a new short[] type array by specifying the length.

=head2 new_short_array

C<void* (*new_short_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

The same as C<new_short_array_no_mortal>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_short_array_no_mortal>.

Examples:

  void* short_array = env->new_short_array(env, stack, 100);

=head2 new_int_array_no_mortal

C<void* (*new_int_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

Creates a new int[] type array by specifying the length.

=head2 new_int_array

C<void* (*new_int_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

The same as C<new_int_array_no_mortal>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_int_array_no_mortal>.

Examples:

  void* int_array = env->new_int_array(env, stack, 100);

=head2 new_long_array_no_mortal

C<void* (*new_long_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

Creates a new long[] type array by specifying the length.

=head2 new_long_array

C<void* (*new_long_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

The same as C<new_long_array_no_mortal>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_long_array_no_mortal>.

Examples:

  void* long_array = env->new_long_array(env, stack, 100);

=head2 new_float_array_no_mortal

C<void* (*new_float_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

Creates a new float[] type array by specifying the length.

=head2 new_float_array

C<void* (*new_float_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

The same as C<new_float_array_no_mortal>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_float_array_no_mortal>.

Examples:

  void* float_array = env->new_float_array(env, stack, 100);

=head2 new_double_array_no_mortal

C<void* (*new_double_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

Creates a new double[] type array by specifying the length.

=head2 new_double_array

C<void* (*new_double_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

The same as C<new_double_array_no_mortal>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_double_array_no_mortal>.

Examples:

  void* double_array = env->new_double_array(env, stack, 100);

=head2 new_object_array_no_mortal

C<void* (*new_object_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);>

Creates a new object type array by specifying the basic type and the array length. The basic type must be the correct basic type got by the L</"get_basic_type"> Native API.

=head2 new_object_array

C<void* (*new_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);>

The same as C<new_object_array_no_mortal>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_object_array_no_mortal>.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, stack, "Int");
  void* object_array = env->new_object_array(env, stack, basic_type_id, 100);

=head2 new_muldim_array_no_mortal

C<void* (*new_muldim_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t type_dimension, int32_t length);>

Creates a new multi-dimensional array by specifying the basic type and the type dimension, and the array length. The basic type must be the correct basic type got bu the L</"get_basic_type_id"> Native API. the type dimension of the element must be less than or equals to 255.

=head2 new_muldim_array

C<void* (*new_muldim_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t type_dimension, int32_t length);>

The same as C<new_muldim_array_no_mortal>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_muldim_array_no_mortal>.

Examples:

  // Creates 2-dimensional array - The same as "new Int[][100]".
  int32_t basic_type_id = env->get_basic_type_id(env, stack, "Int");
  void* multi_array = env->new_muldim_array(env, stack, basic_type_id, 2, 100);

=head2 new_mulnum_array_no_mortal

C<void* (*new_mulnum_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);>

Creates a new multi-numeric array by specifying the basic type and the array length. The basic type must be the correct basic type got by the L</"basic_type_id"> Native API.

=head2 new_mulnum_array

C<void* (*new_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);>

The same as C<new_mulnum_array_no_mortal>, and add the created array to the mortal stack of the environment. Use this function in normal use instead of C<new_mulnum_array_no_mortal>.

Examples:

  int32_t basic_type_id = env->get_basic_type_id(env, stack, "Complex_2d");
  void* value_array = env->new_mulnum_array(env, stack, basic_type_id, 100);

=head2 new_string_nolen_no_mortal

C<void* (*new_string_nolen_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);>

Creates a new string object by specifying C language char* type value. this value must end with "\0".

=head2 new_string_nolen

C<void* (*new_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);>

The same as C<new_string_nolen_no_mortal>, and push the created object to the mortal stack. Use this function in normal use instead of C<new_string_nolen_no_mortal>.

Examples:

  void* str_obj = env->new_string_nolen(env, stack, "Hello World");

=head2 new_string_no_mortal

C<void* (*new_string_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);>

Creates a new string object with the bytes and the length.

If the length of bytes is lower than the specified length or the bytes is NULL, The part that longer than the length of bytes will be filled with C<\0>. 

=head2 new_string

C<void* (*new_string)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);>

The same as C<new_string_no_mortal>, and push the created object to the mortal stack. Usually use this function instead of C<new_string_no_mortal>.

Examples:

  void* str_obj = env->new_string(env, stack, "Hello \0World", 11);

=head2 concat_no_mortal

C<void* (*concat_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);>

Concats two strings.

=head2 concat

C<void* (*concat)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);>

The same as C<concat_no_mortal>, and push the created object to the mortal stack. Use this function in normal use instead of C<concat_no_mortal>.

=head2 new_stack_trace_no_mortal

C<void* (*new_stack_trace_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, void* method, int32_t line);>

Creates a string object that represents a stack trace by adding the file and line the method is called to the end of the exception message.

=head2 new_stack_trace

C<void* (*new_stack_trace)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, void* method, int32_t line);>

The same as L</"new_stack_trace_no_mortal">, and push the created object to the mortal stack.

=head2 length

C<int32_t (*length)(SPVM_ENV*, void* array);>

If you specify an array, the length of the array is returned.

Examples:

  int32_t length = env->length(env, stack, array);

=head2 get_elems_byte

C<int8_t* (*get_elems_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);>

If you specify a byte[] type array, the pointer at the beginning of the internally stored C language int8_t[] type array is returned.  

Examples:

  int8_t* values = env->get_elems_byte(env, stack, array);
  values[3] = 5;

=head2 get_elems_short

C<int16_t* (*get_elems_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);>

If a short[] type array is specified, the pointer at the beginning of the internally stored C language int16_t[] type array is returned.

Examples:

  int16_t* values = env->get_elems_short(env, stack, array);
  values[3] = 5;

=head2 get_elems_int

C<int32_t* (*get_elems_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);>

When an int[] type array is specified, the pointer at the beginning of the internally stored C language int32_t[] type array is returned.

Examples:

  int32_t* values = env->get_elems_int(env, stack, array);
  values[3] = 5;

=head2 get_elems_long

C<int64_t* (*get_elems_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);>

When a long[] type array is specified, the pointer at the beginning of the internally stored C language int64_t[] type array is returned.

Examples:

  int64_t* values = env->get_elems_long(env, stack, array);
  values[3] = 5;

=head2 get_elems_float

C<float* (*get_elems_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);>

When a float[] type array is specified, the pointer at the beginning in the C language float[] type array internally held is returned.

Examples:

  float* values = env->get_elems_float(env, stack, array);
  values[3] = 1.5f;

=head2 get_elems_double

C<double* (*get_elems_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);>

If a double[] type array is specified, the pointer at the beginning of the internally stored C double[] type array is returned.

Examples:

  double* values = env->get_elems_double(env, stack, array);
  values[3] = 1.5;

=head2 get_elem_object

C<void* (*get_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index);>

Gets an object of an element given an array of object types and a methodscript. If the element is a weak reference, the weak reference is removed.

Examples:

  void* object = env->get_elem_object(env, stack, array, 3);

=head2 set_elem_object

C<void (*set_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* object);>

If you specify an array of object type and methodscript and element objects, the element object is assigned to the corresponding methodscript position. If the element's object has a weak reference, the weak reference is removed. The reference count of the originally assigned object is decremented by 1.

Examples:

  env->get_elem_object(env, stack, array, 3, object);

=head2 get_pointer

C<void* (*get_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object);>

Specifies a pointer object and return the C language pointer stored inside the object.

Examples:

  strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, stack, tm_obj);

=head2 set_pointer

C<void (*set_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object, void* pointer);>

If you specify a pointer object and a C language pointer, the C language pointer is saved in the internal data of the pointer type object.

=head2 call_method_no_mortal

C<int32_t (*call_method_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* method, int32_t args_width);>

Call a method by specifying the method address and the stack length of the argument. If an exception occurs in the method, The return value is 1. If not, return 0.

The return value of the method is set to stack[0].

=head2 get_exception

C<void* (*get_exception)(SPVM_ENV* env, SPVM_VALUE* stack);>

Gets a exception message which type is byte[].

=head2 set_exception

C<void (*set_exception)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception);>

Sets a exception message which type is byte[].

=head2 enter_scope

C<int32_t (*enter_scope)(SPVM_ENV* env, SPVM_VALUE* stack);>

Creates a new scope and return the scope ID.

=head2 push_mortal

C<int32_t (*push_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

Add an object to the mortal stack.

If this method succeed, return 0.

If this method don't alloc memory for new mortal information, return 1.

=head2 leave_scope

C<void (*leave_scope)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t scope_id);>

Specifies a scope ID to exit that scope and decrement the object's reference count stored in the mortal stack. Objects with a reference count of 0 are released. The scope ID must be the ID obtained by the enter_scope function.

=head2 isa

C<int32_t (*isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* cast_basic_type, int32_t cast_type_dimension);>

Checks if the object C<object> can be assigned to the type given by the basic type C<cast_basic_type> and the type dimension C<cast_type_dimension>.

If it is ok, returns 1. Otherwise returns 0.

=head2 elem_isa

C<int32_t (*elem_isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, void* element);>

Checks if the element C<element> can be assigned to the element of the array C<array>.

If it is ok, returns 1. Otherwise returns 0.

=head2 is_type

C<int32_t (*is_type)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* basic_type, int32_t type_dimension);>

Given an object and a basic type and a type dimension, returns a nonzero value if the object matches both the basic type and the type dimension, and 0 otherwise.

=head2 is_object_array

C<int32_t (*is_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

If the object is a object array, returns 1, otherwise returns 0.

If the object is C<NULL>, returns 0.

=head2 weaken

C<int32_t (*weaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** ref);>

Weakens the reference C<ref>.

=head2 isweak 

C<int32_t (*isweak()SPVM_ENV* env, void** ref);>

Checks if the reference C<ref> is weakend. If so, returns 1, otherwise, returns 0.

=head2 unweaken

C<void (*unweaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** ref);>

Unweakens the reference C<ref>.

=head2 get_type_name_no_mortal

C<void* (*get_type_name_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

Gets a new C<string> object that is the type name of the object.

This function does not add the returned object to the mortal stack, so use the L<get_type_name> Native API for normal use to avoid memory leaks.

=head2 get_type_name

C<void* (*get_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

Gets a new C<string> object that is the type name of the object.

=head2 get_chars

C<const char* (*get_chars)(SPVM_ENV* env, SPVM_VALUE* stack, void* string_object);>

Gets characters in the string object.

Examples:

C<const char* bytes = env->get_chars(env, stack, string_object);>

=head2 die

C<int32_t (*die)(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...);>

Creates a C<sprintf> formatted message with file name and line number and set it to the exception.

Last three arguments are the function name, the file name, and the line number.

Returns value is the basic type ID of the L<Error|SPVM::Error> class. 

Examples:

  return env->die(env, stack, "Value must be %d", 3, __func__, __FILE__, __LINE__);

=head2 new_object_by_name

C<void* (*new_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

This is the same as the L</"new_object"> Native API, but you can specify basic type name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

Examples:

  int32_t error_id = 0;
  void* minimal = env->new_object_by_name(env, stack, "TestCase::Minimal", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 call_class_method_by_name

C<void (*call_class_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Calls a class method given the basic type name and method name.

Examples:
  
  int32_t error_id = 0;
  int32_t output;
  {
    int32_t args_width = 1;
    stack[0].ival = 5;
    env->call_class_method_by_name(env, stack, "TestCase::NativeAPI", "my_value", args_width, &error_id, __func__, __FILE__, __LINE__);
    if (error_id) { return error_id; }
    
    output = stack[0].ival;
  }

=head2 call_instance_method_by_name

C<void (*call_instance_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Calls an instance method given the method name.

=head2 get_field_string_chars_by_name

C<const char* (*get_field_string_chars_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

=head2 dump_no_mortal

C<void* (*dump_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

Gets the string which dump the object. The string is the same as the return value of C<dump> operator.

=head2 dump

C<void* (*dump)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

The same as C<dump_no_mortal>, and push the created object to the mortal stack. Use this function in normal use instead of C<dump_no_mortal>.

=head2 get_instance_method_static

C<void* (*get_instance_method_static)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);>

Returns an instance method given a basic type name and a method name. If the instance method does not exists, returns NULL.

Examples:
  
  void* method = env->get_instance_method_static(env, stack, "Foo", "get");

=head2 get_bool_object_value

C<int32_t (*get_bool_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* bool_object);>

Gets the value of a L<Bool|SPVM::Bool> object. If the Bool object is true, return 1, otherwise return 0.

Examples:

  int32_t bool_value = env->get_bool_object_value(env, stack, bool_object);

=head2 make_read_only

C<void (*make_read_only)(SPVM_ENV* env, SPVM_VALUE* stack, void* string)>

Make the string read-only.

=head2 is_read_only

C<void (*make_read_only)(SPVM_ENV* env, SPVM_VALUE* stack, void* string)>

If the string is read-only, returns 1, otherwise returns 0.

=head2 is_array

C<int32_t (*is_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

If the object is an array, returns 1, otherwise returns 0.

If the object is C<NULL>, returns 0.

=head2 is_string

C<int32_t (*is_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

If the object is a string, returns 1, otherwise returns 0.

If the object is C<NULL>, returns 0.

=head2 is_numeric_array

C<int32_t (*is_numeric_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

If the object is a numeric array, returns 1, otherwise returns 0.

If the object is C<NULL>, returns 0.

=head2 is_mulnum_array

C<int32_t (*is_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

If the object is a multi numeric array, returns 1, otherwise returns 0.

If the object is C<NULL>, returns 0.

=head2 get_elem_size

C<int32_t (*get_elem_size)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);>

Gets the byte size of the element of the array.

=head2 new_array_proto

C<void* (*new_array_proto)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t length);>

Creates a new array that have the type of the given array and the given length.

The given array must be the object that is an array type.

If the given array is L<NULL>, returns C<NULL>.

If the given length is lower than 0, returns C<NULL>.

=head2 copy

C<void* (*copy)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

Copy the object. The type of the object must be a string type, a numeric array, or a multi numeric array.

If the given object is L<NULL>, returns L<NULL>.

=head2 shorten

C<void (*shorten)(SPVM_ENV* env, SPVM_VALUE* stack, void* string, int32_t new_length);>

Shorten the string with the given length.

If the string is null, does nothing.

If the given length is greater than the length of the string, does nothing.

If the given length is lower than 0, the given length become 0.

The charaters of the after the given length are filled with C<\0>.

=head2 print

C<void (*print)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);>

Prints a string to stdout. This is the same operator as the print operator.

=head2 print_stderr

C<void (*print_stderr)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);>

Prints a string to stderr. This is the same operator as the print operator except for the destination of the output.

=head2 new_stack

C<SPVM_VALUE* (*new_stack)(SPVM_ENV* env);>

=head2 free_stack

C<void (*free_stack)(SPVM_ENV* env, SPVM_VALUE* stack);>

=head2 new_memory_block

C<void* (*new_memory_block)(SPVM_ENV* env, SPVM_VALUE* stack, size_t size);>

Creates a new memory block that is managed by the call stack with the byte size and return the address. If it fails, return C<NULL>.

The count of the memory block that is managed by the stack is incremented by 1.

The count of the memory block that is managed by the environment is incremented by 1.

=head2 free_memory_block

C<void (*free_memory_block)(SPVM_ENV* env, SPVM_VALUE* stack, void* block);>

Frees the memory block that is managed by the call stack.

The count of the memory block that is managed by the stack is decremented by 1.

The count of the memory block that is managed by the environment is decremented by 1.

=head2 get_memory_blocks_count

C<int32_t (*get_memory_blocks_count)(SPVM_ENV* env, SPVM_VALUE* stack);>

Returns the count of memory blocks the current runtime allocates.

=head2 strerror_string

C<void* (*strerror_string)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);>

The same as the L</"strerror"> function, but return a string object.

=head2 strerror_string_nolen

C<void* (*strerror_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);>

Calls the L</"strerror_string"> function given I<length> 0, and returns its return value.

=head2 strerror

C<const char* (*strerror)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);>

Returns the return value of the L<strerror|https://linux.die.net/man/3/strerror> function in the C language.

If the length is 0, the length is set to 128.

If the C<strerror> function failed, C<errno> is set to the an appropriate positive value.

This function is thread-safe.

This function actually is implemented by the following functions:

Windows:

C<errno_t L<strerror_s|https://learn.microsoft.com/ja-jp/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s?view=msvc-170>(char *buffer, size_t sizeInBytes, int errnum);>

Other OSs:

C<int L<strerror_r|https://linux.die.net/man/3/strerror_r>(int errnum, char *buf, size_t buflen); /* XSI-compliant */>

=head2 strerror_nolen

C<const char* (*strerror_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);>

Calls the L</"strerror"> function given I<length> 0, and returns its return value.

=head2 new_string_array

C<void* (*new_string_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

Calls the L</"new_string_array_no_mortal"> native API and calls the L</"push_mortal/"> native API given the return value.

=head2 new_string_array_no_mortal

C<void* (*new_string_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);>

Creates a new string array.

=head2 dumpc

C<const char* (*dumpc)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

The alias for the following code using L</"dump">.

  const char* ret = env->get_chars(env, stack, env->dump(env, stack, object));

=head2 new_pointer_object_no_mortal

C<void* (*new_pointer_object_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, void* pointer);>

Creates a pointer object by specifying a basic type and a C language pointer. The basic type must be the correct basic type got by the L</"get_basic_type"> Native API.

=head2 new_pointer_object

C<void* (*new_pointer_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, void* pointer);>

The same as L</"new_pointer_no_mortal">, and push the created object to the mortal stack. Use this function in normal use instead of C<new_pointer_no_mortal>.

Examples:

  void* basic_type = env->get_basic_type(env, stack, "MyTime");
  void* pointer = malloc(sizeof (struct tm));
  void* pointer_obj = env->new_pointer(env, stack, basic_type, pointer);

=head2 new_pointer_object_by_name

C<void* (*new_pointer_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, void* pointer, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

This is the same as L</"new_pointer"> function, but you can specify basic type name directly.

If function is succeeded, C<error> is set to 0. If a exception occurs, C<error> is set to 1. 

  int32_t error_id = 0;
  void* minimal = env->new_pointer_by_name(env, stack, "TestCase::Pointer", pointer, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

=head2 get_elem_string

C<void* (*get_elem_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index);>

The same as L</"get_elem_object">.

=head2 set_elem_string

C<void (*set_elem_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* string);>

The same as L</"set_elem_object">.

=head2 is_class

C<int32_t (*is_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

If the object is an instance of a class, returns 1, otherwise returns 0.

If the object is C<NULL>, returns 0.

=head2 is_pointer_class

C<int32_t (*is_pointer_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);>

If the object is an instance of a pointer class, returns 1, otherwise returns 0.

If the object is C<NULL>, returns 0.

=head2 call_instance_method_static_by_name

C<void (*call_instance_method_static_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Calls an instance method by the basic type name and the method name.

Examples:
  
  int32_t error_id = 0;
  int32_t output;
  {
    int32_t args_width = 1;
    stack[0].oval = obj_point;
    env->call_instance_method_static_by_name(env, stack, "Point", "x", args_width, &error_id, __func__, __FILE__, __LINE__);
    if (error_id) { return error_id; }
    output = stack[0].ival;
  }

=head2 get_compile_type_name_no_mortal

C<void* (*get_compile_type_name_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag);>

Gets a new C<string> object that is the compile-time type name with a basic type name, a type dimension, a type flag.

This function does not add the returned object to the mortal stack, so use the L<get_compile_type_name> Native API for normal use to avoid memory leaks.

=head2 get_compile_type_name

C<void* (*get_compile_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag);>

Gets a new C<string> object that is the compile-time type name with a basic type name, a type dimension, a type flag.

=head2 get_spvm_version_string

  const char* (*get_spvm_version_string)(SPVM_ENV* env, SPVM_VALUE* stack);

Returns the L<version string|SPVM::Document::Language/"Version String"> of the SPVM language.

=head2 get_spvm_version_number

C<double (*get_spvm_version_number)(SPVM_ENV* env, SPVM_VALUE* stack);>

Returns the L<version number|SPVM::Document::Language/"Version Number"> of the SPVM language.

=head2 get_version_string

  const char* (*get_version_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);

Returns the version string of a basic_type. The C<basic_type_id> must be a valid basic type.

If the version string in the basic_type is not defined, returns NULL.

=head2 get_version_number

C<double (*get_version_number)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);>

Returns the version number of a basic_type. The C<basic_type_id> must be a valid basic type.

If the version string in the basic_type is not defined, returns -1.

=head2 call_method

C<int32_t (*call_method)(SPVM_ENV* env, SPVM_VALUE* stack, void* method, int32_t args_width);>

Call a method by specifying the method address and the stack length of the argument. If an exception occurs in the method, The return value is 1. If not, return 0.

The return value of the method is set to stack[0].

If stack[0] is a value of an object type, the object is pushed to the mortal stack.

=head2 isa_by_name

C<int32_t (*isa_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* basic_type_name, int32_t type_dimension);>

The feature is the same as the L</"isa">, but the basic type name can be given. If the basic type name is not found, returns 0.

=head2 is_type_by_name

C<int32_t (*is_type_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* basic_type_name, int32_t type_dimension);>

The feature is the same as the L</"is_type">, but the basic type name can be given. If the basic type name is not found, returns 0.

=head2 new_stack_trace_raw_by_name

C<void* (*new_stack_trace_raw_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, const char* basic_type_name, const char* method_name, int32_t line);>

Creates a string object that represents a stack trace by adding the file and line the method is called to the end of the exception message.

=head2 new_stack_trace_by_name

C<void* (*new_stack_trace_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, const char* basic_type_name, const char* method_name, int32_t line);>

The same as L</"new_stack_trace_raw_by_name">, and push the created object to the mortal stack.

=head2 new_object_array_raw_by_name

C<void* (*new_object_array_raw_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length);>

=head2 new_object_array_by_name

C<void* (*new_object_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length);>

=head2 new_muldim_array_raw_by_name

C<void* (*new_muldim_array_raw_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t element_dimension, int32_t length);>

=head2 new_muldim_array_by_name

C<void* (*new_muldim_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t element_dimension, int32_t length);>

=head2 new_mulnum_array_raw_by_name

C<void* (*new_mulnum_array_raw_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length);>

=head2 new_mulnum_array_by_name

C<void* (*new_mulnum_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length);>

=head2 get_field_object_defined_and_has_pointer_by_name

C<void* (*get_field_object_defined_and_has_pointer_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file_name, int32_t line);>

=head2 get_field_object_ref

C<void** (*get_field_object_ref)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);>

Gets the address of the value of a field of the object type.

The argument C<field> must be a valid L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_field_object_ref_by_name

C<void** (*get_field_object_ref_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);>

Gets the address of the value of a field of the object type by its basic type name of the object and field name.

If an excetpion is thrown because the field does not exist or other errors occur, the argument C<error_id> is set to non-zero value. Otherwise set to 0.

=head2 check_stack_env

C<int32_t (*check_stack_env)(SPVM_ENV* env, SPVM_VALUE* stack);>

If the env of the stack is equal to the env, returns 1. Otherwise returns 0.

=head2 assign_object

C<void (*assign_object)(SPVM_ENV* env, SPVM_VALUE* stack, void** ref, void* object);>

Assigns an object C<object> to the place referred by the reference C<ref>.

=head2 say

C<void (*say)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);>

Prints a string and C<\n> to stdout. This is the same operator as the say operator.

=head2 warn

C<void (*warn)(SPVM_ENV* env, SPVM_VALUE* stack, void* string, const char* class_dir, const char* class_rel_file, int32_t line);>

Operates the warn operator.

=head2 spvm_stdin

C<FILE* (*spvm_stdin)(SPVM_ENV* env, SPVM_VALUE* stack);>

Gets the standard input opened for SPVM.

=head2 spvm_stdout

C<FILE* (*spvm_stdout)(SPVM_ENV* env, SPVM_VALUE* stack);>

Gets the standard output opened for SPVM.

=head2 spvm_stderr

C<FILE* (*spvm_stderr)(SPVM_ENV* env, SPVM_VALUE* stack);>

Gets the standard error opened for SPVM.

=head1 Native API IDs

Native APIs have its IDs. These IDs are permanently same for the binary compatibility after the future release C<v1.0>.

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
  194 reserved194,
  195 reserved195,
  196 new_stack,
  197 free_stack,
  198 get_field_object_defined_and_has_pointer_by_name,
  199 get_field_object_ref,
  200 get_field_object_ref_by_name,
  201 check_stack_env,
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
    <td>3</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE</td><td>The basic type ID of the byte type</td>
  </tr>
  <tr>
    <td>4</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT</td><td>The basic type ID of the short type</td>
  </tr>
  <tr>
    <td>5</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_INT</td><td>The basic type ID of the int type</td>
  </tr>
  <tr>
    <td>6</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_LONG</td><td>The basic type ID of the long type</td>
  </tr>
  <tr>
    <td>7</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT</td><td>The basic type ID of the float type</td>
  </tr>
  <tr>
    <td>8</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE</td><td>The basic type ID of the double type</td>
  </tr>
  <tr>
    <td>9</td><td>SPVM_NATIVE_C_BASIC_TYPE_ID_STRING</td><td>The basic type ID of the string type</td>
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
    <td>5</td><td>SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING</td><td>The basic type category for the string type</td>
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

The version number of the SPVM language.

Examples:
  
  // 0.989062
  double spvm_version_number = SPVM_NATIVE_VERSION_NUMBER;

=head2 SPVM_NATIVE_VERSION_STRING

The version string of the SPVM language. This is a string constant.

Examples:
  
  // "0.989062"
  const char* spvm_version_string = SPVM_NATIVE_VERSION_STRING;

=head1 Macro Functions

=head2 spvm_warn

  #define spvm_warn(format, ...)

Prints the formatted message I<format> to C<stderr> with a new line.

I<format> must be the C<char*> type.

Examples:

  spvm_warn("Hello");
  spvm_warn("Hello %s%d", "Foo", 3);

=head2 spvm_warnf

  #define spvm_warnf(stream, format, ...)

Prints the formatted message I<format> to the stream I<stream> with a new line.

I<format> must be the C<char*> type.

I<stream> must be the C<FILE> type.

Examples:

  spvm_warnf(env->spvm_stderr(env, stack), "Hello");
  spvm_warnf(env->spvm_stderr(env, stack), "Hello %s%d", "Foo", 3);

=head2 SPVM_NATIVE_GET_POINTER

C<#define SPVM_NATIVE_GET_POINTER(object)>

Gets the pointer stored in the object I<object> and returns it. The return type is the void* type.

=head2 SPVM_NATIVE_SET_POINTER

C<#define SPVM_NATIVE_SET_POINTER(object, pointer)>

Sets the pointer I<pointer> in the object I<object>.

=head1 Examples

=over 2

=item * L<Examples using SPVM native APIs|https://github.com/yuki-kimoto/SPVM/tree/master/examples/native>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
