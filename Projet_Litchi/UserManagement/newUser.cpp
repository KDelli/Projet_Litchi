#include "newUser.h"

NewUser::NewUser()
{
    nameChoosen = new QString();
    languageChoosen = new int(0); /*0 : FR, 1 : EN*/
    sexChoosen = new int(1); /*0 : Male, 1 : Female, 2 : Other*/
}

NewUser::~NewUser()
{
    delete nameChoosen;

    delete languageChoosen;
    delete sexChoosen;
}
