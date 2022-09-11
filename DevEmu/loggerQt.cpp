#include "Misc/Logger.h"

#include <QDebug>


namespace logging {
    Log& Log::Instance() {
        static Log log;
        return log;
    }

    void Log::log(const std::string& str) {
        qDebug() << QString::fromStdString(str);
    }
}
