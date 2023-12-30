#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

class Step {
public:
    virtual void execute() = 0;
};

std::vector<Step*> currentFlowSteps;


class TitleStep : public Step {
private:
    std::string title;
    std::string subtitle;
public:
    TitleStep(std::string title, std::string subtitle) : title(title), subtitle(subtitle) {}
    TitleStep() : title("NO TITLE"), subtitle("NO SUBTITLE") {}

    void displayInfo() {
        std::cout << "Process Title: " << title << "\n";
        std::cout << "Process Subtitle: " << subtitle << "\n";
    }

    void execute() override {
        std::string choice;

        // the user can't continue unless he either completes the step
        // or skips it
        while (true) {
            std::cout << "---------------------------\n";
            std::cout << "Running Title Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);
            if (choice == "1") {
                // Ask the user to input the title and subtitle
                std::cout << "---------------------------\n";
                std::cout << "Title: ";
                std::string title;
                getline(std::cin, title);
                std::cout << "Subtitle: ";
                std::string subtitle;
                getline(std::cin, subtitle);

                // asign each of the new inputs to it's respective field
                this->title = title;
                this->subtitle = subtitle;

                break; // no need to continue
            }
            else if (choice == "2") {
                std::cout << "Skipping this step...\n";
                break; // exit and continue with the next step
            } 
            else {
                std::cout << "Invalid choice! Please try again.\n";
            }
        }
    }
};


class TextStep : public Step {
private:
    std::string title;
    std::string copy;
public:
    TextStep(std::string title, std::string copy) : title(title), copy(copy) {}
    TextStep() : title("NO TITLE"), copy("NO COPY") {}

    void displayInfo() {
        std::cout << "Text Title: " << title << "\n";
        std::cout << "Text: " << copy << "\n";
    }

    void execute() override {
        std::string choice;
        
        // the user can't continue unless he either completes the step
        // or skips it
        while (true) {
            std::cout << "---------------------------\n";
            std::cout << "Running Text Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);
            if (choice == "1") {
                // Ask the user to input the title and copy
                std::cout << "---------------------------\n";
                std::cout << "Title: ";
                std::string title;
                getline(std::cin, title);
                std::cout << "Copy: ";
                std::string copy;
                getline(std::cin, copy);

                // asign each of the new inputs to it's respective field
                this->title = title;
                this->copy = copy;

                break; // no need to continue
            }
            else if (choice == "2") {
                std::cout << "Skipping this step...\n";
                break; // exit and continue with the next step
            }
            else {
                std::cout << "Invalid choice! Please try again.\n";
            }
        }
    }
};


class TextInput : public Step {
private:
    std::string description;
    std::string text;
public:
    TextInput(std::string description, std::string text) : description(description), text(text) {}
    TextInput() : description("NO DESCRIPTION"), text("NO TEXT") {}

    void displayInfo() {
        std::cout << "TextInput Description: " << description << "\n";
        std::cout << "textInput: " << text << "\n";
    }

