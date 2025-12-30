#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include "Titre.h"

class Playlist
{
public:
    Playlist();
    ~Playlist();

    void ajouterTitre(Titre* titre);
    void supprimerTitre(Titre* titre);
    Titre* rechercherTitre(const QString& nom) const;
    int getTaille() const;

    // TEMPORAIREMENT public pour éviter d'autres erreurs
    Titre* tete;
    Titre* queue;

private:
    int taille;
};

#endif // PLAYLIST_H
