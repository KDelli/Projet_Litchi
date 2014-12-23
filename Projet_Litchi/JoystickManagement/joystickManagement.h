/*
#######################################################################################
#######################################################################################
###                                                                                 ###
###                 If you want to know what happen on this class,                  ###
###                 please read the .cpp, everything is explained.                  ###
###                                                                                 ###
#######################################################################################
#######################################################################################
*/

#ifndef JOYSTICKMANAGEMENT_H
#define JOYSTICKMANAGEMENT_H

#include <QThread>
#include <string>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "joystickType.h"

class joystickManagement : public QThread
{
    Q_OBJECT

public :
    joystickManagement();
    void softwareMod(bool mod);
    QString getTheJoystickType();
    std::vector<JoystickType> getJoystickConnected();

signals :
    void newJoystickConnected();
    void theJoystickIsDisconnected();
    void xButtonPressed();
    void oButtonPressed();
    void onTheRight();
    void onTheLeft();
    void toTheTop();
    void toTheBottom();
    void closeTheSoftware();

private :
    std::vector<JoystickType> joysticksType;
    bool aSoftwareIsRunning;
    int numberOfJoystickConnected;
    int startButton;
    int selectButton;

protected :
    void run();

};

#endif
