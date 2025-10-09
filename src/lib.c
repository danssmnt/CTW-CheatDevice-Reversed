#include <pspkernel.h>
#include <psputilsforkernel.h>
#include <string.h>

#include "lib.h"
#include "main.h"

/*
 * UndefinedFunction_00000AB8
 * REV: UNUSED FUNCTION - Check if address is a valid PSP Memory address.
 */
int __attribute__((used)) UNUSED_00000AB8_AddressInRange(u32 addr)
{
  return (addr >= 0x08400000 && addr < 0x0A000000);
}

/*
 * FUN_00000AE8
 * REV: Trim whitespace (from start and end of str)
 */
char* trim_whitespace(char* string)
{
  char* char_ptr = string + 1;
  char* next_char_ptr;
  char  curr_char = *string;
  char* eos_ptr;
  char* last_valid_char_ptr;

  while( 1 ) {
    last_valid_char_ptr = char_ptr + -1;
    next_char_ptr = char_ptr + 1;

    if (curr_char == '\0') break;

    if (curr_char == ' ') {
      curr_char = *char_ptr;
      char_ptr = next_char_ptr;
    }
    else if (curr_char == '\t') {
      curr_char = *char_ptr;
      char_ptr = next_char_ptr;
    }
    else if (curr_char == '\r') {
      curr_char = *char_ptr;
      char_ptr = next_char_ptr;
    }
    else {
      eos_ptr = last_valid_char_ptr;

      if (curr_char != '\v') goto joined_r0x00000b40;

      curr_char = *char_ptr;
      char_ptr = next_char_ptr;
    }
  }
  curr_char = *string;
  eos_ptr = string;
  
joined_r0x00000b40:
  while (curr_char != '\n') {
    curr_char = eos_ptr[1];
    eos_ptr = eos_ptr + 1;
  }
  curr_char = eos_ptr[-1];
  *eos_ptr = '\0';
  eos_ptr = eos_ptr + -1;

  while( 1 ) {
    if (curr_char == '\n') {
      return last_valid_char_ptr;
    }
    if (curr_char == ' ') {
      *eos_ptr = '\0';
    }
    else if (curr_char == '\t') {
      *eos_ptr = '\0';
    }
    else if (curr_char == '\r') {
      *eos_ptr = '\0';
    }
    else {
      if (curr_char != '\v') {
        return last_valid_char_ptr;
      }
      *eos_ptr = '\0';
    }
    eos_ptr = eos_ptr + -1;
    curr_char = *eos_ptr;
  };
}

/*
 * FUN_00000BB8
 * REV: Finds module by it's name
 *      I'm not 100% sure it is that but should be it.
 */
SceModule2* FindModuleByName(const char* module)
{
  SceModule2* mod = NULL;
  u32 kaddr = 0x88000000;

  while (((( !strcmp((const char *)kaddr, module) || (mod = *(SceModule2 **)(kaddr + 0x64), mod != *(SceModule2 **)(kaddr + 0x78))) ||
        ( *(int *)(kaddr + 0x68) != *(int *)(kaddr + 0x88) )) ||
        ( (!mod || (*(int *)(kaddr + 0x68) == 0) )))) {

    kaddr += 4;

    if (kaddr == 0x88400000) {
      return NULL;
    }

  }

  return mod;
}

/*
 * FUN_00000C5C
 * REV: Unknown? Doesn't seem to match any known qwikrazor87 made function.
 *      Doesn't help that the output is this shit, thanks Ghidra!
 *
 *      Those comparisons adding 0xf7c00000U and 0x78000000U are for checking if address is valid
 *      Wonder if that UNUSED_00000AB8_AddressInRange func was inlined by the compiler...
 */
