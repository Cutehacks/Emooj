// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
#include <QtCore/QStringBuilder>

#include "emojiimageprovider.h"

namespace com { namespace cutehacks { namespace emooj {

static const QString SHEET_BASE(QStringLiteral(":/com/cutehacks/emooj/assets/"));
static const QString SHEET_APPLE(SHEET_BASE % QStringLiteral("sheet_apple_32.png"));
static const QString SHEET_GOOGLE(SHEET_BASE % QStringLiteral("sheet_google_32.png"));
static const QString SHEET_EMOJIONE(SHEET_BASE % QStringLiteral("sheet_emojione_32.png"));
static const QString SHEET_TWITTER(SHEET_BASE % QStringLiteral("sheet_twitter_32.png"));

EmojiImageProvider::EmojiImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    QString sheet;
#ifdef EMOOJ_APPLE
    sheet = SHEET_APPLE;
#elif defined(EMOOJ_GOOGLE)
    sheet = SHEET_GOOGLE;
#elif defined(EMOOJ_EMOJIONE)
    sheet = SHEET_EMOJIONE;
#elif defined(EMOOJ_TWITTER)
    sheet = SHEET_TWITTER;
#endif
    if (!m_src.load(sheet))
        qWarning("Could not load emooj sheet.");
}

QPixmap EmojiImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &)
{
    static const int SIZE = 32;
    QStringList parts = id.split("/");
    int coords[2];
    for (int i = 0; i < 2; i++)
        coords[i] = parts[i].toInt();
    int x = coords[0] * SIZE;
    int y = coords[1] * SIZE;
    if (size)
        *size = QSize(SIZE, SIZE);
    return m_src.copy(x, y, SIZE, SIZE);
}

} } }
