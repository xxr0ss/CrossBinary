#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDockWidget>
#include "loader.h"
#include "output_handler.h"
#include "outputwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void binary_loaded();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionAbout_triggered();
    void output_load_info();

private:
    Ui::MainWindow *ui;

    QDockWidget *dock_output_window;
    OutputHandler* output_handler;

    void init_widgets();
};
#endif // MAINWINDOW_H
