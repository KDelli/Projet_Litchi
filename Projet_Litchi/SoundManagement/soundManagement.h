#ifndef SOUNDMANAGEMENT_H
#define SOUNDMANAGEMENT_H


#if QT_VERSION >= 0x050000
#include <QtMultimedia/QSound>
#else
#include <QSound>
#endif

#include <QThread>

class SoundManagement
{    
    public :
        SoundManagement();
        virtual ~SoundManagement();
        
        void playTheMoveSound();
        void playTheStartGameSound();
        void muteTheConsole(const bool on);
        
    private :
        bool mute;

        QSound* soundMenu;
        QSound* game;
    
};
#endif
