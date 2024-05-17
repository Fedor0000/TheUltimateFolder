#include "tramvai.h"
#include "ui_tramvai.h"
#include <QRegExpValidator>

struct otchet // вспомогательная структоура для хранения отчета за день
{
    uint64_t plusTram = 0; // доход
    uint64_t minusElectricity = 0; // расход на электричество
    uint64_t minusRepair = 0; // расход на ремонт
    uint64_t repairs = 0; // количество ремонтов
    uint64_t minusCrash = 0; // расходы на аварии
    uint64_t crashes = 0; // количество аварий
    uint64_t repairPath = 0; // расходы на ремонт трамвайных путей
    void clear() // метод отчистки
    {
        plusTram = 0;
        minusElectricity = 0;
        minusRepair = 0;
        repairs = 0;
        minusCrash = 0;
        crashes = 0;
        repairPath = 0;
    }
};

otchet svodka; // для хранения отчета

QString prognoz = ""; // для хранения прогноза на день


static bool randomByPercents(int percent) // рандомно по проценту
{
    if ((rand() % (100 - 0 + 1) + 0) <= percent) return true;
    else return false;
}

static int randomBetween(int low, int high) // рандом между двумя числами
{
    return ((rand()*rand()) % ((high + 1) - low) + low);
}

Tramvai::Tramvai(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tramvai)
{
    ui->setupUi(this);

    // коннекты слотов и кнопок
    connect(ui->newGameBTN, &QPushButton::clicked, this, &Tramvai::newGame);
    connect(ui->buyTramBTN, &QPushButton::clicked, this, &Tramvai::buyTram);
    connect(ui->newMarshrutBTN, &QPushButton::clicked, this, &Tramvai::buyMarshrut);
    connect(ui->setTramvaiBTN, &QPushButton::clicked, this, &Tramvai::setTrams);
    connect(ui->ubgradeBiletsBTN, &QPushButton::clicked, this, &Tramvai::upgradeBilet);
    connect(ui->upMarshrutInput, &QLineEdit::textChanged, this, &Tramvai::selectUpM);
    connect(ui->upMarshrutBTN, &QPushButton::clicked, this, &Tramvai::upMarshrut);
    connect(ui->newDayBTN, &QPushButton::clicked, this, &Tramvai::nextDay);

    // установка текста подсказки в поля ввода
    ui->setTramKolvoInput->setPlaceholderText("Кол-во трамваев");
    ui->marshrutInput->setPlaceholderText("Маршрут");
    ui->upMarshrutInput->setPlaceholderText("Маршрут");

    // сначала доступна только кнопка НАЧАТЬ
    blockAllBTNs();
    ui->newGameBTN->setEnabled(true);

    // устанавливаем ограничение ввода
    QRegExp re("^[0-9]*[1-9][0-9]*$");
    QRegExpValidator*v = new QRegExpValidator(re);
    ui->marshrutInput->setValidator(v);
    ui->setTramKolvoInput->setValidator(v);
    ui->upMarshrutInput->setValidator(v);
}

void Tramvai::blockAllBTNs() // блокировка всех кнопок
{
    ui->buyTramBTN->setEnabled(false);
    ui->newDayBTN->setEnabled(false);
    ui->newGameBTN->setEnabled(false);
    ui->newMarshrutBTN->setEnabled(false);
    ui->setTramvaiBTN->setEnabled(false);
    ui->ubgradeBiletsBTN->setEnabled(false);
    ui->upMarshrutBTN->setEnabled(false);
}
void Tramvai::unblockAllBTNs() // разблокировка всех кнопок
{
    ui->buyTramBTN->setEnabled(true);
    ui->newDayBTN->setEnabled(true);
    ui->newGameBTN->setEnabled(true);
    ui->newMarshrutBTN->setEnabled(true);
    ui->setTramvaiBTN->setEnabled(true);
    ui->ubgradeBiletsBTN->setEnabled(true);
    ui->upMarshrutBTN->setEnabled(true);
}

