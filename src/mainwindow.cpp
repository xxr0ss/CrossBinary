#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(binary_loaded()), this, SLOT(output_load_info()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    auto loader = BinaryLoader::getBinaryLoader();
    QString fname = QFileDialog::getOpenFileName(this, "Choose a binary file");

    if(fname.isNull())
        return;

    if(loader->load_binary(fname, Binary::BIN_TYPE_AUTO) != -1){
        emit binary_loaded();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QString about_content = QString::asprintf("Cross Binary %s, developed by PJX, build with Capstone engine and Qt", PROJECT_VER);
    QMessageBox::about(this, "About", about_content);
}

void MainWindow::output_load_info()
{
    using namespace std;
    auto loader = BinaryLoader::getBinaryLoader();
    auto &bin = loader->binary;
    cout << "filename: " << bin->filename << endl;

    string type_str;
    switch (bin->type)
    {
    case Binary::BIN_TYPE_ELF:
        type_str = "ELF";
        break;
    case Binary::BIN_TYPE_PE:
        type_str = "PE";
        break;
    default:
        type_str = "RAW";
    }

    cout << "type: " << type_str << endl;

    if (bin->bits == 32)
        printf("entry: 0x%I32X\n", (unsigned int)bin->entry);
    else if (bin->bits == 64)
        printf("entry: 0x%I64X\n", bin->entry);
}