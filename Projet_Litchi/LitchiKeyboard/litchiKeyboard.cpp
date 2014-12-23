#include "litchiKeyboard.h"

LitchiKeyboard::LitchiKeyboard(QString *keyAddress)
    :keyPressed(*keyAddress)
{
    keyboardHeight = 340;
    keyboardWidth = 820;
    this->setFocus();;
    this->setFixedSize(keyboardWidth, keyboardHeight);
    this->setFocusPolicy(Qt::StrongFocus);

    horizontalPosition = 0;
    verticalPosition = 0;
    toUpper = false;
    toSymbol = false;

    keyPressed = *keyAddress;

    keyboardLetterMap = new std::map<int,std::vector<QPushButton*>>();
    keyboardSymbolMap = new std::map<int,std::vector<QPushButton*>>();
    keyboardQWMap = new std::map<int,std::vector<QPushButton*>>();

    actualMap = keyboardLetterMap;

    selectColor = "red";
    unselectColor = "black";
    backgroundColor = "pink";
    StringSelectColor = ("color : %1;"
                   "background-color: %2;");
    StringBackgroundColor = ("background-color: %1;"
                             "font : 30px ;");

    std::vector<QPushButton*> vector0;
        vector0.push_back(new QPushButton("1",this));
        vector0.push_back(new QPushButton("2",this));
        vector0.push_back(new QPushButton("3",this));
        vector0.push_back(new QPushButton("4",this));
        vector0.push_back(new QPushButton("5",this));
        vector0.push_back(new QPushButton("6",this));
        vector0.push_back(new QPushButton("7",this));
        vector0.push_back(new QPushButton("8",this));
        vector0.push_back(new QPushButton("9",this));
        vector0.push_back(new QPushButton("0",this));
    (*keyboardLetterMap)[0] = vector0;

    std::vector<QPushButton*> vector1;
        vector1.push_back(new QPushButton("a",this));
        vector1.push_back(new QPushButton("z",this));
        vector1.push_back(new QPushButton("e",this));
        vector1.push_back(new QPushButton("r",this));
        vector1.push_back(new QPushButton("t",this));
        vector1.push_back(new QPushButton("y",this));
        vector1.push_back(new QPushButton("u",this));
        vector1.push_back(new QPushButton("i",this));
        vector1.push_back(new QPushButton("o",this));
        vector1.push_back(new QPushButton("p",this));
    (*keyboardLetterMap)[1] = vector1;

    std::vector<QPushButton*> vector2;
        vector2.push_back(new QPushButton("q",this));
        vector2.push_back(new QPushButton("s",this));
        vector2.push_back(new QPushButton("d",this));
        vector2.push_back(new QPushButton("f",this));
        vector2.push_back(new QPushButton("g",this));
        vector2.push_back(new QPushButton("h",this));
        vector2.push_back(new QPushButton("j",this));
        vector2.push_back(new QPushButton("k",this));
        vector2.push_back(new QPushButton("l",this));
        vector2.push_back(new QPushButton("m",this));
    (*keyboardLetterMap)[2] = vector2;

    std::vector<QPushButton*> vector3;
        vector3.push_back(new QPushButton("w",this));
        vector3.push_back(new QPushButton("x",this));
        vector3.push_back(new QPushButton("c",this));
        vector3.push_back(new QPushButton("v",this));
        vector3.push_back(new QPushButton("b",this));
        vector3.push_back(new QPushButton("n",this));
        vector3.push_back(new QPushButton("A/a",this));
        vector3.push_back(new QPushButton("?/@",this));
        vector3.push_back(new QPushButton("Back Space",this));
    (*keyboardLetterMap)[3] = vector3;

    std::vector<QPushButton*> vector4;
        vector4.push_back(new QPushButton("Space",this));
    (*keyboardLetterMap)[4] = vector4;

/***********************************************************************************/
    (*keyboardSymbolMap)[0] = vector0;

    std::vector<QPushButton*> vector5;
        vector5.push_back(new QPushButton("&&",this));
        vector5.push_back(new QPushButton("~",this));
        vector5.push_back(new QPushButton("\"",this));
        vector5.push_back(new QPushButton("#",this));
        vector5.push_back(new QPushButton("'",this));
        vector5.push_back(new QPushButton("(",this));
        vector5.push_back(new QPushButton(")",this));
        vector5.push_back(new QPushButton("[",this));
        vector5.push_back(new QPushButton("]",this));
        vector5.push_back(new QPushButton("@",this));
    (*keyboardSymbolMap)[1] = vector5;

    std::vector<QPushButton*> vector6;
        vector6.push_back(new QPushButton("=",this));
        vector6.push_back(new QPushButton("+",this));
        vector6.push_back(new QPushButton("*",this));
        vector6.push_back(new QPushButton("-",this));
        vector6.push_back(new QPushButton("_",this));
        vector6.push_back(new QPushButton("$",this));
        vector6.push_back(new QPushButton("£",this));
        vector6.push_back(new QPushButton("€",this));
        vector6.push_back(new QPushButton("!",this));
        vector6.push_back(new QPushButton("?",this));
   (*keyboardSymbolMap)[2] = vector6;

    std::vector<QPushButton*> vector7;
        vector7.push_back(new QPushButton(",",this));
        vector7.push_back(new QPushButton(".",this));
        vector7.push_back(new QPushButton(";",this));
        vector7.push_back(new QPushButton(":",this));
        vector7.push_back(new QPushButton("<",this));
        vector7.push_back(new QPushButton(">",this));
        vector7.push_back(new QPushButton("%",this));
        vector7.push_back(new QPushButton("?/@",this));
        vector7.push_back(new QPushButton("Back Space",this));
    (*keyboardSymbolMap)[3] = vector7;

    (*keyboardSymbolMap)[4] = vector4;

/**************************************************************************/
        (*keyboardQWMap)[0] = vector0;

        std::vector<QPushButton*> vector11;
            vector11.push_back(new QPushButton("q",this));
            vector11.push_back(new QPushButton("w",this));
            vector11.push_back(new QPushButton("e",this));
            vector11.push_back(new QPushButton("r",this));
            vector11.push_back(new QPushButton("t",this));
            vector11.push_back(new QPushButton("y",this));
            vector11.push_back(new QPushButton("u",this));
            vector11.push_back(new QPushButton("i",this));
            vector11.push_back(new QPushButton("o",this));
            vector11.push_back(new QPushButton("p",this));
        (*keyboardQWMap)[1] = vector11;

        std::vector<QPushButton*> vector12;
            vector12.push_back(new QPushButton("a",this));
            vector12.push_back(new QPushButton("s",this));
            vector12.push_back(new QPushButton("d",this));
            vector12.push_back(new QPushButton("f",this));
            vector12.push_back(new QPushButton("g",this));
            vector12.push_back(new QPushButton("h",this));
            vector12.push_back(new QPushButton("j",this));
            vector12.push_back(new QPushButton("k",this));
            vector12.push_back(new QPushButton("l",this));
            vector12.push_back(new QPushButton("A/a",this));
        (*keyboardQWMap)[2] = vector12;

        std::vector<QPushButton*> vector13;
            vector13.push_back(new QPushButton("z",this));
            vector13.push_back(new QPushButton("x",this));
            vector13.push_back(new QPushButton("c",this));
            vector13.push_back(new QPushButton("v",this));
            vector13.push_back(new QPushButton("b",this));
            vector13.push_back(new QPushButton("n",this));
            vector13.push_back(new QPushButton("m",this));
            vector13.push_back(new QPushButton("?/@",this));
            vector13.push_back(new QPushButton("Back Space",this));
        (*keyboardQWMap)[3] = vector13;

        (*keyboardQWMap)[4] = vector4;

/********************************************************************************/

    buttonPosition(*keyboardSymbolMap);
    buttonPosition(*keyboardLetterMap);
    buttonPosition(*keyboardQWMap);


    std::vector<QPushButton*> actualVector = keyboardLetterMap->at(verticalPosition);
    QPushButton* button = actualVector.at(horizontalPosition);
    button->setStyleSheet(StringSelectColor.arg(selectColor).arg(backgroundColor));
    this->setStyleSheet(StringBackgroundColor.arg(backgroundColor));

}

