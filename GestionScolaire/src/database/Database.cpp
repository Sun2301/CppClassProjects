#include "database/Database.h"
#include <wx/datetime.h>

bool Database::s_initialized = false;
int Database::s_nextAbsenceId = 1;
std::vector<StudentRecord> Database::s_students;
std::vector<AbsenceRecord> Database::s_absences;
std::vector<NoteRecord> Database::s_notes;

void Database::InitIfNeeded()
{
    if (s_initialized)
        return;

    s_students = {
        {wxT("L3-GE-2024-001"), wxT("KOSSOU"), wxT("Jean")},
        {wxT("L3-GE-2024-002"), wxT("DOSSA"), wxT("Marie")},
        {wxT("L3-GE-2024-003"), wxT("AGBO"), wxT("Pierre")},
        {wxT("L3-GE-2024-004"), wxT("HOUNKPE"), wxT("Sophie")},
        {wxT("L3-GE-2024-005"), wxT("AZONHIHO"), wxT("Michel")},
        {wxT("L3-GE-2024-006"), wxT("GBEDJI"), wxT("Aicha")},
        {wxT("L3-GE-2024-007"), wxT("TOSSA"), wxT("Laurent")},
        {wxT("L3-GE-2024-008"), wxT("SINSIN"), wxT("Fatou")},
        {wxT("L3-GE-2024-009"), wxT("ZODEHOUGAN"), wxT("Yves")},
        {wxT("L3-GE-2024-010"), wxT("MENSAH"), wxT("Nadege")}
    };

    s_initialized = true;
}

wxString Database::NowStr()
{
    wxDateTime now = wxDateTime::Now();
    return now.FormatISODate() + wxT(" ") + now.FormatISOTime();
}

const std::vector<StudentRecord>& Database::GetStudents()
{
    InitIfNeeded();
    return s_students;
}

bool Database::GetStudentByMatricule(const wxString& matricule, StudentRecord& out)
{
    InitIfNeeded();
    for (const auto& s : s_students)
    {
        if (s.matricule == matricule)
        {
            out = s;
            return true;
        }
    }
    return false;
}

int Database::AddAbsence(const wxString& matricule,
                         const wxString& nom,
                         const wxString& prenom,
                         const wxString& cours,
                         const wxString& date)
{
    InitIfNeeded();

    AbsenceRecord rec;
    rec.id = s_nextAbsenceId++;
    rec.matricule = matricule;
    rec.nom = nom;
    rec.prenom = prenom;
    rec.cours = cours;
    rec.date = date;
    rec.statut = wxT("Non justifiee");
    rec.justification = wxT("");

    s_absences.push_back(rec);
    return rec.id;
}

std::vector<AbsenceRecord> Database::GetAbsences()
{
    InitIfNeeded();
    return s_absences;
}

std::vector<AbsenceRecord> Database::GetAbsencesByMatricule(const wxString& matricule)
{
    InitIfNeeded();
    std::vector<AbsenceRecord> out;
    for (const auto& a : s_absences)
    {
        if (a.matricule == matricule)
            out.push_back(a);
    }
    return out;
}

bool Database::JustifyAbsence(int id, const wxString& justification)
{
    InitIfNeeded();
    for (auto& a : s_absences)
    {
        if (a.id == id)
        {
            a.justification = justification;
            a.statut = wxT("Justification soumise");
            return true;
        }
    }
    return false;
}

void Database::UpsertNote(const NoteRecord& note)
{
    InitIfNeeded();

    for (auto& n : s_notes)
    {
        if (n.matricule == note.matricule && n.cours == note.cours)
        {
            n = note;
            return;
        }
    }
    s_notes.push_back(note);
}

std::vector<NoteRecord> Database::GetAllNotes()
{
    InitIfNeeded();
    return s_notes;
}

std::vector<NoteRecord> Database::GetNotesByCourse(const wxString& cours)
{
    InitIfNeeded();
    std::vector<NoteRecord> out;
    for (const auto& n : s_notes)
    {
        if (n.cours == cours)
            out.push_back(n);
    }
    return out;
}

std::vector<NoteRecord> Database::GetNotesByMatricule(const wxString& matricule)
{
    InitIfNeeded();
    std::vector<NoteRecord> out;
    for (const auto& n : s_notes)
    {
        if (n.matricule == matricule)
            out.push_back(n);
    }
    return out;
}

bool Database::UpdateNoteValidation(const wxString& matricule,
                                    const wxString& cours,
                                    const wxString& statut,
                                    const wxString& adminComment)
{
    InitIfNeeded();
    for (auto& n : s_notes)
    {
        if (n.matricule == matricule && n.cours == cours)
        {
            n.statut = statut;
            n.adminComment = adminComment;
            n.validationAt = NowStr();
            return true;
        }
    }
    return false;
}
