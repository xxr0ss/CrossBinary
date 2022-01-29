#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include <QObject>
#include <mutex>
#include "outputwindow.h"

class OutputHandler: public QObject
{
    Q_OBJECT
public:
    static OutputHandler* getOutputHandler();
    ~OutputHandler();
    void attach_to_window(OutputWindow* window);
    int print(QString msg);

    bool ready;

private:
    OutputHandler();
    static std::mutex _mutex;
    static OutputHandler* _instance;

    OutputWindow* outputwindow;
};

#endif /* OUTPUT_HANDLER_H */