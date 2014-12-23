#ifndef LITCHIKEYBOARD_H
#define LITCHIKEYBOARD_H

#include "QWidget"
#include "QPushButton"
#include "QKeyEvent"
#include "map"
#include "QMainWindow"

class LitchiKeyboard : public QMainWindow
{
    Q_OBJECT

    public:
        LitchiKeyboard(QString *keyAddress);
        void keyPressEvent(QKeyEvent* event);
        void setNewTheme(QString backgroundColor, QString selectColor, QString unselectColor);
        void reinitKeyboard();
        void setToKeyboardTypeChoosen();
        void setKeyboardType(int type);

    signals:
        void aNewKeyIsPressed();
        void hideTheKeyboard();

    private :
        void buttonPosition(std::map<int,std::vector<QPushButton*>> &map);
        void setForeground(std::map<int,std::vector<QPushButton*>> &map);


        int horizontalPosition;
        int verticalPosition;
        int type;
        int keyboardHeight;
        int keyboardWidth;

        bool toUpper;
        bool toSymbol;

        QString selectColor;
        QString unselectColor;
        QString backgroundColor;
        QString StringSelectColor;
        QString StringBackgroundColor;

        QString& keyPressed;

        std::map<int,std::vector<QPushButton*>>* keyboardLetterMap;
        std::map<int,std::vector<QPushButton*>>* keyboardSymbolMap;
        std::map<int,std::vector<QPushButton*>>* keyboardQWMap;


        std::map<int,std::vector<QPushButton*>>* actualMap;
};

#endif
