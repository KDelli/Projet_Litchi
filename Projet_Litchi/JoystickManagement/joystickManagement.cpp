/*
#######################################################################################
#######################################################################################
###                                                                                 ###
###              This class use the SFML library. It's a threaded class             ###
###              who can be launcher on every other class as you need it.           ###
###              This class manage what happen when a joystick is connected         ###
###              or what happen when a joystick event is made                       ###
###                                                                                 ###
###              In each complexe function, you can found a summary                 ###
###              which explain the actions for the one you read                     ###
###                                                                                 ###
#######################################################################################
#######################################################################################
*/


#include "joystickManagement.h"

joystickManagement::joystickManagement()
{
    aSoftwareIsRunning = false;
    numberOfJoystickConnected = 0;
}
void joystickManagement::run()
{
    /*Summary :
    This function manage the joystick event.
    Every 50ms, this class is updated and  a signal
    corresponding on what happen is emited*/

    bool joystickConnected[4] = {false, false, false, false};
    bool buttonXPressed = false;
    bool buttonOPressed = false;
    int firstJoystickConnected = 0;

    int sleep = 0;

    for(; ;)
    {
        /*get joystick event*/
        sf::Joystick::update();

        if(!aSoftwareIsRunning)
        {
            /*Check if a new joystick is connected*/
            int i, x = 4;
            for(i = 0; i < x ; i++)
            {
                if(sf::Joystick::isConnected(i))
                {
                    if(!joystickConnected[i])
                    {
                        joystickConnected[i] = true;
                        numberOfJoystickConnected += 1;

                        emit newJoystickConnected();

                        msleep(50);
                        continue;
                    }
                }
                else
                { 
                    if(joystickConnected[i])
                    {
                        /*The joystick have been previously connected*/
                        joystickConnected[i] = false;
                        numberOfJoystickConnected -= 1;

                        emit theJoystickIsDisconnected();
                        getTheJoystickType();
                    }
                    msleep(50);
                    continue;
                }
            }

            int j;
            for(j = 0; j <= 4 ;j++)
            {
                if(joystickConnected[j])
                {
                    firstJoystickConnected = j;
                    break;
                }
            }

            /*button X*/
            if (sf::Joystick::isButtonPressed(firstJoystickConnected, 2))
            {
                if(!buttonXPressed)
                {
                    emit xButtonPressed();
                    buttonXPressed = true;
                }
            }
            /*Prevent fake multiuse*/
            else
            {
                buttonXPressed = false;
            }
            /*button O*/
            if (sf::Joystick::isButtonPressed(firstJoystickConnected, 3))
            {
                if(!buttonOPressed)
                {
                    emit oButtonPressed();
                    buttonOPressed = true;
                }
            }
            /*Prevent fake multiuse*/
            else
            {
                buttonOPressed = false;
            }

            /*Right button*/
            if (sf::Joystick::getAxisPosition(firstJoystickConnected,sf::Joystick::X) > 90)
            {
                emit onTheRight();
                msleep(175);
            }
            /*Left button*/
            if (sf::Joystick::getAxisPosition(firstJoystickConnected,sf::Joystick::X) < -90)
            {
                emit onTheLeft();
                msleep(175);
            }
            /*Top button*/
            if (sf::Joystick::getAxisPosition(firstJoystickConnected,sf::Joystick::Y) < -90)
            {
                emit toTheTop();
                msleep(175);
            }
            /*Bottom button*/
            if (sf::Joystick::getAxisPosition(firstJoystickConnected,sf::Joystick::Y) > 90)
            {
                emit toTheBottom();
                msleep(175);
            }

            msleep(50);
            continue;
        }
        else
        {
            if (sf::Joystick::isButtonPressed(firstJoystickConnected, startButton) && sf::Joystick::isButtonPressed(firstJoystickConnected, selectButton))
            {
                msleep(50);
                sleep += 50;

                if(sleep >= 1500)
                {
                    emit closeTheSoftware();
                }
            }
            else
            {
                sleep = 0;
                msleep(50);
            }
        }
    }
}

void joystickManagement::softwareMod(bool mod)
{
    aSoftwareIsRunning = mod;
}

QString joystickManagement::getTheJoystickType() /*Check the type of joystick connected*/
{
    QString returnJoystickType = "";
    joysticksType.clear();

    int i;
    for(i = 0; i < numberOfJoystickConnected; i++)
    {
        unsigned int axeCount = 0;

        sf::Joystick::update();

        unsigned int buttons = sf::Joystick::getButtonCount(i);


        if(sf::Joystick::hasAxis(i, sf::Joystick::R)) axeCount++;
        if(sf::Joystick::hasAxis(i, sf::Joystick::U)) axeCount++;
        if(sf::Joystick::hasAxis(i, sf::Joystick::V)) axeCount++;
        if(sf::Joystick::hasAxis(i, sf::Joystick::X)) axeCount++;
        if(sf::Joystick::hasAxis(i, sf::Joystick::Y)) axeCount++;
        if(sf::Joystick::hasAxis(i, sf::Joystick::Z)) axeCount++;
        if(sf::Joystick::hasAxis(i,sf::Joystick::PovX)) axeCount++;
        if(sf::Joystick::hasAxis(i,sf::Joystick::PovY)) axeCount++;



        if ((axeCount == 8 || axeCount == 6) && (buttons == 12 || buttons == 14))
        {
            returnJoystickType = "Playstation";
            joysticksType.push_back(Playstation);

            if(i == 0)
            {
                startButton = 8;
                selectButton = 9;
            }
        }
        else if (axeCount == 2 && buttons == 2)
        {
            returnJoystickType = "NES";
        }
        else if (axeCount == 2 && buttons == 4)
        {
            returnJoystickType = "SNES";
        }
        else if(axeCount == 8 && buttons == 11)
        {
            returnJoystickType = "XBox";
            joysticksType.push_back(XBox);

            if(i == 0)
            {
                startButton = 7;
                selectButton = 6;
            }
        }

        else
        {
            returnJoystickType = "Unknown";
        }
    }

    return returnJoystickType;
}

std::vector<JoystickType> joystickManagement::getJoystickConnected()
{
    return joysticksType;
}
