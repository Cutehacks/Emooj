// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
#include <QtCore/QVector>
#include <QtQml/QQmlEngine>

#include "utilswrapper.h"
#include "unicodeutils.h"

namespace com { namespace cutehacks { namespace emooj {

class JSEmojiReplacer : public AbstractEmojiReplacer
{

public:
    JSEmojiReplacer(QQmlEngine * engine, const QJSValue& callback) :
        m_engine(engine),
        m_callback(callback)
    { }

    QString replace(const Emoji &emoji) const
    {
        if (m_callback.isCallable()) {
            QJSValue args = m_engine->newObject();
            args.setProperty("unicode", emoji.unicode);
            args.setProperty("name", emoji.name);
            args.setProperty("shortName", emoji.shortName);
            args.setProperty("sheetX", emoji.sheetX);
            args.setProperty("sheetY", emoji.sheetY);
            return m_callback.call(
                QJSValueList() << args
            ).toString();
        }
        qWarning("Second argument to UnicodeUtils.replaceEmojis should be a function");
        return m_callback.toString();
    }

private:
    QQmlEngine *m_engine;
    mutable QJSValue m_callback;
};

UtilsWrapper::UtilsWrapper(QQmlEngine *engine) :
    QObject(engine),
    m_engine(engine)
{ }

/*!
    Calculate the number of actual symbols in the QString and not
    just the length of the string.
 */
int UtilsWrapper::length(const QString &str) const
{
    return str.toUcs4().length();
}

/*!
    Find all emoijs in 'src' and replace them with the result returned by
    callback.
 */
QString UtilsWrapper::replaceEmojis(const QString &src, QJSValue callback)
{
    JSEmojiReplacer replacer(m_engine, callback);
    return UnicodeUtils::replaceEmojis(src, &replacer);
}

} } }

