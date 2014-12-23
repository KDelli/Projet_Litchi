/* Read me !
#######################################################################################
#######################################################################################
###                                                                                 ###
###              This class create the IHM for the video-game console.              ###
###              In this class, you'll found all the function making                ###
###              the IHM move, react or displaying what you actually see            ###
###                                                                                 ###
###              In each complexe function, you can found a summary                 ###
###              which explain the actions for the one you read                     ###
###                                                                                 ###
#######################################################################################
#######################################################################################
*/

#include "consoleIHM.h"

/*Functions for graphicals actions*/
ConsoleIHM::ConsoleIHM()
{
    /*Summary :
    This is the constructor of the class. It
    actually instanciate all the objects for
    the class*/


    /*Init of variable*/
    endOfAnimation = true;
    firstListView = true;
    subFolderCreatorAlreadyCalled = false;
    keyboardActivated = false;
    videoIsPlaying = false;
    consoleAsBooted = false;
    gameIsLaunched = false;
    rotationPosition = 0;
    subMenuPosition = 0;
    iconsNumber = 0;
    wWidth = 0;
    widthScalling = 1;
    wHeight = 0;
    heightScalling = 1;
    positionInEmulatorsView = 0;
    positionInDirView = 0;

    /*Focus*/
    qApp->installEventFilter(this);

    /*User settings*/
    userManagement = new UserManagement();
    newUser = new NewUser();

    userSettings = userManagement->getUserSettings();
        userSettings->name = "Guest";

    /*Sound management*/
    soundManagement = new SoundManagement;

    /*joystick management thread*/
    joystick = new joystickManagement;
        joystick->start();
        connect(joystick, SIGNAL(xButtonPressed()), this, SLOT(joystickXButtonPressed()));
        connect(joystick, SIGNAL(oButtonPressed()), this, SLOT(joystickOButtonPressed()));
        connect(joystick, SIGNAL(onTheRight()), this, SLOT(joystickRightAxeUsed()));
        connect(joystick, SIGNAL(onTheLeft()), this, SLOT(joystickLeftAxeUsed()));
        connect(joystick, SIGNAL(toTheTop()), this, SLOT(joystickTopAxeUsed()));
        connect(joystick, SIGNAL(toTheBottom()), this, SLOT(joystickBottomAxeUsed()));
        connect(joystick, SIGNAL(newJoystickConnected()), this, SLOT(joystickConnected()));
        connect(joystick, SIGNAL(theJoystickIsDisconnected()), this, SLOT(joystickDisconnected()));
        connect(joystick, SIGNAL(closeTheSoftware()), this, SLOT(closeTheSoftware()));


    /*Description of the current icon of the main menu*/
    text = new QGraphicsTextItem;
        text->setScale(4);

    /*Text for sub-menu*/
    listOfKeyboardType << "azerty";
    listOfKeyboardType << "qwerty";
    getAllTheThemes();

    actualElement = nullptr;

    /*Main-menu icon*/
    shutdownImage = new QPixmap;
    disconnectImage = new QPixmap;
    internetImage = new QPixmap;
    gameImage = new QPixmap;
    videoImage = new QPixmap;
    optionImage = new QPixmap;
    musicImage = new QPixmap;

    shutdownButton = new QGraphicsPixmapItem;
        shutdownButton->setPixmap(*shutdownImage);
    disconnectButton = new QGraphicsPixmapItem;
        disconnectButton->setPixmap(*disconnectImage);
    gameButton = new QGraphicsPixmapItem;
        gameButton->setPixmap(*gameImage);
    musicButton = new QGraphicsPixmapItem;
        musicButton->setPixmap(*musicImage);
    internetButton = new QGraphicsPixmapItem;
        internetButton->setPixmap(*internetImage);
    videoButton = new QGraphicsPixmapItem;
        videoButton->setPixmap(*videoImage);
    optionButton = new QGraphicsPixmapItem;
        optionButton->setPixmap(*optionImage);
    wallpaper = new QGraphicsPixmapItem;

    /*Avatar*/
    avatarRenderer = new QGraphicsPixmapItem;

    /*For the emulator*/
    emulatorManagement = new EmulatorManagement();

    emualtorDir = this->currentWorkingDirectory + "/../Emulators/";
    emulatorModel.setStringList(emualtorDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name));
        emulatorsView.setModel(&emulatorModel);
        emulatorsView.setFixedSize(550,750);
        emulatorsView.setSelectionMode(QAbstractItemView::ExtendedSelection);
        emulatorsView.setFont(QFont("Arial",30));

    emulatorsProxy = new QGraphicsProxyWidget;
        emulatorsProxy->setWidget(&emulatorsView);

    emulatorIndex = emulatorsView.model();

    /*Keyboard*/
    keyboardProxy = new QGraphicsProxyWidget;
    keyPressed = new QString();
    keyboard = new LitchiKeyboard(keyPressed);
        connect(keyboard, SIGNAL(aNewKeyIsPressed()), this, SLOT(newKeyPressed()));
        connect(keyboard, SIGNAL(hideTheKeyboard()), this, SLOT(hideTheKeyboard()));
        keyboardProxy->setWidget(keyboard);
        keyboardProxy->setFlag(QGraphicsItem::ItemIsFocusable, true);


    /*Emulator view*/
    dirView.setModel(&dirModel);
    dirView.setFixedSize(550,750);
    dirView.setSelectionMode(QAbstractItemView::ExtendedSelection);
    dirView.setFont(QFont("Arial",23));

    dirProxy = new QGraphicsProxyWidget;
        dirProxy->setWidget(&dirView);
        dirIndex = dirView.model();


    /*Creation of the window*/
    viewPort = new QGLWidget;
    scene = new QGraphicsScene();
        scene->addItem(wallpaper);
        scene->addItem(optionButton);
        scene->addItem(disconnectButton);
        scene->addItem(shutdownButton);
        scene->addItem(internetButton);
        scene->addItem(musicButton);
        scene->addItem(videoButton);
        scene->addItem(gameButton);
        scene->addItem(text);

    this->setViewport(viewPort);
    this->setScene(scene);

    this->setGeometry(QApplication::desktop()->screenGeometry()); /*make scene go with the full resolution*/

    this->setStyleSheet("QGraphicsScene { border-style: none; }");
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );


    /*Creation of the main menu carousel*/
    mainMenuCarousel = new VerticalCarousel(350,(double)550,(double)50,0);
        mainMenuCarousel->addToGroup(disconnectButton);
        mainMenuCarousel->addToGroup(shutdownButton);
        mainMenuCarousel->addToGroup(gameButton);
        mainMenuCarousel->addToGroup(musicButton);
        mainMenuCarousel->addToGroup(internetButton);
        mainMenuCarousel->addToGroup(videoButton);
        mainMenuCarousel->addToGroup(optionButton);
}
void ConsoleIHM::showEvent(QShowEvent*)
{
    /*Summary :
    What happen when the IHM show up for the
    first time*/

    setNewTheme(NewTheme);

    //this->showFullScreen();

    scallingManagement();
    this->fitInView(wallpaper);

    setLogScreen(true);
    consoleAsBooted = true;
}
void ConsoleIHM::onConnect()
{
    userSettings->name = listOfUserName.at(rotationPosition);
    listOfUserName.clear();
    loadUserTheme();
    setLanguage(userSettings->language);
    optionMenuElements->actualizeContent(true);

    iconsNumber = 7;
    rotationPosition = 0;
    startAngle = 0;
    endAngle = 90;
    emulatorManagement->checkEmulatorInstalled(this->currentWorkingDirectory);

    setLogScreen(false);
}
void ConsoleIHM::setCarousel(const bool on)
{
    if(on)
    {
        scene->addItem(mainMenuCarousel);
        scene->addItem(text);
        resolutionManagement();
    }
    else
    {
        scene->removeItem(mainMenuCarousel);
        scene->removeItem(text);
    }

}
void ConsoleIHM::setLogScreen(const bool on)
{
    scene->removeItem(text);
    if(on)
    {
        logScreenMenuCarousel = new HorizontalCarousel(350,(double)550, (double)50,0);
        if(consoleAsBooted)
        {
            setNewTheme(NewTheme);
        }
        rotationPosition = 0;
        startAngle = 0;
        endAngle = 90;

        scene->addItem(text);
        consoleMode = LoginScreen;

        QDir dir;
        dir = this->currentWorkingDirectory + "/../users/";
        listOfUserName = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
        int numberOfUsers = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name).count();
        int i;

        if(listOfUserName.count() < 1)
        {
            qWarning() << "Warning : No users have been found";
        }

        iconsNumber = numberOfUsers;

        for(i = numberOfUsers - 1 ; i >= 0 ; i--)
        {
            QGraphicsPixmapItem *user = new QGraphicsPixmapItem;

            QString loginPicturePath = this->currentWorkingDirectory + "/../users/" + listOfUserName.at(i) + "/LogPicture.png";
            if(QFile(loginPicturePath).exists())
            {
                user->setPixmap(QPixmap(loginPicturePath));
            }
            else
            {
                int sexOfUser = userManagement->getUserSex(this->currentWorkingDirectory, listOfUserName.at(i));

                switch(sexOfUser)
                {
                    case 0 :
                    {
                        user->setPixmap(QPixmap(":/QDefault/noPictureMan"));
                        break;
                    }

                    case 1 :
                    {
                        user->setPixmap(QPixmap(":/QDefault/noPictureWoman"));
                        break;
                    }

                    case 2 :
                    {
                        user->setPixmap(QPixmap(":/QDefault/noPictureOther"));
                        break;
                    }

                    default :
                        break;
                }
            }

            logScreenMenuCarousel->addToGroup(user);
        }

        doAnim();
        scene->addItem(logScreenMenuCarousel);
        logScreenMenuCarousel->setTransform(QTransform().translate(0, 0).scale(widthScalling, heightScalling).translate(0, 0));
        resolutionManagement();
    }
    else
    {
        scene->removeItem(logScreenMenuCarousel);
        delete logScreenMenuCarousel;

        consoleMode = MainMenu;
        setCarousel(true);
        doAnim();
    }
}

