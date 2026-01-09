#include "dialogs/SaisieNotesDialog.h"
#include <wx/msgdlg.h>

SaisieNotesDialog::SaisieNotesDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, wxT("Saisie des Notes"), 
               wxDefaultPosition, wxSize(900, 600))
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // 1. Titre
    wxStaticText* lblTitre = new wxStaticText(panel, wxID_ANY, wxT("Saisie des Notes"));
    wxFont fontTitre = lblTitre->GetFont();
    fontTitre.SetPointSize(14);
    fontTitre.SetWeight(wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_CENTER, 15);

    // 2. Sélection du cours
    wxBoxSizer* coursSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* lblCours = new wxStaticText(panel, wxID_ANY, wxT("Cours :"));
    coursSizer->Add(lblCours, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    
    listeCours.Clear(); // On vide pour éviter les doublons
    listeCours.Add(wxT("INF301 - Programmation Orientée Objet"));
    listeCours.Add(wxT("INF302 - Base de Données"));
    listeCours.Add(wxT("ELEC201 - Électronique Numérique"));
    listeCours.Add(wxT("MATH301 - Analyse Numérique"));
    
    choixCours = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(400, -1), listeCours);
    choixCours->SetSelection(0);
    choixCours->Bind(wxEVT_CHOICE, &SaisieNotesDialog::OnCoursChange, this);
    coursSizer->Add(choixCours, 1, wxALL, 5);
    mainSizer->Add(coursSizer, 0, wxALL | wxEXPAND, 10);

    // 3. Infos de pondération et Statut
    lblInfo = new wxStaticText(panel, wxID_ANY, wxT("Pondérations: CC (30%) + TP (20%) + Examen (50%) = Moyenne"));
    lblInfo->SetForegroundColour(wxColour(100, 100, 100));
    mainSizer->Add(lblInfo, 0, wxALL | wxALIGN_CENTER, 5);

    lblStatut = new wxStaticText(panel, wxID_ANY, wxT("Statut: Brouillon (non soumis)"));
    wxFont fontStatut = lblStatut->GetFont();
    fontStatut.SetWeight(wxFONTWEIGHT_BOLD);
    lblStatut->SetFont(fontStatut);
    lblStatut->SetForegroundColour(wxColour(230, 126, 34));
    mainSizer->Add(lblStatut, 0, wxALL | wxALIGN_CENTER, 5);

    // 4. Grille pour les notes
    gridNotes = new wxGrid(panel, wxID_ANY);
    gridNotes->CreateGrid(10, 7);
    
    gridNotes->SetColLabelValue(0, wxT("Matricule"));
    gridNotes->SetColLabelValue(1, wxT("Nom"));
    gridNotes->SetColLabelValue(2, wxT("Prénom"));
    gridNotes->SetColLabelValue(3, wxT("CC (/20)"));
    gridNotes->SetColLabelValue(4, wxT("TP (/20)"));
    gridNotes->SetColLabelValue(5, wxT("Examen (/20)"));
    gridNotes->SetColLabelValue(6, wxT("Moyenne"));
    
    gridNotes->SetColSize(0, 120);
    gridNotes->SetColSize(1, 120);
    gridNotes->SetColSize(2, 120);
    gridNotes->SetColSize(3, 80);
    gridNotes->SetColSize(4, 80);
    gridNotes->SetColSize(5, 100);
    gridNotes->SetColSize(6, 120);

    for (int i = 0; i < 10; i++) {
        gridNotes->SetReadOnly(i, 0); gridNotes->SetReadOnly(i, 1);
        gridNotes->SetReadOnly(i, 2); gridNotes->SetReadOnly(i, 6);
    }
    
    gridNotes->Bind(wxEVT_GRID_CELL_CHANGED, &SaisieNotesDialog::OnCellChange, this);
    mainSizer->Add(gridNotes, 1, wxALL | wxEXPAND, 10);

    // --- ICI ON CHARGE LES DONNÉES ---
    ChargerEtudiants();

    // 5. Boutons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    
    btnSauvegarder = new wxButton(panel, wxID_ANY, wxT("Sauvegarder Brouillon"), wxDefaultPosition, wxSize(180, 35));
    btnSauvegarder->SetBackgroundColour(wxColour(241, 196, 15));
    btnSauvegarder->Bind(wxEVT_BUTTON, &SaisieNotesDialog::OnSauvegarder, this);
    
    btnEnregistrer = new wxButton(panel, wxID_OK, wxT("Enregistrer et Soumettre"), wxDefaultPosition, wxSize(180, 35));
    btnEnregistrer->SetBackgroundColour(wxColour(46, 204, 113));
    btnEnregistrer->SetForegroundColour(*wxWHITE);
    btnEnregistrer->Bind(wxEVT_BUTTON, &SaisieNotesDialog::OnEnregistrer, this);
    
    btnAnnuler = new wxButton(panel, wxID_CANCEL, wxT("Annuler"), wxDefaultPosition, wxSize(120, 35));
    btnAnnuler->Bind(wxEVT_BUTTON, &SaisieNotesDialog::OnAnnuler, this);
    
    buttonSizer->Add(btnSauvegarder, 0, wxALL, 5);
    buttonSizer->Add(btnEnregistrer, 0, wxALL, 5);
    buttonSizer->Add(btnAnnuler, 0, wxALL, 5);

    // On ajoute le sizer des boutons en bas à droite
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    panel->SetSizer(mainSizer);
}

