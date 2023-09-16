//#
//# Copyright (C) 2018-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "itelegrambot.h"
#include "qTbot/messages/telegramupdateansver.h"
#include <QNetworkAccessManager>

#include <qTbot/requests/telegramgetme.h>
#include <qTbot/requests/telegramsendmsg.h>

#include <QNetworkReply>
#include <QSharedPointer>
#include <QDebug>

namespace qTbot {

ITelegramBot::ITelegramBot() {
    _manager = new QNetworkAccessManager();
}

ITelegramBot::~ITelegramBot() {
    delete _manager;
}

bool ITelegramBot::login(const QByteArray &token) {
    if (token.isEmpty()) {
        return false;
    }

    setToken(token);

    ITelegramBot::Responce cb = [this]( const QSharedPointer<iRequest>& ,
                                       const QSharedPointer<iMessage>& responce,
                                       int err) {

        if (err) {
            qDebug() << "Network error occured. code: " << err;
        }

        if (auto message = responce.dynamicCast<ITelegramMessage>()) {
            setId(message->rawJson().value("id").toInt());
            setName(message->rawJson().value("first_name").toString());
            setUsername(message->rawJson().value("username").toString());
        }
    };
    
    return sendRequest(QSharedPointer<TelegramGetMe>::create(), cb);
}

bool ITelegramBot::sendMessage(const QVariant &chatId, const QString &text) {
    return sendSpecificMessage(chatId.toLongLong(), text);
}

bool ITelegramBot::sendSpecificMessage(const QVariant & chatId,
                                       const QString &text,
                                       unsigned long long replyToMessageId,
                                       bool markdown,
                                       bool disableWebPagePreview,
                                       const Responce &cb) {

    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (text.isEmpty()) {
        return false;
    }

    auto msg = QSharedPointer<TelegramSendMsg>::create(chatId,
                                                       text,
                                                       replyToMessageId,
                                                       markdown,
                                                       disableWebPagePreview);
    return sendRequest(msg, cb);
}

//Message::Id qTbot::ITelegramBot::Bot::sendMessage(const QVariant &chatId, const QString &text)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    return sendMessage({
//        { "chat_id",    HttpParameter(chatId) },
//        { "text",       HttpParameter(text)}
//    });
//}

//Message::Id qTbot::ITelegramBot::Bot::sendMessage(const QVariant &chatId, const QString &text, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    return sendMessage({
//        { "chat_id",              HttpParameter(chatId) },
//        { "text",                 HttpParameter(text) },
//        { "reply_to_message_id",  HttpParameter(replyToMessageId) }
//    });
//}

//Message::Id qTbot::ITelegramBot::Bot::sendMessage(const QVariant &chatId, const QString &text, const GenericReply &replyMarkup)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    return sendMessage({
//        { "chat_id",         HttpParameter(chatId) },
//        { "text",            HttpParameter(text)},
//        { "reply_markup",    HttpParameter(replyMarkup.serialize()) }
//    });
//}

//Message::Id qTbot::ITelegramBot::Bot::sendMessage(const QVariant &chatId, const QString &text, const GenericReply &replyMarkup, bool markdown, bool disableWebPagePreview)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",         HttpParameter(chatId) },
//        { "text",            HttpParameter(text)},
//        { "reply_markup",    HttpParameter(replyMarkup.serialize()) }
//    };

//    if (markdown)                 params.insert("parse_mode", HttpParameter(QString("Markdown")));
//    if (disableWebPagePreview)    params.insert("disable_web_page_preview", HttpParameter(disableWebPagePreview));

//    return sendMessage(params);
//}

//Message::Id qTbot::ITelegramBot::Bot::sendMessage(const QVariant &chatId, const QString &text, bool markdown, bool disableWebPagePreview, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "text",HttpParameter(text)}
//    };

//    if (replyToMessageId >= 0)    params.insert("reply_to_message_id",HttpParameter(replyToMessageId));
//    if (markdown)                 params.insert("parse_mode", HttpParameter(QString("Markdown")));
//    if (disableWebPagePreview)    params.insert("disable_web_page_preview", HttpParameter(disableWebPagePreview));

//    return sendMessage(params);
//}

//Message::Id qTbot::ITelegramBot::Bot::sendMessage(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_MESSAGE,params,Networking::POST));
//}

//Message::Id qTbot::ITelegramBot::Bot::forwardMessage(const QVariant &chatId, const QVariant &fromChatId, Message::Id messageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    if (fromChatId.type() != QVariant::String && fromChatId.type() != QVariant::Int && fromChatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    return forwardMessage({
//        { "chat_id",HttpParameter(chatId) },
//        { "from_chat_id",HttpParameter(fromChatId) },
//        { "message_id",HttpParameter(messageId) }
//    });
//}

//Message::Id qTbot::ITelegramBot::Bot::forwardMessage(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_FORWARD_MESSAGE, params, Networking::GET));
//}

//Message::Id qTbot::ITelegramBot::Bot::copyMessage(const QVariant &chatId, const QVariant &fromChatId, Message::Id messageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    if (fromChatId.type() != QVariant::String && fromChatId.type() != QVariant::Int && fromChatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    return copyMessage({
//        { "chat_id",      HttpParameter(chatId) },
//        { "from_chat_id", HttpParameter(fromChatId) },
//        { "message_id",   HttpParameter(messageId) }
//    });
//}

//Message::Id qTbot::ITelegramBot::Bot::copyMessage(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_COPY_MESSAGE, params, Networking::GET));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendPhoto(const QVariant &chatId, QFile *file, const QString &caption, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "caption",HttpParameter(caption)}
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(sendFilePayload(params,file,"photo",ENDPOINT_SEND_PHOTO));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendPhoto(const QVariant &chatId, const QString &fileId, const QString &caption, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "caption",HttpParameter(caption)},
//        { "photo",HttpParameter(fileId) }
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_PHOTO, params, Networking::GET));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendPhoto(const QVariant &chatId, const QByteArray &fileData, const QString &caption, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "caption",HttpParameter(caption)}
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(sendFilePayload(params,fileData,"photo",ENDPOINT_SEND_PHOTO));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendPhoto(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_PHOTO, params, Networking::UPLOAD));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendAudio(const QVariant &chatId, QFile *file, qint64 duration, const QString &performer, const QString &title, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "duration",HttpParameter(duration)},
//        { "performer",HttpParameter(performer)},
//        { "title",HttpParameter(title)}
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(sendFilePayload(params,file,"audio",ENDPOINT_SEND_AUDIO));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendAudio(const QVariant &chatId, const QString &fileId, qint64 duration, const QString &performer, const QString &title, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",    HttpParameter(chatId) },
//        { "duration",   HttpParameter(duration)},
//        { "performer",  HttpParameter(performer)},
//        { "title",      HttpParameter(title)},
//        { "audio",      HttpParameter(fileId) }
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(makeApiCall(ENDPOINT_SEND_AUDIO, params, Networking::GET));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendAudio(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_AUDIO, params, Networking::UPLOAD));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendDocument(const QVariant &chatId, QFile *file, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//                            { "chat_id",HttpParameter(chatId) },
//                            };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(sendFilePayload(params,file,"document",ENDPOINT_SEND_DOCUMENT));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendDocument(const QVariant &chatId, const QByteArray &fileData, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//                            { "chat_id",HttpParameter(chatId) },
//                            };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(sendFilePayload(params,fileData,"document",ENDPOINT_SEND_DOCUMENT));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendDocument(const QVariant &chatId, const QString &fileId, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "document", HttpParameter(fileId) }
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(makeApiCall(ENDPOINT_SEND_DOCUMENT,params,Networking::GET));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendDocument(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_DOCUMENT, params, Networking::UPLOAD));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendVideo(const QVariant &chatId, QFile *file, qint64 duration, const QString &caption, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "duration",HttpParameter(duration) },
//        { "caption",HttpParameter(caption) }
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(sendFilePayload(params,file,"video",ENDPOINT_SEND_VIDEO));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendVideo(const QVariant &chatId, const QString &fileId, qint64 duration, const QString &caption, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "video", HttpParameter(fileId) },
//        { "duration", HttpParameter(duration) },
//        { "caption", HttpParameter(caption) }
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(makeApiCall(ENDPOINT_SEND_VIDEO,params,Networking::GET));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendVideo(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_VIDEO, params, Networking::UPLOAD));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendVoice(const QVariant &chatId, QFile *file, qint64 duration, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "duration",HttpParameter(duration) }
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(sendFilePayload(params,file,"voice",ENDPOINT_SEND_VOICE));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendVoice(const QVariant &chatId, const QString &fileId, qint64 duration, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "voice", HttpParameter(fileId) },
//        { "duration", HttpParameter(duration) }
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id",HttpParameter(replyToMessageId));

