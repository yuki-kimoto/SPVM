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
use Time::Piece();

use SPVM::Builder;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/exe/lib";

my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
my $blib_lib = File::Spec->rel2abs('blib/lib');
my $blib_arch = File::Spec->rel2abs('blib/arch');
my $include_blib = "-I$blib_arch -I$blib_lib";

# -h, --help
{
  {
    my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path -h);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\Qusage: spvmdist [<options>] <class_name> [<dir>]/);
  }
  {
    my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --help);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\Qusage: spvmdist [<options>] <class_name> [<dir>]/);
  }
}

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
  my $today_tp = Time::Piece::localtime;
  my $year = $today_tp->year;
  ok(SPVM::Builder::Util::file_contains($perl_module_file, $year));
  ok(SPVM::Builder::Util::file_contains($perl_module_file, '[--user-name]'));
  ok(SPVM::Builder::Util::file_contains($perl_module_file, '[--user-email]'));
  
  my $spvm_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.spvm";
  ok(-f $spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($spvm_module_file, "class Foo {"));
  
  my $makefile_pl_file = "$tmp_dir/SPVM-Foo/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "'SPVM::Foo'"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "'lib/SPVM/Foo.pm'"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "t/*.t t/*/*.t t/*/*/*.t"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "NORECURS => 1"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "CONFIGURE_REQUIRES"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "PREREQ_PM"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "TEST_REQUIRES"));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, 'unless ($meta) {'));
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, q|my %configure_and_runtime_requires = ('SPVM' => |));
  
  my $readme_markdown_file = "$tmp_dir/SPVM-Foo/README.md";
  ok(-f $readme_markdown_file);
  ok(SPVM::Builder::Util::file_contains($readme_markdown_file, "SPVM::Foo"));
  
  my $changes_file = "$tmp_dir/SPVM-Foo/Changes";
  ok(-f $changes_file);
  ok(SPVM::Builder::Util::file_contains($changes_file, "0.01 "));
  my $today = $today_tp->strftime('%Y-%m-%d');
  ok(SPVM::Builder::Util::file_contains($changes_file, $today));
  ok(SPVM::Builder::Util::file_contains($changes_file, '[Changes]'));
  
  my $gitignore_file = "$tmp_dir/SPVM-Foo/.gitignore";
  ok(-f $gitignore_file);
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '/blib/*'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '/Makefile'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '/Makefile.old'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '/MYMETA.yml'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '/MYMETA.json'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '/pm_to_blib'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '/SPVM-*'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '.spvm_build'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, 'core.*'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, 'core'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '*.bak'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '*.BAK'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '*.tmp'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '*.o'));
  ok(SPVM::Builder::Util::file_contains($gitignore_file, '*.bs'));
  
  my $manifest_skip_file = "$tmp_dir/SPVM-Foo/MANIFEST.SKIP";
  ok(-f $manifest_skip_file);
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)blib/'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)Makefile$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)Makefile.old$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)MYMETA.yml$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)MYMETA.json$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)pm_to_blib$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/).spvm_build/'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)t/.spvm_build/'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)SPVM-'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)core\\.'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)core$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '(^|\\/)\\.git/'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '\\.bak$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '\\.tmp$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '\\.tmp/'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '\\.BAK$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '\\.o$'));
  ok(SPVM::Builder::Util::file_contains($manifest_skip_file, '\\.bs$'));
  
  my $basic_test_file = "$tmp_dir/SPVM-Foo/t/basic.t";
  ok(-f $basic_test_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_file, "use SPVM 'TestCase::Foo';"));
  ok(SPVM::Builder::Util::file_contains($basic_test_file, 'BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }'));

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

# Foo::Bar::Baz, --user-name, --user-email
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --user-name Yuki --user-email yuki.com Foo::Bar::Baz);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  my $perl_module_file = "$tmp_dir/SPVM-Foo-Bar-Baz/lib/SPVM/Foo/Bar/Baz.pm";
  ok(-f $perl_module_file);
  ok(SPVM::Builder::Util::file_contains($perl_module_file, "package SPVM::Foo::Bar::Baz;"));
  ok(SPVM::Builder::Util::file_contains($perl_module_file, "Yuki C<"));
  ok(SPVM::Builder::Util::file_contains($perl_module_file, "Yuki,"));
  ok(SPVM::Builder::Util::file_contains($perl_module_file, 'yuki.com'));
  
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

# --native c
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
  ok(SPVM::Builder::Util::file_contains($native_module_file, 'static const char* FILE_NAME = "Foo.c";'));
  ok(SPVM::Builder::Util::file_contains($native_module_file, "SPVM__Foo__foo"));

  my $gitkeep_file_for_native_module_include_dir = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.native/include/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_include_dir);

  my $gitkeep_file_for_native_module_src_dir = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.native/src/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_src_dir);

  chdir($save_cur_dir) or die;
}

