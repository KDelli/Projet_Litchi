#include "emulatorComposite.h"

EmulatorComposite::EmulatorComposite()
{
}

void EmulatorComposite::add(IEmulatorManagement *emulatorManagement)
{
    children.push_back(emulatorManagement); /*Add a new emulator to the composite Pattern*/
}

void EmulatorComposite::configureEmulator(QString path, std::vector<JoystickType> joysticksType)
{
    unsigned int i;

    for(i = 0; i < children.size() ; i++) /*For each emulator added*/
    {
        children[i]->configureEmulator(path, joysticksType);
    }
}

void EmulatorComposite::checkRoms(QString path)
{
    unsigned int i;

    for(i = 0; i < children.size() ; i++)
    {
        children[i]->checkRoms(path);
    }
}


