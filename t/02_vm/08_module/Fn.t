use lib "t/testlib";
use TestAuto;
use TestFile;

use strict;
use warnings;
use Config;

use Test::More;

use SPVM 'TestCase::Module::Fn';

use SPVM 'Fn';

use POSIX();

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Note: Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;
my $NaN = 9**9**9 / 9**9**9;
my $nan_re = qr/(nan|ind)/i;

my $seed = time();

# Fn
{
  # Class methods
  {
    ok(SPVM::TestCase::Module::Fn->BYTE_MAX);
    ok(SPVM::TestCase::Module::Fn->BYTE_MIN);
    {
      ok(SPVM::TestCase::Module::Fn->DBL_MAX);
      is(SPVM::Fn->DBL_MAX, POSIX::DBL_MAX);
    }
    {
      ok(SPVM::TestCase::Module::Fn->DBL_MIN);
      is(SPVM::Fn->DBL_MIN, POSIX::DBL_MIN);
    }
    ok(SPVM::TestCase::Module::Fn->DOUBLE_MAX);
    ok(SPVM::TestCase::Module::Fn->DOUBLE_MIN);
    ok(SPVM::TestCase::Module::Fn->FLOAT_MAX);
    ok(SPVM::TestCase::Module::Fn->FLOAT_MIN);
    {
      ok(SPVM::TestCase::Module::Fn->FLT_MAX);
      is(SPVM::Fn->FLT_MAX, POSIX::FLT_MAX);
      like(SPVM::Fn->FLT_MAX(), qr/[0-9]/);
    }
    {
      ok(SPVM::TestCase::Module::Fn->FLT_MIN);
      is(SPVM::Fn->FLT_MIN, POSIX::FLT_MIN);
      like(SPVM::Fn->FLT_MIN(), qr/[0-9]/);
    }
    ok(SPVM::TestCase::Module::Fn->INT16_MAX);
    ok(SPVM::TestCase::Module::Fn->INT16_MIN);
    ok(SPVM::TestCase::Module::Fn->INT32_MAX);
    ok(SPVM::TestCase::Module::Fn->INT32_MIN);
    ok(SPVM::TestCase::Module::Fn->INT8_MAX);
    ok(SPVM::TestCase::Module::Fn->INT8_MIN);
    ok(SPVM::TestCase::Module::Fn->INT_MAX);
    ok(SPVM::TestCase::Module::Fn->INT_MIN);
    ok(SPVM::TestCase::Module::Fn->LONG_MAX);
    ok(SPVM::TestCase::Module::Fn->LONG_MIN);
    ok(SPVM::TestCase::Module::Fn->RAND_MAX);
    ok(SPVM::TestCase::Module::Fn->SHORT_MAX);
    ok(SPVM::TestCase::Module::Fn->SHORT_MIN);
    ok(SPVM::TestCase::Module::Fn->UINT16_MAX);
    ok(SPVM::TestCase::Module::Fn->UINT32_MAX);
    ok(SPVM::TestCase::Module::Fn->UINT64_MAX);
    ok(SPVM::TestCase::Module::Fn->UINT8_MAX);
    ok(SPVM::TestCase::Module::Fn->UBYTE_MAX);
    ok(SPVM::TestCase::Module::Fn->UINT_MAX);
    ok(SPVM::TestCase::Module::Fn->ULONG_MAX);
    ok(SPVM::TestCase::Module::Fn->USHORT_MAX);
    ok(SPVM::TestCase::Module::Fn->abs);
    ok(SPVM::TestCase::Module::Fn->chomp);
    ok(SPVM::TestCase::Module::Fn->chompr);
    ok(SPVM::TestCase::Module::Fn->chr);
    ok(SPVM::TestCase::Module::Fn->contains);
    ok(SPVM::TestCase::Module::Fn->copy_string);
    ok(SPVM::TestCase::Module::Fn->crand($seed));
    ok(SPVM::TestCase::Module::Fn->equals_string_range);
    ok(SPVM::TestCase::Module::Fn->get_code_point);
    ok(SPVM::TestCase::Module::Fn->hex);
    ok(SPVM::TestCase::Module::Fn->index);
    ok(SPVM::TestCase::Module::Fn->init_string);
    ok(SPVM::TestCase::Module::Fn->is_alnum);
    ok(SPVM::TestCase::Module::Fn->is_alpha);
    ok(SPVM::TestCase::Module::Fn->is_array);
    ok(SPVM::TestCase::Module::Fn->is_blank);
    ok(SPVM::TestCase::Module::Fn->is_class);
    ok(SPVM::TestCase::Module::Fn->is_cntrl);
    ok(SPVM::TestCase::Module::Fn->is_digit);
    ok(SPVM::TestCase::Module::Fn->is_graph);
    ok(SPVM::TestCase::Module::Fn->is_hex_digit);
    ok(SPVM::TestCase::Module::Fn->is_lower);
    ok(SPVM::TestCase::Module::Fn->is_mulnum_array);
    ok(SPVM::TestCase::Module::Fn->is_numeric_array);
    ok(SPVM::TestCase::Module::Fn->is_object_array);
    ok(SPVM::TestCase::Module::Fn->is_perl_space);
    ok(SPVM::TestCase::Module::Fn->is_perl_word);
    ok(SPVM::TestCase::Module::Fn->is_pointer_class);
    ok(SPVM::TestCase::Module::Fn->is_print);
    ok(SPVM::TestCase::Module::Fn->is_print);
    ok(SPVM::TestCase::Module::Fn->is_punct);
    ok(SPVM::TestCase::Module::Fn->is_space);
    ok(SPVM::TestCase::Module::Fn->is_upper);
    ok(SPVM::TestCase::Module::Fn->is_xdigit);
    ok(SPVM::TestCase::Module::Fn->join);
    ok(SPVM::TestCase::Module::Fn->labs);
    ok(SPVM::TestCase::Module::Fn->lc);
    ok(SPVM::TestCase::Module::Fn->lcfirst);
    ok(SPVM::TestCase::Module::Fn->look_code_point);
    ok(SPVM::TestCase::Module::Fn->memcpy);
    ok(SPVM::TestCase::Module::Fn->memmove);
    ok(SPVM::TestCase::Module::Fn->ord);
    ok(SPVM::TestCase::Module::Fn->rand($seed));
    ok(SPVM::TestCase::Module::Fn->repeat);
    ok(SPVM::TestCase::Module::Fn->replace_chars);
    ok(SPVM::TestCase::Module::Fn->rindex);
    ok(SPVM::TestCase::Module::Fn->sizeof_native_int);
    {
      is(SPVM::Fn->sizeof_native_pointer, $Config{ptrsize});
    }
    ok(SPVM::TestCase::Module::Fn->shorten);
    ok(SPVM::TestCase::Module::Fn->shorten_null_char);
    ok(SPVM::TestCase::Module::Fn->split);
    ok(SPVM::TestCase::Module::Fn->substr);
    ok(SPVM::TestCase::Module::Fn->to_code_points);
    ok(SPVM::TestCase::Module::Fn->to_double);
    ok(SPVM::TestCase::Module::Fn->to_float);
    ok(SPVM::TestCase::Module::Fn->to_int);
    ok(SPVM::TestCase::Module::Fn->to_int_with_base);
    ok(SPVM::TestCase::Module::Fn->to_long);
    ok(SPVM::TestCase::Module::Fn->to_long_with_base);
    ok(SPVM::TestCase::Module::Fn->to_lower);
    ok(SPVM::TestCase::Module::Fn->to_upper);
    ok(SPVM::TestCase::Module::Fn->to_utf8_chars);
    ok(SPVM::TestCase::Module::Fn->tr);
    ok(SPVM::TestCase::Module::Fn->trim);
    ok(SPVM::TestCase::Module::Fn->uc);
    ok(SPVM::TestCase::Module::Fn->ucfirst);
    ok(SPVM::TestCase::Module::Fn->utf8_length);
    ok(SPVM::TestCase::Module::Fn->utf8_substr);
    
    ok(SPVM::TestCase::Module::Fn->merge_options);
    ok(SPVM::TestCase::Module::Fn->object_to_int);
    ok(SPVM::TestCase::Module::Fn->object_to_long);
    ok(SPVM::TestCase::Module::Fn->get_version_string);
    ok(SPVM::TestCase::Module::Fn->get_version_number);
    {
      my $spvm_version_string = SPVM::Fn->get_spvm_version_string;
      warn "[Test Output]The version of the SPVM language:$spvm_version_string";
      ok(SPVM::Builder::Util::file_contains("lib/SPVM/Builder/include/spvm_version.h", $spvm_version_string));
    }
    {
      my $spvm_version_string = $SPVM::VERSION;
      $spvm_version_string =~ s/_//g;
      
      my $perl_version_number = SPVM::Fn->to_double($spvm_version_string);
      my $spvm_version_number = SPVM::Fn->get_spvm_version_number;
      warn "[Test Output]Perl Version Number:" . sprintf("%.20f", $perl_version_number) . ",SPVM Version Number:" . sprintf("%.20f", $spvm_version_number);
      ok($perl_version_number == $spvm_version_number);
    }
    ok(SPVM::TestCase::Module::Fn->defer);
    
    ok(SPVM::TestCase::Module::Fn->get_memory_blocks_count);
    
    ok(SPVM::TestCase::Module::Fn->to_address);
    
    ok(SPVM::TestCase::Module::Fn->check_option_names);
    
    ok(SPVM::TestCase::Module::Fn->get_basic_type_id);
    
    ok(SPVM::TestCase::Module::Fn->memset_char);
    
    ok(SPVM::TestCase::Module::Fn->or);
    
    ok(SPVM::TestCase::Module::Fn->if);
    
    ok(SPVM::TestCase::Module::Fn->grep);
    
    ok(SPVM::TestCase::Module::Fn->grep_byte);
    
    ok(SPVM::TestCase::Module::Fn->grep_short);
    
    ok(SPVM::TestCase::Module::Fn->grep_int);
    
    ok(SPVM::TestCase::Module::Fn->grep_long);
    
    ok(SPVM::TestCase::Module::Fn->grep_float);
    
    ok(SPVM::TestCase::Module::Fn->grep_double);
    
    ok(SPVM::TestCase::Module::Fn->map);
    
    ok(SPVM::TestCase::Module::Fn->map_expand);
    
    ok(SPVM::TestCase::Module::Fn->get_compile_type_name);
    
    ok(SPVM::TestCase::Module::Fn->is_any_numeric_array);
    
    ok(SPVM::TestCase::Module::Fn->array_length);
    
    ok(SPVM::TestCase::Module::Fn->get_elem_size);
    
    ok(SPVM::TestCase::Module::Fn->get_elem_type_name);
    
    # Tests for Fn#print_stderr is at t/05_op/warn.t
    
    # Tests for Fn#say_stderr is at t/05_op/warn.t
    
    ok(SPVM::TestCase::Module::Fn->memcmp);
    
    ok(SPVM::TestCase::Module::Fn->reverse_inplace);
    
    ok(SPVM::TestCase::Module::Fn->is_string_array);
    
    ok(SPVM::TestCase::Module::Fn->length);
    
    ok(SPVM::TestCase::Module::Fn->get_elem_or_char_size);
    
    ok(SPVM::TestCase::Module::Fn->copy);
    
    ok(SPVM::TestCase::Module::Fn->reverse);
    
    ok(SPVM::TestCase::Module::Fn->slice);
    
    # system_is_little_endian
    {
      my $system_is_little_endian_expected;
      if ($Config{byteorder} =~ /^1234/) {
        $system_is_little_endian_expected = 1;
      }
      
      is(SPVM::Fn->system_is_little_endian, $system_is_little_endian_expected);
    }
    
    ok(SPVM::TestCase::Module::Fn->sprintf);
    
    ok(SPVM::TestCase::Module::Fn->sort_asc);
    
    ok(SPVM::TestCase::Module::Fn->sort_desc);
    
    ok(SPVM::TestCase::Module::Fn->sort);
    
    ok(SPVM::TestCase::Module::Fn->change_endian);
    ok(SPVM::TestCase::Module::Fn->big_endian_to_system_endian);
    ok(SPVM::TestCase::Module::Fn->system_endian_to_big_endian);
    ok(SPVM::TestCase::Module::Fn->little_endian_to_system_endian);
    ok(SPVM::TestCase::Module::Fn->system_endian_to_little_endian);
    ok(SPVM::TestCase::Module::Fn->pack);
    ok(SPVM::TestCase::Module::Fn->unpack);
    ok(SPVM::TestCase::Module::Fn->no_free);
    ok(SPVM::TestCase::Module::Fn->set_no_free);
    ok(SPVM::TestCase::Module::Fn->get_pointer);
    ok(SPVM::TestCase::Module::Fn->set_pointer);
    ok(SPVM::TestCase::Module::Fn->has_null_pointer);
    ok(SPVM::TestCase::Module::Fn->eq_pointer);
    ok(SPVM::TestCase::Module::Fn->pointer_to_string);
    ok(SPVM::TestCase::Module::Fn->dump_object_internal);
    ok(SPVM::TestCase::Module::Fn->get_seed);
    ok(SPVM::TestCase::Module::Fn->get_basic_type_name_in_version_from);
    ok(SPVM::TestCase::Module::Fn->destroy_cache_class_vars);
    ok(SPVM::TestCase::Module::Fn->destroy_runtime_permanent_vars);
    ok(SPVM::TestCase::Module::Fn->range);
    ok(SPVM::TestCase::Module::Fn->to_hash);
    
  }
  
  # Extra
  {
    my $BYTE_MAX = 127;
    my $BYTE_MIN = -128;
    my $SHORT_MAX = 32767;
    my $SHORT_MIN = -32768;
    my $INT_MAX = 2147483647;
    my $INT_MIN = -2147483648;
    my $LONG_MAX = 9223372036854775807;
    my $LONG_MIN = -9223372036854775808;
    
    is(SPVM::Fn->INT16_MAX, $SHORT_MAX);
    is(SPVM::Fn->INT16_MAX, 32767);
    is(SPVM::Fn->INT16_MIN, $SHORT_MIN);
    is(SPVM::Fn->INT16_MIN, -32768);
    is(SPVM::Fn->INT32_MAX, $INT_MAX);
    is(SPVM::Fn->INT32_MAX, 2147483647);
    is(SPVM::Fn->INT32_MIN, $INT_MIN);
    is(SPVM::Fn->INT32_MIN, -2147483648);
    is(SPVM::Fn->INT64_MAX, $LONG_MAX);
    is(SPVM::Fn->INT64_MAX, 9223372036854775807);
    is(SPVM::Fn->INT64_MIN, $LONG_MIN);
    is(SPVM::Fn->INT64_MIN, -9223372036854775808);
    is(SPVM::Fn->INT8_MAX, $BYTE_MAX);
    is(SPVM::Fn->INT8_MAX, 127);
    is(SPVM::Fn->INT8_MIN, $BYTE_MIN);
    is(SPVM::Fn->INT8_MIN, -128);
    is(SPVM::Fn->UINT16_MAX, -1);
    is(SPVM::Fn->UINT32_MAX, -1);
    is(SPVM::Fn->UINT64_MAX, -1);
    is(SPVM::Fn->UINT8_MAX, -1);
    # split
    {
      my $sep = ",";
      my $string = "foo,bar,baz,,";
      {
        is_deeply(SPVM::Fn->split($sep, $string, -1)->to_elems, [split $sep, $string, -1]);
        is_deeply(SPVM::Fn->split($sep, $string)->to_elems, [split $sep, $string, 0]);
        is_deeply(SPVM::Fn->split($sep, $string, 1)->to_elems, [split $sep, $string, 1]);
        is_deeply(SPVM::Fn->split($sep, $string, 2)->to_elems, [split $sep, $string, 2]);
        is_deeply(SPVM::Fn->split($sep, $string, 3)->to_elems, [split $sep, $string, 3]);
      }
    }
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
