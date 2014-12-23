#include "popup.h"

Popup::Popup(QString joystickType, SupportedLanguage language, QGraphicsProxyWidget* popupProxy ,const bool connected)
{    
    LanguageManagement translator;
    QFont font("Arial", 11);

    if(connected)
    {
        constLabel.setText(translator.getTranslation(joystickType, language, "Popup"));
            constLabel.setFont(font);
        pict.setPixmap(QPixmap(":/QPopUp/connected"));
        writableLabel.setText(translator.getTranslation("Connected", language, "Popup"));
            writableLabel.setFont(font);

        layout.addWidget(&constLabel,       0, 1, 1, 1, Qt::AlignLeft);
        layout.addWidget(&writableLabel,    1, 1, 1, 1, Qt::AlignLeft);
        layout.addWidget(&pict,             0, 0, 2, 2, Qt::AlignLeft);
    }
    else
    {
        constLabel.setText(translator.getTranslation("Disconnected", language, "Popup"));
            constLabel.setFont(font);
        pict.setPixmap(QPixmap(":/QPopUp/disconnected"));

        layout.addWidget(&constLabel,       0, 1, 2, 2, Qt::AlignLeft);
        layout.addWidget(&pict,             0, 0, 2, 2, Qt::AlignLeft);
    }

    layout.setHorizontalSpacing(0);
    layout.setVerticalSpacing(0);

    this->popupProxy = popupProxy;
    this->popupProxy->setWidget(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setLayout(&layout);
    this->setFixedSize(300,90);

    this->setPalette(QPalette(QColor(223, 242, 255))); /*http://fr.wikipedia.org/wiki/Liste_de_couleurs*/
    this->setAutoFillBackground(true);
}

void Popup::showEvent(QShowEvent *)
{
    QTimer::singleShot(5500,this, SLOT(close()));
}

Popup::~Popup()
{
    /*If multiple popups shows only, the last one must hide the proxy*/
    if(this->popupProxy->widget() == this)
    {
        this->popupProxy->setWidget(NULL);
    }
}
