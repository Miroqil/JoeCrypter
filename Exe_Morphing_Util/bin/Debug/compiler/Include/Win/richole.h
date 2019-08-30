#ifndef _RICHOLE_H
#define _RICHOLE_H

#if __POCC__ >= 500
#pragma once
#endif

/* Windows RichEdit OLE Extension definitions */

#if defined(WIN32_DEFAULT_LIBS)
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#endif

#define REO_GETOBJ_NO_INTERFACES  0
#define REO_GETOBJ_POLEOBJ  1
#define REO_GETOBJ_PSTG  2
#define REO_GETOBJ_POLESITE  4
#define REO_GETOBJ_ALL_INTERFACES  7

#define REO_CP_SELECTION  ((ULONG)-1)
#define REO_IOB_SELECTION  ((ULONG)-1)
#define REO_IOB_USE_CP  ((ULONG)-2)

#define REO_NULL  0x00000000
#define REO_READWRITEMASK  0x0000003F
#define REO_DONTNEEDPALETTE  0x00000020
#define REO_BLANK  0x00000010
#define REO_DYNAMICSIZE  0x00000008
#define REO_INVERTEDSELECT  0x00000004
#define REO_BELOWBASELINE  0x00000002
#define REO_RESIZABLE  0x00000001
#define REO_LINK  0x80000000
#define REO_STATIC  0x40000000
#define REO_SELECTED  0x08000000
#define REO_OPEN  0x04000000
#define REO_INPLACEACTIVE  0x02000000
#define REO_HILITED  0x01000000
#define REO_LINKAVAILABLE  0x00800000
#define REO_GETMETAFILE  0x00400000

#define RECO_PASTE  0
#define RECO_DROP  1
#define RECO_COPY  2
#define RECO_CUT  3
#define RECO_DRAG  4

DEFINE_GUID(IID_IRichEditOle,0x00020D00,0,0,0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IRichEditOleCallback,0x00020D03,0,0,0xC0,0,0,0,0,0,0,0x46);

#ifndef INITGUID
typedef struct _reobject {
    DWORD cbStruct;
    LONG cp;
    CLSID clsid;
    LPOLEOBJECT poleobj;
    LPSTORAGE pstg;
    LPOLECLIENTSITE polesite;
    SIZEL sizel;
    DWORD dvaspect;
    DWORD dwFlags;
    DWORD dwUser;
} REOBJECT;

#undef INTERFACE
#define INTERFACE IRichEditOle
DECLARE_INTERFACE_(IRichEditOle, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    STDMETHOD(GetClientSite)(THIS_ LPOLECLIENTSITE*) PURE;
    STDMETHOD_(LONG,GetObjectCount)(THIS) PURE;
    STDMETHOD_(LONG,GetLinkCount)(THIS) PURE;
    STDMETHOD(GetObject)(THIS_ LONG, REOBJECT*,DWORD) PURE;
    STDMETHOD(InsertObject)(THIS_ REOBJECT*) PURE;
    STDMETHOD(ConvertObject)(THIS_ LONG,REFCLSID,LPCSTR) PURE;
    STDMETHOD(ActivateAs)(THIS_ REFCLSID,REFCLSID) PURE;
    STDMETHOD(SetHostNames)(THIS_ LPCSTR,LPCSTR) PURE;
    STDMETHOD(SetLinkAvailable)(THIS_ LONG,BOOL) PURE;
    STDMETHOD(SetDvaspect)(THIS_ LONG,DWORD) PURE;
    STDMETHOD(HandsOffStorage)(THIS_ LONG) PURE;
    STDMETHOD(SaveCompleted)(THIS_ LONG,LPSTORAGE) PURE;
    STDMETHOD(InPlaceDeactivate)(THIS) PURE;
    STDMETHOD(ContextSensitiveHelp)(THIS_ BOOL) PURE;
    STDMETHOD(GetClipboardData)(THIS_ CHARRANGE*,DWORD,LPDATAOBJECT*) PURE;
    STDMETHOD(ImportDataObject)(THIS_ LPDATAOBJECT,CLIPFORMAT,HGLOBAL) PURE;
};
typedef IRichEditOle *LPRICHEDITOLE;

#undef INTERFACE
#define INTERFACE IRichEditOleCallback
DECLARE_INTERFACE_(IRichEditOleCallback, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    STDMETHOD(GetNewStorage)(THIS_ LPSTORAGE*) PURE;
    STDMETHOD(GetInPlaceContext)(THIS_ LPOLEINPLACEFRAME*,LPOLEINPLACEUIWINDOW*,LPOLEINPLACEFRAMEINFO) PURE;
    STDMETHOD(ShowContainerUI)(THIS_ BOOL) PURE;
    STDMETHOD(QueryInsertObject)(THIS_ LPCLSID,LPSTORAGE,LONG) PURE;
    STDMETHOD(DeleteObject)(THIS_ LPOLEOBJECT) PURE;
    STDMETHOD(QueryAcceptData)(THIS_ LPDATAOBJECT,CLIPFORMAT*,DWORD,BOOL,HGLOBAL) PURE;
    STDMETHOD(ContextSensitiveHelp)(THIS_ BOOL) PURE;
    STDMETHOD(GetClipboardData)(THIS_ CHARRANGE*,DWORD,LPDATAOBJECT*) PURE;
    STDMETHOD(GetDragDropEffect)(THIS_ BOOL,DWORD,PDWORD) PURE;
    STDMETHOD(GetContextMenu)(THIS_ WORD,LPOLEOBJECT,CHARRANGE*,HMENU*) PURE;
};
typedef IRichEditOleCallback *LPRICHEDITOLECALLBACK;
#endif

#endif /* _RICHOLE_H */