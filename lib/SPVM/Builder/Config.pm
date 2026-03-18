package SPVM::Builder::Config;

use parent 'SPVM::Builder::Config::Linker';

use strict;
use warnings;
use Config;
use Carp 'confess';
use SPVM::Builder::Util;

use SPVM::Builder::Accessor 'has';

# Fields
my $cc_fields = [qw(
  cc
  ccflags
  defines
  optimize
  std
  language
  dialect
  ext
  copyright_print_ccflags
  language_ccflags
  arch_ccflags
  function_level_linking_ccflags
  cpp_exception_handling_ccflags
  library_linkage_ccflags
  dynamic_lib_ccflags
  thread_ccflags
  cc_input_dir
  cc_output_dir
  include_dirs
  spvm_core_include_dir
  native_include_dir
  native_src_dir
  source_files
  before_compile_cbs
  cc_output_option_name
)];

has($cc_fields);

sub option_names {
  my ($self) = @_;
  
  return [@{$self->SUPER::option_names}, @$cc_fields];
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = $class->SUPER::new(@_);
  
  # ccflags
  unless (exists $self->{ccflags}) {
    $self->ccflags([]);
  }

  # defines
  unless (exists $self->{defines}) {
    $self->defines([]);
  }

  # dynamic_lib_ccflags
  unless (exists $self->{dynamic_lib_ccflags}) {
    if ($^O eq 'MSWin32') {
      $self->dynamic_lib_ccflags([]);
    }
    else {
      $self->dynamic_lib_ccflags(['-fPIC']);
    }
  }

  # thread_ccflags
  unless (exists $self->{thread_ccflags}) {
    $self->thread_ccflags(['-pthread']);
  }

  # optimize
  unless (exists $self->{optimize}) {
    $self->optimize('-O3 -DNDEBUG');
  }

  # include_dirs
  unless (exists $self->{include_dirs}) {
    $self->include_dirs([]);
  }

  # spvm_core_include_dir
  unless (exists $self->{spvm_core_include_dir}) {
    my $builder_dir = SPVM::Builder::Util::get_builder_dir();
    my $spvm_core_include_dir = "$builder_dir/include";
    
    $self->spvm_core_include_dir($spvm_core_include_dir);
  }

  # source_files
  unless (exists $self->{source_files}) {
    $self->source_files([]);
  }

  # before_compile_cbs
  unless (exists $self->{before_compile_cbs}) {
    $self->before_compile_cbs([]);
  }

  # copyright_print_ccflags
  unless (exists $self->{copyright_print_ccflags}) {
    $self->copyright_print_ccflags([]);
  }

  # language_ccflags
  unless (exists $self->{language_ccflags}) {
    $self->language_ccflags([]);
  }

  # arch_ccflags
  unless (exists $self->{arch_ccflags}) {
    $self->arch_ccflags([]);
  }
  
  # function_level_linking_ccflags
  unless (exists $self->{function_level_linking_ccflags}) {
    $self->function_level_linking_ccflags([]);
  }

  # cpp_exception_handling_ccflags
  unless (exists $self->{cpp_exception_handling_ccflags}) {
    if ($^O eq 'MSWin32') {
      $self->cpp_exception_handling_ccflags(['-D__USE_MINGW_ANSI_STDIO']);
    }
    else {
      $self->cpp_exception_handling_ccflags([]);
    }
  }

  # library_linkage_ccflags
  unless (exists $self->{library_linkage_ccflags}) {
    $self->library_linkage_ccflags([]);
  }

  # cc_output_option_name
  unless (exists $self->{cc_output_option_name}) {
    $self->cc_output_option_name("-o");
  }

  return $self;
}

sub new_c {
  my $class = shift;
  
  my $self = $class->new(@_);
  
  # C compiler
  my $config_gcc_version = $Config{gccversion};
  if ($config_gcc_version =~ /\bclang\b/i) {
    $self->cc('clang');
  }
  else {
    $self->cc('gcc');
  }
  
  $self->language('c');
  
  $self->ext('c');
  
  return $self;
}

