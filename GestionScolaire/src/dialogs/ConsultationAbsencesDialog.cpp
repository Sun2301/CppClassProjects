#include "dialogs/ConsultationAbsencesDialog.h"
#include "database/Database.h"
#include <wx/msgdlg.h>
#include <wx/textdlg.h>

ConsultationAbsencesDialog::ConsultationAbsencesDialog(wxWindow* parent, const wxString& matricule)
    : wxDialog(parent, wxID_ANY, wxT("Mes absences"),
               wxDefaultPosition, wxSize(750, 450)),
      m_matricule(matricule)
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblTitre = new wxStaticText(panel, wxID_ANY, wxT("Mes absences"));
    wxFont fontTitre = lblTitre->GetFont();
    fontTitre.SetPointSize(12);
    fontTitre.SetWeight(wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_CENTER, 10);

    listAbsences = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(-1, 250),
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
    listAbsences->InsertColumn(0, wxT("Date"), wxLIST_FORMAT_LEFT, 120);
    listAbsences->InsertColumn(1, wxT("Cours"), wxLIST_FORMAT_LEFT, 200);
    listAbsences->InsertColumn(2, wxT("Statut"), wxLIST_FORMAT_LEFT, 160);
    listAbsences->InsertColumn(3, wxT("Justification"), wxLIST_FORMAT_LEFT, 220);

    mainSizer->Add(listAbsences, 1, wxALL | wxEXPAND, 10);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

    btnJustifier = new wxButton(panel, wxID_ANY, wxT("Justifier"), wxDefaultPosition, wxSize(120, 35));
    btnJustifier->SetBackgroundColour(wxColour(230, 126, 34));
    btnJustifier->SetForegroundColour(*wxWHITE);
    btnJustifier->Bind(wxEVT_BUTTON, &ConsultationAbsencesDialog::OnJustifier, this);

    btnRafraichir = new wxButton(panel, wxID_ANY, wxT("Rafraichir"), wxDefaultPosition, wxSize(120, 35));
    btnRafraichir->Bind(wxEVT_BUTTON, &ConsultationAbsencesDialog::OnRafraichir, this);

    btnFermer = new wxButton(panel, wxID_CANCEL, wxT("Fermer"), wxDefaultPosition, wxSize(120, 35));
    btnFermer->Bind(wxEVT_BUTTON, &ConsultationAbsencesDialog::OnFermer, this);

    btnSizer->Add(btnJustifier, 0, wxALL, 5);
    btnSizer->Add(btnRafraichir, 0, wxALL, 5);
    btnSizer->Add(btnFermer, 0, wxALL, 5);

    mainSizer->Add(btnSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    panel->SetSizer(mainSizer);

    ChargerAbsences();
    Centre();
}

void ConsultationAbsencesDialog::ChargerAbsences()
{
    listAbsences->DeleteAllItems();

    auto absences = Database::GetAbsencesByMatricule(m_matricule);
    long index = 0;
    for (const auto& a : absences)
    {
        long item = listAbsences->InsertItem(index, a.date);
        listAbsences->SetItem(item, 1, a.cours);
        listAbsences->SetItem(item, 2, a.statut);
        listAbsences->SetItem(item, 3, a.justification.IsEmpty() ? wxT("-") : a.justification);
        listAbsences->SetItemData(item, static_cast<long>(a.id));
        index++;
    }
}

void ConsultationAbsencesDialog::OnJustifier(wxCommandEvent& event)
{
    long selected = listAbsences->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selected == -1)
    {
        wxMessageBox(wxT("Selectionnez une absence."), wxT("Info"), wxOK | wxICON_INFORMATION);
        return;
    }

    long id = listAbsences->GetItemData(selected);

    wxTextEntryDialog dlg(this, wxT("Entrez votre justification:"), wxT("Justification d'absence"));
    if (dlg.ShowModal() == wxID_OK)
    {
        wxString justification = dlg.GetValue();
        if (justification.IsEmpty())
        {
            wxMessageBox(wxT("La justification ne peut pas etre vide."), wxT("Erreur"), wxOK | wxICON_ERROR);
            return;
        }

        if (Database::JustifyAbsence(static_cast<int>(id), justification))
        {
            wxMessageBox(wxT("Justification envoyee."), wxT("Succes"), wxOK | wxICON_INFORMATION);
            ChargerAbsences();
        }
    }
}

void ConsultationAbsencesDialog::OnRafraichir(wxCommandEvent& event)
{
    ChargerAbsences();
}

void ConsultationAbsencesDialog::OnFermer(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
