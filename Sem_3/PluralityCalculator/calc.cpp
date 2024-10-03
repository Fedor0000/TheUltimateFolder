#include "calc.h"
#include "ui_calc.h"

#include <queue>

uint64_t idx = 0; // индекс множества для заполнения
uint64_t idx2 = 0;

Calc::Calc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calc)
{
    ui->setupUi(this);

    hideAll();
    srand(time(NULL));

    ui->namePlu->setPlaceholderText("Введите имя множества");
    ui->namePluForSet->setPlaceholderText("Введите имя существующего множества");
    ui->onePluShow->setText("Введите существующее множество для отображения!");
    ui->firstPlu->setPlaceholderText("Имя первого множества"); ui->secondPlu->setPlaceholderText("Имя вторго множества");
    ui->resultPlu->setPlaceholderText("Имя множества, куда запишется результат");
    ui->resultPlu->setToolTip("Если написать несуществующее имя,\nсоздастся новое множество");
    ui->goBTN->setToolTip("Нажмите, чтобы сохранить результат\nв указанное множество или создать новое");
    ui->resultPluForFormula->setPlaceholderText("Имя множества, куда запишется результат");
    ui->goformulaBTN->setToolTip("Нажмите, чтобы сохранить результат\nв указанное множество или создать новое");
    ui->resultPluForFormula->setToolTip("Если написать несуществующее имя,\nсоздастся новое множество");
    ui->formula->setPlaceholderText("Введите сюда формулу");

    // установка валидатора на числа через пробелы
    QRegExp regExp("(-?\\d+\\s)*-?\\d+");
    QRegExpValidator *validator = new QRegExpValidator(regExp, ui->manualFillEdit);
    ui->manualFillEdit->setValidator(validator);

    QRegExp rx("[^)(∩∪∆\\\\¬]+");
    QRegExpValidator *validatorr = new QRegExpValidator(rx, this);
    ui->namePlu->setValidator(validatorr);

    connect(ui->confirmUniBTN, &QPushButton::clicked, this, &Calc::setUni);
    connect(ui->actionSelector, &QComboBox::currentTextChanged, this, &Calc::moder);
    connect(ui->confirmNameBTN, &QPushButton::clicked, this, &Calc::addPlu);
    connect(ui->DelBTN, &QPushButton::clicked, this, &Calc::delPlu);
    connect(ui->namePluForSet, &QLineEdit::textChanged, this, &Calc::unblockBtns);
    connect(ui->randomBTN, &QRadioButton::clicked, this, &Calc::randomMode);
    connect(ui->mainBTN, &QRadioButton::clicked, this, &Calc::manualMode);
    connect(ui->ifBTN, &QRadioButton::clicked, this, &Calc::ifMode);
    connect(ui->confirmFill, &QPushButton::clicked, this, &Calc::modeSelector);

    connect(ui->actionSelector2, &QComboBox::currentTextChanged, this, &Calc::checker);
    connect(ui->firstPlu, &QLineEdit::textChanged, this, &Calc::checker);
    connect(ui->secondPlu, &QLineEdit::textChanged, this, &Calc::checker);
    connect(ui->resultPlu, &QLineEdit::textChanged, this, &Calc::checker);

    connect(ui->goBTN, &QPushButton::clicked, this, &Calc::saver);

    connect(ui->resultPluForFormula, &QLineEdit::textChanged, this, &Calc::checkFormula);
    connect(ui->formula, &QLineEdit::textChanged, this, &Calc::checkFormula);

    connect(ui->mergeBTN, &QPushButton::clicked, this, &Calc::mergeBTNclicked);
    connect(ui->interBTN, &QPushButton::clicked, this, &Calc::interBTNclicked);
    connect(ui->minusBTN, &QPushButton::clicked, this, &Calc::minusBTNclicked);
    connect(ui->simminusBTN, &QPushButton::clicked, this, &Calc::simminusBTNclicked);
    connect(ui->addingBTN, &QPushButton::clicked, this, &Calc::addingBTNclicked);

    connect(ui->goformulaBTN, &QPushButton::clicked, this, &Calc::saveFormula);
}

Calc::~Calc()
{
    delete ui;
}

