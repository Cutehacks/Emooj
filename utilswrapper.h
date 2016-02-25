// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
#ifndef UTILSWRAPPER_H
#define UTILSWRAPPER_H

#include <QObject>
#include <QtQml/QJSValue>

class QQmlEngine;

namespace com { namespace cutehacks { namespace emooj {

class UtilsWrapper : public QObject
{
    Q_OBJECT

public:
    explicit UtilsWrapper(QQmlEngine *engine = 0);

    Q_INVOKABLE int length(const QString&) const;
    Q_INVOKABLE QString replaceEmojis(const QString&, QJSValue);

private:
    QQmlEngine *m_engine;
};

} } }

#endif // UTILSWRAPPER_H
