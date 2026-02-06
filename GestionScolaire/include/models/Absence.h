#ifndef ABSENCE_H
#define ABSENCE_H

#include <string>
#include <vector>
#include "models/Etudiant.h"

struct Absence
{
    int id = 0;
    std::string matricule;
    std::string nom;
    std::string prenom;
    std::string cours;
    std::string date;
    std::string statut;
    std::string justification;

    static std::vector<Absence> getByMatricule(const std::string& matricule);
    static bool justifier(int id, const std::string& justification);

    static int enregistrerAbsences(const std::vector<Etudiant>& etudiants,
                                   const std::vector<size_t>& indices,
                                   const std::string& cours,
                                   const std::string& date);
};

#endif // ABSENCE_H
