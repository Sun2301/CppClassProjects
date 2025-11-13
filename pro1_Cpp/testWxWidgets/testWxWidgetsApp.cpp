/***************************************************************
 * Name:      testWxWidgetsApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2025-10-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "testWxWidgetsApp.h"
#include "testWxWidgetsMain.h"

IMPLEMENT_APP(testWxWidgetsApp);

bool testWxWidgetsApp::OnInit()
{
    testWxWidgetsFrame* frame = new testWxWidgetsFrame(0L, _("wxWidgets Application Template"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}
