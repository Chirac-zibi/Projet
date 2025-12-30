#ifndef SONG_H
#define SONG_H

#include <QString>

class Song {
public:
    QString title;
    QString artist;
    Song* next;
    Song* prev;

    Song(QString t, QString a); // Déclaration uniquement
};

#endif // SONG_H
