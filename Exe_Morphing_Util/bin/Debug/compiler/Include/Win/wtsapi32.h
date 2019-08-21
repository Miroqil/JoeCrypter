#ifndef _WTSAPI32_H
#define _WTSAPI32_H

#if __POCC__ >= 500
#pragma once
#endif

/* Windows Terminal Server API definitions */

#if defined(WIN32_DEFAULT_LIBS)
#pragma comment(lib, "wtsapi32.lib")
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define WTS_CURRENT_SERVER  ((HANDLE)NULL)
#define WTS_CURRENT_SERVER_HANDLE  ((HANDLE)NULL)
#define WTS_CURRENT_SERVER_NAME  (NULL)

#define WTS_CURRENT_SESSION  ((DWORD)-1)

#ifndef IDTIMEOUT
#define IDTIMEOUT  32000
#endif
#ifndef IDASYNC
#define IDASYNC  32001
#endif

#define USERNAME_LENGTH  20
#define CLIENTNAME_LENGTH  20
#define CLIENTADDRESS_LENGTH  30

#define WTS_WSD_LOGOFF  0x00000001
#define WTS_WSD_SHUTDOWN  0x00000002
#define WTS_WSD_REBOOT  0x00000004
#define WTS_WSD_POWEROFF  0x00000008
#define WTS_WSD_FASTREBOOT  0x00000010

#define MAX_ELAPSED_TIME_LENGTH  15
#define MAX_DATE_TIME_LENGTH  56
#define WINSTATIONNAME_LENGTH  32
#define DOMAIN_LENGTH  17

#define WTS_PROTOCOL_TYPE_CONSOLE  0
#define WTS_PROTOCOL_TYPE_ICA  1
#define WTS_PROTOCOL_TYPE_RDP  2

#define WTS_EVENT_NONE  0x00000000
#define WTS_EVENT_CREATE  0x00000001
#define WTS_EVENT_DELETE  0x00000002
#define WTS_EVENT_RENAME  0x00000004
#define WTS_EVENT_CONNECT  0x00000008
#define WTS_EVENT_DISCONNECT  0x00000010
#define WTS_EVENT_LOGON  0x00000020
#define WTS_EVENT_LOGOFF  0x00000040
#define WTS_EVENT_STATECHANGE  0x00000080
#define WTS_EVENT_LICENSE  0x00000100
#define WTS_EVENT_ALL  0x7FFFFFFF
#define WTS_EVENT_FLUSH  0x80000000

#define REMOTECONTROL_KBDSHIFT_HOTKEY  0x1
#define REMOTECONTROL_KBDCTRL_HOTKEY  0x2
#define REMOTECONTROL_KBDALT_HOTKEY  0x4

#define WTS_CHANNEL_OPTION_DYNAMIC  0x00000001
#define WTS_CHANNEL_OPTION_DYNAMIC_PRI_LOW  0x00000000
#define WTS_CHANNEL_OPTION_DYNAMIC_PRI_MED  0x00000002
#define WTS_CHANNEL_OPTION_DYNAMIC_PRI_HIGH  0x00000004
#define WTS_CHANNEL_OPTION_DYNAMIC_PRI_REAL  0x00000006

#define NOTIFY_FOR_ALL_SESSIONS  1
#define NOTIFY_FOR_THIS_SESSION  0

typedef enum _WTS_CONNECTSTATE_CLASS {
    WTSActive,
    WTSConnected,
    WTSConnectQuery,
    WTSShadow,
    WTSDisconnected,
    WTSIdle,
    WTSListen,
    WTSReset,
    WTSDown,
    WTSInit,
} WTS_CONNECTSTATE_CLASS;

typedef struct _WTS_SERVER_INFOW {
    LPWSTR pServerName;
} WTS_SERVER_INFOW, *PWTS_SERVER_INFOW;

typedef struct _WTS_SERVER_INFOA {
    LPSTR pServerName;
} WTS_SERVER_INFOA, *PWTS_SERVER_INFOA;

