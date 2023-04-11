=head1 Name

SPVM::Document::Resource - How to write the resource class

=head1 Resource

A resource is a L<native class|SPVM::Document::NativeClass> that contains a set of sources and headers of native language such as the C language or C<C++>.

A resource doesn't has the native class file such as C<Foo.c>. It has a config file such as C<Foo.config>. Header files are placed at C<Foo.native/include>. Source filies are placed at C<Foo.native/src>. 

Let's see the files of L<Resource::Zlib|SPVM::Resource::Zlib> as an example.

B<SPVM/Resource/Zlib/V1_2_11.config>

  use strict;
  use warnings;
   
  use SPVM::Builder::Config;
  my $config = SPVM::Builder::Config->new_c99(file => __FILE__);
   
  # C souce files
  my @source_files = qw(
    adler32.c
    compress.c
    crc32.c
    deflate.c
    gzclose.c
    gzlib.c
    gzread.c
    gzwrite.c
    infback.c
    inffast.c
    inflate.c
    inftrees.c
    trees.c
    uncompr.c
    zutil.c
  );
  $config->add_source_file(@source_files);
   
  my @ccflags = '-D_LARGEFILE64_SOURCE';
   
  $config->add_ccflag(@ccflags);
   
  $config;  

B<The list of the files in C<include> directory>

The header files of C<zlib>. These files are the header files extracted from C<src> directory.

  crc32.h
  deflate.h
  gzguts.h
  inffast.h
  inffixed.h
  inflate.h
  inftrees.h
  trees.h
  zconf.h
  zlib.h
  zutil.h

B<The list of the files in C<src> directory>

The source files of C<zlib>.

  adler32.c
  amiga
  ChangeLog
  CMakeLists.txt
  compress.c
  configure
  contrib
  crc32.c
  deflate.c
  doc
  examples
  FAQ
  gzclose.c
  gzlib.c
  gzread.c
  gzwrite.c
  INDEX
  infback.c
  inffast.c
  inflate.c
  inftrees.c
  Makefile
  Makefile.in
  make_vms.com
  msdos
  nintendods
  old
  os400
  qnx
  README
  test
  treebuild.xml
  trees.c
  uncompr.c
  watcom
  win32
  zconf.h.cmakein
  zconf.h.in
  zlib2ansi
  zlib.3
  zlib.3.pdf
  zlib.map
  zlib.pc.cmakein
  zlib.pc.in
  zutil.c

=head1 Using Resource

The method L<SPVM::Builder::Config/"use_resource">  loads a resource. C<MyZlib> is a L<native class|SPVM::Document::NativeClass> to use L<Resource::Zlib|SPVM::Resource::Zlib>.

B<lib/SPVM/MyZlib.config>

  use strict;
  use warnings;
  
  my $config = SPVM::Builder::Config->new_c99(file => __FILE__);
  
  $config->use_resource('Resource::Zlib');
  
  $config;

B<lib/SPVM/MyZlib.spvm>

Define a native method C<test_gzopen_gzread>.

  class MyZlib {
    native static method test_gzopen_gzread : void ($file : string);
  }

B<lib/SPVM/MyZlib.c>

C<zlib.h> can be included because L<Resource::Zlib|SPVM::Resource::Zlib> is used.

  #include "spvm_native.h"
  
  #include <zlib.h>
  
  int32_t SPVM__MyZlib__test_gzopen_gzread(SPVM_ENV* env, SPVM_VALUE* stack) {
    (void)env;
    
    void* sp_file = stack[0].oval;
    
    const char* file = env->get_chars(env, stack, sp_file);
    
    z_stream z;
    
    gzFile gz_fh = gzopen(file, "rb");
    
    if (gz_fh == NULL){
      return env->die(env, stack, "Can't open file \"%s\"\n", __func__, file, __LINE__);
    }
    
    char buffer[256] = {0};
    int32_t cnt;
    while((cnt = gzread(gz_fh, buffer, sizeof(buffer))) > 0){
      
    }
    
    printf("%s", buffer);
    
    return 0;
  }

B<myzlib.pl>

A Perl script to call C<test_gzopen_gzread> method of C<MyZlib> class.

  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";
  BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

  use SPVM 'MyZlib';

  my $gz_file = "$FindBin::Bin/minitest.txt.gz";
  SPVM::MyZlib->test_gzopen_gzread($gz_file);

=head1 Creating Resource Distribution

L<spvmdist> command with C<--resource> option create a resource distribution.
  
  # C language resource
  spvmdist --resource Resource::Foo::V1_0_0

  # C++ resource
  spvmdist --resource --native c++ Resource::Foo::V1_0_0

=head1 Resource Modules

B<L<Resource::Zlib|SPVM::Resource::Zlib>>

=over 2

=item * L<Resource::Zlib|SPVM::Resource::Zlib>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
