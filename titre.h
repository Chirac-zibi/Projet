#ifndef TITRE_H
#define TITRE_H

#include <QString>

class Titre {
public:
    Titre(const QString& nom, const QString& artiste, int duree);

    QString getNom() const;
    QString getArtiste() const;
    int getDuree() const;

    Titre* suivant;
    Titre* precedent;

private:
    QString nom;
    QString artiste;
    int duree;
};

#endif // TITRE_H
