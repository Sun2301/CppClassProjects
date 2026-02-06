#ifndef CONSULTATIONABSENCESDIALOG_H
#define CONSULTATIONABSENCESDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>

class ConsultationAbsencesDialog : public wxDialog
{
public:
    ConsultationAbsencesDialog(wxWindow* parent, const wxString& matricule);

private:
    wxString m_matricule;
    wxListCtrl* listAbsences;
    wxButton* btnJustifier;
    wxButton* btnFermer;
    wxButton* btnRafraichir;

    void ChargerAbsences();
    void OnJustifier(wxCommandEvent& event);
    void OnRafraichir(wxCommandEvent& event);
    void OnFermer(wxCommandEvent& event);
};

#endif // CONSULTATIONABSENCESDIALOG_H