//    return responseMessageId(makeApiCall(ENDPOINT_SEND_VOICE,params,Networking::GET));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendVoice(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_VOICE, params, Networking::UPLOAD));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendLocation(const QVariant &chatId, float latitude, float longitude, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    ParameterList params = {
//        { "chat_id", HttpParameter(chatId) },
//        { "latitude", HttpParameter(latitude) },
//        { "longitude", HttpParameter(longitude) }
//    };

//    if (replyToMessageId >= 0) params.insert("reply_to_message_id", HttpParameter(replyToMessageId));

//    return sendLocation(params);
//}

//Message::Id qTbot::ITelegramBot::Bot::sendLocation(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_SEND_LOCATION, params, Networking::POST));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendContact(const QVariant &chatId, const QString &phoneNumber, const QString &firstName)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return sendContact({
//        { "chat_id", HttpParameter(chatId) },
//        { "phone_number", HttpParameter(phoneNumber)},
//        { "first_name",HttpParameter(firstName) }
//    });
//}

//Message::Id qTbot::ITelegramBot::Bot::sendContact(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_CONTACT, params, Networking::GET));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendPoll(const QVariant &chatId, const QString &question, const QStringList &options)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return sendPoll({
//        { "chat_id",  HttpParameter(chatId) },
//        { "question", HttpParameter(question)},
//        { "options",  HttpParameter(options) }
//    });
//}

