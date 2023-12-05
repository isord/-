#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <cstdlib>

const int WIDTH = 4;   // x�� ��� ��
const int HEIGHT = 30; // y�� ��� ��

class TypingExercise {
public:
    virtual void start() = 0;
    virtual ~TypingExercise() {}
};

class BasicTypingExercise : public TypingExercise {
protected:
    std::string text;
    int xPos;           // <- ���ڿ��� ������ x�� ��ġ���� �����Ǵ� ��
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
                    userInput = userInput.substr(1); // �Է°��� ���̰� ���ڿ����� ����� ���, �Է°����� ù ���� ����
                }

                if (userInput == text) {
                    text = getRandomWords(); // �Է°��� ���ڿ��� ��ġ�ϸ� ���ο� ���� �ܾ��� ����
                    userInput = "";
                }
            }

            moveDown();
            Sleep(getRandomSpeed()); // <- ���ڿ��� �ϰ��ϴ� �ӵ��� �����ϰ� �����Ǵ� ��
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

        // �� �Ʒ��� 'Your input' �޽����� ������Ŵ
        cursorPosition = { 0, HEIGHT };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    }

    void moveDown() {
        ++yPos;
    }

    int getRandomSpeed() {
        return rand() % 300 + 1000; // <- ���ڿ��� �ð����� �ϰ��ϵ��� �ϴ� �ӵ��� �����ϰ� �����ϴ� ��
    }

    std::string getRandomWords() {
        const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
        const std::string numbers = "0123456789";
        const std::string specialChars = "!@#$%^&*()_+-=[]{};':,.<>?";

        std::string randomString;

        int length = rand() % 6 + 5; // <- ���ڿ��� �ִ� ���̸� �����ϴ� �� (5���� 10 ������ ���� ���� ����)

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
            return ""; // �ùٸ��� ���� �ɼ��� ��� �� ���ڿ� ��ȯ �Ǵ� ���� ó�� �߰�
        }

        return randomString;
    }

    std::string getRandomWords(int opt) {
        switch (opt) {
        case 1: return getRandomWords(); // Alphabet Option
        case 2: return getRandomWords(); // Number Option
        case 3: return getRandomWords(); // Special Character Option
        default: return ""; // �ùٸ��� ���� �ɼ��� ��� �� ���ڿ� ��ȯ �Ǵ� ���� ó�� �߰�
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
