#include "frames/LoginFrame.h"
#include <wx/msgdlg.h>
#include "frames/AdminFrame.h"
#include "frames/EnseignantFrame.h"
#include "frames/EtudiantFrame.h"

// Table des événements
wxBEGIN_EVENT_TABLE(LoginFrame, wxFrame)
    EVT_BUTTON(wxID_OK, LoginFrame::OnConnexion)
    EVT_BUTTON(wxID_EXIT, LoginFrame::OnQuitter)
    EVT_CHOICE(wxID_ANY, LoginFrame::OnRoleChange)
wxEND_EVENT_TABLE()

LoginFrame::LoginFrame()
    : wxFrame(nullptr, wxID_ANY, wxT("EPAC - Système de Gestion Scolaire"), 
              wxDefaultPosition, wxSize(500, 450))
{
    // Panneau principal
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(240, 240, 240));

    // Sizer principal
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Titre
    lblTitre = new wxStaticText(panel, wxID_ANY, 
        wxT("ÉCOLE POLYTECHNIQUE D'ABOMEY-CALAVI\nSystème de Gestion Scolaire"),
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
    lblRole = new wxStaticText(panel, wxID_ANY, wxT("Vous êtes:"));
    formSizer->Add(lblRole, 0, wxLEFT | wxRIGHT | wxTOP, 10);
    
    wxArrayString roles;
    roles.Add(wxT("Administrateur"));
    roles.Add(wxT("Enseignant"));
    roles.Add(wxT("Étudiant"));
    choixRole = new wxChoice(panel, wxID_ANY, wxDefaultPosition, 
                              wxSize(300, -1), roles);
    choixRole->SetSelection(0);
    formSizer->Add(choixRole, 0, wxALL | wxEXPAND, 10);

    // Login
    lblLogin = new wxStaticText(panel, wxID_ANY, wxT("Identifiant:"));
    formSizer->Add(lblLogin, 0, wxLEFT | wxRIGHT | wxTOP, 10);
    
    txtLogin = new wxTextCtrl(panel, wxID_ANY, wxT(""), 
                               wxDefaultPosition, wxSize(300, -1));
    formSizer->Add(txtLogin, 0, wxALL | wxEXPAND, 10);

    // Mot de passe
    lblPassword = new wxStaticText(panel, wxID_ANY, wxT("Mot de passe:"));
    formSizer->Add(lblPassword, 0, wxLEFT | wxRIGHT | wxTOP, 10);
    
    txtPassword = new wxTextCtrl(panel, wxID_ANY, wxT(""), 
                                  wxDefaultPosition, wxSize(300, -1), 
                                  wxTE_PASSWORD);
    formSizer->Add(txtPassword, 0, wxALL | wxEXPAND, 10);

    // Case à cocher pour afficher/masquer le mot de passe
    wxCheckBox* chkShowPassword = new wxCheckBox(panel, wxID_ANY, 
                                                  wxT("Afficher le mot de passe"));
    formSizer->Add(chkShowPassword, 0, wxLEFT | wxRIGHT, 10);
    
    // Lier l'événement pour afficher/masquer le mot de passe
    chkShowPassword->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& event) {
        if (event.IsChecked()) {
            txtPassword->SetWindowStyle(wxTE_LEFT);
        } else {
            txtPassword->SetWindowStyle(wxTE_PASSWORD);
        }
        txtPassword->Refresh();
    });

    mainSizer->Add(formSizer, 0, wxALL | wxALIGN_CENTER, 20);

    // Boutons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    
    btnConnexion = new wxButton(panel, wxID_OK, wxT("Se connecter"), 
                                 wxDefaultPosition, wxSize(120, 35));
    btnConnexion->SetBackgroundColour(wxColour(0, 102, 204));
    btnConnexion->SetForegroundColour(*wxWHITE);
    
    btnQuitter = new wxButton(panel, wxID_EXIT, wxT("Quitter"), 
                               wxDefaultPosition, wxSize(120, 35));
    
    buttonSizer->Add(btnConnexion, 0, wxALL, 5);
    buttonSizer->Add(btnQuitter, 0, wxALL, 5);
    
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    panel->SetSizer(mainSizer);
    
    Centre();
    txtLogin->SetFocus();
}void LoginFrame::OnConnexion(wxCommandEvent& event)
{
    wxString login = txtLogin->GetValue();
    wxString password = txtPassword->GetValue();
    int role = choixRole->GetSelection();

    // Validation simple
    if (login.IsEmpty() || password.IsEmpty())
    {
        wxMessageBox(wxT("Veuillez remplir tous les champs"), 
                     wxT("Erreur"), wxOK | wxICON_ERROR);
        return;
    }

    // Connexion réussie - Ouvrir le tableau de bord approprié
    wxFrame* dashboard = nullptr;
    
    switch(role)
    {
        case 0: // Administrateur
            dashboard = new AdminFrame(login);
            break;
        case 1: // Enseignant
            dashboard = new EnseignantFrame(login);
            break;
        case 2: // Étudiant
            dashboard = new EtudiantFrame(login, wxT("L3-GE-2024-001"));
            break;
    }
    
    if (dashboard)
    {
        dashboard->Show(true);
        this->Hide();
    }
}
void LoginFrame::OnQuitter(wxCommandEvent& event)
{
    Close(true);
}

void LoginFrame::OnRoleChange(wxCommandEvent& event)
{
    // On peut adapter l'interface selon le rôle si nécessaire
}

