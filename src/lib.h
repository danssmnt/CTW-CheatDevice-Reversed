#ifndef LIB_H_
#define LIB_H_

#include <psptypes.h>
#include "sctrl.h"

/*
 * UndefinedFunction_00000AB8
 * REV: UNUSED FUNCTION - Check if address is a valid PSP mem address.
 */
int __attribute__((used)) UNUSED_00000AB8_AddressInRange(u32 addr);

/*
 * FUN_00000AE8
 * REV: Trim whitespace (from start and end of str)
 */
char* trim_whitespace(char* string);

/*
 * FUN_00000BB8
 * REV: Finds module by it's name
 *      I'm not 100% sure it is that but should be
 */
SceModule2* FindModuleByName(const char* module);

/*
 * FUN_00000C5C
 * REV: Unknown? Doesn't seem to match any known qwikrazor87 made function.
 *      Could be 'FindExport'.
 */
u32 UNK_FindKernelMod(char* module, char* library, u32 nid);

/*
 * FUN_00000DD8
 * REV: Clears D and I cache
 */
void ClearCaches(void);

/*
 * FUN_00000DF4
 * REV: Clears the framebuffer with a custom color
 */
void ClearFrameBuf(u32 color);

/*
 * FUN_00000E18
 * REV: Print to screen (almost like pspDebugScreenPrintf)
 */
void psp_printf(int x, int y, char* string, u32 color);

/*
 * FUN_00000F88
 * REV: UNUSED FUNCTION - Doesn't do anything
 */
void UNUSED_00000F88_Empty(void);

#endif /* LIB_H_ */