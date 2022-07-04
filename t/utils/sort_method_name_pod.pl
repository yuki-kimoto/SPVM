# Sort the subs by name asc order

my $is_sub;

my $sub_defs_h = {};

my $cur_name = '';
my $cur_sub = '';
while (my $line = <>) {
  if ($line =~ /^=cut/) {
    $is_sub = 0;
  }
  if ($is_sub) {
    if ($line =~ /^=head2\s+(\w+)\b/) {
      $cur_name = $1;
      $sub_defs_h->{$cur_name} = $line;
    }
    else {
      $sub_defs_h->{$cur_name} .= $line;
    }
  }
  else {
    if ($line =~ /^=head2\s+(\w+)\b/) {
      $is_sub = 1;
      $cur_name = $1;
      $sub_defs_h->{$cur_name} = $line;
    }
  }
}

for my $sub_name (sort { lc $a cmp lc $b } keys %$sub_defs_h) {
  my $sub_def = $sub_defs_h->{$sub_name};
  print $sub_def;
}