sub new_c99 {
  my $class = shift;
  
  my $self = $class->new_c(@_);
  
  # C99
  $self->std('c99');
  
  return $self;
}

sub new_c11 {
  my $class = shift;
  
  my $self = $class->new_c(@_);
  
  # C11
  $self->std('c11');
  
  return $self;
}

sub new_cpp {
  my $class = shift;
  
  my $self = $class->new(@_);
  
  # C++ compiler
  my $config_gcc_version = $Config{gccversion};
  if ($config_gcc_version =~ /\bclang\b/i) {
    $self->cc('clang++');
  }
  else {
    $self->cc('g++');
  }
  
  $self->language('cpp');
  
  $self->ext('cpp');
  
  return $self;
}

sub new_cpp11 {
  my $class = shift;
  
  my $self = $class->new_cpp(@_);
  
  # C++11
  $self->std('c++11');
  
  return $self;
}

sub new_cpp14 {
  my $class = shift;
  
  my $self = $class->new_cpp(@_);
  
  # C++14
  $self->std('c++14');
  
  return $self;
}

sub new_cpp17 {
  my $class = shift;
  
  my $self = $class->new_cpp(@_);
  
  # C++17
  $self->std('c++17');
  
  return $self;
}

# Instance Methods
sub add_ccflag {
  my ($self, @ccflags) = @_;
  
  push @{$self->{ccflags}}, @ccflags;
}

sub add_define {
  my ($self, @defines) = @_;
  
  push @{$self->{defines}}, @defines;
}

sub add_include_dir {
  my ($self, @include_dirs) = @_;
  
  push @{$self->{include_dirs}}, @include_dirs;
}

sub add_source_file {
  my ($self, @source_files) = @_;
  
  push @{$self->{source_files}}, @source_files;
}

sub add_before_compile_cb {
  my ($self, @before_compile_cbs) = @_;
  
  push @{$self->{before_compile_cbs}}, @before_compile_cbs;
}

sub clear_system_fields {
  my $self = shift;
  
  $self->SUPER::clear_system_fields;
  
  $self->dynamic_lib_ccflags([]);
  $self->thread_ccflags([]);
  $self->copyright_print_ccflags([]);
  $self->language_ccflags([]);
  $self->arch_ccflags([]);
  $self->function_level_linking_ccflags([]);
  $self->cpp_exception_handling_ccflags([]);
  $self->library_linkage_ccflags([]);
  $self->thread_ccflags([]);
}

1;

=head1 Name

SPVM::Builder::Config - Config for Compiling and Linking Native Classes

=head1 Description

L<SPVM::Builder::Config> is a class to manage the configurations for compiling and linking native classes (C, C++, etc.).

An instance of this class holds compiler settings (managed by L<SPVM::Builder::Config> itself), linker and resource settings (inherited from L<SPVM::Builder::Config::Linker>), and configuration loading and common settings (inherited from L<SPVM::Builder::Config::Base>).

Within a configuration file (C<.config>), you can customize the build environment by accessing methods from all of these hierarchical levels.=head1 Usage

  use SPVM::Builder::Config;
  
  # Create a config
  my $config = SPVM::Builder::Config->new;
  
  # C99
  my $config = SPVM::Builder::Config->new_c99;
  
  # C++
  my $config = SPVM::Builder::Config->new_cpp;
  
  # C++11
  my $config = SPVM::Builder::Config->new_cpp11;
  
  # C++17
  my $config = SPVM::Builder::Config->new_cpp17;
  
  # Optimize
  $config->optimize("-O2");
  
  # Optimize with debug mode
  $config->optimize("-O0 -g");
  
  # Add ccflags
  $config->add_ccflag("-DFOO");
  
  $config->add_define("FOO");
  
  # Add source files
  $config->add_source_file("foo.c", "bar.c", "baz/baz.c");
  
  # Add libraries
  $config->add_lib("gdi32", "d2d1", "Dwrite");
  
  # Add ldflags
  $config->add_ldflag("-pthread");
  
  # Use resource
  $config->use_resource("Resource::MyResource");

