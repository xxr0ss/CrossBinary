#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QWidget>

namespace Ui {
class OutputWindow;
}

class OutputWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OutputWindow(QWidget *parent = nullptr);
    ~OutputWindow();

    /* so that the mainwindow display the dock widget properly */
    QSize sizeHint() const override;

    void Output(QString &data);

private:
    Ui::OutputWindow *ui;

    QWidget *parent;
};

#endif // OUTPUTWINDOW_H
