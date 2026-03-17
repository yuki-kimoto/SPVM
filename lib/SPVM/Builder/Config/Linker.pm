package SPVM::Builder::Config::Linker;

use parent 'SPVM::Builder::Config::Base';

use strict;
use warnings;
use Config;
use SPVM::Builder::Accessor 'has';
use SPVM::Builder::LibInfo;
use SPVM::Builder::Resource;

my $fields = [qw(
  ld
  ldflags
  ld_optimize
  output_type
  resource_loader_config
  warn_ldflags
  debug_ldflags
  dynamic_lib_ldflags
  thread_ldflags
  bcrypt_ldflags
  libcpp_ldflags
  dynamic_lib_libcpp_ldflags
  exe_libcpp_ldflags
  static_lib_ldflag
  lib_dirs
  libs
  lib_prefix
  lib_option_name
  lib_option_suffix
  lib_dir_option_name
  dynamic_lib_ext
  static_lib_ext
  exe_ext
  ld_output_option_name
  output_dir
  output_file
  before_link_cbs
  after_link_cbs
)];

has($fields);

sub option_names {
  my ($self) = @_;
  return [@{$self->SUPER::option_names}, @$fields];
}

sub new {
  my $class = shift;
  my $self = $class->SUPER::new(@_);

  unless (defined $self->{ld}) {
    my $config_gcc_version = $Config{gccversion};
    if ($config_gcc_version =~ /\bclang\b/i) {
      $self->ld('clang++');
    }
    else {
      $self->ld('g++');
    }
  }

  unless (defined $self->{ldflags}) {
    $self->ldflags([]);
  }

  unless (defined $self->{dynamic_lib_ldflags}) {
    if ($^O eq 'MSWin32') {
      $self->dynamic_lib_ldflags(['-mdll', '-s']);
    }
    else {
      $self->dynamic_lib_ldflags(['-shared']);
    }
  }

  unless (defined $self->{thread_ldflags}) {
    $self->thread_ldflags(['-pthread']);
    if ($^O eq 'MSWin32') {
      push @{$self->thread_ldflags}, '-Wl,-Bstatic', '-lwinpthread', '-Wl,-Bdynamic';
    }
  }

  unless (defined $self->{bcrypt_ldflags}) {
    if ($^O eq 'MSWin32') {
      $self->bcrypt_ldflags(['-lbcrypt']);
    }
    else {
      $self->bcrypt_ldflags([]);
    }
  }

  unless (defined $self->{libcpp_ldflags}) {
    if ($^O eq 'MSWin32') {
      $self->libcpp_ldflags(['-Wl,-Bstatic', '-lstdc++', '-lgcc', '-Wl,-Bdynamic']);
    }
    elsif ($^O eq 'darwin') {
      $self->libcpp_ldflags([]);
    }
    else {
      $self->libcpp_ldflags(['-lstdc++']);
    }
  }

  unless (defined $self->{dynamic_lib_libcpp_ldflags}) {
    $self->dynamic_lib_libcpp_ldflags([]);
  }

  unless (defined $self->{exe_libcpp_ldflags}) {
    if ($^O eq 'darwin') {
      $self->exe_libcpp_ldflags(['-lc++']);
    }
    else {
      $self->exe_libcpp_ldflags([]);
    }
  }

  unless (defined $self->{static_lib_ldflag}) {
    my $begin = '-Wl,-Bstatic';
    my $end = '-Wl,-Bdynamic';
    $self->static_lib_ldflag([$begin, $end]);
  }

  unless (defined $self->{ld_optimize}) {
    $self->ld_optimize('-O2');
  }

  unless (defined $self->{lib_dirs}) {
    $self->lib_dirs([]);
  }

  unless (defined $self->{libs}) {
    $self->libs([]);
  }

  unless (defined $self->{before_link_cbs}) {
    $self->before_link_cbs([]);
  }

  unless (defined $self->{after_link_cbs}) {
    $self->after_link_cbs([]);
  }

  unless (defined $self->output_type) {
    $self->output_type('dynamic_lib');
  }

  unless (defined $self->{warn_ldflags}) {
    $self->warn_ldflags([]);
  }

  unless (defined $self->{debug_ldflags}) {
    $self->debug_ldflags([]);
  }

  unless (defined $self->{lib_dir_option_name}) {
    $self->lib_dir_option_name("-L");
  }

  unless (defined $self->{dynamic_lib_ext}) {
    my $ext = $Config{dlext};
    $ext =~ s/^\.//;
    $self->dynamic_lib_ext($ext);
  }
  
  unless (defined $self->{static_lib_ext}) {
    my $ext = $Config{_a};
    $ext =~ s/^\.//;
    $self->static_lib_ext($ext);
  }
  
  unless (defined $self->{exe_ext}) {
    my $ext = $Config{_exe};
    if (length $ext) {
      $ext =~ s/^\.//;
      $self->exe_ext($ext);
    }
    else {
      $self->exe_ext(undef);
    }
  }

  unless (defined $self->{lib_prefix}) {
    $self->lib_prefix("lib");
  }

  unless (defined $self->{lib_option_suffix}) {
    $self->lib_option_suffix("");
  }

  unless (defined $self->{lib_option_name}) {
    $self->lib_option_name("-l");
  }

  unless (defined $self->{ld_output_option_name}) {
    $self->ld_output_option_name("-o");
  }
  
  # resources
  unless (defined $self->{resources}) {
    $self->{resources} = {};
  }
  
  return $self;
}

