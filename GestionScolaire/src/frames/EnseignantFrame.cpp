#include "frames/EnseignantFrame.h"
#include <wx/msgdlg.h>
#include <wx/statline.h>
#include "dialogs/SaisieNotesDialog.h"

EnseignantFrame::EnseignantFrame(const wxString& nomEnseignant)
    : wxFrame(nullptr, wxID_ANY, wxT("EPAC - Tableau de bord Enseignant"),
              wxDefaultPosition, wxSize(800, 600)),
      m_nomEnseignant(nomEnseignant)
{
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(245, 245, 245));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // En-tête
    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);
    
    lblBienvenue = new wxStaticText(panel, wxID_ANY,
        wxString::Format(wxT("Bienvenue, Pr. %s"), m_nomEnseignant));
    wxFont fontBienvenue = lblBienvenue->GetFont();
    fontBienvenue.SetPointSize(14);
    fontBienvenue.SetWeight(wxFONTWEIGHT_BOLD);
    lblBienvenue->SetFont(fontBienvenue);
    lblBienvenue->SetForegroundColour(wxColour(0, 51, 102));
    
    headerSizer->Add(lblBienvenue, 1, wxALL | wxALIGN_CENTER_VERTICAL, 15);
    
    btnDeconnexion = new wxButton(panel, wxID_ANY, wxT("Déconnexion"), 
                                   wxDefaultPosition, wxSize(120, 35));
    btnDeconnexion->Bind(wxEVT_BUTTON, &EnseignantFrame::OnDeconnexion, this);
    headerSizer->Add(btnDeconnexion, 0, wxALL | wxALIGN_CENTER_VERTICAL, 15);
    
    mainSizer->Add(headerSizer, 0, wxEXPAND);
    mainSizer->Add(new wxStaticLine(panel), 0, wxEXPAND | wxALL, 5);

    // Titre
    wxStaticText* lblTitre = new wxStaticText(panel, wxID_ANY, 
        wxT("Fonctionnalités Enseignant"));
    wxFont fontTitre = lblTitre->GetFont();
    fontTitre.SetPointSize(12);
    fontTitre.SetWeight(wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_CENTER, 15);

    // Grille de boutons (2 colonnes)
    wxGridSizer* gridSizer = new wxGridSizer(4, 2, 15, 15);

    // Bouton 1: Mes cours
    btnMesCours = new wxButton(panel, wxID_ANY, 
        wxT("Mes Cours"), wxDefaultPosition, wxSize(250, 80));
    btnMesCours->SetBackgroundColour(wxColour(52, 152, 219));
    btnMesCours->SetForegroundColour(*wxWHITE);
    btnMesCours->Bind(wxEVT_BUTTON, &EnseignantFrame::OnMesCours, this);
    gridSizer->Add(btnMesCours, 0, wxEXPAND);

    // Bouton 2: Saisir les notes
    btnSaisirNotes = new wxButton(panel, wxID_ANY, 
        wxT("Saisir les\nNotes"), wxDefaultPosition, wxSize(250, 80));
    btnSaisirNotes->SetBackgroundColour(wxColour(46, 204, 113));
    btnSaisirNotes->SetForegroundColour(*wxWHITE);
    btnSaisirNotes->Bind(wxEVT_BUTTON, &EnseignantFrame::OnSaisirNotes, this);
    gridSizer->Add(btnSaisirNotes, 0, wxEXPAND);

    // Bouton 3: Consulter les notes
    btnConsulterNotes = new wxButton(panel, wxID_ANY, 
        wxT("Consulter les\nNotes"), wxDefaultPosition, wxSize(250, 80));
    btnConsulterNotes->SetBackgroundColour(wxColour(155, 89, 182));
    btnConsulterNotes->SetForegroundColour(*wxWHITE);
    btnConsulterNotes->Bind(wxEVT_BUTTON, &EnseignantFrame::OnConsulterNotes, this);
    gridSizer->Add(btnConsulterNotes, 0, wxEXPAND);

    // Bouton 4: Enregistrer absences
    btnEnregistrerAbsences = new wxButton(panel, wxID_ANY, 
        wxT("Enregistrer\nles Absences"), wxDefaultPosition, wxSize(250, 80));
    btnEnregistrerAbsences->SetBackgroundColour(wxColour(230, 126, 34));
    btnEnregistrerAbsences->SetForegroundColour(*wxWHITE);
    btnEnregistrerAbsences->Bind(wxEVT_BUTTON, &EnseignantFrame::OnEnregistrerAbsences, this);
    gridSizer->Add(btnEnregistrerAbsences, 0, wxEXPAND);

    // Bouton 5: Consulter absences
    btnConsulterAbsences = new wxButton(panel, wxID_ANY, 
        wxT("Consulter les\nAbsences"), wxDefaultPosition, wxSize(250, 80));
    btnConsulterAbsences->SetBackgroundColour(wxColour(231, 76, 60));
    btnConsulterAbsences->SetForegroundColour(*wxWHITE);
    btnConsulterAbsences->Bind(wxEVT_BUTTON, &EnseignantFrame::OnConsulterAbsences, this);
    gridSizer->Add(btnConsulterAbsences, 0, wxEXPAND);

    // Bouton 6: Emploi du temps
    btnEmploiTemps = new wxButton(panel, wxID_ANY, 
        wxT("Mon Emploi\ndu Temps"), wxDefaultPosition, wxSize(250, 80));
    btnEmploiTemps->SetBackgroundColour(wxColour(26, 188, 156));
    btnEmploiTemps->SetForegroundColour(*wxWHITE);
    btnEmploiTemps->Bind(wxEVT_BUTTON, &EnseignantFrame::OnEmploiTemps, this);
    gridSizer->Add(btnEmploiTemps, 0, wxEXPAND);

    // Bouton 7: Statistiques
    btnStatistiquesCours = new wxButton(panel, wxID_ANY, 
        wxT("Statistiques\nde mes Cours"), wxDefaultPosition, wxSize(250, 80));
    btnStatistiquesCours->SetBackgroundColour(wxColour(52, 73, 94));
    btnStatistiquesCours->SetForegroundColour(*wxWHITE);
    btnStatistiquesCours->Bind(wxEVT_BUTTON, &EnseignantFrame::OnStatistiquesCours, this);
    gridSizer->Add(btnStatistiquesCours, 0, wxEXPAND);

    mainSizer->Add(gridSizer, 1, wxALL | wxALIGN_CENTER, 30);

    panel->SetSizer(mainSizer);
    Centre();
}

void EnseignantFrame::OnMesCours(wxCommandEvent& event)
{
    wxMessageBox(wxT("Liste de mes cours\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EnseignantFrame::OnSaisirNotes(wxCommandEvent& event)
{
    SaisieNotesDialog dialog(this);
    dialog.ShowModal();
}
void EnseignantFrame::OnConsulterNotes(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Consultation des Notes\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EnseignantFrame::OnEnregistrerAbsences(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Enregistrement des Absences\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EnseignantFrame::OnConsulterAbsences(wxCommandEvent& event)
{
    wxMessageBox(wxT("Module Consultation des Absences\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EnseignantFrame::OnEmploiTemps(wxCommandEvent& event)
{
    wxMessageBox(wxT("Mon Emploi du Temps\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EnseignantFrame::OnStatistiquesCours(wxCommandEvent& event)
{
    wxMessageBox(wxT("Statistiques de mes cours\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EnseignantFrame::OnDeconnexion(wxCommandEvent& event)
{
    if (wxMessageBox(wxT("Voulez-vous vraiment vous déconnecter?"), 
                     wxT("Confirmation"), 
                     wxYES_NO | wxICON_QUESTION) == wxYES)
    {
        Close(true);
        // TODO: Retourner à l'écran de connexion
    }
}