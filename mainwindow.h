#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QFontDatabase>
#include "playlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_shuffleButton_clicked();
    void on_repeatButton_toggled(bool checked);
    void on_searchButton_clicked();
    void on_moveButton_clicked();

private:
    Ui::MainWindow *ui;
    Playlist playlist;

    QFont customFont;
    void applyCustomStyle();
    void refreshPlaylistDisplay();
};

#endif // MAINWINDOW_H