sub add_ldflag {
  my ($self, @ldflags) = @_;
  push @{$self->{ldflags}}, @ldflags;
}

sub add_lib_dir {
  my ($self, @lib_dirs) = @_;
  push @{$self->{lib_dirs}}, @lib_dirs;
}

sub add_lib {
  my ($self, @libs) = @_;
  push @{$self->{libs}}, @libs;
}

sub add_lib_abs {
  my ($self, @libs) = @_;
  $self->_add_lib_info({is_abs => 1}, @libs);
}

sub add_static_lib_abs {
  my ($self, @libs) = @_;
  $self->_add_lib_info({is_static => 1, is_abs => 1}, @libs);
}

sub add_static_lib {
  my ($self, @libs) = @_;
  $self->_add_lib_info({is_static => 1}, @libs);
}

sub _add_lib_info {
  my ($self, $options, @libs) = @_;
  my @lib_infos;
  for my $lib (@libs) {
    my $lib_info;
    if (ref $lib eq 'SPVM::Builder::LibInfo') {
      $lib_info = $lib;
    }
    else {
      my $lib_name = $lib;
      $lib_info = SPVM::Builder::LibInfo->new(config => $self, name => $lib_name);
    }
    $lib_info->is_static($options->{is_static});
    $lib_info->is_abs($options->{is_abs});
    push @lib_infos, $lib_info;
  }
  $self->add_lib(@lib_infos);
}

sub add_before_link_cb {
  my ($self, @before_link_cbs) = @_;
  push @{$self->{before_link_cbs}}, @before_link_cbs;
}

sub add_after_link_cb {
  my ($self, @after_link_cbs) = @_;
  push @{$self->{after_link_cbs}}, @after_link_cbs;
}

sub use_resource {
  my ($self, @args) = @_;
  
  my $first_arg;
  unless (@args % 2 == 0) {
    $first_arg = shift @args;
  }
  
  my $resource;
  if (ref $first_arg) {
    $resource = $first_arg;
  }
  else {
    my $class_name = $first_arg;
    my %args = @args;
    if (exists $args{class_name}) {
      $class_name = delete $args{class_name};
    }
    $resource = SPVM::Builder::Resource->new(class_name => $class_name, %args);
  }
  
  my $resource_class_name = $resource->class_name;
  
  my $ext = 'config';
  my $config_file_base = SPVM::Builder::Util::convert_class_name_to_rel_file($resource_class_name, $ext);
  
  my $config_file = SPVM::Builder::Util::search_config_file($resource_class_name);
  
  unless (defined $config_file) {
    my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($resource_class_name, 'config');
    
    confess("A config file \"$config_rel_file\" is not found in (@INC)");
  }
  
  my $config = $self->load_config($config_file);
  $config->file($config_file);
  
  $resource->config($config);
  
  my $index = keys %{$self->{resources}};
  
  $self->{resources}->{$resource_class_name} = {resource => $resource, index => $index};
  
  return $resource;
}

sub get_resource {
  my ($self, $resource_class_name) = @_;
  
  unless (defined $self->{resources}{$resource_class_name}) {
    return;
  }
  
  my $resource = $self->{resources}{$resource_class_name}{resource};
  
  return $resource;
}

sub get_resource_names {
  my ($self) = @_;
  
  my @resource_names = sort { $self->{resources}{$a}{index} <=> $self->{resources}{$b}{index} } keys %{$self->{resources}};
  
  return \@resource_names;
}

