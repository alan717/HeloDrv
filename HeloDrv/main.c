#include <ntddk.h>
#include <ntstrsafe.h>

VOID DriverUnload(IN PDRIVER_OBJECT pDrvObj)   //卸载函数
{
	HANDLE handle = 0;
	UNREFERENCED_PARAMETER(pDrvObj);

	handle = PsGetCurrentProcessId();

	DbgPrint("[NtDemoDrv]DriverUnload.\n");
}


NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDrvObj, IN PUNICODE_STRING pRegPath)   //入口函数
{
	UNREFERENCED_PARAMETER(pRegPath);

	pDrvObj->DriverUnload = DriverUnload;
	//KeWaitForSingleObject;
	DbgPrint("[NtDemoDrv]DriverEntry.\n");
	return STATUS_SUCCESS;
}

