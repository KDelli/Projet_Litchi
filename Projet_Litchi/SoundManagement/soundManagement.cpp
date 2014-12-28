#include "soundManagement.h"

SoundManagement::SoundManagement()
{
    soundMenu = new QSound(":/QSound/tick");
    game = new QSound(":/QSound/groovy.wav");

    mute = false;
}

void SoundManagement::playTheMoveSound()
{
    if(!mute)
    {
        soundMenu->play();
    }
}

void SoundManagement::playTheStartGameSound()
{
    if(!mute)
    {
        game->play();
    }
}

void SoundManagement::muteTheConsole(const bool onOrOff)
{
    mute = onOrOff;
}

SoundManagement::~SoundManagement()
{
    delete soundMenu;
    delete game;
}
