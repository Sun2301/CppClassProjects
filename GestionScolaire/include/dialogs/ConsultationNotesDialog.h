#ifndef CONSULTATIONNOTESDIALOG_H
#define CONSULTATIONNOTESDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>

class ConsultationNotesDialog : public wxDialog
{
public:
    ConsultationNotesDialog(wxWindow* parent, const wxString& matricule);

private:
    wxString m_matricule;
    wxListCtrl* listNotes;
    wxButton* btnRafraichir;
    wxButton* btnFermer;

    void ChargerNotes();
    void OnRafraichir(wxCommandEvent& event);
    void OnFermer(wxCommandEvent& event);
};

#endif // CONSULTATIONNOTESDIALOG_H