sub clear_system_settings {
  my $self = shift;
  
  $self->dynamic_lib_ldflags([]);
  $self->thread_ldflags([]);
  $self->libcpp_ldflags([]);
  $self->dynamic_lib_libcpp_ldflags([]);
  $self->exe_libcpp_ldflags([]);
  $self->warn_ldflags([]);
  $self->debug_ldflags([]);
}

1;

=head1 Name

SPVM::Builder::Config::Linker - Config for Linking Native Classes

=head1 Inheritance

L<SPVM::Builder::Config::Base>

=head1 Fields

=head2 ld

  my $ld = $config->ld;
  $config->ld($ld);

Gets and sets C<ld> field, a linker name.

Examples:

  $config->ld('g++');

=head2 lib_dirs

  my $lib_dirs = $config->lib_dirs;
  $config->lib_dirs($lib_dirs);

Gets and sets C<lib_dirs> field, an array reference containing library search directories.

The values of this field are converted to C<-L> options when the arguments of the linker L</"ld"> are created.

  # -L /path1 -L /path2
  $config->lib_dirs(['/path1', '/path2']);

=head2 libs

  my $libs = $config->libs;
  $config->libs($libs);

Gets and sets C<libs> field, an array reference containing library names such as C<z>, and C<png> or L<SPVM::Builder::LibInfo> objects.

The values of this field are converted to C<-l> options when the arguments of the linker L</"ld"> are created.

See L</"Library Path Resolution"> about resolving library paths.

Examples:

  # -l libz -l libpng
  $config->libs(['z', 'png']);

=head2 ldflags

  my ldflags = $config->ldflags;
  $config->ldflags(ldflags);

Gets and sets C<ldflags> field, an array reference containing arguments of the linker L</"ld">.

=head2 dynamic_lib_ldflags

  my dynamic_lib_ldflags = $config->dynamic_lib_ldflags;
  $config->dynamic_lib_ldflags(dynamic_lib_ldflags);

Gets and sets C<dynamic_lib_ldflags> field, an array reference containing arguments of the linker L</"ld"> for dynamic libraries.

This field is automatically set and users nomally do not change it.

=head2 thread_ldflags

  my thread_ldflags = $config->thread_ldflags;
  $config->thread_ldflags(thread_ldflags);

Gets and sets C<thread_ldflags> field, an array reference containing arguments of the linker L</"ld"> for threads.

This field is automatically set and users nomally do not change it.

=head2 bcrypt_ldflags

  my $bcrypt_ldflags = $config->bcrypt_ldflags;
  $config->bcrypt_ldflags($bcrypt_ldflags);

Gets and sets C<bcrypt_ldflags> field, an array reference containing arguments of the linker L</"ld"> for bcrypt.

This field is automatically set and users normally do not change it.

=head2 libcpp_ldflags

  my $libcpp_ldflags = $config->libcpp_ldflags;
  $config->libcpp_ldflags($libcpp_ldflags);

Gets and sets C<libcpp_ldflags> field, an array reference containing arguments of the linker L</"ld"> for the C++ standard library.

This field is automatically set depending on the OS, and users normally do not change it.

=head2 dynamic_lib_libcpp_ldflags

  my $dynamic_lib_libcpp_ldflags = $config->dynamic_lib_libcpp_ldflags;
  $config->dynamic_lib_libcpp_ldflags($dynamic_lib_libcpp_ldflags);

Gets and sets C<dynamic_lib_libcpp_ldflags> field, an array reference containing arguments of the linker L</"ld"> for the C++ standard library used for dynamic libraries.

This field is automatically set depending on the OS, and users normally do not change it.

=head2 exe_libcpp_ldflags

  my $exe_libcpp_ldflags = $config->exe_libcpp_ldflags;
  $config->exe_libcpp_ldflags($exe_libcpp_ldflags);

Gets and sets C<exe_libcpp_ldflags> field, an array reference containing arguments of the linker L</"ld"> for the C++ standard library used for executable files.

This field is automatically set depending on the OS, and users normally do not change it.

=head2 static_lib_ldflag

  my static_lib_ldflag = $config->static_lib_ldflag;
  $config->static_lib_ldflag(static_lib_ldflag);

Gets and sets C<static_lib_ldflag> field, an array reference containing a pair of arguments to start statically linking and end it.