void Tramvai::renderPrognoz() // вывод прогнозов и распределения трамваев по маршрутам
{
    prognoz = "";
    prognoz.push_back("День №" + QString::number(day) + "\nВсего трамваев: " + QString::number(vsegoTramvaev) + "\n\n");
    for (uint64_t i = 0; i < tramsOnMarsruts.size(); i++)
    {
        prognoz.push_back("Маршрут №"+QString::number(i)+ ": " + "\nТрамваи: " + QString::number(tramsOnMarsruts[i]) + "\nМинимально: " + QString::number(minTramsOnMarshruts[i]) + "\nМаксимально: " + QString::number(maxTramsOnMarshruts[i]) + "\nЛюди: " + (manyPeople[i] == 1 ? "много" : (manyPeople[i] == -1 ? "мало" : "средне")) + "\n\n");
    }
    uint64_t nonUsed = vsegoTramvaev;
    for(uint64_t i = 0; i < tramsOnMarsruts.size(); i++)
    {
        nonUsed -= tramsOnMarsruts[i];
    }
    prognoz.push_back("Неиспользовано трамваев: " + QString::number(nonUsed));

    ui->marshrutiANDtrams->setText(prognoz);
}

void Tramvai::renderRashodi() // вывод сводки за предыдущий день
{
    QString vivod = 0;

    // конструирование строки: расходы доходы аварии ремонты
    vivod.push_back("Трамваями заработано: " + QString::number(svodka.plusTram) + " ₽" + "\n");
    vivod.push_back("Расходы на электричество: " + QString::number(svodka.minusElectricity) + " ₽" + "\n");
    vivod.push_back("Расходы на ремонт трамваев: " + QString::number(svodka.minusRepair) + " ₽" + "\n");
    vivod.push_back("Трамваев отремонтировано: " + QString::number(svodka.repairs) + "\n");
    vivod.push_back("Расходы на аварии: " + QString::number(svodka.minusCrash) + " ₽" + "\n");
    vivod.push_back("Всего аварий: " + QString::number(svodka.crashes) + "\n");
    if (svodka.repairPath != 0) vivod.push_back("На ремонт путей потрачено: " + QString::number(svodka.repairPath) + " ₽" + "\n");

    // Считаем деньги
    uint64_t vsegoVMinus = svodka.minusElectricity + svodka.minusRepair + svodka.minusCrash + svodka.repairPath; // все расходы за день
    vivod.push_back("---------------------------------------------\nИТОГО расходов: " + QString::number(vsegoVMinus) + " ₽" + "\n");
    if (vsegoVMinus > svodka.plusTram) // ушли в минус
    {
        if (money < vsegoVMinus - svodka.plusTram) // не смогли покрыть расходы
        {
            vivod.push_back("\nВЫ БАНКРОТ!!!!!!!! НО вы можете начать заного.");
            money = 0;
            blockAllBTNs();
            ui->newGameBTN->setEnabled(true);
        }
        else
        {
            money -= (vsegoVMinus - svodka.plusTram); // смогли покрыть расходы
            vivod.push_back("\nВаше состояние изменилось на: -" + QString::number(vsegoVMinus - svodka.plusTram) + " .");
        }
    }
    else if (vsegoVMinus < svodka.plusTram) // получили прибыль
    {
        money += (svodka.plusTram - vsegoVMinus);
        vivod.push_back("\nВаше состояние изменилось на: +" + QString::number(svodka.plusTram - vsegoVMinus) + " ₽.");
    }
    else vivod.push_back("\nВаше состояние НЕ изменилось."); // расходы и доходы равны
    ui->rashodi->setText(vivod);
}

void Tramvai::updateDisplay() // обновление всех полей с текстом
{
    ui->biletUPcost->setText(QString::number(costOfbiletUpgrading)+" ₽");
    ui->money->setText(QString::number(money)+" ₽");
    ui->newMarshrutCost->setText(QString::number(costOfNewMarshrut)+" ₽");
    ui->tramCost->setText(QString::number(costOfNewTram)+" ₽");
    ui->upMarshrutCost->setText("Введите маршрут");
    ui->setTramKolvoInput->setText("");
    ui->marshrutInput->setText("");
    ui->upMarshrutInput->setText("");

    renderPrognoz();
}