void Calc::updateAll()
{
    QString stringi;
    ui->uniShow->setText(QString("Текущий универсум: [" + QString::number(storage.uni.left) + "; " + QString::number(storage.uni.right) + "]"));

    stringi.push_back("Всего множеств: " + QString::number(storage.Pluralities.size()) + ((storage.Pluralities.empty()) ? "" : " - "));
    for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
    {
        if (i == storage.Pluralities.size()-1) stringi.push_back(storage.Pluralities[i].name + ".\n\n");
        else stringi.push_back(storage.Pluralities[i].name + ", ");
    }
    for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
    {
        stringi.push_back(QString::number(i+1) + ". " + storage.Pluralities[i].name + " {");
        if (storage.Pluralities[i].elements.empty()) stringi.push_back(" ");
        for (uint64_t j = 0; j < storage.Pluralities[i].elements.size(); j++)
        {
            if (j == (storage.Pluralities[i].elements.size()-1)) stringi.push_back(QString::number(storage.Pluralities[i].elements[j]));
            else stringi.push_back(QString::number(storage.Pluralities[i].elements[j]) + "; ");
        }
        if (i == (storage.Pluralities.size()-1)) stringi.push_back("}.");
        else stringi.push_back("};\n\n");
    }
    ui->pluesShow->setText(stringi);
}
void Calc::hideAll()
{
    ui->uniShow->hide(); ui->leftUni->hide(); ui->rightUni->hide(); ui->confirmUniBTN->hide(); // прячем все
    ui->pluesShow->hide(); ui->confirmNameBTN->hide(); ui->namePlu->hide();
    ui->DelBTN->hide();
    ui->ifBTN->hide();
    ui->onePluShow->hide();
    ui->mainBTN->hide();
    ui->randomBTN->hide();
    ui->namePluForSet->hide();
    ui->label->hide();
    ui->colvoRan->hide();
    ui->confirmFill->hide();
    ui->labelMan->hide();
    ui->manualFillEdit->hide();

    ui->chooseKratos->hide();
    ui->choosedSign->hide();
    ui->leftRange->hide();
    ui->rightRange->hide();
    ui->kratos->hide();
    ui->sign->hide();
    ui->labelIF->hide();
    ui->diapazon->hide();

    ui->actionSelector2->hide();
    ui->goBTN->hide();
    ui->firstPlu->hide();
    ui->secondPlu->hide();
    ui->twoPluShow->hide();
    ui->resultOfAction->hide();
    ui->resultPlu->hide();

    ui->resultOfFormula->hide();
    ui->goformulaBTN->hide();
    ui->resultPluForFormula->hide();
    ui->labelInstr->hide();
    ui->interBTN->hide();
    ui->mergeBTN->hide();
    ui->minusBTN->hide();
    ui->simminusBTN->hide();
    ui->addingBTN->hide();
    ui->formula->hide();
}

void Calc::moder()
{
    uint modeS = ui->actionSelector->currentIndex();
    switch (modeS)
    {
    case 0: hideAll(); break;
    case 1: setUniMode(); break;
    case 2: addPluMode(); break;
    case 3: delPluMode(); break;
    case 4: setPluMode(); break;
    case 5: actionsWithPlu(); break;
    case 6: formulaMode(); break;
    }
}

void Calc::addPlu()
{
    if (ui->namePlu->text().isEmpty()) return;
    for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
    {
        if (ui->namePlu->text() == storage.Pluralities[i].name) return;
    }
    Plurality newPly;
    newPly.name = ui->namePlu->text();
    storage.Pluralities.push_back(newPly);
    ui->namePlu->setText("");
    updateAll();
}

void Calc::delPlu()
{
    if (ui->namePlu->text().isEmpty()) return;
    for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
    {
        if (ui->namePlu->text() == storage.Pluralities[i].name)
        {
            storage.Pluralities.erase(storage.Pluralities.begin()+i);
            ui->namePlu->setText("");
            break;
        }
    }
    updateAll();
}

void Calc::setUni()
{
    if (!(ui->leftUni->value() <= ui->rightUni->value())) return;
    storage.uni.left = ui->leftUni->value();
    storage.uni.right = ui->rightUni->value();
    for (uint64_t i = 0; i < storage.Pluralities.size(); i++) // проверяем все множества на вшивость
    {
        std::vector<int64_t> tmp;
        for (uint64_t j = 0; j < storage.Pluralities[i].elements.size(); j++) // проверяем во всех множествах элементы и удаляем несуществующие
        {
            if (!((storage.Pluralities[i].elements[j] < storage.uni.left) || (storage.Pluralities[i].elements[j] > storage.uni.right))) // если элемент не лезет в ворота
            {
                tmp.push_back(storage.Pluralities[i].elements[j]); // стираем нехороший элемент
            }
        }
        storage.Pluralities[i].elements = tmp;
    }
    updateAll();
}

void Calc::setUniMode()
{
    hideAll();
    updateAll();
    ui->uniShow->setHidden(false);
    ui->confirmUniBTN->setHidden(false);
    ui->leftUni->setHidden(false); ui->rightUni->setHidden(false);
}

void Calc::addPluMode()
{
    hideAll();
    updateAll();
    ui->uniShow->setHidden(false);
    ui->namePlu->setHidden(false);
    ui->confirmNameBTN->setHidden(false);
    ui->pluesShow->setHidden(false);
    ui->namePlu->setText("");
}

void Calc::delPluMode()
{
    hideAll();
    updateAll();
    ui->uniShow->setHidden(false);
    ui->namePlu->setHidden(false);
    ui->DelBTN->setHidden(false);
    ui->pluesShow->setHidden(false);
    ui->namePlu->setText("");
}

bool Calc::checkCorrectName()
{
    if (ui->namePluForSet->text().isEmpty()) return false;
    for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
    {
        if (ui->namePluForSet->text() == storage.Pluralities[i].name)
        {
            return true;
        }
    }
    return false;
}

