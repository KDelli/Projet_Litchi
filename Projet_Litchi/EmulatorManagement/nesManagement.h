#ifndef NESMANAGEMENT_H
#define NESMANAGEMENT_H

#include "IEmualtorManagement.h"

class NesManagement : public IEmulatorManagement
{

    public :
        NesManagement();

        void configureEmulator(const QString path, std::vector<JoystickType> joysticksType);
        void checkRoms(const QString path);
};

#endif
