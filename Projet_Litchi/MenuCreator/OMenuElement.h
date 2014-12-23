#ifndef OMENUELEMENT_H
#define OMENUELEMENT_H

#include "abstractMenuElement.h"
#include "VMenuElement.h"
#include "KMenuElement.h"
#include "RMenuElement.h"


class OMenuElement : public AbstractMenuElement
{
    public:
        OMenuElement(QString content, IMenuElement* parentMenu = nullptr);
        virtual ~OMenuElement();

        void addChild(QString content);
        void addChild(QString content, int* var, int minValue, int maxValue);
        void addChild(QString content, int* var, QStringList list);
        void addChild(QString content, QString* inputValue);
        void addChild(QString content, ActionType requestedAction);
        void addChild(IMenuElement& content);
        void actualizeContent(const bool childrenToo);
        bool addToVariableValue(const int incremental);
        void setReferenceToValue(int& variable);

        QString returnSubsidiaryContent() const;
        ActionType returnActionNeeded() const;

    protected :
        OMenuElement();
};

#endif
