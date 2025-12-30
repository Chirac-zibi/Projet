#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"
#include <QString>
#include <QVector>

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;
    bool isCircular;

public:
    Playlist();
    ~Playlist();

    void addSong(QString title, QString artist);
    void removeCurrentSong();
    void shuffle();
    void repeatMode(bool enable);
    void moveSong(int fromIndex, int toIndex);
    Song* search(QString title);
    QVector<Song*> getAllSongs();

private:
    int countSongs() const;
    Song* getSongAt(int index);
    void clear();
};

#endif // PLAYLIST_H
