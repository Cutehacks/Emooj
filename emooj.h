#ifndef EMOOJ_H
#define EMOOJ_H

#include <QtQml/QQmlEngine>
// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
#include <QtQml/qqml.h>

#include "utilswrapper.h"
#include "emojidatamodel.h"
#include "emojiimageprovider.h"

namespace com { namespace cutehacks { namespace emooj {

static const char* EMOOJ_NS = "com.cutehacks.emooj";

static QObject *utilsWrapperFactory(QQmlEngine *engine, QJSEngine *)
{
    return new UtilsWrapper(engine);
}

static void registerEngine(QQmlEngine *engine)
{
    qmlRegisterSingletonType<UtilsWrapper>(EMOOJ_NS,
        1, 0, "UnicodeUtils", com::cutehacks::emooj::utilsWrapperFactory);
    qmlRegisterType<EmojiDataModel>(EMOOJ_NS, 1, 0, "EmojiDataModel");
    engine->addImageProvider(EMOOJ_NS, new EmojiImageProvider);
}


} } }

#endif // EMOOJ_H

