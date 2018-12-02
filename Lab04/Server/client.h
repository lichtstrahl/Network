#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QVariant>
#include <QTcpSocket>

const quint8 fields = 4;
const QStringList headers = QStringList() << "Name" << "Token" << "Upload File Progress" << "Files Loaded";

enum Field
{
    F_NAME,
    F_TOKEN,
    F_FILEPROGRESS,
    F_FILESLOADED
};

struct Client
{
    QString name;
    bool hasToken;
    bool pendingFile;
    quint64 fileProgress;
    quint8 filesLoaded;
    QTcpSocket *socket;

    Client &operator=(const Client &other)
    {
        name = other.name;
        hasToken = other.hasToken;
        pendingFile = other.pendingFile;
        fileProgress = other.fileProgress;
        filesLoaded = other.filesLoaded;
        socket = other.socket;

        return *this;
    }

    QString valueString(const Field field) const
    {
        switch(field)
        {
        case F_NAME:
            return name;

        case F_TOKEN:
            return hasToken ? "T" : "F";

        case F_FILESLOADED:
            return QString::number(filesLoaded);

        case F_FILEPROGRESS:
            return QString::number(fileProgress);
        }

        return "";
    }

    QVariant value(const Field field) const
    {
        switch(field)
        {
        case F_NAME:
            return name;

        case F_TOKEN:
            return hasToken;

        case F_FILESLOADED:
            return filesLoaded;

        case F_FILEPROGRESS:
            return fileProgress;
        }

        return QVariant();
    }

    void setValue(const Field field, const QVariant &value)
    {
        if (!value.isValid())
            return;

        switch(field)
        {
        case F_NAME:
            name = value.toString();
            break;

        case F_TOKEN:
            hasToken = value.toBool();
            break;

        case F_FILESLOADED:
            filesLoaded = static_cast<quint8>(value.toInt());
            break;

        case F_FILEPROGRESS:
            fileProgress = static_cast<quint8>(value.toInt());
        }
    }
};

#endif // CLIENT_H
