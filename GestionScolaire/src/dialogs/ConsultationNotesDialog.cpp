#include "dialogs/ConsultationNotesDialog.h"
#include "models/Note.h"
#include <wx/msgdlg.h>

ConsultationNotesDialog::ConsultationNotesDialog(wxWindow* parent, const wxString& matricule)
    : wxDialog(parent, wxID_ANY, wxT("Mes notes"),
               wxDefaultPosition, wxSize(800, 450)),
      m_matricule(matricule)
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblTitre = new wxStaticText(panel, wxID_ANY, wxT("Consultation des notes"));
    wxFont fontTitre = lblTitre->GetFont();
    fontTitre.SetPointSize(12);
    fontTitre.SetWeight(wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_CENTER, 10);

    listNotes = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(-1, 260),
                              wxLC_REPORT | wxLC_SINGLE_SEL);
    listNotes->InsertColumn(0, wxT("Cours"), wxLIST_FORMAT_LEFT, 220);
    listNotes->InsertColumn(1, wxT("CC"), wxLIST_FORMAT_LEFT, 70);
    listNotes->InsertColumn(2, wxT("TP"), wxLIST_FORMAT_LEFT, 70);
    listNotes->InsertColumn(3, wxT("Examen"), wxLIST_FORMAT_LEFT, 80);
    listNotes->InsertColumn(4, wxT("Moyenne"), wxLIST_FORMAT_LEFT, 90);
    listNotes->InsertColumn(5, wxT("Statut"), wxLIST_FORMAT_LEFT, 120);
    listNotes->InsertColumn(6, wxT("Derniere maj"), wxLIST_FORMAT_LEFT, 140);
    listNotes->InsertColumn(7, wxT("Validation"), wxLIST_FORMAT_LEFT, 140);
    listNotes->InsertColumn(8, wxT("Commentaire admin"), wxLIST_FORMAT_LEFT, 220);

    mainSizer->Add(listNotes, 1, wxALL | wxEXPAND, 10);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

    btnRafraichir = new wxButton(panel, wxID_ANY, wxT("Rafraichir"), wxDefaultPosition, wxSize(120, 35));
    btnRafraichir->Bind(wxEVT_BUTTON, &ConsultationNotesDialog::OnRafraichir, this);

    btnFermer = new wxButton(panel, wxID_CANCEL, wxT("Fermer"), wxDefaultPosition, wxSize(120, 35));
    btnFermer->Bind(wxEVT_BUTTON, &ConsultationNotesDialog::OnFermer, this);

    btnSizer->Add(btnRafraichir, 0, wxALL, 5);
    btnSizer->Add(btnFermer, 0, wxALL, 5);

    mainSizer->Add(btnSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    panel->SetSizer(mainSizer);

    ChargerNotes();
    Centre();
}

void ConsultationNotesDialog::ChargerNotes()
{
    listNotes->DeleteAllItems();

    auto notes = Note::getByMatricule(std::string(m_matricule.ToUTF8()));
    long index = 0;
    for (const auto& n : notes)
    {
        wxString cours = wxString::FromUTF8(n.cours.c_str());
        wxString statut = wxString::FromUTF8(n.statut.c_str());
        wxString updatedAt = wxString::FromUTF8(n.updatedAt.c_str());
        wxString validationAt = wxString::FromUTF8(n.validationAt.c_str());
        wxString adminComment = wxString::FromUTF8(n.adminComment.c_str());

        long item = listNotes->InsertItem(index, cours);
        listNotes->SetItem(item, 1, n.hasCC ? wxString::Format(wxT("%.2f"), n.cc) : wxT("-"));
        listNotes->SetItem(item, 2, n.hasTP ? wxString::Format(wxT("%.2f"), n.tp) : wxT("-"));
        listNotes->SetItem(item, 3, n.hasExamen ? wxString::Format(wxT("%.2f"), n.examen) : wxT("-"));
        listNotes->SetItem(item, 4, (n.hasCC && n.hasTP && n.hasExamen) ? wxString::Format(wxT("%.2f"), n.moyenne) : wxT("-"));
        listNotes->SetItem(item, 5, statut);
        listNotes->SetItem(item, 6, updatedAt.IsEmpty() ? wxT("-") : updatedAt);
        listNotes->SetItem(item, 7, validationAt.IsEmpty() ? wxT("-") : validationAt);
        listNotes->SetItem(item, 8, adminComment.IsEmpty() ? wxT("-") : adminComment);
        index++;
    }

    if (index == 0)
    {
        wxMessageBox(wxT("Aucune note soumise pour le moment."), wxT("Info"), wxOK | wxICON_INFORMATION);
    }
}

void ConsultationNotesDialog::OnRafraichir(wxCommandEvent& event)
{
    ChargerNotes();
}

void ConsultationNotesDialog::OnFermer(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
