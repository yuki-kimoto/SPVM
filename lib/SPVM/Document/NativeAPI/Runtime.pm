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
  2  
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
  43 
  44 reserved44
  45 reserved45
  46 
  47 
  48 
  49 
  50 
  51 
  52 
  53 
  54 
  55 
  56 
  57 
  58 
  59 reserved59
  60 
  61 reserved61
  62 
  63 reserved63
  64 reserved64
  65 
  66 
  67 
  68 
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
  79 
  80 reserved80
  81 
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
  106   
  107   
  108   
  109   
  110   
  111   
  112   
  113   
  114   
  115   
  116   
  117   get_basic_type_by_id
  118   
  119   
  120   reserved120,
  121   reserved121
  122   
  123   
  124   
  125   
  126   reserved126
  127   
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

=head2 get_basic_types_length

  int32_t (*get_basic_types_length)(void* runtime);
  
=head2 get_basic_type_by_id

  void* (*get_basic_type_by_id)(void* runtime, int32_t basic_type_id);
  
=head2 get_basic_type_by_name

  void* (*get_basic_type_by_name)(void* runtime, const char* basic_type_name);
  
=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
