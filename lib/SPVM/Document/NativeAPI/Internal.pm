=head1 Name

SPVM::Document::NativeAPI::Internal - Internal Native APIs

=head1 Description

The internal native APIs in L<SPVM> are the APIs for internal operations.

These APIs are used for the implementation of the SPVM language, so they should not be used.

=head1 Usage

  SPVM_API_INTERNAL* api_internal = env->api->internal;

=head1 Native APIs

=head2 get_ref_count

C<int32_t (*get_ref_count)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<SPVM_OBJ* object|SPVM::Document::NativeAPI/"SPVM_OBJ">);>

Returns the reference count of the object I<object>.

=head2 inc_ref_count

C<void (*inc_ref_count)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<SPVM_OBJ* object|SPVM::Document::NativeAPI/"SPVM_OBJ">);>

Increments the reference count of the object I<object>.

=head2 dec_ref_count

C<void (*dec_ref_count)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, L<SPVM_OBJ* object|SPVM::Document::NativeAPI/"SPVM_OBJ">);>

Decrements the reference count of the object I<object>.

=head2 get_stack_tmp_buffer

C<char* (*get_stack_tmp_buffer)(SPVM_ENV* env, SPVM_VALUE* stack);>

Returns the temporary buffer on the runtime stack I<stack>.

The byte size of the temporary buffer is L<SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE|SPVM::Document::NativeAPI/"SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE">.

Currently, this internal native API is the same as L<get_stack_tmp_buffer|SPVM::Document::NativeAPI/"get_stack_tmp_buffer"> native API.

=head2 leave_scope_local

C<void (*leave_scope_local)(SPVM_ENV* env, SPVM_VALUE* stack, L<SPVM_OBJ** object_vars|SPVM::Document::NativeAPI/"SPVM_OBJ">, int32_t* mortal_stack_typed_var_index, int32_t* mortal_stack_top_ptr, int32_t* mortal_stack_tops, int32_t mortal_stack_tops_index);>

Performs a leaving scope operation for local variables given object variables I<object_vars>, the mortal stack I<mortal_stack>, the address of the top of the mortal stack I<mortal_stack_top_ptr>, and the mortal stack tops I<mortal_stack_tops>, and the index of the top of the mortal stack I<mortal_stack_tops_index>.

The value referenced by I<mortal_stack_top_ptr> is updated.

=head2 c_strlen

C<size_t (*c_strlen)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* str);>

A wrapper for the C standard function L<strlen|https://linux.die.net/man/3/strlen>.

=head2 c_memcpy

C<void* (*c_memcpy)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* dest, const void* src, size_t n);>

A wrapper for the C standard function L<memcpy|https://linux.die.net/man/3/memcpy>.

=head2 c_memset

C<void* (*c_memset)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* s, int c, size_t n);>

A wrapper for the C standard function L<memset|https://linux.die.net/man/3/memset>.

=head2 c_memcmp

C<int (*c_memcmp)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const void* s1, const void* s2, size_t n);>

A wrapper for the C standard function L<memcmp|https://linux.die.net/man/3/memcmp>.

=head2 c_strtoll

C<long long (*c_strtoll)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* str, char** endptr, int base);>

A wrapper for the C standard function L<strtoll|https://linux.die.net/man/3/strtoll>.

=head2 c_strtof

C<float (*c_strtof)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* str, char** endptr);>

A wrapper for the C standard function L<strtof|https://linux.die.net/man/3/strtof>.

=head2 c_strtod

C<double (*c_strtod)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* str, char** endptr);>

A wrapper for the C standard function L<strtod|https://linux.die.net/man/3/strtod>.

=head2 c_fputs

C<int (*c_fputs)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, const char* s, void* stream);>

A wrapper for the C standard function L<fputs|https://linux.die.net/man/3/fputs>.

=head2 c_fgetc

C<int (*c_fgetc)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* stream);>

A wrapper for the C standard function L<fgetc|https://linux.die.net/man/3/fgetc>.

=head2 c_snprintf_len

C<int32_t (*c_snprintf_len)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, char* s, size_t n, const char* format, L<SPVM_VALUE* args|SPVM::Document::NativeClass/"Runtime Stack">, int32_t args_length);>

A wrapper for the C standard function L<snprintf|https://linux.die.net/man/3/snprintf>.

This function receives arguments as an array of L<SPVM_VALUE|SPVM::Document::NativeClass/"Runtime Stack"> instead of variadic arguments. 

The format specifiers in the C<format> string must match the types of the values stored in C<args>. 

For example:
* C<%d>, C<%x>: Expects an C<ival> (C<int32_t>).
* C<%ld>, C<%lld> (or C<PRId64>): Expects a C<lval> (C<int64_t>).
* C<%f>, C<%g>: Expects a C<dval> (C<double>).
* C<%s>, C<%p>: Expects an C<address> (C<void*>).

Returns the number of characters that would have been written if C<n> had been sufficiently large, not counting the terminating null character.

=head1 Native Internal API IDs

  0 get_ref_count
  1 inc_ref_count
  2 dec_ref_count
  3 get_stack_tmp_buffer
  4 leave_scope_local
  5 c_strlen
  6 c_memcpy
  7 c_memset
  8 c_memcmp
  9 c_strtoll
  10 c_strtof
  11 c_strtod
  12 c_fputs
  13 c_fgetc
  14 c_snprintf_len
  
=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