# --native c Foo::Bar::Baz
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --native c Foo::Bar::Baz);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $makefile_pl_file = "$tmp_dir/SPVM-Foo-Bar-Baz/Makefile.PL";
  ok(-f $makefile_pl_file);
  ok(SPVM::Builder::Util::file_contains($makefile_pl_file, "\$make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Foo::Bar::Baz')"));

  my $native_config_file = "$tmp_dir/SPVM-Foo-Bar-Baz/lib/SPVM/Foo/Bar/Baz.config";
  ok(-f $native_config_file);
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'use SPVM::Builder::Config;'));
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'SPVM::Builder::Config->new_gnu99'));
  
  my $native_module_file = "$tmp_dir/SPVM-Foo-Bar-Baz/lib/SPVM/Foo/Bar/Baz.c";
  ok(-f $native_module_file);
  ok(SPVM::Builder::Util::file_contains($native_module_file, '#include "spvm_native.h"'));
  ok(SPVM::Builder::Util::file_contains($native_module_file, 'static const char* FILE_NAME = "Foo/Bar/Baz.c";'));
  ok(SPVM::Builder::Util::file_contains($native_module_file, "SPVM__Foo__Bar__Baz__foo"));

  my $gitkeep_file_for_native_module_include_dir = "$tmp_dir/SPVM-Foo-Bar-Baz/lib/SPVM/Foo/Bar/Baz.native/include/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_include_dir);

  my $gitkeep_file_for_native_module_src_dir = "$tmp_dir/SPVM-Foo-Bar-Baz/lib/SPVM/Foo/Bar/Baz.native/src/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_src_dir);

  chdir($save_cur_dir) or die;
}

# --native c++
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

# --precompile
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
  ok(!SPVM::Builder::Util::file_contains($perl_module_file, '$VERSION'));
  
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

# --native c --precompile and perl Makefile.PL && make && make test
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

  ok(SPVM::Builder::Util::file_contains('Makefile', 'build_dynamic_lib_dist_native'));
  ok(SPVM::Builder::Util::file_contains('Makefile', 'build_dynamic_lib_dist_precompile'));
  
  chdir($save_cur_dir) or die;
}

# --native c++ and perl Makefile.PL && make && make test
{
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --native c++ Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";
  
  chdir('SPVM-Foo')
    or die "Can't chdir";
  
  my $make = $Config{make};
  my $ret = system("$^X Makefile.PL && $make && $make test");
  ok($ret == 0);

  ok(SPVM::Builder::Util::file_contains('Makefile', 'build_dynamic_lib_dist_native'));
  
  chdir($save_cur_dir) or die;
}

# --meta
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
  my $ret = system("$^X Makefile.PL --meta");
  ok($ret == 0);

  ok(!SPVM::Builder::Util::file_contains('Makefile', 'build_dynamic_lib_dist_native'));
  ok(!SPVM::Builder::Util::file_contains('Makefile', 'build_dynamic_lib_dist_precompile'));
  
  chdir($save_cur_dir) or die;
}

# --no-build-spvm-modules
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
  my $ret = system("$^X Makefile.PL --no-build-spvm-modules");
  ok($ret == 0);
  
  ok(!SPVM::Builder::Util::file_contains('Makefile', 'build_dynamic_lib_dist_native'));
  ok(!SPVM::Builder::Util::file_contains('Makefile', 'build_dynamic_lib_dist_precompile'));
  
  chdir($save_cur_dir) or die;
}

# --resource and --resource --native c
for my $test_index (0 .. 1) {
  my $native_opt = '';
  if ($test_index == 1) {
    $native_opt = '--native c';
  }
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --resource $native_opt Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $makefile_pl_file = "$tmp_dir/SPVM-Foo/Makefile.PL";
  ok(-f $makefile_pl_file);

  my $spvm_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.spvm";
  ok(!-f $spvm_module_file);

  my $native_config_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.config";
  ok(-f $native_config_file);
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'use SPVM::Builder::Config;'));
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'SPVM::Builder::Config->new_gnu99'));
  
  my $native_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.c";
  ok(!-f $native_module_file);

  my $gitkeep_file_for_native_module_include_dir = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.native/include/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_include_dir);

  my $gitkeep_file_for_native_module_src_dir = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.native/src/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_src_dir);

  my $basic_test_file = "$tmp_dir/SPVM-Foo/t/basic.t";
  ok(-f $basic_test_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_file, "use SPVM 'TestCase::Foo';"));
  ok(SPVM::Builder::Util::file_contains($basic_test_file, 'BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }'));

  my $basic_test_spvm_module_file = "$tmp_dir/SPVM-Foo/t/lib/SPVM/TestCase/Foo.spvm";
  ok(-f $basic_test_spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_spvm_module_file, "class TestCase::Foo {"));
  ok(SPVM::Builder::Util::file_contains($basic_test_spvm_module_file, "native static method test : int ();"));
  
  my $basic_test_native_module_file = "$tmp_dir/SPVM-Foo/t/lib/SPVM/TestCase/Foo.c";
  ok(-f $basic_test_native_module_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_native_module_file, '#include "spvm_native.h"'));
  ok(SPVM::Builder::Util::file_contains($basic_test_native_module_file, "SPVM__TestCase__Foo__test"));
  
  my $basic_test_native_config_file = "$tmp_dir/SPVM-Foo/t/lib/SPVM/TestCase/Foo.config";
  ok(-f $basic_test_native_config_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_native_config_file, 'my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);'));
  ok(SPVM::Builder::Util::file_contains($basic_test_native_config_file, q($config->use_resource('Foo');)));


  chdir($save_cur_dir) or die;
}