void Calc::unblockBtns()
{
    if (checkCorrectName())
    {
        ui->mainBTN->setEnabled(true);
        ui->randomBTN->setEnabled(true);
        ui->ifBTN->setEnabled(true);
        ui->confirmFill->setEnabled(true);
        ui->colvoRan->setEnabled(true);
        ui->label->setEnabled(true);
        ui->labelMan->setEnabled(true);
        ui->manualFillEdit->setEnabled(true);
        ui->chooseKratos->setEnabled(true);
        ui->choosedSign->setEnabled(true);
        ui->leftRange->setEnabled(true);
        ui->rightRange->setEnabled(true);
        ui->kratos->setEnabled(true);
        ui->sign->setEnabled(true);
        ui->labelIF->setEnabled(true);
        ui->diapazon->setEnabled(true);
        for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
        {
            if (ui->namePluForSet->text() == storage.Pluralities[i].name)
            {
                idx = i;
                break;
            }
        }
        QString stringi;
        stringi.push_back("Элементов: " + QString::number(storage.Pluralities[idx].elements.size()) + ". " + storage.Pluralities[idx].name + " {" );
        if (storage.Pluralities[idx].elements.empty()) stringi.push_back(" ");
        for (uint64_t j = 0; j < storage.Pluralities[idx].elements.size(); j++)
        {
            if (j == (storage.Pluralities[idx].elements.size()-1)) stringi.push_back(QString::number(storage.Pluralities[idx].elements[j]));
            else stringi.push_back(QString::number(storage.Pluralities[idx].elements[j]) + "; ");
        }
        stringi.push_back("}");
        ui->onePluShow->setText(stringi);
        ui->colvoRan->setMaximum(storage.uni.right - storage.uni.left + 1);
    }
    else
    {
        ui->mainBTN->setEnabled(false);
        ui->randomBTN->setEnabled(false);
        ui->ifBTN->setEnabled(false);
        ui->confirmFill->setEnabled(false);
        ui->colvoRan->setEnabled(false);
        ui->label->setEnabled(false);
        ui->labelMan->setEnabled(false);
        ui->manualFillEdit->setEnabled(false);
        ui->chooseKratos->setEnabled(false);
        ui->choosedSign->setEnabled(false);
        ui->leftRange->setEnabled(false);
        ui->rightRange->setEnabled(false);
        ui->kratos->setEnabled(false);
        ui->sign->setEnabled(false);
        ui->labelIF->setEnabled(false);
        ui->diapazon->setEnabled(false);
        ui->onePluShow->setText("Введите существующее множество для отображения!");
    }
    ui->manualFillEdit->setText("");
    ui->colvoRan->setValue(0);
    ui->chooseKratos->setValue(0);
    ui->choosedSign->setCurrentIndex(0);
    ui->kratos->setChecked(false);
    ui->sign->setChecked(false);
    ui->diapazon->setChecked(false);
    ui->leftRange->setMinimum(storage.uni.left); ui->leftRange->setMaximum(storage.uni.right); ui->leftRange->setValue(storage.uni.left);
    ui->rightRange->setMinimum(storage.uni.left); ui->rightRange->setMaximum(storage.uni.right); ui->rightRange->setValue(storage.uni.right);
}

void Calc::setPluMode()
{
    hideAll();
    updateAll();
    ui->uniShow->setHidden(false);
    ui->namePluForSet->setHidden(false);
    ui->onePluShow->setHidden(false);
    ui->mainBTN->setHidden(false);
    ui->randomBTN->setHidden(false);
    ui->ifBTN->setHidden(false);
    ui->confirmFill->setHidden(false);
    ui->colvoRan->setHidden(false);
    ui->label->setHidden(false);
    ui->randomBTN->setChecked(true);
    ui->mainBTN->setChecked(false);
    ui->ifBTN->setChecked(false);
    ui->namePluForSet->setText("");
    ui->confirmFill->setToolTip("При заполнении множество будет перезаписано");
}

void Calc::randomMode()
{
    ui->colvoRan->setHidden(false);
    ui->label->setHidden(false);
    ui->colvoRan->setValue(0);
    ui->confirmFill->setToolTip("При заполнении множество будет перезаписано");
    ui->labelMan->setHidden(true);
    ui->manualFillEdit->setHidden(true);
    ui->chooseKratos->hide();
    ui->choosedSign->hide();
    ui->leftRange->hide();
    ui->rightRange->hide();
    ui->kratos->hide();
    ui->sign->hide();
    ui->labelIF->hide();
    ui->diapazon->hide();
}

void Calc::manualMode()
{
    ui->colvoRan->setHidden(true);
    ui->label->setHidden(true);
    ui->confirmFill->setToolTip("При заполнении элементы будут добавлены в существующее множество");
    ui->labelMan->setHidden(false);
    ui->manualFillEdit->setHidden(false);
    ui->chooseKratos->hide();
    ui->choosedSign->hide();
    ui->leftRange->hide();
    ui->rightRange->hide();
    ui->kratos->hide();
    ui->sign->hide();
    ui->labelIF->hide();
    ui->diapazon->hide();
}

