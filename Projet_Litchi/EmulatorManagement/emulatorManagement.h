#ifndef EMULATORMANAGEMENT_H
#define EMULATORMANAGEMENT_H

#include "emulatorComposite.h"
#include "nesManagement.h"
#include "gbaMangement.h"
#include "n64Management.h"

#include <QDir>

class EmulatorManagement
{

    public :
        EmulatorManagement();

        void checkEmulatorInstalled(QString path);
        void configureTheEmulators(QString path, std::vector<JoystickType> joysticksType);
        void checkTheRoms(QString path);

        QString getTheEmulatorChoosen(QString emulator);


    private :
        EmulatorComposite* composite;
};



#endif
