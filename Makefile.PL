use 5.008007;
use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.

# SPVM only support the environment 64bit integer is supported
use Config;

my $ivsize = $Config{ivsize};
if ($ivsize < 8) {
  die "SPVM don't support the Perl which \"ivsize\" is lower than 8";
}

use Getopt::Long;

my $debug;
GetOptions('d' => \$debug);

# Edit CCFLAGS
my $ccflags = "$Config{ccflags} -Wall -Wextra";

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
    OPTIMIZE => '-O3',
    OBJECT            => '$(O_FILES)', # link all the C files too
    $debug ? (DEFINE => '-DDEBUG') : ()
);

# Build shared library
sub MY::postamble {

  my $make =<<"EOS";
dynamic :: shared_lib_SPVM__std shared_lib_SPVM__Math

shared_lib_SPVM__std ::
\tperl build_shared_lib.pl --object_dir=. SPVM::std

shared_lib_SPVM__Math ::
\tperl build_shared_lib.pl --object_dir=. SPVM::Math

EOS

  return $make;
}

1;