u32 UNK_FindKernelMod(char* module, char* library, u32 nid)
{
  char* pcVar1;
  SceModule2* mod = FindModuleByName(module);
  int iVar2;
  u32 uVar3;
  int iVar4;
  u32* puVar5;
  SceModule2* pSVar6;

  if (mod) {
    pSVar6 = (SceModule2 *)0xa000000;
    if (((u32 *)0x17fffff < mod[-0xb1a20].segmentaddr) &&
       (pSVar6 = (SceModule2 *)0x8800000, (char *)0x3fffff < mod[-0xac688].modname + 0x18)) {
      pSVar6 = (SceModule2 *)0x88400000;
    }
    pcVar1 = mod->modname;
    for (; pcVar1 = pcVar1 + 4, mod < pSVar6; mod = (SceModule2 *)&mod->attribute) {
      if (((((int)mod->next + 0xf7c00000U < 0x1c00000) || ((int)mod->next + 0x78000000U < 0x2000000)
           ) && ((*(int *)pcVar1 + 0xf7c00000U < 0x1c00000 ||
                 (*(int *)pcVar1 + 0x78000000U < 0x2000000)))) &&
         (iVar2 = strcmp(library,mod->next), iVar2 == 0)) {
        iVar2 = (uint)(char)mod->modname[1] + (uint)*(ushort *)(mod->modname + 2);
        puVar5 = *(u32 **)pcVar1;
        if (!iVar2) {
          return 0;
        }
        uVar3 = *puVar5;
        iVar4 = iVar2;
        while( 1 ) {
          if (uVar3 == nid) {
            return puVar5[iVar2];
          }
          iVar4--;
          puVar5++;
          if (!iVar4) break;
          uVar3 = *puVar5;
        }
        return 0;
      }
    }
  }
  return 0;
}

/*
 * FUN_00000DD8
 * REV: Clears D and I cache
 */
void ClearCaches(void)
{
  sceKernelDcacheWritebackInvalidateAll();
  sceKernelIcacheInvalidateAll();
  return;
}

/*
 * FUN_00000DF4
 * REV: Clears the framebuffer with a custom color
 */
void ClearFrameBuf(u32 color)
{
  u32* framebuf_ptr = (u32 *)(0x44000000);

  while (framebuf_ptr != (u32 *)0x44088000) {
    *framebuf_ptr = color;
    framebuf_ptr++;
  }
  return;
}

/*
 * FUN_00000E18
 * REV: Print to screen (almost like a custom pspDebugScreenPrintf)
 */
void psp_printf(int x, int y, char* string, u32 color)
{
  uint uVar1;
  int string_len = strlen(string);
  char* str_ptr = string;
  uint str_len;
  int curr_char;
  u32* puVar2;
  char* pbVar3;
  u32* curr_framebuf_addr;
  u32* framebuf_limit;
  uint str_char_count = 0;
  uint curr_x = x;
  int stop_drawing;

  if (string_len > 0) {
    do {
      curr_char = (int)*str_ptr;
      if (curr_char == L'\n') {
        y += 16;
        curr_x = x;
      }
      else if (curr_char == L'\t') {
        curr_x = curr_x + 32;
      }
      else {
        if (471 < curr_x) {
          return;
        }
        if (y < 0) {
          return;
        }
        if (255 < y) {
          return;
        }
        if (((curr_char - 33U) & 0xff) < L'^') {

          /* REV: Cool math to determine the framebuffer addr by x and y position. */
          curr_framebuf_addr = (u32 *)((curr_x + 0x11000000 + y * 0x200) * 4);
          
          pbVar3 = font + (char)(curr_char - 33U) * 0x10;
          framebuf_limit = curr_framebuf_addr + 0x1e00;
          while( 1 ) {
            str_len = 0;
            puVar2 = curr_framebuf_addr;
            do {
              uVar1 = str_len & 0x1f;
              str_len++;
              if ((0x80 >> uVar1 & (uint)*pbVar3) != 0) {
                *puVar2 = color;
              }
              puVar2++;
            } while (str_len != 8);
            stop_drawing = curr_framebuf_addr == framebuf_limit;

            curr_framebuf_addr += 0x200;

            if (stop_drawing) break;

            pbVar3++;
          }
        }
        curr_x += 8;
      }
      str_char_count++;
      str_len = strlen(string);
      str_ptr = string + str_char_count;
    } while (str_char_count < str_len);
  }
  return;
}

/*
 * FUN_00000F88
 * REV: UNUSED FUNCTION - Doesn't do anything
 */
void __attribute__((used)) UNUSED_00000F88_Empty(void)
{
  return;
}