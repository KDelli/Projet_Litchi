#include "emulatorManagement.h"

EmulatorManagement::EmulatorManagement()
{
    composite = new EmulatorComposite;
}

void EmulatorManagement::checkEmulatorInstalled(const QString path)
{
    QDir dir(path + "/../Emulators");
    QStringList emulator = dir.entryList();

    if(emulator.contains("Nes"))
    {
        composite->add(new NesManagement());
    }

    if(emulator.contains("GBA"))
    {
        composite->add(new GBAMangement);
    }

    if(emulator.contains("N64"))
    {
        composite->add(new N64Management);
    }
}

void EmulatorManagement::configureTheEmulators(const QString path, std::vector<JoystickType> joysticksType)
{
    composite->configureEmulator(path, joysticksType);
}

void EmulatorManagement::checkTheRoms(const QString path)
{
    composite->checkRoms(path);
}

QString EmulatorManagement::getTheEmulatorChoosen(const QString emulatorChoosen)
{
    if(emulatorChoosen.compare("Nes") == 0)
    {
        return "fceux";
    }

    if(emulatorChoosen.compare("N64") == 0)
    {
        return "mupen64";
    }

    if(emulatorChoosen.compare("GBA") == 0)
    {
        return "boyca";
    }

    return "";
}
