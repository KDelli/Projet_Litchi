#include "menuCreator.h"
#include "actionType.h"

MenuCreator::MenuCreator()
{
}

OMenuElement* MenuCreator::createNewMenu(UserSettings* userSettings, NewUser* newUser, QStringList colorList, QStringList keyboardColorList,  QStringList listOfKeyboardType, QStringList listOfSupportedLanguages, QStringList iconList, QStringList wallpaperList, QStringList mutedOrNot, QStringList listOfSex, SupportedLanguage language)
{
    LanguageManagement manager;

    OMenuElement *menuElement = new OMenuElement(manager.getTranslation("Option",language, "Option"));
        menuElement->addChild(manager.getTranslation("CreateNewUser",language, "Option"));
        IMenuElement* childMenuElement = menuElement->getChild(0);
            childMenuElement->addChild(manager.getTranslation("NameOfNewUser",language,"Option"), newUser->nameChoosen);
            childMenuElement->addChild(manager.getTranslation("ChoosenLanguage",language,"Option"), newUser->languageChoosen, listOfSupportedLanguages);
            childMenuElement->addChild(manager.getTranslation("Sex",language,"Option"), newUser->sexChoosen, listOfSex);
            childMenuElement->addChild(manager.getTranslation("Validate",language,"Option"),  CreateNewUser);
        menuElement->addChild(manager.getTranslation("CustomLitchi",language, "Option"));
        childMenuElement = menuElement->getChild(1);
            childMenuElement->addChild(manager.getTranslation("Wallpaper",language, "Option"),userSettings->wallpaperPosition, wallpaperList);
            childMenuElement->addChild(manager.getTranslation("Icons",language, "Option"), userSettings->iconThemePosition, iconList);
            childMenuElement->addChild(manager.getTranslation("ColorSelect",language, "Option"));
            IMenuElement* subChildMenuElement = childMenuElement->getChild(2);
                    subChildMenuElement->addChild(manager.getTranslation("Predefined",language, "Option"), userSettings->presettedSelectColor, colorList);
                    subChildMenuElement->addChild(manager.getTranslation("Red",language, "Option"), userSettings->redSelect, 0, 255);
                    subChildMenuElement->addChild(manager.getTranslation("Green",language, "Option"), userSettings->greenSelect, 0, 255);
                    subChildMenuElement->addChild(manager.getTranslation("Blue",language, "Option"), userSettings->blueSelect, 0, 255);
            childMenuElement->addChild(manager.getTranslation("ColorUnselect",language, "Option"));
                subChildMenuElement = childMenuElement->getChild(3);
                    subChildMenuElement->addChild(manager.getTranslation("Predefined",language, "Option"), userSettings->preSettedUnselectColor, colorList);
                    subChildMenuElement->addChild(manager.getTranslation("Red",language, "Option"), userSettings->redUnselect, 0, 255);
                    subChildMenuElement->addChild(manager.getTranslation("Green",language, "Option"), userSettings->greenUnselect, 0, 255);
                    subChildMenuElement->addChild(manager.getTranslation("Blue",language, "Option"), userSettings->blueUnselect, 0, 255);
            childMenuElement->addChild(manager.getTranslation("ModifyKeyboard",language, "Option"));
                subChildMenuElement = childMenuElement->getChild(4);
                    subChildMenuElement->addChild(manager.getTranslation("KeyboardBackground",language, "Option"), userSettings->keyboardBackgroundColor, keyboardColorList);
                    subChildMenuElement->addChild(manager.getTranslation("KeyboardSelectColor",language, "Option"), userSettings->keyboardSelectColor, keyboardColorList);
                    subChildMenuElement->addChild(manager.getTranslation("KeyboardUnselectColor",language, "Option"), userSettings->keyboardUnselectColor, keyboardColorList);
                    subChildMenuElement->addChild(manager.getTranslation("KeyboardType",language, "Option"), userSettings->keyboardTypeSelected, listOfKeyboardType);
            childMenuElement->addChild(manager.getTranslation("Sound",language, "Option"), userSettings->consoleMuted, mutedOrNot);
        menuElement->addChild(manager.getTranslation("Avatar",language, "Option"), DisplayChangeAvatar);
        childMenuElement = menuElement->getChild(2);
            childMenuElement->addChild(manager.getTranslation("Sex",language,"Option"), userSettings->sex, listOfSex);
            childMenuElement->addChild(manager.getTranslation("Hair",language,"Option"), userSettings->hairChoosen, 0, 4);
            childMenuElement->addChild(manager.getTranslation("Eyes",language,"Option"), userSettings->eyesChoosen, 1, 7);
            childMenuElement->addChild(manager.getTranslation("Mouth",language,"Option"), userSettings->mouthChoosen, 0, 5);
            childMenuElement->addChild(manager.getTranslation("Body",language,"Option"), userSettings->bodyChoosen, 1, 18);
            childMenuElement->addChild(manager.getTranslation("ChangeAvatar",language, "Option"), ChangeAvatar);
        menuElement->addChild(manager.getTranslation("Language",language, "Option"));
        childMenuElement = menuElement->getChild(3);
            childMenuElement->addChild("Francais", ChangeLanguage);
            childMenuElement->addChild("English", ChangeLanguage);

    return menuElement;
}
