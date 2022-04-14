=head1 NAME

SPVM::Document::NativeAPI::Precompile - SPVM Precompile Native APIs

=head1 SYNOPSYS

  // Precompile API
  void* precompile_api = env->api->precompile;
  
  // New precompile
  void* precompile = precompile_api->new_precompile();
  
  // Free precompile
  precompile_api->free_precompile(precompile);

=head1 DESCRIPTION

SPVM Precompile Native APIs are the public APIs to precompile SPVM methods.

=head1 List of Precompile Native APIs
