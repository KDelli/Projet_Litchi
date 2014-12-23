#include "UserSettings.h"

UserSettings::UserSettings()
{
    this->sex = new int(0);

    this->wallpaperPosition = new int(2);
    this->wallpaperChoosen = "Litchi-Chili.jpg";

    this->iconThemePosition = new int(1);
    this->iconThemeChoosen = "Theme Litchi";

    this->presettedSelectColor = new int(2);
    this->redSelect = new int(219);
    this->greenSelect = new int(23);
    this->blueSelect = new int(3);

    this->preSettedUnselectColor = new int(1);
    this->redUnselect = new int(0);
    this->greenUnselect = new int(0);
    this->blueUnselect = new int(0);

    this->keyboardBackgroundColor = new int(5);
    this->keyboardSelectColor = new int(2);
    this->keyboardUnselectColor = new int(1);
    this->keyboardTypeSelected = new int(0);

    this->hairChoosen = new int(0);
    this->eyesChoosen = new int(0);
    this->mouthChoosen = new int(0);
    this->bodyChoosen = new int(0);

    this->consoleMuted = new int(0);
    this->language = EN;
}

UserSettings::~UserSettings()
{
    delete this->sex;

    delete this->wallpaperPosition;
    delete this->iconThemePosition;

    delete this->presettedSelectColor;
    delete this->redSelect;
    delete this->greenSelect;
    delete this->blueSelect;

    delete this->preSettedUnselectColor;
    delete this->redUnselect;
    delete this->greenUnselect;
    delete this->blueUnselect;

    delete this->keyboardBackgroundColor;
    delete this->keyboardSelectColor;
    delete this->keyboardUnselectColor;
    delete this->keyboardTypeSelected;

    delete this->hairChoosen;
    delete this->eyesChoosen;
    delete this->mouthChoosen;
    delete this->bodyChoosen;

    delete this->consoleMuted;
}