    void execute() override {
        while (true) {
            std::cout << "---------------------------\n";
            std::cout << "Running TextInput Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            std::string choice;
            getline(std::cin, choice);

            if (choice == "1") {
                // Ask the user to input the description and text
                std::cout << "---------------------------\n";
                std::cout << "Description: ";
                std::string description;
                getline(std::cin, description);
                std::cout << "Text: ";
                std::string text;
                getline(std::cin, text);

                // asign each of the new inputs to it's respective field
                this->description = description;
                this->text = text;

                break; // no need to continue
            }
            else if (choice == "2") {
                std::cout << "Skipping this step...\n";
                break; // exit and continue with the next step
            }
            else {
                std::cout << "Invalid choice! Please try again.\n";
            }
        }
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

    std::string getDescription() {
        return description;
    }

    NumberInput(std::string description, float number) : description(description), number(number) {}
    NumberInput() : description("NO DESCRIPTION"), number(0) {}

    void displayInfo() {
        std::cout << "NumberInput Description: " << description << "\n";
        std::cout << "Number: " << number << "\n";
    }

    void execute() override {
        std::string choice;

        // the user can't continue unless he either completes the step
        // or skips it
        while (true) {
            std::cout << "---------------------------\n";
            std::cout << "Running NumberInput Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);
            
            if (choice == "1") {
                // Ask the user to input the description and number
                std::cout << "---------------------------\n";
                std::cout << "Description: ";
                std::string description;
                getline(std::cin, description);
                std::string number;

                this->description = description;

                bool validNumber = false;
                while (!validNumber) {
                    std::cout << "Number: ";
                    std::string number;
                    getline(std::cin, number); // get the number as a string

                    try {
                        this->number = stof(number); // convert the string to a float
                        validNumber = true;
                    } catch (const std::exception& e) {
                        std::cout << "Invalid number! Please try again.\n";
                    }
                }

                break;
            }
            else if (choice == "2") {
                std::cout << "Skipping this step...\n";
                break; // exit and continue with the next step
            }
            else {
                std::cout << "Invalid choice! Please try again.\n";
            }
        }
    }
};


std::vector<NumberInput*> currentFlowNumberInputs;

class CalculusStep : public Step {
private:
    float number1, number2, result;

    bool isValidNumber(const std::string& str) {
        // Regular expression for a number
        std::regex pattern("^[-+]?[0-9]*\\.?[0-9]+$");

        return std::regex_match(str, pattern);
    }

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
    CalculusStep() : number1(0), number2(0), result(0) {}

    float getResult() {
        return result;
    }

