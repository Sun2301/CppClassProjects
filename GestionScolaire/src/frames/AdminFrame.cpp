#include "frames/AdminFrame.h"
#include <wx/statline.h>
#include <wx/msgdlg.h>

wxBEGIN_EVENT_TABLE(AdminFrame, wxFrame)
    EVT_BUTTON(wxID_ANY, AdminFrame::OnGestionEtudiants)
wxEND_EVENT_TABLE()

AdminFrame::AdminFrame(const wxString& nomAdmin)
    : wxFrame(nullptr, wxID_ANY, wxT("EPAC - Tableau de bord Administrateur"),
              wxDefaultPosition, wxSize(800, 600)),
      m_nomAdmin(nomAdmin)
{
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(245, 245, 245));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // En-tête
    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);
    
    lblBienvenue = new wxStaticText(panel, wxID_ANY,
        wxString::Format(wxT("Bienvenue, %s"), m_nomAdmin));
    wxFont fontBienvenue = lblBienvenue->GetFont();
    fontBienvenue.SetPointSize(14);
    fontBienvenue.SetWeight(wxFONTWEIGHT_BOLD);
    lblBienvenue->SetFont(fontBienvenue);
    lblBienvenue->SetForegroundColour(wxColour(0, 51, 102));
    
    headerSizer->Add(lblBienvenue, 1, wxALL | wxALIGN_CENTER_VERTICAL, 15);
    
    btnDeconnexion = new wxButton(panel, wxID_ANY, wxT("Déconnexion"), 
                                   wxDefaultPosition, wxSize(120, 35));
    btnDeconnexion->Bind(wxEVT_BUTTON, &AdminFrame::OnDeconnexion, this);
    headerSizer->Add(btnDeconnexion, 0, wxALL | wxALIGN_CENTER_VERTICAL, 15);
    
    mainSizer->Add(headerSizer, 0, wxEXPAND);
    mainSizer->Add(new wxStaticLine(panel), 0, wxEXPAND | wxALL, 5);

    // Titre des fonctionnalités
    wxStaticText* lblTitre = new wxStaticText(panel, wxID_ANY, 
        wxT("Fonctionnalités Administrateur"));
    wxFont fontTitre = lblTitre->GetFont();
    fontTitre.SetPointSize(12);
    fontTitre.SetWeight(wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_CENTER, 15);

    // Grille de boutons (2 colonnes)
    wxGridSizer* gridSizer = new wxGridSizer(4, 2, 15, 15);

    // Bouton 1: Gestion des étudiants
    btnGestionEtudiants = new wxButton(panel, wxID_ANY, 
        wxT("Gestion des\nÉtudiants"), wxDefaultPosition, wxSize(250, 80));
    btnGestionEtudiants->SetBackgroundColour(wxColour(52, 152, 219));
    btnGestionEtudiants->SetForegroundColour(*wxWHITE);
    btnGestionEtudiants->Bind(wxEVT_BUTTON, &AdminFrame::OnGestionEtudiants, this);
    gridSizer->Add(btnGestionEtudiants, 0, wxEXPAND);

    // Bouton 2: Gestion des enseignants
    btnGestionEnseignants = new wxButton(panel, wxID_ANY, 
        wxT("Gestion des\nEnseignants"), wxDefaultPosition, wxSize(250, 80));
    btnGestionEnseignants->SetBackgroundColour(wxColour(46, 204, 113));
    btnGestionEnseignants->SetForegroundColour(*wxWHITE);
    btnGestionEnseignants->Bind(wxEVT_BUTTON, &AdminFrame::OnGestionEnseignants, this);
    gridSizer->Add(btnGestionEnseignants, 0, wxEXPAND);

    // Bouton 3: Gestion des cours
    btnGestionCours = new wxButton(panel, wxID_ANY, 
        wxT("Gestion des\nCours"), wxDefaultPosition, wxSize(250, 80));
    btnGestionCours->SetBackgroundColour(wxColour(155, 89, 182));
    btnGestionCours->SetForegroundColour(*wxWHITE);
    btnGestionCours->Bind(wxEVT_BUTTON, &AdminFrame::OnGestionCours, this);
    gridSizer->Add(btnGestionCours, 0, wxEXPAND);

    // Bouton 4: Valider inscriptions
    btnValiderInscriptions = new wxButton(panel, wxID_ANY, 
        wxT("Valider les\nInscriptions"), wxDefaultPosition, wxSize(250, 80));
    btnValiderInscriptions->SetBackgroundColour(wxColour(230, 126, 34));
    btnValiderInscriptions->SetForegroundColour(*wxWHITE);
    btnValiderInscriptions->Bind(wxEVT_BUTTON, &AdminFrame::OnValiderInscriptions, this);
    gridSizer->Add(btnValiderInscriptions, 0, wxEXPAND);

    // Bouton 5: Valider les notes
    btnValiderNotes = new wxButton(panel, wxID_ANY, 
        wxT("Valider les\nNotes"), wxDefaultPosition, wxSize(250, 80));
    btnValiderNotes->SetBackgroundColour(wxColour(231, 76, 60));
    btnValiderNotes->SetForegroundColour(*wxWHITE);
    btnValiderNotes->Bind(wxEVT_BUTTON, &AdminFrame::OnValiderNotes, this);
    gridSizer->Add(btnValiderNotes, 0, wxEXPAND);

    // Bouton 6: Créer emploi du temps
    btnCreerEmploiTemps = new wxButton(panel, wxID_ANY, 
        wxT("Créer Emploi\ndu Temps"), wxDefaultPosition, wxSize(250, 80));
    btnCreerEmploiTemps->SetBackgroundColour(wxColour(26, 188, 156));
    btnCreerEmploiTemps->SetForegroundColour(*wxWHITE);
    btnCreerEmploiTemps->Bind(wxEVT_BUTTON, &AdminFrame::OnCreerEmploiTemps, this);
    gridSizer->Add(btnCreerEmploiTemps, 0, wxEXPAND);

    // Bouton 7: Statistiques
    btnStatistiques = new wxButton(panel, wxID_ANY, 
        wxT("Statistiques\net Rapports"), wxDefaultPosition, wxSize(250, 80));
    btnStatistiques->SetBackgroundColour(wxColour(52, 73, 94));
    btnStatistiques->SetForegroundColour(*wxWHITE);
    btnStatistiques->Bind(wxEVT_BUTTON, &AdminFrame::OnStatistiques, this);
    gridSizer->Add(btnStatistiques, 0, wxEXPAND);

    mainSizer->Add(gridSizer, 1, wxALL | wxALIGN_CENTER, 30);

    panel->SetSizer(mainSizer);
    Centre();
}

void AdminFrame::OnGestionEtudiants(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Gestion des Étudiants\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnGestionEnseignants(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Gestion des Enseignants\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnGestionCours(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Gestion des Cours\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnValiderInscriptions(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Validation des Inscriptions\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnValiderNotes(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Validation des Notes\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnCreerEmploiTemps(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Création Emploi du Temps\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnStatistiques(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Statistiques et Rapports\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnDeconnexion(wxCommandEvent& event)
{
    if (wxMessageBox(wxT("Voulez-vous vraiment vous déconnecter?"), 
                     wxT("Confirmation"), 
                     wxYES_NO | wxICON_QUESTION) == wxYES)
    {
        Close(true);
        // TODO: Retourner à l'écran de connexion
    }
}