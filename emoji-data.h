#ifndef EMOJIDATA_H
// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
#define EMOJIDATA_H

#include <QtCore/QVector>
#include <QtCore/QHash>

namespace com { namespace cutehacks { namespace emooj {

struct Emoji {
    QString unicode;
    QString name;
    QString shortName;
    QString category;
    int sheetX;
    int sheetY;
};

extern QHash<QString, QString> emoticons;
extern QVector<QString> emojis;
extern QHash<QString, Emoji> emojiData;

} } }

#endif // EMOJIDATA_H

