#include "mmaster.h"
#include "ui_mmaster.h"

#include <QFileDialog>
#include <fstream>
#include <sstream>

uint64_t firInd = UINT64_MAX, secInd = UINT64_MAX;
QGraphicsTextItem * testoo;

MMaster::MMaster(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MMaster)
{
    ui->setupUi(this);

    connect(ui->scale, &QSlider::valueChanged, this, &MMaster::scaleChanged);
    connect(ui->fileBTN, &QPushButton::clicked, this, &MMaster::getMatrixFromFile);
    connect(ui->pushButton, &QPushButton::clicked, this, &MMaster::createMatrix);
    connect(ui->zeroBTN, &QPushButton::clicked, this, &MMaster::nullBTN);
    connect(ui->oneBTN, &QPushButton::clicked, this, &MMaster::oneBTN);
    connect(ui->randBTN, &QPushButton::clicked, this, &MMaster::randBTN);
    connect(ui->saveBTN, &QPushButton::clicked, this, &MMaster::toFile);
    connect(ui->plus, &QPushButton::clicked, this, &MMaster::appendMatr);
    connect(ui->minus, &QPushButton::clicked, this, &MMaster::disappendMatr);
    connect(ui->delBTN, &QPushButton::clicked, this, &MMaster::delMatr);
    connect(ui->go, &QPushButton::clicked, this, &MMaster::analyzeMatr);
    connect(ui->printerBTN, &QPushButton::clicked, this, &MMaster::scaleChanged);

    graphicsView = ui->telek; //коннекты телевизора и сцены
    scene = new QGraphicsScene;
    sceneForText = new QGraphicsScene;
    testoo = sceneForText->addText("       Здесь пусто (\nСоздайте матрицу!", QFont("Montserrat Alternates", ui->scale->value()/1.3));
    graphicsView -> setScene(scene);
    ui->telek->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->telek->setCacheMode(QGraphicsView::CacheNone); // Кэш
    ui->telek->setViewportUpdateMode(QGraphicsView::FullViewportUpdate); // режим обнавления телека - полный
    printMatrix();
    srand(time(NULL));
}

void MMaster::text(QString text, QFont font)
{
    graphicsView->setScene(sceneForText);
    testoo->setPlainText(text);
    testoo->setFont(font);
    QRectF rect = sceneForText->itemsBoundingRect();
    sceneForText->setSceneRect(rect);
    ui->telek->update();
}

void MMaster::printMatrix()
{
    graphicsView->setScene(scene);
    scene->clear();
    indexation.clear();
    if (matr.size() == 0)
    {
        text("       Здесь пусто (\nСоздайте матрицу!", QFont("Montserrat Alternates", ui->scale->value()/1.3));
    }
    uint64_t posx = 0, posy = 0;
    for (uint64_t i = 0; i < matr.size(); i++)
    {
        std::vector<CellItem*> stroka(matr.size(), nullptr);
        for (uint64_t j = 0; j < matr.size(); j++)
        {
            CellItem * item = new CellItem;
            item->number = matr[i][j];
            item->isSelected = false;
            item->scale = ui->scale->value();
            item->setPos(posx, posy);
            scene->addItem(item);
            connect(item, &CellItem::activeChanged, this, &MMaster::selectedCell);
            stroka[j] = item;
            posx += ui->scale->value();
        }
        posy += ui->scale->value();
        posx = 0;
        indexation.push_back(stroka);
    }
    QRectF rect = scene->itemsBoundingRect();
    scene->setSceneRect(rect);
    ui->telek->update();
}

