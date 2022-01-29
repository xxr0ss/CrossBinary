#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      dock_output_window(nullptr)
{
    ui->setupUi(this);

    init_widgets();
    output_handler = OutputHandler::getOutputHandler();
    output_handler->attach_to_window((OutputWindow*)dock_output_window->widget());
    connect(this, SIGNAL(binary_loaded()), this, SLOT(output_load_info()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_widgets()
{
    dock_output_window = new QDockWidget("Output", this);
    dock_output_window->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock_output_window->setWidget(new OutputWindow(this));
    addDockWidget(Qt::TopDockWidgetArea, dock_output_window);
}

void MainWindow::on_actionOpen_triggered()
{
    auto loader = BinaryLoader::getBinaryLoader();
    QString fname = QFileDialog::getOpenFileName(this, "Choose a binary file");

    if (fname.isNull())
        return;

    if (loader->load_binary(fname, Binary::BIN_TYPE_AUTO) != -1)
    {
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

    output_handler->print(QString("fielname: %1").arg(QString::fromStdString(bin->filename)));

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

    output_handler->print(QString("type: %1").arg(QString::fromStdString(type_str)));

    output_handler->print(QString("bits: %1").arg(bin->bits));

    output_handler->print(QString("entry: 0x%1\n").arg(
        (qulonglong)(bin->entry), (int)bin->bits/8, 16, QChar('0')));
}