void Calc::ifMode()
{
    ui->colvoRan->setHidden(true);
    ui->label->setHidden(true);
    ui->confirmFill->setToolTip("При заполнении элементы будут добавлены в существующее множество");
    ui->labelMan->setHidden(true);
    ui->manualFillEdit->setHidden(true);
    ui->chooseKratos->setHidden(false);
    ui->choosedSign->setHidden(false);
    ui->leftRange->setHidden(false);
    ui->rightRange->setHidden(false);
    ui->kratos->setHidden(false);
    ui->sign->setHidden(false);
    ui->labelIF->setHidden(false);
    ui->diapazon->setHidden(false);
}

void Calc::randomFill()
{
    storage.Pluralities[idx].elements.clear();
    std::vector<int64_t> tmp;
    for (int64_t i = storage.uni.left; i <=storage.uni.right; i++) tmp.push_back(i);
    for (int64_t i = 0; i < ui->colvoRan->value(); i++)
    {
        int64_t t = (rand()*rand()) % tmp.size();
        storage.Pluralities[idx].elements.push_back(tmp[t]);
        tmp.erase(tmp.begin()+t);
    }
    sort(storage.Pluralities[idx].elements.begin(), storage.Pluralities[idx].elements.end());
    unblockBtns();
}

std::vector<int64_t> converter(std::string input)
{
    std::vector<int64_t> result = { 0 };
    bool negative = false;
    for (int i = 0; i < (int)input.size() - 1; ++i)
    {
        if ((input[i] == ' ') && negative)
        {
            result.back() *= -1;
            negative = false;
            result.push_back(0);
        }
        else if (input[i] == ' ')
        {
            result.push_back(0);
        }
        else if (input[i] == '-')
        {
            negative = true;
        }
        else
        {
            result.back() *= 10;
            result.back() += input[i] - '0';
        }
    }
    if (negative) result.back() *= -1;
    return result;
}

void Calc::mainFill()
{
    std::string input(ui->manualFillEdit->text().toStdString()); if (input[input.size()-1] == '-') input.pop_back();
    if (input.empty()) return;
    Plurality newPly;
    newPly.name = storage.Pluralities[idx].name;
    std::vector<int64_t> tmp = converter(input + ((input[input.size()-1] == ' ') ? "" : " "));
    for (uint64_t i = 0; i < tmp.size(); i++) if ((tmp[i] >= storage.uni.left) && (tmp[i] <= storage.uni.right)) newPly.elements.push_back(tmp[i]);
    storage.Pluralities[idx] = storage.merger(storage.Pluralities[idx], newPly);
    storage.Pluralities[idx].name = newPly.name;
    ui->manualFillEdit->setText("");
    unblockBtns();
}

