#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include <wx/wx.h>

class LoginFrame : public wxFrame
{
public:
    LoginFrame();

private:
    // Composants de l'interface
    wxTextCtrl* txtLogin;
    wxTextCtrl* txtPassword;
    wxButton* btnConnexion;
    wxButton* btnQuitter;
    wxChoice* choixRole;
    wxStaticText* lblTitre;
    wxStaticText* lblLogin;
    wxStaticText* lblPassword;
    wxStaticText* lblRole;

    // Gestionnaires d'événements
    void OnConnexion(wxCommandEvent& event);
    void OnQuitter(wxCommandEvent& event);
    void OnRoleChange(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // LOGINFRAME_H