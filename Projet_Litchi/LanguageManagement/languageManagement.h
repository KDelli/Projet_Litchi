#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include "supportedLanguage.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>

class LanguageManagement
{
	
	public:
		LanguageManagement();
		
        QString getTranslation(QString translationToGet, SupportedLanguage language, QString menuToTranslate);
		
};

#endif
