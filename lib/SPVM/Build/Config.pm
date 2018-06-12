package SPVM::Build::Config;

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{config} = {};
  
  bless $self, $class;
  
  return $self;
}

sub replace_extra_compiler_flags { shift->{extra_compiler_flags} = shift }
sub add_extra_compiler_flags { shift->{extra_compiler_flags} .= shift }

sub replace_extra_linker_flags { shift->{extra_linker_flags} = shift }
sub add_extra_linker_flags { shift->{extra_linker_flags} .= shift }

sub quiet_on { shift->{quiet} = 1 };
sub quiet_off { shift->{quiet} = 0 };
sub quiet_auto { delete shift->{quiet} };

sub optimize { shift->{optimize} = shift }

sub config {
  my $self = shift;
  
  if (@_) {
    $self->{config} = $_[0];
  }
  
  return $self->{config};
}

1;