void Calc::ifFill()
{
    if (!ui->sign->isChecked() && !ui->kratos->isChecked() && !ui->diapazon->isChecked()) return; // ничего не выбрано
    if (ui->sign->isChecked() && !ui->kratos->isChecked() && !ui->diapazon->isChecked()) // со знаком
    {
        Plurality newPly;
        newPly.name = storage.Pluralities[idx].name;
        if (ui->choosedSign->currentIndex() == 0)
        {
            for (int64_t i = storage.uni.left; i <= storage.uni.right; i++) if (i >= 0) newPly.elements.push_back(i);
        }
        else
        {
            for (int64_t i = storage.uni.left; i <= storage.uni.right; i++) if (i < 0) newPly.elements.push_back(i);
        }
        storage.Pluralities[idx] = storage.merger(storage.Pluralities[idx], newPly);
        storage.Pluralities[idx].name = newPly.name;
        unblockBtns();
        return;
    }
    if (!ui->sign->isChecked() && ui->kratos->isChecked() && !ui->diapazon->isChecked()) // кратные
    {
        if (ui->chooseKratos->value() <= 0) return;
        Plurality newPly;
        newPly.name = storage.Pluralities[idx].name;
        for (int64_t i = storage.uni.left; i <= storage.uni.right; i++) if ((i % ui->chooseKratos->value()) == 0) newPly.elements.push_back(i);
        storage.Pluralities[idx] = storage.merger(storage.Pluralities[idx], newPly);
        storage.Pluralities[idx].name = newPly.name;
        unblockBtns();
        return;
    }
    if (!ui->sign->isChecked() && !ui->kratos->isChecked() && ui->diapazon->isChecked()) // в диапазоне
    {
        if (ui->rightRange->value() < ui->leftRange->value()) return;
        Plurality newPly;
        newPly.name = storage.Pluralities[idx].name;
        for (int64_t i = ui->leftRange->value(); i <= ui->rightRange->value(); i++) newPly.elements.push_back(i);
        storage.Pluralities[idx] = storage.merger(storage.Pluralities[idx], newPly);
        storage.Pluralities[idx].name = newPly.name;
        unblockBtns();
        return;
    }
    if (ui->sign->isChecked() && ui->kratos->isChecked() && ui->diapazon->isChecked()) // кратные со знаком в диапазоне
    {
        if (ui->chooseKratos->value() <= 0) return;
        if (ui->rightRange->value() < ui->leftRange->value()) return;
        Plurality newPly;
        newPly.name = storage.Pluralities[idx].name;
        if (ui->choosedSign->currentIndex() == 0)
        {
            for (int64_t i = ui->leftRange->value(); i <= ui->rightRange->value(); i++) if ((i >= 0) && ((i % ui->chooseKratos->value()) == 0)) newPly.elements.push_back(i);
        }
        else
        {
            for (int64_t i = ui->leftRange->value(); i <= ui->rightRange->value(); i++) if ((i < 0) && ((i % ui->chooseKratos->value()) == 0)) newPly.elements.push_back(i);
        }
        storage.Pluralities[idx] = storage.merger(storage.Pluralities[idx], newPly);
        storage.Pluralities[idx].name = newPly.name;
        unblockBtns();
        return;
    }
    if (ui->sign->isChecked() && !ui->kratos->isChecked() && ui->diapazon->isChecked()) // со знаком в диапазоне
    {
        if (ui->rightRange->value() < ui->leftRange->value()) return;
        Plurality newPly;
        newPly.name = storage.Pluralities[idx].name;
        if (ui->choosedSign->currentIndex() == 0)
        {
            for (int64_t i = ui->leftRange->value(); i <= ui->rightRange->value(); i++) if (i >= 0) newPly.elements.push_back(i);
        }
        else
        {
            for (int64_t i = ui->leftRange->value(); i <= ui->rightRange->value(); i++) if (i < 0) newPly.elements.push_back(i);
        }
        storage.Pluralities[idx] = storage.merger(storage.Pluralities[idx], newPly);
        storage.Pluralities[idx].name = newPly.name;
        unblockBtns();
        return;
    }
    if (ui->sign->isChecked() && ui->kratos->isChecked() && !ui->diapazon->isChecked()) // кратные со знаком
    {
        if (ui->chooseKratos->value() <= 0) return;
        if (ui->rightRange->value() < ui->leftRange->value()) return;
        Plurality newPly;
        newPly.name = storage.Pluralities[idx].name;
        if (ui->choosedSign->currentIndex() == 0)
        {
            for (int64_t i = storage.uni.left; i <= storage.uni.right; i++) if ((i >= 0) && ((i % ui->chooseKratos->value()) == 0)) newPly.elements.push_back(i);
        }
        else
        {
            for (int64_t i = storage.uni.left; i <= storage.uni.right; i++) if ((i < 0) && ((i % ui->chooseKratos->value()) == 0)) newPly.elements.push_back(i);
        }
        storage.Pluralities[idx] = storage.merger(storage.Pluralities[idx], newPly);
        storage.Pluralities[idx].name = newPly.name;
        unblockBtns();
        return;
    }
    if (!ui->sign->isChecked() && ui->kratos->isChecked() && ui->diapazon->isChecked()) // кратные в диапазоне
    {
        if (ui->chooseKratos->value() <= 0) return;
        if (ui->rightRange->value() < ui->leftRange->value()) return;
        Plurality newPly;
        newPly.name = storage.Pluralities[idx].name;
        for (int64_t i = ui->leftRange->value(); i <= ui->rightRange->value(); i++) if ((i % ui->chooseKratos->value()) == 0) newPly.elements.push_back(i);
        storage.Pluralities[idx] = storage.merger(storage.Pluralities[idx], newPly);
        storage.Pluralities[idx].name = newPly.name;
        unblockBtns();
        return;
    }
}

QString Calc::twoPluesShow()
{
    QString stringi;
    stringi.push_back("Элементов: " + QString::number(storage.Pluralities[idx].elements.size()) + ". " + storage.Pluralities[idx].name + " {" );
    if (storage.Pluralities[idx].elements.empty()) stringi.push_back(" ");
    for (uint64_t j = 0; j < storage.Pluralities[idx].elements.size(); j++)
    {
        if (j == (storage.Pluralities[idx].elements.size()-1)) stringi.push_back(QString::number(storage.Pluralities[idx].elements[j]));
        else stringi.push_back(QString::number(storage.Pluralities[idx].elements[j]) + "; ");
    }
    stringi.push_back("}");
    if (ui->actionSelector2->currentIndex() != 4)
    {
        stringi.push_back(";\n\nЭлементов: " + QString::number(storage.Pluralities[idx2].elements.size()) + ". " + storage.Pluralities[idx2].name + " {" );
        if (storage.Pluralities[idx2].elements.empty()) stringi.push_back(" ");
        for (uint64_t j = 0; j < storage.Pluralities[idx2].elements.size(); j++)
        {
            if (j == (storage.Pluralities[idx2].elements.size()-1)) stringi.push_back(QString::number(storage.Pluralities[idx2].elements[j]));
            else stringi.push_back(QString::number(storage.Pluralities[idx2].elements[j]) + "; ");
        }
        stringi.push_back("}");
    }
    return stringi;
}

