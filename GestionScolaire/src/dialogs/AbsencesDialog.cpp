#include "dialogs/AbsencesDialog.h"
#include "models/Absence.h"
#include "models/Etudiant.h"
#include <wx/msgdlg.h>

AbsencesDialog::AbsencesDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, wxT("Enregistrement des absences"),
               wxDefaultPosition, wxSize(700, 500))
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblTitre = new wxStaticText(panel, wxID_ANY,
        wxT("Enregistrer les absences"));
    wxFont fontTitre = lblTitre->GetFont();
    fontTitre.SetPointSize(12);
    fontTitre.SetWeight(wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_CENTER, 10);

    // Ligne: cours + date
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* lblCours = new wxStaticText(panel, wxID_ANY, wxT("Cours:"));
    topSizer->Add(lblCours, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxArrayString cours;
    cours.Add(wxT("INF301 - POO"));
    cours.Add(wxT("INF302 - BD"));
    cours.Add(wxT("ELEC201 - EN"));
    cours.Add(wxT("MATH301 - AN"));

    choixCours = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(260, -1), cours);
    choixCours->SetSelection(0);
    topSizer->Add(choixCours, 0, wxALL, 5);

    wxStaticText* lblDate = new wxStaticText(panel, wxID_ANY, wxT("Date:"));
    topSizer->Add(lblDate, 0, wxLEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);

    datePicker = new wxDatePickerCtrl(panel, wxID_ANY);
    topSizer->Add(datePicker, 0, wxALL, 5);

    mainSizer->Add(topSizer, 0, wxALL | wxEXPAND, 5);

    wxStaticText* lblListe = new wxStaticText(panel, wxID_ANY,
        wxT("Cochez les etudiants absents:"));
    mainSizer->Add(lblListe, 0, wxLEFT | wxRIGHT | wxTOP, 10);

    checklistEtudiants = new wxCheckListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(-1, 250));
    mainSizer->Add(checklistEtudiants, 1, wxALL | wxEXPAND, 10);

    ChargerEtudiants();

    // Boutons
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

    btnEnregistrer = new wxButton(panel, wxID_OK, wxT("Enregistrer"), wxDefaultPosition, wxSize(120, 35));
    btnEnregistrer->SetBackgroundColour(wxColour(46, 204, 113));
    btnEnregistrer->SetForegroundColour(*wxWHITE);
    btnEnregistrer->Bind(wxEVT_BUTTON, &AbsencesDialog::OnEnregistrer, this);

    btnAnnuler = new wxButton(panel, wxID_CANCEL, wxT("Annuler"), wxDefaultPosition, wxSize(120, 35));
    btnAnnuler->Bind(wxEVT_BUTTON, &AbsencesDialog::OnAnnuler, this);

    btnSizer->Add(btnEnregistrer, 0, wxALL, 5);
    btnSizer->Add(btnAnnuler, 0, wxALL, 5);

    mainSizer->Add(btnSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    panel->SetSizer(mainSizer);
    Centre();
}

void AbsencesDialog::ChargerEtudiants()
{
    checklistEtudiants->Clear();

    const auto students = Etudiant::getAll();
    for (const auto& s : students)
    {
        wxString matricule = wxString::FromUTF8(s.matricule.c_str());
        wxString nom = wxString::FromUTF8(s.nom.c_str());
        wxString prenom = wxString::FromUTF8(s.prenom.c_str());
        wxString label = wxString::Format(wxT("%s - %s %s"), matricule, nom, prenom);
        checklistEtudiants->Append(label);
    }
}

void AbsencesDialog::OnEnregistrer(wxCommandEvent& event)
{
    const auto students = Etudiant::getAll();

    wxString cours = choixCours->GetStringSelection();
    wxDateTime date = datePicker->GetValue();
    wxString dateStr = date.FormatISODate();

    std::vector<size_t> indices;
    for (unsigned int i = 0; i < checklistEtudiants->GetCount(); i++)
    {
        if (checklistEtudiants->IsChecked(i))
        {
            indices.push_back(i);
        }
    }

    int checked = Absence::enregistrerAbsences(
        students,
        indices,
        std::string(cours.ToUTF8()),
        std::string(dateStr.ToUTF8()));

    wxString msg = wxString::Format(wxT("Absences enregistrees: %d"), checked);
    wxMessageBox(msg, wxT("Succes"), wxOK | wxICON_INFORMATION);

    EndModal(wxID_OK);
}

void AbsencesDialog::OnAnnuler(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
