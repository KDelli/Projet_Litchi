#ifndef GBAMANGEMENT_H
#define GBAMANGEMENT_H

#include "IEmualtorManagement.h"

#include <fstream>

class GBAMangement : public IEmulatorManagement
{

    public:
        GBAMangement();

        void configureEmulator(const QString path, std::vector<JoystickType> joysticksType);
        void checkRoms(const QString path);
};

#endif
