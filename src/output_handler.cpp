#include "output_handler.h"

OutputHandler *OutputHandler::_instance = nullptr;
std::mutex OutputHandler::_mutex;

OutputHandler *OutputHandler::getOutputHandler()
{
    if (!_instance)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (!_instance)
        {
            _instance = new OutputHandler();
            return _instance;
        }
    }
    return _instance;
}

OutputHandler::OutputHandler() :
    ready(false),
    outputwindow(nullptr)
{
}

OutputHandler::~OutputHandler()
{
}

void OutputHandler::attach_to_window(OutputWindow* window) {
    outputwindow = window;
}

int OutputHandler::print(QString msg) {
    outputwindow->Output(msg);
    return 0;
}