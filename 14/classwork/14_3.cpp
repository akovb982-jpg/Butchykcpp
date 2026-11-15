/*
 * Розділ 14, задача 3 (аудиторна).
 * У текстовому файлі слова зашифровані - кожне з них записано навпаки.
 * Розшифрувати повідомлення та вивести його в інший файл. Слова
 * розділяються пробілами (довільною кількістю) та знаками коми, крапки,
 * знаками оклику та питання.
 *
 * Роздільники (і переводи рядків) залишаються на своїх місцях, кожне слово
 * перевертається. Слова перевертаються по символах UTF-8, тому працюють і
 * українські літери.
 */
#include <iostream>
#include <fstream>
#include <string>

bool is_separator(char c){
    return c == ' ' || c == ',' || c == '.' || c == '!' || c == '?' ||
           c == '\n' || c == '\r' || c == '\t';
}

// перевертає рядок UTF-8 по символах (а не по байтах)
std::string reverse_utf8(const std::string &w){
    std::string r;
    size_t i = w.size();
    while (i > 0){
        size_t start = i - 1;
        // байти-продовження мають вигляд 10xxxxxx
        while (start > 0 && (static_cast<unsigned char>(w[start]) & 0xC0) == 0x80) start--;
        r += w.substr(start, i - start);
        i = start;
    }
    return r;
}

int main(){
    std::string in_name, out_name;
    std::cout << "Encrypted file: ";
    std::cin >> in_name;
    std::cout << "Output file: ";
    std::cin >> out_name;

    std::ifstream fin(in_name);
    if (!fin){
        std::cout << "Cannot open " << in_name << '\n';
        return 1;
    }
    std::ofstream fout(out_name);
    if (!fout){
        std::cout << "Cannot create " << out_name << '\n';
        return 1;
    }

    std::string word;
    char c;
    while (fin.get(c)){
        if (is_separator(c)){
            fout << reverse_utf8(word) << c;
            word.clear();
        } else {
            word += c;
        }
    }
    fout << reverse_utf8(word);   // останнє слово, якщо файл не закінчується роздільником
    std::cout << "Done. Result is in " << out_name << '\n';
    return 0;
}
