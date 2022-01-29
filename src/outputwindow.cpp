#include "outputwindow.h"
#include "ui_outputwindow.h"

OutputWindow::OutputWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputWindow)
{
    this->parent = parent;
    ui->setupUi(this);
}

OutputWindow::~OutputWindow()
{
    qDebug() << "outputwindow destroyed";
    delete ui;
}


QSize OutputWindow::sizeHint() const{
    return parent->size();
}

void OutputWindow::Output(QString &data) {
    ui->output_text->append(data);
}