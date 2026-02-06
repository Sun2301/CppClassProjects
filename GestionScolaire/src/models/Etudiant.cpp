#include "models/Etudiant.h"
#include "database/Database.h"

static std::string ToStdString(const wxString& value)
{
    wxCharBuffer buffer = value.ToUTF8();
    return buffer.data() ? std::string(buffer.data()) : std::string();
}

static wxString ToWxString(const std::string& value)
{
    return wxString::FromUTF8(value.c_str());
}

std::vector<Etudiant> Etudiant::getAll()
{
    std::vector<Etudiant> result;
    const auto& students = Database::GetStudents();
    result.reserve(students.size());

    for (const auto& s : students)
    {
        result.push_back({
            ToStdString(s.matricule),
            ToStdString(s.nom),
            ToStdString(s.prenom)
        });
    }

    return result;
}

bool Etudiant::getByMatricule(const std::string& matricule, Etudiant& out)
{
    StudentRecord student;
    if (!Database::GetStudentByMatricule(ToWxString(matricule), student))
    {
        return false;
    }

    out.matricule = ToStdString(student.matricule);
    out.nom = ToStdString(student.nom);
    out.prenom = ToStdString(student.prenom);
    return true;
}

std::string Etudiant::nomComplet() const
{
    if (nom.empty())
        return prenom;
    if (prenom.empty())
        return nom;
    return nom + " " + prenom;
}
