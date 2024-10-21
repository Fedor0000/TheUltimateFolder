#ifndef CALC_H
#define CALC_H

#include <QMainWindow>
#include "PluralityLogic.h"
#include <stack>

QT_BEGIN_NAMESPACE
namespace Ui { class Calc; }
QT_END_NAMESPACE

class Calc : public QMainWindow
{
    Q_OBJECT

public:
    Calc(QWidget *parent = nullptr);
    ~Calc();

    PluralityLogic storage;

    bool checkCorrectName();
    QString twoPluesShow();
    Plurality doAction(Plurality&, Plurality&);
    Plurality applyOperator(Plurality, Plurality, QString);
    Plurality handleFormula(const QString&);

public slots:
    void updateAll();
    void hideAll();
    void moder();

    void addPlu();
    void delPlu();
    void setUni();
    // Режимы, выбераемые модером при выборе режимов
    void setUniMode();
    void addPluMode();
    void delPluMode();
    void unblockBtns(); // разблокировка/чистка всего необходимого в режиме задания множеств
    void setPluMode();
    // для заполнения множеств
    void randomMode();
    void manualMode();
    void ifMode();
    void randomFill();
    void mainFill();
    void ifFill();
    void modeSelector();
    void checker();
    void actionsWithPlu();
    void saver();

    void mergeBTNclicked();
    void interBTNclicked();
    void minusBTNclicked();
    void simminusBTNclicked();
    void addingBTNclicked();

    void checkFormula();
    void formulaMode();

    void saveFormula();
private:
    Ui::Calc *ui;
};
#endif // CALC_H
