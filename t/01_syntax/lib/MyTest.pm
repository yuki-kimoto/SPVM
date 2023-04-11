use strict;
use warnings;
use Exporter;
use File::Temp();
use Test::More;
use Carp 'confess';
use File::Path 'mkpath';
use File::Basename 'dirname';

our @EXPORT_OK = qw(compile_not_ok_file compile_not_ok);

sub compile_not_ok {
  my ($sources, $error_message_re) = @_;
  
  if (defined $error_message_re) {
    unless (ref $error_message_re) {
      my $quotemeta = quotemeta $error_message_re;
      $error_message_re = qr/$quotemeta/;
    }
  }
  
  unless (ref $sources eq 'ARRAY') {
    $sources = [$sources];
  }
  
  my (undef, $file, $line) = caller;
  
  my $builder = SPVM::Builder->new;
  
  my $tmp_class_path = File::Temp->newdir;
    
  my $first_class_name;
  for my $source (@$sources) {
    my $class_name;
    if ($source =~ /\bclass\s+([\w+:]+)\s*/) {
      $class_name = $1;
    }
    unless (defined $class_name) {
      die "Can't find class name in the source";
    }
    
    unless (defined $first_class_name) {
      $first_class_name = $class_name;
    }
    
    my $class_file = "$tmp_class_path/$class_name.spvm";
    $class_file =~ s|::|/|g;
    
    mkpath dirname $class_file;
    open my $class_fh, '>', $class_file
      or confess "Can't open file \"$class_file\":$!";
    
    print $class_fh $source;
    close $class_fh;
  }
  
  compile_not_ok_file($first_class_name, $error_message_re, {class_path => "$tmp_class_path", file => $file, line => $line});
}

sub compile_not_ok_file {
  my ($class_name, $error_message_re, $options) = @_;
  
  unless ($options) {
    $options = {};
  }
  
  my $class_path = $options->{class_path};
  
  my (undef, $caller_file, $caller_line) = caller;
  
  my $file;
  if (defined $options->{file}) {
    $file = $options->{file};
  }
  else {
    $file = $caller_file;
  }

  my $line;
  if (defined $options->{line}) {
    $line = $options->{line};
  }
  else {
    $line = $caller_line;
  }
  
  my $builder = SPVM::Builder->new;
  if (defined $class_path) {
    unshift @{$builder->class_paths}, $class_path;
  }

  my $compiler = SPVM::Builder::Compiler->new(
    class_paths => $builder->class_paths
  );
  
  my $success = $compiler->compile($class_name, $file, $line);
  ok(!$success);
  my $error_messages = $compiler->get_error_messages;
  my $first_error_message = $error_messages->[0];
  my $message_ok;
  if ($error_message_re) {
    $message_ok = like($first_error_message, $error_message_re);
  }
  
  if ($success || ($error_message_re && !$message_ok)) {
    warn "  at $file line $line\n";
  }
}

sub compile_ok {
  my ($sources) = @_;
  
  unless (ref $sources eq 'ARRAY') {
    $sources = [$sources];
  }
  
  my (undef, $file, $line) = caller;
  
  my $builder = SPVM::Builder->new;
  
  my $tmp_class_path = File::Temp->newdir;
    
  my $first_class_name;
  for my $source (@$sources) {
    my $class_name;
    if ($source =~ /\bclass\s+([\w+:]+)\s*/) {
      $class_name = $1;
    }
    unless (defined $class_name) {
      die "Can't find class name in the source";
    }
    
    unless (defined $first_class_name) {
      $first_class_name = $class_name;
    }
    
    my $class_file = "$tmp_class_path/$class_name.spvm";
    $class_file =~ s|::|/|g;
    
    mkpath dirname $class_file;
    open my $class_fh, '>', $class_file
      or confess "Can't open file \"$class_file\":$!";
    
    print $class_fh $source;
    close $class_fh;
  }
  
  compile_ok_file($first_class_name, {class_path => "$tmp_class_path", file => $file, line => $line});
}

sub compile_ok_file {
  my ($class_name, $options) = @_;
  
  unless ($options) {
    $options = {};
  }
  
  my $class_path = $options->{class_path};
  
  my (undef, $caller_file, $caller_line) = caller;
  
  my $file;
  if (defined $options->{file}) {
    $file = $options->{file};
  }
  else {
    $file = $caller_file;
  }

  my $line;
  if (defined $options->{line}) {
    $line = $options->{line};
  }
  else {
    $line = $caller_line;
  }
  
  my $builder = SPVM::Builder->new;
  if (defined $class_path) {
    unshift @{$builder->class_paths}, $class_path;
  }
  
  my $compiler = SPVM::Builder::Compiler->new(
    class_paths => $builder->class_paths
  );
  my $success = $compiler->compile($class_name, $file, $line);
  ok($success);
  
  if (!$success) {
    warn "  at $file line $line\n";
    
    my $error_messages = $compiler->get_error_messages;
    my $first_error_message = $error_messages->[0];
    warn "[Compile Error]$first_error_message";
  }
}
