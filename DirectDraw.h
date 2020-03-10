#ifndef __DIRECTDRAW_H
#define __DIRECTDRAW_H

#include <assert.h>
#define ASSERT assert

#include <ddraw.h>

class CDirectDraw {

// Attributes
protected:
    BOOL m_bModeSet;

public:
	LPDIRECTDRAW	    m_lpDD;
	LPDIRECTDRAW2	    m_lpDD2;
    LPDIRECTDRAWSURFACE m_lpDDSurface;
	HRESULT m_hResult;

// Operations
public:
	CDirectDraw()
	{
		m_lpDD = NULL;
        m_lpDD2 = NULL;
        m_bModeSet = FALSE;
	}

	~CDirectDraw()
	{
		if (m_lpDD2 && m_bModeSet)
            m_lpDD2->RestoreDisplayMode();
        
        if (m_lpDD2 != NULL)
			m_lpDD2->Release();

		if (m_lpDD != NULL)
			m_lpDD->Release();
	}

	BOOL Create(GUID FAR *lpGUID=NULL)
	{
		m_hResult = DirectDrawCreate(lpGUID, &m_lpDD, NULL);
		ASSERT(m_hResult == DD_OK);

		m_hResult = m_lpDD->QueryInterface(IID_IDirectDraw2,
									      (LPVOID *)&m_lpDD2);
		if(m_hResult != DD_OK)
			m_lpDD2 = NULL;  // DirectDraw2 interface not available
		
		return TRUE;
	}

	BOOL SetCooperativeLevel(CWnd *pWnd, 
							 DWORD dwFlags = DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN)
	{
        HWND hOldWnd = ::SetFocus(pWnd->m_hWnd);
		m_hResult = m_lpDD2->SetCooperativeLevel(pWnd->m_hWnd, dwFlags);
        ::SetFocus(hOldWnd);

/*#ifdef _DEBUG
		if (m_hResult != DD_OK)
			ShowError(_T("SetCooperativeLevel()"), m_hResult);
#endif
*/
		return (m_hResult == DD_OK);
	}

	BOOL SetDisplayMode(DWORD dwWidth, DWORD dwHeight,
						DWORD dwBPP,   DWORD dwRefreshRate=NULL, 
						DWORD dwFlags=NULL)
	{
        m_hResult = m_lpDD2->SetDisplayMode(dwWidth, dwHeight, dwBPP,
									        dwRefreshRate, dwFlags);

	    if (m_hResult == DD_OK)
            m_bModeSet = TRUE;

        return (m_hResult == DD_OK);
	}

    BOOL RestoreDisplayMode()
    {
        m_hResult = m_lpDD2->RestoreDisplayMode();

        return (m_hResult == DD_OK);
    }

    BOOL CreateSurface()
    {
        // Create the primary surface with one back buffer.
        DDSURFACEDESC ddsd;
        ddsd.dwSize = sizeof(ddsd);
        ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
        ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
                              DDSCAPS_FLIP | DDSCAPS_COMPLEX;
        ddsd.dwBackBufferCount = 1;

        m_hResult = m_lpDD2->CreateSurface(&ddsd, &m_lpDDSurface, NULL);
        if(m_hResult == DD_OK)
        {
            // lpDDSPrimary points to the new surface.
HDC hdc;
if (m_lpDDSurface->GetDC(&hdc) == DD_OK)
{
    SetBkColor(hdc, RGB(0, 0, 255));
    SetTextColor(hdc, RGB(255, 255, 0));
    TextOut(hdc, 0, 0, "****FUCK!!!!****", 16);
    m_lpDDSurface->ReleaseDC(hdc);
}


        }
        else
        {
            // The surface was not created
//            ShowError(_T("CreateSurface()"), m_hResult);
        }

        return (m_hResult == DD_OK);
    }

