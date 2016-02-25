// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
#ifndef EMOJIIMAGEPROVIDER_H
#define EMOJIIMAGEPROVIDER_H

#include <QtQuick/QQuickImageProvider>

namespace com { namespace cutehacks { namespace emooj {

class EmojiImageProvider : public QQuickImageProvider
{
public:
    EmojiImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    QPixmap m_src;
};

} } }

#endif // EMOJIIMAGEPROVIDER_H
