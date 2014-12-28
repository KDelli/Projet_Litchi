#ifndef POPUP_H
#define POPUP_H

#include "LanguageManagement/languageManagement.h"
#include "LanguageManagement/supportedLanguage.h"

#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>

class Popup : public QWidget
{
    public :
        explicit Popup(const QString joystickType, SupportedLanguage language, QGraphicsProxyWidget* popupProxy, const bool connected);
        ~Popup();

    private :
    void showEvent(QShowEvent*);

        QLabel constLabel;
        QLabel writableLabel;
        QLabel pict;

        QGraphicsProxyWidget* popupProxy;

        QGridLayout layout;

};
#endif
