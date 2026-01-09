#ifndef ETUDIANTFRAME_H
#define ETUDIANTFRAME_H

#include <wx/wx.h>

class EtudiantFrame : public wxFrame
{
public:
    EtudiantFrame(const wxString& nomEtudiant, const wxString& matricule);

private:
    wxString m_nomEtudiant;
    wxString m_matricule;
    
    // Composants de l'interface
    wxStaticText* lblBienvenue;
    wxStaticText* lblMatricule;
    wxButton* btnConsulterNotes;
    wxButton* btnTelechargerBulletin;
    wxButton* btnConsulterAbsences;
    wxButton* btnJustifierAbsence;
    wxButton* btnEmploiTemps;
    wxButton* btnMesCours;
    wxButton* btnModifierContact;
    wxButton* btnDeconnexion;

    // Gestionnaires d'événements
    void OnConsulterNotes(wxCommandEvent& event);
    void OnTelechargerBulletin(wxCommandEvent& event);
    void OnConsulterAbsences(wxCommandEvent& event);
    void OnJustifierAbsence(wxCommandEvent& event);
    void OnEmploiTemps(wxCommandEvent& event);
    void OnMesCours(wxCommandEvent& event);
    void OnModifierContact(wxCommandEvent& event);
    void OnDeconnexion(wxCommandEvent& event);
};

#endif // ETUDIANTFRAME_H