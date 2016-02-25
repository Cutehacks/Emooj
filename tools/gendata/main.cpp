#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QTextStream>
#include <QtCore/QStringBuilder>
#include <QtCore/QMap>
#include <QtCore/QLinkedList>

#include <QDebug>

#include "../../unicodeutils.h"
using namespace com::cutehacks::emooj;

#ifndef SRCDIR
#define SRCDIR "."
#endif

static const QString EMOJI_FILE(QStringLiteral(SRCDIR) % "/tools/gendata/emoji_pretty.json");
static const QString DEST_FILE(QStringLiteral(SRCDIR) % "/emoji-data.cpp");
static const QRegularExpression escapeRe("[ \\-]");

int main(int argc, char** argv)
{
    QMap<QString, QString> emoticons;
    QLinkedList<QPair<QString, QString> > variables;
    QMap<QString, Emoji> emojiData;

    QCoreApplication app(argc, argv);
    QFile src(EMOJI_FILE);
    if (!src.open(QIODevice::ReadOnly))
        qFatal(QString("Could not open file: %1").arg(src.fileName()).toLatin1());

    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(src.readAll(), &err);
    if (err.error != QJsonParseError::NoError)
        qFatal(QString("JSON Parse Error: %1").arg(err.errorString()).toLatin1());

    if (!json.isArray())
        qFatal("JSON was not an array");

    QFile dest(DEST_FILE);
    if (!dest.open(QIODevice::WriteOnly))
        qFatal(QString("Could not open file: %1").arg(dest.fileName()).toLatin1());

    QTextStream out(&dest);
    out << "// This file is generated. Don't bother editing it." << endl;
    out << endl;
    out << "#include \"emoji-data.h\"" << endl;
    out << endl;
    out << "namespace com { namespace cutehacks { namespace emooj {" << endl;

    QJsonArray jsa = json.array();
    for (QJsonArray::const_iterator ita = jsa.constBegin(); ita != jsa.constEnd(); ita++) {
        QJsonObject emoji = (*ita).toObject();

        QString unified = emoji["unified"].toString();
        QStringList codePoints = unified.split("-");
        QString encoded;
        QString unicode;
        foreach (QString cp, codePoints) {
            bool ok;
            uint ucs4 = cp.toUInt(&ok, 16);
            if (ok) {
                unicode = unicode % QString::fromUcs4(&ucs4, 1);
                encoded = encoded % QString("\\U%1").arg(ucs4, 8, 16, QLatin1Char('0'));
            }
        }

        QString variable = emoji["name"].toString().replace(escapeRe, "_");
        if (variable.isEmpty())
            variable = emoji["short_name"].toString().toUpper().replace(escapeRe, "_");
        variables.append(QPair<QString, QString>(variable, encoded));

        Emoji data = {
            variable,
            emoji["name"].toString(),
            emoji["short_name"].toString(),
            emoji["category"].toString(),
            emoji["sheet_x"].toInt(),
            emoji["sheet_y"].toInt()
        };

        emojiData.insert(variable, data);

        if (!emoji["skin-variations"].isUndefined()) {
            QJsonObject skinVariations = emoji["skin-variations"].toObject();
        }

        QJsonValue text = emoji["text"];
        if (!text.isUndefined() && !text.isNull()) {
            emoticons.insert(text.toString(), variable);
        }

        QJsonValue texts = emoji["texts"];
        if (texts.isArray()) {
            QJsonArray textsArray = texts.toArray();
            for (QJsonArray::const_iterator textsIt = textsArray.constBegin();
                 textsIt != textsArray.constEnd(); textsIt++) {

                QString ascii = (*textsIt).toString();
                ascii.replace("\\", "\\\\");

                emoticons.insert(ascii, variable);
            }
        }
    }

    // Generate output file

    // Declare static string variables to reduce duplication
    out << endl;
    for (QLinkedList<QPair<QString, QString> >::const_iterator vIt = variables.constBegin();
         vIt != variables.constEnd(); vIt++) {

        out << "static const QString " << (*vIt).first << "(QStringLiteral(\"" << (*vIt).second << "\"));" << endl;
    }

    // Declare a staticly initialized vector of all the strings
    out << endl << endl;
    out << "QVector<QString> emojis {" << endl;
    for (QLinkedList<QPair<QString, QString> >::const_iterator vIt = variables.constBegin();
         vIt != variables.constEnd(); ) {

        out << "    " << (*vIt).first;
        vIt++;
        if (vIt != variables.constEnd())
            out << ",";
        out << endl;
    }
    out << "};";

    // Declare a staticly initialized hashmap of the emoji data
    out << endl << endl;
    out << "QHash<QString, Emoji> emojiData {" << endl;
    for (QMap<QString, Emoji>::const_iterator eIt = emojiData.constBegin();
         eIt != emojiData.constEnd(); ) {

        Emoji data = eIt.value();
        out << "    " << "{" << eIt.key() << ", Emoji {" << endl;
        out << "        " << data.unicode << "," << endl;
        out << "        \"" << data.name << "\"," << endl;
        out << "        \"" << data.shortName << "\"," << endl;
        out << "        \"" << data.category << "\"," << endl;
        out << "        " << data.sheetX << "," << endl;
        out << "        " << data.sheetY << "}" << endl;
        out << "    }";

        eIt++;
        if (eIt != emojiData.constEnd())
            out << ",";
        out << endl;
    }
    out << "};";


    // Declare a static hash of ASCII emoticons to Unicode Emojis
    out << endl << endl;
    out << "QHash<QString, QString> emoticons {" << endl;
    for (QMap<QString, QString>::const_iterator eIt = emoticons.constBegin();
         eIt != emoticons.constEnd(); ) {

        out << "    " << "{\"" << eIt.key() << "\", " << eIt.value() << "}";
        eIt++;
        if (eIt != emoticons.constEnd())
            out << ",";
        out << endl;
    }
    out << "};";

    out << endl;
    out << endl;
    out << "} } }" << endl;

    dest.close();

    return 0;
}