# --resource --native c++
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --resource --native c++ Foo);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $makefile_pl_file = "$tmp_dir/SPVM-Foo/Makefile.PL";
  ok(-f $makefile_pl_file);

  my $spvm_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.spvm";
  ok(!-f $spvm_module_file);

  my $native_config_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.config";
  ok(-f $native_config_file);
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'use SPVM::Builder::Config;'));
  ok(SPVM::Builder::Util::file_contains($native_config_file, 'SPVM::Builder::Config->new_cpp'));
  
  my $native_module_file = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.c";
  ok(!-f $native_module_file);

  my $gitkeep_file_for_native_module_include_dir = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.native/include/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_include_dir);

  my $gitkeep_file_for_native_module_src_dir = "$tmp_dir/SPVM-Foo/lib/SPVM/Foo.native/src/.gitkeep";
  ok(-f $gitkeep_file_for_native_module_src_dir);

  my $basic_test_file = "$tmp_dir/SPVM-Foo/t/basic.t";
  ok(-f $basic_test_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_file, "use SPVM 'TestCase::Foo';"));
  ok(SPVM::Builder::Util::file_contains($basic_test_file, 'BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }'));

  my $basic_test_spvm_module_file = "$tmp_dir/SPVM-Foo/t/lib/SPVM/TestCase/Foo.spvm";
  ok(-f $basic_test_spvm_module_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_spvm_module_file, "class TestCase::Foo {"));
  ok(SPVM::Builder::Util::file_contains($basic_test_spvm_module_file, "native static method test : int ();"));
  
  my $basic_test_native_module_file = "$tmp_dir/SPVM-Foo/t/lib/SPVM/TestCase/Foo.cpp";
  ok(-f $basic_test_native_module_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_native_module_file, '#include "spvm_native.h"'));
  ok(SPVM::Builder::Util::file_contains($basic_test_native_module_file, 'extern "C" {'));
  ok(SPVM::Builder::Util::file_contains($basic_test_native_module_file, "SPVM__TestCase__Foo__test"));
  
  my $basic_test_native_config_file = "$tmp_dir/SPVM-Foo/t/lib/SPVM/TestCase/Foo.config";
  ok(-f $basic_test_native_config_file);
  ok(SPVM::Builder::Util::file_contains($basic_test_native_config_file, 'my $config = SPVM::Builder::Config->new_cpp(file => __FILE__);'));
  ok(SPVM::Builder::Util::file_contains($basic_test_native_config_file, q($config->use_resource('Foo');)));


  chdir($save_cur_dir) or die;
}

# --resource and perl Makefile.PL && make && make test
{
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --resource Foo);
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

# --resource --native c++ and perl Makefile.PL && make && make test
{
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --resource --native c++ Foo);
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

# --genlib
{
  my $spvmdist_path = File::Spec->rel2abs('blib/script/spvmdist');
  my $blib = File::Spec->rel2abs('blib/lib');
  
  my $tmp_dir = File::Temp->newdir;
  my $spvmdist_cmd = qq($^X $include_blib $spvmdist_path --genlib --native c Foo mylib);
  my $save_cur_dir = getcwd();
  chdir($tmp_dir) or die;
  system($spvmdist_cmd) == 0
    or die "Can't execute spvmdist command $spvmdist_cmd:$!";

  my $spvm_module_file = "$tmp_dir/mylib/SPVM/Foo.spvm";
  ok(-f $spvm_module_file);

  my $native_config_file = "$tmp_dir/mylib/SPVM/Foo.config";
  ok(-f $native_config_file);
  
  my $native_module_file = "$tmp_dir/mylib/SPVM/Foo.c";
  ok(-f $native_module_file);
  
  my $perl_module_file = "$tmp_dir/mylib/SPVM/Foo.pm";
  ok(!-f $perl_module_file);
  
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
done_testing;
