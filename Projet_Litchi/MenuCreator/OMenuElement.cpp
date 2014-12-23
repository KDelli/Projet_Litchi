#include "OMenuElement.h"

OMenuElement::OMenuElement(QString content, IMenuElement *parentMenu)
{
    if(parentMenu != nullptr)
    {
        this->parent = parentMenu;
    }
    else
    {
        this->parent = nullptr;
    }
    this->actionIsNedded = false;
    this->menuContent = content;
}

void OMenuElement::addChild(QString content, int *var, int minValue, int maxValue)
{
    IMenuElement *childMenu = new VMenuElement(content, this, var, minValue, maxValue);
    this->children.push_back(childMenu);
}
void OMenuElement::addChild(QString content, int* var, QStringList list)
{
    IMenuElement *childMenu = new VMenuElement(content, this, var, list);
    this->children.push_back(childMenu);
}
void OMenuElement::addChild(QString content, QString* inputContent)
{
    IMenuElement *childMenu = new KMenuElement(content, this, inputContent);
    this->children.push_back(childMenu);
}
void OMenuElement::addChild(QString content)
{
    OMenuElement *childMenu = new OMenuElement(content, this);
    this->children.push_back(childMenu);
}
void OMenuElement::addChild(QString content, ActionType requestedAction)
{
    IMenuElement *childMenu = new RMenuElement(content, this, requestedAction);
    this->children.push_back(childMenu);
}
void OMenuElement::addChild(IMenuElement& content)
{
    this->children.push_front(&content);
}

void OMenuElement::actualizeContent(bool childrenToo)
{
    if(!childrenToo)
    {
        return;
    }
    int numberOfChildren = this->countChildren();

    if(numberOfChildren > 0)
    {
        int i;

        for(i = 0; i < numberOfChildren; i++)
        {
            IMenuElement* menuElement = this->getChild(i);

            menuElement->actualizeContent(true);
        }
    }
}
bool OMenuElement::addToVariableValue(const int)
{
    return false;
}

QString OMenuElement::returnSubsidiaryContent() const
{
    return "";
}
ActionType OMenuElement::returnActionNeeded() const
{
    return Nothing;
}

OMenuElement::~OMenuElement()
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
