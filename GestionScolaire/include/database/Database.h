#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <wx/string.h>

struct StudentRecord
{
    wxString matricule;
    wxString nom;
    wxString prenom;
};

struct AbsenceRecord
{
    int id;
    wxString matricule;
    wxString nom;
    wxString prenom;
    wxString cours;
    wxString date;
    wxString statut;
    wxString justification;
};

struct NoteRecord
{
    wxString matricule;
    wxString nom;
    wxString prenom;
    wxString cours;
    double cc;
    double tp;
    double examen;
    bool hasCC;
    bool hasTP;
    bool hasExamen;
    double moyenne;
    wxString statut; // Disponible, Soumise, Validee, Rejetee
    wxString adminComment;
    wxString updatedAt;
    wxString submittedAt;
    wxString validationAt;
};

class Database
{
public:
    // Etudiants (donnees simulees pour la demo)
    static const std::vector<StudentRecord>& GetStudents();
    static bool GetStudentByMatricule(const wxString& matricule, StudentRecord& out);
    static wxString NowStr();

    // Absences
    static int AddAbsence(const wxString& matricule,
                          const wxString& nom,
                          const wxString& prenom,
                          const wxString& cours,
                          const wxString& date);
    static std::vector<AbsenceRecord> GetAbsences();
    static std::vector<AbsenceRecord> GetAbsencesByMatricule(const wxString& matricule);
    static bool JustifyAbsence(int id, const wxString& justification);

    // Notes
    static void UpsertNote(const NoteRecord& note);
    static std::vector<NoteRecord> GetAllNotes();
    static std::vector<NoteRecord> GetNotesByCourse(const wxString& cours);
    static std::vector<NoteRecord> GetNotesByMatricule(const wxString& matricule);
    static bool UpdateNoteValidation(const wxString& matricule,
                                     const wxString& cours,
                                     const wxString& statut,
                                     const wxString& adminComment);

private:
    static void InitIfNeeded();
    static bool s_initialized;
    static int s_nextAbsenceId;
    static std::vector<StudentRecord> s_students;
    static std::vector<AbsenceRecord> s_absences;
    static std::vector<NoteRecord> s_notes;
};

#endif // DATABASE_H
