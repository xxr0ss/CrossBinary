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
    auto loader = BinaryLoader::getBinaryLoader();
    QString fname = QFileDialog::getOpenFileName(this, "Choose a binary file");
    loader->load_binary(fname, Binary::BIN_TYPE_AUTO);
}

void MainWindow::on_actionAbout_triggered() {
    QString about_content = QString::asprintf("Cross Binary %s, developed by PJX, build with Capstone engine and Qt", PROJECT_VER);
    QMessageBox::about(this, "About", about_content);
}