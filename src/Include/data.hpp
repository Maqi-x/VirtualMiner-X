// --------------------------------------------------- //
//                    VirtualMiner-X                   //
//                       data.hpp                      //
// (c) 2025 Maqi-x                                     //
// --------------------------------------------------- //

#pragma once

#include <QSettings>

extern QSettings settings;
extern long long totalOresMined;
extern long long totalMoneyCollected;
extern long pickaxePower;
// TODO add more --^

struct Upgrade {
    QString name;
    QString description;
    long price;
    std::function<void()> action;
};

typedef long long bigInt;
typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;