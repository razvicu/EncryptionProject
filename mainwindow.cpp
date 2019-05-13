#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QUuid>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));
    crypto = new SimpleCrypt();

    quint64 key = (((long long)rand() << 32) | rand());
    crypto->setKey(key);
    ui->encryptionKeyLineEdit->setText(QString::number(key));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete crypto;

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
    crypto->setKey(key.toULongLong());

    QString encryptedText = crypto->encryptToString(content);

    QFile outFile("encryptedText");
    outFile.open(QIODevice::WriteOnly);
    outFile.write(encryptedText.toStdString().c_str());

    ui->plainTextEdit->setPlainText(encryptedText);
}

void MainWindow::on_decryptionButton_clicked()
{
    QString message = ui->plainTextEdit->toPlainText();
    QString key = ui->encryptionKeyLineEdit->text();
    crypto->setKey(key.toULongLong());

    QString decryptedText = crypto->decryptToString(message);

    QFile outFile("decryptedText");
    outFile.open(QIODevice::WriteOnly);
    outFile.write(decryptedText.toStdString().c_str());

    ui->plainTextEdit->setPlainText(decryptedText);


}