void ConsoleIHM::resolutionManagement(const bool popup)
{
    /*Summary :
    Function which manage the actual resolution of the screen

    What happen : This function take the actual width and height
    of the screen, then make somes calculs for knowing what type
    a screen it is (4:3,16:9,16:10). Then, place the carousel
    and the text at the place when their belong

    Arg : The boolean said if the function had to manage
    the IHM for the menu or the sub menus
    */

    if(popup)
    {
        notificationPopup->move(wWidth*0.75, wHeight*0.10);
        return;
    }

    if(keyboardActivated)
    {
        keyboardProxy->setX(wWidth*0.3);
        keyboardProxy->setY(wHeight*0.6);
    }

    switch(consoleMode)
    {
        case LoginScreen:
        {
            logScreenMenuCarousel->setX(wWidth*0.46);
            logScreenMenuCarousel->setY(wHeight*0.23);
            text->setPos(wWidth*0.436,wHeight*0.47);

            QString userName = listOfUserName.at(rotationPosition);
            int size = userName.size();
            if (size <= 5)
            {
                return;
            }
            qreal newPlace = -(size-5)*widthScalling*11;
            text->moveBy(newPlace,0);
            break;
        }

        case MainMenu:
        {
            mainMenuCarousel->setX(wWidth*0.3);
            mainMenuCarousel->setY(wHeight*0.47);
            text->setPos(wWidth*0.55,wHeight*0.50);
            break;
        }

        case SubMenu:
        {
            mainMenuCarousel->setX(wWidth*0.05);
            mainMenuCarousel->setY(wHeight*0.47);
            text->setPos(wWidth*0.30,wHeight*0.50);

            int numberOfLine = displayedElements.count();

            qreal freeSpace = wHeight*0.8;
            qreal spaceBeetweenLine = freeSpace/(numberOfLine-1);

            int i;
            qreal wWidthPosition = wWidth*0.55;
            qreal wHeightPosition = wHeight*0.05;
            for(i = 0; i < numberOfLine; i++)
            {
                QGraphicsTextItem *currentSubFolder = displayedElements.at(numberOfLine-(i+1));
                currentSubFolder->setPos(wWidthPosition, wHeightPosition + (i*spaceBeetweenLine) );
            }
            break;
        }

        case ChangeAvatarIHM:
        {
            avatarRenderer->setX(wWidth*0.45);
            avatarRenderer->setY(wHeight*0.3);

            int numberOfLine = displayedElements.count();

            float freeSpace = wHeight*0.7;
            float spaceBeetweenLine = freeSpace/(numberOfLine-1);

            int i;
            qreal wWidthPosition = wWidth*0.05;
            qreal wHeightPosition = wHeight*0.15;
            for(i = 0; i < numberOfLine; i++)
            {
                QGraphicsTextItem *currentSubFolder = displayedElements.at(numberOfLine-(i+1));

                if(i == numberOfLine-1)
                {
                    currentSubFolder->setPos(wWidth*0.33, wHeight*0.15 + (i*spaceBeetweenLine) );
                }
                else
                {
                    currentSubFolder->setPos(wWidthPosition, wHeightPosition + (i*spaceBeetweenLine) );
                }
            }
            break;
        }

        case Videoing:
        {
            dirProxy->setX(wWidth*0.1);
            dirProxy->setY(wHeight*0.05);
            break;
        }

        case Gaming:
        {
            emulatorsProxy->setX(wWidth*0.1);
            emulatorsProxy->setY(wHeight*0.05);

            dirProxy->setX(wWidth*0.5);
            dirProxy->setY(wHeight*0.05);
            break;
        }

        default:
            break;
    }
}
void ConsoleIHM::scallingManagement()
{

    wWidth = this->width();
    wHeight = this->height();

    widthScalling = wWidth/wallpaper->boundingRect().width();
    heightScalling = wHeight/wallpaper->boundingRect().height();

    wallpaper->setTransform(QTransform().translate(0, 0).scale(widthScalling, heightScalling).translate(0, 0));

    scene->setSceneRect(scene->sceneRect());
    this->setSceneRect(scene->sceneRect());

    if ((widthScalling == 1) && (heightScalling == 1))
    {
        return;
    }

    /*If we are not in a 16:9 shape, there'll be some disformation
    So we had to revert it*/
    qreal ratio = wWidth/wHeight;
    if(ratio <= 1.75 || ratio >= 1.8)
    {
        qreal tempWidthScalling = widthScalling;
        widthScalling = widthScalling*heightScalling*1.5;
        heightScalling = heightScalling * tempWidthScalling*1.5;
    }

    /*In the first time, we rescale normally*/
    mainMenuCarousel->setTransform(QTransform().translate(0, 0).scale(widthScalling, heightScalling).translate(0, 0));
    text->setTransform(QTransform().translate(0, 0).scale(widthScalling, heightScalling).translate(0, 0));

    /*TODO => Fin a way to scale*/
    //avatarRenderer->scale(2*widthScalling,2*heightScalling);

    //dirProxy->scale(widthScalling,heightScalling);
    //emulatorsProxy->scale(widthScalling,heightScalling);
    //keyboardProxy->scale(widthScalling,heightScalling);
}
void ConsoleIHM::subFolderAnimation(const MenuAction action)
{
    /*Summary :
    This function move the carousel in order to
    display or hide the sub-menu items*/

        if(displayedElements.count() > 0)
        {
            int i;

            for(i = 0; i < displayedElements.count(); i++)
            {
                QGraphicsTextItem *currentElement = displayedElements.at(i);
                scene->removeItem(currentElement);
            }
            displayedElements.clear();
        }

        switch(action)
        {
            case DisplayThis:
                break;

            case DisplayChildren:
                    actualElement = actualElement->getChild(subMenuPosition);
                    if(actualElement->countChildren() == 0 )
                    {
                        return;
                    }
                    subMenuPositionVector.push_back(subMenuPosition);
                    subMenuPosition = 0;
                    break;

            case DisplayParent:
                if(!actualElement->hasParent())
                {
                    consoleMode = MainMenu;
                    resolutionManagement();

                    /*We save only when we have finish*/
                    userManagement->saveUserSettings(this->currentWorkingDirectory);
                    subMenuPosition = 0;
                    return;
                }
                actualElement = actualElement->getParentMenu();
                subMenuPosition = subMenuPositionVector.back();
                subMenuPositionVector.pop_back();
                break;
        }

        int numberOfChildren = actualElement->countChildren() - 1;
        if(numberOfChildren == 0)
        {
            return;
        }

        int i;
        for(i = 0; i <= numberOfChildren; i++)
        {
            IMenuElement* currentChild = actualElement->getChild(i);

            QGraphicsTextItem *currentTextMenu = new QGraphicsTextItem;
                currentTextMenu->setScale(4);
                currentTextMenu->setPlainText( currentChild->returnContent() + currentChild->returnSubsidiaryContent());
                currentTextMenu->setTransform(QTransform().translate(0, 0).scale(widthScalling, heightScalling).translate(0, 0));

            scene->addItem(currentTextMenu);
            displayedElements.push_front(currentTextMenu);
        }

        resolutionManagement();
        subFolderTextColorManagement();
}
void ConsoleIHM::subFolderTextColorManagement()
{
    /*Summary :
    This function color the actual sub-menu line
    choosen.*/

    int i;
    int numberOfChild = displayedElements.count()-1;
    for(i = 0; i < displayedElements.count(); i++)
    {
        QGraphicsTextItem *currentSubFolder = displayedElements.at(numberOfChild-i);

        if(i == subMenuPosition)
        {
            currentSubFolder->setDefaultTextColor(QColor(*userSettings->redSelect,*userSettings->greenSelect,*userSettings->blueSelect));
        }
        else
        {
            currentSubFolder->setDefaultTextColor(QColor(*userSettings->redUnselect,*userSettings->greenUnselect,*userSettings->blueUnselect));
        }
    }
}
void ConsoleIHM::colorManagement()
{
    int i;
    int* preset,*red,*green,*blue;
    for(i = 0; i < 3; i++)
    {
        if(i == 0)
        {
            preset = userSettings->presettedSelectColor;
            red = userSettings->redSelect;
            green = userSettings->greenSelect;
            blue = userSettings->blueSelect;
        }
        else if(i == 1)
        {
            preset = userSettings->preSettedUnselectColor;
            red = userSettings->redUnselect;
            green = userSettings->greenUnselect;
            blue = userSettings->blueUnselect;
        }
        else
        {
            QString background = getRGB(*userSettings->keyboardBackgroundColor);
            QString select = getRGB(*userSettings->keyboardSelectColor);
            QString unselect = getRGB(*userSettings->keyboardUnselectColor);

            keyboard->setNewTheme(background, select, unselect);
            return;
        }
        getRGB(*preset, *red, *green, *blue);
    }
}
QString ConsoleIHM::getRGB(int &preset)
{
    switch(preset)
    {
        case 0 : /*White*/
            return "white";
            break;

        case 1 : /*Black*/
            return "black";
            break;

        case 2 : /*Red*/
            return "red";
            break;

        case 3 : /*Green*/
            return "green";
            break;

        case 4 : /*Blue*/
            return "blue";
            break;

        case 5 : /*Pink*/
            return "pink";
            break;

        case 6 : /*Yellow*/
            return "yellow";
            break;

        case 7 : /*Orange*/
            return "orange";
            break;

        case 8 : /*Brown*/
            return "brown";
            break;

        case 9 : /*Purple*/
            return "purple";
            break;

        case 10 : /*Gray*/
            return "gray";
            break;

        default :
            break;
    }

    return "fail";
}
void ConsoleIHM::getRGB(int &preset, int &red, int &green, int &blue)
{
    switch(preset)
    {
        case 0 : /*White*/
            red = 255;
            green = 255;
            blue = 255;
            break;

        case 1 : /*Black*/
            red = 0;
            green = 0;
            blue = 0;
            break;

        case 2 : /*Red*/
            red = 219;
            green = 23;
            blue = 2;
            break;

        case 3 : /*Green*/
            red = 58;
            green = 157;
            blue = 35;
            break;

        case 4 : /*Blue*/
            red = 38;
            green = 97;
            blue = 156;
            break;

        case 5 : /*Pink*/
            red = 218;
            green = 112;
            blue = 214;
            break;

        case 6 : /*Yellow*/
            red = 255;
            green = 203;
            blue = 96;
            break;

        case 7 : /*Orange*/
            red = 231;
            green = 62;
            blue = 1;
            break;

        case 8 : /*Brown*/
            red = 139;
            green = 108;
            blue = 66;
            break;

        case 9 : /*Purple*/
            red = 150;
            green = 131;
            blue = 236;
            break;

        case 10 : /*Gray*/
            red = 121;
            green = 128;
            blue = 129;
            break;

        default :
            break;
    }
}

