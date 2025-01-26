// --------------------------------------------------- //
//                    VirtualMiner-X                   //
//                       data.cpp                      //
// (c) 2025 Maqi-x                                     //
// --------------------------------------------------- //

#include <data.hpp>
#include <stdint.h>

QSettings settings(QSettings::UserScope, "MqApps", "VirtualMiner-X");
long long totalOresMined = settings.value("Stats/totalOresMined", 0).toLongLong();
long long totalMoneyCollected = settings.value("Stats/totalMoneyCollected", 0).toLongLong();
long pickaxePower = 1;