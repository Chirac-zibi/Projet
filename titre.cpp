#include "Titre.h"

Titre::Titre(const QString& nom, const QString& artiste, int duree)
    : nom(nom), artiste(artiste), duree(duree),
    suivant(nullptr), precedent(nullptr)
{
}

QString Titre::getNom() const {
    return nom;
}
QString Titre::getArtiste() const {
    return artiste;
}
int Titre::getDuree() const {
    return duree;
}
