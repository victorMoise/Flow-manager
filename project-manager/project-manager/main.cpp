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
    TitleStep() : title("NO TITLE"), subtitle("NO SUBTITLE") {}

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
    TextStep() : title("NO TITLE"), copy("NO COPY") {}

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
    TextInput() : description("NO DESCRIPTION"), text("NO TEXT") {}

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
    NumberInput() : description("NO DESCRIPTION"), number(0) {}

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
    CalculusStep() : step1(nullptr), step2(nullptr), number1(0), number2(0) {}

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
    TextFileStep() : description("NO DESCRIPTION"), name("NOFILE") {}
    TextFileStep(std::string description, std::string name) :  description(description), name(name + ".txt") {
        try {
            file.open(this->name);
            if (!file) {
                throw std::runtime_error("File not found!");
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::string getName() {
        return name;
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
    CsvFileStep() : description("NO DESCRIPTION"), name("NOFILE") {}
    CsvFileStep(std::string description, std::string name) : description(description), name(name + ".csv") {
        try {
            file.open(this->name);
            if (!file) {
                throw std::runtime_error("File not found!");
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::string getName() {
        return name;
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
    std::string filename;

    void displayContentsOfFile(std::string name) {
        std::ifstream file(name);
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
    }

public:
    DisplayStep(std::string filename) : filename(filename) {}
    DisplayStep() : filename("NOFILE") {}

    void execute() override {
        displayContentsOfFile(filename);
    }
};


class OutputStep : public Step {
private:
    std::string title;
    std::string description;
    std::string previousInfo;
public:
    OutputStep(std::string title, std::string description, std::string previousInfo) : title(title), description(description), previousInfo(previousInfo) {}
    OutputStep() : title("NO TITLE"), description("NO DESCRIPTION"), previousInfo("NO PREVIOUS INFO") {}

    void execute() override {
        std::cout << "Process Title: " << title << "\n";
        std::cout << "Process Description: " << description << "\n";
        std::cout << "Previous Info: " << previousInfo << "\n";
    }
};


class Flow {
private:
    std::vector<Step*> steps;
    std::string name;

public:
    void addStep(Step* step) {
        steps.push_back(step);
    }

    std::vector<Step*> getStep() {
        return steps;
    }

    void execute() {
        for (auto step : steps) {
            if (step != nullptr) { // Add null check
                step->execute();
            }
        }
    }
};


int main() {
    std::vector<Flow*> flows;

    try {
        // Initial options to create or execute a flow
        std::cout << "1. Create a new flow\n";
        std::cout << "2. Execute a flow\n";
        std::cout << "Enter your choice: "; 
        std::string choice;
        getline(std::cin, choice);
        

        // Creating a new flow
        if (choice == "1") {
            // create a new flow
            Flow* flow = new Flow();

            // giving a name to the flow is forced, this cannot be skipped
            std::cout << "---------------------------\n";
            std::cout << "Enter the name of the flow: ";
            std::string name;
            getline(std::cin, name);

            while (true) {
                // display all available steps
                std::cout << "---------------------------\n";
                std::cout << "Available steps:\n";
                std::cout << "1. Title\n";
                std::cout << "2. Text\n";
                std::cout << "3. TextInput\n";
                std::cout << "4. NumberInput\n";
                std::cout << "5. Calculus\n";
                std::cout << "6. TextFile\n";
                std::cout << "7. CsvFile\n";
                std::cout << "8. Display\n";
                std::cout << "9. Output\n";
                std::cout << "0. End\n";
                std::cout << "Enter your choice: ";

                // get the user's choice
                std::string stepChoice;
                getline(std::cin, stepChoice);

                if (stepChoice == "0") { // add the flow to the list of flows and exit the loop
                    flows.push_back(flow);
                    break; 
                } else if (stepChoice == "1") { // create and add a new TitleStep
                    Step* step = new TitleStep();
                    flow->addStep(step);
                    std::cout << "Title added successfully!\n";
                } else if (stepChoice == "2") { // create and add a new TextStep
                    Step* step = new TextStep();
                    flow->addStep(step);
                    std::cout << "Text added successfully!\n";
                } else if (stepChoice == "3") { // create and add a new TextInput
                    Step *step = new TextInput();
                    flow->addStep(step);
                    std::cout << "TextInput added successfully!\n";
                } else if (stepChoice == "4") { // create and add a new NumberInput
                    Step *step = new NumberInput();
                    flow->addStep(step);
                    std::cout << "Number added successfully!\n";
                } else if (stepChoice == "5") { // create and add a new CalculusStep
                    Step *step = new CalculusStep();
                    flow->addStep(step);
                    std::cout << "Calculus added successfully!\n";
                } else if (stepChoice == "6") { // create and add a new TextFileStep
                    Step *step = new TextFileStep();
                    flow->addStep(step);
                    std::cout << "TextFile added successfully!\n";
                } else if (stepChoice == "7") { // create and add a new CsvFileStep
                    Step *step = new CsvFileStep();
                    flow->addStep(step);
                    std::cout << "CsvFile added successfully!\n";
                } else if (stepChoice == "8") { // create and add a new DisplayStep
                    Step *step = new DisplayStep();
                    flow->addStep(step);
                    std::cout << "Display added successfully!\n";
                } else if (stepChoice == "9") { // create and add a new OutputStep
                    Step *step = new OutputStep();
                    flow->addStep(step);
                    std::cout << "Output added successfully!\n";
                } else { // insteaf of throwing an error, just display a message and ask the user to try again
                    std::cout << "Invalid choice! Please try again.\n";
                }
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    for (auto flow : flows) {
        flow->execute();
    }
}