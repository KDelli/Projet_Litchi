#ifndef NEWUSER_H
#define NEWUSER_H

#include <QString>

class NewUser
{
    public:
        NewUser();
        virtual ~NewUser();

        QString* nameChoosen;

        int* languageChoosen;
        int* sexChoosen;

};

#endif
