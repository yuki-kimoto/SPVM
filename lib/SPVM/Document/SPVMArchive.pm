=head1 Name

SPVM::Document::SPVMArchive - The Specification of SPVM Archive

=head1 Description

L<SPVM Archive|SPVM::Document::SPVMArchive> is a format used to bundle compiled SPVM native classes, precompiled classes, third-party header files, and static libraries into a single directory or a C<.tar.gz> file. 

These bundled assets are used by L<spvmcc|spvmcc> to build a standalone native executable.

