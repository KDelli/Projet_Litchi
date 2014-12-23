#include "VMenuElement.h"

VMenuElement::VMenuElement(QString content, IMenuElement* parentMenu, int* var, int minValue, int maxValue):variable(*var)
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
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->actionIsNedded = false;

    this->actualizeContent(false);
}
VMenuElement::VMenuElement(QString content, IMenuElement* parentMenu, int* var, QStringList list):variable(*var)
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
    this->listForVariable = list;
    this->minValue = 0;
    this->maxValue = list.length()-1;
    this->actionIsNedded = false;

    this->actualizeContent(false);
}

void VMenuElement::addChild(QString content, int *var, int minValue, int maxValue)
{
    IMenuElement *childMenu = new VMenuElement(content, this, var, minValue, maxValue);
    this->children.push_back(childMenu);
}
void VMenuElement::addChild(QString content, int* var, QStringList list)
{
    IMenuElement *childMenu = new VMenuElement(content, this, var, list);
    this->children.push_back(childMenu);
}
void VMenuElement::addChild(QString content, QString* inputValue)
{
    IMenuElement *childMenu = new KMenuElement(content, this, inputValue);
    this->children.push_back(childMenu);
}
void VMenuElement::addChild(QString content)
{
    IMenuElement *childMenu = new OMenuElement(content, this);
    this->children.push_back(childMenu);
}
void VMenuElement::addChild(QString content, ActionType requestedAction)
{
    IMenuElement *childMenu = new RMenuElement(content, this, requestedAction);
    this->children.push_back(childMenu);
}
void VMenuElement::addChild(IMenuElement& content)
{
    this->children.push_front(&content);
}

void VMenuElement::actualizeContent(const bool childrenToo)
{
    this->setSubsidiaryContent(this->variable);

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
void VMenuElement::setSubsidiaryContent(int content)
{
    if(this->listForVariable.isEmpty())
    {
        this->subsidiaryContent = QString::number(content);
        return;
    }
    if(this->variable < 0)
    {
        this->subsidiaryContent = "Default";
        return;
    }

    this->subsidiaryContent = this->listForVariable.at(this->variable);
}
bool VMenuElement::addToVariableValue(const int incremental)
{
    this->variable += incremental;

    if(variable > maxValue)
    {
        variable = minValue;
    }
    else if(variable < minValue)
    {
        variable = maxValue;
    }
    actualizeContent(false);
    return true;
}

QString VMenuElement::returnSubsidiaryContent() const
{
    return this->subsidiaryContent;
}
ActionType VMenuElement::returnActionNeeded() const
{
    return Nothing;
}

VMenuElement::~VMenuElement()
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
