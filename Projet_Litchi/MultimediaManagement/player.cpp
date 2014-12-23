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
    /*preparation of the vlc command*/
    const char * const vlc_args[] = {
              "-I", "dummy", /* Don't use any interface */
              "--ignore-config", /* Don't use VLC's config */
              "--extraintf=logger", /*log anything*/
              "--verbose=2", /*be much more verbose then normal for debugging purpose*/
              "--plugin-path=C:\\vlc-0.9.9-win32\\plugins\\" };

#ifdef Q_WS_X11
    videoWidget=new QX11EmbedContainer(this);
#else
    videoWidget=new QFrame(this);
#endif
    /*[20101215 JG] If KDE is used like unique desktop environment, only use _videoWidget=new QFrame(this);*/
    isPlaying = false;
    inPause = false;

    //QVBoxLayout *layout = new QVBoxLayout;
        //layout->addWidget(videoWidget);

    //this->setLayout(layout);
    this->setStyleSheet("background-color: black");

    poller=new QTimer(this);
        connect(poller, SIGNAL(timeout()), this, SLOT(updateInterface()));
        poller->start(100);

    vlcInstance=libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);  /*tricky calculation of the char space used*/
    mediaPlayer = libvlc_media_player_new (vlcInstance);

    /*Fullscreen + FramelessWindow to hide bord;*/
    libvlc_set_fullscreen(mediaPlayer,true);
    setWindowFlags(Qt::FramelessWindowHint);
}

void Player::playFile(QString file)
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

    /* Create a new LibVLC media descriptor */
    media = libvlc_media_new_path(vlcInstance, file.toLatin1());

    libvlc_media_player_set_media (mediaPlayer, media);

    int windid = this->winId();//videoWidget->winId();
    libvlc_media_player_set_xwindow (mediaPlayer, windid);

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
    if(!isPlaying)
    {
        return;
    }

    /*It's possible that the vlc doesn't play anything
    so check before*/
    libvlc_media_t *curMedia = libvlc_media_player_get_media (mediaPlayer);

    if (curMedia == NULL)
    {
        return;
    }
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
