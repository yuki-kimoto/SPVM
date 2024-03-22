package SPVM::Native::Constant;



1;

=head1 Name

SPVM::Native::Constant - Constant Values in Native APIs

=head1 Description

The Native::Constant class in L<SPVM> has methods to get constant values in native APIs.

=head1 Usage

  use Native::Constant;

=head1 Enumerations

=head2 Basic Type IDs

  enum {
    SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN,
    SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF,
    SPVM_NATIVE_C_BASIC_TYPE_ID_VOID,
    SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE,
    SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT,
    SPVM_NATIVE_C_BASIC_TYPE_ID_INT,
    SPVM_NATIVE_C_BASIC_TYPE_ID_LONG,
    SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT,
    SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE,
    SPVM_NATIVE_C_BASIC_TYPE_ID_STRING,
    SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT,
    SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_COMMAND_INFO_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_ADDRESS_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_COMPILE_CLASS,
  };

See L<SPVM::Document::NativeAPI/"Basic Type IDs">.

=head2 Basic Type Category IDs

  enum {
    SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN,
    SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNDEF,
    SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID,
    SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC,
    SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM,
    SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING,
    SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS,
    SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE,
    SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT,
  };

See L<SPVM::Document::NativeAPI/"Basic Type Category IDs">.

=head2 Type Flag IDs

  enum {
    SPVM_NATIVE_C_TYPE_FLAG_REF = 1,
    SPVM_NATIVE_C_TYPE_FLAG_MUTABLE = 2,
  };

See L<SPVM::Document::NativeAPI/"Type Flag IDs">.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License