=head1 Inheritance

L<SPVM::Builder::Config::Linker>

=head2 Class Hierarchy

=over 2

=item 1. L<SPVM::Builder::Config::Base>

The base class for all configuration classes. It provides the "loading configuration files" mechanism and manages common settings shared across all build phases, such as C<class_name>, C<force>, and C<quiet>.

=item 2. L<SPVM::Builder::Config::Linker>

This class manages settings for "linking" (converting object files to shared libraries or executables) and "resource management". Fields like C<ld>, C<libs>, C<ldflags>, and C<resources> are defined in this class. Inherits L<SPVM::Builder::Config::Base>.

=item 3. L<SPVM::Builder::Config>

This class primarily manages settings for "compilation" (converting C/C++ source files to object files). Inherits L<SPVM::Builder::Config::Linker> and L<SPVM::Builder::Config::Base>.

=back

=head1 Fields

=head2 ext

  my $ext = $config->ext;
  $config->ext($ext);

Gets and sets C<ext> field, the extension of a native class.

Examples:

  # MyClass.c
  $config->ext('c');
  
  # MyClass.cpp
  $config->ext('cpp');
  
  # MyClass.cc
  $config->ext('cc');
  
  # MyClass.cu
  $config->ext('cu');
  
  # MyClass.m
  $config->ext('m');

=head2 cc

  my $cc = $config->cc;
  $config->cc($cc);

Gets and sets C<cc> field, a compiler name.

Examples:
  
  # gcc
  $config->cc('gcc');
  
  # g++ for C++
  $config->cc('g++');
  
  # nvcc for CUDA/GUP
  $config->cc('nvcc');
  
=head2 include_dirs

  my $include_dirs = $config->include_dirs;
  $config->include_dirs($include_dirs);

Gets and sets C<include_dirs> field, an array reference containing header file search directories.

The values of this field are converted to C<-I> options when the arguments of the compiler L</"cc"> are created.

  # -I /path1 -I /path2
  $config->include_dirs(['/path1', '/path2']);

=head2 spvm_core_include_dir

  my $spvm_core_include_dir = $config->spvm_core_include_dir;
  $config->spvm_core_include_dir($spvm_core_include_dir);

Gets and sets C<spvm_core_include_dir> field, an SPVM core header file search directory.

The value of this field is converted to C<-I> option when the arguments of the compiler L</"cc"> are created.

This field is automatically set and users nomally do not change it.

=head2 native_include_dir

  my $native_include_dir = $config->native_include_dir;
  $config->native_include_dir($native_include_dir);

Gets and sets C<native_include_dir> field, a L<native header file|SPVM::Document::NativeClass/"Native Header Files"> search directory.

The value of this field is converted to C<-I> option when the arguments of the compiler L</"cc"> are created.

This field is automatically set and users nomally do not change it.

=head2 native_src_dir

  my $native_src_dir = $config->native_src_dir;
  $config->native_src_dir($native_src_dir);

Gets and sets C<native_src_dir> field, a L<native source file|SPVM::Document::NativeClass/"Native Source Files"> search directory.

This field is automatically set and users nomally do not change it.

=head2 ccflags

  my $ccflags = $config->ccflags;
  $config->ccflags($ccflags);

Gets and sets C<ccflags> field, an array reference containing arugments of the compiler L</"cc">.

=head2 defines

  my $defines = $config->defines;
  $config->defines($defines);

Gets and sets C<defines> field, an array reference containing the values of C<-D> arugments of the compiler L</"cc">.

=head2 optimize

  my $optimize = $config->optimize;
  $config->optimize($optimize);

Gets and sets C<optimize> field, an arugment of the compiler L</"cc"> for optimization.

Examples:

  $config->optimize('-O3 -DNDEBUG');
  $config->optimize('-O2');
  $config->optimize('-g3 -O0');

=head2 dynamic_lib_ccflags

  my $dynamic_lib_ccflags = $config->dynamic_lib_ccflags;
  $config->dynamic_lib_ccflags($dynamic_lib_ccflags);

