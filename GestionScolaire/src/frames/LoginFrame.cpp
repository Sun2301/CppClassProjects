#include "frames/LoginFrame.h"
#include <wx/msgdlg.h>

// Table des événements
wxBEGIN_EVENT_TABLE(LoginFrame, wxFrame)
    EVT_BUTTON(wxID_OK, LoginFrame::OnConnexion)
    EVT_BUTTON(wxID_EXIT, LoginFrame::OnQuitter)
    EVT_CHOICE(wxID_ANY, LoginFrame::OnRoleChange)
wxEND_EVENT_TABLE()

LoginFrame::LoginFrame()
    : wxFrame(nullptr, wxID_ANY, "EPAC - Système de Gestion Scolaire", 
              wxDefaultPosition, wxSize(500, 400))
{
    // Panneau principal
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(240, 240, 240));

    // Sizer principal
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Titre
    lblTitre = new wxStaticText(panel, wxID_ANY, 
        "ÉCOLE POLYTECHNIQUE D'ABOMEY-CALAVI\nSystème de Gestion Scolaire",
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    wxFont fontTitre = lblTitre->GetFont();
    fontTitre.SetPointSize(12);
    fontTitre.SetWeight(wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    lblTitre->SetForegroundColour(wxColour(0, 51, 102));

    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_CENTER, 20);

    // Sizer pour le formulaire
    wxBoxSizer* formSizer = new wxBoxSizer(wxVERTICAL);

    // Choix du rôle
    lblRole = new wxStaticText(panel, wxID_ANY, "Vous êtes:");
    formSizer->Add(lblRole, 0, wxLEFT | wxRIGHT | wxTOP, 10);
    
    wxArrayString roles;
    roles.Add("Administrateur");
    roles.Add("Enseignant");
    roles.Add("Étudiant");
    choixRole = new wxChoice(panel, wxID_ANY, wxDefaultPosition, 
                              wxSize(300, -1), roles);
    choixRole->SetSelection(0);
    formSizer->Add(choixRole, 0, wxALL | wxEXPAND, 10);

    // Login
    lblLogin = new wxStaticText(panel, wxID_ANY, "Identifiant:");
    formSizer->Add(lblLogin, 0, wxLEFT | wxRIGHT | wxTOP, 10);
    
    txtLogin = new wxTextCtrl(panel, wxID_ANY, "", 
                               wxDefaultPosition, wxSize(300, -1));
    formSizer->Add(txtLogin, 0, wxALL | wxEXPAND, 10);

    // Mot de passe
    lblPassword = new wxStaticText(panel, wxID_ANY, "Mot de passe:");
    formSizer->Add(lblPassword, 0, wxLEFT | wxRIGHT | wxTOP, 10);
    
    txtPassword = new wxTextCtrl(panel, wxID_ANY, "", 
                                  wxDefaultPosition, wxSize(300, -1), 
                                  wxTE_PASSWORD);
    formSizer->Add(txtPassword, 0, wxALL | wxEXPAND, 10);

    mainSizer->Add(formSizer, 0, wxALL | wxALIGN_CENTER, 20);

    // Boutons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    
    btnConnexion = new wxButton(panel, wxID_OK, "Se connecter", 
                                 wxDefaultPosition, wxSize(120, 35));
    btnConnexion->SetBackgroundColour(wxColour(0, 102, 204));
    btnConnexion->SetForegroundColour(*wxWHITE);
    
    btnQuitter = new wxButton(panel, wxID_EXIT, "Quitter", 
                               wxDefaultPosition, wxSize(120, 35));
    
    buttonSizer->Add(btnConnexion, 0, wxALL, 5);
    buttonSizer->Add(btnQuitter, 0, wxALL, 5);
    
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    panel->SetSizer(mainSizer);
    
    Centre();
    txtLogin->SetFocus();
}

void LoginFrame::OnConnexion(wxCommandEvent& event)
{
    wxString login = txtLogin->GetValue();
    wxString password = txtPassword->GetValue();
    int role = choixRole->GetSelection();

    // Validation simple
    if (login.IsEmpty() || password.IsEmpty())
    {
        wxMessageBox("Veuillez remplir tous les champs", 
                     "Erreur", wxOK | wxICON_ERROR);
        return;
    }

    // Pour l'instant, connexion factice pour tester
    wxString roleStr;
    switch(role)
    {
        case 0: roleStr = "Administrateur"; break;
        case 1: roleStr = "Enseignant"; break;
        case 2: roleStr = "Étudiant"; break;
    }

    wxString message = wxString::Format(
        "Connexion réussie!\n\nRôle: %s\nIdentifiant: %s", 
        roleStr, login);
    
    wxMessageBox(message, "Succès", wxOK | wxICON_INFORMATION);
    
    // TODO: Ouvrir la fenêtre appropriée selon le rôle
}

void LoginFrame::OnQuitter(wxCommandEvent& event)
{
    Close(true);
}

void LoginFrame::OnRoleChange(wxCommandEvent& event)
{
    // On peut adapter l'interface selon le rôle si nécessaire
}