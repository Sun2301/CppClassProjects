#ifndef ADMINFRAME_H
#define ADMINFRAME_H

#include <wx/wx.h>

class AdminFrame : public wxFrame
{
public:
    AdminFrame(const wxString& nomAdmin);

private:
    wxString m_nomAdmin;
    
    // Composants de l'interface
    wxStaticText* lblBienvenue;
    wxButton* btnGestionEtudiants;
    wxButton* btnGestionEnseignants;
    wxButton* btnGestionCours;
    wxButton* btnValiderInscriptions;
    wxButton* btnValiderNotes;
    wxButton* btnCreerEmploiTemps;
    wxButton* btnStatistiques;
    wxButton* btnDeconnexion;

    // Gestionnaires d'événements
    void OnGestionEtudiants(wxCommandEvent& event);
    void OnGestionEnseignants(wxCommandEvent& event);
    void OnGestionCours(wxCommandEvent& event);
    void OnValiderInscriptions(wxCommandEvent& event);
    void OnValiderNotes(wxCommandEvent& event);
    void OnCreerEmploiTemps(wxCommandEvent& event);
    void OnStatistiques(wxCommandEvent& event);
    void OnDeconnexion(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // ADMINFRAME_H