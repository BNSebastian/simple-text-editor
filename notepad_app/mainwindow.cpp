#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path_ = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
    // declare the file path
    QString file_name = QFileDialog::getOpenFileName(this, "open the file");
    // save the file path globaly to be used later
    file_path_ = file_name;
    // use the file path to open the file
    QFile file(file_name);


    // if file couldn't be opened, interupt the process
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "Couldn't open the file");
        return;
    }

    // save output of file to buffer
    QTextStream in(&file);
    // save buffer content to a string
    QString text = in.readAll();
    // set the content of the textEdit widget to that of the string
    ui->textEdit->setText(text);

    // close the file
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    // use the globaly defined file path to open the file
    QFile file(file_path_);

    // if the file doesn't exist, call save as function
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        MainWindow::on_actionSave_as_triggered();
    }

    // output buffer
    QTextStream out(&file);
    // save widget content to a string
    QString text = ui->textEdit->toPlainText();
    // save the widget content to the buffer
    out << text;

    // flush the buffer
    file.flush();
    // close the file
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    // declare the file path
    QString file_name = QFileDialog::getSaveFileName(this, "save the file");
    // declare the file path globaly
    file_path_ = file_name;
    // use the file path to open the file
    QFile file(file_name);

    // if file couldn't be opened, interupt the process
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "The file wasn't saved, try again");
        return;
    }

    // output buffer
    QTextStream out(&file);
    // save widget content to a string
    QString text = ui->textEdit->toPlainText();
    // save the widget content to the buffer
    out << text;

    // flush the buffer
    file.flush();
    // close the file
    file.close();
}

void MainWindow::on_actionFont_triggered()
{
    bool set;
    QFont font = QFontDialog::getFont(&set, this);
    if (set)
        ui->textEdit->setFont(font);
    else return;
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color");
    if (color.isValid())
        ui->textEdit->setTextColor(color);
}

void MainWindow::on_actionBackground_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color");
    if (color.isValid())
        ui->textEdit->setTextBackgroundColor(color);
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionAbout_me_triggered()
{
    QString about_text = "Author: Bucovala Sebastian-Nicu \nStack: This app was made using C++ and the Qt framework";
    QMessageBox::about(this, "About text app", about_text);
}

