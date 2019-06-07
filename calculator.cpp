#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTriggered = false;
bool multTriggered = false;
bool addTriggered = false;
bool subTriggered = false;


Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    /*added stuff from here*/

    //Sets display to "0.0"
    ui->Display->setText(QString::number(calcVal));

    //create an array of pointers for number buttons
    QPushButton *numButtons[10];

    //assigning the number buttons (being calculator child widgets) to the array of ptr
    for (int i = 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);

        numButtons[i] = Calculator::findChild<QPushButton *>(butName);

        //connect the ptr to being pressed
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

}

Calculator::~Calculator()
{
    delete ui;
}

/* Pressing a number button*/
void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
    } else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));


    }
}



void Calculator::MathButtonPressed(){
    divTriggered = false;
    multTriggered = false;
    addTriggered = false;
    subTriggered = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTriggered = true;
    } else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTriggered = true;
    } else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTriggered = true;
    } else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0){
        subTriggered = true;
    }

    ui->Display->setText("");

}

void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if (addTriggered || subTriggered || multTriggered || divTriggered){
        if(addTriggered){
            solution = calcVal + dblDisplayVal;
        } else if(subTriggered){
            solution = calcVal - dblDisplayVal;
        } else if(multTriggered){
            solution = calcVal * dblDisplayVal;
        } else if(divTriggered){
            solution = calcVal / dblDisplayVal;
        }
    }

    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValeSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValeSign));
    }
}