typedef struct _WTS_SESSION_INFOW {
    DWORD SessionId;
    LPWSTR pWinStationName;
    WTS_CONNECTSTATE_CLASS State;
} WTS_SESSION_INFOW, *PWTS_SESSION_INFOW;

typedef struct _WTS_SESSION_INFOA {
    DWORD SessionId;
    LPSTR pWinStationName;
    WTS_CONNECTSTATE_CLASS State;
} WTS_SESSION_INFOA, *PWTS_SESSION_INFOA;

typedef struct _WTS_PROCESS_INFOW {
    DWORD SessionId;
    DWORD ProcessId;
    LPWSTR pProcessName;
    PSID pUserSid;
} WTS_PROCESS_INFOW, *PWTS_PROCESS_INFOW;

typedef struct _WTS_PROCESS_INFOA {
    DWORD SessionId;
    DWORD ProcessId;
    LPSTR pProcessName;
    PSID pUserSid;
} WTS_PROCESS_INFOA, *PWTS_PROCESS_INFOA;

typedef enum _WTS_INFO_CLASS {
    WTSInitialProgram,
    WTSApplicationName,
    WTSWorkingDirectory,
    WTSOEMId,
    WTSSessionId,
    WTSUserName,
    WTSWinStationName,
    WTSDomainName,
    WTSConnectState,
    WTSClientBuildNumber,
    WTSClientName,
    WTSClientDirectory,
    WTSClientProductId,
    WTSClientHardwareId,
    WTSClientAddress,
    WTSClientDisplay,
    WTSClientProtocolType,
    WTSIdleTime,
    WTSLogonTime,
    WTSIncomingBytes,
    WTSOutgoingBytes,
    WTSIncomingFrames,
    WTSOutgoingFrames,
    WTSClientInfo,
    WTSSessionInfo
} WTS_INFO_CLASS;

typedef struct _WTSINFOW {
    WTS_CONNECTSTATE_CLASS State;
    DWORD SessionId;
    DWORD IncomingBytes;
    DWORD OutgoingBytes;
    DWORD IncomingFrames;
    DWORD OutgoingFrames;
    DWORD IncomingCompressedBytes;
    DWORD OutgoingCompressedBytes;
    WCHAR WinStationName[WINSTATIONNAME_LENGTH];
    WCHAR Domain[DOMAIN_LENGTH];
    WCHAR UserName[USERNAME_LENGTH + 1];
    LARGE_INTEGER ConnectTime;
    LARGE_INTEGER DisconnectTime;
    LARGE_INTEGER LastInputTime;
    LARGE_INTEGER LogonTime;
    LARGE_INTEGER CurrentTime;
} WTSINFOW, *PWTSINFOW;

typedef struct _WTSINFOA {
    WTS_CONNECTSTATE_CLASS State;
    DWORD SessionId;
    DWORD IncomingBytes;
    DWORD OutgoingBytes;
    DWORD IncomingFrames;
    DWORD OutgoingFrames;
    DWORD IncomingCompressedBytes;
    DWORD OutgoingCompressedBy;
    CHAR WinStationName[WINSTATIONNAME_LENGTH];
    CHAR Domain[DOMAIN_LENGTH];
    CHAR UserName[USERNAME_LENGTH + 1];
    LARGE_INTEGER ConnectTime;
    LARGE_INTEGER DisconnectTime;
    LARGE_INTEGER LastInputTime;
    LARGE_INTEGER LogonTime;
    LARGE_INTEGER CurrentTime;
} WTSINFOA, *PWTSINFOA;

