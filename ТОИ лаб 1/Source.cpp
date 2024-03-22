#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Структура для символов и их частот
struct SymbolFreq {
    char symbol;
    double freq;
};

// Функция для кодирования
double arithmetic_encode(string text, const vector<SymbolFreq>& frequencies) {
    double low = 0.0; // Начальное значение нижней границы
    double high = 1.0; // Начальное значение верхней границы

    for (char c : text) {
        // Находим частоту символа c
        double range = high - low;
        double symbol_low = 0.0;
        for (const SymbolFreq& sf : frequencies) {
            if (sf.symbol == c) {
                high = low + range * (symbol_low + sf.freq);
                low = low + range * symbol_low;
                break;
            }
            symbol_low += sf.freq;
        }
    }

    // Возвращаем любое число из получившегося отрезка
    return low;
}

// Функция для декодирования
string arithmetic_decode(double code, const vector<SymbolFreq>& frequencies, int text_length) {
    string decoded_text;

    double low = 0.0;
    double high = 1.0;

    for (int i = 0; i < text_length; ++i) {
        // Находим символ по подотрезку, содержащему входное вещественное число
        double range = high - low;
        char symbol = '\0';
        double cumulative_prob = 0.0;
        for (const SymbolFreq& sf : frequencies) {
            cumulative_prob += sf.freq;
            if (code < cumulative_prob * range + low) {
                symbol = sf.symbol;
                high = low + range * cumulative_prob;
                low += range * (cumulative_prob - sf.freq);
                break;
            }
        }
        decoded_text += symbol;
    }

    return decoded_text;
}

int main() {
    // Символы и их частоты для слова "vladislav"
    string text = "vladislav";
    vector<SymbolFreq> frequencies = {
        {'v', 2.0 / 9.0},
        {'l', 2.0 / 9.0},
        {'a', 2.0 / 9.0},
        {'d', 1.0 / 9.0},
        {'i', 1.0 / 9.0},
        {'s', 1.0 / 9.0},

    };

    // Кодирование
    double encoded_code = arithmetic_encode(text, frequencies);
    cout << "Encoded code: " << encoded_code << endl;

    // Декодирование
    string decoded_text = arithmetic_decode(encoded_code, frequencies, text.length());
    cout << "Decoded text: " << decoded_text << endl;

    return 0;
}