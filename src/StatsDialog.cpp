// --------------------------------------------------- //
//                    VirtualMiner-X                   //
//                    StatsDialog.cpp                  //
// (c) 2025 Maqi-x                                     //
// --------------------------------------------------- //

#include <QPixmap>
#include <statsDialog.hpp>

StatsDialog::StatsDialog(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::Tool);
    setWindowTitle("Stats");
    setObjectName("statsDialogPanel");
    setFixedSize(650, 270);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QFrame *oreFrame = new QFrame(this);
    oreFrame->setObjectName("oreFrame");
    oreFrame->setFixedHeight(100);

    QHBoxLayout *oreLayout = new QHBoxLayout(oreFrame);
    oreIconLabel = new QLabel(oreFrame);
    oreIconLabel->setPixmap(
        QPixmap(":/images/ore.png").scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    oreIconLabel->setObjectName("oreIconLabel");

    oreTextLabel = new QLabel(QString("Total Ores Mined: %1").arg(totalOresMined), oreFrame);
    oreTextLabel->setObjectName("oreTextLabel");

    oreLayout->addWidget(oreIconLabel);
    oreLayout->addWidget(oreTextLabel);
    oreLayout->setSpacing(5);

    QFrame *moneyFrame = new QFrame(this);
    moneyFrame->setObjectName("moneyFrame");
    moneyFrame->setFixedHeight(100);

    QHBoxLayout *moneyLayout = new QHBoxLayout(moneyFrame);
    moneyIconLabel = new QLabel(moneyFrame);
    moneyIconLabel->setPixmap(
        QPixmap(":/images/coin.jpeg").scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    moneyIconLabel->setObjectName("moneyIconLabel");

    moneyTextLabel = new QLabel(QString("Total Money Collected: %1").arg(totalMoneyCollected), moneyFrame);
    moneyTextLabel->setObjectName("moneyTextLabel");

    moneyLayout->addWidget(moneyIconLabel);
    moneyLayout->addWidget(moneyTextLabel);
    moneyLayout->setSpacing(5);

    // ----------------- //

    mainLayout->addWidget(oreFrame);
    mainLayout->addWidget(moneyFrame);
    mainLayout->setSpacing(20);

    setLayout(mainLayout);
}