//Message::Id qTbot::ITelegramBot::Bot::sendPoll(const QVariant &chatId, const QString &question, const QStringList &options, bool isAnonymous)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return sendPoll({
//        { "chat_id",         HttpParameter(chatId) },
//        { "question",        HttpParameter(question)},
//        { "options",         HttpParameter(options) },
//        { "is_anonymous",    HttpParameter(isAnonymous) }
//    });
//}

//Message::Id qTbot::ITelegramBot::Bot::sendPoll(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_POLL, params, Networking::POST));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendDice(const QVariant &chatId, Message::Id replyToMessageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    ParameterList params;
//    params.insert("chat_id", HttpParameter(chatId));
//    if (replyToMessageId > 0)
//        params.insert("message_id",HttpParameter(replyToMessageId));

//    return sendDice(params);
//}

//Message::Id qTbot::ITelegramBot::Bot::sendDice(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_DICE, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::sendChatAction(const QVariant &chatId, Bot::ChatAction action)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::LongLong && chatId.type() != QVariant::Int) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    ParameterList params;
//    params.insert("chat_id", HttpParameter(chatId));
//    switch (action) {
//    case Typing:
//        params.insert("action", HttpParameter("typing"));
//        break;
//    case UploadingPhoto:
//        params.insert("action", HttpParameter("upload_photo"));
//        break;
//    case RecordingVideo:
//        params.insert("action", HttpParameter("record_video"));
//        break;
//    case UploadingVideo:
//        params.insert("action", HttpParameter("upload_video"));
//        break;
//    case RecordingAudio:
//        params.insert("action", HttpParameter("record_audio"));
//        break;
//    case UploadingAudio:
//        params.insert("action", HttpParameter("upload_audio"));
//        break;
//    case UploadingDocument:
//        params.insert("action", HttpParameter("upload_document"));
//        break;
//    case FindingLocation:
//        params.insert("action", HttpParameter("find_location"));
//        break;
//    case RecordingVoice:
//        params.insert("action", HttpParameter("record_voice"));
//        break;
//    case UploadingVoice:
//        params.insert("action", HttpParameter("upload_voice"));
//        break;
//    case RecordingVideoNote:
//        params.insert("action", HttpParameter("record_video_note"));
//        break;
//    case UploadingVideoNote:
//        params.insert("action", HttpParameter("upload_video_note"));
//        break;
//    case ChoosingSticker:
//        params.insert("action", HttpParameter("choose_sticker"));
//        break;
//    }

//    return sendChatAction(params);
//}

//bool qTbot::ITelegramBot::Bot::sendChatAction(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_SEND_CHAT_ACTION, params, Networking::POST));
//}

