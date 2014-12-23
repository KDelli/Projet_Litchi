#include "RMenuElement.h"

RMenuElement::RMenuElement(QString content, IMenuElement* parentMenu, ActionType requestedAction)
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
    this->requestedAction = requestedAction;
    this->actionIsNedded = true;

    this->actualizeContent(false);
}

void RMenuElement::addChild(QString content, int *var, int minValue, int maxValue)
{
    IMenuElement *childMenu = new VMenuElement(content, this, var, minValue, maxValue);
    this->children.push_back(childMenu);
}
void RMenuElement::addChild(QString content, int* var, QStringList list)
{
    IMenuElement *childMenu = new VMenuElement(content, this, var, list);
    this->children.push_back(childMenu);
}
void RMenuElement::addChild(QString content, QString* inputValue)
{
    IMenuElement *childMenu = new KMenuElement(content, this, inputValue);
    this->children.push_back(childMenu);
}
void RMenuElement::addChild(QString content)
{
    IMenuElement *childMenu = new OMenuElement(content, this);
    this->children.push_back(childMenu);
}
void RMenuElement::addChild(QString content, ActionType requestedAction)
{
    IMenuElement *childMenu = new RMenuElement(content, this, requestedAction);
    this->children.push_back(childMenu);
}
void RMenuElement::addChild(IMenuElement& content)
{
    this->children.push_front(&content);
}

void RMenuElement::actualizeContent(const bool childrenToo)
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

bool RMenuElement::addToVariableValue(const int)
{
    return false;
}

QString RMenuElement::returnSubsidiaryContent() const
{
    return "";
}
ActionType RMenuElement::returnActionNeeded() const
{
    return this->requestedAction;
}

RMenuElement::~RMenuElement()
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
