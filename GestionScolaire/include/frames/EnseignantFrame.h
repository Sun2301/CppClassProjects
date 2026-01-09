#ifndef ENSEIGNANTFRAME_H
#define ENSEIGNANTFRAME_H

#include <wx/wx.h>

class EnseignantFrame : public wxFrame
{
public:
    EnseignantFrame(const wxString& nomEnseignant);

private:
    wxString m_nomEnseignant;
    
    // Composants de l'interface
    wxStaticText* lblBienvenue;
    wxButton* btnMesCours;
    wxButton* btnSaisirNotes;
    wxButton* btnConsulterNotes;
    wxButton* btnEnregistrerAbsences;
    wxButton* btnConsulterAbsences;
    wxButton* btnEmploiTemps;
    wxButton* btnStatistiquesCours;
    wxButton* btnDeconnexion;

    // Gestionnaires d'événements
    void OnMesCours(wxCommandEvent& event);
    void OnSaisirNotes(wxCommandEvent& event);
    void OnConsulterNotes(wxCommandEvent& event);
    void OnEnregistrerAbsences(wxCommandEvent& event);
    void OnConsulterAbsences(wxCommandEvent& event);
    void OnEmploiTemps(wxCommandEvent& event);
    void OnStatistiquesCours(wxCommandEvent& event);
    void OnDeconnexion(wxCommandEvent& event);
};

#endif // ENSEIGNANTFRAME_H