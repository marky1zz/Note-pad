#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    setWindowTitle("NotePad");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    current_file = "";
    ui->textEdit->clear();
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Opened file");
    QFile file(file_name);
    current_file = file_name;
    if (!file.open(QFile :: ReadOnly | QFile :: Text))
    {
        QMessageBox :: warning(this, "..", "File not open");
        return;
    }
    QFileInfo fi(file_name);
    setWindowTitle(fi.fileName());
    QTextStream in(&file);
    QString  text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString file_name;
    file_name = current_file;
    QFile file(file_name);
    if (!file.open(QFile :: WriteOnly | QFile :: Text))
    {
        QMessageBox :: warning(this, "..", "File not open");
        return;
    }
    QFileInfo fi(file_name);
    setWindowTitle(fi.fileName());
    QTextStream out(&file);
    QString  text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save As");
    QFile file(file_name);
    current_file = file_name;
    if (!file.open(QFile :: WriteOnly | QFile :: Text))
    {
        QMessageBox :: warning(this, "..", "File not open");
        return;
    }
    QFileInfo fi(file_name);
    setWindowTitle(fi.fileName());
    QTextStream out(&file);
    QString  text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

/*
void MainWindow::on_actionPrint_triggered()
{

}
*/

void MainWindow::on_actionExit_triggered()
{
    close();
}

