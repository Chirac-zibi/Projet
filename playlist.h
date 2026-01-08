#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QVector>

struct Song {
    QString title;
    QString artist;
};

class Playlist {
public:
    Playlist();

    void addSong(const QString &title, const QString &artist);
    void removeCurrentSong();
    void shuffle();
    void repeatMode(bool enabled);
    Song* search(const QString &title);
    void moveSong(int from, int to);

    Song* currentSong();
    void next();

    QVector<Song*> getAllSongs();
    bool isShuffleMode() const;
    QVector<int> getShuffledOrder() const;

private:
    QVector<Song*> songs;
    QVector<int> shuffledOrder;
    int currentIndex;
    bool repeat;
    bool isShuffle;
};

#endif // PLAYLIST_H
