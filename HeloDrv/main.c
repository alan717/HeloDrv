#include <ntddk.h>
#include <ntstrsafe.h>

VOID DriverUnload(IN PDRIVER_OBJECT pDrvObj)   //ж�غ���
{
	HANDLE handle = 0;
	UNREFERENCED_PARAMETER(pDrvObj);

	handle = PsGetCurrentProcessId();

	DbgPrint("[NtDemoDrv]DriverUnload.\n");
}


NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDrvObj, IN PUNICODE_STRING pRegPath)   //��ں���
{
	UNREFERENCED_PARAMETER(pRegPath);

	pDrvObj->DriverUnload = DriverUnload;
	//KeWaitForSingleObject;
	DbgPrint("[NtDemoDrv]DriverEntry.\n");
	return STATUS_SUCCESS;
}

