#ifndef COMPOSITEPATTERN_H
#define COMPOSITEPATTERN_H


#include "IEmualtorManagement.h"

#include <vector>


class EmulatorComposite : IEmulatorManagement
{
    public :
        EmulatorComposite();

        void add(IEmulatorManagement* emulatorManagement);
        void configureEmulator(const QString path, std::vector<JoystickType> joysticksType);
        void checkRoms(const QString path);

    protected :
        std::vector <IEmulatorManagement*> children;
};






#endif
