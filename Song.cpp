#include "song.h"

Song::Song(QString t, QString a)
    : title(t), artist(a), next(nullptr), prev(nullptr) {}
