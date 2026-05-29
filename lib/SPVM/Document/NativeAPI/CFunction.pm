=head1 Name

SPVM::Document::NativeAPI::CFunction - C Function Native APIs

=head1 Description

Native APIs for C standard functions.

=head1 Details

=head1 Details

These native APIs are provided to safely invoke C standard functions within the SPVM runtime, effectively bridging the isolation between different compilation environments.

In scenarios where the SPVM core is compiled with one compiler (e.g., GCC) and its extension modules are compiled with another (e.g., MSVC), a "runtime boundary" is created. Because each compiler environment maintains its own global state (such as standard I/O streams) and thread-local storage (such as C<errno>), data modified in the SPVM core may not be visible or correctly interpreted by the extension modules, and vice versa.

These APIs encapsulate the necessary logic to capture, synchronize, and handle such states across these runtime boundaries. By using these APIs, developers ensure that global and thread-specific states—such as error codes or stream positions—remain consistent and accessible, regardless of how the individual components were compiled.

Consider the following implementation of C<say_stderr>, which attempts to print a string to standard error:

  int32_t SPVM__Fn__say_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
    SPVM_OBJ* obj_string = stack[0].oval;
    
    // Prints the string via the SPVM runtime
    env->print_stderr(env, stack, obj_string);
    
    // Attempts to print a newline using a direct C function call
    env->api->cfunc->c_fputs(env, stack, "\n", env->spvm_stderr(env, stack));
    
    return 0;
  }

In this example, C<env->spvm_stderr> returns a C<FILE*> pointer managed by the SPVM core (compiled with GCC). However, when C<c_fputs> is called from an extension module compiled with a different compiler (e.g., MSVC), it attempts to use the standard I/O streams of the MSVC runtime. 

Because the C<FILE*> structure and its underlying state are incompatible between different C runtimes, calling C<fputs> with a file pointer from one runtime in another will lead to undefined behavior or crashes. Using the provided C<NativeAPI> ensures that such operations are routed through the correct runtime environment, maintaining cross-compiler compatibility.

=head1 Usage

  SPVM_API_INTERNAL* api_internal = env->api->internal;

=head1 Native APIs

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

=head1 Native C Function API IDs

  0 c_strlen
  1 c_memcpy
  2 c_memset
  3 c_memcmp
  4 c_strtoll
  5 c_strtof
  6 c_strtod
  7 c_fputs
  8 c_fgetc
  9 c_snprintf_len
  
=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
