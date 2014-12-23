#ifndef RMENUELEMENT_H
#define RMENUELEMENT_H

#include "abstractMenuElement.h"
#include "VMenuElement.h"
#include "KMenuElement.h"
#include "OMenuElement.h"

class RMenuElement : public AbstractMenuElement
{
    public:
        RMenuElement(QString content, IMenuElement* parentMenu, ActionType requestedAction);
        virtual ~RMenuElement();

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
        RMenuElement();

    private :
        ActionType requestedAction;
};

#endif // RMENUELEMENT_H
