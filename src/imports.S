	.set noreorder

#include "pspstub.s"

	STUB_START "SystemCtrlForKernel", 0x00090000, 0x00010005
	STUB_FUNC	0x1C90BECB, sctrlHENSetStartModuleHandler
	STUB_END

    STUB_START "SysMemForKernel", 0x00010011, 0x00010005
	STUB_FUNC	0xEF29061C, sceKernelGetGameInfo
	STUB_END