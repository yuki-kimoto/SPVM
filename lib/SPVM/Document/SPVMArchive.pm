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

=head1 Merging SPVM Archives

You can merge an existing SPVM Archive into a new one by combining the C<use_spvm_archive> method in your C<.config> file with the C<--build-spvm-archive> option of the L<spvmcc|spvmcc> command.

Examples:

If your C<myapp.config> uses an existing archive:

  # In myapp.config
  $config_exe->use_spvm_archive("/path/to/existing-archive");

And you run C<spvmcc> with the C<--build-spvm-archive> option:

  spvmcc -o spvm-archive-merged --build-spvm-archive myapp.spvm

The following merging process occurs:

=over 2

=item * B<Class Metadata>: The C<classes_h> registry from the existing archive and the newly compiled classes are merged. If there are duplicate class names, the ones from the new build take precedence.

=item * B<Object Files>: All C<.o> files from the existing archive are copied into the new archive's C<object/> directory, alongside the new object files.

=item * B<Native Assets>: Static libraries in C<lib/> and header files in C<include/> from the existing archive are collected and bundled into the new archive.

=item * B<Metadata Fields>: Fields like C<spvm_version>, C<app_name>, C<mode>, and C<version> are updated based on the current build's information.

=back

=cut

=head1 Merging SPVM Archives

You can merge an existing SPVM Archive into a new one by combining the C<use_spvm_archive> method in your C<.config> file with the C<--build-spvm-archive> option of the L<spvmcc|spvmcc> command.

Examples:

If your C<myapp.config> uses an existing archive:

  # In myapp.config
  $config_exe->use_spvm_archive("/path/to/existing-archive");

And you run C<spvmcc> with the C<--build-spvm-archive> option:

  spvmcc -o spvm-archive-merged --build-spvm-archive myapp.spvm

The following merging process occurs:

=over 2

=item Class Metadata

The C<classes_h> registry and other metadata fields (C<app_name>, C<spvm_version>, C<mode>, C<version>) are merged or updated. If there are duplicate class names, the ones from the new build take precedence.

=item SPVM Class Files

All C<.spvm> source files required for the classes are collected from the existing archive and the current include paths, then stored in the C<SPVM/> directory of the new archive.

=item Object Files

All C<.o> files for SPVM native classes and precompiled classes are collected from the existing archive and copied into the new archive's C<object/> directory, alongside the newly generated object files.

=item Native Assets

Static libraries (C<.a>, C<.lib>) in C<lib/> and header files (C<.h>, C<.hpp>) in C<include/> from the existing archive are collected and bundled into the new archive.

=back

=cut