typedef struct _WTSCLIENTW {
    WCHAR ClientName[CLIENTNAME_LENGTH + 1];
    WCHAR Domain[DOMAIN_LENGTH + 1];
    WCHAR UserName[USERNAME_LENGTH + 1];
    WCHAR WorkDirectory[MAX_PATH + 1];
    WCHAR InitialProgram[MAX_PATH + 1];
    BYTE EncryptionLevel;
    ULONG ClientAddressFamily;
    USHORT ClientAddress[CLIENTADDRESS_LENGTH + 1];
    USHORT HRes;
    USHORT VRes;
    USHORT ColorDepth;
    WCHAR ClientDirectory[MAX_PATH + 1];
    ULONG ClientBuildNumber;
    ULONG ClientHardwareId;
    USHORT ClientProductId;
    USHORT OutBufCountHost;
    USHORT OutBufCountClient;
    USHORT OutBufLength;
    WCHAR DeviceId[MAX_PATH + 1];
} WTSCLIENTW, *PWTSCLIENTW;

typedef struct _WTSCLIENTA {
    CHAR ClientName[CLIENTNAME_LENGTH + 1];
    CHAR Domain[DOMAIN_LENGTH + 1];
    CHAR UserName[USERNAME_LENGTH + 1];
    CHAR WorkDirectory[MAX_PATH + 1];
    CHAR InitialProgram[MAX_PATH + 1];
    BYTE EncryptionLevel;
    ULONG ClientAddressFamily;
    USHORT ClientAddress[CLIENTADDRESS_LENGTH + 1];
    USHORT HRes;
    USHORT VRes;
    USHORT ColorDepth;
    CHAR ClientDirectory[MAX_PATH + 1];
    ULONG ClientBuildNumber;
    ULONG ClientHardwareId;
    USHORT ClientProductId;
    USHORT OutBufCountHost;
    USHORT OutBufCountClient;
    USHORT OutBufLength;
    CHAR DeviceId[MAX_PATH + 1];
} WTSCLIENTA, *PWTSCLIENTA;

typedef struct _WTS_CLIENT_ADDRESS {
    DWORD AddressFamily;
    BYTE Address[20];
} WTS_CLIENT_ADDRESS, *PWTS_CLIENT_ADDRESS;

typedef struct _WTS_CLIENT_DISPLAY {
    DWORD HorizontalResolution;
    DWORD VerticalResolution;
    DWORD ColorDepth;
} WTS_CLIENT_DISPLAY, *PWTS_CLIENT_DISPLAY;

typedef enum _WTS_CONFIG_CLASS {
    WTSUserConfigInitialProgram,
    WTSUserConfigWorkingDirectory,
    WTSUserConfigfInheritInitialProgram,
    WTSUserConfigfAllowLogonTerminalServer,
    WTSUserConfigTimeoutSettingsConnections,
    WTSUserConfigTimeoutSettingsDisconnections,
    WTSUserConfigTimeoutSettingsIdle,
    WTSUserConfigfDeviceClientDrives,
    WTSUserConfigfDeviceClientPrinters,
    WTSUserConfigfDeviceClientDefaultPrinter,
    WTSUserConfigBrokenTimeoutSettings,
    WTSUserConfigReconnectSettings,
    WTSUserConfigModemCallbackSettings,
    WTSUserConfigModemCallbackPhoneNumber,
    WTSUserConfigShadowingSettings,
    WTSUserConfigTerminalServerProfilePath,
    WTSUserConfigTerminalServerHomeDir,
    WTSUserConfigTerminalServerHomeDirDrive,
    WTSUserConfigfTerminalServerRemoteHomeDir,
} WTS_CONFIG_CLASS;

typedef struct _WTS_USER_CONFIG_SET_NWSERVERW {
    LPWSTR pNWServerName;
    LPWSTR pNWDomainAdminName;
    LPWSTR pNWDomainAdminPassword;
} WTS_USER_CONFIG_SET_NWSERVERW, *PWTS_USER_CONFIG_SET_NWSERVERW;

typedef struct _WTS_USER_CONFIG_SET_NWSERVERA {
    LPSTR pNWServerName;
    LPSTR pNWDomainAdminName;
    LPSTR pNWDomainAdminPassword;
} WTS_USER_CONFIG_SET_NWSERVERA, *PWTS_USER_CONFIG_SET_NWSERVERA;

typedef enum _WTS_VIRTUAL_CLASS {
    WTSVirtualClientData,
    WTSVirtualFileHandle
} WTS_VIRTUAL_CLASS;

