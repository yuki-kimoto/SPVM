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

my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
my $blib_lib = File::Spec->rel2abs('blib/lib');
my $blib_arch = File::Spec->rel2abs('blib/arch');
my $include_blib = "-I$blib_arch -I$blib_lib";

# Minimal
{
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  my $perl_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.pm";
  ok(-f $perl_module_file);
  ok(SPVM::Builder::Util::file_contains($perl_module_file, "package SPVM::Foo;"));
  ok(SPVM::Builder::Util::file_contains($perl_module_file, q(our $VERSION = '0.01')));
  
  my $spvm_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.spvm";
  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo {"));
  
  my $makefile_pl_file = "$tmp_dir/SPVM-Foo/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "'SPVM::Foo'"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "'lib/SPVM/Foo.pm'"));
  
  my $readme_markdown_file = "$tmp_dir/SPVM-Foo/README.md";
  ok(-f $readme_markdown_file);
  ok(SPVM::Builder::Util::file_contains($readme_markdown_file, "SPVM::Foo"));
  
  my $changes_file = "$tmp_dir/SPVM-Foo/Changes";
  ok(-f $changes_file);
  ok(SPVM::Builder::Util::file_contains($changes_file, "0.01 "));
  
  my $gitignore_file = "$tmp_dir/SPVM-Foo/.gitignore";
  ok(-f $gitignore_file);
  ok(SPVM::Builder::Util::file_contains($gitignore_file, "Makefile"));
  
  my $manifest_skip_file = "$tmp_dir/SPVM-Foo/MANIFEST.SKIP";
  ok(-f $manifest_skip_file);
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, "Makefile"));
  
  my $basic_test_file = "$tmp_dir/SPVM-Foo/t/basic.t";
  ok(-f $basic_test_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_file, "use SPVM 'TestCase::Foo';"));

  my $basic_test_spvm_module_file = "$tmp_dir/SPVM-Foo/t/lib/SPVM/TestCase/Foo.spvm";
  ok(-f $basic_test_spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_spvm_module_file, "class TestCase::Foo {"));
  ok(SPVM::Builder::Util::file_contains($basic_test_spvm_module_file, "static method test : int () {"));
  
  chdir($save_cur_dir) or die;
}

# Run again
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  # Run again
  my $output = `$spvmdist_cmd`;
  like($output, qr/\[exists\]/);
  
  my $perl_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.pm";
  ok(-f $perl_module_file);
  ok(SPVM::Builder::Util::file_contains($perl_module_file, "package SPVM::Foo;"));
  ok(SPVM::Builder::Util::file_contains($perl_module_file, q(our $VERSION = '0.01')));
  
  my $spvm_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.spvm";
  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo {"));
  
  my $makefile_pl_file = "$tmp_dir/SPVM-Foo/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "'SPVM::Foo'"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "'lib/SPVM/Foo.pm'"));
  
  my $readme_markdown_file = "$tmp_dir/SPVM-Foo/README.md";
  ok(-f $readme_markdown_file);
  ok(SPVM::Builder::Util::file_contains($readme_markdown_file, "SPVM::Foo"));
  
  my $changes_file = "$tmp_dir/SPVM-Foo/Changes";
  ok(-f $changes_file);
  ok(SPVM::Builder::Util::file_contains($changes_file, "0.01 "));
  
  my $gitignore_file = "$tmp_dir/SPVM-Foo/.gitignore";
  ok(-f $gitignore_file);
  ok(SPVM::Builder::Util::file_contains($gitignore_file, "Makefile"));
  
  my $manifest_skip_file = "$tmp_dir/SPVM-Foo/MANIFEST.SKIP";
  ok(-f $manifest_skip_file);
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, "Makefile"));
  
  my $basic_test_file = "$tmp_dir/SPVM-Foo/t/basic.t";
  ok(-f $basic_test_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_file, 'use lib "$FindBin::Bin/lib";'));
  ok(SPVM::Builder::Util::file_contains($basic_test_file, "use SPVM 'TestCase::Foo';"));
  ok(SPVM::Builder::Util::file_contains($basic_test_file, "ok(SPVM::TestCase::Foo->test);"));

  chdir($save_cur_dir) or die;
}

# Foo::Bar::Baz
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path Foo::Bar::Baz);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  my $perl_module_file = "$tmp_dir/SPVM-Foo-Bar-Baz/lib/SPVM/Foo/Bar/Baz.pm";
  ok(-f $perl_module_file);
  ok(SPVM::Builder::Util::file_contains($perl_module_file, "package SPVM::Foo::Bar::Baz;"));
  
  my $spvm_module_file = "$tmp_dir/SPVM-Foo-Bar-Baz/lib/SPVM//Foo/Bar/Baz.spvm";
  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo::Bar::Baz {"));
  
  my $basic_test_file = "$tmp_dir/SPVM-Foo-Bar-Baz/t/basic.t";
  ok(-f $basic_test_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_file, "use SPVM 'TestCase::Foo::Bar::Baz';"));

  my $basic_test_spvm_module_file = "$tmp_dir/SPVM-Foo-Bar-Baz/t/lib/SPVM/TestCase/Foo/Bar/Baz.spvm";
  ok(-f $basic_test_spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_spvm_module_file, "class TestCase::Foo::Bar::Baz {"));
  ok(SPVM::Builder::Util::file_contains($basic_test_spvm_module_file, "static method test : int () {"));

  chdir($save_cur_dir) or die;
}

