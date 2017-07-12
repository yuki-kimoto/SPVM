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

WriteMakefile(
    NAME              => 'SPVM',
    VERSION_FROM      => 'lib/SPVM.pm', # finds $VERSION
    PREREQ_PM         => {}, # e.g., Module::Name => 1.1
    ($] >= 5.005 ?     ## Add these new keywords supported since 5.005
      (ABSTRACT_FROM  => 'lib/SPVM.pm', # retrieve abstract from module
       AUTHOR         => 'A. U. Thor <kimoto@sakura.ne.jp>') : ()),
    LIBS              => ['-lm'], # e.g., '-lm'
    INC               => '-I.', # e.g., '-I. -I/usr/include/other'
    OPTIMIZE => '-O3',
    OBJECT            => '$(O_FILES)', # link all the C files too
);
