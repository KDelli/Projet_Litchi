#ifndef POPUP_H
#define POPUP_H

#include "LanguageManagement/languageManagement.h"
#include "LanguageManagement/supportedLanguage.h"

#include <QWidget>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>

class Popup : public QWidget
{
    public :
        explicit Popup(QString joystickType, SupportedLanguage language, const bool connected);
        ~Popup();

    private :
    void showEvent(QShowEvent*);

        QLabel constLabel;
        QLabel writableLabel;
        QLabel pict;

        QGridLayout layout;

};
#endif
