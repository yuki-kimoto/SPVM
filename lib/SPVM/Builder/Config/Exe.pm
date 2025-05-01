package SPVM::Builder::Config::Exe;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;

# Super Class
use base 'SPVM::Builder::Config';

# Fields
sub before_compile_cbs_global {
  my $self = shift;
  if (@_) {
    $self->{before_compile_cbs_global} = $_[0];
    return $self;
  }
  else {
    return $self->{before_compile_cbs_global};
  }
}

sub ccflags_global {
  my $self = shift;
  if (@_) {
    $self->{ccflags_global} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_global};
  }
}

sub ccflags_spvm {
  my $self = shift;
  if (@_) {
    $self->{ccflags_spvm} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_spvm};
  }
}

sub ccflags_native {
  my $self = shift;
  if (@_) {
    $self->{ccflags_native} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_native};
  }
}

sub ccflags_native_class {
  my $self = shift;
  my $class_name = shift;
  
  unless (defined $class_name) {
    return $self->{ccflags_native_class};
  }
  
  if (@_) {
    $self->{ccflags_native_class}{$class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_native_class}{$class_name};
  }
}

sub ccflags_precompile {
  my $self = shift;
  if (@_) {
    $self->{ccflags_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_precompile};
  }
}

sub defines_global {
  my $self = shift;
  if (@_) {
    $self->{defines_global} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_global};
  }
}

sub defines_spvm {
  my $self = shift;
  if (@_) {
    $self->{defines_spvm} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_spvm};
  }
}

sub defines_native {
  my $self = shift;
  if (@_) {
    $self->{defines_native} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_native};
  }
}

sub defines_native_class {
  my $self = shift;
  my $class_name = shift;
  
  unless (defined $class_name) {
    return $self->{defines_native_class};
  }
  
  if (@_) {
    $self->{defines_native_class}{$class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_native_class}{$class_name};
  }
}

sub defines_precompile {
  my $self = shift;
  if (@_) {
    $self->{defines_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_precompile};
  }
}

sub optimize_global {
  my $self = shift;
  if (@_) {
    $self->{optimize_global} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_global};
  }
}

sub optimize_spvm {
  my $self = shift;
  if (@_) {
    $self->{optimize_spvm} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_spvm};
  }
}

sub optimize_native {
  my $self = shift;
  if (@_) {
    $self->{optimize_native} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_native};
  }
}

sub optimize_native_class {
  my $self = shift;
  my $class_name = shift;
  
  unless (defined $class_name) {
    return $self->{optimize_native_class};
  }
  
  if (@_) {
    $self->{optimize_native_class}{$class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_native_class}{$class_name};
  }
}

sub optimize_precompile {
  my $self = shift;
  if (@_) {
    $self->{optimize_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_precompile};
  }
}

sub include_dirs_global {
  my $self = shift;
  if (@_) {
    $self->{include_dirs_global} = $_[0];
    return $self;
  }
  else {
    return $self->{include_dirs_global};
  }
}

sub include_dirs_spvm {
  my $self = shift;
  if (@_) {
    $self->{include_dirs_spvm} = $_[0];
    return $self;
  }
  else {
    return $self->{include_dirs_spvm};
  }
}

sub include_dirs_native {
  my $self = shift;
  if (@_) {
    $self->{include_dirs_native} = $_[0];
    return $self;
  }
  else {
    return $self->{include_dirs_native};
  }
}