Gets and sets C<dynamic_lib_ccflags> field, an array reference containing arugments of the compiler L</"cc"> for dynamic linking.

This field is automatically set and users nomally do not change it.

=head2 thread_ccflags

  my $thread_ccflags = $config->thread_ccflags;
  $config->thread_ccflags($thread_ccflags);

Gets and sets C<thread_ccflags> field, an array reference containing arugments of the compiler L</"cc"> for threads.

This field is automatically set and users nomally do not change it.

=head2 std

  my $std = $config->std;
  $config->std($std);

Gets and sets C<std> field, a language standard.

This field is converted to C<-std> option when the arguments of the compiler L</"cc"> are created.

Examples:
  
  # -std=c99
  $config->std('c99');
  
  # -std=cpp
  $config->std('cpp');
  
  # -std=cpp11
  $config->std('cpp11');
  
  # -std=cpp17
  $config->std('cpp17');

=head2 source_files

  my $source_files = $config->source_files;
  $config->source_files($source_files);

Gets and sets C<source_files> field, an array reference containing relative paths of L<native source file|SPVM::Document::NativeClass/"Native Source Files"> file from L</"native_src_dir"> field.

=head2 before_compile_cbs

  my $before_compile_cbs = $config->before_compile_cbs;
  $config->before_compile_cbs($before_compile_cbs);

Gets and sets C<before_compile_cbs> field, an array reference containing callbacks called just before the compile command L</"cc"> is executed.

These callbacks are executed only if an object file is actually generated.

The 1th argument of the callback is an L<SPVM::Builder::Config> object.

The 2th argument of the callback is an L<SPVM::Builder::CompileInfo> object.

=head2 cc_input_dir

  my $cc_input_dir = $config->cc_input_dir;
  $config->cc_input_dir($cc_input_dir);

Gets and sets C<cc_input_dir> field, an input directory for the compiler L</"cc">.

This field is automatically set and users nomally do not change it.

=head2 cc_output_dir

  my $cc_output_dir = $config->cc_output_dir;
  $config->cc_output_dir($cc_output_dir);

Gets and sets C<cc_output_dir> field, an output directory for the compiler L</"cc">.

This field is automatically set and users nomally do not change it.

=head2 language

  my $language = $config->language;
  $config->language($language);

Gets and sets the C<language> field.

The language of the source files.

One of the following languages can be specified:

=over 2

=item * C<c>

C language

=item * C<cpp>

C++ language

=back

=head2 dialect

  my $dialect = $config->dialect;
  $config->dialect($dialect);

Gets and sets the C<dialect> field.

The dialect of the language.

You can specify any dialect name, but the following names are reserved for specific compilers or toolchains:

Each unit of a dialect name must consist of lowercase alphanumeric characters (C<a-z0-9>).

Multiple units can be combined using a hyphen (C<->) to represent sub-dialects, such as C<arduino-avr>, C<esp32-s3>, or C<cuda-sm80>.

You can specify any dialect name, but the following names are reserved for specific compilers or toolchains:

=over 2

=item * C Based Dialects

=over 4

=item * Languages

=over 6

=item * C<objc>

Objective-C language

=back

=item * Shaders

=over 6

=item * C<glsl>

Vulkan/OpenGL Shading Language. (Requires C<glslc>)

=back

=item * Microcontrollers

=over 6

=item * C<arduino>

Arduino dialect. Requires C<avr-gcc> or C<arm-none-eabi-gcc>.

=item * C<esp32>

ESP32 specific dialect. Requires C<xtensa-esp32-elf-gcc>.

=item * C<pic>

Microchip PIC dialect. Requires C<xc8>, C<xc16>, or C<xc32>.

=item * C<avr>

Raw AVR dialect. Requires C<avr-gcc>.

=back

=back

=item * C++ Based Dialects

=over 4

=item * Languages

=over 6

=item * C<objcpp>

Objective-C++ language

=back

=item * Shaders

=over 6

=item * C<metal> - Apple Metal Shading Language. (Based on C++14. Requires C<metal> compiler)

=back

