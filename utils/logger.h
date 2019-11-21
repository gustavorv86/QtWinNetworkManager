#ifndef LOGGER_H
#define LOGGER_H

#include <QDateTime>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>

class Logger {
private:
    const static QStringList LEVEL_NAMES;

    int logLevel;
    QFile * file;

    void write(const QString & message, int logLevel);

public:
    const static int LEVEL_DEBUG = 5;
    const static int LEVEL_INFO  = 4;
    const static int LEVEL_WARNING = 3;
    const static int LEVEL_ERROR = 2;
    const static int LEVEL_CRITICAL = 1;

    Logger();
    ~Logger();

    void setLogFile(const QString & filename);
    void setLogLevel(int logLevel);

    void debug(const QString & message);
    void info(const QString & message);
    void warning(const QString & message);
    void error(const QString & message);
    void critical(const QString & message);

    static Logger & getInstance() {
        static Logger SINGLETON;
        return SINGLETON;
    }
};

#endif // LOGGER_H