sub include_dirs_native_class {
  my $self = shift;
  my $class_name = shift;
  
  unless (defined $class_name) {
    return $self->{include_dirs_native_class};
  }
  
  if (@_) {
    $self->{include_dirs_native_class}{$class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{include_dirs_native_class}{$class_name};
  }
}

sub include_dirs_precompile {
  my $self = shift;
  if (@_) {
    $self->{include_dirs_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{include_dirs_precompile};
  }
}

# Class Methods
sub new {
  my $self = shift;
  
  my $default_config = SPVM::Builder::Util::API::create_default_config();
  
  my %fields = (
    %$default_config,
    output_type => 'exe',
    before_compile_cbs_global => [],
    ccflags_global => [],
    ccflags_spvm => [],
    ccflags_native => [],
    ccflags_native_class => {},
    ccflags_precompile => [],
    defines_global => [],
    defines_spvm => [],
    defines_native => [],
    defines_native_class => {},
    defines_precompile => [],
    optimize_native_class => {},
    include_dirs_global => [],
    include_dirs_spvm => [],
    include_dirs_native => [],
    include_dirs_native_class => {},
    include_dirs_precompile => [],
    @_,
  );
  
  $self = $self->SUPER::new(%fields);
  
  return $self;
}

# Instance Methods
sub add_before_compile_cb_global {
  my ($self, @before_compile_cbs_global) = @_;
  
  push @{$self->{before_compile_cbs_global}}, @before_compile_cbs_global;
}

sub add_ccflag_global {
  my ($self, @ccflags_global) = @_;
  
  push @{$self->{ccflags_global}}, @ccflags_global;
}

sub add_ccflag_spvm {
  my ($self, @ccflags_spvm) = @_;
  
  push @{$self->{ccflags_spvm}}, @ccflags_spvm;
}

sub add_ccflag_native {
  my ($self, @ccflags_native) = @_;
  
  push @{$self->{ccflags_native}}, @ccflags_native;
}

sub add_ccflag_native_class {
  my ($self, $class_name, @ccflags_native_class) = @_;
  
  unless (defined $self->{ccflags_native_class}{$class_name}) {
    $self->{ccflags_native_class}{$class_name} = [];
  }
  
  push @{$self->{ccflags_native_class}{$class_name}}, @ccflags_native_class;
}

sub add_ccflag_precompile {
  my ($self, @ccflags_precompile) = @_;
  
  push @{$self->{ccflags_precompile}}, @ccflags_precompile;
}

sub add_define_global {
  my ($self, @defines_global) = @_;
  
  push @{$self->{defines_global}}, @defines_global;
}

sub add_define_spvm {
  my ($self, @defines_spvm) = @_;
  
  push @{$self->{defines_spvm}}, @defines_spvm;
}

sub add_define_native {
  my ($self, @defines_native) = @_;
  
  push @{$self->{defines_native}}, @defines_native;
}

sub add_define_native_class {
  my ($self, $class_name, @defines_native_class) = @_;
  
  unless (defined $self->{defines_native_class}{$class_name}) {
    $self->{defines_native_class}{$class_name} = []
  }
  
  push @{$self->{defines_native_class}{$class_name}}, @defines_native_class;
}

sub add_define_precompile {
  my ($self, @defines_precompile) = @_;
  
  push @{$self->{defines_precompile}}, @defines_precompile;
}

sub add_include_dir_global {
  my ($self, @include_dirs_global) = @_;
  
  push @{$self->{include_dirs_global}}, @include_dirs_global;
}

sub add_include_dir_spvm {
  my ($self, @include_dirs_spvm) = @_;
  
  push @{$self->{include_dirs_spvm}}, @include_dirs_spvm;
}

sub add_include_dir_native {
  my ($self, @include_dirs_native) = @_;
  
  push @{$self->{include_dirs_native}}, @include_dirs_native;
}

sub add_include_dir_native_class {
  my ($self, $class_name, @include_dirs_native_class) = @_;
  
  unless (defined $self->{include_dirs_native_class}{$class_name}) {
    $self->{include_dirs_native_class}{$class_name} = [];
  }
  
  push @{$self->{include_dirs_native_class}{$class_name}}, @include_dirs_native_class;
}

sub add_include_dir_precompile {
  my ($self, @include_dirs_precompile) = @_;
  
  push @{$self->{include_dirs_precompile}}, @include_dirs_precompile;
}

1;

=head1 Name

SPVM::Builder::Config::Exe - Excutable File Config

=head1 Description

The SPVM::Builder::Config::Exe class has methods to manipulate the config for the excutable file generated by L<spvmcc> command.

=head1 Usage

  use SPVM::Builder::Config::Exe;
  
  my $config_exe = SPVM::Builder::Config::Exe->new_gnu99;

=head1 Super Class

=over 2

=item * L<SPVM::Builder::Config>

=back

=head1 Fields

=head2 before_compile_cbs_global

  my $before_compile_cbs_global = $config_exe->before_compile_cbs_global;
  $config_exe->before_compile_cbs_global($before_compile_cbs_global);

Gets and sets the C<before_compile_cbs_global> field, an array reference of callbacks that work globally called just before the compile command L</"cc"> is executed.

This affects all compilations.

=head2 ccflags_global

  my $ccflags_global = $config->ccflags_global;
  $config->ccflags_global($ccflags_global);

Gets and sets C<ccflags> field, an array reference containing arugments of the compiler L</"cc"> in all compilation.

=head2 ccflags_spvm

  my $ccflags_spvm = $config->ccflags_spvm;
  $config->ccflags_spvm($ccflags_spvm);

Gets and sets C<ccflags_spvm> field, an array reference containing arugments of the compiler L</"cc"> in compilations of SPVM source code and a bootstrap source file.

=head2 ccflags_native

  my $ccflags_native = $config->ccflags_native;
  $config->ccflags_native($ccflags_native);

Gets and sets C<ccflags_native> field, an array reference containing arugments of the compiler L</"cc"> in compilation of all native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c>.

=head2 ccflags_native_class

  my $ccflags_native_class = $config->ccflags_native_class($class_name);
  $config->ccflags_native_class($class_name, $ccflags_native);

Gets and sets the value of C<ccflags_native_class> field's class name key $class_name, an array reference containing arugments of the compiler L</"cc"> in compilation of native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c> in $class_name.

=head2 ccflags_precompile

  my $ccflags_precompile = $config->ccflags_precompile;
  $config->ccflags_precompile($ccflags_precompile);

Gets and sets C<ccflags_precompile> field, an array reference containing arugments of the compiler L</"cc"> in compilation for precompilation.

=head2 defines_global

  my $defines_global = $config->defines_global;
  $config->defines_global($defines_global);

Gets and sets C<defines> field, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in all compilation.

=head2 defines_spvm

  my $defines_spvm = $config->defines_spvm;
  $config->defines_spvm($defines_spvm);

Gets and sets C<defines_spvm> field, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in compilations of SPVM source code and a bootstrap source file.

=head2 defines_native

  my $defines_native = $config->defines_native;
  $config->defines_native($defines_native);

Gets and sets C<defines_native> field, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in compilation of all native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c>.

=head2 defines_native_class

  my $defines_native_class = $config->defines_native_class($class_name);
  $config->defines_native_class($class_name, $defines_native);

Gets and sets the value of C<defines_native_class> field's class name key $class_name, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in compilation of native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c> in $class_name.

=head2 defines_precompile

  my $defines_precompile = $config->defines_precompile;
  $config->defines_precompile($defines_precompile);

Gets and sets C<defines_precompile> field, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in compilation for precompilation.

=head2 optimize_global

  my $optimize_global = $config->optimize_global;
  $config->optimize_global($optimize_global);

Gets and sets C<optimize> field, an arugment of the compiler L</"cc"> for optimization in all compilation.

=head2 optimize_spvm

  my $optimize_spvm = $config->optimize_spvm;
  $config->optimize_spvm($optimize_spvm);

Gets and sets C<optimize_spvm> field, an arugment of the compiler L</"cc"> for optimization in compilations of SPVM source code and a bootstrap source file.

=head2 optimize_native

  my $optimize_native = $config->optimize_native;
  $config->optimize_native($optimize_native);

Gets and sets C<optimize_native> field, an arugment of of the compiler L</"cc"> for optimization in compilation of all native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c>.

=head2 optimize_native_class

  my $optimize_native_class = $config->optimize_native_class($class_name);
  $config->optimize_native_class($class_name, $optimize_native);

Gets and sets the value of C<optimize_native_class> field's class name key $class_name, an arugments of the compiler L</"cc"> for optimization in compilation of native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c> in $class_name.

=head2 optimize_precompile

  my $optimize_precompile = $config->optimize_precompile;
  $config->optimize_precompile($optimize_precompile);

Gets and sets C<optimize_precompile> field, an arugment of of the compiler L</"cc"> for optimization in compilation for precompilation.

=head2 include_dirs_global

  my $include_dirs_global = $config->include_dirs_global;
  $config->include_dirs_global($include_dirs_global);

Gets and sets C<include_dirs> field, an array reference containing C<-I> arugments of the compiler L</"cc"> in all compilation.

=head2 include_dirs_spvm

  my $include_dirs_spvm = $config->include_dirs_spvm;
  $config->include_dirs_spvm($include_dirs_spvm);

Gets and sets C<include_dirs_spvm> field, an array reference containing C<-I> arugments of the compiler L</"cc"> in compilations of SPVM source code and a bootstrap source file.

=head2 include_dirs_native

  my $include_dirs_native = $config->include_dirs_native;
  $config->include_dirs_native($include_dirs_native);

Gets and sets C<include_dirs_native> field, an array reference containing C<-I> arugments of the compiler L</"cc"> in compilation of all native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c>.

=head2 include_dirs_native_class

  my $include_dirs_native_class = $config->include_dirs_native_class($class_name);
  $config->include_dirs_native_class($class_name, $include_dirs_native);

Gets and sets the value of C<include_dirs_native_class> field's class name key $class_name, an array reference containing C<-I> arugments of the compiler L</"cc"> in compilation of native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c> in $class_name.

=head2 include_dirs_precompile

  my $include_dirs_precompile = $config->include_dirs_precompile;
  $config->include_dirs_precompile($include_dirs_precompile);

Gets and sets C<include_dirs_precompile> field, an array reference containing C<-I> arugments of the compiler L</"cc"> in compilation for precompilation.

=head1 Methods

=head2 new

  my $config_exe = SPVM::Builder::Config::Exe->new(%fields);

Create a new L<SPVM::Builder::Config::Exe> object with L</"Fields"> and fields of its super classes.

This method calls the C<new> method of its L<super class|/"Inheritance"> given %fields with field default values applied.

Field Default Values:

=over 2

=item * L<output_type|SPVM::Builder::Config/"output_type">

  "exe"

=item * L</"before_compile_cbs_global">

  []

=item * Other Fields

  undef

=back

=head2 add_before_compile_cb_global

  $config_exe->add_before_compile_cb_global(@before_compile_cbs_global);

Adds @before_compile_cbs_global to the end of L</"before_compile_cbs_global"> field.

Examples:

  $config_exe->add_before_compile_cb_global(sub {
    my ($config, $compile_info) = @_;
    
    my $cc_command = $compile_info->to_command;
    
    # Do something
  });

=head2 add_ccflag_global

  $config->add_ccflag_global(@ccflags_global);

Adds @ccflags_global to the end of L</"ccflags_global"> field.

=head2 add_ccflag_spvm

  $config->add_ccflag_spvm(@ccflags_spvm);

Adds @ccflags_spvm to the end of L</"ccflags_spvm"> field.

=head2 add_ccflag_native

  $config->add_ccflag_native(@ccflags_native);

Adds @ccflags_native to the end of L</"ccflags_native"> field.

=head2 add_ccflag_native_class

  $config->add_ccflag_native_class($class_name, @ccflags_native_class);

Adds @ccflags_native_class to the end of L</"ccflags_native_class"> field's key $class_name.

=head2 add_ccflag_precompile

  $config->add_ccflag_precompile(@ccflags_precompile);

Adds @ccflags_precompile to the end of L</"ccflags_precompile"> field.

=head2 add_define_global

  $config->add_define_global(@defines_global);

Adds @defines_global to the end of L</"defines_global"> field.

=head2 add_define_spvm

  $config->add_define_spvm(@defines_spvm);

Adds @defines_spvm to the end of L</"defines_spvm"> field.

=head2 add_define_native

  $config->add_define_native(@defines_native);

Adds @defines_native to the end of L</"defines_native"> field.

=head2 add_define_native_class

  $config->add_define_native_class($class_name, @defines_native_class);

Adds @defines_native_class to the end of L</"defines_native_class"> field's key $class_name.

=head2 add_define_precompile

  $config->add_define_precompile(@defines_precompile);

Adds @defines_precompile to the end of L</"defines_precompile"> field.

=head2 add_include_dir_global

  $config->add_include_dir_global(@include_dirs_global);

Adds @include_dirs_global to the end of L</"include_dirs_global"> field.

=head2 add_include_dir_spvm

  $config->add_include_dir_spvm(@include_dirs_spvm);

Adds @include_dirs_spvm to the end of L</"include_dirs_spvm"> field.

=head2 add_include_dir_native

  $config->add_include_dir_native(@include_dirs_native);

Adds @include_dirs_native to the end of L</"include_dirs_native"> field.

=head2 add_include_dir_native_class

  $config->add_include_dir_native_class($class_name, @include_dirs_native_class);

Adds @include_dirs_native_class to the end of L</"include_dirs_native_class"> field's key $class_name.

=head2 add_include_dir_precompile

  $config->add_include_dir_precompile(@include_dirs_precompile);

Adds @include_dirs_precompile to the end of L</"include_dirs_precompile"> field.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
