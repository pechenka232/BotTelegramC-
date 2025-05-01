#ifndef TELEGRAM_BOT_H
#define TELEGRAM_BOT_H

#include <string>

class TelegramBot {
public:
    TelegramBot(const std::string& token, const std::string& chatId);
    void sendMessage(const std::string& message);

private:
    std::string token;
    std::string chatId;
};

#endif // TELEGRAM_BOT_H
