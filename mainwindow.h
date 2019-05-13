#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simplecrypt.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_decryptionButton_clicked();

    void on_encryptionButton_clicked();

private:
    Ui::MainWindow *ui;
    SimpleCrypt *crypto;
};

#endif // MAINWINDOW_H
