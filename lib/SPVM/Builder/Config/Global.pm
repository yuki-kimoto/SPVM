package SPVM::Builder::Config::Global;

use parent 'SPVM::Builder::Config::Linker';

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;
use SPVM::Builder::Accessor 'has';

# Fields
my $fields;
BEGIN {
  $fields = [qw(
    before_compile_cbs
    build_type
  )];
  
  has($fields);
}

{
  no warnings 'redefine';
  sub build_type {
    my $self = shift;
    if (@_) {
      my $build_type = $_[0];
      
      my %valid_build_types = map { $_ => 1 } qw(Debug Release RelWithDebInfo MinSizeRel);
      
      unless (defined $build_type && $valid_build_types{$build_type}) {
        my $valid_build_types_string = join(', ', sort keys %valid_build_types);
        confess("The build_type '$build_type' is invalid. It must be one of ($valid_build_types_string).");
      }
      
      $self->{build_type} = $build_type;
      return $self;
    }
    else {
      return $self->{build_type};
    }
  }
}

sub optimize {
  my $self = shift;
  
  if (@_) {
    my ($optimize, $condition) = @_;
    $self->compile_rule($condition, {optimize => $optimize});
    return $self;
  }
  else {
    confess "The optimize method only supports the setter. Use match methods to configure dynamic settings.";
  }
}

sub option_names {
  my ($self) = @_;
  return [@{$self->SUPER::option_names}, @$fields];
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = $class->SUPER::new(
    before_compile_cbs => [],
    @_
  );
  
  if (exists $self->{build_type}) {
    $self->build_type($self->{build_type});
  }
  
  # --- Build type rules (Strict CMake GCC/Clang Compatibility) ---
  # Debug: Just -g (Optimization defaults to -O0 in GCC)
  $self->compile_rule(
    { global => {build_type => 'Debug'} },
    {
      optimize           => '', 
      debug_info_ccflags => ['-g'],
      ndebug_ccflags     => [],
      symbol_strip_ldflags => [],
    }
  );

  # Release: -O3 -DNDEBUG
  $self->compile_rule(
    { global => {build_type => 'Release'} },
    {
      optimize           => '-O3',
      debug_info_ccflags => [],
      ndebug_ccflags     => ['-DNDEBUG'],
    }
  );

  # RelWithDebInfo: -O2 -g -DNDEBUG
  $self->compile_rule(
    { global => {build_type => 'RelWithDebInfo'} },
    {
      optimize           => '-O2',
      debug_info_ccflags => ['-g'],
      ndebug_ccflags     => ['-DNDEBUG'],
    }
  );

  # MinSizeRel: -Os -DNDEBUG
  $self->compile_rule(
    { global => {build_type => 'MinSizeRel'} },
    {
      optimize           => '-Os',
      debug_info_ccflags => [],
      ndebug_ccflags     => ['-DNDEBUG'],
    }
  );
  
  return $self;
}

# Instance Methods
sub add_before_compile_cb {
  my ($self, @before_compile_cbs) = @_;
  
  push @{$self->{before_compile_cbs}}, @before_compile_cbs;
}

sub compile_rule {
  my ($self, $condition, $match_config_or_cb) = @_;
  
  # Normalize condition for key validation
  if (ref $condition eq 'HASH') {
    my %normalized;
    for my $name (keys %$condition) {
      next if $name eq 'global';
      
      # Remove non-word characters (ASCII only)
      my $target_name = $name;
      $target_name =~ s/[^\w]//ga;
      $normalized{$target_name} = $condition->{$name};
    }
    
    # Validate with normalized keys
    SPVM::Builder::Config->new_empty(%normalized);
  }

  # Normalize match_config if it's a hash (not a callback)
  if (ref $match_config_or_cb eq 'HASH') {
    my %normalized;
    for my $name (keys %$match_config_or_cb) {
      # Remove prefix operators like '+', '-', '.'
      my $target_name = $name;
      $target_name =~ s/[^\w]//ga;
      $normalized{$target_name} = $match_config_or_cb->{$name};
    }
    
    # Validate with normalized keys
    SPVM::Builder::Config->new_empty(%normalized);
  }
  
  $self->add_before_compile_cb(sub {
    my ($config) = @_;
    
    &_match_apply($config, $condition, $match_config_or_cb);
  });
}

sub compile_rule_any { shift->compile_rule(undef, @_) }

