#ifndef TIINGOCONNECTION_HPP
#define TIINGOCONNECTION_HPP

#include <QObject>

class QWebSocket;

class TiingoConnection : public QObject
{
    Q_OBJECT
    void onConnected();
    void onTextMessageReceived(QString message);
    enum class Quotes{BidSz, BidPr, AskSz, AskPr};

public:
    explicit TiingoConnection(QObject *parent = nullptr);

signals:
    void newBid(QString pair, double bidSz, double bidPr, double askSz, double askPr);

private:
    QWebSocket* m_webSocket = nullptr;
};

#endif // TIINGOCONNECTION_HPP
