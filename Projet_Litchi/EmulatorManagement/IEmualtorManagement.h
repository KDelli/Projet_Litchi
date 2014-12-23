#ifndef IEMUALTORMANAGEMENT_H
#define IEMUALTORMANAGEMENT_H

#include "JoystickManagement/joystickType.h"

#include <vector>
#include <QString>
#include <fstream>
#include <map>
#include <sstream>

class IEmulatorManagement
{

    public :
        virtual void configureEmulator(QString path, std::vector<JoystickType> joysticksType) = 0;
        virtual void checkRoms(QString path) = 0;

};

#endif
