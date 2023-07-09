=head1 Name

SPVM::Document::NativeAPI::OperationCode - Operation Code Native APIs

=head1 Description

The operation code native APIs of L<SPVM> are the APIs to get information of operation codes.

=head1 Usage

  SPVM_API_OPCODE* api_opcode = env->api->opcode;
  
  int32_t opcode_id = api_opcode->get_id(runtime, opcode);

The C<opcode> is got by the L<get_opcode_by_index|SPVM::Document::NativeAPI::Method/"get_opcode_by_index"> method native API.

=head1 Native APIs

=head1 Native API IDs

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