sub _match_apply {
  my ($config, $condition, $match_config_or_cb) = @_;
  
  if ($condition) {
    $condition = {%$condition};
  }
  my $condition_global = delete $condition->{global};
  
  my $match = 1;
  if ($condition || $condition_global) {
    my $check_match = sub {
      my ($target_h, $cond_h) = @_;
      
      my $inner_match = 1;
      if ($cond_h) {
        for my $name (keys %$cond_h) {
          my $cond_val = $cond_h->{$name};
          my $target_name = $name;
          my $is_not = ($target_name =~ s/^!//);
          
          my $val = $target_h ? $target_h->{$target_name} : undef;
          my @candidates = (defined $val && ref $val eq 'ARRAY') ? @$val : ($val);
          
          my $found = 0;
          for my $c (@candidates) {
            if (ref $cond_val eq 'Regexp') {
              if (defined $c && $c =~ $cond_val) { $found = 1; last; }
            }
            elsif (defined $cond_val) {
              if (defined $c && $c eq $cond_val) { $found = 1; last; }
            }
            else {
              if (!defined $c) { $found = 1; last; }
            }
          }
          
          $found = !$found if $is_not;
          
          unless ($found) {
            $inner_match = 0;
            last;
          }
        }
      }
      
      return $inner_match;
    };
    
    my $match_condition = $check_match->($config, $condition);
    my $match_condition_global = $check_match->($config->{config_global}, $condition_global);
    
    $match = $match_condition && $match_condition_global;
  }
  
  if ($match) {
    if (ref $match_config_or_cb eq 'CODE') {
      $match_config_or_cb->($config);
    }
    else {
      for my $match_name (keys %$match_config_or_cb) {
        my $new_value = $match_config_or_cb->{$match_name};
        
        if ($match_name =~ /^\+(.+)$/) {
          my $name = $1;
          my $old_value = $config->{$name};
          
          if (!defined $old_value) {
            $config->{$name} = $new_value;
          }
          elsif (ref $old_value eq '' && ref $new_value eq '') {
            $config->{$name} .= $new_value;
          }
          elsif (ref $old_value eq '' && ref $new_value eq 'ARRAY') {
            $config->{$name} = [$old_value, @$new_value];
          }
          elsif (ref $old_value eq 'ARRAY' && ref $new_value eq '') {
            push @{$config->{$name}}, $new_value;
          }
          elsif (ref $old_value eq 'ARRAY' && ref $new_value eq 'ARRAY') {
            push @{$config->{$name}}, @$new_value;
          }
          else {
            my $old_value_type = ref $old_value || 'scalar(string)';
            my $new_value_type = ref $new_value || 'scalar(string)';
            confess "The addition of the \"$match_name\" field is not supported for the combination of $old_value_type and $new_value_type.";
          }
        }
        else {
          $config->{$match_name} = $new_value;
        }
      }
    }
  }
}

1;

=head1 Name

SPVM::Builder::Config::Global - Excutable File Config

=head1 Description

The SPVM::Builder::Config::Global class has methods to manipulate the config for the excutable file generated by L<spvmcc> command.

=head1 Usage

  use SPVM::Builder::Config::Global;
  
  my $config_global = SPVM::Builder::Config::Global->new;

=head1 Usage

  use SPVM::Builder::Config::Global;
  
  my $config_global = SPVM::Builder::Config::Global->new;
  
  # Basic conditional update (Exact match)
  # If language is 'c', set optimization to -O3
  $self->compile_rule({language => 'c'}, {optimize => '-O3'});

  # Regex matching and field appending (+)
  # If dialect matches c11/c17, add a specific warning flag
  $self->compile_rule({dialect => qr/^c1[17]$/}, {'+ccflags' => ['-Wpedantic']});

  # Array Sensitivity (Checking if a flag exists in an array)
  # If '-DDEBUG' is already in ccflags, add debug linker flags
  $self->compile_rule({ccflags => '-DDEBUG'}, {'+ldflags' => ['-DEBUG']});

  # Negative Match (!prefix)
  # If '-Zi' is NOT in ccflags, enable linker optimizations
  $self->compile_rule({'!ccflags' => '-Zi'}, {'+ld_optimize' => '-OPT:REF,ICF'});

  # Complex conditions (AND logic)
  # If it's C++ AND dialect is NOT c++11 (e.g. c++14), add exception handling
  $self->compile_rule({language => 'cpp', '!dialect' => 'c++11'}, {
    '+ccflags' => ['-EHsc']
  });

  # Procedural update with a callback
  # Dynamically modify the config object based on custom logic
  $self->compile_rule({language => 'c'}, sub {
    my $config = shift;
    if ($ENV{MY_CUSTOM_OPT}) {
      $config->optimize('-Ofast');
    }
  });

  # Apply to all configurations (compile_rule_any)
  # Ensure all configs have the -nologo flag regardless of any condition
  $self->compile_rule_any({'+ccflags' => ['-nologo']});

  # Reset or global initialization via callback
  # Useful for clearing fields before applying specific rules
  $self->compile_rule_any(sub {
    my $config = shift;
    $config->clear_system_fields;
  });

=head1 Details

=head2 Warning: Should Not Change Compiler Flags

The fields for compiler flags in L<SPVM::Builder::Config> such as L<SPVM::Builder::Config/"cc">, L<SPVM::Builder::Config/"std"> should not be changed.

This is because the compiler flags are used to compile SPVM core source files and a bootstrap source file generagted by C<spvmcc> command.

=head1 Super Class

=over 2

=item * L<SPVM::Builder::Config>

=back

=head1 Fields

=head2 before_compile_cbs

  my $before_compile_cbs = $self->before_compile_cbs;
  $self->before_compile_cbs($before_compile_cbs);

Gets and sets the C<before_compile_cbs> field, an array reference of callbacks that work globally called just before the compile command L</"cc"> is executed.

This affects all compilations.

=head2 optimize

  $config->optimize($optimize, $condition);

Sets C<optimize> field for the configs that match the condition C<$condition>.

This method is a setter-only method. It calls L</"compile_rule"> internally.

If C<$condition> is not defined, the optimization setting is applied to all configs.

Examples:

  # Set -O3 for all configs
  $config->optimize('-O3');
  
  # Set -O2 for native category configs
  $config->optimize('-O2', {category => 'native'});

=head2 build_type

  my $build_type = $config->build_type;
  $config->build_type($build_type);

Sets and gets the C<build_type> field.

The C<build_type> field must be one of the following CMake-compatible values:

=over 2

=item * C<Debug>

=item * C<Release>

=item * C<RelWithDebInfo>

=item * C<MinSizeRel>

=back

If an invalid value is specified, an exception is thrown.

Examples:

  # Set build_type
  $config->build_type('Debug');
  
  # Get build_type
  my $build_type = $config->build_type;

=head1 Methods

=head2 new

  my $config_global = SPVM::Builder::Config::Global->new(%fields);

Create a new L<SPVM::Builder::Config::Global> object with L</"Fields"> and fields of its super classes.

This method calls the C<new> method of its L<super class|/"Inheritance"> given %fields with field default values applied.

Field Default Values:

=over 2

=item * L<output_type|SPVM::Builder::Config/"output_type">

  "exe"

=item * L</"before_compile_cbs">

  []

=item * Other Fields

  undef

=back

=head2 add_before_compile_cb

  $self->add_before_compile_cb(@before_compile_cbs);

Adds @before_compile_cbs to the end of L</"before_compile_cbs"> field.

Examples:

  $self->add_before_compile_cb(sub {
    my ($config, $compile_info) = @_;
    
    my $cc_command = $compile_info->to_command;
    
    # Do something
  });

=head2 compile_rule

  $global_config->compile_rule($condition, $match_config_or_cb);

Adds a rule to dynamically update the configuration before compilation if the given conditions are met.

Parameters:

=over 2

=item * C<$condition>

A hash reference specifying the match criteria. Each key represents a field name in the target configuration.

A match occurs only if B<all> specified conditions in the hash are satisfied (AND logic). For each individual field, the matching behavior is as follows:

=over 4

=item * B<Negative Match (!prefix)>: If a field name starts with B<C<!>> (e.g., C<'!ccflags' => '-O2'>), the condition is B<inverted>. It matches only if the criteria is B<not> met.

=item * B<Array Sensitivity>: If the field value in the target configuration is an B<array reference>, the condition matches if B<at least one element> within that array satisfies the criteria below (OR logic within the array). When combined with the B<C<!>> prefix, it matches only if B<none> of the elements satisfy the criteria.

=item * B<Regex Match>: If the condition value is a C<Regexp> object (e.g., C<qr/.../>), it performs a regex match against the field value (or its elements).

=item * B<Undef Match>: If the condition value is C<undef>, it matches if the target field (or an element within its array) is also C<undef>.

=item * B<String Match>: Otherwise, it performs a string equality check (C<eq>) against the field value (or its elements).

=back

=item * C<$match_config_or_cb>

A hash reference, an L<SPVM::Builder::Config> object, or a code reference (callback).

If it is a hash reference or a config object, the fields in the target configuration are updated. 
You can use the B<C<+>> prefix in the field name to B<append> values instead of overwriting them:

=over 4

=item * B<C<+field => $string>> : If the existing value is a string, it concatenates the new string. If the existing value is an array reference, it pushes the new string into the array.

=item * B<C<+field => $array_ref>> : Pushes the elements of the array reference into the existing array. If the existing value is a scalar, it is promoted to an array before the push.

=back

If it is a code reference, the callback is executed with the target L<SPVM::Builder::Config> object as its first argument. This allows for complex, procedural updates to the configuration.

=back

=head2 compile_rule_any

  $global_config->compile_rule_any($match_config_or_cb);

A syntax sugar for L</"match"> with no conditions. 
The C<$match_config> will be applied to all configurations before compilation.

=cut

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
