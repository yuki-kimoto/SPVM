#include <assert.h>
#include <string.h>

#include "spvm_core_func.h"



#include "spvm_core_func_bind.h"

#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_sub.h"
#include "spvm_op.h"

void SPVM_CORE_FUNC_BIND_bind_core_func(SPVM_COMPILER* compiler, SPVM_LIST* op_subs) {
  // Bind native subroutine
  {
    int32_t i;
    for (i = 0; i < op_subs->length; i++) {
      SPVM_OP* op_sub = SPVM_LIST_fetch(op_subs, i);
      SPVM_SUB* sub = op_sub->uv.sub;
      
      if (sub->have_native_desc) {
        // Sub abs name
        const char* sub_name = sub->op_name->uv.name;
        switch (sub_name[0]) {
          case 'p':
            if (strcmp(sub_name, "print") == 0) {
              sub->native_address = SPVM_CORE_FUNC_print;
            }
            break;
          case 'w':
            if (strcmp(sub_name, "warn") == 0) {
              sub->native_address = SPVM_CORE_FUNC_warn;
            }
            break;
          case 't':
            if (strcmp(sub_name, "time") == 0) {
              sub->native_address = SPVM_CORE_FUNC_time;
            }
            break;
          default:
            assert(0);
        }
      }
    }
  }
}
