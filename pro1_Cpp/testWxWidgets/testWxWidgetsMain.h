/***************************************************************
 * Name:      testWxWidgetsMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2025-10-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef TESTWXWIDGETSMAIN_H
#define TESTWXWIDGETSMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "testWxWidgetsApp.h"

class testWxWidgetsFrame: public wxFrame
{
    public:
        testWxWidgetsFrame(wxFrame *frame, const wxString& title);
        ~testWxWidgetsFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // TESTWXWIDGETSMAIN_H
