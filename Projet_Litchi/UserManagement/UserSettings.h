#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include "LanguageManagement/supportedLanguage.h"

#include <QString>

class UserSettings
{
    public :
        UserSettings();
        virtual ~UserSettings();

        QString name;
        int* sex;

        QString wallpaperChoosen;
        QString iconThemeChoosen;

        SupportedLanguage language;

        int* wallpaperPosition;
        int* iconThemePosition;

        int* preSettedUnselectColor;
        int* redUnselect;
        int* greenUnselect;
        int* blueUnselect;

        int* presettedSelectColor;
        int* redSelect;
        int* greenSelect;
        int* blueSelect;

        int* keyboardBackgroundColor;
        int* keyboardSelectColor;
        int* keyboardUnselectColor;
        int* keyboardTypeSelected;

        int* hairChoosen;
        int* eyesChoosen;
        int* mouthChoosen;
        int* bodyChoosen;

        int* consoleMuted;

};

#endif
