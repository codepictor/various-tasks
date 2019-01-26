#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Protocol/Shell.h>


EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE            ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
)   
{
    Print(L"!!! Hello world !!!\n");
    Print(L"Press any key to boot your system\n");

    EFI_SYSTEM_TABLE *gST = SystemTable;
    EFI_BOOT_SERVICES *gBS = gST->BootServices;

    UINTN index = 0;
    EFI_EVENT event = gST->ConIn->WaitForKey;
    gBS->WaitForEvent(1, &event, &index);

    EFI_SHELL_PROTOCOL *EfiShellProtocol;
    EFI_STATUS Status;

    Status = gBS->LocateProtocol(&gEfiShellProtocolGuid,
                                 NULL,
                                 (VOID **) &EfiShellProtocol);

    if (EFI_ERROR(Status)) {
        return Status; 
    }

    EfiShellProtocol->Execute(&ImageHandle,
                              L"\\EFI\\ubuntu\\shimx64.efi",
                              NULL,
                              &Status);

    return Status;
}