//UserProfilePhotos qTbot::ITelegramBot::Bot::getUserProfilePhotos(User::Id userId, qint16 offset, qint8 limit)
//{
//    ParameterList params;
//    params.insert("user_id", HttpParameter(userId));
//    if (offset > -1) params.insert("offset", HttpParameter(offset));
//    if (limit > -1) params.insert("limit", HttpParameter(limit));

//    return getUserProfilePhotos(params);
//}

//UserProfilePhotos qTbot::ITelegramBot::Bot::getUserProfilePhotos(ParameterList &params)
//{
//    return responseObject<UserProfilePhotos>(makeApiCall(ENDPOINT_GET_USER_PROFILE_PHOTOS,params,Networking::GET));
//}

//File qTbot::ITelegramBot::Bot::getFile(const QString &fileId)
//{
//    return getFile({
//        {"file_id",HttpParameter(fileId)}
//    });
//}

//File qTbot::ITelegramBot::Bot::getFile(const ParameterList &params)
//{
//    return responseObject<File>(makeApiCall(ENDPOINT_GET_FILE, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::banChatMember(const QVariant &chatId, User::Id userId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::LongLong && chatId.type() != QVariant::Int) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return banChatMember({
//        { "chat_id", HttpParameter(chatId) },
//        { "user_id", HttpParameter(userId) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::banChatMember(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_BAN_CHAT_MEMBER,params,Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::unbanChatMember(const QVariant &chatId, User::Id userId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::LongLong && chatId.type() != QVariant::Int) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return unbanChatMember({
//        { "chat_id", HttpParameter(chatId) },
//        { "user_id", HttpParameter(userId) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::unbanChatMember(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_UNBAN_CHAT_MEMBER, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::restrictChatMember(const QVariant &chatId, const QVariant &userId, qint32 untilDate, bool canSendMessages, bool can_send_media_messages, bool can_send_other_messages, bool can_add_web_page_previews)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return restrictChatMember({
//        { "chat_id",                        HttpParameter(chatId) },
//        { "user_id",                        HttpParameter(userId) },
//        { "until_date",                     HttpParameter(untilDate) },
//        { "can_send_messages",              HttpParameter(canSendMessages) },
//        { "can_send_media_messages",        HttpParameter(can_send_media_messages) },
//        { "can_send_other_messages",        HttpParameter(can_send_other_messages) },
//        { "can_add_web_page_previews",      HttpParameter(can_add_web_page_previews) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::restrictChatMember(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_RESTRICT_CHAT_MEMBER,params,Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::setChatAdministratorCustomTitle(const QVariant &chatId, User::Id userId, const QString &customTitle)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return setChatAdministratorCustomTitle({
//        { "chat_id",         HttpParameter(chatId) },
//        { "user_id",         HttpParameter(userId) },
//        { "custom_title",    HttpParameter(customTitle) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::setChatAdministratorCustomTitle(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_SET_CHAT_ADMIN_CUSTOM_TITLE,params,Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::banChatSenderChat(const QVariant &chatId, const QVariant &senderChatId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    if (senderChatId.type() != QVariant::String && senderChatId.type() != QVariant::Int && senderChatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return banChatSenderChat({
//        { "chat_id",         HttpParameter(chatId) },
//        { "sender_chat_id",  HttpParameter(senderChatId) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::banChatSenderChat(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_BAN_CHAT_SENDER_CHAT, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::unbanChatSenderChat(const QVariant &chatId, const QVariant &senderChatId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    if (senderChatId.type() != QVariant::String && senderChatId.type() != QVariant::Int && senderChatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return unbanChatSenderChat({
//        { "chat_id",         HttpParameter(chatId) },
//        { "sender_chat_id",  HttpParameter(senderChatId) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::unbanChatSenderChat(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_UNBAN_CHAT_SENDER_CHAT, params, Networking::GET));
//}

//QString qTbot::ITelegramBot::Bot::exportChatInviteLink(const QVariant &chatId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return QString();
//    }

//    return exportChatInviteLink({
//        { "chat_id",HttpParameter(chatId) }
//    });
//}

//QString qTbot::ITelegramBot::Bot::exportChatInviteLink(const ParameterList &params)
//{
//    return responseString(makeApiCall(ENDPOINT_EXPORT_CHAT_INVITE_LINK, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::approveChatJoinRequest(const QVariant &chatId, User::Id userId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    ParameterList params;
//    params.insert("chat_id",HttpParameter(chatId));
//    params.insert("user_id",HttpParameter(userId));

//    return approveChatJoinRequest(params);
//}

