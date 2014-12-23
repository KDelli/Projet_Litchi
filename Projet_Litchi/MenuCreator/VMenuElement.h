#ifndef KMENUELEMENT_H
#define KMENUELEMENT_H

#include "abstractMenuElement.h"
#include "OMenuElement.h"
#include "KMenuElement.h"
#include "RMenuElement.h"

#include <QStringList>

class VMenuElement : public AbstractMenuElement
{
    public:
        VMenuElement(QString content, IMenuElement* parentMenu, int* var, int minValue, int maxValue);
        VMenuElement(QString content, IMenuElement* parentMenu, int* var, QStringList list);
        virtual ~VMenuElement();

        void addChild(QString content);
        void addChild(QString content, int* var, int minValue, int maxValue);
        void addChild(QString content, int* var, QStringList list);
        void addChild(QString content, QString* inputValue);
        void addChild(QString content, ActionType requestedAction);
        void addChild(IMenuElement& content);
        void actualizeContent(const bool childrenToo);
        bool addToVariableValue(const int incremental);
        void setSubsidiaryContent(int content);

        QString returnSubsidiaryContent() const;
        ActionType returnActionNeeded() const;

    protected :
        VMenuElement();

    private :
        QString subsidiaryContent;

        int& variable;
        int minValue;
        int maxValue;
        QStringList listForVariable;
};

#endif
