#ifndef IMENUELEMENT_H
#define IMENUELEMENT_H

#include "actionType.h"

#include <QString>

class IMenuElement
{
    public:
    /*Handled in AbstractMenuElement*/
        virtual void removeChild(const int index) = 0;
        virtual void removeChildren(IMenuElement* element = nullptr) = 0;

        virtual QString returnContent() const = 0;
        virtual ActionType returnActionNeeded() const = 0;

        virtual int countChildren() const = 0;

        virtual bool hasParent() const = 0;
        virtual bool requestAction() const = 0;

        virtual IMenuElement* getParentMenu() const = 0;
        virtual IMenuElement* getChild(const int index) = 0;
        virtual const QList<IMenuElement*> getChildren() const = 0;

    /*Not Handled in AbstractMenuElement*/
        virtual void addChild(QString content) = 0;
        virtual void addChild(QString content, int* var, int minValue, int maxValue) = 0;
        virtual void addChild(QString content, int* var, QStringList list) = 0;
        virtual void addChild(QString content, QString* inputValue) = 0;
        virtual void addChild(QString content, ActionType requestedAction) = 0;
        virtual void addChild(IMenuElement& content) = 0;
        virtual void actualizeContent(const bool childrenToo) = 0;

        virtual QString returnSubsidiaryContent() const = 0;

        virtual bool addToVariableValue(const int incremental) = 0; /*Return false if there's no variable to change*/
};

#endif
