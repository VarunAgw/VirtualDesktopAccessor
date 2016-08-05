#pragma once

#include "stdafx.h"

const IID IID_IServiceProvider = {
	0x6D5140C1, 0x7436, 0x11CE, 0x80, 0x34, 0x00, 0xAA, 0x00, 0x60, 0x09, 0xFA };

const CLSID CLSID_ImmersiveShell = {
	0xC2F03A33, 0x21F5, 0x47FA, 0xB4, 0xBB, 0x15, 0x63, 0x62, 0xA2, 0xF2, 0x39 };

const CLSID CLSID_VirtualDesktopManagerInternal = {
	0xC5E0CDCA, 0x7B6E, 0x41B2, 0x9F, 0xC4, 0xD9, 0x39, 0x75, 0xCC, 0x46, 0x7B };

const CLSID CLSID_IVirtualNotificationService = {
	0xA501FDEC, 0x4A09, 0x464C, 0xAE, 0x4E, 0x1B, 0x9C, 0x21, 0xB8, 0x49, 0x18 
};

const CLSID CLSID_IVirtualDesktopManager = {
	0xAA509086, 0x5CA9, 0x4C25, { 0x8f, 0x95, 0x58, 0x9d, 0x3c, 0x07, 0xb4, 0x8a }
};

const CLSID CLSID_VirtualDesktopPinnedApps = {
	0xb5a399e7, 0x1c87, 0x46b8, 0x88, 0xe9, 0xfc, 0x57, 0x47, 0xb1, 0x71, 0xbd
};

// IID same as in MIDL IVirtualDesktopNotification
// C179334C-4295-40D3-BEA1-C654D965605A
const IID IID_IVirtualDesktopNotification = {
	0xC179334C, 0x4295, 0x40D3, { 0xBE, 0xA1, 0xC6, 0x54, 0xD9, 0x65, 0x60, 0x5A }
};


struct IApplicationView : public IUnknown
{
public:

};

MIDL_INTERFACE("FF72FFDD-BE7E-43FC-9C03-AD81681E88E4")
IVirtualDesktop : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE IsViewVisible(
		IApplicationView *pView,
		int *pfVisible) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetID(
		GUID *pGuid) = 0;
};

enum AdjacentDesktop
{
	LeftDirection = 3,
	RightDirection = 4
};


// Old: AF8DA486-95BB-4460-B3B7-6E7A6B2962B5
MIDL_INTERFACE("f31574d6-b682-4cdc-bd56-1827860abec6")
IVirtualDesktopManagerInternal : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetCount(
		UINT *pCount) = 0;

	virtual HRESULT STDMETHODCALLTYPE MoveViewToDesktop(
		IApplicationView *pView,
		IVirtualDesktop *pDesktop) = 0;

	// Since build 10240
	virtual HRESULT STDMETHODCALLTYPE CanViewMoveDesktops(
		IApplicationView *pView,
		int *pfCanViewMoveDesktops) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentDesktop(
		IVirtualDesktop** desktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDesktops(
		IObjectArray **ppDesktops) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAdjacentDesktop(
		IVirtualDesktop *pDesktopReference,
		AdjacentDesktop uDirection,
		IVirtualDesktop **ppAdjacentDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE SwitchDesktop(
		IVirtualDesktop *pDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE CreateDesktopW(
		IVirtualDesktop **ppNewDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE RemoveDesktop(
		IVirtualDesktop *pRemove,
		IVirtualDesktop *pFallbackDesktop) = 0;

	// Since build 10240
	virtual HRESULT STDMETHODCALLTYPE FindDesktop(
		GUID *desktopId,
		IVirtualDesktop **ppDesktop) = 0;
};

// aa509086-5ca9-4c25-8f95-589d3c07b48a ?
MIDL_INTERFACE("a5cd92ff-29be-454c-8d04-d82879fb3f1b")
IVirtualDesktopManager : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE IsWindowOnCurrentVirtualDesktop(
		/* [in] */ __RPC__in HWND topLevelWindow,
		/* [out] */ __RPC__out BOOL *onCurrentDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetWindowDesktopId(
		/* [in] */ __RPC__in HWND topLevelWindow,
		/* [out] */ __RPC__out GUID *desktopId) = 0;

	virtual HRESULT STDMETHODCALLTYPE MoveWindowToDesktop(
		/* [in] */ __RPC__in HWND topLevelWindow,
		/* [in] */ __RPC__in REFGUID desktopId) = 0;
};

MIDL_INTERFACE("C179334C-4295-40D3-BEA1-C654D965605A")
IVirtualDesktopNotification : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopCreated(
		IVirtualDesktop *pDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopDestroyBegin(
		IVirtualDesktop *pDesktopDestroyed,
		IVirtualDesktop *pDesktopFallback) = 0;

	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopDestroyFailed(
		IVirtualDesktop *pDesktopDestroyed,
		IVirtualDesktop *pDesktopFallback) = 0;

	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopDestroyed(
		IVirtualDesktop *pDesktopDestroyed,
		IVirtualDesktop *pDesktopFallback) = 0;

	virtual HRESULT STDMETHODCALLTYPE ViewVirtualDesktopChanged(
		IApplicationView *pView) = 0;

	virtual HRESULT STDMETHODCALLTYPE CurrentVirtualDesktopChanged(
		IVirtualDesktop *pDesktopOld,
		IVirtualDesktop *pDesktopNew) = 0;

};

// Ignore following API's:
#define IImmersiveApplication UINT
#define IApplicationViewChangeListener UINT

DECLARE_INTERFACE_IID_(IApplicationViewCollection, IUnknown, "2C08ADF0-A386-4B35-9250-0FE183476FCC")
{
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObject) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	/*** IApplicationViewCollection methods ***/
	STDMETHOD(GetViews)(THIS_ IObjectArray**) PURE;
	STDMETHOD(GetViewsByZOrder)(THIS_ IObjectArray**) PURE;
	STDMETHOD(GetViewsByAppUserModelId)(THIS_ PCWSTR, IObjectArray**) PURE;
	STDMETHOD(GetViewForHwnd)(THIS_ HWND, IApplicationView**) PURE;
	STDMETHOD(GetViewForApplication)(THIS_ IImmersiveApplication*, IApplicationView**) PURE;
	STDMETHOD(GetViewForAppUserModelId)(THIS_ PCWSTR, IApplicationView**) PURE;
	STDMETHOD(GetViewInFocus)(THIS_ IApplicationView**) PURE;
	STDMETHOD(RefreshCollection)(THIS) PURE;
	STDMETHOD(RegisterForApplicationViewChanges)(THIS_ IApplicationViewChangeListener*, DWORD*) PURE;
	STDMETHOD(RegisterForApplicationViewPositionChanges)(THIS_ IApplicationViewChangeListener*, DWORD*) PURE;
	STDMETHOD(UnregisterForApplicationViewChanges)(THIS_ DWORD) PURE;
};


MIDL_INTERFACE("0CD45E71-D927-4F15-8B0A-8FEF525337BF")
IVirtualDesktopNotificationService : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE Register(
		IVirtualDesktopNotification *pNotification,
		DWORD *pdwCookie) = 0;

	virtual HRESULT STDMETHODCALLTYPE Unregister(
		DWORD dwCookie) = 0;
};