The library name added by the L</"add_static_lib"> are surrounded by the values of the pair.

  # -Wl,-Bstatic -llibfoo -Wl,-Bdynamic
  $config->static_lib_ldflag(['-Wl,-Bstatic', '-Wl,-Bdynamic']);
  $config->add_static_lib('foo');

This field is automatically set and users nomally do not change it.

This field only works correctly in Linux/Unix.

Mac does not support these options. If you want to search a static library, create a new library search directory, copy a static library to there, and add the new library search directory.
  
  # /path_for_static_lib/libz.a
  $config->add_lib_dir('/path_for_static_lib');
  $config->add_lib('z');

MinGW on Windows supports these options, but instead of linking statically, it links dynamically with absolute paths. This is usually not the intended behavior. If you want to do static linking on Windows, you need to use C<-static> option.

=head2 ld_optimize

  my $ld_optimize = $config->ld_optimize;
  $config->ld_optimize($ld_optimize);

Gets and sets C<ld_optimize> field, an argument of the linker L</"ld"> for optimization.

Examples:

  $config->ld_optimize("-O3");

=head2 before_link_cbs

  my $before_link_cbs = $config->before_link_cbs;
  $config->before_link_cbs($before_link_cbs);

Gets and sets C<before_link_cbs> field, an array reference containing callbacks called just before the link command L</"ld"> is executed.

These callbacks are executed even if the link command is not actually executed because of caching.

The 1th argument of the callback is an L<SPVM::Builder::Config> object.

The 2th argument of the callback is an L<SPVM::Builder::LinkInfo> object.

=head2 after_link_cbs

  my $after_link_cbs = $config->after_link_cbs;
  $config->after_link_cbs($after_link_cbs);

Gets and sets C<after_link_cbs> field, an array reference containing callbacks called just after the link command L</"ld"> is executed.

These callbacks are executed even if the link command is not actually executed because of caching.

The 1st argument of the callback is an L<SPVM::Builder::Config> object.

The 2nd argument of the callback is an L<SPVM::Builder::LinkInfo> object.

=head2 output_type

  my $output_type = $config->output_type;
  $config->output_type($output_type);

Gets and sets C<output_type> field, a type of the output file L</"output_file"> generated by the linker L</"ld">.

If thie field is C<exe>, the output file is an executable file.

If thie field is C<dynamic_lib>, the output file is a dynamic link library.

=head2 warn_ldflags

  my $warn_ldflags = $config->warn_ldflags;
  $config->warn_ldflags($warn_ldflags);

Gets and sets C<warn_ldflags> field, an array reference containing arguments of the linker L</"ld"> for warning settings.

=head2 debug_ldflags

  my $debug_ldflags = $config->debug_ldflags;
  $config->debug_ldflags($debug_ldflags);

Gets and sets C<debug_ldflags> field, an array reference containing arguments of the linker L</"ld"> for debug information.

=head2 lib_dir_option_name

  my $lib_dir_option_name = $config->lib_dir_option_name;
  $config->lib_dir_option_name($lib_dir_option_name);

Gets and sets C<lib_dir_option_name> field, a string that is an option name to specify a library search path.

=head2 dynamic_lib_ext

  my $dynamic_lib_ext = $config->dynamic_lib_ext;
  $config->dynamic_lib_ext($dynamic_lib_ext);

Gets and sets C<dynamic_lib_ext> field, the extension of a dynamic library such as C<so> or C<dll>.

The dot C<.> is not included.

=head2 static_lib_ext

  my $static_lib_ext = $config->static_lib_ext;
  $config->static_lib_ext($static_lib_ext);

Gets and sets C<static_lib_ext> field, the extension of a static library such as C<a> or C<lib>.

The dot C<.> is not included.

=head2 exe_ext

  my $exe_ext = $config->exe_ext;
  $config->exe_ext($exe_ext);

Gets and sets C<exe_ext> field, the extension of an executable file such as C<exe>.

The dot C<.> is not included.

=head2 lib_prefix

  my $lib_prefix = $config->lib_prefix;
  $config->lib_prefix($lib_prefix);

Gets and sets C<lib_prefix> field, the prefix of a library name such as C<lib>.

=head2 lib_option_suffix

  my $lib_option_suffix = $config->lib_option_suffix;
  $config->lib_option_suffix($lib_option_suffix);

Gets and sets C<lib_option_suffix> field, the suffix of a library name such as C<.lib>.