/*Personalisation*/
void ConsoleIHM::getAllTheThemes()
{
    QDir dir;

    dir = this->currentWorkingDirectory + "/../themes/Wallpapers";
    QStringList listOfWallpaperWithExt = dir.entryList(QDir::Files | QDir::NoDot, QDir::Name);

    if(listOfWallpaperWithExt.count() == 0)
    {
        qWarning() << "There is no wallpaper present in your wallpapers directory";
    }

    foreach(QString fWallpaper, listOfWallpaperWithExt)
    {
        int size = fWallpaper.size();

        listOfWallpaper.push_back(fWallpaper.remove(size-4,4));
    }

    dir = this->currentWorkingDirectory + "/../themes/Icons";
    listOfIconTheme = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);

    if(listOfIconTheme.count() == 0)
    {
        qWarning() << "There is no icon theme present in your icons theme directory";
    }
}
void ConsoleIHM::setNewTheme(LoadAction action)
{
    if(action != NewTheme)
    {
        colorManagement();
    }
    else
    {
        userSettings->wallpaperChoosen = "";
        userSettings->iconThemeChoosen = "";

        getThemePosition("chooseyourlitchi", "Theme Litchi");

        *userSettings->presettedSelectColor = 2;
        *userSettings->redSelect = 219;
        *userSettings->greenSelect = 23;
        *userSettings->blueSelect = 3;

        *userSettings->preSettedUnselectColor = 1;
        *userSettings->redUnselect = 0;
        *userSettings->greenUnselect = 0;
        *userSettings->blueUnselect = 0;
    }

    QString wallpaperChoosen;
    bool wallpaperNotFound = false;
    if(*userSettings->wallpaperPosition != -1)
    {
        wallpaperChoosen = listOfWallpaper.at(*userSettings->wallpaperPosition);
    }
    else
    {
        if(action == NewTheme)
        {
            wallpaperChoosen = ":/QDefault/ChooseYourLitchi";
        }
        else
        {
            wallpaperChoosen = ":/QDefault/LitchiChili";
        }
        wallpaperNotFound = true;
    }
    QString previousWallpaper = userSettings->wallpaperChoosen;

    if(previousWallpaper != wallpaperChoosen)
    {
        QString wallpaperPath = this->currentWorkingDirectory + "/../Themes/Wallpapers/";
        userSettings->wallpaperChoosen = wallpaperChoosen;

        if(!wallpaperNotFound)
        {
            wallpaper->setPixmap(QPixmap(wallpaperPath + wallpaperChoosen + ".jpg"));
        }
        else
        {
            wallpaper->setPixmap(QPixmap(wallpaperChoosen));
        }


        qreal wallpaperWidthScalling = wWidth/wallpaper->boundingRect().width();
        qreal wallpaperHeightScalling = wHeight/wallpaper->boundingRect().height();
        wallpaper->setTransform(QTransform().translate(0, 0).scale(wallpaperWidthScalling, wallpaperHeightScalling).translate(0, 0));
    }

    QString iconChoosen;
    bool iconNotFounded = false;
    if(*userSettings->iconThemePosition != -1)
    {
        iconChoosen = listOfIconTheme.at(*userSettings->iconThemePosition);
    }
    else
    {
        iconChoosen = ":/QDefault/";
        iconNotFounded = true;
    }

    QString previousIconTheme = userSettings->iconThemeChoosen;
    if(previousIconTheme != iconChoosen)
    {
        QString iconsPath = this->currentWorkingDirectory + "/../Themes/Icons/";
        userSettings->iconThemeChoosen = iconChoosen;

        if(!iconNotFounded)
        {
            shutdownImage->load(iconsPath + iconChoosen + "/shutdown.png");
            disconnectImage->load(iconsPath + iconChoosen + "/disconnect.png");
            optionImage->load(iconsPath + iconChoosen + "/settings.png");
            gameImage->load(iconsPath + iconChoosen + "/games.png");
            videoImage->load(iconsPath + iconChoosen + "/videos.png");
            musicImage->load(iconsPath + iconChoosen + "/musics.png");
            internetImage->load(iconsPath + iconChoosen + "/internet.png");
        }
        else
        {
            shutdownImage->load(":/QDefault/Shutdown");
            disconnectImage->load(":/QDefault/Disconnect");
            optionImage->load(":/QDefault/Settings");
            gameImage->load(":/QDefault/Games");
            videoImage->load(":/QDefault/Videos");
            musicImage->load(":/QDefault/Musics");
            internetImage->load(":/QDefault/Internet");
        }

        shutdownButton->setPixmap(*shutdownImage);
        disconnectButton->setPixmap(*disconnectImage);
        optionButton->setPixmap(*optionImage);
        gameButton->setPixmap(*gameImage);
        videoButton->setPixmap(*videoImage);
        musicButton->setPixmap(*musicImage);
        internetButton->setPixmap(*internetImage);
    }

    text->setDefaultTextColor(QColor(*userSettings->redUnselect, *userSettings->greenUnselect, *userSettings->blueUnselect));

    QString qListViewStyleSheet("color: rgb(%1,%2,%3);"
                                "background-color: transparent;"
                                "selection-color: rgb(%4,%5,%6);"
                                "border-style: none;");

    emulatorsView.setStyleSheet(qListViewStyleSheet.arg(*userSettings->redUnselect).arg(*userSettings->greenUnselect).arg(*userSettings->blueUnselect).arg(*userSettings->redSelect).arg(*userSettings->greenSelect).arg(*userSettings->blueSelect));
    dirView.setStyleSheet(qListViewStyleSheet.arg(*userSettings->redUnselect).arg(*userSettings->greenUnselect).arg(*userSettings->blueUnselect).arg(*userSettings->redSelect).arg(*userSettings->greenSelect).arg(*userSettings->blueSelect));


    keyboard->setKeyboardType(*userSettings->keyboardTypeSelected);

    soundManagement->muteTheConsole(*userSettings->consoleMuted == 0 ? false : true);

    switch(action)
    {
        case NewTheme :
        case LoadedTheme :
            subFolderTextColorManagement();
            break;

        case ActualTheme :
            actualElement->actualizeContent(true);
            subFolderAnimation(DisplayThis);
            break;
    }
}
void ConsoleIHM::displayNewAvatar()
{
    QImage bodyAvatar("Themes/Avatars/Body" + QString::number(*userSettings->bodyChoosen) + ".png");
    QImage hairAvatar("Themes/Avatars/Hair" + QString::number(*userSettings->hairChoosen) + ".png");
    QImage eyesAvatar("Themes/Avatars/Eye" + QString::number(*userSettings->eyesChoosen) + ".png");
    QImage mouthAvatar("Themes/Avatars/Mouth" + QString::number(*userSettings->mouthChoosen) + ".png");

    QImage results(210, 213, QImage::Format_ARGB32_Premultiplied);
    results.fill(Qt::transparent);

    QPainter renderer;
    renderer.begin(&results);
    renderer.setCompositionMode(QPainter::CompositionMode_SourceOver);
    renderer.drawImage(0, 0, bodyAvatar);
    renderer.drawImage(0, 0, hairAvatar);
    renderer.drawImage(0, 0, eyesAvatar);
    renderer.drawImage(0, 0, mouthAvatar);
    renderer.end();

    avatarRenderer->setPixmap(QPixmap::fromImage(results));
}
void ConsoleIHM::getThemePosition(QString wallpaper, QString icon)
{
    QString wallpaperToFound = wallpaper == "" ? userSettings->wallpaperChoosen : wallpaper;
    int i;
    bool founded = false;
    for(i = 0; i < listOfWallpaper.count() ; i++)
    {
        if(wallpaperToFound.compare(listOfWallpaper.at(i)) == 0)
        {
            *userSettings->wallpaperPosition = i;
            founded = true;
            break;
        }
    }
    if(!founded)
    {
        *userSettings->wallpaperPosition = -1;
    }
    userSettings->wallpaperChoosen = "";

    QString iconToFound = icon == "" ? userSettings->iconThemeChoosen : icon;
    founded = false;
    for(i = 0; i < listOfIconTheme.count(); i++)
    {
        if(iconToFound.compare(listOfIconTheme.at(i)) == 0)
        {
            *userSettings->iconThemePosition = i;
            founded = true;
            break;
        }
    }
    if(!founded)
    {
        *userSettings->iconThemePosition = -1;
    }
    userSettings->iconThemeChoosen = "";
}
void ConsoleIHM::loadUserTheme()
{
    userSettings = userManagement->loadUserSettings(this->currentWorkingDirectory, userSettings->name);

    QString qListViewStyleSheet("color: rgb(%1,%2,%3);"
                                "background-color: transparent;"
                                "selection-color: rgb(%4,%5,%6);"
                                "border-style: none;");

    emulatorsView.setStyleSheet(qListViewStyleSheet.arg(*userSettings->redUnselect).arg(*userSettings->greenUnselect).arg(*userSettings->blueUnselect).arg(*userSettings->redSelect).arg(*userSettings->greenSelect).arg(*userSettings->blueSelect));
    dirView.setStyleSheet(qListViewStyleSheet.arg(*userSettings->redUnselect).arg(*userSettings->greenUnselect).arg(*userSettings->blueUnselect).arg(*userSettings->redSelect).arg(*userSettings->greenSelect).arg(*userSettings->blueSelect));
    getThemePosition();

    setLanguage(userSettings->language);
    setNewTheme(LoadedTheme);
}
void ConsoleIHM::setLanguage(SupportedLanguage language)
{
    userSettings->language = language;

    listOfName[0] = translator.getTranslation("Option", language, "Menu");
    listOfName[1] = translator.getTranslation("Video", language, "Menu");
    listOfName[2] = translator.getTranslation("Internet", language, "Menu");
    listOfName[3] = translator.getTranslation("Music", language, "Menu");
    listOfName[4] = translator.getTranslation("Game", language, "Menu");
    listOfName[5] = translator.getTranslation("Shutdown", language, "Menu");
    listOfName[6] = translator.getTranslation("Disconnect", language, "Menu");

    QStringList listOfColors;

    listOfColors << translator.getTranslation("White", language, "Menu");
    listOfColors << translator.getTranslation("Black", language, "Menu");
    listOfColors << translator.getTranslation("Red", language, "Menu");
    listOfColors << translator.getTranslation("Green", language, "Menu");
    listOfColors << translator.getTranslation("Blue", language, "Menu");
    listOfColors << translator.getTranslation("Pink", language, "Menu");
    listOfColors << translator.getTranslation("Yellow", language, "Menu");
    listOfColors << translator.getTranslation("Orange", language, "Menu");
    listOfColors << translator.getTranslation("Purple", language, "Menu");
    listOfColors << translator.getTranslation("Brown", language, "Menu");
    listOfColors << translator.getTranslation("Gray", language, "Menu");

    QStringList listOfKeyboardColors;
    listOfKeyboardColors = listOfColors;

    listOfColors << translator.getTranslation("Presetted", language, "Menu");

    QStringList listOfSupportedLanguages;
    listOfSupportedLanguages << translator.getTranslation("French", language, "Option");
    listOfSupportedLanguages << translator.getTranslation("English", language, "Option");

    QStringList mutedOrNot;
    mutedOrNot << translator.getTranslation("Enabled", language, "Option");
    mutedOrNot << translator.getTranslation("Disabled", language, "Option");

    QStringList listOfSex;
    listOfSex << translator.getTranslation("Male", language, "Option");
    listOfSex << translator.getTranslation("Female", language, "Option");
    listOfSex << translator.getTranslation("Other", language, "Option");

    MenuCreator menuCreator;
    optionMenuElements = menuCreator.createNewMenu(userSettings, newUser, listOfColors, listOfKeyboardColors, listOfKeyboardType, listOfSupportedLanguages, listOfIconTheme, listOfWallpaper, mutedOrNot, listOfSex, language);

    text->setPlainText(listOfName[rotationPosition]);
}
void ConsoleIHM::getFilesInFolder(QString path)
{
    switch(consoleMode)
    {
        case Gaming :
            romsDir.setPath(path + emulatorIndex->index(positionInEmulatorsView,0).data(Qt::DisplayRole).toString());
            dirModel.setStringList(romsDir.entryList(QDir::Files | QDir::NoDot, QDir::Name));
            break;

        case Videoing:
            romsDir.setPath(path);
            dirModel.setStringList(romsDir.entryList(QDir::Files | QDir::NoDot, QDir::Name));
            break;

        default:
            break;
    }
        dirProxy->resetTransform();
}

