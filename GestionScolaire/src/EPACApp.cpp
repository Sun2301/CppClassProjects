#include "EPACApp.h"
#include "frames/LoginFrame.h"

wxIMPLEMENT_APP(EPACApp);

bool EPACApp::OnInit()
{
    LoginFrame* loginFrame = new LoginFrame();
    loginFrame->Show(true);
    return true;
}