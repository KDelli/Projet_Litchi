#ifndef ABSTRACTMENUELEMENT_H
#define ABSTRACTMENUELEMENT_H

#include "IMenuElement.h"

#include <QList>

class AbstractMenuElement : public IMenuElement
{
    public:
        void removeChild(const int index);
        void removeChildren(IMenuElement* element = nullptr);

        QString returnContent() const;

        bool hasParent() const;
        bool requestAction() const;

        int countChildren() const;

        IMenuElement* getParentMenu() const;
        IMenuElement* getChild(const int index);
        const QList<IMenuElement*> getChildren() const;

    protected:
        bool actionIsNedded;

        IMenuElement* parent;
        QList<IMenuElement*> children;

        QString menuContent;
};

#endif