/*Functions for the joysticks*/
void ConsoleIHM::joystickXButtonPressed() /*Simulate the key "enter"*/
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
}
void ConsoleIHM::joystickOButtonPressed() /*Simulate the key "escape"*/
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
    QApplication::sendEvent(this, &event);

}
void ConsoleIHM::joystickRightAxeUsed()
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
}
void ConsoleIHM::joystickLeftAxeUsed()
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
}
void ConsoleIHM::joystickTopAxeUsed()
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
}
void ConsoleIHM::joystickBottomAxeUsed()
{
        QKeyEvent event(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
        QApplication::sendEvent(this, &event);
}
void ConsoleIHM::joystickConnected()
{
    QString joystickType = joystick->getTheJoystickType();
    if(consoleMode == LoginScreen)
    {
        return;
    }
    else if ((consoleMode == Gaming) && !gameIsLaunched)
    {
        std::vector<JoystickType> joysticksType = joystick->getJoystickConnected();
        emulatorManagement->configureTheEmulators(this->currentWorkingDirectory, joysticksType);
    }

    notificationPopup = new Popup(joystickType, userSettings->language, true);
        notificationPopup->show();

    resolutionManagement(true);
}
void ConsoleIHM::joystickDisconnected()
{    
    if(consoleMode == LoginScreen)
    {
        return;
    }
    else if ((consoleMode == Gaming) && !gameIsLaunched)
    {
        std::vector<JoystickType> joysticksType = joystick->getJoystickConnected();
        emulatorManagement->configureTheEmulators(this->currentWorkingDirectory, joysticksType);
    }

    notificationPopup = new Popup(NULL, userSettings->language, false);
        notificationPopup->show();

    resolutionManagement(true);
}

/*Functions for animations or actions on event*/
void ConsoleIHM::keyPressEvent(QKeyEvent* event)
{
    /*Summary :
    This function manage the keyboard events, but not only !
    In order to make the joysticks events easier, the joysticks event
    emulate a keybord event

    This function is separte in two subfunction :
        What happen when we are on the main menu
        What happen when we are on a sub-menu
    */

    if(keyboardActivated)
    {
        keyboard->keyPressEvent(event);
        return;
    }
    if(videoIsPlaying)
    {
       player->keyPressEvent(event);
       return;
    }
    if(event->key() == Qt::Key_Escape)
    {
        switch(consoleMode)
        {
            case SubMenu :
                subFolderAnimation(DisplayParent);
                break;

            case Gaming :
                gameMode(false);
                break;

            case Videoing:
                videoMode(false);
                break;

            case ChangeAvatarIHM:
                scene->removeItem(avatarRenderer);
                consoleMode = SubMenu;
                setCarousel(true);
                subFolderAnimation(DisplayParent);
                break;

            default:
                break;
        }
        soundManagement->playTheMoveSound();
    }

    switch(consoleMode)
    {
        case LoginScreen:
        case MainMenu: /*Carousel management*/
        {
            if(endOfAnimation) /*No animation is present*/
            {
                switch(event->key())
                {
                    case Qt::Key_Right:
                    case Qt::Key_Down:
                    {
                        rotationPosition += 1;

                        if(rotationPosition > iconsNumber - 1)
                        {
                            rotationPosition = 0;
                        }

                        startAngle = endAngle;
                        endAngle = startAngle + (360/(float)iconsNumber);

                        doAnim(); /*make animation for moving to the icon choosen*/
                        soundManagement->playTheMoveSound();
                        break;
                    }

                    case Qt::Key_Left:
                    case Qt::Key_Up:
                    {
                        rotationPosition -= 1;

                        if(rotationPosition < 0)
                        {
                            rotationPosition = iconsNumber - 1;
                        }

                        startAngle = endAngle;
                        endAngle = startAngle - 360/(float)iconsNumber;

                        doAnim();
                        soundManagement->playTheMoveSound();
                        break;
                    }

                    case Qt::Key_Backspace:
                    {
                        soundManagement->playTheMoveSound();
                        if(consoleMode == LoginScreen)
                        {
                            onConnect();
                            return;
                        }

                        switch (rotationPosition)
                        {
                            case 0 : /*Option*/
                                consoleMode = SubMenu;

                                actualElement = optionMenuElements;
                                subFolderAnimation(DisplayThis); /*To the option !*/
                                break;

                            case 1 : /*Video*/
                                videoMode(true);
                                break;

                            case 2 : /*Internet*/
                                navigator = new litchiNavigator; /*Let's use Internet !*/
                                navigator->show();
                                consoleMode = InternetNavigator;
                                joystick->softwareMod(true);
                                break;

                            case 3 : /*Musique*/
                                keyboardActivated = !keyboardActivated;
                                activateKeyboard(keyboardActivated);
                                break;

                            case 4 : /*Game*/
                                gameMode(true);
                                break;

                            case 5 : /*Shutdown*/
                                qApp->quit();
                                break;

                            case 6 : /*Disconnect*/
                                setCarousel(false);
                                setLogScreen(true);

                            default :
                                break;
                        }
                    }
                }
            }
            break;
        }

        case ChangeAvatarIHM: /*We are in a sub menu*/
        case SubMenu:
        {
            int numberOfChild = actualElement->countChildren() - 1;

            switch(event->key())
            {
                case Qt::Key_Up:
                {
                    soundManagement->playTheMoveSound();
                    subMenuPosition -= 1;

                    if(subMenuPosition < 0)
                    {
                        subMenuPosition = numberOfChild;
                    }
                    subFolderTextColorManagement();
                    break;
                }

                case Qt::Key_Down:
                {
                    soundManagement->playTheMoveSound();
                    subMenuPosition += 1;

                    if(subMenuPosition > numberOfChild)
                    {
                        subMenuPosition = 0;
                    }
                    subFolderTextColorManagement();
                    break;
                }

                case Qt::Key_Left:
                {
                    IMenuElement* selectedMenuElement = actualElement->getChild(subMenuPosition);
                    if(selectedMenuElement->addToVariableValue(-1))
                    {
                        if(consoleMode==ChangeAvatarIHM)
                        {
                            displayNewAvatar();
                        }
                        setNewTheme(ActualTheme);
                    }
                    break;
                }

                case Qt::Key_Right:
                {
                    IMenuElement* selectedMenuElement = actualElement->getChild(subMenuPosition);
                    if(selectedMenuElement->addToVariableValue(+1))
                    {
                        if(consoleMode==ChangeAvatarIHM)
                        {
                            displayNewAvatar();
                        }
                        setNewTheme(ActualTheme);
                    }
                    break;
                }

                case Qt::Key_Backspace:
                {
                    if(rotationPosition == 0) /*Option Menu*/
                    {
                        IMenuElement* menu = actualElement->getChild(subMenuPosition);
                        int numberOfActualChild = menu->countChildren();
                        /*If the selected child have children, we display them*/
                        if(numberOfActualChild > 0 && !menu->requestAction())
                        {
                            subFolderAnimation(DisplayChildren);
                        }
                        /*Sometimes, the menu need a specific action*/
                        else if(menu->requestAction())
                        {
                            switch(menu->returnActionNeeded())
                            {
                                case ChangeLanguage :
                                {
                                    QString content = menu->returnContent();
                                    delete optionMenuElements;

                                    if(content == "Francais")
                                    {
                                        setLanguage(FR);
                                    }
                                    else
                                    {
                                        setLanguage(EN);
                                    }

                                    actualElement = optionMenuElements;
                                    this->setNewTheme(ActualTheme);
                                    break;
                                }

                                case RequestKeyboard :
                                {
                                    activateKeyboard(true);
                                    break;
                                }

                                case CreateNewUser :
                                {
                                    if(userManagement->createNewUser(this->currentWorkingDirectory, newUser)) /*If the user a perfectly created*/
                                    {
                                        QKeyEvent echap(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
                                        QApplication::sendEvent(this, &echap);

                                        /*We reset the new user after the creation*/
                                        *newUser->nameChoosen = "";
                                        *newUser->sexChoosen = 0;
                                        *newUser->languageChoosen = 0;
                                    }
                                    else /*Not handled yet*/
                                    {

                                    }
                                    break;
                                }

                                case ChangeAvatar:
                                {
                                    userManagement->createAvatar();
                                    QKeyEvent echap(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
                                    QApplication::sendEvent(this, &echap);
                                    break;
                                }

                                case DisplayChangeAvatar:
                                {
                                    consoleMode = ChangeAvatarIHM;
                                    setCarousel(false);
                                    scene->addItem(avatarRenderer);
                                    subFolderAnimation(DisplayChildren);

                                    displayNewAvatar();
                                    break;
                                }

                                case Return:
                                {
                                    QKeyEvent echap(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
                                    QApplication::sendEvent(this, &echap);
                                    break;
                                }

                                default:
                                    break;
                            }
                        }
                    }
                    break;
                }
            }
            break;
        }

        case Gaming: /*We are in the game menu*/
        {
            switch(event->key())
            {
                case Qt::Key_Left:
                case Qt::Key_Right:
                    soundManagement->playTheMoveSound();

                    if(firstListView)
                    {
                        dirView.setCurrentIndex(dirModel.index(positionInDirView));
                    }
                    else
                    {

                        emulatorsView.setCurrentIndex(emulatorModel.index(positionInEmulatorsView));
                        dirView.setCurrentIndex(dirModel.index(-1));
                    }
                    firstListView = !firstListView;
                    break;

                case Qt::Key_Up:
                    soundManagement->playTheMoveSound();

                    if(firstListView)
                    {
                        positionInEmulatorsView -= 1;

                        if(positionInEmulatorsView < 0)
                        {
                           positionInEmulatorsView = emulatorModel.rowCount() - 1;
                        }

                        emulatorsView.setCurrentIndex(emulatorModel.index(positionInEmulatorsView));
                        positionInDirView = 0;
                        getFilesInFolder(this->currentWorkingDirectory + "/../Roms/");
                    }
                    else
                    {
                        positionInDirView -= 1;

                        if(positionInDirView < 0)
                        {
                           positionInDirView = dirModel.rowCount() - 1;
                        }

                        dirView.setCurrentIndex(dirModel.index(positionInDirView));
                    }
                    break;

                case Qt::Key_Down:
                    soundManagement->playTheMoveSound();

                    if(firstListView)
                    {
                        positionInEmulatorsView += 1;

                        if(positionInEmulatorsView >= emulatorModel.rowCount())
                        {
                            positionInEmulatorsView = 0;
                        }

                        emulatorsView.setCurrentIndex(emulatorModel.index(positionInEmulatorsView));
                        getFilesInFolder(this->currentWorkingDirectory + "/../Roms/");
                        positionInDirView = 0;
                    }
                    else
                    {
                        positionInDirView += 1;

                        if(positionInDirView >= dirModel.rowCount())
                        {
                            positionInDirView = 0;
                        }

                        dirView.setCurrentIndex(dirModel.index(positionInDirView));
                    }
                    break;

                case Qt::Key_Backspace:
                    QString emulatorChoosen = this->currentWorkingDirectory + "/../Emulators/";
                    emulatorChoosen += emulatorIndex->index(positionInEmulatorsView,0).data(Qt::DisplayRole).toString() + "/";
                    emulatorChoosen += emulatorManagement->getTheEmulatorChoosen(emulatorIndex->index(positionInEmulatorsView,0).data(Qt::DisplayRole).toString());

                    QString romChoosen = this->currentWorkingDirectory + "/../Roms/" + emulatorIndex->index(positionInEmulatorsView,0).data(Qt::DisplayRole).toString() + "/";
                    romChoosen += dirIndex->index(positionInDirView,0).data(Qt::DisplayRole).toString();

                    runTheEmulator(emulatorChoosen, romChoosen);
                    break;
            }
            break;
        }

        case Videoing: /*We are in the video menu*/
        {
            switch(event->key())
            {
                case Qt::Key_Escape:
                    videoMode(false);
                    break;

                case Qt::Key_Up:
                {
                    soundManagement->playTheMoveSound();
                    positionInDirView -= 1;

                    if(positionInDirView < 0)
                    {
                       positionInDirView = dirModel.rowCount() - 1;
                    }

                    dirView.setCurrentIndex(dirModel.index(positionInDirView));
                    break;
                }

                case Qt::Key_Down:
                {
                    soundManagement->playTheMoveSound();
                    positionInDirView += 1;

                    if(positionInDirView >= dirModel.rowCount())
                    {
                        positionInDirView = 0;
                    }

                    dirView.setCurrentIndex(dirModel.index(positionInDirView));
                    break;
                }

                case Qt::Key_Backspace:
                {
                    QString videoChoosen = this->currentWorkingDirectory + "/../Videos/" + dirIndex->index(positionInDirView,0).data(Qt::DisplayRole).toString();
                    playTheVideo(videoChoosen);
                    break;
                }

            }
            break;
        }

        default:
            break;
    }
}
void ConsoleIHM::activateKeyboard(const bool on)
{
    if(on)
    {
        scene->addItem(keyboardProxy);
    }
    else
    {
        scene->removeItem(keyboardProxy);
    }
    keyboardActivated = on;
    resolutionManagement();
}
void ConsoleIHM::newKeyPressed()
{
    QString keyActuallyPressed = *keyPressed;
    if(keyActuallyPressed == "Back Space")
    {
        int size = newUser->nameChoosen->size();
        QString appendedVar = newUser->nameChoosen->remove(size-1,1);
        *newUser->nameChoosen = appendedVar;
    }
    else if (keyActuallyPressed == "Space")
    {
        *newUser->nameChoosen += " ";
    }
    else if(keyActuallyPressed == "&&")
    {
        *newUser->nameChoosen += "&";
    }
    else
    {
        *newUser->nameChoosen += *keyPressed;
    }
    subFolderAnimation(DisplayThis);
}
void ConsoleIHM::hideTheKeyboard()
{
    activateKeyboard(false);
}
void ConsoleIHM::doAnim() /*Make the carousel turn*/
{
    text->setPlainText("");
    endOfAnimation = false;

    if(consoleMode == LoginScreen)
    {
        logScreenMenuCarousel->mAngleAnimator->setStartValue(startAngle);
        logScreenMenuCarousel->mAngleAnimator->setEndValue(endAngle);
        logScreenMenuCarousel->mAngleAnimator->start();
    }
    else
    {
        mainMenuCarousel->mAngleAnimator->setStartValue(startAngle);
        mainMenuCarousel->mAngleAnimator->setEndValue(endAngle);
        mainMenuCarousel->mAngleAnimator->start();
    }

    QTimer::singleShot(450, this, SLOT(stop())); /*Timer for making a smoothy anim*/
}
void ConsoleIHM::stop() /*What happen when the carousel's animation stops*/
{
    endOfAnimation = true;

    if(consoleMode == LoginScreen)
    {
        text->setPlainText(listOfUserName.at(rotationPosition));
        resolutionManagement();
    }
    else
    {
        text->setPlainText(listOfName[rotationPosition]);
    }
}
void ConsoleIHM::closeTheSoftware()
{
    switch(consoleMode)
    {
        case Gaming:
        {
            if(gameIsLaunched)
            {
                emulator->close();
                delete emulator;
                gameIsLaunched = false;
            }
            break;
        }
        case InternetNavigator:
        {
            navigator->close();
            delete navigator;
            consoleMode = MainMenu;
            break;
        }

         default :
            break;
    }

    joystick->softwareMod(false);
    this->showFullScreen();
}

/*Functions for the emulators*/
void ConsoleIHM::gameMode(const bool on)
{
    if(on)
    {
        consoleMode = Gaming;
        positionInDirView = 0;

        setCarousel(false);
        std::vector<JoystickType> joysticksType = joystick->getJoystickConnected();
        emulatorManagement->configureTheEmulators(this->currentWorkingDirectory, joysticksType);
        emulatorManagement->checkTheRoms(this->currentWorkingDirectory);

        scene->addItem(dirProxy);
        scene->addItem(emulatorsProxy);

        positionInEmulatorsView = 0;
        emulatorsView.setCurrentIndex(emulatorModel.index(positionInEmulatorsView));
        getFilesInFolder(this->currentWorkingDirectory + "/../Roms/");
    }
    else
    {
        consoleMode = MainMenu;
        setCarousel(true);

        scene->removeItem(dirProxy);
        scene->removeItem(emulatorsProxy);
    }
    resolutionManagement();
}
void ConsoleIHM::runTheEmulator(QString emulatorChoosen, QString romChoosen)
{
    soundManagement->playTheStartGameSound();
    emulator = new QProcess;
    emulator->start(emulatorChoosen, QStringList() <<  romChoosen);
    gameIsLaunched = true;
    joystick->softwareMod(true);
}

/*Function for the video*/
void ConsoleIHM::videoMode(const bool on)
{
    if(on)
    {
        consoleMode = Videoing;
        positionInDirView = 0;

        setCarousel(false);
        getFilesInFolder(this->currentWorkingDirectory + "/../Videos/");

        dirView.setCurrentIndex(dirModel.index(positionInDirView));
        scene->addItem(dirProxy);
    }
    else
    {
        consoleMode = MainMenu;

        scene->removeItem(dirProxy);
        setCarousel(true);
    }
    resolutionManagement();
}
void ConsoleIHM::playTheVideo(QString path)
{
    videoIsPlaying = true;

    player = new Player();
    connect(player, SIGNAL(exitThePlayer()), this, SLOT(closeThePlayer()));
    player->resize(wWidth,wHeight);
    player->playFile(path);
    player->show();
    player->move(wHeight/2,wWidth/2);
}
void ConsoleIHM::closeThePlayer()
{
    videoIsPlaying = false;
    delete player;
    this->showFullScreen();
}
