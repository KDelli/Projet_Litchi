#ifndef MENUCREATOR_H
#define MENUCREATOR_H

#include <QString>

#include "LanguageManagement/languageManagement.h"
#include "LanguageManagement/supportedLanguage.h"
#include "OMenuElement.h"
#include "VMenuElement.h"
#include "UserManagement/UserSettings.h"
#include "UserManagement/newUser.h"
#include "QStringList"

enum creationOption
{
    menuOption
};

class MenuCreator
{
public:
    MenuCreator();
    OMenuElement* createNewMenu(UserSettings* userSettings, NewUser* newUser, QStringList colorList, QStringList keyboardColorList, QStringList listOfKeyboardType, QStringList listOfSupportedLanguages, QStringList iconList, QStringList wallpaperList, QStringList mutedOrNot, QStringList listOfSex, SupportedLanguage language);
};

#endif
