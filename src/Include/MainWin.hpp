// --------------------------------------------------- //
//                    VirtualMiner-X                   //
//                      MainWin.hpp                    //
// (c) 2025 Maqi-x                                     //
// --------------------------------------------------- //

#pragma once

//-------------- Qt------------- //
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
// ----------------------------- //

#include <data.hpp>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  protected:
    void mousePressEvent(QMouseEvent *event) override;

  private:
    QLabel *stone;
    QWidget *oreWidget;
    QLabel *oreLabel;
    QLabel *oreIcon;
    QWidget *moneyWidget;
    QLabel *moneyLabel;
    QLabel *moneyIcon;
    QWidget *statsPanel;
    QPushButton *sellButton;
    QWidget *upgradeShopPanel;
    QPropertyAnimation *shakeAnm;
    QList<QPair<QString, Upgrade>> upgrades;
    QTimer *exchangeTimer;
    int64 toWithdraw;
    int64 ore;
    int64 money;
    int64 oresPerTick;
    int64 exchangeRate;
    int32 autoCollect;
    int32 autoMine;

    void setupUI();
    void updateStats();
    void sellOres();
    void openStatsPanel();
    void processExchangeStep();
    QPoint getStoneCenter();

  signals:
    void moneyChanged(qint64 money);
};