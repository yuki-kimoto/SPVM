#include "spvm_call_stack_info.h"
#include "spvm_runtime.h"

#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_field.h"
#include "spvm_compiler.h"
#include "spvm_my.h"
#include "spvm_op.h"
#include "spvm_list.h"

void SPVM_CALL_STACK_init_call_stack_info(SPVM_CALL_STACK_INFO* call_stack_info, SPVM_RUNTIME* runtime, int32_t sub_id) {
  SPVM_COMPILER* compiler = runtime->compiler;

  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;
  
  // Length
  call_stack_info->length = sub->op_mys->length + 1 + sub->auto_dec_ref_count_stack_max_length;
  
  call_stack_info->auto_dec_ref_count_stack_top_index = sub->op_mys->length;
  call_stack_info->auto_dec_ref_count_stack_base = call_stack_info->auto_dec_ref_count_stack_top_index + 1;
}
