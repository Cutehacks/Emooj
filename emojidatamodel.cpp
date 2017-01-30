// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
#include <QtGui/QGuiApplication>
#include <QtGui/QInputMethodEvent>

#include "emojidatamodel.h"
#include "emoji-data.h"
#include "emojiimageprovider.h"

namespace com { namespace cutehacks { namespace emooj {

static QHash<int, QByteArray> roles {
    {Qt::DisplayRole,               "display"},
    {Qt::DecorationRole,            "decoration"},
    {EmojiDataModel::UnicodeRole,   "unicode"},
    {EmojiDataModel::NameRole,      "name"},
    {EmojiDataModel::ShortNameRole, "shortName"},
    {EmojiDataModel::CategoryRole,  "category"},
    {EmojiDataModel::SheetXRole,    "sheetX"},
    {EmojiDataModel::SheetYRole,    "sheetY"}
};

EmojiDataModel::EmojiDataModel(QObject *parent) : QAbstractItemModel(parent)
{

}

QModelIndex EmojiDataModel::index(int row, int, const QModelIndex &) const
{
    return createIndex(row, 0);
}

QModelIndex EmojiDataModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int EmojiDataModel::rowCount(const QModelIndex &) const
{
    return emojis.length();
}

int EmojiDataModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant EmojiDataModel::data(const QModelIndex &index, int role) const
{
    QString key = emojis[index.row()];
    if (role == UnicodeRole || role == Qt::DisplayRole)
        return key;

    Emoji data = emojiData[key];
    switch (role) {
    case Qt::ToolTipRole:
    case NameRole:
        return data.name;
    case Qt::EditRole: // Used for completion for QCompleter
    case ShortNameRole:
        return data.shortName;
    case CategoryRole:
        return data.category;
    case SheetXRole:
        return data.sheetX;
    case SheetYRole:
        return data.sheetY;
    case Qt::DecorationRole:
        return EmojiImageProvider::urlForCoords(data.sheetX, data.sheetY);
        break;
    }
    return key;
}


QHash<int, QByteArray> EmojiDataModel::roleNames() const
{
    return roles;
}

void EmojiDataModel::emitIMEvent(int i)
{
    if (i >= 0 && i < emojis.length()) {
        QString key = emojis[i];
        Emoji data = emojiData[key];
        QInputMethodEvent *e = new QInputMethodEvent(
                    QString(),
                    QList<QInputMethodEvent::Attribute>());
        e->setCommitString(data.unicode);
        qApp->sendEvent(qApp->focusObject(), e);
    }
}

} } }