# Output directory
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path Foo myfoo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  my $perl_module_file = "$tmp_dir/myfoo/lib/SPVM/Foo.pm";
  ok(-f $perl_module_file);
  ok(SPVM::Builder::Util::file_contains($perl_module_file, "package SPVM::Foo;"));
  
  chdir($save_cur_dir) or die;
}

# Native C
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --native c Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $makefile_pl_file = "$tmp_dir/SPVM-Foo/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "\$make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Foo')"));

  my $native_config_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.config";
  ok(-f $native_config_file);
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'use SPVM::Builder::Config;'));
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'SPVM::Builder::Config->new_gnu99'));
  
  my $native_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.c";
  ok(-f $native_module_file);
  ok(SPVM::Builder::Util::file_contains($native_module_file, '#include "spvm_native.h"'));
  ok(SPVM::Builder::Util::file_contains($native_module_file, "SPVM__Foo__foo"));

  my $gitkeep_file_for_native_module_include_dir = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.native/include/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_include_dir);

  my $gitkeep_file_for_native_module_src_dir = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.native/src/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_src_dir);

  chdir($save_cur_dir) or die;
}

# Native C++
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --native c++ Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $makefile_pl_file = "$tmp_dir/SPVM-Foo/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "\$make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Foo')"));

  my $native_config_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.config";
  ok(-f $native_config_file);
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'use SPVM::Builder::Config;'));
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'SPVM::Builder::Config->new_cpp'));
  
  my $native_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.cpp";
  ok(-f $native_module_file);
  ok(SPVM::Builder::Util::file_contains($native_module_file, '#include "spvm_native.h"'));
  ok(SPVM::Builder::Util::file_contains($native_module_file, 'extern "C" {'));
  ok(SPVM::Builder::Util::file_contains($native_module_file, "SPVM__Foo__foo"));

  chdir($save_cur_dir) or die;
}

# Precompile
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --precompile Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $makefile_pl_file = "$tmp_dir/SPVM-Foo/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "\$make_rule .= SPVM::Builder::Util::API::create_make_rule_precompile('Foo')"));

  my $native_config_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.config";
  ok(!-f $native_config_file);
  
  my $native_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.c";
  ok(!-f $native_module_file);

  chdir($save_cur_dir) or die;
}

# only-lib-files
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --only-lib-files --native c Foo mylib);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $perl_module_file = "$tmp_dir/mylib/SPVM/Foo.pm";
  ok(-f $perl_module_file);
  
  my $spvm_module_file = "$tmp_dir/mylib/SPVM/Foo.spvm";
  ok(-f $spvm_module_file);
  
  my $native_config_file = "$tmp_dir/mylib/SPVM/Foo.config";
  ok(-f $native_config_file);
  
  my $native_module_file = "$tmp_dir/mylib/SPVM/Foo.c";
  ok(-f $native_module_file);

  my $makefile_pl_file = "$tmp_dir/SPVM-Foo/Makefile.PL";
  ok(!-f $makefile_pl_file);
  
  my $readme_markdown_file = "$tmp_dir/SPVM-Foo/README.md";
  ok(!-f $readme_markdown_file);
  
  my $changes_file = "$tmp_dir/SPVM-Foo/Changes";
  ok(!-f $changes_file);
  
  my $gitignore_file = "$tmp_dir/SPVM-Foo/.gitignore";
  ok(!-f $gitignore_file);
  
  my $manifest_skip_file = "$tmp_dir/SPVM-Foo/MANIFEST.SKIP";
  ok(!-f $manifest_skip_file);
  
  my $basic_test_file = "$tmp_dir/SPVM-Foo/t/basic.t";
  ok(!-f $basic_test_file);

  chdir($save_cur_dir) or die;
}

# --no-pm-file
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --no-pm-file Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  my $perl_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.pm";
  ok(!-f $perl_module_file);
  
  my $spvm_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.spvm";
  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo {"));

  chdir($save_cur_dir) or die;
}

# --force
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  my $spvm_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.spvm";
  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo {"));
  
  SPVM::Builder::Util::spurt_binary($spvm_module_file, 'AAAAA');
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "AAAA"));

  my $spvmdist_cmd_fource = qq($^X $include_blib $spvmdist_path --force Foo);
  system($spvmdist_cmd_fource) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo {"));
  
  chdir($save_cur_dir) or die;
}

# -f
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  my $spvm_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.spvm";
  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo {"));
  
  SPVM::Builder::Util::spurt_binary($spvm_module_file, 'AAAAA');
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "AAAA"));

  my $spvmdist_cmd_fource = qq($^X $include_blib $spvmdist_path -f Foo);
  system($spvmdist_cmd_fource) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo {"));
  
  chdir($save_cur_dir) or die;
}

# perl Makefile.PL && make && make test
{
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  chdir($save_cur_dir) or die;
}

# perl Makefile.PL && make && make test
{
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --native c --precompile Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  chdir('SPVM-Foo')
    or die "Can't chdir";
  
  my $make = $Config{make};
  my $ret = system("$^X Makefile.PL && $make && $make test");
  ok($ret == 0);
  
  chdir($save_cur_dir) or die;
}

done_testing;
