#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

struct Note
{
    std::string matricule;
    std::string nom;
    std::string prenom;
    std::string cours;
    double cc = 0.0;
    double tp = 0.0;
    double examen = 0.0;
    bool hasCC = false;
    bool hasTP = false;
    bool hasExamen = false;
    double moyenne = 0.0;
    std::string statut;
    std::string adminComment;
    std::string updatedAt;
    std::string submittedAt;
    std::string validationAt;

    static std::vector<Note> getAll();
    static std::vector<Note> getByCourse(const std::string& cours);
    static std::vector<Note> getByMatricule(const std::string& matricule);
    static std::vector<Note> getNotesEnAttente();
    static std::vector<std::string> getCourseCodesWithStatus(const std::string& statut);
    static std::vector<Note> getByStatusAndCourseCode(const std::string& statut,
                                                      const std::string& courseCodeFilter);

    static void upsert(const Note& note);
    static bool updateValidation(const std::string& matricule,
                                 const std::string& cours,
                                 const std::string& statut,
                                 const std::string& adminComment);

    static std::string nowStr();
    static std::string courseCode(const std::string& cours);
};

#endif // NOTE_H
