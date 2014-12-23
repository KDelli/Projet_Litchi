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


#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include "horizontalCarousel.h"
#include "verticalCarousel.h"
#include "variantAnimator.h"
#include "popup.h"
#include "Navigator/litchiNavigator.h"
#include "JoystickManagement/joystickManagement.h"
#include "EmulatorManagement/emulatorManagement.h"
#include "SoundManagement/soundManagement.h"
#include "UserManagement/UserSettings.h"
#include "UserManagement/userManagement.h"
#include "MenuCreator/menuCreator.h"
#include "MenuCreator/VMenuElement.h"
#include "MenuCreator/menuAction.h"
#include "RGB.h"
#include "UserManagement/loadAction.h"
#include "MultimediaManagement/player.h"
#include "LanguageManagement/languageManagement.h"
#include "LitchiKeyboard/litchiKeyboard.h"
#include "consoleModes.h"
#include "UserManagement/newUser.h"
#include "MenuCreator/actionType.h"

#include <QDesktopWidget>
#include <QGraphicsView>
#include <QtOpenGL/QGLWidget>
#include <QGraphicsProxyWidget>
#include <QListView>



class ConsoleIHM : public QGraphicsView
{
    Q_OBJECT

    public:
        ConsoleIHM();


    private :
        void onConnect();
        void keyPressEvent(QKeyEvent* event);
        void showEvent(QShowEvent*);
        void subFolderTextColorManagement();
        void subFolderAnimation(const MenuAction action);
        void resolutionManagement(const bool popup = false);
        void colorManagement();
        void setCarousel(const bool on);
        void setLogScreen(const bool on);
        void doAnim();
        void gameMode(const bool on);
        void videoMode(const bool on);
        void runTheEmulator(QString emulatorChoosen, QString romChoosen);
        void getAllTheThemes();
        void setNewTheme(LoadAction action);
        void getThemePosition(QString wallpaper = "", QString icon = "");
        void loadUserTheme();
        void setLanguage(SupportedLanguage language);
        void activateKeyboard(const bool on);
        void getRGB(int& preset, int& red, int& green, int& blue);
        QString getRGB(int& preset);
        void getFilesInFolder(QString path);
        void playTheVideo(QString path);
        void scallingManagement();
        void displayNewAvatar();


    private slots :
        void stop();

        /*Joystick events*/
        void joystickXButtonPressed();
        void joystickOButtonPressed();
        void joystickRightAxeUsed();
        void joystickLeftAxeUsed();
        void joystickTopAxeUsed();
        void joystickBottomAxeUsed();
        void joystickConnected();
        void joystickDisconnected();
        void closeTheSoftware();

        /*Keyboard events*/
        void newKeyPressed();
        void hideTheKeyboard();

        /*Player events*/
        void closeThePlayer();

    private:
    /*Item and variable of the main menu*/
    QGLWidget *viewPort;
    QGraphicsScene *scene;
        VerticalCarousel* mainMenuCarousel;
            QGraphicsPixmapItem* shutdownButton;
            QGraphicsPixmapItem* disconnectButton;
            QGraphicsPixmapItem* internetButton;
            QGraphicsPixmapItem* gameButton;
            QGraphicsPixmapItem* videoButton;
            QGraphicsPixmapItem* optionButton;
            QGraphicsPixmapItem* musicButton;

    QPixmap* shutdownImage;
    QPixmap* disconnectImage;
    QPixmap* internetImage;
    QPixmap* gameImage;
    QPixmap* videoImage;
    QPixmap* optionImage;
    QPixmap* musicImage;

        QGraphicsPixmapItem* wallpaper;
        QGraphicsTextItem* text;

        LanguageManagement translator;
        QString listOfName[7];

    /*LoginScreen*/
    HorizontalCarousel* logScreenMenuCarousel;
    QStringList listOfUserName;

    /*Current dir*/
    const QString currentWorkingDirectory = QDir::currentPath();

    /*JoystickManagement*/
    joystickManagement* joystick;
    QThread* joystickThread;

    /*Avatar*/
    QGraphicsPixmapItem* avatarRenderer;

    /*Popup*/
    Popup* notificationPopup;

    /*sound*/
    SoundManagement* soundManagement;

    /*Object for video*/
    Player* player;

    /*Object for emulators*/
    QProcess* emulator;
    EmulatorManagement* emulatorManagement;

    QDir emualtorDir;
    QDir romsDir;

    QStringListModel emulatorModel;
    QStringListModel dirModel;

    QListView emulatorsView;
    QListView dirView;

    QGraphicsProxyWidget* emulatorsProxy;
    QGraphicsProxyWidget* dirProxy;

    QAbstractItemModel* emulatorIndex;
    QAbstractItemModel* dirIndex;

    /*Keyboard*/
    QString* keyPressed;
    LitchiKeyboard* keyboard;
    QGraphicsProxyWidget* keyboardProxy;


    /*Object for internet navigation*/
    litchiNavigator* navigator;

    /*Object and variable of the sub-menu*/
    OMenuElement* optionMenuElements;
    IMenuElement* actualElement;
    QList<QGraphicsTextItem*> displayedElements;
    std::vector<int> subMenuPositionVector;

    /*Personnalisation*/
    QStringList listOfWallpaper;
    QStringList listOfIconTheme;
    QStringList listOfKeyboardType;

    UserSettings* userSettings;
    UserManagement* userManagement;
    NewUser* newUser;

    /*Console Mode*/
    ConsoleModes consoleMode;

    /*Boolean of the menu's statut*/
    bool endOfAnimation;
    bool firstListView;
    bool subFolderCreatorAlreadyCalled;
    bool keyboardActivated;
    bool videoIsPlaying;
    bool consoleAsBooted;
    bool gameIsLaunched;


    /*interger or float of the menu*/
    int rotationPosition;
    int subMenuPosition;
    int iconsNumber;

    qreal startAngle;
    qreal endAngle;
    qreal wWidth;
    qreal wHeight;
    qreal widthScalling;
    qreal heightScalling;

    /*integer for emulator*/
    int positionInEmulatorsView;
    int positionInDirView;
};

#endif
