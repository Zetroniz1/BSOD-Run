#include <windows.h>

typedef NTSTATUS (NTAPI *pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);
typedef NTSTATUS (NTAPI *pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

int main() {
    BOOLEAN bEnabled;
    ULONG uResp;

    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");

    if (hNtdll) {

        pdef_RtlAdjustPrivilege RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
        pdef_NtRaiseHardError NtRaiseHardError = (pdef_NtRaiseHardError)GetProcAddress(hNtdll, "NtRaiseHardError");

        if (RtlAdjustPrivilege && NtRaiseHardError) {

            RtlAdjustPrivilege(19, TRUE, FALSE, &bEnabled);

            NtRaiseHardError(0xC0000022, 0, 0, NULL, 6, &uResp);
        }
    }

    return 0;
}
