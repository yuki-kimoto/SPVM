=head1 Name

SPVM::Document::SPVMArchive - The Specification of SPVM Archive

=head1 Description

L<SPVM Archive|SPVM::Document::SPVMArchive> is a format used to bundle compiled SPVM native classes, precompiled classes, third-party header files, and static libraries into a single directory or a C<.tar.gz> file. 

These bundled assets are used by L<spvmcc|spvmcc> to build a standalone native executable.

=head1 How to Create an SPVM Archive

To create an SPVM Archive, use the L<spvmcc|spvmcc> command with the C<--build-spvm-archive> option.

  spvmcc --build-spvm-archive [Archive Directory] [Main SPVM File]

Examples:

If you have a main SPVM file C<myapp.spvm>, you can build the SPVM Archive into a directory named C<spvm-archive-myapp> as follows:

  spvmcc -o spvm-archive-myapp --build-spvm-archive myapp.spvm

After execution, you can verify the created SPVM Archive using the C<ls> command:

  ls -R spvm-archive-myapp

The output should contain C<spvm-archive.json> and the directories C<SPVM/>, C<object/>, C<lib/>, and C<include/>.

=cut
