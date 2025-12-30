#include "playlist.h"
#include <QRandomGenerator>

Playlist::Playlist() : head(nullptr), tail(nullptr), current(nullptr), isCircular(false) {}

Playlist::~Playlist() {
    clear();
}

void Playlist::clear() {
    Song* temp = head;
    while (temp) {
        Song* next = temp->next;
        delete temp;
        if (isCircular && next == head) break;
        temp = next;
    }
    head = tail = current = nullptr;
}

void Playlist::addSong(QString title, QString artist) {
    Song* newSong = new Song(title, artist);
    if (!head) {
        head = tail = current = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
        if (isCircular) {
            tail->next = head;
            head->prev = tail;
        }
    }
}

void Playlist::removeCurrentSong() {
    if (!current) return;

    Song* toDelete = current;

    if (toDelete == head) head = head->next;
    if (toDelete == tail) tail = tail->prev;

    if (toDelete->prev) toDelete->prev->next = toDelete->next;
    if (toDelete->next) toDelete->next->prev = toDelete->prev;

    current = toDelete->next ? toDelete->next : head;
    delete toDelete;
}

void Playlist::repeatMode(bool enable) {
    isCircular = enable;
    if (enable && head && tail) {
        tail->next = head;
        head->prev = tail;
    } else if (tail) {
        tail->next = nullptr;
        if (head) head->prev = nullptr;
    }
}

void Playlist::shuffle() {
    int n = countSongs();
    if (n < 2) return;

    QVector<Song*> songs = getAllSongs();
    for (int i = 0; i < n; ++i) {
        int j = QRandomGenerator::global()->bounded(n);
        std::swap(songs[i]->title, songs[j]->title);
        std::swap(songs[i]->artist, songs[j]->artist);
    }
}

void Playlist::moveSong(int fromIndex, int toIndex) {
    if (fromIndex == toIndex || fromIndex < 0 || toIndex < 0) return;

    Song* from = getSongAt(fromIndex);
    if (!from) return;

    // Unlink
    if (from->prev) from->prev->next = from->next;
    if (from->next) from->next->prev = from->prev;
    if (from == head) head = from->next;
    if (from == tail) tail = from->prev;

    // Relink
    Song* to = getSongAt(toIndex);
    if (!to) {
        // Append at end
        from->next = nullptr;
        from->prev = tail;
        if (tail) tail->next = from;
        tail = from;
        if (!head) head = from;
    } else {
        from->next = to;
        from->prev = to->prev;
        if (to->prev) to->prev->next = from;
        to->prev = from;
        if (to == head) head = from;
    }
}

Song* Playlist::search(QString title) {
    Song* temp = head;
    while (temp) {
        if (temp->title.compare(title, Qt::CaseInsensitive) == 0) {
            return temp;
        }
        temp = temp->next;
        if (isCircular && temp == head) break;
    }
    return nullptr;
}

QVector<Song*> Playlist::getAllSongs() {
    QVector<Song*> list;
    Song* temp = head;
    while (temp) {
        list.append(temp);
        temp = temp->next;
        if (isCircular && temp == head) break;
    }
    return list;
}

int Playlist::countSongs() const {
    int count = 0;
    Song* temp = head;
    while (temp) {
        ++count;
        temp = temp->next;
        if (isCircular && temp == head) break;
    }
    return count;
}

Song* Playlist::getSongAt(int index) {
    int i = 0;
    Song* temp = head;
    while (temp) {
        if (i == index) return temp;
        temp = temp->next;
        ++i;
        if (isCircular && temp == head) break;
    }
    return nullptr;
}
