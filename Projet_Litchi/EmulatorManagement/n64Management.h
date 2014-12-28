#ifndef N64MANAGEMENT_H
#define N64MANAGEMENT_H

#include "IEmualtorManagement.h"

#include <fstream>

class N64Management : public IEmulatorManagement
{

    public :
        N64Management();

        void configureEmulator(const QString path, std::vector<JoystickType> joysticksType);
        void checkRoms(const QString path);
};

#endif
