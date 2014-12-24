#include "userManagement.h"

UserManagement::UserManagement()
{
    this->userSettings = new UserSettings;
}

UserSettings* UserManagement::loadUserSettings(QString path, QString name)
{
    QString upath = path + "/../Users/" + name + "/" + name + ".xml";

    QFile file(upath);
    if(!file.exists())
    {
        qWarning() << "User not found ! Returning default user setting";
    }
    file.open(QFile::ReadOnly | QFile::Text);

    QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();

        do
        {
            if(xmlReader.name().compare("Name") == 0)
            {
                userSettings->name = xmlReader.readElementText();
            }
            else if(xmlReader.name().compare("Sex") == 0)
            {
                *userSettings->sex = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("Wallpaper") == 0)
            {
                userSettings->wallpaperChoosen = xmlReader.readElementText();
            }
            else if(xmlReader.name().compare("WallpaperPosition") == 0)
            {
                *userSettings->wallpaperPosition = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("IconTheme") == 0)
            {
                userSettings->iconThemeChoosen = xmlReader.readElementText();
            }
            else if(xmlReader.name().compare("IconPosition") == 0)
            {
                *userSettings->iconThemePosition = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("ConsoleMuted") == 0)
            {
                *userSettings->consoleMuted = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("PresettedUnselectColor") == 0)
            {
                *userSettings->preSettedUnselectColor = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("RedUnselect") == 0)
            {
                *userSettings->redUnselect = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("GreenUnselect") == 0)
            {
                *userSettings->greenUnselect = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("BlueUnselect") == 0)
            {
                *userSettings->blueUnselect = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("PresettedSelectColor") == 0)
            {
                *userSettings->presettedSelectColor = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("RedSelect") == 0)
            {
                *userSettings->redSelect = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("GreenSelect") == 0)
            {
                *userSettings->greenSelect = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("BlueSelect") == 0)
            {
                *userSettings->blueSelect = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("KeyboardBackground") == 0)
            {
                *userSettings->keyboardBackgroundColor = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("KeyboardSelect") == 0)
            {
                *userSettings->keyboardSelectColor = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("KeyboardUnselect") == 0)
            {
                *userSettings->keyboardUnselectColor = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("KeyboardTypeSelected") == 0)
            {
                *userSettings->keyboardTypeSelected = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("HairChoosen") == 0)
            {
                *userSettings->hairChoosen = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("EyesChoosen") == 0)
            {
                *userSettings->eyesChoosen = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("MouthChoosen") == 0)
            {
                *userSettings->mouthChoosen = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("BodyChoosen") == 0)
            {
                *userSettings->bodyChoosen = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name().compare("Language") == 0)
            {
                userSettings->language = (SupportedLanguage)xmlReader.readElementText().toInt();
            }

            xmlReader.readNext();

        }while(!xmlReader.atEnd());

    return userSettings;
}
UserSettings* UserManagement::getUserSettings()
{
    return this->userSettings;
}
int UserManagement::getUserSex(QString path, QString name)
{
    QString upath = path + "/../Users/" + name + "/" + name + ".xml";

    QFile file(upath);
    if(!file.exists())
    {
        qWarning() << "User not found ! Returning default user setting";
    }
    file.open(QFile::ReadOnly | QFile::Text);

    QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();

        do
        {
            if(xmlReader.name().compare("Sex") == 0)
            {
                return xmlReader.readElementText().toInt();
            }
            xmlReader.readNext();

        }while(!xmlReader.atEnd());

        return 0;
}

