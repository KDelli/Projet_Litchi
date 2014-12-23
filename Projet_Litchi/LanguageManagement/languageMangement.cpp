#include "languageManagement.h"

LanguageManagement::LanguageManagement()
{
}

QString LanguageManagement::getTranslation(QString translationToGet, SupportedLanguage language, QString menuToTranslate)
{
	QString path;
	
	switch(language)
	{
		case FR:
            path = ":/QLanguage/FR_" + menuToTranslate;
			break;
		case EN:
            path = ":/QLanguage/EN_" + menuToTranslate;
			break;
	}

	QFile file(path);
        file.open(QFile::ReadOnly | QFile::Text);
		
	QXmlStreamReader xmlReader;
		xmlReader.setDevice(&file);
		xmlReader.readNext();
		
	do
	{
        if(xmlReader.name() == translationToGet)
		{
            return xmlReader.readElementText();
		}
		
		xmlReader.readNext();
	}while(!xmlReader.atEnd());
	
    return "Not founded";
}
