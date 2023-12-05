#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <cstdlib>

const int WIDTH = 4;   // x축 등분 수
const int HEIGHT = 30; // y축 등분 수

class TypingExercise {
public:
    virtual void start() = 0;
    virtual ~TypingExercise() {}
};

class BasicTypingExercise : public TypingExercise {
protected:
    std::string text;
    int xPos;           // <- 문자열이 랜덤한 x축 위치에서 생성되는 곳
    int yPos;
    std::string userInput;
    int option;

public:
    BasicTypingExercise(const std::string& inputText, int x, int y, int opt) : text(inputText), xPos(x), yPos(y), option(opt) {}

    void start() override {
        userInput = "";

        while (true) {
            clearScreen();
            printText();
            printUserInput();

            if (yPos >= HEIGHT - 1) {
                break;
            }

            if (_kbhit()) {
                char input = _getch();
                userInput += input;

                if (userInput.length() > text.length()) {
                    userInput = userInput.substr(1); // 입력값의 길이가 문자열보다 길어질 경우, 입력값에서 첫 글자 제거
                }

                if (userInput == text) {
                    text = getRandomWords(); // 입력값과 문자열이 일치하면 새로운 랜덤 단어들로 갱신
                    userInput = "";
                }
            }

            moveDown();
            Sleep(getRandomSpeed()); // <- 문자열이 하강하는 속도가 랜덤하게 조정되는 곳
        }

        std::cout << "Game Over!" << std::endl;
    }

protected:
    void clearScreen() {
        COORD cursorPosition = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    }

    void printText() {
        COORD cursorPosition = { xPos, yPos };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
        std::cout << text;
    }

    void printUserInput() {
        COORD cursorPosition = { 0, HEIGHT };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
        std::cout << "Your input: " << userInput;

        // 맨 아래에 'Your input' 메시지를 고정시킴
        cursorPosition = { 0, HEIGHT };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    }

    void moveDown() {
        ++yPos;
    }

    int getRandomSpeed() {
        return rand() % 300 + 1000; // <- 문자열이 시간별로 하강하도록 하는 속도를 랜덤하게 조정하는 곳
    }

    std::string getRandomWords() {
        const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
        const std::string numbers = "0123456789";
        const std::string specialChars = "!@#$%^&*()_+-=[]{};':,.<>?";

        std::string randomString;

        int length = rand() % 6 + 5; // <- 문자열의 최대 길이를 결정하는 곳 (5에서 10 사이의 랜덤 길이 설정)

        switch (option) {
        case 1: // Alphabet Option
            for (int i = 0; i < length; ++i) {
                int index = rand() % alphabet.length();
                randomString += alphabet[index];
            }
            break;
        case 2: // Number Option
            for (int i = 0; i < length; ++i) {
                int index = rand() % numbers.length();
                randomString += numbers[index];
            }
            break;
        case 3: // Special Character Option
            for (int i = 0; i < length; ++i) {
                int index = rand() % specialChars.length();
                randomString += specialChars[index];
            }
            break;
        case 4: // All Option
            randomString += getRandomWords(1);
            randomString += getRandomWords(2);
            randomString += getRandomWords(3);
            break;
        default:
            return ""; // 올바르지 않은 옵션일 경우 빈 문자열 반환 또는 에러 처리 추가
        }

        return randomString;
    }

    std::string getRandomWords(int opt) {
        switch (opt) {
        case 1: return getRandomWords(); // Alphabet Option
        case 2: return getRandomWords(); // Number Option
        case 3: return getRandomWords(); // Special Character Option
        default: return ""; // 올바르지 않은 옵션일 경우 빈 문자열 반환 또는 에러 처리 추가
        }
    }
};

TypingExercise* createExerciseWithOptions(int option) {
    srand(static_cast<unsigned int>(time(nullptr)));

    switch (option) {
    case 1:
        return new BasicTypingExercise("", rand() % (80 / WIDTH) * WIDTH, 0, option);
    case 2:
        return new BasicTypingExercise("", rand() % (80 / WIDTH) * WIDTH, 0, option);
    case 3:
        return new BasicTypingExercise("", rand() % (80 / WIDTH) * WIDTH, 0, option);
    case 4:
        return new BasicTypingExercise("", rand() % (80 / WIDTH) * WIDTH, 0, option);
    default:
        return nullptr;
    }
}

int main() {
    int option;
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Alphabet\n2. Number\n3. Special Character\n4. All" << std::endl;
    std::cin >> option;

    TypingExercise* exercise = createExerciseWithOptions(option);

    exercise->start();

    delete exercise;

    return 0;
}