    HRESULT GetAttachedSurface(LPDDSCAPS lpDDSCaps,
                               LPDIRECTDRAWSURFACE2 FAR * lplpDDAttachedSurface)
    {
        return NULL;
    }

/*
#ifdef _DEBUG
	void ShowError(const CString &strFunction, HRESULT hResult)
	{
        CString strError = "UNKNOWN";

        switch(hResult)
        {
        case DDERR_ALREADYINITIALIZED :
            strError = "DDERR_ALREADYINITIALIZED";
            break;
        case DDERR_BLTFASTCANTCLIP :
            strError = "DDERR_BLTFASTCANTCLIP";
            break;
        case DDERR_CANNOTATTACHSURFACE :
            strError = "DDERR_CANNOTATTACHSURFACE";
            break;
        case DDERR_CANNOTDETACHSURFACE :
            strError = "DDERR_CANNOTDETACHSURFACE";
            break;
        case DDERR_CANTCREATEDC :
            strError = "DDERR_CANTCREATEDC";
            break;
        case DDERR_CANTDUPLICATE :
            strError = "DDERR_CANTDUPLICATE";
            break;
        case DDERR_CANTLOCKSURFACE :
            strError = "DDERR_CANTLOCKSURFACE";
            break;
        case DDERR_CANTPAGELOCK :
            strError = "DDERR_CANTPAGELOCK";
            break;
        case DDERR_CANTPAGEUNLOCK :
            strError = "DDERR_CANTPAGEUNLOCK";
            break;
        case DDERR_CLIPPERISUSINGHWND :
            strError = "DDERR_CLIPPERISUSINGHWND";
            break;
        case DDERR_COLORKEYNOTSET :
            strError = "DDERR_COLORKEYNOTSET";
            break;
        case DDERR_CURRENTLYNOTAVAIL :
            strError = "DDERR_CURRENTLYNOTAVAIL";
            break;
        case DDERR_DCALREADYCREATED :
            strError = "DDERR_DCALREADYCREATED";
            break;
        case DDERR_DIRECTDRAWALREADYCREATED :
            strError = "DDERR_DIRECTDRAWALREADYCREATED";
            break;
        case DDERR_EXCEPTION :
            strError = "DDERR_EXCEPTION";
            break;
        case DDERR_EXCLUSIVEMODEALREADYSET :
            strError = "DDERR_EXCLUSIVEMODEALREADYSET";
            break;
        case DDERR_GENERIC :
            strError = "DDERR_GENERIC";
            break;
        case DDERR_HEIGHTALIGN :
            strError = "DDERR_HEIGHTALIGN";
            break;
        case DDERR_HWNDALREADYSET :
            strError = "DDERR_HWNDALREADYSET";
            break;
        case DDERR_HWNDSUBCLASSED :
            strError = "DDERR_HWNDSUBCLASSED";
            break;
        case DDERR_IMPLICITLYCREATED :
            strError = "DDERR_IMPLICITLYCREATED";
            break;
        case DDERR_INCOMPATIBLEPRIMARY :
            strError = "DDERR_INCOMPATIBLEPRIMARY";
            break;
        case DDERR_INVALIDCAPS :
            strError = "DDERR_INVALIDCAPS";
            break;
        case DDERR_INVALIDCLIPLIST :
            strError = "DDERR_INVALIDCLIPLIST";
            break;
        case DDERR_INVALIDDIRECTDRAWGUID :
            strError = "DDERR_INVALIDDIRECTDRAWGUID";
            break;
        case DDERR_INVALIDMODE :
            strError = "DDERR_INVALIDMODE";
            break;
        case DDERR_INVALIDOBJECT :
            strError = "DDERR_INVALIDOBJECT";
            break;
        case DDERR_INVALIDPARAMS :
            strError = "DDERR_INVALIDPARAMS";
            break;
        case DDERR_INVALIDPIXELFORMAT :
            strError = "DDERR_INVALIDPIXELFORMAT";
            break;
        case DDERR_INVALIDPOSITION :
            strError = "DDERR_INVALIDPOSITION";
            break;
        case DDERR_INVALIDRECT :
            strError = "DDERR_INVALIDRECT";
            break;
        case DDERR_INVALIDSURFACETYPE :
            strError = "DDERR_INVALIDSURFACETYPE";
            break;
        case DDERR_LOCKEDSURFACES :
            strError = "DDERR_LOCKEDSURFACES";
            break;
        case DDERR_NO3D :
            strError = "DDERR_NO3D";
            break;
        case DDERR_NOALPHAHW :
            strError = "DDERR_NOALPHAHW";
            break;
        case DDERR_NOBLTHW :
            strError = "DDERR_NOBLTHW";
            break;
        case DDERR_NOCLIPLIST :
            strError = "DDERR_NOCLIPLIST";
            break;
        case DDERR_NOCLIPPERATTACHED :
            strError = "DDERR_NOCLIPPERATTACHED";
            break;
        case DDERR_NOCOLORCONVHW :
            strError = "DDERR_NOCOLORCONVHW";
            break;
        case DDERR_NOCOLORKEY :
            strError = "DDERR_NOCOLORKEY";
            break;
        case DDERR_NOCOLORKEYHW :
            strError = "DDERR_NOCOLORKEYHW";
            break;
        case DDERR_NOCOOPERATIVELEVELSET :
            strError = "DDERR_NOCOOPERATIVELEVELSET";
            break;
        case DDERR_NODC :
            strError = "DDERR_NODC";
            break;
        case DDERR_NODDROPSHW :
            strError = "DDERR_NODDROPSHW";
            break;
        case DDERR_NODIRECTDRAWHW :
            strError = "DDERR_NODIRECTDRAWHW";
            break;
        case DDERR_NODIRECTDRAWSUPPORT :
            strError = "DDERR_NODIRECTDRAWSUPPORT";
            break;
        case DDERR_NOEMULATION :
            strError = "DDERR_NOEMULATION";
            break;
        case DDERR_NOEXCLUSIVEMODE :
            strError = "DDERR_NOEXCLUSIVEMODE";
            break;
        case DDERR_NOFLIPHW :
            strError = "DDERR_NOFLIPHW";
            break;
        case DDERR_NOGDI :
            strError = "DDERR_NOGDI";
            break;
        case DDERR_NOHWND :
            strError = "DDERR_NOHWND";
            break;
        case DDERR_NOMIPMAPHW :
            strError = "DDERR_NOMIPMAPHW";
            break;
        case DDERR_NOMIRRORHW :
            strError = "DDERR_NOMIRRORHW";
            break;
        case DDERR_NOOVERLAYDEST :
            strError = "DDERR_NOOVERLAYDEST";
            break;
        case DDERR_NOOVERLAYHW :
            strError = "DDERR_NOOVERLAYHW";
            break;
        case DDERR_NOPALETTEATTACHED :
            strError = "DDERR_NOPALETTEATTACHED";
            break;
        case DDERR_NOPALETTEHW :
            strError = "DDERR_NOPALETTEHW";
            break;
        case DDERR_NORASTEROPHW :
            strError = "DDERR_NORASTEROPHW";
            break;
        case DDERR_NOROTATIONHW :
            strError = "DDERR_NOROTATIONHW";
            break;
        case DDERR_NOSTRETCHHW :
            strError = "DDERR_NOSTRETCHHW";
            break;
        case DDERR_NOT4BITCOLOR :
            strError = "DDERR_NOT4BITCOLOR";
            break;
        case DDERR_NOT4BITCOLORINDEX :
            strError = "DDERR_NOT4BITCOLORINDEX";
            break;
        case DDERR_NOT8BITCOLOR :
            strError = "DDERR_NOT8BITCOLOR";
            break;
        case DDERR_NOTAOVERLAYSURFACE :
            strError = "DDERR_NOTAOVERLAYSURFACE";
            break;
        case DDERR_NOTEXTUREHW :
            strError = "DDERR_NOTEXTUREHW";
            break;
        case DDERR_NOTFLIPPABLE :
            strError = "DDERR_NOTFLIPPABLE";
            break;
        case DDERR_NOTFOUND :
            strError = "DDERR_NOTFOUND";
            break;
        case DDERR_NOTINITIALIZED :
            strError = "DDERR_NOTINITIALIZED";
            break;
        case DDERR_NOTLOCKED :
            strError = "DDERR_NOTLOCKED";
            break;
        case DDERR_NOTPAGELOCKED :
            strError = "DDERR_NOTPAGELOCKED";
            break;
        case DDERR_NOTPALETTIZED :
            strError = "DDERR_NOTPALETTIZED";
            break;
        case DDERR_NOVSYNCHW :
            strError = "DDERR_NOVSYNCHW";
            break;
        case DDERR_NOZBUFFERHW :
            strError = "DDERR_NOZBUFFERHW";
            break;
        case DDERR_NOZOVERLAYHW :
            strError = "DDERR_NOZOVERLAYHW";
            break;
        case DDERR_OUTOFCAPS :
            strError = "DDERR_OUTOFCAPS";
            break;
        case DDERR_OUTOFMEMORY :
            strError = "DDERR_OUTOFMEMORY";
            break;
        case DDERR_OUTOFVIDEOMEMORY :
            strError = "DDERR_OUTOFVIDEOMEMORY";
            break;
        case DDERR_OVERLAYCANTCLIP :
            strError = "DDERR_OVERLAYCANTCLIP";
            break;
        case DDERR_OVERLAYCOLORKEYONLYONEACTIVE :
            strError = "DDERR_OVERLAYCOLORKEYONLYONEACTIVE";
            break;
        case DDERR_OVERLAYNOTVISIBLE :
            strError = "DDERR_OVERLAYNOTVISIBLE";
            break;
        case DDERR_PALETTEBUSY :
            strError = "DDERR_PALETTEBUSY";
            break;
        case DDERR_PRIMARYSURFACEALREADYEXISTS :
            strError = "DDERR_PRIMARYSURFACEALREADYEXISTS";
            break;
        case DDERR_REGIONTOOSMALL :
            strError = "DDERR_REGIONTOOSMALL";
            break;
        case DDERR_SURFACEALREADYATTACHED :
            strError = "DDERR_SURFACEALREADYATTACHED";
            break;
        case DDERR_SURFACEALREADYDEPENDENT :
            strError = "DDERR_SURFACEALREADYDEPENDENT";
            break;
        case DDERR_SURFACEBUSY :
            strError = "DDERR_SURFACEBUSY";
            break;
        case DDERR_SURFACEISOBSCURED :
            strError = "DDERR_SURFACEISOBSCURED";
            break;
        case DDERR_SURFACELOST :
            strError = "DDERR_SURFACELOST";
            break;
        case DDERR_SURFACENOTATTACHED :
            strError = "DDERR_SURFACENOTATTACHED";
            break;
        case DDERR_TOOBIGHEIGHT :
            strError = "DDERR_TOOBIGHEIGHT";
            break;
        case DDERR_TOOBIGSIZE :
            strError = "DDERR_TOOBIGSIZE";
            break;
        case DDERR_TOOBIGWIDTH :
            strError = "DDERR_TOOBIGWIDTH";
            break;
        case DDERR_UNSUPPORTED :
            strError = "DDERR_UNSUPPORTED";
            break;
        case DDERR_UNSUPPORTEDFORMAT :
            strError = "DDERR_UNSUPPORTEDFORMAT";
            break;
        case DDERR_UNSUPPORTEDMASK :
            strError = "DDERR_UNSUPPORTEDMASK";
            break;
        case DDERR_UNSUPPORTEDMODE :
            strError = "DDERR_UNSUPPORTEDMODE";
            break;
        case DDERR_VERTICALBLANKINPROGRESS :
            strError = "DDERR_VERTICALBLANKINPROGRESS";
            break;
        case DDERR_WASSTILLDRAWING :
            strError = "DDERR_WASSTILLDRAWING";
            break;
        case DDERR_WRONGMODE :
            strError = "DDERR_WRONGMODE";
            break;
        case DDERR_XALIGN :
            strError = "DDERR_XALIGN";
            break;
        }
        TRACE2( "DirectDraw error: Function: %s, Code: %s\n", strFunction, strError);
    }
#endif
*/
};

#endif // __DIRECTDRAW_H