BOOL WINAPI WTSStopRemoteControlSession(ULONG);
BOOL WINAPI WTSStartRemoteControlSessionW(LPWSTR, ULONG, BYTE, USHORT);
BOOL WINAPI WTSStartRemoteControlSessionA(LPSTR, ULONG, BYTE, USHORT);
BOOL WINAPI WTSConnectSessionA(ULONG, ULONG, PSTR, BOOL);
BOOL WINAPI WTSConnectSessionW(ULONG, ULONG, PWSTR, BOOL);
BOOL WINAPI WTSEnumerateServersW(LPWSTR,DWORD,DWORD,PWTS_SERVER_INFOW*,DWORD*);
BOOL WINAPI WTSEnumerateServersA(LPSTR,DWORD,DWORD,PWTS_SERVER_INFOA*,DWORD*);
HANDLE WINAPI WTSOpenServerW(LPWSTR);
HANDLE WINAPI WTSOpenServerA(LPSTR);
VOID WINAPI WTSCloseServer(HANDLE);
BOOL WINAPI WTSEnumerateSessionsW(HANDLE,DWORD,DWORD,PWTS_SESSION_INFOW*,DWORD*);
BOOL WINAPI WTSEnumerateSessionsA(HANDLE,DWORD,DWORD,PWTS_SESSION_INFOA*,DWORD*);
BOOL WINAPI WTSEnumerateProcessesW(HANDLE,DWORD,DWORD,PWTS_PROCESS_INFOW*,DWORD*);
BOOL WINAPI WTSEnumerateProcessesA(HANDLE,DWORD,DWORD,PWTS_PROCESS_INFOA*,DWORD*);
BOOL WINAPI WTSTerminateProcess(HANDLE,DWORD,DWORD);
BOOL WINAPI WTSQuerySessionInformationW(HANDLE,DWORD,WTS_INFO_CLASS,LPWSTR*,DWORD*);
BOOL WINAPI WTSQuerySessionInformationA(HANDLE,DWORD,WTS_INFO_CLASS,LPSTR*,DWORD*);
BOOL WINAPI WTSQueryUserConfigW(LPWSTR,LPWSTR,WTS_CONFIG_CLASS,LPWSTR*,DWORD*);
BOOL WINAPI WTSQueryUserConfigA(LPSTR,LPSTR,WTS_CONFIG_CLASS,LPSTR*,DWORD*);
BOOL WINAPI WTSSetUserConfigW(LPWSTR,LPWSTR,WTS_CONFIG_CLASS,LPWSTR,DWORD);
BOOL WINAPI WTSSetUserConfigA(LPSTR,LPSTR,WTS_CONFIG_CLASS,LPSTR,DWORD);
BOOL WINAPI WTSSendMessageW(HANDLE,DWORD,LPWSTR,DWORD,LPWSTR,DWORD,DWORD,DWORD,DWORD*,BOOL);
BOOL WINAPI WTSSendMessageA(HANDLE,DWORD,LPSTR,DWORD,LPSTR,DWORD,DWORD,DWORD,DWORD*,BOOL);
BOOL WINAPI WTSDisconnectSession(HANDLE,DWORD,BOOL);
BOOL WINAPI WTSLogoffSession(HANDLE,DWORD,BOOL);
BOOL WINAPI WTSShutdownSystem(HANDLE,DWORD);
BOOL WINAPI WTSWaitSystemEvent(HANDLE,DWORD,DWORD*);
HANDLE WINAPI WTSVirtualChannelOpen(HANDLE,DWORD,LPSTR);
HANDLE WINAPI WTSVirtualChannelOpenEx(DWORD,LPSTR,DWORD);
BOOL WINAPI WTSVirtualChannelClose(HANDLE);
BOOL WINAPI WTSVirtualChannelRead(HANDLE,ULONG,PCHAR,ULONG,PULONG);
BOOL WINAPI WTSVirtualChannelWrite(HANDLE,PCHAR,ULONG,PULONG);
BOOL WINAPI WTSVirtualChannelPurgeInput(HANDLE);
BOOL WINAPI WTSVirtualChannelPurgeOutput(HANDLE);
BOOL WINAPI WTSVirtualChannelQuery(HANDLE,WTS_VIRTUAL_CLASS,PVOID*,DWORD*);
VOID WINAPI WTSFreeMemory(PVOID);
BOOL WINAPI WTSRegisterSessionNotification(HWND, DWORD);
BOOL WINAPI WTSUnRegisterSessionNotification(HWND);
BOOL WINAPI WTSRegisterSessionNotificationEx(HANDLE, HWND, DWORD);
BOOL WINAPI WTSUnRegisterSessionNotificationEx(HANDLE, HWND);
BOOL WINAPI WTSQueryUserToken(ULONG, PHANDLE);

