//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMDOCUMENT_H
#define TELEGRAMDOCUMENT_H

#include <qTbot/ijsonbasedobject.h>

namespace qTbot {

/**
 * @brief The TelegramDocument class This is implementation of the documents objects of telegram
 */
class TelegramDocument: public IJsonBasedObject
{
public:
    TelegramDocument();

    /**
     * @brief Constructs a Document object from a JSON object.
     * @param jsonObject The JSON object containing document data.
     */
    TelegramDocument(const QJsonObject &jsonObject);

    /**
     * @brief Returns the file name of the document.
     * @return The file name of the document.
     */
    QString fileName() const;

    /**
     * @brief Returns the MIME type of the document.
     * @return The MIME type of the document.
     */
    QString mimeType() const;

    /**
     * @brief Returns the file ID of the document.
     * @return The file ID of the document.
     */
    QString fileId() const;

    /**
     * @brief Returns the unique ID of the document.
     * @return The unique ID of the document.
     */
    QString fileUniqueId() const;

    /**
     * @brief Returns the file size of the document in bytes.
     * @return The file size of the document.
     */
    int fileSize() const;
};
}
#endif // TELEGRAMDOCUMENT_H
