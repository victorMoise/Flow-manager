#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class Step {
public:
    virtual void execute() = 0;
};


class TitleStep : public Step {
private:
    std::string title;
    std::string subtitle;
public:
    TitleStep(std::string title, std::string subtitle) : title(title), subtitle(subtitle) {}

    void execute() override {
        std::cout << "Process Title: " << title << "\n";
        std::cout << "Process Subtitle: " << subtitle << "\n";
    }
};


class TextStep : public Step {
private:
    std::string title;
    std::string copy;
public:
    TextStep(std::string title, std::string copy) : title(title), copy(copy) {}

    void execute() override {
        std::cout << "Process Text: " << title << "\n";
        std::cout << "Process Copy: " << copy << "\n";
    }
};


class TextInput : public Step {
private:
    std::string description;
    std::string text;
public:
    TextInput(std::string description, std::string text) : description(description), text(text) {}

    void execute() override {
        std::cout << "Process Description: " << description << "\n";
        std::cout << "Process Text: " << text << "\n";
    }
};


class NumberInput : public Step {
private:
    std::string description;
    float number;
public:
    float getNumber() {
        return number;
    }

    NumberInput(std::string description, float number) : description(description), number(number) {}

    void execute() override {
        std::cout << "Process Description: " << description << "\n";
        std::cout << "Process Number: " << number << "\n";
    }
};


class CalculusStep : public Step {
private: 
    Step *step1, *step2;
    float number1, number2, result;
    std::string operation;

    void add() {
        result = number1 + number2;
    }

    void subtract() {
        result = number1 - number2;
    }

    void multiply() {
        result = number1 * number2;
    }

    void divide() {
        result = number1 / number2;
    }

    void min() {
        result = number1 < number2 ? number1 : number2;
    }

    void max() {
        result = number1 > number2 ? number1 : number2;
    }
public:
    CalculusStep(Step *step1, Step *step2, std::string operation) : step1(step1), step2(step2), number1(dynamic_cast<NumberInput*>(step1)->getNumber()), number2(dynamic_cast<NumberInput*>(step2)->getNumber()) {}

    float getResult() {
        return result;
    }

    void execute() override {
        if (operation == "add") {
            add();
        } else if (operation == "subtract") {
            subtract();
        } else if (operation == "multiply") {
            multiply();
        } else if (operation == "divide") {
            divide();
        } else if (operation == "min") {
            min();
        } else if (operation == "max") {
            max();
        }
    }
};


class TextFileStep : public Step {
private:
    std::string description;
    std::string name = "NOFILE"; // default value
    std::ifstream file;
public:
    TextFileStep(std::string description, std::string name) :  description(description), name(name) {
        try {
            name += ".txt";
            file.open(name);
            if (!file) {
                throw std::runtime_error("File not found!");
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    void execute() override {
        std::cout << "Process Description: " << description << "\n";
        std::cout << "File Name: " << name << "\n";

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
    }
};


class CsvFileStep : public Step {
private:
    std::string description;
    std::string name = "NOFILE"; // default value
    std::ifstream file;
public:
    CsvFileStep(std::string description, std::string name) : description(description) ,name(name) {
        try {
            std::string newName = name + ".csv";
            file.open(newName);
            if (!file) {
                throw std::runtime_error("File not found!");
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    void execute() override {
        std::cout << "Process Description: " << description << "\n";
        std::cout << "File Name: " << name << "\n";

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
    }
};


class DisplayStep : public Step {
private:
    Step *step1, *step2;

    void displayContentsOfFile(std::ifstream& file) {
        std::string line;
        while (getline(file, line)) {
            std::cout << line << "\n";
        }
    }
public:
    DisplayStep(Step *step1, Step *step2) : step1(step1), step2(step2) {}

    void execute() override {
        std::cout << "Display the contents of:\n";
        std::cout << "1. TextFile\n2. CsvFile\n";
        std::cout << "Enter your choice: ";

        try {
            int choice;
            std::cin >> choice;
            if (choice != 1 && choice != 2) {
                throw std::runtime_error("Invalid choice!");
            } else if (choice == 1) {
                if (step1 != nullptr) {
                    step1->execute();
                } else {
                    throw std::runtime_error("No Text file!");
                }
            } else if (choice == 2) {
                if (step2 != nullptr) {
                    step2->execute();
                } else {
                    throw std::runtime_error("No CSV file!");
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
};


class OutputStep : public Step {

};

int main() {

}