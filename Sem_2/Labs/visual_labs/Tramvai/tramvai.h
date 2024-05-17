#ifndef TRAMVAI_H
#define TRAMVAI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Tramvai; }
QT_END_NAMESPACE

class Tramvai : public QMainWindow
{
    Q_OBJECT

public:
    Tramvai(QWidget *parent = nullptr);
    ~Tramvai();

    std::vector<uint64_t> tramsOnMarsruts; // индексы - номера маршрутов
    std::vector<uint64_t> maxTramsOnMarshruts; // по индексу мршрута - максимальное кол-во трамваев
    std::vector<uint64_t> minTramsOnMarshruts; // по индексу маршрута - минимально кол-во трамваев
    std::vector<short int> manyPeople; // по индексам - сколько людей -1 мало 0 средне 1 много
    std::vector<uint64_t> costOfMarsrutsUpgrading; // цена улучшения маршрута
    uint64_t costOfNewMarshrut; // цена нового маршрута
    uint64_t costOfbiletUpgrading; // стоимость повышения цены билета
    uint64_t costOfbilet; // цена одного билета
    uint64_t costOfNewTram; // цена нового трамвая
    uint64_t money; // ваше состояние
    uint64_t vsegoTramvaev; // всего трамваев
    uint64_t day; // текущий день
    void randomEvent(); // рандомное распределение людей
    void blockAllBTNs(); // блокировка всех кнопок
    void unblockAllBTNs(); // разблокировка всех кнопок
    void renderPrognoz(); // вывод распределения трамваев и прогнозов на экран
    void renderRashodi(); // вывод сводки расходы/доходы
    void updateDisplay(); // обновление всех ценников и прочих полей с текстом
public slots:
    void newGame(); // начало игры
    void nextDay(); // переход к следующему дню
    void buyTram(); // купить трамвай
    void buyMarshrut(); // купить маршрут
    void setTrams(); // установить количество трамваев на маршрут
    void upgradeBilet(); // Увеличить стоимость билета
    void selectUpM(); // автомотически показывает цену улучшения выбранного маршрута
    void upMarshrut(); // улучшает маршрут
private:
    Ui::Tramvai *ui;
};
#endif // TRAMVAI_H
