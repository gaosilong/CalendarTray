#pragma once

#include "mshtmhst.h"

#include   <exdispid.h> 

class IDocHostUIHandlerImpl :
	public IDocHostUIHandler
{
private: 

	ULONG   RefCount; 

public:             

	IDocHostUIHandlerImpl():RefCount(0){   } 

	//   IUnknown   Method 
	HRESULT   __stdcall   QueryInterface(REFIID   riid,   void   **ppv); 
	ULONG       __stdcall   AddRef(); 
	ULONG       __stdcall   Release(); 

	//   IDocHostUIHandler   Method 
	STDMETHOD(ShowContextMenu)( 
		/*   [in]   */   DWORD   dwID, 
		/*   [in]   */   POINT   __RPC_FAR   *ppt, 
		/*   [in]   */   IUnknown   __RPC_FAR   *pcmdtReserved, 
		/*   [in]   */   IDispatch   __RPC_FAR   *pdispReserved); 

		STDMETHOD(GetHostInfo)( 
		/*   [out][in]   */   DOCHOSTUIINFO   __RPC_FAR   *pInfo); 

		STDMETHOD(ShowUI)( 
		/*   [in]   */   DWORD   dwID, 
		/*   [in]   */   IOleInPlaceActiveObject   __RPC_FAR   *pActiveObject, 
		/*   [in]   */   IOleCommandTarget   __RPC_FAR   *pCommandTarget, 
		/*   [in]   */   IOleInPlaceFrame   __RPC_FAR   *pFrame, 
		/*   [in]   */   IOleInPlaceUIWindow   __RPC_FAR   *pDoc){   return   E_NOTIMPL;   } 

		STDMETHOD(HideUI)(   void){   return   E_NOTIMPL;   } 

		STDMETHOD(UpdateUI)(   void){   return   E_NOTIMPL;   } 

		STDMETHOD(EnableModeless)( 
			/*   [in]   */   BOOL   fEnable){   return   E_NOTIMPL;   } 

			STDMETHOD(OnDocWindowActivate)( 
			/*   [in]   */   BOOL   fActivate){   return   E_NOTIMPL;   } 

			STDMETHOD(OnFrameWindowActivate)( 
			/*   [in]   */   BOOL   fActivate){   return   E_NOTIMPL;   } 

			STDMETHOD(ResizeBorder)( 
			/*   [in]   */   LPCRECT   prcBorder, 
			/*   [in]   */   IOleInPlaceUIWindow   __RPC_FAR   *pUIWindow, 
			/*   [in]   */   BOOL   fRameWindow){   return   E_NOTIMPL;   } 

			STDMETHOD(TranslateAccelerator)( 
			/*   [in]   */   LPMSG   lpMsg, 
			/*   [in]   */   const   GUID   __RPC_FAR   *pguidCmdGroup, 
			/*   [in]   */   DWORD   nCmdID){   return   E_NOTIMPL;   } 

			STDMETHOD(GetOptionKeyPath)( 
			/*   [out]   */   LPOLESTR   __RPC_FAR   *pchKey, 
			/*   [in]   */   DWORD   dw){   return   E_NOTIMPL;   } 

			STDMETHOD(GetDropTarget)( 
			/*   [in]   */   IDropTarget   __RPC_FAR   *pDropTarget, 
			/*   [out]   */   IDropTarget   __RPC_FAR   *__RPC_FAR   *ppDropTarget){   return   E_NOTIMPL;   } 

			STDMETHOD(GetExternal)( 
			/*   [out]   */   IDispatch   __RPC_FAR   *__RPC_FAR   *ppDispatch){   return   E_NOTIMPL;   } 

			STDMETHOD(TranslateUrl)( 
			/*   [in]   */   DWORD   dwTranslate, 
			/*   [in]   */   OLECHAR   __RPC_FAR   *pchURLIn, 
			/*   [out]   */   OLECHAR   __RPC_FAR   *__RPC_FAR   *ppchURLOut){   return   E_NOTIMPL;   } 

			STDMETHOD(FilterDataObject)( 
			/*   [in]   */   IDataObject   __RPC_FAR   *pDO, 
			/*   [out]   */   IDataObject   __RPC_FAR   *__RPC_FAR   *ppDORet){   return   E_NOTIMPL;   } 

};
