// --------------------------------------------------- //
//                    VirtualMiner-X                   //
//                   statsDialog.hpp                   //
// (c) 2025 Maqi-x                                     //
// --------------------------------------------------- //

#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <data.hpp>

class StatsDialog : public QDialog {
    Q_OBJECT

  public:
    explicit StatsDialog(QWidget *parent = nullptr);

  private:
    QLabel *oreIconLabel;
    QLabel *oreTextLabel;
    QLabel *moneyIconLabel;
    QLabel *moneyTextLabel;
};