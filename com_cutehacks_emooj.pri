
RESOURCES += \
    $$PWD/com_cutehacks_emooj.qrc

isEmpty(EMOOJ_SHEETS) {
    EMOOJ_SHEETS = twitter
    ios|macx: EMOOJ_SHEETS += apple
    android: EMOOJ_SHEETS += google
}

contains(EMOOJ_SHEETS, apple) {
    RESOURCES += $$PWD/com_cutehacks_emooj_apple.qrc
    DEFINES += EMOOJ_APPLE
}
contains(EMOOJ_SHEETS, google) {
    RESOURCES += $$PWD/com_cutehacks_emooj_google.qrc
    DEFINES += EMOOJ_GOOGLE
}
contains(EMOOJ_SHEETS, emojione) {
    RESOURCES += $$PWD/com_cutehacks_emooj_emojione.qrc
    DEFINES += EMOOJ_EMOJIONE
}
contains(EMOOJ_SHEETS, twitter) {
    RESOURCES += $$PWD/com_cutehacks_emooj_twitter.qrc
    DEFINES += EMOOJ_TWITTER
}

HEADERS += \
    $$PWD/unicodeutils.h \
    $$PWD/emooj.h \
    $$PWD/emojidatamodel.h \
    $$PWD/utilswrapper.h \
    $$PWD/emoji-data.h \
    $$PWD/emojiimageprovider.h

SOURCES += \
    $$PWD/unicodeutils.cpp \
    $$PWD/emojidatamodel.cpp \
    $$PWD/utilswrapper.cpp \
    $$PWD/emoji-data.cpp \
    $$PWD/emojiimageprovider.cpp

INCLUDEPATH += $$PWD
