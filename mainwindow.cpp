#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playlist.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QFontDatabase>
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    applyCustomStyle();
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

void MainWindow::applyCustomStyle() {
    // Charger une police personnalisée (optionnel)
    QFontDatabase::addApplicationFont(":/fonts/OpenSans-Regular.ttf");
    customFont = QFont("Open Sans", 10);
    this->setFont(customFont);

    // Appliquer un fond d’écran
    QPixmap bkgnd(":/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    // Styliser les champs de texte
    QString lineEditStyle = "QLineEdit { background-color: #ffffff; border: 1px solid #ccc; border-radius: 4px; padding: 6px; font-size: 14px; }";
    ui->titleInput->setStyleSheet(lineEditStyle);
    ui->artistInput->setStyleSheet(lineEditStyle);

    // Styliser la liste
    ui->listWidget->setStyleSheet("QListWidget { background-color: rgba(255, 255, 255, 0.85); border: 1px solid #aaa; font-size: 14px; }");

    // Style général des boutons
    QString baseButtonStyle = "QPushButton { background-color: #4CAF50; color: white; border-radius: 6px; padding: 6px; font-weight: bold; }"
                              "QPushButton:hover { background-color: #45a049; }";
    ui->addButton->setStyleSheet(baseButtonStyle);
    ui->removeButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; border-radius: 6px; padding: 6px; font-weight: bold; }"
                                    "QPushButton:hover { background-color: #d32f2f; }");
    ui->shuffleButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; border-radius: 6px; padding: 6px; font-weight: bold; }"
                                     "QPushButton:hover { background-color: #1976D2; }");
    ui->searchButton->setStyleSheet("QPushButton { background-color: #9C27B0; color: white; border-radius: 6px; padding: 6px; font-weight: bold; }"
                                    "QPushButton:hover { background-color: #7B1FA2; }");
    ui->moveButton->setStyleSheet("QPushButton { background-color: #FF9800; color: white; border-radius: 6px; padding: 6px; font-weight: bold; }"
                                  "QPushButton:hover { background-color: #FB8C00; }");

    // Case à cocher
    ui->repeatButton->setStyleSheet("QCheckBox { color: white; font-weight: bold; font-size: 14px; }");
}