void Tramvai::newGame() // начало игры
{
    // чистим векторы от прошлой игры
    tramsOnMarsruts.clear();
    maxTramsOnMarshruts.clear();
    minTramsOnMarshruts.clear();
    costOfMarsrutsUpgrading.clear();
    manyPeople.clear();

    // устанавливаем начальные значения
    tramsOnMarsruts.push_back(1);
    maxTramsOnMarshruts.push_back(3);
    minTramsOnMarshruts.push_back(1);
    costOfMarsrutsUpgrading.push_back(10000000);
    manyPeople.push_back(0);
    costOfNewMarshrut = 100000000;
    costOfbiletUpgrading = 100000000;
    costOfbilet = 35;
    costOfNewTram = 1000000;
    money = 100000000;
    vsegoTramvaev = 1;
    day = 1;

    // стираем остатки от предыдущей игры
    ui->setTramKolvoInput->setText("");
    ui->marshrutInput->setText("");
    ui->upMarshrutInput->setText("");
    ui->marshrutiANDtrams->setText("");
    ui->rashodi->setText("Проведите хоть один день, чтобы узнать сводку за прошлый день");

    unblockAllBTNs(); // разблокируем все кнопки
    updateDisplay(); // обновляем дисплей

    srand(time(NULL)); // меняем сид рандома

    randomEvent(); // начинаем игру

}

void Tramvai::randomEvent() // распределяет людей по трамваям
{
    for (uint64_t i = 0; i < manyPeople.size(); i++)
    {
        if (randomByPercents(20)) manyPeople[i] = 1; // много людей
        else if (randomByPercents(20)) manyPeople[i] = -1; // мало людей
        else manyPeople[i] = 0; // обычное кол-во людей
    }
    renderPrognoz();
}

void Tramvai::nextDay() // переход к следующему дню
{
    for (uint64_t i = 0; i < tramsOnMarsruts.size(); i++) // проверка на выполненность условий
    {
        if (tramsOnMarsruts[i] < minTramsOnMarshruts[i] || tramsOnMarsruts[i] > maxTramsOnMarshruts[i])
        {
            updateDisplay();
            ui->marshrutiANDtrams->setText(prognoz+"\nНе все условия выполнены!!!\nЕсли вы не можете выполнить условия, нажмите НАЧАТЬ ЗАНОГО.");
            return;
        }
    }

    // подсчет трамваев на маршрутах (они приносят деньги, тратят электричество и могут попадать в аварии)
    uint64_t vsegoTramOnMarsh = 0;
    for (uint64_t i = 0; i < tramsOnMarsruts.size(); i++)
    {
        vsegoTramOnMarsh += tramsOnMarsruts[i];
    }

    svodka.clear(); // удаляем старый отчет

    // подсчитываем выручку
    for(uint64_t i = 0; i < tramsOnMarsruts.size(); i++)
    {
        if (manyPeople[i] == 0) svodka.plusTram += tramsOnMarsruts[i] * costOfbilet * randomBetween(1000, 1500); // зароботок трамваев там где средее кол-во людей
        else if (manyPeople[i] == 1) svodka.plusTram += tramsOnMarsruts[i] * costOfbilet * randomBetween(1500, 3000); // зароботок трамваев там где большое кол-во людей
        else if (manyPeople[i] == -1) svodka.plusTram += tramsOnMarsruts[i] * costOfbilet * randomBetween(500, 1000); // зароботок трамваев там где малое кол-во людей
    }

    svodka.minusElectricity = vsegoTramOnMarsh * randomBetween(1000, 2000); // подсчет потраченного электричества

    // подсчет денег на ремонт и лечение сбитых людей и моральный ущерб
    for (uint64_t i = 0; i < vsegoTramOnMarsh; i++)
    {
        if (randomByPercents(4))
        {
            svodka.repairs++;
            svodka.minusRepair += randomBetween(1000, 1000000); // трамвай могли просто поцарапать, а могли и сломать почти полностью
        }
        if(randomByPercents(1)&&randomByPercents(1))
        {
            svodka.crashes++;
            svodka.minusCrash += randomBetween(100, 5000000); // человека могло сбить, а могло и просто зажать дверью его сумку, оттуда и разные суммы
        }
    }

    if (day % 100 == 0) // каждый 100 - й день ремонтируем трамвайные пути
    {
        for(uint64_t i = 0; i < tramsOnMarsruts.size(); i++)
        {
            svodka.repairPath += 1000000 * maxTramsOnMarshruts[i]; // чем выше уровень маршрута, тем дороже его ремонтировать
        }
    }
    renderRashodi(); // выводим сводку
    day++; // наступает новый день
    randomEvent();
    updateDisplay();
}

