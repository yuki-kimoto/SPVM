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
use SPVM::Builder::Config;
use Getopt::Long 'GetOptions';
use File::Basename 'basename';
use File::Copy 'copy';

# Check supported environment
{
  # SPVM only support 64bit integer Perl
  my $ivsize = $Config{ivsize};
  if ($ivsize < 8) {
    warn "SPVM don't support the Perl which \"ivsize\" is lower than 8\n";
    die "OS unsupported\n";
  }

  # SPVM only support NetBSD 7+
  if ($Config{osname} eq 'netbsd' && $Config{osvers} < 7) {
    warn "SPVM don't support NetBSD 6, 5, 4, 3, 2, 1";
    die "OS unsupported\n";
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

my $bconf = SPVM::Builder::Config->new_c99;
$optimize ||= $bconf->get_config('optimize');
my $ccflags = $bconf->get_ccflags;
my $include_dirs = $bconf->get_include_dirs;
my $inc = join(' ', map { "-I$_" } @$include_dirs);
my $extra_compiler_flags = $bconf->get_extra_compiler_flags;

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
    CCFLAGS => "$ccflags $extra_compiler_flags",
    OPTIMIZE => $optimize,
    C => [@csource_files],
    INC => $inc,
    OBJECT            => '$(O_FILES)', # link all the C files too
    test => {TESTS => 't/*.t t/*/*.t t/*/*/*.t'},
    clean => {FILES => "spvm_build/work t/default/spvm_build/work t/default/lib/UseAllTestCase.spvm t/precompile t/exe/spvm_build/work t/test_files_tmp @object_files"},
    DEFINE => "@defines -o \$@",
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
  
  unless (grep { $_ eq '-DSPVM_DONT_COMPILE_CORE_MODULES' } @defines) {
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::Util');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::Math');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::Hash');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::Time');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::Unicode');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::Sort');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::IO::FileHandle');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::IO::File');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::IO::Stdout');
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('SPVM::IO::Stderr');
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('SPVM::Util');
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('SPVM::Sort');
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('SPVM::Regex');
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('SPVM::Unicode');
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('SPVM::Hash');
  }
  
  return $make_rule;
}

1;