=item * GPU Computing

=over 6

=item * C<cuda> - NVIDIA CUDA dialect. (Requires C<nvcc>)

=item * C<hip> - AMD ROCm HIP dialect. (Requires C<hipcc>)

=item * C<sycl> - SYCL dialect for heterogeneous computing. (Requires C<dpc++>)

=back

=item * Hardware Logic Design (FPGA)

=over 6

=item * C<hls> - High-Level Synthesis dialect. (Usually based on C++. Requires C<v++>)

=back

=back

=back

=head2 copyright_print_ccflags

  my $copyright_print_ccflags = $config->copyright_print_ccflags;
  $config->copyright_print_ccflags(['-nologo']);

Gets and sets the C<copyright_print_ccflags> field, an array reference containing compiler arguments to control the printing of the copyright banner or logo (e.g., C<-nologo> in MSVC).

=head2 language_ccflags

  my $language_ccflags = $config->language_ccflags;
  $config->language_ccflags($language_ccflags);

Gets and sets C<language_ccflags> field, an array reference containing arguments of the compiler L</"cc"> for language.

=head2 arch_ccflags

  my $arch_ccflags = $config->arch_ccflags;
  $config->arch_ccflags($arch_ccflags);

Gets and sets C<arch_ccflags> field, an array reference containing arguments of the compiler L</"cc"> for CPU architecture or host environment.

=head2 function_level_linking_ccflags

  my $function_level_linking_ccflags = $config->function_level_linking_ccflags;
  $config->function_level_linking_ccflags(['-Gy']);

Gets and sets the C<function_level_linking_ccflags> field, an array reference containing compiler arguments to enable function-level linking (e.g., C<-Gy> in MSVC).

This allows the linker to optimize the executable size by removing unreferenced functions.

=head2 cpp_exception_handling

  my $cpp_exception_handling = $config->cpp_exception_handling;
  $config->cpp_exception_handling(1);

Gets and sets the C<cpp_exception_handling> field, a boolean value that indicates whether C++ exception handling is enabled.

If this value is true, the compiler is configured to support C++ exceptions (e.g., C<-EHsc> in MSVC, C<-fexceptions> in GCC). 
Defaults to undef.

=head2 library_linkage_ccflags

  my $library_linkage_ccflags = $config->library_linkage_ccflags;
  $config->library_linkage_ccflags(['-MT']);

Gets and sets the C<library_linkage_ccflags> field, an array reference containing compiler arguments to specify the library linkage (e.g., static or dynamic linking).

These flags are passed to the compiler L</"cc"> to determine how libraries (such as the C runtime library) are linked. For example, C<-MT> or C<-MD> in MSVC.

=head2 cc_output_option_name

  my $cc_output_option_name = $config->cc_output_option_name;
  $config->cc_output_option_name($cc_output_option_name);

Gets and sets C<cc_output_option_name> field, a string that is an option name to specify a compiler output file name.

=head1 Class Methods

=head2 new

  my $config = SPVM::Builder::Config->new(%fields);

Creates a new C<SPVM::Builder::Config> object. This method calls the C<new> method of the super class L<SPVM::Builder::Config::Linker>.

Default settings for the GCC or Clang compiler are performed.

Field Default Values:

=over 2

=item * L</"cc">

  undef

=item * L</"ccflags">

  []

=item * L</"defines">

  []

=item * L</"optimize">

  "-O3 -DNDEBUG"

=item * L</"copyright_print_ccflags">

  []

=item * L</"language_ccflags">

  []

=item * L</"arch_ccflags">

  []

=item * L</"function_level_linking_ccflags">

  []

=item * L</"cpp_exception_handling_ccflags">

Windows:

  ['-D__USE_MINGW_ANSI_STDIO']

Other OSs:

  []

=item * L</"library_linkage_ccflags">

  []

=item * L</"dynamic_lib_ccflags">

Windows:

  []

Other OSs:

  ["-fPIC"]

=item * L</"thread_ccflags">

  ["-pthread"]

=item * L</"include_dirs">

  []

=item * L</"spvm_core_include_dir">

