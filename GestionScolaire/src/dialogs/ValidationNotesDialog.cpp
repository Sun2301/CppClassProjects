#include "dialogs/ValidationNotesDialog.h"
#include <wx/msgdlg.h>
#include <wx/textdlg.h>

ValidationNotesDialog::ValidationNotesDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, wxT("Validation des notes"),
               wxDefaultPosition, wxSize(900, 500))
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblTitre = new wxStaticText(panel, wxID_ANY, wxT("Notes a valider"));
    wxFont fontTitre = lblTitre->GetFont();
    fontTitre.SetPointSize(12);
    fontTitre.SetWeight(wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_CENTER, 10);

    // Choix du cours + filtre statut
    wxBoxSizer* filtreSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* lblCours = new wxStaticText(panel, wxID_ANY, wxT("Cours:"));
    filtreSizer->Add(lblCours, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    choixCours = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(320, -1));
    filtreSizer->Add(choixCours, 0, wxALL, 5);

    wxStaticText* lblStatut = new wxStaticText(panel, wxID_ANY, wxT("Statut:"));
    filtreSizer->Add(lblStatut, 0, wxLEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);

    wxArrayString statuts;
    statuts.Add(wxT("Soumise"));
    statuts.Add(wxT("Validee"));
    statuts.Add(wxT("Rejetee"));
    choixStatut = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(140, -1), statuts);
    filtreSizer->Add(choixStatut, 0, wxALL, 5);

    mainSizer->Add(filtreSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    // Legende
    wxStaticText* lblLegende = new wxStaticText(
        panel, wxID_ANY,
        wxT("Legende: Soumise = en attente | Validee = approuvee | Rejetee = a corriger"));
    lblLegende->SetForegroundColour(wxColour(90, 90, 90));
    mainSizer->Add(lblLegende, 0, wxLEFT | wxRIGHT | wxBOTTOM, 10);

    listNotes = new wxDataViewListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(-1, 280), wxDV_ROW_LINES);

    // Columns: checkbox, cours (code), matricule, nom, CC, TP, EX, statut, soumis
    // First column is an editable checkbox for selection
    listNotes->AppendToggleColumn(wxT("Sel"), wxDATAVIEW_CELL_ACTIVATABLE, 40);
    listNotes->AppendTextColumn(wxT("Cours"), wxDATAVIEW_CELL_INERT, 100, wxALIGN_LEFT);
    listNotes->AppendTextColumn(wxT("Matricule"), wxDATAVIEW_CELL_INERT, 90, wxALIGN_LEFT);
    listNotes->AppendTextColumn(wxT("Nom"), wxDATAVIEW_CELL_INERT, 200, wxALIGN_LEFT);
    listNotes->AppendTextColumn(wxT("CC"), wxDATAVIEW_CELL_INERT, 60, wxALIGN_RIGHT);
    listNotes->AppendTextColumn(wxT("TP"), wxDATAVIEW_CELL_INERT, 60, wxALIGN_RIGHT);
    listNotes->AppendTextColumn(wxT("EX"), wxDATAVIEW_CELL_INERT, 60, wxALIGN_RIGHT);
    listNotes->AppendTextColumn(wxT("Statut"), wxDATAVIEW_CELL_INERT, 90, wxALIGN_LEFT);
    listNotes->AppendTextColumn(wxT("Soumis"), wxDATAVIEW_CELL_INERT, 130, wxALIGN_LEFT);

    mainSizer->Add(listNotes, 1, wxALL | wxEXPAND, 10);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

    btnValider = new wxButton(panel, wxID_ANY, wxT("Valider"), wxDefaultPosition, wxSize(120, 35));
    btnValider->SetBackgroundColour(wxColour(46, 204, 113));
    btnValider->SetForegroundColour(*wxWHITE);
    btnValider->Bind(wxEVT_BUTTON, &ValidationNotesDialog::OnValider, this);

    btnRejeter = new wxButton(panel, wxID_ANY, wxT("Rejeter"), wxDefaultPosition, wxSize(120, 35));
    btnRejeter->SetBackgroundColour(wxColour(231, 76, 60));
    btnRejeter->SetForegroundColour(*wxWHITE);
    btnRejeter->Bind(wxEVT_BUTTON, &ValidationNotesDialog::OnRejeter, this);

    btnRafraichir = new wxButton(panel, wxID_ANY, wxT("Rafraichir"), wxDefaultPosition, wxSize(120, 35));
    btnRafraichir->Bind(wxEVT_BUTTON, &ValidationNotesDialog::OnRafraichir, this);

    btnFermer = new wxButton(panel, wxID_CANCEL, wxT("Fermer"), wxDefaultPosition, wxSize(120, 35));
    btnFermer->Bind(wxEVT_BUTTON, &ValidationNotesDialog::OnFermer, this);

    btnSizer->Add(btnValider, 0, wxALL, 5);
    btnSizer->Add(btnRejeter, 0, wxALL, 5);
    btnSizer->Add(btnRafraichir, 0, wxALL, 5);
    btnSizer->Add(btnFermer, 0, wxALL, 5);

    mainSizer->Add(btnSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    panel->SetSizer(mainSizer);

    ChargerCours();
    Centre();
}

