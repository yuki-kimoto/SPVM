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

# Check supported environment
{
  # SPVM only support 64bit integer Perl
  my $ivsize = $Config{ivsize};
  if ($ivsize < 8) {
    die "SPVM don't support the Perl which \"ivsize\" is lower than 8";
  }

  # SPVM only support NetBSD 7+
  if ($Config{osname} eq 'netbsd' && $Config{osvers} < 7) {
    die "SPVM don't support NetBSD 6, 5, 4, 3, 2, 1";
  }

  # Uunatural ccflags is not supported
  # for example
  # -D_REENTRANT -D_GNU_SOURCE -O2 -W -Wformat=2 -Wswitch -Wshadow -Wwrite-strings -Wuninitialized -Wall -pipe -mtune=native -march=native -fomit-frame-pointer -mfpmath=sse -pedantic -D_FORTIFY_SOURCE=2 -Wpointer-arith -Wstrict-prototypes -fstack-protector -Wstack-protector -Wextra -Wbad-function-cast -Wcast-align -Wcast-qual -Wdisabled-optimization -Wendif-labels -Wfloat-equal -Wformat-nonliteral -Winline -Wmissing-declarations -Wmissing-prototypes -Wnested-externs -Wpointer-arith -Wundef -Wformat-security -fno-strict-aliasing -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
  my $original_ccflag = $Config{ccflags};
  my $original_ccflag_warnings_count = ($original_ccflag =~ s/-W/-W/g) || 0;
  if ($original_ccflag_warnings_count > 5) {
    die "SPVM don't support unnatural ccflags $original_ccflag";
  }
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
    clean => {FILES => "spvm_build/work t/default/spvm_build/work t/default/lib/UseAllTestCase.spvm t/precompile t/exe/spvm_build/work t/test_files_tmp @object_files"},
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

# Create use all test modules script
my $create_use_all_testcase_cmd = 'perl t/create_use_all_testcase.pl';
system($create_use_all_testcase_cmd) == 0
  or die "Can't execute $create_use_all_testcase_cmd: $!";

# Create precompile test
my $create_precompile_test_cmd = 'perl t/copy_default_to_precompile.pl';
system($create_precompile_test_cmd) == 0
  or die "Can't execute $create_precompile_test_cmd: $!";

# Add Build shared library make rule
sub MY::postamble {

  my $make_rule = '';
  
  unless (grep { $_ eq '-DSPVM_DONT_USE_CORE_LIB' } @defines) {
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::CORE');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::FileHandle');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::Socket');
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('SPVM::CORE');
  }
  
  return $make_rule;
}

1;