#ifdef UNICODE
#define WTS_SERVER_INFO WTS_SERVER_INFOW
#define PWTS_SERVER_INFO PWTS_SERVER_INFOW
#define WTS_SESSION_INFO WTS_SESSION_INFOW
#define PWTS_SESSION_INFO PWTS_SESSION_INFOW
#define WTS_PROCESS_INFO WTS_PROCESS_INFOW
#define PWTS_PROCESS_INFO PWTS_PROCESS_INFOW
#define WTS_USER_CONFIG_SET_NWSERVER WTS_USER_CONFIG_SET_NWSERVERW
#define PWTS_USER_CONFIG_SET_NWSERVER PWTS_USER_CONFIG_SET_NWSERVERW
#define WTSINFO  WTSINFOW
#define PWTSINFO PWTSINFOW
#define WTSCLIENT WTSCLIENTW
#define PWTSCLIENT PWTSCLIENTW
#define WTSStartRemoteControlSession WTSStartRemoteControlSessionW
#define WTSConnectSession WTSConnectSessionW
#define WTSEnumerateServers WTSEnumerateServersW
#define WTSOpenServer WTSOpenServerW
#define WTSEnumerateSessions WTSEnumerateSessionsW
#define WTSEnumerateProcesses WTSEnumerateProcessesW
#define WTSQuerySessionInformation WTSQuerySessionInformationW
#define WTSQueryUserConfig WTSQueryUserConfigW
#define WTSSetUserConfig WTSSetUserConfigW
#define WTSSendMessage WTSSendMessageW
#else
#define WTS_SERVER_INFO WTS_SERVER_INFOA
#define PWTS_SERVER_INFO PWTS_SERVER_INFOA
#define WTS_SESSION_INFO WTS_SESSION_INFOA
#define PWTS_SESSION_INFO PWTS_SESSION_INFOA
#define WTS_PROCESS_INFO WTS_PROCESS_INFOA
#define PWTS_PROCESS_INFO PWTS_PROCESS_INFOA
#define WTS_USER_CONFIG_SET_NWSERVER WTS_USER_CONFIG_SET_NWSERVERA
#define PWTS_USER_CONFIG_SET_NWSERVER PWTS_USER_CONFIG_SET_NWSERVERA
#define WTSINFO  WTSINFOA
#define PWTSINFO PWTSINFOA
#define WTSCLIENT WTSCLIENTA
#define PWTSCLIENT PWTSCLIENTA
#define WTSStartRemoteControlSession WTSStartRemoteControlSessionA
#define WTSConnectSession WTSConnectSessionA
#define WTSEnumerateServers WTSEnumerateServersA
#define WTSOpenServer WTSOpenServerA
#define WTSEnumerateSessions WTSEnumerateSessionsA
#define WTSEnumerateProcesses WTSEnumerateProcessesA
#define WTSQuerySessionInformation WTSQuerySessionInformationA
#define WTSQueryUserConfig WTSQueryUserConfigA
#define WTSSetUserConfig WTSSetUserConfigA
#define WTSSendMessage WTSSendMessageA
#endif /* UNICODE */

#ifdef __cplusplus
}
#endif

#endif /* _WTSAPI32_H */
