#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshPlaylistDisplay();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::refreshPlaylistDisplay() {
    ui->listWidget->clear();
    QVector<Song*> songs = playlist.getAllSongs();
    for (int i = 0; i < songs.size(); ++i) {
        ui->listWidget->addItem(QString::number(i + 1) + ". " + songs[i]->title + " - " + songs[i]->artist);
    }
}

void MainWindow::on_addButton_clicked() {
    QString title = ui->titleInput->text();
    QString artist = ui->artistInput->text();

    if (title.isEmpty() || artist.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez entrer un titre et un artiste.");
        return;
    }

    playlist.addSong(title, artist);
    refreshPlaylistDisplay();
    ui->titleInput->clear();
    ui->artistInput->clear();
}

void MainWindow::on_removeButton_clicked() {
    playlist.removeCurrentSong();
    refreshPlaylistDisplay();
}

void MainWindow::on_shuffleButton_clicked() {
    playlist.shuffle();
    refreshPlaylistDisplay();
}

void MainWindow::on_repeatButton_toggled(bool checked) {
    playlist.repeatMode(checked);
    QString status = checked ? "Mode répétition activé" : "Mode répétition désactivé";
    QMessageBox::information(this, "Répétition", status);
}

void MainWindow::on_searchButton_clicked() {
    QString query = QInputDialog::getText(this, "Recherche", "Entrez le titre de la chanson :");
    if (query.isEmpty()) return;

    Song* found = playlist.search(query);
    if (found) {
        QMessageBox::information(this, "Chanson trouvée", "Titre : " + found->title + "\nArtiste : " + found->artist);
    } else {
        QMessageBox::warning(this, "Introuvable", "Aucune chanson trouvée avec ce titre.");
    }
}

void MainWindow::on_moveButton_clicked() {
    bool ok1, ok2;
    int from = QInputDialog::getInt(this, "Déplacer chanson", "Index de départ :", 1, 1, 100, 1, &ok1);
    int to = QInputDialog::getInt(this, "Déplacer chanson", "Nouvel index :", 1, 1, 100, 1, &ok2);

    if (ok1 && ok2) {
        playlist.moveSong(from - 1, to - 1);
        refreshPlaylistDisplay();
    }
}