/*Display*/
void LitchiKeyboard::buttonPosition(std::map<int,std::vector<QPushButton*>> &map)
{
    unsigned i,j;
    qreal divisedKeyboardHeight = keyboardHeight/5;
    qreal divisedKeyboardWidth = keyboardWidth/10;
    for(i = 0; i < map.size(); i++)
    {
        std::vector<QPushButton*> actualVector = map.at(i);
        for(j = 0; j < actualVector.size(); j++)
        {
            QPushButton* button = actualVector.at(j);
            /*The space button is the only button of the vector*/
            if(i==4)
            {
                button->setGeometry(QRect( 0, 0, keyboardWidth , divisedKeyboardHeight));
            }
            else
            {
                /*The backspace button is twice wider than other button*/
                if(i == 3 && j == 8)
                {
                    button->setGeometry(QRect( 0, 0, 2*divisedKeyboardWidth, divisedKeyboardHeight));
                }
                else
                {
                    button->setGeometry(QRect( 0, 0, divisedKeyboardWidth, divisedKeyboardHeight));
                }
            }
            button->move(j*divisedKeyboardWidth,i*divisedKeyboardHeight);

            button->setStyleSheet(StringSelectColor.arg(unselectColor).arg(backgroundColor));
        }
    }
}

/*Give visibility to the selected map*/
void LitchiKeyboard::setForeground(std::map<int, std::vector<QPushButton *> > &map)
{
    unsigned i,j;
    for(i = 0; i < map.size(); i++)
    {
        std::vector<QPushButton*> actualVector = map.at(i);
        for(j = 0; j < actualVector.size(); j++)
        {
            QPushButton* button = actualVector.at(j);
            button->raise();
            button->setStyleSheet(StringSelectColor.arg(unselectColor).arg(backgroundColor));
        }
    }
    std::vector<QPushButton*> actualVector = actualMap->at(verticalPosition);
    QPushButton* button = actualVector.at(horizontalPosition);
    button->setStyleSheet(StringSelectColor.arg(selectColor).arg(backgroundColor));
}

