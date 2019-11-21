#include "logger.h"

const QStringList Logger::LEVEL_NAMES = {"", "CRITICAL", "ERROR", "WARNING", "INFORMATION", "DEBUG"};

Logger::Logger() {
    this->logLevel = Logger::LEVEL_INFO;
    this->file = nullptr;
}

void Logger::moveFile(const QString & source, const QString & destination) {
	if(QFile::exists(destination)) {
		QFile::remove(destination);
	}
	QFile::rename(source, destination);
}

void Logger::setLogFile(const QString & filename) {
    if (!filename.isEmpty()) {

		for(int i=NUMBER_OF_BACKUPS; i>0; i--) {
			QString fOrig(filename + "." + QString::number(i-1));
			QString fDest(filename + "." + QString::number(i));
			if(QFile::exists(fOrig)) {
				this->moveFile(fOrig, fDest);
			}
		}

		if(QFile::exists(filename)) {
			this->moveFile(filename, filename + ".1);
		}

        file = new QFile;
        file->setFileName(filename);
        file->open(QIODevice::Append | QIODevice::Text);
    }
}

void Logger::setLogLevel(int logLevel) {
    this->logLevel = logLevel;
}

void Logger::write(const QString & message, int logLevel) {
    if(logLevel <= this->logLevel) {
        QString datetime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
        QString text = datetime + " [" + Logger::LEVEL_NAMES[logLevel] + "] " + message + "\n";

        if(file != nullptr) {
            QTextStream out(file);
            out.setCodec("UTF-8");
            out << text;
        } else {
            std::cout << text.toStdString();
        }
    }
}

void Logger::debug(const QString & message) {
    this->write(message, Logger::LEVEL_DEBUG);
}

void Logger::info(const QString & message) {
    this->write(message, Logger::LEVEL_INFO);
}

void Logger::warning(const QString & message) {
    this->write(message, Logger::LEVEL_WARNING);
}

void Logger::error(const QString & message) {
    this->write(message, Logger::LEVEL_ERROR);
}

void Logger::critical(const QString & message) {
    this->write(message, Logger::LEVEL_CRITICAL);
}

Logger::~Logger() {
    if (file != nullptr) {
        file->close();
    }
}
