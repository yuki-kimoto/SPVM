use Test::More;
use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use Config;
use File::Path 'mkpath', 'rmtree';
use File::Spec;
use SPVM::Builder::Util;
use File::Temp();
use Cwd 'getcwd';

use SPVM::Builder;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/exe/lib";

# Minimal
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X -I$blib $spvmdist_path Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  my $perl_module_file = "$tmp_dir/Foo/lib/SPVM/Foo.pm";
  ok(-f $perl_module_file);
  ok(SPVM::Builder::Util::file_contains($perl_module_file, "package SPVM::Foo;"));
  ok(SPVM::Builder::Util::file_contains($perl_module_file, q(our $VERSION = '0.01')));
  
  my $spvm_module_file = "$tmp_dir/Foo/lib/SPVM/Foo.spvm";
  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo {"));
  
  my $makefile_pl_file = "$tmp_dir/Foo/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "'Foo'"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "'lib/SPVM/Foo.pm'"));
  
  my $readme_markdown_file = "$tmp_dir/Foo/README.md";
  ok(-f $readme_markdown_file);
  ok(SPVM::Builder::Util::file_contains($readme_markdown_file, "SPVM::Foo"));
  
  my $changes_file = "$tmp_dir/Foo/Changes";
  ok(-f $changes_file);
  ok(SPVM::Builder::Util::file_contains($changes_file, "0.01 "));
  
  my $gitignore_file = "$tmp_dir/Foo/.gitignore";
  ok(-f $gitignore_file);
  ok(SPVM::Builder::Util::file_contains($gitignore_file, "Makefile"));
  
  my $manifest_skip_file = "$tmp_dir/Foo/MANIFEST.SKIP";
  ok(-f $manifest_skip_file);
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, "Makefile"));
  
  my $basic_test_file = "$tmp_dir/Foo/t/basic.t";
  ok(-f $basic_test_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_file, "use SPVM 'Foo';"));

  chdir($save_cur_dir) or die;
}

# Native C
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X -I$blib $spvmdist_path --native c Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $makefile_pl_file = "$tmp_dir/Foo/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "SPVM::Builder::Util::API::create_make_rule_native('Foo')"));

  my $native_config_file = "$tmp_dir/Foo/lib/SPVM/Foo.config";
  ok(-f $native_config_file);
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'use SPVM::Builder::Config;'));
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'SPVM::Builder::Config->new_gnu99'));
  
  my $native_module_file = "$tmp_dir/Foo/lib/SPVM/Foo.c";
  ok(-f $native_module_file);
  ok(SPVM::Builder::Util::file_contains($native_module_file, '#include "spvm_native.h"'));
  ok(SPVM::Builder::Util::file_contains($native_module_file, "SPVM__Foo__foo"));

  chdir($save_cur_dir) or die;
}

# Native C++
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X -I$blib $spvmdist_path --native c++ Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $makefile_pl_file = "$tmp_dir/Foo/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "SPVM::Builder::Util::API::create_make_rule_native('Foo')"));

  my $native_config_file = "$tmp_dir/Foo/lib/SPVM/Foo.config";
  ok(-f $native_config_file);
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'use SPVM::Builder::Config;'));
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'SPVM::Builder::Config->new_cpp'));
  
  my $native_module_file = "$tmp_dir/Foo/lib/SPVM/Foo.cpp";
  ok(-f $native_module_file);
  ok(SPVM::Builder::Util::file_contains($native_module_file, '#include "spvm_native.h"'));
  ok(SPVM::Builder::Util::file_contains($native_module_file, 'extern "C" {'));
  ok(SPVM::Builder::Util::file_contains($native_module_file, "SPVM__Foo__foo"));

  chdir($save_cur_dir) or die;
}

done_testing;