The SPVM core header file search directory.

=item * L</"native_include_dir">

The directory described in L<SPVM::Document::NativeClass/"Native Header Files">.

=item * L</"native_src_dir">

The directory described in L<SPVM::Document::NativeClass/"Native Source Files">.

=item * L</"source_files">

  []

=item * L</"before_compile_cbs">

  []

=item * L</"cc_output_option_name">

"-o"

=back

=cut

=head2 new_c

  my $config = SPVM::Builder::Config->new_c;

Calls L</"new"> method and sets L</"ext"> field to C<c>, L</"language"> field to C<c>, L</"cc"> field to a C++ compiler, and returns the return value of L</"new"> method.

=head2 new_c99
  
  my $config = SPVM::Builder::Config->new_c99;

Calls L</"new_c"> method and sets L</"std"> field to C<c99>, and returns the return value of L</"new_c"> method.

=head2 new_c11
  
  my $config = SPVM::Builder::Config->new_c11;

Calls L</"new_c"> method and sets L</"std"> field to C<c11>, and returns the return value of L</"new_c"> method.

=head2 new_cpp

  my $config = SPVM::Builder::Config->new_cpp;

Calls L</"new"> method and sets L</"ext"> field to C<cpp>, L</"language"> field to C<cpp>, L</"cc"> field to a C++ compiler, and L</"ld"> field to a C++ linker, and returns the return value of L</"new"> method.

If C<$Config{gccversion}> contains C<clang>, L</"cc"> field and L</"ld"> field are set to C<clang++>. Otherwise, L</"cc"> field and L</"ld"> field are set to C<g++>.

=head2 new_cpp11
  
  my $config = SPVM::Builder::Config->new_cpp11;

Calls L</"new_cpp"> method and sets L</"std"> field to C<c++11>, and returns the return value of L</"new_cpp"> method.

=head2 new_cpp14
  
  my $config = SPVM::Builder::Config->new_cpp14;

Calls L</"new_cpp"> method and sets L</"std"> field to C<c++14>, and returns the return value of L</"new_cpp"> method.

=head2 new_cpp17
  
  my $config = SPVM::Builder::Config->new_cpp17;

Calls L</"new_cpp"> method and sets L</"std"> field to C<c++17>, and returns the return value of L</"new_cpp"> method.

=head1 Instance Methods

=head2 add_ccflag

  $config->add_ccflag(@ccflags);

Adds @ccflags to the end of L</"ccflags"> field.

=head2 add_define

  $config->add_define(@defines);

Adds @defines to the end of L</"defines"> field.

=head2 add_include_dir

  $config->add_include_dir(@include_dirs);

Adds @include_dirs to the end of L</"include_dirs"> field.

=head2 add_source_file

  $config->add_source_file(@source_files);

Adds @source_files to the end of L</"source_files"> field.

Examples:

  $config->add_source_file('foo.c', 'bar.c');

=head2 add_before_compile_cb

  $config->add_before_compile_cb(@before_compile_cbs);

Adds @before_compile_cbs to the end of L</"before_compile_cbs"> field.

Examples:

  $config->add_before_compile_cb(sub {
    my ($config, $compile_info) = @_;
    
    my $cc_command = $compile_info->to_command;
    
    # Do something
  });

=head2 clear_system_fields

  $config->clear_system_fields;

Clears the fields that are set by default for a specific environment.

These fields might be updated in the future to support appropriate settings for different environments.

This method calls the L<clear_system_fields|SPVM::Builder::Config::Linker/"clear_system_fields"> method of the L<SPVM::Builder::Config::Linker> class to clear linker settings, and then clears the following compiler settings by setting them to C<[]>.

=over 2

=item * L</"dynamic_lib_ccflags">

=item * L</"thread_ccflags">

=item * L</"copyright_print_ccflags">

=item * L</"language_ccflags">

=item * L</"arch_ccflags">

=item * L</"function_level_linking_ccflags">

=item * L</"cpp_exception_handling_ccflags">

=item * L</"library_linkage_ccflags">

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License