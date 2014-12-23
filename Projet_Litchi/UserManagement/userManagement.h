#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "UserSettings.h"
#include "newUser.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QPainter>
#include <QDebug>


class UserManagement
{
    public:
        UserManagement();
        virtual ~UserManagement();

        void saveUserSettings(QString path, UserSettings* userToSave = nullptr);
        void createAvatar();
        bool createNewUser(QString path, NewUser* newUser);

        int getUserSex(QString path, QString name);

        UserSettings* loadUserSettings(QString path, QString name);
        UserSettings* getUserSettings();

    private :
        UserSettings* userSettings;

};

#endif
