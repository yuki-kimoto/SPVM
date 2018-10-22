use 5.008007;
use ExtUtils::MakeMaker;

# If you edit yacc/spvm_yacc.y, spvm_yacc.c is re-generate by the folloing command before perl Makefile.PL
#   yacc/bison.sh

use strict;
use warnings;
use Config;
use Getopt::Long;
use FindBin;
use lib "$FindBin::Bin/lib";
use SPVM::Builder::Util;
use Getopt::Long 'GetOptions';
use File::Basename 'basename';
use File::Copy 'copy';

# SPVM only support 64bit integer Perl
my $ivsize = $Config{ivsize};
if ($ivsize < 8) {
  die "SPVM don't support the Perl which \"ivsize\" is lower than 8";
}

# SPVM only support NetBSD 7+
if ($Config{osname} eq 'netbsd' && $Config{osvers} < 7) {
  die "SPVM don't support NetBSD 6, 5, 4, 3, 2, 1";
}

my @defines;
my $optimize;

GetOptions(
  "--DEFINE=s" => \@defines,
  "--OPTIMIZE=s" => \$optimize,
);

# Add -D
@defines = map { "-D$_" } @defines;

# Add -
if ($optimize) {
  $optimize = "$optimize";
}

my $build_config = SPVM::Builder::Util::new_default_build_config();
$optimize ||= $build_config->get_config('optimize');
my $ccflags = $build_config->get_ccflags;

my @csource_files;
push @csource_files, 'SPVM.c';
push @csource_files, glob('lib/SPVM/Builder/src/*.c');

my @object_files = map { my $object_file = $_; $object_file =~ s/\.c$/.o/; $object_file } @csource_files;

WriteMakefile(
    NAME              => 'SPVM',
    VERSION_FROM      => 'lib/SPVM.pm', # finds $VERSION
    PREREQ_PM         => {}, # e.g., Module::Name => 1.1
    LICENSE           => 'perl_5',
    ($] >= 5.005 ?     ## Add these new keywords supported since 5.005
      (ABSTRACT_FROM  => 'lib/SPVM.pm', # retrieve abstract from module
       AUTHOR         => 'Yuki Kimoto<kimoto.yuki@gmail.com>') : ()),
    CCFLAGS => $ccflags,
    OPTIMIZE => $optimize,
    C => [@csource_files],
    OBJECT            => '$(O_FILES)', # link all the C files too
    test => {TESTS => 't/*.t t/*/*.t t/*/*/*.t'},
    clean => {FILES => "spvm_build/src spvm_build/work spvm_build/lib spvm_build/exe t/spvm_build/src t/spvm_build/work t/spvm_build/lib @object_files"},
    DEFINE => "@defines -o \$@",
    EXE_FILES => ['script/spvmcc'],
    META_MERGE => {
        'meta-spec' => { version => 2 },
        resources => {
            repository => {
                type => 'git',
                url  => 'https://github.com/yuki-kimoto/SPVM.git',
                web  => 'https://github.com/yuki-kimoto/SPVM',
            },
        },
    },
);

# Create precompile test
my $create_precompile_test_cmd = 'perl t/copy_default_to_precompile.pl';
system('perl t/copy_default_to_precompile.pl') == 0
  or die "Can't execute $create_precompile_test_cmd: $!";

# Add Build shared library make rule
sub MY::postamble {

  my $make_rule = '';
  
  unless (grep { $_ eq '-DSPVM_DONT_USE_CORE_LIB' } @defines) {
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::CORE');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::Example');
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('SPVM::Example');
  }
  
  return $make_rule;
}

1;
