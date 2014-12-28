#include "player.h"

#if QT_VERSION >= 0x050000
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QFrame>
#else
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QFrame>
#endif
#include <QTimer>



Player::Player()
: QWidget()
{
#ifdef Q_WS_X11
    videoWidget=new QX11EmbedContainer(this);
#else
    videoWidget=new QFrame(this);
#endif
    isPlaying = false;
    inPause = false;

    this->setStyleSheet("background-color: black");

    poller=new QTimer(this);
        connect(poller, SIGNAL(timeout()), this, SLOT(updateInterface()));
        poller->start(100);

    vlcInstance=libvlc_new(0, NULL);
    mediaPlayer = libvlc_media_player_new (vlcInstance);

    /*Fullscreen + FramelessWindow to hide bord;*/
    libvlc_set_fullscreen(mediaPlayer, true);
    setWindowFlags(Qt::FramelessWindowHint);
}

void Player::playFile(QString ofile)
{
    /*the file has to be in one of the following formats /perhaps a little bit outdated)

    [file://]filename              Plain media file
    http://ip:port/file            HTTP URL
    ftp://ip:port/file             FTP URL
    mms://ip:port/file             MMS URL
    screen://                      Screen capture
    [dvd://][device][@raw_device]  DVD device
    [vcd://][device]               VCD device
    [cdda://][device]              Audio CD device
    udp:[[<source address>]@[<bind address>][:<bind port>]]
    */        

    /*Prevent path problems*/
    QString file = ofile.replace('/','\\');

    /* Create a new LibVLC media descriptor */
    media = libvlc_media_new_path(vlcInstance, file.toLatin1());

    libvlc_media_player_set_media (mediaPlayer, media);

    libvlc_media_player_set_xwindow (mediaPlayer, reinterpret_cast<unsigned int>(videoWidget->winId()));

    /* Play */
    libvlc_media_player_play (mediaPlayer);
    isPlaying=true;
}

void Player::togglePause()
{
    if(!isPlaying)
    {
        return;
    }

    /*Resume if 0, pause if other*/
    if(inPause)
    {
        libvlc_media_player_set_pause(mediaPlayer, 0);
    }
    else
    {
        libvlc_media_player_set_pause(mediaPlayer, 1);
    }
    inPause = !inPause;
}

void Player::updateInterface()
{
}

void Player::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Backspace:
            this->togglePause();
            break;

        case Qt::Key_Escape:
            emit exitThePlayer();
            break;
    }
}

Player::~Player()
{
    /* Stop playing */
    libvlc_media_player_stop (mediaPlayer);

    /* Free the media_player */
    libvlc_media_player_release (mediaPlayer);

    libvlc_release (vlcInstance);
}
