#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <string>
#include <vector>

struct Etudiant
{
    std::string matricule;
    std::string nom;
    std::string prenom;

    static std::vector<Etudiant> getAll();
    static bool getByMatricule(const std::string& matricule, Etudiant& out);

    std::string nomComplet() const;
};

#endif // ETUDIANT_H
