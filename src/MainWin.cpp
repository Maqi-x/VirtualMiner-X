// --------------------------------------------------- //
//                    VirtualMiner-X                   //
//                      MainWin.cpp                    //
// (c) 2025 Maqi-x                                     //
// --------------------------------------------------- //

//-------------- Qt------------- //
#include <QDebug>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPixmap>
#include <QRandomGenerator>
#include <QScrollArea>
#include <QSizePolicy>
#include <QVBoxLayout>
// ----------------------------- //

#include <MainWin.hpp>
#include <bubble.hpp>
#include <data.hpp>
#include <statsDialog.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ore(0), money(0) {
    QTimer *AutoMine = new QTimer();
    AutoMine->start(1000);
    QObject::connect(AutoMine, &QTimer::timeout, [this]() {
        if (autoMine <= 0 || stone == nullptr) return;
        ore += autoMine;
        updateStats();
        auto bubble = new Bubble(QString::fromStdString("+%1").arg(autoMine),
                                 stone->mapToGlobal(QPoint(20, 20)), this, Qt::black);
        bubble->resize(50, 50);
        bubble->show();
    });
    QTimer *AutoCollect = new QTimer();
    AutoCollect->start(500);
    QObject::connect(AutoCollect, &QTimer::timeout, [this]() {
        if (autoCollect <= 0) return;
        money += autoCollect;
        updateStats();
    });

    exchangeTimer = new QTimer(this);
    connect(exchangeTimer, &QTimer::timeout, this, &MainWindow::processExchangeStep);
    exchangeRate = 2; //     1 ore -> {exchangeRate} money        //
    setupUI();
    shakeAnm = new QPropertyAnimation(stone, "pos");
    shakeAnm->setDuration(200);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    setFixedSize(1500, 800);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(30);

    // ------------------------ stats panel ---------------------- //
    statsPanel = new QWidget(this);
    statsPanel->setObjectName("statsPanel");
    statsPanel->setFixedWidth(500);
    QVBoxLayout *statsLayout = new QVBoxLayout(statsPanel);
    statsLayout->setContentsMargins(10, 10, 10, 10);

    //////// ores ////////
    oreWidget = new QWidget(this);
    QHBoxLayout *oreLayout = new QHBoxLayout(oreWidget);
    oreLayout->setContentsMargins(0, 0, 0, 0);
    oreLayout->setSpacing(5);

    oreIcon = new QLabel(this);
    oreIcon->setPixmap(QPixmap(":/images/ore.png"));
    oreIcon->setScaledContents(true);
    oreIcon->setFixedSize(50, 50);
    oreIcon->setObjectName("oreIcon");

    oreLabel = new QLabel("Ores: 0", this);
    oreLabel->setObjectName("oreLabel");

    oreLayout->addWidget(oreIcon);
    oreLayout->addWidget(oreLabel);
    oreWidget->setLayout(oreLayout);

    statsLayout->addWidget(oreWidget);

    //////// money ////////
    moneyWidget = new QWidget(this);
    QHBoxLayout *moneyLayout = new QHBoxLayout(moneyWidget);
    moneyLayout->setContentsMargins(0, 0, 0, 0);
    moneyLayout->setSpacing(5);

    moneyIcon = new QLabel(this);
    moneyIcon->setPixmap(QPixmap(":/images/coin.jpeg"));
    moneyIcon->setScaledContents(true);
    moneyIcon->setFixedSize(50, 50);
    moneyIcon->setObjectName("moneyIcon");

    moneyLabel = new QLabel("Money: 0", this);
    moneyLabel->setObjectName("moneyLabel");

    moneyLayout->addWidget(moneyIcon);
    moneyLayout->addWidget(moneyLabel);
    moneyWidget->setLayout(moneyLayout);

    statsLayout->addWidget(moneyWidget);

    ///////// sell button ////////
    statsLayout->addStretch();
    sellButton = new QPushButton("Sell ores", this);
    sellButton->setObjectName("sellButton");
    connect(sellButton, &QPushButton::clicked, this, &MainWindow::sellOres);

    statsLayout->addWidget(sellButton);

    // ----------------------- stone ------------------------- //

    stone = new QLabel(this);
    stone->setPixmap(QPixmap(":/images/stone.png"));
    stone->setScaledContents(true);
    stone->setFixedSize(200, 200);
    stone->setObjectName("stone");

    // -------------------------------------------------------- //

    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->addWidget(statsPanel);
    contentLayout->addWidget(stone, 0, Qt::AlignCenter);

    // --------------------- Upgrade shop --------------------- //
    upgradeShopPanel = new QWidget(this);
    upgradeShopPanel->setStyleSheet("background: transparent;");
    upgradeShopPanel->setObjectName("upgradeShopPanel");
    QFile style(":/upgradeStore.qss");
    if (style.open(QFile::ReadOnly)) {
        upgradeShopPanel->setStyleSheet(style.readAll());
    }

    QVBoxLayout *shopLayout = new QVBoxLayout(upgradeShopPanel);
    shopLayout->setContentsMargins(10, 10, 10, 10);
    shopLayout->setSpacing(15);

    upgradeShopPanel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    upgradeShopPanel->setMinimumHeight(0);

    QWidget *scrollContent = new QWidget();
    scrollContent->setStyleSheet("background: transparent;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scrollLayout->addWidget(upgradeShopPanel);
    scrollLayout->addStretch();

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background: transparent;");
    scrollArea->setObjectName("upgradeShopScrollArea");
    scrollArea->setFrameShape(QFrame::NoFrame);

    upgrades = {
        {"Auto Miner",
         {"Auto Miner", "Every second automatically earns you an additional 1 ore", 400,
          [this]() { autoMine++; }}},
        {"Basic Cursor",
         {"Basic Cursor", "Every 0.3 seconds automatically earns you an additional 1 coin", 600,
          [this]() { autoCollect++; }}},
        {"Pickaxe upgrade",
         {"Pickaxe upgrade", "Increases the power of your pick by 1 ore per hit", 800,
          [this]() { pickaxePower++; }}},
        {"Better rate",
         {"Better rate", "increases the amount of coins received per ore sold by 1", 1200,
          [this]() { exchangeRate++; }}},
        {"Repair Pickaxe",
         {"Repair Pickaxe", "Repairs your pickaxe, allowing you to keep digging TODO!", 1500,
          [this]() { qDebug("TODO"); }}},
        {"Auto Miner premium",
         {"Auto Miner premium", "Every second automatically earns you an additional 10 ores", 2000,
          [this]() { autoMine += 10; }}},
        {"Advanced cursor",
         {"Advanced cursor", "Every 0.5 seconds automatically earns you an additional 10 coin", 2500,
          [this]() { autoCollect += 10; }}},
        {"A real investment",
         {"A real investment", "Increases the amount of gold received for selling one stone by 5", 3000,
          [this]() { exchangeRate += 5; }}},
        {"New better pickaxe",
         {"New better pickaxe",
          "You buy a new better pick that mines 10 more ores every strike and has a higher maximum strength",
          4000, []() {
              pickaxePower += 10;
              qDebug() << "TODO";
          }}}};

    for (auto &pair : upgrades) {
        // const QString &key = pair.first;
        Upgrade &upgrade = pair.second;

        QWidget *widget = new QWidget(upgradeShopPanel);
        widget->setObjectName("upgradeWidget");

        QVBoxLayout *layout = new QVBoxLayout(widget);
        widget->setLayout(layout);
        layout->setContentsMargins(10, 10, 10, 10);
        layout->setSpacing(5);

        QLabel *nameLabel = new QLabel(upgrade.name, widget);
        nameLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
        QLabel *descriptionLabel = new QLabel(upgrade.description, widget);
        descriptionLabel->setStyleSheet("font-size: 14px; color:rgb(128, 127, 127);");
        QLabel *priceLabel = new QLabel(QString("Price: <b>%1</b>").arg(upgrade.price), widget);
        QPushButton *buyButton = new QPushButton("Buy", widget);
        buyButton->setObjectName("buyButton");

        QHBoxLayout *bottomLayout = new QHBoxLayout();
        bottomLayout->addWidget(priceLabel);
        bottomLayout->addStretch();
        bottomLayout->addWidget(buyButton);

        layout->addWidget(nameLabel);
        layout->addWidget(descriptionLabel);
        layout->addLayout(bottomLayout);

        shopLayout->addWidget(widget);

        connect(buyButton, &QPushButton::clicked, widget, [this, priceLabel, upgrade]() mutable {
            if (static_cast<qint64>(money) >= static_cast<qint64>(upgrade.price)) {
                money -= upgrade.price;
                upgrade.action();
                upgrade.price *= 2;
                priceLabel->setText(QString("Price: <b>%1</b>").arg(upgrade.price));
            } else {
                QMessageBox::warning(this, "Not enough money",
                                     "You don't have enough money to buy this upgrade!");
            }
            updateStats();
        });
        // connect(buyButton) // TODO
    }

    contentLayout->addWidget(scrollArea);

    // --------------------------------------------------------- //

    mainLayout->addLayout(contentLayout);
    QPushButton *statsButton = new QPushButton("Open Stats", this);
    statsButton->setObjectName("statsButton");
    connect(statsButton, &QPushButton::clicked, this, &MainWindow::openStatsPanel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(statsButton);

    mainLayout->addLayout(buttonLayout);

    updateStats();
}

void MainWindow::openStatsPanel() {
    StatsDialog dialog(this);
    dialog.setWindowModality(Qt::ApplicationModal);
    dialog.exec();
}

void MainWindow::sellOres() {
    if (ore > 0) {
        toWithdraw = ore;
        totalMoneyCollected += ore * exchangeRate;
        const int interval = 10;
        const int maxTime = 2500;
        const int ticks = maxTime / interval;

        oresPerTick = (ore + ticks - 1) / ticks;
        exchangeTimer->start(interval);
    }
}

void MainWindow::processExchangeStep() {
    if (toWithdraw > 0) {
        int processed = std::min(oresPerTick, ore);
        ore -= processed;
        toWithdraw -= processed;
        money += processed * exchangeRate;
        updateStats();
    } else {
        exchangeTimer->stop();
    }
}

void MainWindow::updateStats() {
    settings.setValue("Stats/totalOresMined", totalOresMined);
    settings.setValue("Stats/totalMoneyCollected", totalMoneyCollected);
    oreLabel->setText(QString("Ores: %1").arg(ore));
    moneyLabel->setText(QString("Money: %1").arg(money));
}

QPoint MainWindow::getStoneCenter() {
    int availableWidth = width() - statsPanel->width() - upgradeShopPanel->width();
    return QPoint(statsPanel->width() + (availableWidth - stone->width()) / 2,
                  (height() - stone->height()) / 2);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (stone->geometry().contains(event->pos())) {
        ore += pickaxePower;
        totalOresMined++;
        auto *bubble =
            new Bubble(QString::fromStdString("+%1").arg(pickaxePower), event->pos() - QPoint(20, 20), this);
        bubble->resize(50, 50);
        bubble->show();

        if (shakeAnm->state() == QAbstractAnimation::Running) {
            return;
        }

        QPoint centerPos = getStoneCenter();
        auto rand = QRandomGenerator::global;
        const int shakePw = 15;

        int dX1 = rand()->bounded(-shakePw, shakePw);
        int dY1 = rand()->bounded(-shakePw, shakePw);
        int dX2 = rand()->bounded(-shakePw, shakePw);
        int dY2 = rand()->bounded(-shakePw, shakePw);
        int dX3 = rand()->bounded(-shakePw, shakePw);
        int dY3 = rand()->bounded(-shakePw, shakePw);

        shakeAnm->stop();

        shakeAnm->setKeyValueAt(0, centerPos);
        shakeAnm->setKeyValueAt(0.2, QPoint(centerPos.x() + dX1, centerPos.y() + dY1));
        shakeAnm->setKeyValueAt(0.3, QPoint(centerPos.x() + dX2, centerPos.y() + dY2));
        shakeAnm->setKeyValueAt(0.8, QPoint(centerPos.x() + dX3, centerPos.y() + dY3));
        shakeAnm->setKeyValueAt(1, centerPos);

        shakeAnm->start();
        stone->move(centerPos);
        updateStats();
    }
}
