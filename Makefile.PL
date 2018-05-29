use 5.008007;
use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.

# SPVM only support the environment 64bit integer is supported
use Config;
use Getopt::Long;
use FindBin;
use lib "$FindBin::Bin/lib";
use SPVM::Build::PPUtil;

my $extutil= SPVM::Build::PPUtil->new;

my $ivsize = $Config{ivsize};
if ($ivsize < 8) {
  die "SPVM don't support the Perl which \"ivsize\" is lower than 8";
}

if ($Config{osname} eq 'netbsd' && $Config{osvers} < 7) {
  die "SPVM don't support NetBSD 6, 5, 4, 3, 2, 1";
}

my $debug;
GetOptions('d' => \$debug);

# Edit CCFLAGS
my $ccflags = "$Config{ccflags} " . $extutil->extra_compiler_flags;

WriteMakefile(
    NAME              => 'SPVM',
    VERSION_FROM      => 'lib/SPVM.pm', # finds $VERSION
    PREREQ_PM         => {}, # e.g., Module::Name => 1.1
    ($] >= 5.005 ?     ## Add these new keywords supported since 5.005
      (ABSTRACT_FROM  => 'lib/SPVM.pm', # retrieve abstract from module
       AUTHOR         => 'A. U. Thor <kimoto@sakura.ne.jp>') : ()),
    LIBS              => ['-lm'], # e.g., '-lm'
    INC               => '-I. -Ilib/SPVM', # e.g., '-I. -I/usr/include/other'
    CCFLAGS => $ccflags,
    OPTIMIZE => $extutil->optimize,
    OBJECT            => '$(O_FILES)', # link all the C files too
    $debug ? (DEFINE => '-DDEBUG') : (),
    test => {TESTS => 't/*.t t/*/*.t t/*/*/*.t'}
);


# Add Build shared library make rule
sub MY::postamble {
  
  my @module_names = qw(
    SPVM::Math
    SPVM::TypeUtil
  );
  
  my $make_rule = '';
  for my $module_name (@module_names) {
    $make_rule .= $extutil->create_build_shared_lib_make_rule($module_name);
  }
  
  return $make_rule;
}

1;
