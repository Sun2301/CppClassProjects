#include "frames/EtudiantFrame.h"
#include <wx/msgdlg.h>
#include <wx/statline.h>

EtudiantFrame::EtudiantFrame(const wxString& nomEtudiant, const wxString& matricule)
    : wxFrame(nullptr, wxID_ANY, wxT("EPAC - Tableau de bord Étudiant"),
              wxDefaultPosition, wxSize(800, 600)),
      m_nomEtudiant(nomEtudiant),
      m_matricule(matricule)
{
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(245, 245, 245));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // En-tête
    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxBoxSizer* infosUserSizer = new wxBoxSizer(wxVERTICAL);
    
    lblBienvenue = new wxStaticText(panel, wxID_ANY,
        wxString::Format(wxT("Bienvenue, %s"), m_nomEtudiant));
    wxFont fontBienvenue = lblBienvenue->GetFont();
    fontBienvenue.SetPointSize(14);
    fontBienvenue.SetWeight(wxFONTWEIGHT_BOLD);
    lblBienvenue->SetFont(fontBienvenue);
    lblBienvenue->SetForegroundColour(wxColour(0, 51, 102));
    
    lblMatricule = new wxStaticText(panel, wxID_ANY,
        wxString::Format(wxT("Matricule: %s"), m_matricule));
    lblMatricule->SetForegroundColour(wxColour(100, 100, 100));
    
    infosUserSizer->Add(lblBienvenue, 0, wxBOTTOM, 5);
    infosUserSizer->Add(lblMatricule, 0);
    
    headerSizer->Add(infosUserSizer, 1, wxALL | wxALIGN_CENTER_VERTICAL, 15);
    
    btnDeconnexion = new wxButton(panel, wxID_ANY, wxT("Déconnexion"), 
                                   wxDefaultPosition, wxSize(120, 35));
    btnDeconnexion->Bind(wxEVT_BUTTON, &EtudiantFrame::OnDeconnexion, this);
    headerSizer->Add(btnDeconnexion, 0, wxALL | wxALIGN_CENTER_VERTICAL, 15);
    
    mainSizer->Add(headerSizer, 0, wxEXPAND);
    mainSizer->Add(new wxStaticLine(panel), 0, wxEXPAND | wxALL, 5);

    // Titre
    wxStaticText* lblTitre = new wxStaticText(panel, wxID_ANY, 
        wxT("Mon Espace Étudiant"));
    wxFont fontTitre = lblTitre->GetFont();
    fontTitre.SetPointSize(12);
    fontTitre.SetWeight(wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_CENTER, 15);

    // Grille de boutons (2 colonnes)
    wxGridSizer* gridSizer = new wxGridSizer(4, 2, 15, 15);

    // Bouton 1: Consulter mes notes
    btnConsulterNotes = new wxButton(panel, wxID_ANY, 
        wxT("Consulter mes\nNotes"), wxDefaultPosition, wxSize(250, 80));
    btnConsulterNotes->SetBackgroundColour(wxColour(52, 152, 219));
    btnConsulterNotes->SetForegroundColour(*wxWHITE);
    btnConsulterNotes->Bind(wxEVT_BUTTON, &EtudiantFrame::OnConsulterNotes, this);
    gridSizer->Add(btnConsulterNotes, 0, wxEXPAND);

    // Bouton 2: Télécharger bulletin
    btnTelechargerBulletin = new wxButton(panel, wxID_ANY, 
        wxT("Télécharger mon\nBulletin"), wxDefaultPosition, wxSize(250, 80));
    btnTelechargerBulletin->SetBackgroundColour(wxColour(46, 204, 113));
    btnTelechargerBulletin->SetForegroundColour(*wxWHITE);
    btnTelechargerBulletin->Bind(wxEVT_BUTTON, &EtudiantFrame::OnTelechargerBulletin, this);
    gridSizer->Add(btnTelechargerBulletin, 0, wxEXPAND);

    // Bouton 3: Consulter absences
    btnConsulterAbsences = new wxButton(panel, wxID_ANY, 
        wxT("Consulter mes\nAbsences"), wxDefaultPosition, wxSize(250, 80));
    btnConsulterAbsences->SetBackgroundColour(wxColour(155, 89, 182));
    btnConsulterAbsences->SetForegroundColour(*wxWHITE);
    btnConsulterAbsences->Bind(wxEVT_BUTTON, &EtudiantFrame::OnConsulterAbsences, this);
    gridSizer->Add(btnConsulterAbsences, 0, wxEXPAND);

    // Bouton 4: Justifier une absence
    btnJustifierAbsence = new wxButton(panel, wxID_ANY, 
        wxT("Justifier une\nAbsence"), wxDefaultPosition, wxSize(250, 80));
    btnJustifierAbsence->SetBackgroundColour(wxColour(230, 126, 34));
    btnJustifierAbsence->SetForegroundColour(*wxWHITE);
    btnJustifierAbsence->Bind(wxEVT_BUTTON, &EtudiantFrame::OnJustifierAbsence, this);
    gridSizer->Add(btnJustifierAbsence, 0, wxEXPAND);

    // Bouton 5: Mon emploi du temps
    btnEmploiTemps = new wxButton(panel, wxID_ANY, 
        wxT("Mon Emploi\ndu Temps"), wxDefaultPosition, wxSize(250, 80));
    btnEmploiTemps->SetBackgroundColour(wxColour(231, 76, 60));
    btnEmploiTemps->SetForegroundColour(*wxWHITE);
    btnEmploiTemps->Bind(wxEVT_BUTTON, &EtudiantFrame::OnEmploiTemps, this);
    gridSizer->Add(btnEmploiTemps, 0, wxEXPAND);

    // Bouton 6: Mes cours
    btnMesCours = new wxButton(panel, wxID_ANY, 
        wxT("Mes Cours"), wxDefaultPosition, wxSize(250, 80));
    btnMesCours->SetBackgroundColour(wxColour(26, 188, 156));
    btnMesCours->SetForegroundColour(*wxWHITE);
    btnMesCours->Bind(wxEVT_BUTTON, &EtudiantFrame::OnMesCours, this);
    gridSizer->Add(btnMesCours, 0, wxEXPAND);

    // Bouton 7: Modifier contact
    btnModifierContact = new wxButton(panel, wxID_ANY, 
        wxT("Modifier mes\nCoordonnées"), wxDefaultPosition, wxSize(250, 80));
    btnModifierContact->SetBackgroundColour(wxColour(52, 73, 94));
    btnModifierContact->SetForegroundColour(*wxWHITE);
    btnModifierContact->Bind(wxEVT_BUTTON, &EtudiantFrame::OnModifierContact, this);
    gridSizer->Add(btnModifierContact, 0, wxEXPAND);

    mainSizer->Add(gridSizer, 1, wxALL | wxALIGN_CENTER, 30);

    panel->SetSizer(mainSizer);
    Centre();
}