Plurality Calc::doAction(Plurality &fir, Plurality &sec)
{
    switch (ui->actionSelector2->currentIndex())
    {
    case 0: return storage.intersection(fir, sec);
    case 1: return storage.merger(fir, sec);
    case 2: return storage.minus(fir, sec);
    case 3: return storage.symmetricalMinus(fir, sec);
    case 4: return storage.addToUniversum(fir);
    default:
    {
        Plurality error; error.name = "error";
        return error;
    }
    }
}

void Calc::checker()
{
    bool allOK = true;
    if (ui->firstPlu->text().isEmpty()) allOK = false;
    if (storage.Pluralities.empty()) allOK = false;
    for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
    {
        if ((allOK == false) && (i == 0)) break;
        if (ui->firstPlu->text() == storage.Pluralities[i].name)
        {
            allOK = true;
            idx = i;
            break;
        }
        else allOK = false;
    }
    if (ui->actionSelector2->currentIndex() != 4) // если у нас объединение, то второго множества нет
    {
        ui->secondPlu->setEnabled(true);
        for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
        {
            if ((allOK == false) && (i == 0)) break;
            if (ui->secondPlu->text() == storage.Pluralities[i].name)
            {
              allOK = true;
              idx2 = i;
              break;
            }
            else allOK = false;
        }
    }
    else
    {
        ui->secondPlu->setText("");
        ui->secondPlu->setEnabled(false);
    }

    if (allOK)
    {
        ui->twoPluShow->setText(twoPluesShow());
        if (ui->resultPlu->text().isEmpty())
        {
            ui->goBTN->setEnabled(false);
            ui->resultOfAction->setText("Для предпросмотра результата введите корректные имена множеств и имя множества-результата!");
        }
        else
        {
            Plurality tmp; tmp.name = ui->resultPlu->text();
            tmp.elements = doAction(storage.Pluralities[idx], storage.Pluralities[idx2]).elements;
            ui->goBTN->setEnabled(true);
            QString stringi;
            stringi.push_back("Предварительный просмотр результата:\nЭлементов: " + QString::number(tmp.elements.size()) + ". " + tmp.name + " {" );
            if (tmp.elements.empty()) stringi.push_back(" ");
            for (uint64_t j = 0; j < tmp.elements.size(); j++)
            {
                if (j == (tmp.elements.size()-1)) stringi.push_back(QString::number(tmp.elements[j]));
                else stringi.push_back(QString::number(tmp.elements[j]) + "; ");
            }
            stringi.push_back("}");
            ui->resultOfAction->setText(stringi);
        }
    }
    else
    {
        ui->goBTN->setEnabled(false);
        ui->twoPluShow->setText("Введите корректные имена множеств!");
        ui->resultOfAction->setText("Для предпросмотра результата введите корректные имена множеств и имя множества-результата!");
    }
}

void Calc::saver()
{
    Plurality result;
    uint64_t index = UINT64_MAX;
    for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
    {
        if (ui->resultPlu->text() == storage.Pluralities[i].name)
        {
            index = i;
            break;
        }
    }
    if (index == UINT64_MAX)
    {
        result = doAction(storage.Pluralities[idx], storage.Pluralities[idx2]);
        result.name = ui->resultPlu->text();
        storage.Pluralities.push_back(result);
    }
    else
    {
        storage.Pluralities[index].elements = doAction(storage.Pluralities[idx], storage.Pluralities[idx2]).elements;
    }
    ui->firstPlu->setText(""); ui->secondPlu->setText(""); ui->resultPlu->setText("");
    ui->resultOfAction->setText("Операция выполнена успешно!");
}

void Calc::actionsWithPlu()
{
    hideAll();
    ui->actionSelector2->setHidden(false);
    ui->goBTN->setHidden(false);
    ui->firstPlu->setHidden(false);
    ui->secondPlu->setHidden(false);
    ui->twoPluShow->setHidden(false);
    ui->resultOfAction->setHidden(false);
    ui->uniShow->setHidden(false);
    ui->resultPlu->setHidden(false);
    ui->actionSelector2->setCurrentIndex(0);
    ui->firstPlu->setText("");
    ui->secondPlu->setText("");
    ui->resultPlu->setText("");
    checker();
    updateAll();
}

void Calc::modeSelector()
{
    if (ui->randomBTN->isChecked())
    {
        randomFill();
        return;
    }
    if (ui->mainBTN->isChecked())
    {
        mainFill();
        return;
    }
    if (ui->ifBTN->isChecked())
    {
        ifFill();
        return;
    }
}

