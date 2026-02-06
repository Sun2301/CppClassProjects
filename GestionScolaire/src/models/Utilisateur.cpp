#include "models/Utilisateur.h"
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

Utilisateur::Utilisateur(const std::string& login,
                         const std::string& nom,
                         const std::string& prenom,
                         const std::string& matricule,
                         Role role)
    : m_login(login),
      m_nom(nom),
      m_prenom(prenom),
      m_matricule(matricule),
      m_role(role)
{
}

Utilisateur* Utilisateur::authentifier(const std::string& login, const std::string& mdp)
{
    if (login.empty() || mdp.empty())
    {
        return nullptr;
    }

    StudentRecord student;
    if (Database::GetStudentByMatricule(ToWxString(login), student))
    {
        return new Utilisateur(
            login,
            ToStdString(student.nom),
            ToStdString(student.prenom),
            ToStdString(student.matricule),
            Role::Etudiant);
    }

    return new Utilisateur(login, std::string(), std::string(), std::string(), Role::Autre);
}

const std::string& Utilisateur::getLogin() const
{
    return m_login;
}

const std::string& Utilisateur::getNom() const
{
    return m_nom;
}

const std::string& Utilisateur::getPrenom() const
{
    return m_prenom;
}

const std::string& Utilisateur::getMatricule() const
{
    return m_matricule;
}

Utilisateur::Role Utilisateur::getRole() const
{
    return m_role;
}

std::string Utilisateur::getNomComplet() const
{
    if (m_nom.empty())
        return m_prenom;
    if (m_prenom.empty())
        return m_nom;
    return m_nom + " " + m_prenom;
}
