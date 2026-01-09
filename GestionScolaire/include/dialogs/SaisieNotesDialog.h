#ifndef SAISIENOTESDIALOG_H
#define SAISIENOTESDIALOG_H

#include <wx/wx.h>
#include <wx/grid.h>

class SaisieNotesDialog : public wxDialog
{
public:
    SaisieNotesDialog(wxWindow* parent);

private:
   // Composants
    wxChoice* choixCours;
    wxGrid* gridNotes;
    wxButton* btnSauvegarder;      // Nouveau: Sauvegarder brouillon
    wxButton* btnEnregistrer;      // Enregistrer et soumettre
    wxButton* btnAnnuler;
    wxStaticText* lblInfo;
    wxStaticText* lblStatut;       // Nouveau: Afficher le statut

    // Données simulées (à remplacer par base de données)
    wxArrayString listeCours;
    
    // Gestionnaires d'événements
    void OnCoursChange(wxCommandEvent& event);
    void OnEnregistrer(wxCommandEvent& event);
    void OnAnnuler(wxCommandEvent& event);
    void OnCellChange(wxGridEvent& event);
    void OnSauvegarder(wxCommandEvent& event);
    
    // Méthodes utilitaires
    void ChargerEtudiants();
    void CalculerMoyenne(int row);
    wxString AttribuerMention(double moyenne);
};

#endif // SAISIENOTESDIALOG_H