#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "encrypt.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", "/");
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::warning(this, "Warning", "File was not opened");

    QTextStream in(&file);
    QString content = in.readAll();
    ui->plainTextEdit->setPlainText(content);
}

void MainWindow::on_encryptionButton_clicked()
{
    QString content = ui->plainTextEdit->toPlainText();
    QString key = ui->encryptionKeyLineEdit->text();
    EncryptionData ed = encrypt(content);
    QString encryptedMessage = QString::fromStdString(std::string(ed.message.begin(), ed.message.end()));
    QString encryptionKey = QString::fromStdString(std::string(ed.key.begin(), ed.key.end()));

    ui->encryptedTextEdit->setPlainText(encryptedMessage);
    ui->encryptionKeyLineEdit->setText(encryptionKey);
}

void MainWindow::on_decryptionButton_clicked()
{
    QString message = ui->encryptedTextEdit->toPlainText();
    QString key = ui->encryptionKeyLineEdit->text();

    std::vector<char> content = decrypt(message, key);
    QString decryptedMessage = QString::fromStdString(std::string(content.begin(), content.end()));
    ui->encryptedTextEdit->setPlainText(decryptedMessage);
}
