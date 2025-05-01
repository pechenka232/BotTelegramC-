#include <iostream>
#include "database.h"
#include "telegram_bot.h"
#include "json_utils.h"

int main() {
    
    std::string botToken = "YOUR_BOT_TOKEN";
    std::string chatId = "YOUR_CHAT_ID";

    // Создание объектов
    TelegramBot bot(botToken, chatId);
    Database db("notes.db");

    // Инициализация базы данных
    if (!db.init()) {
        std::cerr << "Не удалось инициализировать базу данных!" << std::endl;
        return 1;
    }

    
    db.addNote("Первая заметка");

    // Пример обновления заметки
    db.updateNote(1, "Обновленная первая заметка");

    
    auto notes = db.getAllNotes();
    std::string notesStr = JsonUtils::jsonToString(notes);
    bot.sendMessage("Заметки:\n" + notesStr);

    return 0;
}
