use 5.008007;
use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.

# SPVM only support the environment 64bit integer is supported
use Config;
use Getopt::Long;
use FindBin;
use lib "$FindBin::Bin/lib";
use SPVM::Build::Util;

my $ivsize = $Config{ivsize};
if ($ivsize < 8) {
  die "SPVM don't support the Perl which \"ivsize\" is lower than 8";
}

if ($Config{osname} eq 'netbsd' && $Config{osvers} < 7) {
  die "SPVM don't support NetBSD 6, 5, 4, 3, 2, 1";
}

my $debug;
GetOptions('d' => \$debug);

my $build_setting = SPVM::Build::Util::default_build_setting;
my $optimize = $build_setting->get_config('optimize');
my $ccflags = "$Config{ccflags} " . join(' ', @{$build_setting->get_extra_compiler_flags});

WriteMakefile(
    NAME              => 'SPVM',
    VERSION_FROM      => 'lib/SPVM.pm', # finds $VERSION
    PREREQ_PM         => {}, # e.g., Module::Name => 1.1
    LICENSE           => 'perl_5',
    ($] >= 5.005 ?     ## Add these new keywords supported since 5.005
      (ABSTRACT_FROM  => 'lib/SPVM.pm', # retrieve abstract from module
       AUTHOR         => 'A. U. Thor <kimoto@sakura.ne.jp>') : ()),
    LIBS              => ['-lm'], # e.g., '-lm'
    INC               => '-I. -Ilib/SPVM', # e.g., '-I. -I/usr/include/other'
    CCFLAGS => $ccflags,
    OPTIMIZE => $optimize,
    OBJECT            => '$(O_FILES)', # link all the C files too
    $debug ? (DEFINE => '-DDEBUG') : (),
    test => {TESTS => 't/*.t t/*/*.t t/*/*/*.t'},
    clean => {FILES => "spvm_build/src spvm_build/work spvm_build/lib t/spvm_build/src t/spvm_build/work t/spvm_build/lib"},
);


# Add Build shared library make rule
sub MY::postamble {

  my $make_rule = '';
  
  my @native_package_names = qw(
    SPVM::Example
  );
  
  for my $native_package_name (@native_package_names) {
    $make_rule .= SPVM::Build::Util::create_make_rule_native($native_package_name);
  }

  my @precompile_package_names = qw(
    SPVM::Example
  );
  
  for my $precompile_package_name (@precompile_package_names) {
    $make_rule .= SPVM::Build::Util::create_make_rule_precompile($precompile_package_name);
  }

  return $make_rule;
}

1;