//bool qTbot::ITelegramBot::Bot::approveChatJoinRequest(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_APPROVE_CHAT_JOIN_REQUEST, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::declineChatJoinRequest(const QVariant &chatId, User::Id userId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return approveChatJoinRequest({
//        { "chat_id",HttpParameter(chatId) },
//        { "user_id",HttpParameter(userId) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::declineChatJoinRequest(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_DECLINE_CHAT_JOIN_REQUEST, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::setChatTitle(const QVariant &chatId, const QString &title)
//{
//    return setChatTitle({
//        { "chat_id", HttpParameter(chatId) },
//        { "title",   HttpParameter(title) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::setChatTitle(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_SET_CHAT_TITLE, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::pinChatMessage(const QVariant &chatId, Message::Id messageId)
//{
//    return pinChatMessage({
//        { "chat_id", HttpParameter(chatId) },
//        { "message_id", HttpParameter(messageId) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::pinChatMessage(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_PIN_CHAT_MESSAGE, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::unpinChatMessage(const QVariant &chatId, Message::Id messageId)
//{
//    return unpinChatMessage({
//        { "chat_id", HttpParameter(chatId) },
//        { "message_id", HttpParameter(messageId) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::unpinChatMessage(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_UNPIN_CHAT_MESSAGE, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::unpinAllChatMessages(const QVariant &chatId)
//{
//    return unpinAllChatMessages({
//        { "chat_id", HttpParameter(chatId) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::unpinAllChatMessages(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_UNPIN_ALL_CHAT_MESSAGES, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::leaveChat(const QVariant &chatId)
//{
//    return leaveChat({
//        { "chat_id", HttpParameter(chatId) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::leaveChat(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_LEAVE_CHAT, params, Networking::GET));
//}

//Chat qTbot::ITelegramBot::Bot::getChat(const QVariant &chatId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return Chat();
//    }

//    return getChat({
//        {"chat_id", HttpParameter(chatId)}
//    });
//}

//Chat qTbot::ITelegramBot::Bot::getChat(const ParameterList &params)
//{
//    return responseObject<Chat>(makeApiCall(ENDPOINT_GET_ME, params,Networking::GET));
//}

//QList<ChatMember> qTbot::ITelegramBot::Bot::getChatAdministrators(const QVariant &chatId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return QList<ChatMember>();
//    }

//    return getChatAdministrators({
//        {"chat_id", HttpParameter(chatId)}
//    });
//}

//QList<ChatMember> qTbot::ITelegramBot::Bot::getChatAdministrators(const ParameterList &params)
//{
//    return responseObjectList<ChatMember>(makeApiCall(ENDPOINT_GET_CHAT_ADMINISTRATORS, params, Networking::GET));
//}

//int qTbot::ITelegramBot::Bot::getChatMemberCount(const QVariant &chatId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return 0;
//    }

//    return getChatMemberCount({
//        {"chat_id", HttpParameter(chatId)}
//    });
//}

//int qTbot::ITelegramBot::Bot::getChatMemberCount(const ParameterList &params)
//{
//    return responseInt(makeApiCall(ENDPOINT_GET_CHAT_ADMINISTRATORS, params, Networking::GET));
//}

//ChatMember qTbot::ITelegramBot::Bot::getChatMember(const QVariant &chatId, User::Id userId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return ChatMember();
//    }

//    return getChatMember({
//        { "chat_id", HttpParameter(chatId) },
//        { "user_id",HttpParameter(userId) }
//    });
//}

//ChatMember qTbot::ITelegramBot::Bot::getChatMember(const ParameterList &params)
//{
//    return responseObject<ChatMember>(makeApiCall(ENDPOINT_GET_CHAT_MEMBER_COUNT, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::answerCallbackQuery(const QString &callbackQueryId, const QString &text, bool showAlert, const QString &url, qint32 cahceTime)
//{
//    ParameterList params;
//    params.insert("callback_query_id",HttpParameter(callbackQueryId));
//    params.insert("text",HttpParameter(text));
//    params.insert("show_alert",HttpParameter(showAlert));
//    params.insert("url",HttpParameter(url));
//    params.insert("cache_time",HttpParameter(cahceTime));

//    return answerCallbackQuery(params);
//}

//bool qTbot::ITelegramBot::Bot::answerCallbackQuery(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_ANSWER_CALLBACK_QUERY,params,Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::setMyCommands(const BotCommandList &commands)
//{
//    return setMyCommands({
//        {"commands", HttpParameter(commands.toByteArray())}
//    });
//}