void Calc::mergeBTNclicked()
{
    uint64_t indeh = ui->formula->cursorPosition();
    QString stringi = ui->formula->text();
    stringi.insert(indeh, "∪");
    ui->formula->setText(stringi);
}
void Calc::interBTNclicked()
{
    uint64_t indeh = ui->formula->cursorPosition();
    QString stringi = ui->formula->text();
    stringi.insert(indeh, "∩");
    ui->formula->setText(stringi);
}
void Calc::minusBTNclicked()
{
    uint64_t indeh = ui->formula->cursorPosition();
    QString stringi = ui->formula->text();
    stringi.insert(indeh, "\\");
    ui->formula->setText(stringi);
}
void Calc::simminusBTNclicked()
{
    uint64_t indeh = ui->formula->cursorPosition();
    QString stringi = ui->formula->text();
    stringi.insert(indeh, "∆");
    ui->formula->setText(stringi);
}
void Calc::addingBTNclicked()
{
    uint64_t indeh = ui->formula->cursorPosition();
    QString stringi = ui->formula->text();
    stringi.insert(indeh, "¬");
    ui->formula->setText(stringi);
}

Plurality Calc::applyOperator(Plurality a, Plurality b, QString op)
{
    if (op[0] == "∪") return storage.merger(a, b);
    else if (op[0] == "∩") return storage.intersection(a, b);
    else if (op[0] == "\\") return storage.minus(a, b);
    else if (op[0] == "∆") return storage.symmetricalMinus(a, b);
    else
    {
        throw std::exception();
    }
}

QString getSetName(const QString& expr, int& i)
{
    QString name;
    while (i < expr.size() && expr[i] != "∩" && expr[i] != "∪" && expr[i] != "∆" && expr[i] != "\\" && expr[i] != "(" && expr[i] != ")" && expr[i] != "¬")
    {
        name += expr[i++];
    }
    --i;
    return name;
}

Plurality Calc::handleFormula(const QString& expr)
{
    Plurality first; Plurality second; QString action; bool writeTOfirst = true; bool needAction = false;
    for (int i = 0; i < expr.size(); i++)
    {
        QChar token = expr[i];
        if (token != "∩" && token != "∪" && token != "∆" && token != "\\" && token != "(" && token != ")" && token != "¬")
        {
            QString setName = getSetName(expr, i);
            for (uint64_t l = 0; l < storage.Pluralities.size(); l++)
            {
                if (storage.Pluralities[l].name == setName)
                {
                    if (writeTOfirst) first = storage.Pluralities[l];
                    else
                    {
                        second = storage.Pluralities[l];
                        needAction = true;
                    }
                    break;
                }
                if (l == storage.Pluralities.size()-1)
                {
                    throw std::exception();
                }
            }
        }
        else if (token == "¬")
        {
            i++;
            if (writeTOfirst && expr[i] != "(")
            {
                QString setName = getSetName(expr, i);
                for (uint64_t l = 0; l < storage.Pluralities.size(); l++)
                {
                    if (storage.Pluralities[l].name == setName)
                    {
                        first = storage.Pluralities[l];
                        break;
                    }
                    if (l == storage.Pluralities.size()-1)
                    {
                        throw std::exception();
                    }
                }
                first = storage.addToUniversum(first);
                writeTOfirst = false;
            }
            else if (writeTOfirst && expr[i] == "(")
            {
                i++;
                QString subFormula;
                uint openBracket = 0, closeBracket = 0;
                while (true)
                {
                    if (expr[i] == "(") openBracket++;
                    if ((closeBracket <= openBracket) && expr[i] == ")") closeBracket++;
                    if ((closeBracket > openBracket) && expr[i] == ")") break;
                    subFormula.push_back(expr[i]);
                    i++;
                }
                first = handleFormula(subFormula);
                first = storage.addToUniversum(first);
                writeTOfirst = false;
            }
            else if (!writeTOfirst && expr[i] != "(")
            {
                QString setName = getSetName(expr, i);
                for (uint64_t l = 0; l < storage.Pluralities.size(); l++)
                {
                    if (storage.Pluralities[l].name == setName)
                    {
                        second = storage.Pluralities[l];
                        break;
                    }
                    if (l == storage.Pluralities.size()-1)
                    {
                        throw std::exception();
                    }
                }
                second = storage.addToUniversum(second);
                first = applyOperator(first, second, action);
            }
            else if (!writeTOfirst && expr[i] == "(")
            {
                i++;
                QString subFormula;
                uint openBracket = 0, closeBracket = 0;
                while (true)
                {
                    if (expr[i] == "(") openBracket++;
                    if ((closeBracket <= openBracket) && expr[i] == ")") closeBracket++;
                    if ((closeBracket > openBracket) && expr[i] == ")") break;
                    subFormula.push_back(expr[i]);
                    i++;
                }
                second = handleFormula(subFormula);
                second = storage.addToUniversum(second);
                first = applyOperator(first, second, action);
            }
        }
        else if (token == "(")
        {
            i++;
            QString subFormula;
            uint openBracket = 0, closeBracket = 0;
            while (true)
            {
                if (expr[i] == "(") openBracket++;
                if ((closeBracket <= openBracket) && expr[i] == ")") closeBracket++;
                if ((closeBracket > openBracket) && expr[i] == ")") break;
                subFormula.push_back(expr[i]);
                i++;
            }
            if (writeTOfirst) first = handleFormula(subFormula);
            else
            {
                second = handleFormula(subFormula);
                needAction = true;
            }
        }
        else if (token == "∪")
        {
            writeTOfirst = false;
            action = "∪";
        }
        else if (token == "∩")
        {
            writeTOfirst = false;
            action = "∩";
        }
        else if (token == "∆")
        {
            writeTOfirst = false;
            action = "∆";
        }
        else if (token == "\\")
        {
            writeTOfirst = false;
            action = "\\";
        }
        if (needAction)
        {
            first = applyOperator(first, second, action);
            needAction = false;
        }
    }
    return first;
}

