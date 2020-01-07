#include "tiingoconnection.hpp"
#include <QWebSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

TiingoConnection::TiingoConnection(QObject *parent) : QObject(parent)
{
    auto server = "wss://api.tiingo.com/crypto";
    m_webSocket = new QWebSocket();
    connect(m_webSocket, &QWebSocket::connected, this, &TiingoConnection::onConnected);
//    connect(socket, &QWebSocket::disconnected, this, &TiingoConnection::closed);
    m_webSocket->open(QUrl(server));

}

void TiingoConnection::onConnected()
{
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &TiingoConnection::onTextMessageReceived);
    m_webSocket->sendTextMessage(QStringLiteral("{\"eventName\": \"subscribe\", \"authorization\": \"f93cffb30bc3677785631b17ecb55a7c8ab9ac3a\", \"eventData\": {\"thresholdLevel\": 2}}"));
}

void TiingoConnection::onTextMessageReceived(QString message)
{
    // qDebug() << "Message received:" << message;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    auto obj = doc.object();

    if (!obj.contains("data")) {
        return;
    }
    if (obj["messageType"].toString() != "A") {
        return;
    }
    auto data = obj["data"].toArray();
    if (data[0].toString() != "Q") {
        return;
    }
    auto pair = data[1].toString();
    if (!pair.contains("bnb")) {
        //return;
    }
    double bidSz = data[4].toDouble();
    double bidPr = data[5].toDouble();
    double askSz = data[7].toDouble();
    double askPr = data[8].toDouble();
    emit newBid(pair, bidSz, bidPr, askSz, askPr);
}