//bool qTbot::ITelegramBot::Bot::setMyCommands(const BotCommandList &commands, const GenericScope &commandScope)
//{
//    return setMyCommands({
//        { "commands",   HttpParameter(commands.toByteArray()) },
//        { "scope",      HttpParameter(commandScope.serialize()) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::setMyCommands(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_SET_MY_COMMANDS,params,Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::deleteMyCommands()
//{
//    return deleteMyCommands(ParameterList());
//}

//bool qTbot::ITelegramBot::Bot::deleteMyCommands(const GenericScope &commandScope)
//{
//    return deleteMyCommands({
//        {"scope",HttpParameter(commandScope.serialize())}
//    });
//}

//bool qTbot::ITelegramBot::Bot::deleteMyCommands(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_DELETE_MY_COMMANDS,params,Networking::GET));
//}

//BotCommandList qTbot::ITelegramBot::Bot::getMyCommands()
//{
//    return getMyCommands(ParameterList());
//}

//BotCommandList qTbot::ITelegramBot::Bot::getMyCommands(const GenericScope &commandScope)
//{
//    return getMyCommands({
//        {"scope", HttpParameter(commandScope.serialize())}
//    });
//}

//BotCommandList qTbot::ITelegramBot::Bot::getMyCommands(const ParameterList &params)
//{
//    return BotCommandList(responseObject<BotCommandList>(makeApiCall(ENDPOINT_GET_MY_COMMANDS,params,Networking::GET)));
//}

//bool qTbot::ITelegramBot::Bot::editMessageText(const QVariant &chatId, Message::Id messageId, const QString &text)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return editMessageText({
//        { "chat_id",HttpParameter(chatId) },
//        { "message_id",HttpParameter(messageId) },
//        { "text",HttpParameter(text) }
//    });
//}

//bool qTbot::ITelegramBot::Bot::editMessageText(const QVariant &chatId, Message::Id messageId, const QString &text, const GenericReply &replyMarkup)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    ParameterList params = {
//        { "chat_id",HttpParameter(chatId) },
//        { "message_id",HttpParameter(messageId) },
//        { "text",HttpParameter(text) }
//    };

//    params.insert("reply_markup", HttpParameter(replyMarkup.serialize()));

//    return editMessageText(params);
//}

//bool qTbot::ITelegramBot::Bot::editMessageText(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_EDIT_MESSAGE_TEXT,params,Networking::POST));
//}

//bool qTbot::ITelegramBot::Bot::editMessageReplyMarkup(const QVariant &chatId, Message::Id messageId, const GenericReply &replyMarkup)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    ParameterList params;
//    params.insert("chat_id",HttpParameter(chatId));
//    params.insert("message_id",HttpParameter(messageId));
//    params.insert("reply_markup", HttpParameter(replyMarkup.serialize()));

//    return editMessageReplyMarkup(params);
//}

//bool qTbot::ITelegramBot::Bot::editMessageReplyMarkup(const QString &inlineMessageId, const GenericReply &replyMarkup)
//{
//    ParameterList params;
//    params.insert("inline_message_id",HttpParameter(inlineMessageId));
//    params.insert("reply_markup", HttpParameter(replyMarkup.serialize()));

//    return editMessageReplyMarkup(params);
//}

//bool qTbot::ITelegramBot::Bot::editMessageReplyMarkup(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_EDIT_MESSAGE_REPLY_MARKUP, params, Networking::POST));
//}

//bool qTbot::ITelegramBot::Bot::stopPoll(const QVariant &chatId, Message::Id messageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return stopPoll({
//        { "chat_id", HttpParameter(chatId) },
//        { "message_id", HttpParameter(messageId)  }
//    });
//}

//bool qTbot::ITelegramBot::Bot::stopPoll(const QVariant &chatId, int messageId, const GenericReply &replyMarkup)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    ParameterList params = {
//        { "chat_id", HttpParameter(chatId) },
//        { "message_id", HttpParameter(messageId)  }
//    };

//    params.insert("reply_markup",HttpParameter(replyMarkup.serialize()));

//    return stopPoll(params);
//}

//bool qTbot::ITelegramBot::Bot::stopPoll(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_STOP_POLL, params, Networking::GET));
//}