/*Custom the keyboard*/
void LitchiKeyboard::setNewTheme(QString backgroundColor, QString selectColor, QString unselectColor)
{
    this->backgroundColor = backgroundColor;
    this->selectColor = selectColor;
    this->unselectColor = unselectColor;

    this->setStyleSheet(StringBackgroundColor.arg(backgroundColor));
    setForeground(*actualMap);
}
void LitchiKeyboard::setKeyboardType(int type)
{
    if(this->type == type)
    {
        return;
    }

    this->type =type;
    switch(type)
    {
        case 0: /*azerty*/
        {
                actualMap = keyboardLetterMap;
                break;
        }
        case 1 : /*qwerty*/
        {
                actualMap = keyboardQWMap;
                break;
        }

        default:
            break;
    }
    setForeground(*actualMap);
}
void LitchiKeyboard::setToKeyboardTypeChoosen()
{
    switch(type)
    {
        case 0 :
        actualMap = keyboardLetterMap;
        break;

    case 1 :
        actualMap = keyboardQWMap;
        break;
    }
}

/*Events*/
void LitchiKeyboard::keyPressEvent(QKeyEvent* event)
{
    int mapSize = actualMap->size() -1;
    std::vector<QPushButton*> actualVector = actualMap->at(verticalPosition);

    /*The ancien button return to its original color*/
    QPushButton* button = actualVector.at(horizontalPosition);
    button->setStyleSheet(StringSelectColor.arg(unselectColor).arg(backgroundColor));

    /*Move*/
    switch(event->key())
    {
        case Qt::Key_Up:
                verticalPosition -=1;
                break;

        case Qt::Key_Down:
                verticalPosition +=1;
                break;

       case Qt::Key_Right:
                horizontalPosition +=1;
                break;

        case Qt::Key_Left:
                 horizontalPosition -=1;
                 break;

        case Qt::Key_Escape:
                emit hideTheKeyboard();
                break;
    }

    if(verticalPosition > mapSize)
    {
        verticalPosition = 0;
    }
    if(verticalPosition < 0)
    {
        verticalPosition = mapSize;
    }

    actualVector = actualMap->at(verticalPosition);
    int vectorSize = actualVector.size() -1;

    if(horizontalPosition > vectorSize)
    {
        horizontalPosition = 0;
    }
    else if(horizontalPosition < 0)
    {
        horizontalPosition = vectorSize;
    }

    /*Then we color the next button*/
    button = actualVector.at(horizontalPosition);
    button->setStyleSheet(StringSelectColor.arg(selectColor).arg(backgroundColor));

    /*Symbol*/
    if(event->key() == Qt::Key_Backspace)
    {
        if(button->text() == "A/a")
        {
            if(toSymbol)
            {
                return;
            }

            toUpper = !toUpper;

            unsigned int i,j;
            for(i = 0; i < actualMap->size(); i++)
            {
                std::vector<QPushButton*> actualVector = actualMap->at(i);
                for(j = 0; j < actualVector.size(); j++)
                {
                    QPushButton* button = actualVector.at(j);

                    if(button->text() != "A/a" && button->text() != "Space" && button->text() != "Back Space")
                    {
                        if(toUpper)
                        {
                            button->setText( button->text().toUpper());
                        }
                        else
                        {
                            button->setText( button->text().toLower());
                        }
                    }
                }
            }
        }
        else if(button->text() == "?/@")
        {
            toSymbol = !toSymbol;
            if(toSymbol)
            {
                actualMap = keyboardSymbolMap;
            }
            else
            {
                setToKeyboardTypeChoosen();
            }
            setForeground(*actualMap);
            button->setStyleSheet(StringSelectColor.arg(selectColor).arg(backgroundColor));
        }
        else
        {
            keyPressed = button->text();
            emit aNewKeyIsPressed();
        }
    }
}
void LitchiKeyboard::reinitKeyboard()
{
    verticalPosition = 1;
    horizontalPosition = 0;
    toUpper = false;
    toSymbol = false;

    setToKeyboardTypeChoosen();

    setForeground(*actualMap);
}
