//#
//# Copyright (C) 2018-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef qTbot_GLOBAL_H
#define qTbot_GLOBAL_H

#include <QtCore/qglobal.h>

#define QTBOT_VERSION "0.87.648a8dc"

#if defined(QTBOT_LIBRARY)
#  define QTBOT_EXPORT Q_DECL_EXPORT
#else
#  define QTBOT_EXPORT Q_DECL_IMPORT
#endif

#endif //qTbot_GLOBAL_H