void Tramvai::buyTram() // купить трамвай
{
    if (costOfNewTram <= money) // должно хватать денег
    {
        vsegoTramvaev++;
        money -= costOfNewTram;
        costOfNewTram += costOfNewTram / 10; // типа инфляция
    }
    updateDisplay();
}

void Tramvai::buyMarshrut() // покупка маршрута
{
    if (costOfNewMarshrut <= money) // должно хватать денег
    {
        tramsOnMarsruts.push_back(0);
        minTramsOnMarshruts.push_back(1);
        maxTramsOnMarshruts.push_back(3);
        costOfMarsrutsUpgrading.push_back(10000000);
        manyPeople.push_back(rand() % (1 + 1 + 1) -1);
        money -= costOfNewMarshrut;
        costOfNewMarshrut += costOfNewMarshrut / 10; // типа инфляция
        updateDisplay();
    }
}

void Tramvai::setTrams() // устанавить трамваи на маршрут
{
    uint64_t freeTrams = vsegoTramvaev;
    for(uint64_t i = 0; i < tramsOnMarsruts.size(); i++)
    {
        freeTrams -= tramsOnMarsruts[i];
    }
    if ((ui->setTramKolvoInput->text().toULongLong() <= freeTrams) && (ui->marshrutInput->text().toULongLong() < tramsOnMarsruts.size()))
    {  // нельзя установить больше трамваев, чем свободно
        tramsOnMarsruts[ui->marshrutInput->text().toULongLong()] = ui->setTramKolvoInput->text().toULongLong();
        updateDisplay();
    }
}

void Tramvai::upgradeBilet() // повысить цену на билет
{
    if (costOfbiletUpgrading <= money) // на процедуру должно хватать денег
    {
        costOfbilet += 5;
        money -= costOfbiletUpgrading;
        costOfbiletUpgrading += costOfbiletUpgrading / 10 * 3; // чтобы часто не повышали цены
        updateDisplay();
    }
}

void Tramvai::selectUpM() // выводит информацию о стоимости улучшения выбранного маршрута
{
    if (ui->upMarshrutInput->text() == "")
    {
        ui->upMarshrutCost->setText("Введите маршрут");
        return;
    }
    uint64_t selectedMar = ui->upMarshrutInput->text().toULongLong();
    if (selectedMar < tramsOnMarsruts.size()) ui->upMarshrutCost->setText(QString::number(costOfMarsrutsUpgrading[selectedMar]) + " ₽");
    else
    {
        ui->upMarshrutCost->setText("Введите маршрут");
        return;
    }
}

void Tramvai::upMarshrut() // Увеличивает уровень (макс и мин колво трамваев на маршруте) маршрута
{
    if (ui->upMarshrutInput->text() == "") // только если ввели корректны маршрут
    {
        ui->upMarshrutCost->setText("Введите маршрут");
        return;
    }
    uint64_t selectedMar = ui->upMarshrutInput->text().toULongLong();
    if (selectedMar < tramsOnMarsruts.size())
    {
        if (costOfMarsrutsUpgrading[selectedMar] <= money) // только если хватает денег
        {
            money -= costOfMarsrutsUpgrading[selectedMar];
            costOfMarsrutsUpgrading[selectedMar] += costOfMarsrutsUpgrading[selectedMar] / 10; // типо инфляция
            maxTramsOnMarshruts[selectedMar]++; // повышаем макс число трамваев на маршруте
            minTramsOnMarshruts[selectedMar] = maxTramsOnMarshruts[selectedMar] -3; // повышаем мин колво трамваев на маршруте
            if (minTramsOnMarshruts[selectedMar] == 0) minTramsOnMarshruts[selectedMar] = 1; // если трамваев мало то 1 это минимум
            updateDisplay();
        }
    }
    else
    {
        ui->upMarshrutCost->setText("Введите маршрут");
        return;
    }
}

Tramvai::~Tramvai()
{
    delete ui;
}

