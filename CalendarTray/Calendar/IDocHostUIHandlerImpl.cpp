#include "StdAfx.h"

#include   "IDocHostUIHandlerImpl.h " 

//--------------------------------------------------------------------------- 
//                                             IUnknown   Method 
//--------------------------------------------------------------------------- 
//QueryInterface 
HRESULT   __stdcall IDocHostUIHandlerImpl::QueryInterface(REFIID   riid,   void   **ppv) 
{ 
    if(IsEqualIID(riid,IID_IUnknown)) 
    { 
        *ppv   =   static_cast <IUnknown*> (this); 
        return   S_OK; 
    } 
    else   if(IsEqualIID(riid,IID_IDocHostUIHandler)) 
    { 
        *ppv   =   static_cast <IDocHostUIHandler*> (this); 
        return   S_OK; 
    } 
    else 
    { 
        *ppv   =   NULL; 
        return   E_NOINTERFACE; 
    } 
} 
//--------------------------------------------------------------------------- 
//AddRef 
ULONG   __stdcall   IDocHostUIHandlerImpl::AddRef() 
{ 
    InterlockedIncrement((long*)&RefCount); 

    return   RefCount; 
} 
//--------------------------------------------------------------------------- 
//Release 
ULONG   __stdcall   IDocHostUIHandlerImpl::Release() 
{ 
    if(InterlockedDecrement((long*)&RefCount)   <=   0) 
        delete   this; 

    return   RefCount; 
} 
//--------------------------------------------------------------------------- 
//                                             IDocHostUIHandler   Method 
//--------------------------------------------------------------------------- 
STDMETHODIMP   IDocHostUIHandlerImpl::ShowContextMenu(DWORD   dwID,POINT   *ppt, 
IUnknown   *pcmdtReserved,IDispatch   *pdispReserved) 
{     
    return   S_OK; 
} 
//--------------------------------------------------------------------------- 
STDMETHODIMP   IDocHostUIHandlerImpl::GetHostInfo(DOCHOSTUIINFO   *pInfo) 
{ 
	pInfo->dwFlags = pInfo->dwFlags | DOCHOSTUIFLAG_NO3DBORDER | DOCHOSTUIFLAG_SCROLL_NO;
	ATLTRACE("pInfo");
    return   S_OK; 
} 
