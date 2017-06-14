use 5.008007;
use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.

WriteMakefile(
    NAME              => 'SPVM',
    VERSION_FROM      => 'lib/SPVM.pm', # finds $VERSION
    PREREQ_PM         => {}, # e.g., Module::Name => 1.1
    ($] >= 5.005 ?     ## Add these new keywords supported since 5.005
      (ABSTRACT_FROM  => 'lib/SPVM.pm', # retrieve abstract from module
       AUTHOR         => 'A. U. Thor <kimoto@sakura.ne.jp>') : ()),
    LIBS              => ['-lm'], # e.g., '-lm'
    DEFINE            => '-DDEBUG', # e.g., '-DHAVE_SOMETHING'
    INC               => '-I.', # e.g., '-I. -I/usr/include/other'
	# Un-comment this if you add C files to link with later:
    # OBJECT            => '$(O_FILES)', # link all the C files too
    CCFLAGS => '-std=c99 -g -Wall -Wextra',
    OPTIMIZE => '-O3',
    OBJECT            => '$(O_FILES)', # link all the C files too
);
