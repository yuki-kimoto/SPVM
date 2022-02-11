use strict;
use warnings;
use Config;

use lib 'lib';
use SPVM::Builder::Util;
use SPVM::Builder::Config;
use Getopt::Long 'GetOptions';
use File::Basename 'basename';

GetOptions(
  "DEFINE=s" => \my @defines,
  "OPTIMIZE=s" => \my $optimize,
);

unless (defined $optimize) {
  $optimize = '-O3';
}

# Add -D
@defines = map { "-D$_" } @defines;

# CCFLAGS
my $ccflags .= '-std=gnu99';

# INC
my $inc = '-Ilib/SPVM/Builder/include';

my $object_dir = 'solo';

my $cccmd = "cc -c @defines $ccflags $optimize $inc";
my $ldcmd = "cc ";

my @source_files = qw(
  lib/SPVM/Builder/src/spvm_allocator.c
  lib/SPVM/Builder/src/spvm_allow.c
  lib/SPVM/Builder/src/spvm_api.c
  lib/SPVM/Builder/src/spvm_array_field_access.c
  lib/SPVM/Builder/src/spvm_basic_type.c
  lib/SPVM/Builder/src/spvm_block.c
  lib/SPVM/Builder/src/spvm_call_method.c
  lib/SPVM/Builder/src/spvm_case_info.c
  lib/SPVM/Builder/src/spvm_class.c
  lib/SPVM/Builder/src/spvm_class_var_access.c
  lib/SPVM/Builder/src/spvm_class_var.c
  lib/SPVM/Builder/src/spvm_compatible.c
  lib/SPVM/Builder/src/spvm_compiler.c
  lib/SPVM/Builder/src/spvm_constant.c
  lib/SPVM/Builder/src/spvm_csource_builder_precompile.c
  lib/SPVM/Builder/src/spvm_descriptor.c
  lib/SPVM/Builder/src/spvm_dumper.c
  lib/SPVM/Builder/src/spvm_enumeration.c
  lib/SPVM/Builder/src/spvm_enumeration_value.c
  lib/SPVM/Builder/src/spvm_field_access.c
  lib/SPVM/Builder/src/spvm_field.c
  lib/SPVM/Builder/src/spvm_hash.c
  lib/SPVM/Builder/src/spvm_list.c
  lib/SPVM/Builder/src/spvm_method.c
  lib/SPVM/Builder/src/spvm_my.c
  lib/SPVM/Builder/src/spvm_op.c
  lib/SPVM/Builder/src/spvm_op_checker.c
  lib/SPVM/Builder/src/spvm_opcode_array.c
  lib/SPVM/Builder/src/spvm_opcode_builder.c
  lib/SPVM/Builder/src/spvm_opcode.c
  lib/SPVM/Builder/src/spvm_string_buffer.c
  lib/SPVM/Builder/src/spvm_switch_info.c
  lib/SPVM/Builder/src/spvm_toke.c
  lib/SPVM/Builder/src/spvm_type.c
  lib/SPVM/Builder/src/spvm_use.c
  lib/SPVM/Builder/src/spvm_var.c
  lib/SPVM/Builder/src/spvm_yacc.c
  lib/SPVM/Builder/src/spvm_yacc_util.c
);

my @object_files = map { my $object_file = basename $_; $object_file =~ s/\.c$/.o/; "solo/work/$object_file" } @source_files;

my @cccmds = map { "$cccmd -o $object_files[$_] $source_files[$_]" } (0 .. @source_files - 1);
push @cccmds, "$cccmd -o solo/work/myexe.o solo/myexe.c";

my $makefile = <<"EOS";

all:
\tmkdir -p solo/work
EOS

$makefile .= join("\n", map { "\t$_" } @cccmds) . "\n";

$makefile .= <<"EOS";
\t$ldcmd -o solo/work/myexe solo/work/myexe.o @object_files

clean:
\trm -rf solo/work
\trm -rf solo/Makefile
EOS

my $makefile_file = 'solo/Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;