void SaisieNotesDialog::ChargerEtudiants()
{
    // Données simulées (à remplacer par requête base de données)
    wxString etudiants[][3] = {
        {wxT("L3-GE-2024-001"), wxT("KOSSOU"), wxT("Jean")},
        {wxT("L3-GE-2024-002"), wxT("DOSSA"), wxT("Marie")},
        {wxT("L3-GE-2024-003"), wxT("AGBO"), wxT("Pierre")},
        {wxT("L3-GE-2024-004"), wxT("HOUNKPE"), wxT("Sophie")},
        {wxT("L3-GE-2024-005"), wxT("AZONHIHO"), wxT("Michel")},
        {wxT("L3-GE-2024-006"), wxT("GBEDJI"), wxT("Aïcha")},
        {wxT("L3-GE-2024-007"), wxT("TOSSA"), wxT("Laurent")},
        {wxT("L3-GE-2024-008"), wxT("SINSIN"), wxT("Fatou")},
        {wxT("L3-GE-2024-009"), wxT("ZODEHOUGAN"), wxT("Yves")},
        {wxT("L3-GE-2024-010"), wxT("MENSAH"), wxT("Nadège")}
    };
    
    for (int i = 0; i < 10; i++)
    {
        gridNotes->SetCellValue(i, 0, etudiants[i][0]); // Matricule
        gridNotes->SetCellValue(i, 1, etudiants[i][1]); // Nom
        gridNotes->SetCellValue(i, 2, etudiants[i][2]); // Prénom
        
        // Style pour les colonnes non éditables
        gridNotes->SetCellBackgroundColour(i, 0, wxColour(240, 240, 240));
        gridNotes->SetCellBackgroundColour(i, 1, wxColour(240, 240, 240));
        gridNotes->SetCellBackgroundColour(i, 2, wxColour(240, 240, 240));
        gridNotes->SetCellBackgroundColour(i, 6, wxColour(240, 240, 240));
    }
}

void SaisieNotesDialog::OnCoursChange(wxCommandEvent& event)
{
    // Recharger les notes pour le nouveau cours sélectionné
    ChargerEtudiants();
}

void SaisieNotesDialog::OnCellChange(wxGridEvent& event)
{
    int row = event.GetRow();
    int col = event.GetCol();
    
    // Si on modifie une note (CC, TP ou Examen)
    if (col >= 3 && col <= 5)
    {
        wxString value = gridNotes->GetCellValue(row, col);
        
        // Vérifier que c'est un nombre valide entre 0 et 20
        double note;
        if (!value.ToDouble(&note) || note < 0 || note > 20)
        {
            wxMessageBox(wxT("Veuillez entrer une note entre 0 et 20"), 
                        wxT("Erreur"), wxOK | wxICON_ERROR);
            gridNotes->SetCellValue(row, col, wxT(""));
            return;
        }
        
        // Recalculer la moyenne
        CalculerMoyenne(row);
    }
}

void SaisieNotesDialog::CalculerMoyenne(int row)
{
    wxString ccStr = gridNotes->GetCellValue(row, 3);
    wxString tpStr = gridNotes->GetCellValue(row, 4);
    wxString examenStr = gridNotes->GetCellValue(row, 5);
    
    // Vérifier que toutes les notes sont saisies
    if (ccStr.IsEmpty() || tpStr.IsEmpty() || examenStr.IsEmpty())
    {
        gridNotes->SetCellValue(row, 6, wxT(""));
        return;
    }
    
    double cc, tp, examen;
    ccStr.ToDouble(&cc);
    tpStr.ToDouble(&tp);
    examenStr.ToDouble(&examen);
    
    // Calcul: CC (30%) + TP (20%) + Examen (50%)
    double moyenne = (cc * 0.30) + (tp * 0.20) + (examen * 0.50);
    
    wxString mention = AttribuerMention(moyenne);
    wxString result = wxString::Format(wxT("%.2f - %s"), moyenne, mention);
    
    gridNotes->SetCellValue(row, 6, result);
    
    // Colorer selon la mention
    if (moyenne >= 16)
        gridNotes->SetCellBackgroundColour(row, 6, wxColour(46, 204, 113)); // Vert
    else if (moyenne >= 14)
        gridNotes->SetCellBackgroundColour(row, 6, wxColour(52, 152, 219)); // Bleu
    else if (moyenne >= 12)
        gridNotes->SetCellBackgroundColour(row, 6, wxColour(241, 196, 15)); // Jaune
    else if (moyenne >= 10)
        gridNotes->SetCellBackgroundColour(row, 6, wxColour(230, 126, 34)); // Orange
    else
        gridNotes->SetCellBackgroundColour(row, 6, wxColour(231, 76, 60)); // Rouge
}

