#include "models/Absence.h"
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

std::vector<Absence> Absence::getByMatricule(const std::string& matricule)
{
    std::vector<Absence> result;
    auto absences = Database::GetAbsencesByMatricule(ToWxString(matricule));
    result.reserve(absences.size());

    for (const auto& a : absences)
    {
        Absence item;
        item.id = a.id;
        item.matricule = ToStdString(a.matricule);
        item.nom = ToStdString(a.nom);
        item.prenom = ToStdString(a.prenom);
        item.cours = ToStdString(a.cours);
        item.date = ToStdString(a.date);
        item.statut = ToStdString(a.statut);
        item.justification = ToStdString(a.justification);
        result.push_back(item);
    }

    return result;
}

bool Absence::justifier(int id, const std::string& justification)
{
    return Database::JustifyAbsence(id, ToWxString(justification));
}

int Absence::enregistrerAbsences(const std::vector<Etudiant>& etudiants,
                                 const std::vector<size_t>& indices,
                                 const std::string& cours,
                                 const std::string& date)
{
    int count = 0;
    for (size_t index : indices)
    {
        if (index >= etudiants.size())
            continue;
        const auto& s = etudiants[index];
        Database::AddAbsence(
            ToWxString(s.matricule),
            ToWxString(s.nom),
            ToWxString(s.prenom),
            ToWxString(cours),
            ToWxString(date));
        count++;
    }

    return count;
}