    void execute() override {

        bool stepDone = false;
        while (!stepDone) {
            std::cout << "---------------------------\n";
            std::cout << "Running Calculus Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            std::string choice;
            getline(std::cin, choice);

            if (choice == "1") {
                int chosenNumberInputIndex1 = -1;
                
                while (chosenNumberInputIndex1 < 0 || chosenNumberInputIndex1 >= currentFlowNumberInputs.size()) {
                    std::cout << "---------------------------\n";
                    std::cout << "Choose the first number input step:\n";
                    // Display a list of available NumberInputStep objects and let the user choose
                    for (int i = 0; i < currentFlowNumberInputs.size(); i++) {
                        std::cout << i + 1 << ". " << currentFlowNumberInputs[i]->getNumber() << " (" << currentFlowNumberInputs[i]->getDescription() << ")" << "\n";
                    }
                    std::cout << "Enter your choice: ";
                    std::string chosenNumberInput1Str;
                    getline(std::cin, chosenNumberInput1Str);
                    if (isValidNumber(chosenNumberInput1Str)) {
                        chosenNumberInputIndex1 = std::stoi(chosenNumberInput1Str) - 1;
                        if (chosenNumberInputIndex1 < 0 || chosenNumberInputIndex1 >= currentFlowNumberInputs.size()) {
                            std::cout << "Invalid choice! Please try again.\n";
                        }
                    }
                    else {
                        std::cout << "Invalid choice! Please enter a number.\n";
                    }
                }

                int chosenNumberInputIndex2 = -1;
                while (chosenNumberInputIndex2 < 0 || chosenNumberInputIndex2 >= currentFlowNumberInputs.size()) {
                    std::cout << "---------------------------\n";
                    std::cout << "Choose the second number input step:\n";
                    // Display a list of available NumberInputStep objects and let the user choose
                    for (int i = 0; i < currentFlowNumberInputs.size(); i++) {
                        std::cout << i + 1 << ". " << currentFlowNumberInputs[i]->getNumber() << " (" << currentFlowNumberInputs[i]->getDescription() << ")" << "\n";
                    }
                    std::cout << "Enter your choice: ";
                    std::string chosenNumberInput2Str;
                    getline(std::cin, chosenNumberInput2Str);
                    if (isValidNumber(chosenNumberInput2Str)) {
                        chosenNumberInputIndex2 = std::stoi(chosenNumberInput2Str) - 1;
                        if (chosenNumberInputIndex2 < 0 || chosenNumberInputIndex2 >= currentFlowNumberInputs.size()) {
                            std::cout << "Invalid choice! Please try again.\n";
                        }
                    }
                    else {
                        std::cout << "Invalid choice! Please enter a number.\n";
                    }
                }

                number1 = currentFlowNumberInputs[chosenNumberInputIndex1]->getNumber();
                number2 = currentFlowNumberInputs[chosenNumberInputIndex2]->getNumber();

                while (true) {
                    std::cout << "---------------------------\n";
                    std::cout << "Choose the operation:\n";
                    std::cout << "1. Addition\n";
                    std::cout << "2. Subtraction\n";
                    std::cout << "3. Multiplication\n";
                    std::cout << "4. Division\n";
                    std::cout << "5. Min\n";
                    std::cout << "6. Max\n";
                    std::cout << "Enter your choice: ";
                    std::string operationChoice;
                    getline(std::cin, operationChoice);

                    // Perform the calculation based on the user's choices
                    if (operationChoice == "1" || operationChoice == "+") {
                        add();
                        std::cout << "Result of " << number1 << " + " << number2 << " = " << result << "\n";
                        stepDone = true;
                        break;
                    } else if (operationChoice == "2" || operationChoice == "-") {
                        subtract();
                        std::cout << "Result of " << number1 << " - " << number2 << " = " << result << "\n";
                        stepDone = true;
                        break;
                    } else if (operationChoice == "3" || operationChoice == "*") {
                        multiply();
                        std::cout << "Result of " << number1 << " * " << number2 << " = " << result << "\n";
                        stepDone = true;
                        break;
                    } else if (operationChoice == "4" || operationChoice == "/") {
                        divide();
                        std::cout << "Result of " << number1 << " / " << number2 << " = " << result << "\n";
                        stepDone = true;
                        break;
                    } else if (operationChoice == "5") {
                        min();
                        std::cout << "Result of min(" << number1 << ", " << number2 << ") = " << result << "\n";
                        stepDone = true;
                        break;
                    } else if (operationChoice == "6") {
                        max();
                        std::cout << "Result of max(" << number1 << ", " << number2 << ") = " << result << "\n";
                        stepDone = true;
                        break;
                    } else {
                        std::cout << "Invalid operation choice!\n";
                    }
                }
            } else if (choice == "2") {
                std::cout << "Skipping this step...\n";
                stepDone = true;
                break;
            } else {
                std::cout << "Invalid choice! Please try again.\n";
            }
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
    TextFileStep(std::string description, std::string name) : description(description), name(name + ".txt") {
        try {
            file.open(this->name);
            if (!file) {
                throw std::runtime_error("File not found!");
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::string getName() {
        return name;
    }

    void execute() override {
        std::string choice = "0";
        while (choice != "1" || choice != "2") {
            std::cout << "---------------------------\n";
            std::cout << "Running TextFile Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);

            std::string filename, description;

            if (choice == "1") {
                std::cout << "Enter File Description: ";
                getline(std::cin, description);
                std::cout << "Enter File Name: ";
                getline(std::cin, name);

                this->description = description;
                this->name = name + ".txt";
                return;
            }
            else if (choice == "2") {
                std::cout << "Skipping this step...\n";
                break;
            }
            else {
                std::cout << "Invalid choice! Please try again.\n";
            }
        }

    }
};

std::vector<TextFileStep*> currentFlowTextFileSteps;


class CsvFileStep : public Step {
private:
    std::string description;
    std::string name = "NOFILE"; // default value
    std::ifstream file;
public:
    // default constructor is called when creating the flow
    CsvFileStep() : description("NO DESCRIPTION"), name("NOFILE") {}
    CsvFileStep(std::string description, std::string name) : description(description), name(name + ".csv") {
        try {
            file.open(this->name);
            if (!file) {
                throw std::runtime_error("File not found!");
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::string getName() {
        return name;
    }

    void execute() override {
        std::string choice = "0";
        while (choice != "1" || choice != "2") {
            std::cout << "---------------------------\n";
            std::cout << "Running CsvFile Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);

            std::string filename, description;

            if (choice == "1") {
                std::cout << "Enter File Description: ";
                getline(std::cin, description);
                std::cout << "Enter File Name: ";
                getline(std::cin, name);

                this->description = description;
                this->name = name + ".csv";
                return;
            }
            else if (choice == "2") {
                std::cout << "Skipping this step...\n";
                break;
            }
            else {
                std::cout << "Invalid choice! Please try again.\n";
            }
        }
    }
};

std::vector<CsvFileStep*> currentFlowCsvFileSteps;


class DisplayStep : public Step {
private:
    std::string filename;

    void displayContentsOfFile(std::string name) {
        std::ifstream file(name);
        if (!file.is_open()) {
            std::cout << "Error opening file: " << name << "\n";
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
    }

public:
    DisplayStep(std::string filename) : filename(filename) {}
    DisplayStep() : filename("NOFILE") {}

    void execute() override {
        while (true) {
            std::cout << "---------------------------\n";
            std::cout << "Running Display Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            std::string choice;
            getline(std::cin, choice);

            if (choice == "1") {
                while (true) {
                    std::cout << "---------------------------\n";
                    std::cout << "Display the contents of which file:\n";
                    std::cout << "Text files:\n";
                    for (int i = 0; i < currentFlowTextFileSteps.size(); i++) {
                        std::cout << i + 1 << ". " << currentFlowTextFileSteps[i]->getName() << "\n";
                    }
                    std::cout << "Csv files:\n";
                    for (int i = 0; i < currentFlowCsvFileSteps.size(); i++) {
                        std::cout << i + 1 + currentFlowTextFileSteps.size() << ". " << currentFlowCsvFileSteps[i]->getName() << "\n";
                    }
                    std::cout << "Enter your choice: ";
                    std::string fileChoice;
                    getline(std::cin, fileChoice);

                    if (std::stoi(fileChoice) >= 1 && std::stoi(fileChoice) <= currentFlowTextFileSteps.size()) {
                        displayContentsOfFile(currentFlowTextFileSteps[std::stoi(fileChoice) - 1]->getName());
                        return;
                    }
                    else if (std::stoi(fileChoice) >= currentFlowTextFileSteps.size() + 1 && std::stoi(fileChoice) <= currentFlowTextFileSteps.size() + currentFlowCsvFileSteps.size()) {
                        displayContentsOfFile(currentFlowCsvFileSteps[std::stoi(fileChoice) - currentFlowTextFileSteps.size() - 1]->getName());
                        return;
                    }
                    else {
                        std::cout << "Invalid choice! Please try again.\n";
                    }
                }
            } else {
                std::cout << "Skipping this step...\n";
                break;
            }
        }
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
    Flow(std::string name) : name(name) {}

    void addStep(Step* step) {
        steps.push_back(step);
    }

    std::vector<Step*> getStep() {
        return steps;
    }

    std::string getName() {
        return name;
    }

    void execute() {
        currentFlowNumberInputs.clear();
        currentFlowCsvFileSteps.clear();
        currentFlowTextFileSteps.clear();
        std::cout << "---------------------------\n";
        std::cout << "Executing flow: " << name << "\n";
        for (auto step : steps) {
            if (step != nullptr) { // null check
                if (dynamic_cast<NumberInput*>(step) != nullptr) { // check if current step is a NumberInputStep
                    NumberInput* numberStep = dynamic_cast<NumberInput*>(step);
                    // perform operations specific to NumberInputStep
                    currentFlowNumberInputs.push_back(numberStep);
                }
                if (dynamic_cast<CsvFileStep*>(step) != nullptr) { // check if current step is a CsvFileStep
                    CsvFileStep* csvFileStep = dynamic_cast<CsvFileStep*>(step);
                    // perform operations specific to CsvFileStep
                    currentFlowCsvFileSteps.push_back(csvFileStep);
                }
                if (dynamic_cast<TextFileStep*>(step) != nullptr) { // check if current step is a TextFileStep
                    TextFileStep* textFileStep = dynamic_cast<TextFileStep*>(step);
                    // perform operations specific to TextFileStep
                    currentFlowTextFileSteps.push_back(textFileStep);
                }

                currentFlowSteps.push_back(step);
                step->execute();
            }
        }

        currentFlowNumberInputs.clear();
    }
};


int main() {
    std::vector<Flow*> flows;

    while (true) {
        try {
            // Initial options to create or execute a flow
            std::cout << "---------------------------\n";
            std::cout << "1. Create a new flow\n";
            std::cout << "2. Execute a flow\n";
            std::cout << "3. Exit\n";
            std::cout << "Enter your choice: ";
            std::string choice;
            getline(std::cin, choice);

            // Creating a new flow
            if (choice == "1") {

                // giving a name to the flow is forced, this cannot be skipped
                std::cout << "---------------------------\n";
                std::cout << "Enter the name of the flow: ";
                std::string name;
                getline(std::cin, name);

                Flow* flow = new Flow(name);
                

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
                    }
                    else if (stepChoice == "1") { // create and add a new TitleStep
                        Step* step = new TitleStep();
                        flow->addStep(step);
                        std::cout << "Title added successfully!\n";
                    }
                    else if (stepChoice == "2") { // create and add a new TextStep
                        Step* step = new TextStep();
                        flow->addStep(step);
                        std::cout << "Text added successfully!\n";
                    }
                    else if (stepChoice == "3") { // create and add a new TextInput
                        Step* step = new TextInput();
                        flow->addStep(step);
                        std::cout << "TextInput added successfully!\n";
                    }
                    else if (stepChoice == "4") { // create and add a new NumberInput
                        Step* step = new NumberInput();
                        flow->addStep(step);
                        std::cout << "Number added successfully!\n";
                    }
                    else if (stepChoice == "5") { // create and add a new CalculusStep
                        Step* step = new CalculusStep();
                        flow->addStep(step);
                        std::cout << "Calculus added successfully!\n";
                    }
                    else if (stepChoice == "6") { // create and add a new TextFileStep
                        Step* step = new TextFileStep();
                        flow->addStep(step);
                        std::cout << "TextFile added successfully!\n";
                    }
                    else if (stepChoice == "7") { // create and add a new CsvFileStep
                        Step* step = new CsvFileStep();
                        flow->addStep(step);
                        std::cout << "CsvFile added successfully!\n";
                    }
                    else if (stepChoice == "8") { // create and add a new DisplayStep
                        Step* step = new DisplayStep();
                        flow->addStep(step);
                        std::cout << "Display added successfully!\n";
                    }
                    else if (stepChoice == "9") { // create and add a new OutputStep
                        Step* step = new OutputStep();
                        flow->addStep(step);
                        std::cout << "Output added successfully!\n";
                    }
                    else { // insteaf of throwing an error, just display a message and ask the user to try again
                        std::cout << "Invalid choice! Please try again.\n";
                    }
                }
            }
            else if (choice == "2") {
                currentFlowNumberInputs.clear();
                // display all available flows
                std::cout << "---------------------------\n";
                std::cout << "Available flows:\n";
                for (int i = 0; i < flows.size(); i++) {
                    std::cout << i + 1 << ". " << flows[i]->getName() << "\n";
                }

                // get the user's choice
                std::cout << "\nEnter your choice: ";
                std::string flowChoice;
                getline(std::cin, flowChoice);

                int choice = stoi(flowChoice);
                if (choice >= 1 && choice <= flows.size()) {
                    // execute the flow
                    flows[choice - 1]->execute();
                }
                else {
                    // Invalid choice, go back to the initial page
                    std::cout << "Invalid Input, going back...\n";
                    continue;
                }
            }
            else if (choice == "3") {
                // exit the program
                std::cout << "Exiting...\n";
                return 0;
            }
            else {
                throw std::runtime_error("Invalid choice!");
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}