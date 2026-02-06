#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>

class Utilisateur
{
public:
    enum class Role
    {
        Inconnu,
        Etudiant,
        Autre
    };

    static Utilisateur* authentifier(const std::string& login, const std::string& mdp);

    const std::string& getLogin() const;
    const std::string& getNom() const;
    const std::string& getPrenom() const;
    const std::string& getMatricule() const;
    Role getRole() const;
    std::string getNomComplet() const;

private:
    std::string m_login;
    std::string m_nom;
    std::string m_prenom;
    std::string m_matricule;
    Role m_role = Role::Inconnu;

    Utilisateur(const std::string& login,
                const std::string& nom,
                const std::string& prenom,
                const std::string& matricule,
                Role role);
};

#endif // UTILISATEUR_H
