=head1 Name

SPVM::Document::Language::System - System Setting in the SPVM Language

=head1 Description

This document describes system setting in the SPVM language.

=head1 System Setting

=head2 Standard Streams

SPVM opens own standard input, standard output, and standard error for a runtime just after a runtime is build.

Their open modes are set to L<binary mode|https://learn.microsoft.com/en-us/cpp/c-runtime-library/text-and-binary-mode-file-i-o?view=msvc-170> in Windows.

The L<print operator|SPVM::Document::Language::Operators/"print Operator"> outputs to this SPVM's standard output.

The L<say operator|SPVM::Document::Language::Operators/"say Operator"> outputs to this SPVM's standard output.

The L<warn operator|SPVM::Document::Language::Operators/"warn Operator"> outputs to this SPVM's standard error.

=head2 Thread Safety

The SPVM language has some thread-safe features.

=head3 Runtime Stack

When a new thread, such as an L<OS native thread|SPVM::Thread>, a coroutine such as a L<goroutine|SPVM::Go> is created, a new L<runtime stack|SPVM::Document::NativeClass/"Runtime Stack"> should be created for the new thread.

  SPVM_VALUE* new_stack = env->new_stack(env);

This runtime stack has thread-specific data, such as the value of the exception variable, as well as method-specific data, such as arguments and a return value.

When the new thread finished, the new runtime stack must be released.

  env->free_stack(env, new_stack);

Currently, user data cannot be got and set in a runtime stack.

If thread-specific user data is needed, the thread ID is got by L<Thread#get_id|SPVM::Thread#get_id> method and this thread ID can be a key of a L<hash|SPVM::Hash> for thread-specific user data. In this case, L<Hash|SPVM::Hash> class is not thread safe, a lock using a L<mutex|SPVM::Sync::Mutex> is needed.

=head2 Atomic Operations

This section describe atomic operations.

Generally speaking, when using L<OS native threads|SPVM::Thread> with SPVM, the following atomic operations can result in severe performance degradation.

Therefore, the advice is to minimize object creations and object assignments in newly created L<OS native threads|SPVM::Thread>.

Coroutine threads such as L<goroutines|SPVM::Go> don't have to worry about things like this because these are synchronized.

=head3 Updating Memory Blocks Count

Updating the count of allocated memory blocks is an atomic operation and thread safe. It is protected by a mutex. 

The count of all allocated memory blocks in a runtime is managed and is got by L<get_memory_blocks_count|SPVM::Document::NativeAPI/"get_memory_blocks_count"> native API.

=head3 Updating Runtime Cache

Updating a runtime cache data is an atomic operation and thread safe. It is protected by a mutex.

=head3 Compilation

A compilation is an atomic operation and thread safe. It is protected by a mutex.

=head3 Updating Reference Count

Updating the reference count of an object an atomic operation and thread safe. It is protected by a mutex. 

=head1 See Also

=over 2

=item * L<SPVM::Document::Language::Operators>

=item * L<SPVM::Document::Language>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