=head2 lib_option_name

  my $lib_option_name = $config->lib_option_name;
  $config->lib_option_name($lib_option_name);

Gets and sets C<lib_option_name> field, a string that is an option name to specify a library name.

=head2 ld_output_option_name

  my $ld_output_option_name = $config->ld_output_option_name;
  $config->ld_output_option_name($ld_output_option_name);

Gets and sets C<ld_output_option_name> field, a string that is an option name to specify a linker output file name.

=head2 output_dir

  my $output_dir = $config->output_dir;
  $config->output_dir($output_dir);

Gets and sets C<output_dir> field, an output directory for the linker L</"ld">.

This field is automatically set and users nomally do not change it.

=head2 output_file

  my $output_file = $config->output_file;
  $config->output_file($output_file);

Gets and sets C<output_file> field. A path of a dinamic link library or an executable file generated by the linker L</"ld">.

This field is automatically set and users nomally do not change it.

=head1 Class Methods

=head2 new

  my $config = SPVM::Builder::Config::Linker->new(%fields);

Creates a new C<SPVM::Builder::Config::Linker> object. This method calls the C<new> method of the super class L<SPVM::Builder::Config::Base>.

Field Default Values:

=over 2

=item * L</"ld">

If C<$Config{gccversion}> contains C<clang>, L</"ld"> field are set to C<clang++>. Otherwise, it is set to C<g++>.

=item * L</"ldflags">

  []

=item * L</"ld_optimize">

  "-O2"

=item * L</"output_type">

  "dynamic_lib"

=item * L</"warn_ldflags">

  []

=item * L</"debug_ldflags">

  []

=item * L</"dynamic_lib_ldflags">

Windows:

  ["-mdll", "-s"]

Other OSs:

  ["-shared"]

=item * L</"thread_ldflags">

Windows:

  ["-pthread", "-Wl,-Bstatic", "-lwinpthread", "-Wl,-Bdynamic"]

Other OSs:

  ["-pthread"]

=item * L</"bcrypt_ldflags">

Windows:

  ["-lbcrypt"]

Other OSs:

  []

=item * L</"libcpp_ldflags">

Windows:

  ["-Wl,-Bstatic", "-lstdc++", "-lgcc", "-Wl,-Bdynamic"]

Other OSs:

  ["-lstdc++"]

=item * L</"dynamic_lib_libcpp_ldflags">

  []

=item * L</"exe_libcpp_ldflags">

  []

=item * L</"static_lib_ldflag">

  ["-Wl,-Bstatic", "-Wl,-Bdynamic"]

=item * L</"lib_dirs">

  []

=item * L</"libs">

  []

=item * L</"lib_prefix">

  "lib"

=item * L</"lib_option_name">

  "-l"

=item * L</"lib_option_suffix">

  ""

=item * L</"lib_dir_option_name">

  "-L"

=item * L</"dynamic_lib_ext">

  $Config{dlext} without the leading dot.

=item * L</"exe_ext">

  $Config{_exe} without the leading dot. If $Config{_exe} is an empty string, it is set to undef.

=item * L</"ld_output_option_name">

"-o"

=item * L</"before_link_cbs">

  []

=item * L</"after_link_cbs">

  []

=back

=cut

=head1 Instance Methods

=head2 add_ldflag

  $config->add_ldflag(@ldflags);

Adds @ldflags to the end of L</"ldflags"> field.

=head2 add_lib_dir

  $config->add_lib_dir(@lib_dirs);

Adds @lib_dirs to the end of L</"lib_dirs"> field.

=head2 add_lib

  $config->add_lib(@libs);

Adds @libs to the end of L</"libs"> field.

Examples:

  $config->add_lib('gsl');
  $config->add_lib('gsl', 'z');
  $config->add_lib(
    SPVM::Builder::LibInfo->new(config => $config, name => 'gsl'),
    SPVM::Builder::LibInfo->new(config => $config, name => 'z', is_abs => 1),
  );

=head2 add_lib_abs

  $config->add_lib_abs(@libs);

Adds @libs to the end of L</"libs"> field with L<SPVM::Builder::LibInfo#is_abs|SPVM::Builder::LibInfo/"is_abs"> field set to a true value.

If a value in @libs is not an L<SPVM::Builder::LibInfo> object, an L<SPVM::Builder::LibInfo> object is created from the library name.

If the library is located in your user directory, it is good to use L</"add_lib_abs"> method instead of L</"add_lib"> method.

