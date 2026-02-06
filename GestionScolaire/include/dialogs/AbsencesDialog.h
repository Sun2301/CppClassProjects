#ifndef ABSENCESDIALOG_H
#define ABSENCESDIALOG_H

#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/checklst.h>

class AbsencesDialog : public wxDialog
{
public:
    AbsencesDialog(wxWindow* parent);

private:
    wxChoice* choixCours;
    wxDatePickerCtrl* datePicker;
    wxCheckListBox* checklistEtudiants;
    wxButton* btnEnregistrer;
    wxButton* btnAnnuler;

    void ChargerEtudiants();
    void OnEnregistrer(wxCommandEvent& event);
    void OnAnnuler(wxCommandEvent& event);
};

#endif // ABSENCESDIALOG_H