void ValidationNotesDialog::ChargerCours()
{
    choixCours->Clear();

    wxArrayString cours;
    auto notes = Database::GetAllNotes();
    for (const auto& n : notes)
    {
        if (n.statut == wxT("Soumise"))
        {
            wxString code = n.cours.BeforeFirst(' ');
            if (code.IsEmpty())
                code = n.cours;
            if (cours.Index(code) == wxNOT_FOUND)
                cours.Add(code);
        }
    }

    if (cours.IsEmpty())
    {
        wxMessageBox(wxT("Aucune matiere avec notes soumises."), wxT("Info"),
                     wxOK | wxICON_INFORMATION);
        return;
    }

    for (unsigned int i = 0; i < cours.GetCount(); i++)
        choixCours->Append(cours[i]);

    choixCours->SetSelection(0);
    choixCours->Bind(wxEVT_CHOICE, &ValidationNotesDialog::OnCoursChange, this);
    choixStatut->SetSelection(0);
    choixStatut->Bind(wxEVT_CHOICE, &ValidationNotesDialog::OnStatutChange, this);

    ChargerNotes();
}

void ValidationNotesDialog::ChargerNotes()
{
    listNotes->DeleteAllItems();
    m_currentNotes.clear();

    wxString selectedCourse = choixCours->GetStringSelection();
    wxString selectedStatus = choixStatut->GetStringSelection();
    auto merged = Database::GetAllNotes();

    long index = 0;
    for (const auto& n : merged)
    {
        if (n.statut != selectedStatus)
            continue;
        if (!selectedCourse.IsEmpty())
        {
            wxString code = n.cours.BeforeFirst(' ');
            if (code.IsEmpty())
                code = n.cours;
            if (code != selectedCourse)
                continue;
        }

        // Extract course code (first token)
        wxString courseCode = n.cours.BeforeFirst(' ');
        if (courseCode.IsEmpty())
            courseCode = n.cours;

        wxString cc = n.hasCC ? wxString::Format(wxT("%.2f"), n.cc) : wxT("-");
        wxString tp = n.hasTP ? wxString::Format(wxT("%.2f"), n.tp) : wxT("-");
        wxString ex = n.hasExamen ? wxString::Format(wxT("%.2f"), n.examen) : wxT("-");
        wxString fullname = wxString::Format(wxT("%s %s"), n.nom, n.prenom);

        wxVariant sel(false);
        wxVariant varCourse(courseCode);
        wxVariant varMat(n.matricule);
        wxVariant varName(fullname);
        wxVariant varCC(cc);
        wxVariant varTP(tp);
        wxVariant varEX(ex);
        wxVariant varStat(n.statut);
        wxVariant varSub(n.submittedAt.IsEmpty() ? wxT("-") : n.submittedAt);

        wxVector<wxVariant> row;
        row.push_back(sel);
        row.push_back(varCourse);
        row.push_back(varMat);
        row.push_back(varName);
        row.push_back(varCC);
        row.push_back(varTP);
        row.push_back(varEX);
        row.push_back(varStat);
        row.push_back(varSub);

        listNotes->AppendItem(row);

        // Row coloring skipped for wxDataViewListCtrl to keep implementation simple

        m_currentNotes.push_back(n);
        index++;
    }
}

void ValidationNotesDialog::OnCoursChange(wxCommandEvent& event)
{
    ChargerNotes();
}

void ValidationNotesDialog::OnStatutChange(wxCommandEvent& event)
{
    ChargerNotes();
}

void ValidationNotesDialog::OnValider(wxCommandEvent& event)
{
    int count = 0;
    unsigned int rows = listNotes->GetItemCount();
    for (unsigned int r = 0; r < rows; ++r)
    {
        wxVariant val;
        listNotes->GetValue(val, r, 0);
        if (val.IsType("bool") && val.GetBool())
        {
            if (r < m_currentNotes.size())
            {
                const auto& n = m_currentNotes[r];
                Database::UpdateNoteValidation(n.matricule, n.cours, wxT("Validee"), wxT(""));
                count++;
            }
        }
    }

    if (count == 0)
    {
        wxMessageBox(wxT("Selectionnez au moins une note."), wxT("Info"), wxOK | wxICON_INFORMATION);
        return;
    }

    wxString msg = wxString::Format(wxT("Notes validees: %d\nNotification envoyee au professeur."), count);
    wxMessageBox(msg, wxT("Succes"), wxOK | wxICON_INFORMATION);
    ChargerNotes();
}

void ValidationNotesDialog::OnRejeter(wxCommandEvent& event)
{
    wxTextEntryDialog dlg(this, wxT("Motif du rejet:"), wxT("Rejet des notes"));
    if (dlg.ShowModal() == wxID_OK)
    {
        wxString reason = dlg.GetValue();
        if (reason.IsEmpty())
        {
            wxMessageBox(wxT("Le motif ne peut pas etre vide."), wxT("Erreur"), wxOK | wxICON_ERROR);
            return;
        }
        int count = 0;
        unsigned int rows = listNotes->GetItemCount();
        for (unsigned int r = 0; r < rows; ++r)
        {
            wxVariant val;
            listNotes->GetValue(val, r, 0);
            if (val.IsType("bool") && val.GetBool())
            {
                if (r < m_currentNotes.size())
                {
                    const auto& n = m_currentNotes[r];
                    Database::UpdateNoteValidation(n.matricule, n.cours, wxT("Rejetee"), reason);
                    count++;
                }
            }
        }

        if (count == 0)
        {
            wxMessageBox(wxT("Selectionnez au moins une note."), wxT("Info"), wxOK | wxICON_INFORMATION);
            return;
        }

        wxString msg = wxString::Format(wxT("Notes rejetees: %d\nNotification envoyee au professeur."), count);
        wxMessageBox(msg, wxT("Succes"), wxOK | wxICON_INFORMATION);
        ChargerNotes();
    }
}

void ValidationNotesDialog::OnRafraichir(wxCommandEvent& event)
{
    ChargerNotes();
}

// SelectAll/DeselectAll removed per requirements.

void ValidationNotesDialog::OnFermer(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
