#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered(){
    std::string fileName = QFileDialog::getOpenFileName(this, tr("Open a binary")).toStdString();
    Binary binary;
    load_binary(fileName, &binary, Binary::BIN_TYPE_AUTO);
}

void MainWindow::on_actionAbout_triggered() {
    QString about_content = QString::asprintf("Cross Binary %s, developed by PJX, build with Capstone engine and Qt", PROJECT_VER);
    QMessageBox::about(this, "About", about_content);
}