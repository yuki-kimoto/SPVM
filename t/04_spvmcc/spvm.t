use lib "t/testlib";
use TestAuto;

use Test::More;
use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename', 'dirname';
use Config;
use File::Path 'mkpath', 'rmtree';
use File::Spec;
use SPVM::Builder::Util;
use FindBin;

use SPVM::Builder;
use File::Spec;

my $devnull = File::Spec->devnull;

my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $dev_null = File::Spec->devnull;

# -Mblib, -I, lib directive order
{
  my $lib_directive_a = 'lib_directive_a';
  my $lib_directive_b = 'lib_directive_b';
  my $include_a = 'include_a';
  my $include_b = 'include_b';
  
  # Prepare a source with multiple #lib directives
  my $source = qq|#lib "$lib_directive_a"\n#lib "$lib_directive_b"\nuse NotFoundClass;|;
  
  # Run spvm with:
  #   -Mblib (via $^X)
  #   -Mblib (via spvm script)
  #   -Iinclude_a -Iinclude_b (command line includes)
  my $spvm_cmd = qq|$^X -Mblib blib/script/spvm -Mblib -I $include_a -I $include_b t/04_spvmcc/script/inc-order.spvm|;
  my $output = `$spvm_cmd 2>&1`;
  like($output, qr|lib_directive_b/SPVM.+lib_directive_a/SPVM.+blib/arch/SPVM.+blib/lib/SPVM.+include_a/SPVM.+include_b/SPVM|);
}

# -Mblib option
{
  {
    my $spvm_cmd = qq|$^X -Mblib blib/script/spvm -Mblib -e "use NotFoundClass;"|;
    my $output = `$spvm_cmd 2>&1`;
    
    # Extract the part inside the parentheses (the search paths)
    if ($output =~ /\((.+?)\)/) {
        my $path_string = $1;
        my @paths = split(/ /, $path_string);
        
        # Target paths to check
        my $blib_arch_spvm = 'blib/arch/SPVM';
        my $blib_lib_spvm  = 'blib/lib/SPVM';
        
        # Count occurrences
        my $arch_count = grep { $_ =~ /\Q$blib_arch_spvm\E$/ } @paths;
        my $lib_count  = grep { $_ =~ /\Q$blib_lib_spvm\E$/ } @paths;
        
        # Verify that each path appears at least twice
        cmp_ok($arch_count, '>=', 2, "The path '$blib_arch_spvm' should appear at least twice (Actual: $arch_count)");
        cmp_ok($lib_count, '>=', 2, "The path '$blib_lib_spvm' should appear at least twice (Actual: $lib_count)");
    }
    else {
        fail("Could not find the search path list in the output.");
    }
  }
}

# -c option
{
  {
    my $spvm_cmd = "$^X -Mblib blib/script/spvm -c -I solo/lib/SPVM solo/script/myapp.spvm foo bar";
    my $output = `$spvm_cmd`;
    
    is($output, '');
  }
  
  {
    my $spvm_cmd = "$^X -Mblib blib/script/spvm -c -I solo/lib/SPVM solo/script/myapp.spvm foo bar 2>&1";
    my $output = `$spvm_cmd`;
    
    is($output, "syntax OK\n");
  }
}

# Failed to parse options.
{
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm --not-exist t/04_spvmcc/script/myapp.spvm);
    my $status = system($spvm_cmd);
    isnt($status, 0);
  }
}

{
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I solo/lib/SPVM solo/script/myapp.spvm foo bar);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # -w
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -w -I solo/lib/SPVM solo/script/myapp.spvm foo bar);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # -B
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -B $build_dir -I solo/lib/SPVM solo/script/myapp.spvm foo bar);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  
  # --build-dir and -e
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm --build-dir $build_dir -I solo/lib/SPVM -e "warn q'[Test Output]spvm -e option';");
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # -e, -M
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I solo/lib/SPVM -M Fn -M StringBuffer -e "Fn->INT_MAX; StringBuffer->new;warn q'[Test Output]spvm -e and -M option';");
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # basic
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm $FindBin::Bin/script/basic.spvm);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # lib directive
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm $FindBin::Bin/script/use-class.spvm);
    my $output = `$spvm_cmd`;
    like($output, qr/3000/);
  }
  
  # shebang
  if ($^O eq 'MSWin32') {
    warn "[Test Output]A test for shebang is skipped.";
  }
  else {
    local $ENV{PATH} = "blib/script:$ENV{PATH}";
    local $ENV{PERL5LIB} = "blib/lib:blib/arch:$ENV{PERL5LIB}";
    my $spvm_cmd = qq($FindBin::Bin/script/use-class.spvm);
    my $output = `$spvm_cmd`;
    like($output, qr/3000/);
  }
  
  # prcompile
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I t/04_spvmcc/lib/SPVM $FindBin::Bin/script/precompile.spvm);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # prcompile
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I t/04_spvmcc/lib/SPVM $FindBin::Bin/script/precompile.spvm);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm t/04_spvmcc/script/program_name.spvm);
    my $spvm_output = `$spvm_cmd`;
    like($spvm_output, qr|t/04_spvmcc/script/program_name\.spvm|);
  }
  
  # anon method
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm $FindBin::Bin/script/anon_method.spvm);
    my $output = `$spvm_cmd`;
    like($output, qr/OK/);
  }
  
}


done_testing;
