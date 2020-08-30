/***************************************************************************
	Copyright (c) 2020 Philip Fortier

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
***************************************************************************/
// EditViewChildFrame.cpp : implementation file
//

#include "stdafx.h"
#include "AppState.h"
#include "CursorChildFrame.h"
#include "RasterView.h"

// CCursorChildFrame

IMPLEMENT_DYNCREATE(CCursorChildFrame, CMDITabChildWnd)

CCursorChildFrame::CCursorChildFrame()
{
	_pViewMainView = NULL;
}

CCursorChildFrame::~CCursorChildFrame()
{
}

BEGIN_MESSAGE_MAP(CCursorChildFrame, CMDITabChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()



void CCursorChildFrame::HookUpNonViews(CDocument *pDoc)
{
}


int CCursorChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CCursorChildFrame::OnCmdMsg(UINT nID, int nCode, void *pExtra, AFX_CMDHANDLERINFO *pHandlerInfo)
{
	BOOL fRet = __super::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	if (!fRet)
	{
		// If unhandled, give it the main (even if it was non-active).
		// NOTE: if it was active, it was already asked to handle it above.
		// We could optimize for that case here, if desired.
		if (GetActiveView())
		{
			fRet = GetActiveView()->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
		}

		if (!fRet)
		{
			// Give to CommandType view?

		}
	}
	return fRet;
}


// CCursorChildFrame message handlers
