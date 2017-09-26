use 5.008007;
use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.

# SPVM only support the environment 64bit integer is supported
use Config;
use Getopt::Long;
use FindBin;
use lib "$FindBin::Bin/lib";
use SPVM::Build;

my $ivsize = $Config{ivsize};
if ($ivsize < 8) {
  die "SPVM don't support the Perl which \"ivsize\" is lower than 8";
}

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
  my $postamble = SPVM::Build::create_postamble(
    module_names => [
      'SPVM::std',
      'SPVM::Math',
      'SPVM::Float',
    ]
  );
  
  return $postamble;
}


1;
