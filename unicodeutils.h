// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
#ifndef UNICODEUTILS_H
#define UNICODEUTILS_H

#include <QtCore/QObject>
#include <QtCore/QRegularExpression>

#include "emoji-data.h"

namespace com { namespace cutehacks { namespace emooj {

class AbstractEmojiReplacer
{
public:
    virtual ~AbstractEmojiReplacer() {}
    virtual QString replace(const Emoji&) const = 0;
};

class UnicodeUtils
{
public:
    static QString replaceEmojis(const QString&, AbstractEmojiReplacer*);

private:
    static QRegularExpression emojiRe;
};

} } }

#endif // UNICODEUTILS_H
