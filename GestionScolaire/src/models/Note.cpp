#include "models/Note.h"
#include "database/Database.h"

#include <unordered_set>

static std::string ToStdString(const wxString& value)
{
    wxCharBuffer buffer = value.ToUTF8();
    return buffer.data() ? std::string(buffer.data()) : std::string();
}

static wxString ToWxString(const std::string& value)
{
    return wxString::FromUTF8(value.c_str());
}

static Note FromRecord(const NoteRecord& n)
{
    Note note;
    note.matricule = ToStdString(n.matricule);
    note.nom = ToStdString(n.nom);
    note.prenom = ToStdString(n.prenom);
    note.cours = ToStdString(n.cours);
    note.cc = n.cc;
    note.tp = n.tp;
    note.examen = n.examen;
    note.hasCC = n.hasCC;
    note.hasTP = n.hasTP;
    note.hasExamen = n.hasExamen;
    note.moyenne = n.moyenne;
    note.statut = ToStdString(n.statut);
    note.adminComment = ToStdString(n.adminComment);
    note.updatedAt = ToStdString(n.updatedAt);
    note.submittedAt = ToStdString(n.submittedAt);
    note.validationAt = ToStdString(n.validationAt);
    return note;
}

static NoteRecord ToRecord(const Note& note)
{
    NoteRecord n;
    n.matricule = ToWxString(note.matricule);
    n.nom = ToWxString(note.nom);
    n.prenom = ToWxString(note.prenom);
    n.cours = ToWxString(note.cours);
    n.cc = note.cc;
    n.tp = note.tp;
    n.examen = note.examen;
    n.hasCC = note.hasCC;
    n.hasTP = note.hasTP;
    n.hasExamen = note.hasExamen;
    n.moyenne = note.moyenne;
    n.statut = ToWxString(note.statut);
    n.adminComment = ToWxString(note.adminComment);
    n.updatedAt = ToWxString(note.updatedAt);
    n.submittedAt = ToWxString(note.submittedAt);
    n.validationAt = ToWxString(note.validationAt);
    return n;
}

std::vector<Note> Note::getAll()
{
    std::vector<Note> result;
    auto notes = Database::GetAllNotes();
    result.reserve(notes.size());
    for (const auto& n : notes)
    {
        result.push_back(FromRecord(n));
    }
    return result;
}

std::vector<Note> Note::getByCourse(const std::string& cours)
{
    std::vector<Note> result;
    auto notes = Database::GetNotesByCourse(ToWxString(cours));
    result.reserve(notes.size());
    for (const auto& n : notes)
    {
        result.push_back(FromRecord(n));
    }
    return result;
}

std::vector<Note> Note::getByMatricule(const std::string& matricule)
{
    std::vector<Note> result;
    auto notes = Database::GetNotesByMatricule(ToWxString(matricule));
    result.reserve(notes.size());
    for (const auto& n : notes)
    {
        result.push_back(FromRecord(n));
    }
    return result;
}

std::vector<Note> Note::getNotesEnAttente()
{
    std::vector<Note> result;
    auto notes = Database::GetAllNotes();
    for (const auto& n : notes)
    {
        if (n.statut == wxT("Soumise"))
        {
            result.push_back(FromRecord(n));
        }
    }
    return result;
}

std::vector<std::string> Note::getCourseCodesWithStatus(const std::string& statut)
{
    std::unordered_set<std::string> seen;
    std::vector<std::string> result;
    auto notes = Database::GetAllNotes();

    for (const auto& n : notes)
    {
        if (ToStdString(n.statut) != statut)
            continue;
        std::string code = courseCode(ToStdString(n.cours));
        if (code.empty())
            continue;
        if (seen.insert(code).second)
            result.push_back(code);
    }

    return result;
}

std::vector<Note> Note::getByStatusAndCourseCode(const std::string& statut,
                                                 const std::string& courseCodeFilter)
{
    std::vector<Note> result;
    auto notes = Database::GetAllNotes();

    for (const auto& n : notes)
    {
        std::string status = ToStdString(n.statut);
        if (status != statut)
            continue;

        std::string code = courseCode(ToStdString(n.cours));
        if (!courseCodeFilter.empty() && code != courseCodeFilter)
            continue;

        result.push_back(FromRecord(n));
    }

    return result;
}

void Note::upsert(const Note& note)
{
    Database::UpsertNote(ToRecord(note));
}

bool Note::updateValidation(const std::string& matricule,
                            const std::string& cours,
                            const std::string& statut,
                            const std::string& adminComment)
{
    return Database::UpdateNoteValidation(
        ToWxString(matricule),
        ToWxString(cours),
        ToWxString(statut),
        ToWxString(adminComment));
}

std::string Note::nowStr()
{
    return ToStdString(Database::NowStr());
}

std::string Note::courseCode(const std::string& cours)
{
    size_t pos = cours.find(' ');
    if (pos == std::string::npos)
        return cours;
    return cours.substr(0, pos);
}
