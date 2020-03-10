//#include "stdafx.h"

#include "dialog.h"

LRESULT CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL bMsgProcessed = FALSE;

    CDialog *pDlg = (CDialog *)GetProp(hDlg, PROP_THIS);

    if (pDlg)
    {
        bMsgProcessed = pDlg->WndProc(uMsg, wParam, lParam);
        if (!bMsgProcessed)
            bMsgProcessed = pDlg->DlgProc(uMsg, wParam, lParam);
    }
    else
    {
        // Process any messages that can arrive before window associated with an object

        switch(uMsg)
        {
        case WM_INITDIALOG:
            pDlg = (CDialog*)lParam;
            pDlg->m_hWnd = hDlg;
            SetProp(hDlg, PROP_ID, 0);
            SetProp(hDlg, PROP_THIS, (LPVOID)pDlg);
            pDlg->OnInitDialog();
            bMsgProcessed = TRUE;
            break;
        }
    }

    return bMsgProcessed;

//    if (!bMsgProcessed)
//        return DefDlgProc(hDlg, uMsg, wParam, lParam);
//    else
//        return TRUE;
}

BOOL CDialog::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL bMsgProcessed = FALSE;

//    switch(uMsg)
//    {
//    }

    return bMsgProcessed;
}

CDialog::CDialog()
        :CWnd()
{
}

int CDialog::CreateModal(HINSTANCE hInstance,
                         LPCTSTR   lpszTemplate,
                         HWND      hWndParent)
{
    return DialogBoxParam(hInstance, lpszTemplate, hWndParent, 
                          (DLGPROC)::DlgProc, (LPARAM)this);
}
