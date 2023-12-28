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

    void displayInfo() {
        std::cout << "Process Title: " << title << "\n";
        std::cout << "Process Subtitle: " << subtitle << "\n";
    }

    void execute() override {
        std::cout << "---------------------------\n";
        std::cout << "Running Title Step:\n";
        std::cout << "1. Run this step\n";
        std::cout << "2. Skip this step\n";
        std::cout << "Enter your choice: ";
        std::string choice;
        getline(std::cin, choice);

        // the user can't continue unless he either completes the step
        // or skips it
        while (true) {
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
        std::cout << "---------------------------\n";
        std::cout << "Running Text Step:\n";
        std::cout << "1. Run this step\n";
        std::cout << "2. Skip this step\n";
        std::cout << "Enter your choice: ";
        std::string choice;
        getline(std::cin, choice);
        
        // the user can't continue unless he either completes the step
        // or skips it
        while (true) {
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
        std::cout << "---------------------------\n";
        std::cout << "Running TextInput Step:\n";
        std::cout << "1. Run this step\n";
        std::cout << "2. Skip this step\n";
        std::cout << "Enter your choice: ";
        std::string choice;
        getline(std::cin, choice);

        // the user can't continue unless he either completes the step
        // or skips it
        while (true) {
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

    NumberInput(std::string description, float number) : description(description), number(number) {}
    NumberInput() : description("NO DESCRIPTION"), number(0) {}

    void displayInfo() {
        std::cout << "NumberInput Description: " << description << "\n";
        std::cout << "Number: " << number << "\n";
    }

    void execute() override {
        std::cout << "---------------------------\n";
        std::cout << "Running NumberInput Step:\n";
        std::cout << "1. Run this step\n";
        std::cout << "2. Skip this step\n";
        std::cout << "Enter your choice: ";
        std::string choice;
        getline(std::cin, choice);

        // the user can't continue unless he either completes the step
        // or skips it
        while (true) {
            if (choice == "1") {
                // Ask the user to input the description and number
                std::cout << "---------------------------\n";
                std::cout << "Description: ";
                std::string description;
                getline(std::cin, description);
                std::cout << "Number: ";
                std::string number;
                getline(std::cin, number); // get the number as a string

                // asign each of the new inputs to it's respective field
                this->description = description;
                this->number = stof(number); // convert the string to a float

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


class CalculusStep : public Step {
private:
    Step* step1, * step2;
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
    CalculusStep() : step1(nullptr), step2(nullptr), number1(0), number2(0) {}

    float getResult() {
        return result;
    }
    
    void execute() override {
        std::cout << "---------------------------\n";
        std::cout << "Running Calculus Step:\n";
        std::cout << "1. Run this step\n";
        std::cout << "2. Skip this step\n";
        std::cout << "Enter your choice: ";
        std::string choice;
        getline(std::cin, choice);

        if (choice == "1") {
            // Prompt the user to choose from existing NumberInputStep objects
            std::cout << "Choose the first number input step:\n";
            // TODO: Display a list of available NumberInputStep objects and let the user choose

            std::cout << "Choose the second number input step:\n";
            // TODO: Display a list of available NumberInputStep objects and let the user choose

            std::cout << "Choose the operation:\n";
            std::cout << "1. Addition\n";
            std::cout << "2. Subtraction\n";
            std::cout << "Enter your choice: ";
            std::string operationChoice;
            getline(std::cin, operationChoice);

            // Perform the calculation based on the user's choices
            if (operationChoice == "1") {
                // Perform addition
                // TODO: Get the numbers from the chosen NumberInputStep objects and perform the addition
            } else if (operationChoice == "2") {
                // Perform subtraction
                // TODO: Get the numbers from the chosen NumberInputStep objects and perform the subtraction
            } else {
                std::cout << "Invalid operation choice!\n";
            }
        } else if (choice == "2") {
            std::cout << "Skipping this step...\n";
        } else {
            std::cout << "Invalid choice! Please try again.\n";
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
        std::cout << "---------------------------\n";
        std::cout << "Executing flow: " << name << "\n";
        std::cout << "Available steps:\n";
        for (auto step : steps) {
            if (step != nullptr) { // null check
                step->execute();
            }
        }
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