QT       += core gui
QT       += opengl
QT       += webkitwidgets
QT       += network
QT       += multimedia

DEFINES += SFML_STATIC
#QMAKE_LFLAGS += -static-libgcc

INCLUDEPATH += D:/Dev/SFML-2.2/include
LIBS += -LD:/Dev/SFML-2.2/lib
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += D:/Dev/Vlc/include
LIBS += -LD:/Dev/Vlc/lib
LIBS += -llibvlc

QMAKE_CXXFLAGS += '-std=c++11'

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += webkit

TARGET = Projet_Litchi
TEMPLATE = app


SOURCES += main.cpp\
        Navigator/cookies.cpp \
        JoystickManagement/joystickManagement.cpp \
    OS/popup.cpp \
    OS/consoleIHM.cpp \
    SoundManagement/soundManagement.cpp \
    EmulatorManagement/n64Management.cpp \
    EmulatorManagement/gbaMangement.cpp \
    UserManagement/userManagement.cpp \
    UserManagement/userSettings.cpp \
    LanguageManagement/languageMangement.cpp \
    MenuCreator/VMenuElement.cpp \
    MultimediaManagement/player.cpp \
    UserManagement/newUser.cpp \
    EmulatorManagement/emulatorComposite.cpp \
    EmulatorManagement/emulatorManagement.cpp \
    EmulatorManagement/nesManagement.cpp \
    LitchiKeyboard/litchiKeyboard.cpp \
    MenuCreator/KMenuElement.cpp \
    MenuCreator/OMenuElement.cpp \
    OS/horizontalCarousel.cpp \
    OS/verticalCarousel.cpp \
    MenuCreator/abstractMenuElement.cpp \
    MenuCreator/menuCreator.cpp \
    Navigator/litchiNavigator.cpp \
    MenuCreator/RMenuElement.cpp \
    OS/abstractCarousel.cpp

HEADERS  += \
        Navigator/cookies.h \
        JoystickManagement/joystickManagement.h \
    OS/popup.h \
    EmulatorManagement/IEmualtorManagement.h \
    OS/consoleIHM.h \
    SoundManagement/soundManagement.h \
    EmulatorManagement/n64Management.h \
    EmulatorManagement/gbaMangement.h \
    UserManagement/UserSettings.h \
    UserManagement/userManagement.h \
    OS/languageManager.h \
    MenuCreator/menuAction.h \
    OS/RGB.h \
    UserManagement/loadAction.h \
    LanguageManagement/languageManagement.h \
    LanguageManagement/supportedLanguage.h \
    MenuCreator/VMenuElement.h \
    MenuCreator/IMenuElement.h \
    MultimediaManagement/player.h \
    OS/consoleModes.h \
    UserManagement/newUser.h \
    EmulatorManagement/emulatorComposite.h \
    EmulatorManagement/emulatorManagement.h \
    EmulatorManagement/nesManagement.h \
    LitchiKeyboard/litchiKeyboard.h \
    MenuCreator/KMenuElement.h \
    MenuCreator/OMenuElement.h \
    OS/horizontalCarousel.h \
    OS/verticalCarousel.h \
    OS/variantAnimator.h \
    MenuCreator/abstractMenuElement.h \
    MenuCreator/menuCreator.h \
    Navigator/litchiNavigator.h \
    MenuCreator/RMenuElement.h \
    MenuCreator/actionType.h \
    OS/abstractCarousel.h \
    JoystickManagement/joystickType.h

FORMS    +=

RESOURCES += \
    Resource/icons.qrc \
    Resource/sound.qrc \
    Resource/defaultTheme.qrc \
    Resource/menuCreator.qrc \
    Resource/language.qrc