This is because if the generated dynamic link library has a relative path, that path cannot be resolved when it is loaded.

For system libraries, there is no problem because the linker knows the search directory for the library.

=head2 add_static_lib

  $config->add_static_lib(@libs);

Adds @libs to the end of L</"libs"> field with L<SPVM::Builder::LibInfo#is_static|SPVM::Builder::LibInfo/"is_static"> field set to a true value.

If a value in @libs is not an L<SPVM::Builder::LibInfo> object, an L<SPVM::Builder::LibInfo> object is created from the library name.

Examples:

  $config->add_static_lib('gsl');
  $config->add_static_lib('gsl', 'z');

=head2 add_static_lib_abs

  $config->add_static_lib_abs(@libs);

Adds @libs to the end of L</"libs"> field with L<SPVM::Builder::LibInfo#is_static|SPVM::Builder::LibInfo/"is_static"> field and L<SPVM::Builder::LibInfo#is_abs|SPVM::Builder::LibInfo/"is_abs"> field set to a true value.

If a value in @libs is not an L<SPVM::Builder::LibInfo> object, an L<SPVM::Builder::LibInfo> object is created from the library name.

=head2 add_before_link_cb

  $config->add_before_link_cb(@before_link_cbs);

Adds @before_link_cbs to the end of L</"before_link_cbs"> field.

Examples:

  $config->add_before_link_cb(sub {
    my ($config, $link_info) = @_;
    
    my $object_files = $link_info->object_files;
    
    # Do something
    
  });

=head2 add_after_link_cb

  $config->add_after_link_cb(@after_link_cbs);

Adds @after_link_cbs to the end of L</"after_link_cbs"> field.

Examples:

  $config->add_after_link_cb(sub {
    my ($config, $link_info) = @_;
    
    my $object_files = $link_info->object_files;
    
    # Do something
    
  });

=head2 resource_loader_config

  my $resource_loader_config = $config->resource_loader_config;
  $config->resource_loader_config($resource_loader_config);

Gets and sets C<resource_loader_config> field, the config file of the class that loaded a resource by L</"use_resource"> method.

This field is automatically set and users nomally do not change it.

=head2 use_resource

  my $resource = $config->use_resource($resource_name);
  my $resource = $config->use_resource($resource_name, %options);

Loads a L<resource|SPVM::Document::Resource> given a resource class name, and returns it. The return value is an L<SPVM::Builder::Resource> object.

Examples:

  $config->use_resource('Resource::MyResource');

=head2 get_resource

  my $resource = $config->get_resource($resource_name);

Gets a resource loaded by L</"use_resource"> method given a resource name, and returns it. The return value is an L<SPVM::Builder::Resource> object.

=head2 get_resource_names

  my $resource_names = $config->get_resource_names;

Returns resource names loaded by L</"use_resource"> method.

=head2 clear_system_settings

  $config->clear_system_settings;

Clears the fields that are set by default for a specific environment.

These fields might be updated in the future to support appropriate settings for different environments.

The following fields are set to C<[]>.

The following fields are set to C<[]>.

=over 2

=item * L</"thread_ldflags">

=item * L</"dynamic_lib_ldflags">

=item * L</"warn_ldflags">

=item * L</"debug_ldflags">

=item * L</"libcpp_ldflags">

=item * L</"dynamic_lib_libcpp_ldflags">

=item * L</"exe_libcpp_ldflags">

=back

=head1 Library Path Resolution

The following is the rule of library path resolution.

Library names are converted to L<SPVM::Builder::LibInfo> objects.

If L<SPVM::Builder::LibInfo#is_abs|SPVM::Builder::LibInfo/"is_abs"> field is a false value, the linker L</"ld"> resolves libaray paths.

If L<SPVM::Builder::LibInfo#is_abs|SPVM::Builder::LibInfo/"is_abs"> field is a true value, libaray paths are resolved by the following rules.

A library is searched in the library search directories contained in L</"lib_dir"> field from the beginning.

If L<SPVM::Builder::LibInfo#is_static|SPVM::Builder::LibInfo/"is_static"> field is a false value, the search is performed in the order of a dynamic library, a static library.

If L<SPVM::Builder::LibInfo#is_static|SPVM::Builder::LibInfo/"is_static"> field is a true value, the search is performed only in static libraries.

If a library is found, C<-l> option of the linker L</"ld"> is created using the found absolute path.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
