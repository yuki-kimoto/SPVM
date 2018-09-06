package SPVM::Builder::Info;

use strict;
use warnings;

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  return $self;
}

sub get_native_sub_names {
  my ($self, $package_name) = @_;
  
  my $subs = $self->get_subs($package_name);
  my $native_subs = [grep { $_->{have_native_desc} } @$subs];
  my $native_sub_names = [map { $_->{name} } @$native_subs];
  
  return $native_sub_names;
}

sub get_precompile_sub_names {
  my ($self, $package_name) = @_;
  
  my $subs = $self->get_subs($package_name);
  my $precompile_subs = [grep { $_->{have_precompile_desc} } @$subs];
  my $precompile_sub_names = [map { $_->{name} } @$precompile_subs];
  
  return $precompile_sub_names;
}

1;
