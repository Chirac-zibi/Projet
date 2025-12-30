#include "Playlist.h"

Playlist::Playlist()
    : tete(nullptr), queue(nullptr), taille(0)
{
}

Playlist::~Playlist()
{
    Titre* courant = tete;
    while (courant != nullptr)
    {
        Titre* suivant = courant->suivant;
        delete courant;
        courant = suivant;
    }
}

void Playlist::ajouterTitre(Titre* titre)
{
    if (!tete)
    {
        tete = queue = titre;
    }
    else
    {
        queue->suivant = titre;
        titre->precedent = queue;
        queue = titre;
    }
    taille++;
}

void Playlist::supprimerTitre(Titre* titre)
{
    if (!titre) return;

    if (titre == tete)
        tete = titre->suivant;

    if (titre == queue)
        queue = titre->precedent;

    if (titre->precedent)
        titre->precedent->suivant = titre->suivant;

    if (titre->suivant)
        titre->suivant->precedent = titre->precedent;

    delete titre;
    taille--;
}

Titre* Playlist::rechercherTitre(const QString& nom) const
{
    Titre* courant = tete;
    while (courant)
    {
        if (courant->getNom() == nom)
            return courant;

        courant = courant->suivant;
    }
    return nullptr;
}

int Playlist::getTaille() const
{
    return taille;
}
