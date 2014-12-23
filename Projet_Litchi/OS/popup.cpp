#include "popup.h"

Popup::Popup(QString joystickType, SupportedLanguage language, const bool connected)
{    
    LanguageManagement translator;

    if(connected)
    {
        constLabel.setText(translator.getTranslation(joystickType, language, "Popup"));
        pict.setPixmap(QPixmap(":/QPopUp/connected"));
        writableLabel.setText(translator.getTranslation("Connected", language, "Popup"));

        layout.addWidget(&constLabel,       0, 2, 1, 1, Qt::AlignCenter);
        layout.addWidget(&writableLabel,    1, 2, 1, 1, Qt::AlignCenter);
        layout.addWidget(&pict,             0, 0, 2, 2, Qt::AlignCenter);
    }
    else
    {
        constLabel.setText(translator.getTranslation("Disconnected", language, "Popup"));
        pict.setPixmap(QPixmap(":/QPopUp/disconnected"));

        layout.addWidget(&constLabel,       0, 2, 2, 2, Qt::AlignCenter);
        layout.addWidget(&pict,             0, 0, 2, 2, Qt::AlignCenter);

        layout.setSpacing(0);
    }

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setLayout(&layout);
    this->setFixedSize(250,60);

    this->setPalette(QPalette(QColor(223, 242, 255))); /*http://fr.wikipedia.org/wiki/Liste_de_couleurs*/
    this->setAutoFillBackground(true);
}

void Popup::showEvent(QShowEvent *)
{
    QTimer::singleShot(3500,this, SLOT(close()));
}

Popup::~Popup()
{
}
