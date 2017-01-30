// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
#ifndef EMOJIDATAMODEL_H
#define EMOJIDATAMODEL_H

#include <QtCore/QAbstractItemModel>

namespace com { namespace cutehacks { namespace emooj {

class EmojiDataModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum EmojiRoles {
        UnicodeRole = Qt::UserRole + 1000,
        NameRole,
        ShortNameRole,
        CategoryRole,
        SheetXRole,
        SheetYRole
    };

    EmojiDataModel(QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void emitIMEvent(int);
};

} } }

#endif // EMOJIDATAMODEL_H
