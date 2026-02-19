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

=head1 How to Create an SPVM Archive

To create an SPVM Archive, use the L<spvmcc|spvmcc> command with the C<--build-spvm-archive> option.

  spvmcc --build-spvm-archive [Archive Directory] [Main SPVM File]

Examples:

If you have a main SPVM file C<myapp.spvm>, you can build the SPVM Archive into a directory named C<spvm-archive-myapp> as follows:

  spvmcc -o spvm-archive-myapp --build-spvm-archive myapp.spvm

After execution, you can verify the created SPVM Archive using the C<ls> command:

  ls -R spvm-archive-myapp

=head1 How to Use an SPVM Archive

To use an existing SPVM Archive, call the C<use_spvm_archive> method in your C<.config> file.

Examples:

If you have created an SPVM Archive named C<spvm-archive-myapp>, you can use it in your C<.config> file like this:

  use strict;
  use warnings;
  use File::Basename 'dirname';

  my $config_exe = SPVM::Builder::Config::Exe->new;
  my $config_dir = dirname __FILE__;

  # Load the pre-compiled assets from the SPVM Archive
  $config_exe->use_spvm_archive("$config_dir/spvm-archive-myapp");

  $config_exe;

Then, build your application using the L<spvmcc|spvmcc> command:

  spvmcc -o myapp myapp.spvm

=cut
