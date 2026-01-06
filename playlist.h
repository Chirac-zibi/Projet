#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QVector>
#include "song.h"

class Playlist {
public:
    Playlist();
    ~Playlist();

    void addSong(QString title, QString artist);
    void removeCurrentSong();
    void repeatMode(bool enable);
    void shuffle();
    void moveSong(int fromIndex, int toIndex);
    Song* search(QString title);
    QVector<Song*> getAllSongs() const;
    int countSongs() const;

    Song* getCurrent() const;  // Accès à la chanson en cours
    void next();               // Avancer à la chanson suivante

private:
    Song* head;
    Song* tail;
    Song* current;
    bool isCircular;

    void clear();
    Song* getSongAt(int index) const;
};

#endif // PLAYLIST_H