void EtudiantFrame::OnConsulterNotes(wxCommandEvent& event)
{
    wxMessageBox(wxT("Consultation de mes notes en temps réel\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EtudiantFrame::OnTelechargerBulletin(wxCommandEvent& event)
{
    wxMessageBox(wxT("Téléchargement du bulletin\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EtudiantFrame::OnConsulterAbsences(wxCommandEvent& event)
{
    wxMessageBox(wxT("Consultation de mes absences\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EtudiantFrame::OnJustifierAbsence(wxCommandEvent& event)
{
    wxMessageBox(wxT("Justification d'absence\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EtudiantFrame::OnEmploiTemps(wxCommandEvent& event)
{
    wxMessageBox(wxT("Mon emploi du temps\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EtudiantFrame::OnMesCours(wxCommandEvent& event)
{
    wxMessageBox(wxT("Liste de mes cours\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EtudiantFrame::OnModifierContact(wxCommandEvent& event)
{
    wxMessageBox(wxT("Modification de mes coordonnées\n(À implémenter)"), 
                 wxT("Info"), wxOK | wxICON_INFORMATION);
}

void EtudiantFrame::OnDeconnexion(wxCommandEvent& event)
{
    if (wxMessageBox(wxT("Voulez-vous vraiment vous déconnecter?"), 
                     wxT("Confirmation"), 
                     wxYES_NO | wxICON_QUESTION) == wxYES)
    {
        Close(true);
        // TODO: Retourner à l'écran de connexion
    }
}