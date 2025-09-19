#include "arch.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(ARCH_X86)
  #include "prefix_x86_64.S.h"
  #include "context_x86.S.h"
#elif defined(ARCH_X64)
  #include "prefix_x86_64.S.h"
  #include "context_x64.S.h"
#elif defined(ARCH_ARM64)
  #include "prefix_arm64.S.h"
  #include "context_arm64.S.h"
#elif defined(ARCH_ARM)
  #include "prefix_arm.S.h"
  #include "context_arm.S.h"
#elif defined(ARCH_MIPS)
  #include "prefix_mips.S.h"
  #include "context_mips.S.h"
#endif

#ifdef __cplusplus
}
#endif
