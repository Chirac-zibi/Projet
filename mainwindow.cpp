#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFontDatabase>
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , playTimer(new QTimer(this))
    , isPlaying(false)
    , currentIndex(0)
{
    ui->setupUi(this);
    applyCustomStyle();
    refreshPlaylistDisplay();

    connect(playTimer, &QTimer::timeout, this, &MainWindow::playNextSong);
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
    currentIndex = 0;
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

void MainWindow::on_playButton_clicked() {
    if (!isPlaying && ui->listWidget->count() > 0) {
        isPlaying = true;
        currentIndex = 0;
        ui->statusLabel->setText("Lecture aléatoire en cours...");
        playTimer->start(1500);
    }
}

void MainWindow::on_stopButton_clicked() {
    isPlaying = false;
    playTimer->stop();
    ui->statusLabel->setText("Lecture arrêtée.");
    ui->listWidget->clearSelection();
}

void MainWindow::playNextSong() {
    int total = ui->listWidget->count();
    if (total == 0) return;

    ui->listWidget->clearSelection();
    ui->listWidget->setCurrentRow(currentIndex);
    ui->listWidget->item(currentIndex)->setSelected(true);

    QString currentText = ui->listWidget->item(currentIndex)->text();
    ui->statusLabel->setText("Lecture : " + currentText);

    currentIndex = (currentIndex + 1) % total;
}

void MainWindow::applyCustomStyle() {
    QFontDatabase::addApplicationFont(":/fonts/OpenSans-Regular.ttf");
    customFont = QFont("Open Sans", 10);
    this->setFont(customFont);

    QPixmap bkgnd(":/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QString lineEditStyle = "QLineEdit { background-color: #ffffff; border: 1px solid #ccc; border-radius: 4px; padding: 6px; font-size: 14px; }";
    ui->titleInput->setStyleSheet(lineEditStyle);
    ui->artistInput->setStyleSheet(lineEditStyle);

    ui->listWidget->setStyleSheet(
        "QListWidget::item:selected { background-color: #00BCD4; color: white; font-weight: bold; }"
        "QListWidget { background-color: rgba(255, 255, 255, 0.85); border: 1px solid #aaa; font-size: 14px; }"
        );

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
    ui->repeatButton->setStyleSheet("QCheckBox { color: white; font-weight: bold; font-size: 14px; }");
    ui->playButton->setStyleSheet("QPushButton { background-color: #00BCD4; color: white; border-radius: 6px; padding: 6px; font-weight: bold; }"
                                  "QPushButton:hover { background-color: #0097A7; }");
    ui->stopButton->setStyleSheet("QPushButton { background-color: #607D8B; color: white; border-radius: 6px; padding: 6px; font-weight: bold; }"
                                  "QPushButton:hover { background-color: #455A64; }");
}