//bool qTbot::ITelegramBot::Bot::deleteMessage(const QVariant &chatId, Message::Id messageId)
//{
//    if (chatId.type() != QVariant::String && chatId.type() != QVariant::Int && chatId.type() != QVariant::LongLong) {
//        qCritical("Please provide a QString or int as chatId");
//        return false;
//    }

//    return deleteMessage({
//        { "chat_id", HttpParameter(chatId) },
//        { "message_id", HttpParameter(messageId)  }
//    });
//}

//bool qTbot::ITelegramBot::Bot::deleteMessage(const ParameterList &params)
//{
//    return responseOk(makeApiCall(ENDPOINT_DELETE_MESSAGE,params,Networking::GET));
//}

//Message::Id qTbot::ITelegramBot::Bot::sendSticker(const QVariant &chatId, const QString &sticker)
//{
//    return sendSticker({
//        { "chat_id", HttpParameter(chatId) },
//        { "sticker", HttpParameter(sticker) }
//    });
//}

//Message::Id qTbot::ITelegramBot::Bot::sendSticker(const ParameterList &params)
//{
//    return responseMessageId(makeApiCall(ENDPOINT_SEND_STICKER,params,Networking::GET));
//}

//QJsonObject qTbot::ITelegramBot::Bot::sendFilePayload(ParameterList params, QFile *filePayload, const QString &payloadType, const QString &endpoint)
//{
//    bool openedFile = false;
//    if (!filePayload->isOpen()) {
//        if (!filePayload->open(QFile::ReadOnly)) {
//            qCritical("Could not open file %s [%s]", qPrintable(filePayload->fileName()), qPrintable(filePayload->errorString()));
//            return QJsonObject();
//        }
//        openedFile = true;
//    }

//    QByteArray data = filePayload->readAll();
//    if (openedFile) filePayload->close();
//    params.insert(payloadType, HttpParameter(data, true, m_mimeDatabase.mimeTypeForData(data).name(), filePayload->fileName()));

//    return makeApiCall(endpoint,params,Networking::UPLOAD);
//}

//QJsonObject qTbot::ITelegramBot::Bot::sendFilePayload(ParameterList params, const QByteArray &fileData, const QString &payloadType, const QString &endpoint)
//{
//    params.insert(payloadType, HttpParameter(fileData, true, m_mimeDatabase.mimeTypeForData(fileData).name(), QString::number(std::time(nullptr))));
//    return makeApiCall(endpoint,params,Networking::UPLOAD);
//}

//bool ITelegramBot::sendMessage(const QSharedPointer<iMessage> &message) {
//    if (!message)
//        return false;

//    return false;
//}

QByteArray ITelegramBot::makePrefix() const {
    return "https://api.telegram.org/bot" + token();
}

bool ITelegramBot::sendRequest(const QSharedPointer<iRequest> &rquest, const Responce &cb) {
    if (!rquest)
        return false;


    auto getInfoRquest = makePrefix() + rquest->makeUpload();

    QNetworkReply* networkReplay = _manager->get(QNetworkRequest(QUrl::fromEncoded(getInfoRquest)));
    if (!networkReplay)
        return false;

    auto handler = [rquest, cb, networkReplay]() {

        auto rawData = networkReplay->readAll();
        qDebug() << rawData;
        auto message = IBot::makeMesasge<TelegramUpdateAnsver>();
        message->setRawData(rawData);

        if (!message->isValid()) {
            qDebug() << "Some request is wrong: code:" << message->rawJson().value("error_code").toInt();
            qDebug() << "What: " << message->rawJson().value("description").toString();

            return;
        }

        networkReplay->deleteLater();

        if (cb) {
            cb(rquest, message, 0);
        }
    };

    auto err = [rquest, cb, networkReplay](QNetworkReply::NetworkError err) {

        networkReplay->deleteLater();

        if (cb) {
            cb(rquest, nullptr, err);
        }
    };

    connect(networkReplay, &QNetworkReply::finished, handler);
    connect(networkReplay, &QNetworkReply::errorOccurred, err);

    return true;
}

void ITelegramBot::setUsername(const QString &newUsername) {
    _username = newUsername;
}

void ITelegramBot::setId(unsigned long long newId) {
    _id = newId;
}

const QString &ITelegramBot::username() const {
    return _username;
}

unsigned long long ITelegramBot::id() const {
    return _id;
}

} // namespace qTbot
