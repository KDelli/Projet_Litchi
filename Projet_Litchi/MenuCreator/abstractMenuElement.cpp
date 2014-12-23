#include "abstractMenuElement.h"

void AbstractMenuElement::removeChild(const int index)
{
    IMenuElement* child =  this->children.at(index);
    this->children.removeAt(index);
    delete child;
}
void AbstractMenuElement::removeChildren(IMenuElement* content)
{
    int i;

    IMenuElement* currentMenuElement = (content == nullptr) ? this : content;
    if(currentMenuElement->countChildren() == 0)
    {
        return;
    }

    for (i = 0; i < currentMenuElement->countChildren(); i++)
    {
        IMenuElement* currentSubChild = currentMenuElement->getChild(i);

        if(currentSubChild->countChildren() > 0)
        {
            currentSubChild->removeChildren(currentSubChild);
        }
        else
        {
            delete currentSubChild;
        }
    }
}

QString AbstractMenuElement::returnContent() const
{
    return this->menuContent;
}

bool AbstractMenuElement::requestAction() const
{
    return this->actionIsNedded;
}

bool AbstractMenuElement::hasParent() const
{
    return this->parent!=nullptr;
}
int AbstractMenuElement::countChildren() const
{
    int numberOfChildren = this->children.count();
    return numberOfChildren;
}

IMenuElement* AbstractMenuElement::getParentMenu() const
{
    return this->parent;
}
IMenuElement* AbstractMenuElement::getChild(const int index)
{
    IMenuElement* menuElement = this->children.at(index);
    return menuElement;
}

const QList<IMenuElement*> AbstractMenuElement::getChildren() const
{
    return this->children;
}
