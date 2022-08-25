#include "messagemodel.h"
#include <QDebug>
MessageModel::MessageModel(OnlineUserModel& senderUser, OnlineSession& sessionDest,
                           QString msgText, QJsonObject msgProfile, QObject *parent) :
    QObject(parent)
{
    senderUsername = senderUser.getUsername();
    sessionID = sessionDest.getSessionID();
    text = msgText;
    profile = msgProfile;
}

int MessageModel::getSessionID() const { return sessionID; }
const QString& MessageModel::getSenderUsername() const { return senderUsername; }


const QString& MessageModel::getMessageText() const { return text; }
const QJsonObject& MessageModel::getMessageProfile() const { return profile; }

MessageModel::MessageModel(MessageModel * old)
{
   if (old == nullptr) {
       return;
   }
   senderUsername = old->senderUsername;
   text = old->text;
   profile = old->profile;
   sessionID = old->sessionID;
}
OnlineMessage::OnlineMessage(QJsonObject json, MessageModel * parent) :
    MessageModel(parent)
{
    messageID = json["MessageID"].toInt();
    sessionID = json["SessionID"].toInt();
    senderUsername = json["SenderName"].toString();

    QJsonObject body = json["Body"].toObject();
    text = body["Text"].toString();
    profile = body["Profile"].toObject();
}

QJsonObject MessageModel::generateJsonOutput() const {
    QJsonObject json = {{ "MsgType", "SessionMessage"}};
    json["MessageID"] = -1;
    json["SessionID"] = sessionID;
    json["SenderName"] = senderUsername;
    QJsonObject body = {{ "Text", text }};
    body["Profile"] = QJsonObject{{ "hasMentionInfo", false }};
    json["Body"] = body;
    return json;
}

OnlineMessage::OnlineMessage(int MessageID, int SessionID, QString sender, QString messageText, QJsonObject Profile, MessageModel * parent)
{
    messageID = MessageID;
    sessionID = SessionID;
    senderUsername = sender;
    text = messageText;
    profile = Profile;
    this->setParent(parent);
}