void UserManagement::saveUserSettings(QString path, UserSettings* userToSave)
{
    UserSettings* trueUserToSave;
    if(userToSave == nullptr)
    {
        trueUserToSave = userSettings;
    }
    else
    {
        trueUserToSave = userToSave;
    }


    QString upath = path + "/../Users/" + trueUserToSave->name + "/" + trueUserToSave->name + ".xml";

    QFile file(upath);
    if(!file.exists())
    {
        qWarning() << "User not found ! Returning default user setting";
    }
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement(trueUserToSave->name);
        xmlWriter.writeTextElement("Name", trueUserToSave->name);
        xmlWriter.writeTextElement("Sex", QString::number(*trueUserToSave->sex));

        xmlWriter.writeTextElement("Wallpaper", trueUserToSave->wallpaperChoosen);
        xmlWriter.writeTextElement("WallpaperPosition", QString::number(*trueUserToSave->wallpaperPosition));

        xmlWriter.writeTextElement("IconTheme", trueUserToSave->iconThemeChoosen);
        xmlWriter.writeTextElement("IconPosition", QString::number(*trueUserToSave->iconThemePosition));

        xmlWriter.writeTextElement("ConsoleMuted", QString::number(*trueUserToSave->consoleMuted));

        xmlWriter.writeTextElement("PresettedUnselectColor", QString::number(*trueUserToSave->preSettedUnselectColor));
        xmlWriter.writeTextElement("RedUnselect", QString::number(*trueUserToSave->redUnselect));
        xmlWriter.writeTextElement("RedUnselect", QString::number(*trueUserToSave->redUnselect));
        xmlWriter.writeTextElement("GreenUnselect", QString::number(*trueUserToSave->greenUnselect));
        xmlWriter.writeTextElement("BlueUnselect", QString::number(*trueUserToSave->blueUnselect));

        xmlWriter.writeTextElement("PresettedSelectColor", QString::number(*trueUserToSave->presettedSelectColor));
        xmlWriter.writeTextElement("RedSelect", QString::number(*trueUserToSave->redSelect));
        xmlWriter.writeTextElement("GreenSelect", QString::number(*trueUserToSave->greenSelect));
        xmlWriter.writeTextElement("BlueSelect", QString::number(*trueUserToSave->blueSelect));

        xmlWriter.writeTextElement("KeyboardBackground", QString::number(*trueUserToSave->keyboardBackgroundColor));
        xmlWriter.writeTextElement("KeyboardSelect", QString::number(*trueUserToSave->keyboardSelectColor));
        xmlWriter.writeTextElement("KeyboardUnselect", QString::number(*trueUserToSave->keyboardUnselectColor));
        xmlWriter.writeTextElement("KeyboardTypeSelected", QString::number(*trueUserToSave->keyboardTypeSelected));

        xmlWriter.writeTextElement("HairChoosen", QString::number(*trueUserToSave->hairChoosen));
        xmlWriter.writeTextElement("EyesChoosen", QString::number(*trueUserToSave->eyesChoosen));
        xmlWriter.writeTextElement("MouthChoosen", QString::number(*trueUserToSave->mouthChoosen));
        xmlWriter.writeTextElement("BodyChoosen", QString::number(*trueUserToSave->bodyChoosen));

        xmlWriter.writeTextElement("Language", QString::number((int)trueUserToSave->language));

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();

        file.close();
}
void UserManagement::createAvatar(QString path)
{
    QString upath = path + "/../Users/" + userSettings->name + "/LogPicture.png";
    if(QFile(upath).exists())
    {
        QFile::remove(upath);
    }

    QImage bodyAvatar(path + "/../Themes/Avatars/Body" + QString::number(*userSettings->bodyChoosen) + ".png");
    QImage hairAvatar(path + "/../Themes/Avatars/Hair" + QString::number(*userSettings->hairChoosen) + ".png");
    QImage eyesAvatar(path + "/../Themes/Avatars/Eye" + QString::number(*userSettings->eyesChoosen) + ".png");
    QImage mouthAvatar(path + "/../Themes/Avatars/Mouth" + QString::number(*userSettings->mouthChoosen) + ".png");

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

    results.save(upath);
}


bool UserManagement::createNewUser(QString path, NewUser* newUser)
{
    /*TODO : Check if the user didn't exist*/
    UserSettings* newTrueUser = new UserSettings();

    /*We write is name*/
    newTrueUser->name = *newUser->nameChoosen;
    /*And check*/
    if(newTrueUser->name == "")
    {
        delete newTrueUser;
        return false;
    }

    /*We write is sex*/
    *newTrueUser->sex = *newUser->sexChoosen;

    /*We write is language*/
    int selectedLanguage = *newUser->languageChoosen;
    switch (selectedLanguage)
    {
        case 0 :
            newTrueUser->language = FR;
            break;

        case 1 :
            newTrueUser->language = EN;
            break;

        default :
            break;
    }

    /*We write is default wallpaper*/
    newTrueUser->wallpaperChoosen = "Litchi-Chili";

    /*We create is folder*/
    QString upath = path + "/../Users/" + newTrueUser->name;

    /*We check if the user already exist*/
    if(QDir().exists(upath))
    {
        delete newTrueUser;
        return false;
    }
    else
    {
        QDir().mkdir(upath);
        QFile userXMLFile(upath + "/" + newTrueUser->name + ".xml");

        if(userXMLFile.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&userXMLFile);
            stream << "";
        }
        else
        {
            delete newTrueUser;
            QDir().rmdir(upath);
            return false;
        }
    }

    /*We manage is avatar*/
    *newTrueUser->hairChoosen = rand() % 4;
    *newTrueUser->eyesChoosen = rand() % 5 + 1;
    *newTrueUser->mouthChoosen = rand() % 5;
    *newTrueUser->bodyChoosen = rand() % 17 + 1;

    /*Then we write him*/
    this->saveUserSettings(path, newTrueUser);

    /*Every new have is delete*/
    delete newTrueUser;
    return true;
}


UserManagement::~UserManagement()
{
    delete this->userSettings;
}
