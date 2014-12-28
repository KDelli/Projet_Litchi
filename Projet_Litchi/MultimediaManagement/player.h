#ifndef PLAYER_H
#define PLAYER_H

#include <vlc/vlc.h>

#include <QKeyEvent>
#include <QDir>

#ifdef Q_WS_X11
#include <QX11EmbedContainer>
#endif

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QWidget>
#endif

class QVBoxLayout;
class QPushButton;
class QTimer;
class QFrame;
class QSlider;

#define POSITION_RESOLUTION 10000

class Player : public QWidget
{
    Q_OBJECT

    public:
        Player();
        ~Player();

        void keyPressEvent(QKeyEvent* event);
        void playFile(const QString file);
        void togglePause();

    public slots:
        void updateInterface();


    signals:
        void exitThePlayer();

    private:
#ifdef Q_WS_X11
        QX11EmbedContainer *videoWidget;
#else
        QFrame *videoWidget;
#endif

        QTimer* poller;
        bool isPlaying;
        bool inPause;
        libvlc_instance_t* vlcInstance;
        libvlc_media_player_t* mediaPlayer;
        libvlc_media_t* media;
};

#endif