void MMaster::selectedCell()
{
    QGraphicsScene * tmp = new QGraphicsScene;
    QPolygonF viewportF = ui->telek->mapToScene(ui->telek->viewport()->geometry());
    ui->telek->setScene(tmp);
    ui->telek->setScene(scene);
    ui->telek->ensureVisible(viewportF.boundingRect());
    ui->telek->update();
    delete tmp;

    if (firInd != UINT64_MAX && secInd != UINT64_MAX)
    {
        if (indexation[firInd][secInd]->isSelected == false) firInd = secInd = UINT64_MAX;
        else
        {
            indexation[firInd][secInd]->isSelected = false;
            for (uint64_t i = 0; i < indexation.size(); i++)
            {
                for (uint64_t j = 0; j < indexation.size(); j++)
                {
                    if (indexation[i][j]->isSelected == true)
                    {
                        firInd = i;
                        secInd = j;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        for (uint64_t i = 0; i < indexation.size(); i++)
        {
            for (uint64_t j = 0; j < indexation.size(); j++)
            {
                if (indexation[i][j]->isSelected == true)
                {
                    firInd = i;
                    secInd = j;
                    break;
                }
            }
        }
    }
}

void MMaster::scaleChanged()
{
    firInd = secInd = UINT64_MAX;
    printMatrix();
}

bool checkString(const QString& input)
{
    QRegExp rx("^(0|1)( (0|1))*$");
    return rx.exactMatch(input);
}

void MMaster::getMatrixFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Текстовые файлы (*.txt);;Файлы бин. матриц (*.bmatr)");
    QFile file(fileName);
    std::vector<std::vector<bool>> matrix;
    if (fileName != "")
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            bool allOK = true;
            while (!in.atEnd())
            {
                QString line = in.readLine();
                if (!(checkString(line) && allOK)) allOK = false;
                std::vector<bool> row;
                for (const QChar& ch : line)
                {
                    if (ch == '0' || ch == '1')
                    {
                        row.push_back(ch == '1');
                    }
                }
                matrix.push_back(row);
            }
            file.close();
            if (allOK && matrix.size()>1)
            {
                matr.matrix = matrix;
                firInd = secInd = UINT64_MAX;
                printMatrix();
            }
            else
            {
                 scene->clear();
                 text("   ТОТАЛЬНАЯ ОШИБКА\nМАТРИЦА НЕКОРРЕКТНА", QFont("Montserrat Alternates", ui->scale->value()/1.1));
                 QRectF rect = scene->itemsBoundingRect();
                 scene->setSceneRect(rect);
                 ui->telek->update();
            }
        }
    }
    else
    {
         scene->clear();
         text(" ТОТАЛЬНАЯ ОШИБКА\nФАЙЛ НЕ ОТКРЫТ ИЛИ\n       НЕКОРРЕКТЕН!!!", QFont("Montserrat Alternates", ui->scale->value()/1.1));
         QRectF rect = scene->itemsBoundingRect();
         scene->setSceneRect(rect);
         ui->telek->update();
    }
}

void MMaster::createMatrix()
{
    Matrixxx m(ui->spinBox->value());
    matr = m;
    firInd = secInd = UINT64_MAX;
    printMatrix();
}

void MMaster::nullBTN()
{
    if (firInd == UINT64_MAX || secInd == UINT64_MAX) return;
    else
    {
        matr[firInd][secInd] = 0;
        indexation[firInd][secInd]->number = 0;
        if (secInd == (matr.size()-1))
        {
            if (firInd == (matr.size()-1)) indexation[0][0]->isSelected = true;
            else indexation[firInd+1][0]->isSelected = true;
        }
        else indexation[firInd][secInd+1]->isSelected = true;
        selectedCell();
    }
}
void MMaster::oneBTN()
{
    if (firInd == UINT64_MAX || secInd == UINT64_MAX) return;
    else
    {
        matr[firInd][secInd] = 1;
        indexation[firInd][secInd]->number = 1;
        if (secInd == (matr.size()-1))
        {
            if (firInd == (matr.size()-1)) indexation[0][0]->isSelected = true;
            else indexation[firInd+1][0]->isSelected = true;
        }
        else indexation[firInd][secInd+1]->isSelected = true;
        selectedCell();
    }
}
void MMaster::randBTN()
{
    for (uint64_t i = 0; i < matr.size(); i++)
    {
        for (uint64_t j = 0; j < matr.size(); j++)
        {
            matr[i][j] = (rand() % 2);
        }
    }
    firInd = secInd = UINT64_MAX;
    printMatrix();
}

void MMaster::toFile()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Сохранить файл", "", "Текстовые файлы (*.txt);;Файлы бин. матриц (*.bmatr)");
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (uint64_t i = 0; i < matr.size(); i++)
        {
            for (uint64_t j = 0; j < matr.size(); j++)
            {
                out << QString::number(static_cast<int>(matr[i][j]));
                (j == (matr.size()-1) ? out << "" : out << " ");
            }
            (i == (matr.size()-1) ? out << "" : out << "\n");
        }
        file.close();
    }
}

