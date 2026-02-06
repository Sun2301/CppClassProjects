#ifndef VALIDATIONNOTESDIALOG_H
#define VALIDATIONNOTESDIALOG_H

#include <wx/wx.h>
#include <wx/dataview.h>
#include <vector>
#include "database/Database.h"

class ValidationNotesDialog : public wxDialog
{
public:
    ValidationNotesDialog(wxWindow* parent);

private:
    wxChoice* choixCours;
    wxChoice* choixStatut;
    wxDataViewListCtrl* listNotes;
    wxButton* btnValider;
    wxButton* btnRejeter;
    wxButton* btnRafraichir;
    wxButton* btnFermer;
    std::vector<NoteRecord> m_currentNotes;

    void ChargerCours();
    void ChargerNotes();
    void OnCoursChange(wxCommandEvent& event);
    void OnStatutChange(wxCommandEvent& event);
    void OnValider(wxCommandEvent& event);
    void OnRejeter(wxCommandEvent& event);
    void OnRafraichir(wxCommandEvent& event);
    void OnFermer(wxCommandEvent& event);
};

#endif // VALIDATIONNOTESDIALOG_H
