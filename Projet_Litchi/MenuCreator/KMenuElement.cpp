#include "KMenuElement.h"

KMenuElement::KMenuElement(QString content, IMenuElement *parentMenu, QString* inputValue):inputValue(*inputValue)
{
    if(parentMenu != nullptr)
    {
        this->parent = parentMenu;
    }
    else
    {
        this->parent = nullptr;
    }
    this->menuContent = content;
    this->actionIsNedded = true;

    this->actualizeContent(false);
}

void KMenuElement::addChild(QString content, int *var, int minValue, int maxValue)
{
    IMenuElement *childMenu = new VMenuElement(content, this, var, minValue, maxValue);
    this->children.push_back(childMenu);
}
void KMenuElement::addChild(QString content, int* var, QStringList list)
{
    IMenuElement *childMenu = new VMenuElement(content, this, var, list);
    this->children.push_back(childMenu);
}
void KMenuElement::addChild(QString content, QString* inputValue)
{
    IMenuElement *childMenu = new KMenuElement(content, this, inputValue);
    this->children.push_back(childMenu);
}
void KMenuElement::addChild(QString content)
{
    IMenuElement *childMenu = new OMenuElement(content, this);
    this->children.push_back(childMenu);
}
void KMenuElement::addChild(QString content, ActionType requestedAction)
{
    IMenuElement *childMenu = new RMenuElement(content, this, requestedAction);
    this->children.push_back(childMenu);
}
void KMenuElement::addChild(IMenuElement& content)
{
    this->children.push_front(&content);
}

void KMenuElement::actualizeContent(const bool childrenToo)
{
    if(!childrenToo)
    {
        return;
    }
    int numberOfChildren = this->countChildren();

    if(numberOfChildren > 0)
    {
        int i;

        for(i = 0; i < numberOfChildren; i ++)
        {
            IMenuElement* menuElement = this->getChild(i);

            menuElement->actualizeContent(true);
        }
    }
}

bool KMenuElement::addToVariableValue(const int)
{
    return false;
}

QString KMenuElement::returnSubsidiaryContent() const
{
    return this->inputValue;
}
ActionType KMenuElement::returnActionNeeded() const
{
    return RequestKeyboard;
}

KMenuElement::~KMenuElement()
{
    if(this->hasParent())
    {
        IMenuElement* parentMenuElement = this->getParentMenu();

        int i;
        for(i = 0; i < parentMenuElement->countChildren(); i++)
        {
            if (parentMenuElement->getChild(i) == parentMenuElement)
            {
                parentMenuElement->removeChild(i);
                break;
            }
        }
    }

    this->removeChildren();
}
