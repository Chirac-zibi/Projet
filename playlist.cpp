#include "playlist.h"
#include <algorithm> // pour std::random_shuffle

Playlist::Playlist()
    : currentIndex(0), repeat(false), isShuffle(false) {}

void Playlist::addSong(const QString &title, const QString &artist) {
    Song* song = new Song{title, artist};
    songs.append(song);
}

void Playlist::removeCurrentSong() {
    if (songs.isEmpty()) return;

    int index = isShuffle ? shuffledOrder[currentIndex] : currentIndex;
    delete songs[index];
    songs.removeAt(index);

    if (isShuffle) {
        shuffledOrder.removeAt(currentIndex);
        if (currentIndex >= shuffledOrder.size()) currentIndex = 0;
    } else {
        if (currentIndex >= songs.size()) currentIndex = 0;
    }
}

void Playlist::shuffle() {
    isShuffle = true;
    shuffledOrder.clear();
    for (int i = 0; i < songs.size(); ++i) {
        shuffledOrder.append(i);
    }
    std::random_shuffle(shuffledOrder.begin(), shuffledOrder.end());
    currentIndex = 0;
}

void Playlist::repeatMode(bool enabled) {
    repeat = enabled;
}

Song* Playlist::search(const QString &title) {
    for (Song* song : songs) {
        if (song->title.compare(title, Qt::CaseInsensitive) == 0) {
            return song;
        }
    }
    return nullptr;
}

void Playlist::moveSong(int from, int to) {
    if (from < 0 || from >= songs.size() || to < 0 || to >= songs.size()) return;
    Song* song = songs.takeAt(from);
    songs.insert(to, song);
}

Song* Playlist::currentSong() {
    if (songs.isEmpty()) return nullptr;
    int index = isShuffle ? shuffledOrder[currentIndex] : currentIndex;
    return songs[index];
}

void Playlist::next() {
    if (songs.isEmpty()) return;

    if (isShuffle) {
        currentIndex++;
        if (currentIndex >= shuffledOrder.size()) {
            if (repeat) {
                shuffle(); // reshuffle and restart
            } else {
                currentIndex = shuffledOrder.size() - 1; // stay at last
            }
        }
    } else {
        currentIndex++;
        if (currentIndex >= songs.size()) {
            if (repeat) {
                currentIndex = 0;
            } else {
                currentIndex = songs.size() - 1;
            }
        }
    }
}

QVector<Song*> Playlist::getAllSongs() {
    return songs;
}

bool Playlist::isShuffleMode() const {
    return isShuffle;
}

QVector<int> Playlist::getShuffledOrder() const {
    return shuffledOrder;
}