wxString SaisieNotesDialog::AttribuerMention(double moyenne)
{
    if (moyenne >= 16) return wxT("Très Bien");
    if (moyenne >= 14) return wxT("Bien");
    if (moyenne >= 12) return wxT("Assez Bien");
    if (moyenne >= 10) return wxT("Passable");
    return wxT("Ajourné");
}

void SaisieNotesDialog::OnSauvegarder(wxCommandEvent& event)
{
    // Compter les notes saisies
    int notesCC = 0, notesTP = 0, notesExamen = 0;
    for (int i = 0; i < gridNotes->GetNumberRows(); i++)
    {
        if (!gridNotes->GetCellValue(i, 3).IsEmpty()) notesCC++;
        if (!gridNotes->GetCellValue(i, 4).IsEmpty()) notesTP++;
        if (!gridNotes->GetCellValue(i, 5).IsEmpty()) notesExamen++;
    }
    
    wxString msg = wxString::Format(
        wxT("Sauvegarde en cours...\n\nNotes saisies:\n- CC: %d/%d étudiants\n- TP: %d/%d étudiants\n- Examen: %d/%d étudiants\n\nLes notes sont sauvegardées en brouillon.\nVous pouvez les modifier à tout moment."),
        notesCC, gridNotes->GetNumberRows(),
        notesTP, gridNotes->GetNumberRows(),
        notesExamen, gridNotes->GetNumberRows());
    
    // TODO: Sauvegarder dans la base de données avec statut "Brouillon"
    
    wxMessageBox(msg, wxT("Brouillon sauvegardé"), wxOK | wxICON_INFORMATION);
    
    // Ne pas fermer la fenêtre, permettre de continuer la saisie
}

void SaisieNotesDialog::OnEnregistrer(wxCommandEvent& event)
{
    // Vérifier que toutes les notes sont complètes
    int notesIncompletes = 0;
    for (int i = 0; i < gridNotes->GetNumberRows(); i++)
    {
        if (gridNotes->GetCellValue(i, 3).IsEmpty() ||
            gridNotes->GetCellValue(i, 4).IsEmpty() ||
            gridNotes->GetCellValue(i, 5).IsEmpty())
        {
            notesIncompletes++;
        }
    }
    
    if (notesIncompletes > 0)
    {
        wxString msg = wxString::Format(
            wxT("ATTENTION: %d étudiant(s) ont des notes incomplètes!\n\nLes notes incomplètes ne seront PAS visibles par les étudiants.\n\nOptions:\n- Cliquez NON pour revenir à la saisie\n- Cliquez OUI pour soumettre quand même (seulement les notes complètes seront visibles)\n- Utilisez 'Sauvegarder Brouillon' pour sauvegarder sans soumettre"),
            notesIncompletes);
        
        if (wxMessageBox(msg, wxT("Notes incomplètes"), 
                        wxYES_NO | wxICON_WARNING) != wxYES)
        {
            return;
        }
    }
    
    // TODO: Enregistrer dans la base de données avec statut "Soumis"
    
    wxMessageBox(wxT("Notes soumises avec succès!\n\n✓ Les notes complètes sont maintenant visibles par les étudiants en temps réel.\n✓ Vous pouvez toujours les modifier avant validation par l'administrateur."), 
                 wxT("Succès"), wxOK | wxICON_INFORMATION);
    
    EndModal(wxID_OK);
}
void SaisieNotesDialog::OnAnnuler(wxCommandEvent& event)
{
    // Vérifier s'il y a des modifications non sauvegardées
    bool hasData = false;
    for (int i = 0; i < gridNotes->GetNumberRows() && !hasData; i++)
    {
        if (!gridNotes->GetCellValue(i, 3).IsEmpty() ||
            !gridNotes->GetCellValue(i, 4).IsEmpty() ||
            !gridNotes->GetCellValue(i, 5).IsEmpty())
        {
            hasData = true;
        }
    }
    
    if (hasData)
    {
        if (wxMessageBox(wxT("Vous avez des notes non sauvegardées!\n\nVoulez-vous vraiment quitter sans sauvegarder?"), 
                         wxT("Confirmation"), 
                         wxYES_NO | wxICON_WARNING) != wxYES)
        {
            return;
        }
    }
    
    EndModal(wxID_CANCEL);
}