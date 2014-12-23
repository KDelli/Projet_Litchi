#ifndef DMENUELEMENT_H
#define DMENUELEMENT_H

#include "actionType.h"
#include "abstractMenuElement.h"
#include "VMenuElement.h"
#include "OMenuElement.h"
#include "RMenuElement.h"

class KMenuElement : public AbstractMenuElement
{
    public:
        KMenuElement(QString content, IMenuElement* parentMenu, QString* inputValue);
        virtual ~KMenuElement();

        void addChild(QString content);
        void addChild(QString content, int* var, int minValue, int maxValue);
        void addChild(QString content, int* var, QStringList list);
        void addChild(QString content, QString* inputValue);
        void addChild(QString content, ActionType requestedAction);
        void addChild(IMenuElement& content);
        void actualizeContent(const bool childrenToo);
        bool addToVariableValue(const int incremental);

        QString returnSubsidiaryContent() const;
        ActionType returnActionNeeded() const;

    protected :
        KMenuElement();

    private :
        QString& inputValue;
};

#endif