bool checkString(const QString& input) {
    QRegExp rx(".*[∩∪∆\\\\]{2,}.*|.*[∩∪∆\\\\]$|.*\\([∩∪∆\\\\].*|.*\\)[^∩∪∆)\\\\].*");
    return !rx.exactMatch(input);
}
bool checkString2(const QString& input)
{
    bool hu = false;
    for (int i = 0; i < input.size(); i++)
    {
        if (hu && (input[i] == "¬")) return false;
        if (input[i] == "¬") hu = true;
        if ((hu == true) && (input[i] == "∩" || input[i] == "∪" || input[i] == "\\" || input[i] == "∆" || input[i] == ")")) return false;
        if (input[i] != "¬") hu = false;
        if (i == (input.size()-1) && (input[i] == "¬")) return false;
    }
    return true;
}

void Calc::checkFormula()
{
    bool formulaCorrect = true;
    if (ui->formula->text().isEmpty()) formulaCorrect = false;
    if (ui->resultPluForFormula->text().isEmpty()) formulaCorrect = false;
    if (storage.Pluralities.empty()) formulaCorrect = false;
    if (formulaCorrect)
    {
        std::string expr = ui->formula->text().toStdString();
        std::stack<QChar> s;
        for (char ch : expr)
        {
            if (ch == '(')
            {
                s.push(ch);
            }
            else if (ch == ')')
            {
                if (s.empty() || s.top() != '(')
                {
                    formulaCorrect = false;
                    break; // Прерываем цикл при обнаружении ошибки
                }
                s.pop();
            }
        }
        if (!s.empty()) // Проверка на оставшиеся открытые скобки
        {
            formulaCorrect = false;
        }
    }

    if (formulaCorrect)
    {
        if (!checkString(ui->formula->text())) formulaCorrect = false;
        if (!checkString2(ui->formula->text())) formulaCorrect = false;
    }

    if (formulaCorrect)
    {

            Plurality tmp; tmp.name = ui->resultPluForFormula->text();
            try
            {
                tmp.elements = handleFormula(ui->formula->text()).elements;
                ui->goformulaBTN->setEnabled(true);
                QString stringi;
                stringi.push_back("Предварительный просмотр результата:\nЭлементов: " + QString::number(tmp.elements.size()) + ". " + tmp.name + " {" );
                if (tmp.elements.empty()) stringi.push_back(" ");
                for (uint64_t j = 0; j < tmp.elements.size(); j++)
                {
                    if (j == (tmp.elements.size()-1)) stringi.push_back(QString::number(tmp.elements[j]));
                    else stringi.push_back(QString::number(tmp.elements[j]) + "; ");
                }
                stringi.push_back("}");
                ui->resultOfFormula->setText(stringi);
            }
            catch (...)
            {
                ui->resultOfFormula->setText("Для предпросмотра результата введите корректную формулу и имя множества-результата!");
            }

    }
    else
    {
        ui->goformulaBTN->setEnabled(false);
        ui->resultOfFormula->setText("Для предпросмотра результата введите корректную формулу и имя множества-результата!");
    }
}

void Calc::formulaMode()
{
    hideAll();
    updateAll();
    ui->resultOfFormula->setHidden(false);
    ui->goformulaBTN->setHidden(false);
    ui->resultPluForFormula->setHidden(false);
    ui->labelInstr->setHidden(false);
    ui->interBTN->setHidden(false);
    ui->mergeBTN->setHidden(false);
    ui->minusBTN->setHidden(false);
    ui->simminusBTN->setHidden(false);
    ui->addingBTN->setHidden(false);
    ui->formula->setHidden(false);
    ui->uniShow->setHidden(false);
    ui->resultOfFormula->setText("");
    ui->resultPluForFormula->setText("");
    ui->formula->setText("");
    checkFormula();
}

void Calc::saveFormula()
{
    Plurality result;
    uint64_t index = UINT64_MAX;
    for (uint64_t i = 0; i < storage.Pluralities.size(); i++)
    {
        if (ui->resultPluForFormula->text() == storage.Pluralities[i].name)
        {
            index = i;
            break;
        }
    }
    if (index == UINT64_MAX)
    {
        result = handleFormula(ui->formula->text());
        result.name = ui->resultPluForFormula->text();
        storage.Pluralities.push_back(result);
    }
    else
    {
        storage.Pluralities[index].elements = handleFormula(ui->formula->text()).elements;
    }
    ui->formula->setText(""); ui->resultPluForFormula->setText("");
    ui->resultOfFormula->setText("Операция выполнена успешно!");
}
