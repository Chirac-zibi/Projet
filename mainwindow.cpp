#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Gestion des playlists");

    // Connexion des boutons
    connect(ui->btnAjouter, &QPushButton::clicked,
            this, &MainWindow::ajouterTitre);

    connect(ui->btnSupprimer, &QPushButton::clicked,
            this, &MainWindow::supprimerTitre);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Ajouter un titre dans la liste
void MainWindow::ajouterTitre()
{
    QString titre = ui->editTitre->text();

    if (titre.isEmpty())
        return;

    ui->listePlaylist->addItem(titre);
    ui->editTitre->clear();
}

// Supprimer le titre sélectionné
void MainWindow::supprimerTitre()
{
    int index = ui->listePlaylist->currentRow();

    if (index < 0)
        return;

    delete ui->listePlaylist->takeItem(index);
}
