#include "telegram_bot.h"
#include <curl/curl.h>
#include <iostream>

TelegramBot::TelegramBot(const std::string& token, const std::string& chatId) : token(token), chatId(chatId) {}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void TelegramBot::sendMessage(const std::string& message) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string url = "https://api.telegram.org/bot" + token + "/sendMessage";
    std::string postData = "chat_id=" + chatId + "&text=" + message;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