void MMaster::appendMatr()
{
    if(matr.size() < 2) return;
    std::vector<bool> newer(matr.size(), 0);
    matr.matrix.push_back(newer);
    for (uint64_t i = 0; i < matr.size(); i++) matr[i].push_back(0);
    firInd = secInd = UINT64_MAX;
    printMatrix();
}
void MMaster::disappendMatr()
{
    if(matr.size() < 3) return;
    uint64_t siz = matr.size();
    for (uint64_t i = 0; i < siz; i++) matr[i].pop_back();
    matr.matrix.pop_back();
    firInd = secInd = UINT64_MAX;
    printMatrix();
}

void MMaster::delMatr()
{
    matr.matrix.clear();
    firInd = secInd = UINT64_MAX;
    printMatrix();
}

void MMaster::analyzeMatr()
{
    if (matr.size() < 2) return;
    bool ref = true, antiref = true, symm = true, antisymm = true, assym = true, tranz = true, svyaz = true;

    for (uint64_t i = 0; i < matr.size(); i++)
    {
        if (matr[i][i] != true)
        {
            ref = false;
            break;
        }
    }
    for (uint64_t i = 0; i < matr.size(); i++)
    {
        if (matr[i][i] != false)
        {
            antiref = false;
            break;
        }
    }
    for (uint64_t i = 0; i < matr.size(); i++)
    {
        for (uint64_t j = 0; j < matr.size(); j++)
        {
            if (matr[i][j] != matr[j][i])
            {
                symm = false;
                break;
            }
        }
    }
    bool oneYes = false;
    for (uint64_t i = 0; i < matr.size(); i++)
    {
        for (uint64_t j = 0; j < matr.size(); j++)
        {
            if (i != j && matr[i][j] && matr[j][i])
            {
                antisymm = false;
                break;
            }
            if (i == j && matr[i][j] == 1 && oneYes == false) oneYes = true;
        }
    }
    if (!oneYes) antisymm = false;
    for (uint64_t i = 0; i < matr.size(); i++)
    {
        for (uint64_t j = 0; j < matr.size(); j++)
        {
            if (matr[i][j] == matr[j][i] && matr[i][j] == true)
            {
                assym = false;
                break;
            }
        }
    }
    for (uint64_t i = 0; i < matr.size(); i++)
    {
        for (uint64_t j = 0; j < matr.size(); j++)
        {
            if (matr[i][j])
            {
                for (uint64_t k = 0; k < matr.size(); k++)
                {
                    if (matr[j][k] && !matr[i][k])
                    {
                        tranz = false;
                    }
                }
            }
        }
    }
    for (uint64_t i = 0; i < matr.size(); i++)
    {
        for (uint64_t j = 0; j < matr.size(); j++)
        {
            if (i != j && !matr[i][j] && !matr[j][i])
            {
                svyaz = false;
                break;
            }
        }
    }

    QString analyz = "Результат анализа матрицы:\n";
    for (uint64_t i = 0; i < matr.size(); ++i)
    {
        for (uint64_t j = 0; j < matr.size(); ++j)
        {
            analyz.push_back(QString::number(static_cast<int>(matr[i][j])) + "  ");
        }
        analyz.push_back("\n");
    }
    if (ref) analyz.push_back("\n1. Матрица рефлексивна\n"); else analyz.push_back("\n1. Матрица НЕ рефлексивна\n");
    if (antiref) analyz.push_back("2. Матрица антирефлексивна\n"); else analyz.push_back("2. Матрица НЕ антирефлексивна\n");
    if (symm) analyz.push_back("3. Матрица симметрична\n"); else analyz.push_back("3. Матрица НЕ является симметричной\n");
    if (antisymm) analyz.push_back("4. Матрица антисимметрична\n"); else analyz.push_back("4. Матрица НЕ является антисимметричной\n");
    if (assym) analyz.push_back("5. Матрица ассимметрична\n"); else analyz.push_back("5. Матрица НЕ является ассимметричной\n");
    if (tranz) analyz.push_back("6. Матрица транзитивна\n"); else analyz.push_back("6. Матрица НЕ транзитивна\n");
    if (svyaz) analyz.push_back("7. Матрица связная (полная)\n"); else analyz.push_back("7. Матрица НЕ связная (НЕ полная)");
    scene->clear();
    text(analyz, QFont("Cascadia Code", ui->scale->value()/4.2));
    QRectF rect = scene->itemsBoundingRect();
    scene->setSceneRect(rect);
    ui->telek->update();
}

MMaster::~MMaster()
{
    delete ui;
}

