=head1 Name

SPVM::Document::NativeAPI::Runtime - SPVM Runtime Native APIs

=head1 Usage

  // Runtime Native API
  SSPVM_API_RUNTIME* runtime_api = env->api->runtime;
  
  // New a runtime object
  void* runtime = runtime_api->new_instance();
  
  // Free a runtime object
  env->api->runtime->free_instance(runtime);

=head1 Description

SPVM Runtime Native APIs are the APIs to manipulate runtime information.

=head1 IDs of Runtime Native APIs

Runtime native APIs have its IDs.

  0  new_instance
  1  free_instance
  2  get_opcodes
  3  reserved3
  4  reserved4
  5  reserved5
  6  reserved6
  7  reserved7
  8  reserved8
  9  reserved9
  10 reserved10
  11 
  12 reserved12
  13 
  14 reserved14
  15 reserved15
  16 reserved16
  17 reserved17
  18 reserved18
  19 reserved19
  20 reserved20
  21 reserved21
  22 reserved22
  23 reserved23
  24 reserved24
  25 reserved25
  26 reserved26
  27 reserved27
  28 reserved28
  29 reserved29
  30 reserved30
  31 reserved31
  32 
  33 reserved33
  34 
  35 reserved35
  36 reserved36
  37 reserved37
  38 
  39 reserved39
  40 reserved40
  41 reserved41
  42 reserved42
  43 get_method_name
  44 reserved44
  45 reserved45
  46 get_method_is_class_method
  47 get_method_is_anon
  48 get_method_is_native
  49 get_method_is_precompile
  50 get_method_byte_vars_width
  51 get_method_short_vars_width
  52 get_method_int_vars_width
  53 get_method_long_vars_width
  54 get_method_float_vars_width
  55 get_method_double_vars_width
  56 get_method_object_vars_width
  57 get_method_ref_vars_width
  58 get_method_mortal_stack_length
  59 reserved59
  60 get_method_opcodes_length
  61 reserved61
  62 get_method_args_length
  63 reserved63
  64 reserved64
  65 get_native_method_address
  66 set_native_method_address
  67 get_precompile_method_address
  68 set_precompile_method_address
  69 object_header_size
  70 object_weaken_backref_head_offset
  71 object_ref_count_offset
  72 reserved72
  73 reserved73
  74 reserved74
  75 object_length_offset
  76 reserved76
  77 reserved77
  78 reserved78
  79 get_method_required_args_length
  80 reserved80
  81 get_method_is_enum
  82 reserved82
  83 is_object_type
  84 reserved84
  85 reserved85
  86 can_assign
  87 
  88 
  89 
  90 reserved90
  91 
  92 reserved92
  93 
  94 reserved94
  95 
  96 reserved96
  97 reserved97
  98 reserved98
  99   get_basic_types_length
  100   
  101   
  102   
  103   
  104   
  105   
  106   get_method_return_basic_type
  107   get_method_return_type_dimension
  108   get_method_return_type_flag
  109   
  110   
  111   
  112   get_method_current_basic_type
  113   
  114   
  115   
  116   
  117   get_basic_type_by_id
  118   
  119   get_method_by_index
  120   reserved120,
  121   reserved121
  122   
  123   
  124   get_method_by_name
  125   
  126   reserved126
  127   get_method_index
  128   reserved128,
  129   
  130   
  131   
  132   
  133   get_basic_type_by_name

=head1 Runtime Native APIs

=head2 new_instance

  void* (*new_instance)(void);

=head2 free_instance

  void (*free_instance)(void* runtime);

=head2 get_opcodes

  int32_t* (*get_opcodes)(void* runtime);

=head2 get_basic_types_length

  int32_t (*get_basic_types_length)(void* runtime);
  
=head2 get_method_return_basic_type

  void* (*get_method_return_basic_type)(void* runtime, void* method);
  
=head2 get_method_return_type_dimension

  int32_t (*get_method_return_type_dimension)(void* runtime, void* method);
  
=head2 get_method_return_type_flag

  int32_t (*get_method_return_type_flag)(void* runtime, void* method);
  
=head2 get_method_current_basic_type

  void* (*get_method_current_basic_type)(void* runtime, void* method);
  
=head2 get_basic_type_by_id

  void* (*get_basic_type_by_id)(void* runtime, int32_t basic_type_id);
  
=head2 get_method_by_index

  void* (*get_method_by_index)(void* runtime, void* basic_type, int32_t method_index);
  
=head2 get_method_by_name

  void* (*get_method_by_name)(void* runtime, void* basic_type, const char* method_name);
  
=head2 get_method_index

  int32_t (*get_method_index)(void* runtime, void* method);
  
=head2 get_basic_type_by_name

  void* (*get_basic_type_by_name)(void* runtime, const char* basic_type_name);
  
=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
