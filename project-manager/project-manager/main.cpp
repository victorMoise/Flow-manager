#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>


// Generic Step class template
class Step {
private:
    // Stores the number of errors for each screen, no step has more than 3 screens
    int errors[3] = {0, 0, 0};
    int skips = 0; // Keeps track of the skips

protected:
    // Displays the contents of a file
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

    void addContentsFromFirstFileToSecond(std::string first, std::string second) {
        std::ifstream file(first); // Open for reading
        if (!file.is_open()) {
            std::cout << "Error opening file: " << first << "\n";
            return;
        }
        
        std::ofstream file2(second, std::ios::app); // Open for appending
        if (!file2.is_open()) {
            std::cout << "Error opening file: " << second << "\n";
            return;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            file2 << line << "\n";
        }

        file.close();
        file2.close();
    }

public:
    // Add an error at a given screen (index)
    void addErrorAtIndex(int index) {
        errors[index] += 1;
    }


    // Add a skip
    void addSkip() {
        skips += 1;
    }


    // Returns the number of errors at a given screen (index)
    int getErrorsAtIndex(int index) {
        return errors[index];
    }


    // Returns the total number of errors
    int totalErrors() {
        return errors[0] + errors[1] + errors[2];
    }


    // Returns the number of skips
    int getSkips() {
        return skips;
    }


    // Displays the number of errors for each screen
    void displayErrors() {
        for (int i = 0; i < 3; i++) {
            std::cout << "Errors on screen " << i + 1 << ": " << errors[i] << "\n";
        }
    }


    // Virtual functions overriden by the child classes
    virtual void execute() = 0;
    virtual std::string getStepName() = 0;
    virtual void displayInfoOnScreen() = 0;
    virtual void addInfoToFile(std::string name) = 0;
};


// Stores all steps of the current flow
std::vector<Step*> currentFlowSteps;


// Clears all steps of the current flow
void clearCurrentSteps();


// TitleStep class
// Title and subtitle are inputted when the object is created
class TitleStep : public Step {
private:
    std::string title = "NO TITLE";
    std::string subtitle = "NO SUBTITLE";

public:
    TitleStep(std::string title, std::string subtitle) : title(title), subtitle(subtitle) {}

    TitleStep() { // Default constructor
        std::cout << "---------------------------\n";
        std::cout << "Creating title step:\n";

        // Get the title
        std::cout << "Title: ";
        std::string title;
        getline(std::cin, title);

        // Get the subtitle
        std::cout << "Subtitle: ";
        std::string subtitle;
        getline(std::cin, subtitle);

        // Assign the input to it's respective field
        this->title = title;
        this->subtitle = subtitle;
    } 


    // Returns the title
    std::string getTitle() {
        return title;
    }


    // Returns the name of the step
    std::string getStepName() {
        return "Title Step";
    }


    // Setter for the subtitle
    std::string setSubtitle(std::string subtitle) {
        this->subtitle = subtitle;
    }


    // Setter for the title
    std::string setTitle(std::string title) {
        this->title = title;
    }


    // Displays the title and subtitle on the screen
    void displayInfoOnScreen() {
        std::cout << "Title Step -> Title: " << title << ", Subtitle: " << subtitle << "\n";
    }


    // Called inside the output step
    void addInfoToFile(std::string name) {
        std::ofstream file(name, std::ios::app); // Open the file in append mode
        if (!file.is_open()) {
            file << "Error opening file: " << name << "\n";
            return;
        }
        
        file << "---------------------------\n";
        file << "Title Step:\n";
        file << "Title: " << title << "\n";
        file << "Subtitle: " << subtitle << "\n";
        file.close();
    }


    // Main function that gets called when the step is executed
    void execute() override {
        std::string choice;

        // The user can't continue unless he either completes the step
        // or skips it
        while (true) {
            // Display available options
            std::cout << "---------------------------\n";
            std::cout << "Executing Title Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);
            if (choice == "1") { // Run the step
                // Ask the user to input the title and subtitle
                std::cout << "---------------------------\n";
                std::cout << "Running Title Step:\n";
                std::cout << "Title: " << title << "\n";
                std::cout << "Subtitle: " << subtitle << "\n";

                break; // Exit and continue to the next step
            } else if (choice == "2") { // Skip the step
                std::cout << "Skipping this Title Step...\n";
                addSkip();
                break; // Exit and continue with the next step
            } else { // Invalid choice
                std::cout << "Invalid choice! Please try again.\n";
                addErrorAtIndex(0); // Error on the first screen
            }
        }
    }
};


// TextStep class
// Both title and copy are inputted when the object is created
class TextStep : public Step {
private:
    // Couln't decide what copy was supposed to be, so it's just an input string
    std::string title;
    std::string copy;

public:
    TextStep(std::string title, std::string copy) : title(title), copy(copy) {}
    TextStep(std::string title) : title(title), copy("NO COPY") {}
    TextStep() {
        // Ask the user to input the title
        std::cout << "---------------------------\n";
        std::cout << "Creaging text step:\n";

        // Get the title
        std::cout << "Text Title: ";
        std::string title;
        getline(std::cin, title);
        
        // Get the copy (just some string text)
        std::cout << "Text Copy: ";
        std::string copy;
        getline(std::cin, copy);

        // Assign the input to it's respective field
        this->title = title;
        this->copy = copy;
    } 


    // Returns the name of the step
    std::string getStepName() {
        return "Text Step";
    }


    // Displays the title and copy on the screen
    void displayInfoOnScreen() {
        std::cout << "Text Step -> Title: " << title << ", Copy: " << copy << "\n";
    }


    // Called inside the output step
    void addInfoToFile(std::string name) {
        std::ofstream file(name, std::ios::app); // Open the file in append mode
        if (!file.is_open()) {
            file << "Error opening file: " << name << "\n";
            return;
        }
        
        file << "---------------------------\n";
        file << "Text Step:\n";
        file << "Text Title: " << title << "\n";
        file << "Text Copy: " << copy << "\n";
        file.close();
    }


    // Main function that gets called when the step is executed
    void execute() override {
        std::string choice;
        
        // The user can't continue unless he either completes the step
        // Or skips it
        while (true) {
            // Display available options
            std::cout << "---------------------------\n";
            std::cout << "Executing Text Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";

            std::cout << "Enter your choice: ";
            getline(std::cin, choice);

            if (choice == "1") { // Run the step
                // Ask the user to input the title and copy (just some text)
                std::cout << "---------------------------\n";
                std::cout << "Running Text Step:\n";
                std::cout << "Text Title: " << title << "\n";
                std::cout << "Text Copy: " << copy << "\n";

                break; // Exit and continue with the next step
            } else if (choice == "2") { // Skip the step
                std::cout << "Skipping this Text Step...\n";
                addSkip();
                break; // Exit and continue with the next step
            } else { // Invalid choice
                std::cout << "Invalid choice! Please try again.\n";
                addErrorAtIndex(0); // Error on the first screen
            }
        }
    }
};


// TextInput class
// Description is inputted when the object is created, text is inputted when the step is executed
class TextInput : public Step {
private:
    std::string description;
    std::string text;

public:
    TextInput(std::string description, std::string text) : description(description), text(text) {}
    TextInput(std::string description) : description(description), text("NO TEXT") {}
    TextInput() {
        std::cout << "---------------------------\n";
        std::cout << "Creating text input step:\n";

        // Get the description
        std::cout << "Text Input Description: ";
        std::string description;
        getline(std::cin, description);

        // Assign the input to it's respective field
        this->description = description;
    }


    // Returns the name of the step
    std::string getStepName() {
        return "Text Input Step";
    }


    // Returns the text description and text on the screen
    void displayInfoOnScreen() {
        std::cout << "Text Input Step -> Description: " << description << ", Text: " << text << "\n";
    }


    // Called inside the output step
    void addInfoToFile(std::string name) {
        std::ofstream file(name, std::ios::app); // Open the file in append mode
        if (!file.is_open()) {
            file << "Error opening file: " << name << "\n";
            return;
        }
        
        file << "---------------------------\n";
        file << "Text Input Step:\n";
        file << "Text Description: " << description << "\n";
        file << "Text Input: " << text << "\n";
        file.close();
    }


    // Main function that gets called when the step is executed
    void execute() override {
        this->text = "NO TEXT"; // Reset the text to the default value

        while (true) {
            // Display available options
            std::cout << "---------------------------\n";
            std::cout << "Executing Text Input Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            std::string choice;
            getline(std::cin, choice);

            if (choice == "1") { // Run the step
                // Ask the user to input the description and text
                std::cout << "---------------------------\n";
                std::cout << "Running Text Input Step:\n";
                std::cout << "Text Input Description: " << description << "\n";
                std::cout << "Enter your Text: ";
                std::string text;
                getline(std::cin, text);

                // Asign the new input to it's respective field
                this->text = text;

                break; // Exit and continue with the next step
            } else if (choice == "2") { // Skip the step
                std::cout << "Skipping this Text Input Step...\n";
                addSkip();
                break; // Exit and continue with the next step
            } else { // Invalid choice
                std::cout << "Invalid choice! Please try again.\n";
                addErrorAtIndex(0); // Error on the first screen
            }
        }
    }
};


template <typename T>
// NumberInput class
class NumberInput : public Step {
private:
    std::string description;
    T number;

public:
    NumberInput(std::string description, float number) : description(description), number(number) {}
    NumberInput(std::string description) : description(description), number(0) {}
    NumberInput() {
        std::cout << "---------------------------\n";
        std::cout << "Creating Number Input Step:\n";

        // Get the description
        std::cout << "Number Description: ";
        std::string description;
        getline(std::cin, description);

        // Assign the input to it's respective field
        this->description = description;
    }


    // Returns the name of the step
    std::string getStepName() {
        return "Number Input Step";
    }


    // Returns the number
    T getNumber() {
        return number;
    }


    // Returns the description
    std::string getDescription() {
        return description;
    }


    // Displays the description and number on the screen
    void displayInfoOnScreen() {
        std::cout << "Number Input Step -> Description: " << description << ", Number: " << number << "\n";
    }


    // Called inside the output step
    void addInfoToFile(std::string name) {
        std::ofstream file(name, std::ios::app); // Open the file in append mode
        if (!file.is_open()) {
            file << "Error opening file: " << name << "\n";
            return;
        }
        
        file << "---------------------------\n";
        file << "NumberInput Step:\n";
        file << "Description: " << description << "\n";
        file << "Number: " << number << "\n";
        file.close();
    }


    // Main function that gets called when the step is executed
    void execute() override {
        this->number = 0; // Reset the number to the default value

        std::string choice;

        // The user can't continue unless he either completes the step
        // Or skips it
        while (true) {
            // Display available options
            std::cout << "---------------------------\n";
            std::cout << "Executing Number Input Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);
            
            if (choice == "1") { // Run the step
                // Ask the user to input the description and number
                std::cout << "---------------------------\n";
                std::cout << "Running Number Input Step:\n";
                std::cout << "Number Description: " << description << "\n";

                bool validNumber = false;

                while (!validNumber) { // Keep asking for a number until the user enters a valid one
                    std::cout << "Enter your Number: ";
                    std::string number;
                    getline(std::cin, number); // Get the number as a string

                    try {
                        this->number = stof(number); // Convert the string to a float
                        validNumber = true;
                    } catch (const std::exception& e) {
                        std::cout << "Invalid number! Please try again.\n";
                        addErrorAtIndex(1); // Error on the second screen
                    }
                }

                break;
            } else if (choice == "2") { // Skip the step
                std::cout << "Skipping this Number Input Step...\n";
                addSkip();
                break; // Exit and continue with the next step
            } else { // Invalid choice
                std::cout << "Invalid choice! Please try again.\n";
                addErrorAtIndex(0); // Error on the first screen
            }
        }
    }
};


// Stores all NumberInputStep objects of the current flow
std::vector<NumberInput<float>*> currentFlowNumberInputs;


// CalculusStep class
class CalculusStep : public Step {
private:
    float number1, number2, result;
    std::string operation;


    // Checks if a string is a valid number
    bool isValidNumber(const std::string& str) {
        // Regular expression for a number
        std::regex pattern("^[-+]?[0-9]*\\.?[0-9]+$");

        return std::regex_match(str, pattern);
    }


    // Performs the Addition operation
    void add() {
        operation = "Addition";
        result = number1 + number2;
    }


    // Performs the Subtraction operation
    void subtract() {
        operation = "Subtraction";
        result = number1 - number2;
    }


    // Performs the Multiplication operation
    void multiply() {
        operation = "Multiplication";
        result = number1 * number2;
    }


    // Performs the Division operation
    void divide() {
        operation = "Division";
        result = number1 / number2;
    }


    // Performs the Min operation
    void min() {
        operation = "Min";
        result = number1 < number2 ? number1 : number2;
    }


    // Performs the Max operation
    void max() {
        operation = "Max";
        result = number1 > number2 ? number1 : number2;
    }

public:
    CalculusStep() : number1(0), number2(0), result(0) {} // Default constructor


    // Returns the name of the step
    std::string getStepName() {
        return "Calculus Step";
    }


    // Returns the result of the operation
    float getResult() {
        return result;
    }


    // Displays the numbers and result on the screen
    void displayInfoOnScreen() {
        std::cout << "Calculus Step -> Number 1: " << number1 << ", Number 2: " << number2 << ", Operation: " << operation << ", Result: " << result << "\n";
    }


    // Called inside the output step
    void addInfoToFile(std::string name) {
        std::ofstream file(name, std::ios::app); // Open the file in append mode
        if (!file.is_open()) {
            file << "Error opening file: " << name << "\n";
            return;
        }
        
        file << "---------------------------\n";
        file << "Calculus Step:\n";
        file << "Number 1: " << number1 << "\n";
        file << "Number 2: " << number2 << "\n";
        file << "Operation: " << operation << "\n";
        file << "Result: " << result << "\n";
        file.close();
    }


    // Main function that gets called when the step is executed
    void execute() override {
        bool stepDone = false;

        while (true) {
            // Display available options
            std::cout << "---------------------------\n";
            std::cout << "Executing Calculus Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";
            std::cout << "Enter your choice: ";
            std::string choice;
            getline(std::cin, choice);

            // If the user ran the step, he can't skip it unless he finishes it
            if (choice == "1") { // Run the step
                int chosenNumberInputIndex1 = -1; // The index of the first NumberInputStep object
                
                // Keep asking to choose a NumberInputStep until the user enters a valid one
                while (chosenNumberInputIndex1 < 0 || chosenNumberInputIndex1 >= currentFlowNumberInputs.size()) {
                    std::cout << "---------------------------\n";
                    std::cout << "Running Calculus Step:\n";
                    std::cout << "Choose the first number input step:\n";

                    // Display a list of available NumberInputStep objects and let the user choose
                    for (int i = 0; i < currentFlowNumberInputs.size(); i++) {
                        std::cout << i + 1 << ". " << currentFlowNumberInputs[i]->getNumber() << " (" << currentFlowNumberInputs[i]->getDescription() << ")" << "\n";
                    }

                    // Get the user's choice
                    std::cout << "Enter your choice: ";
                    std::string chosenNumberInput1Str;
                    getline(std::cin, chosenNumberInput1Str);

                    // Verify that the user entered a valid number and within acceptable range 
                    if (isValidNumber(chosenNumberInput1Str)) {
                        chosenNumberInputIndex1 = std::stoi(chosenNumberInput1Str) - 1;
                        if (chosenNumberInputIndex1 < 0 || chosenNumberInputIndex1 >= currentFlowNumberInputs.size()) {
                            std::cout << "Invalid choice! Please try again.\n";
                            addErrorAtIndex(1); // Error on the second screen
                        }
                    }
                    else { // The user didn't enter a valid number
                        std::cout << "Invalid choice! Please enter a number.\n";
                        addErrorAtIndex(1); // Error on the second screen
                    }
                }

                int chosenNumberInputIndex2 = -1; // The index of the second NumberInputStep object
                while (chosenNumberInputIndex2 < 0 || chosenNumberInputIndex2 >= currentFlowNumberInputs.size()) {
                    std::cout << "---------------------------\n";
                    std::cout << "Running Calculus Step:\n";
                    std::cout << "Choose the second number input step:\n";

                    // Display a list of available NumberInputStep objects and let the user choose
                    for (int i = 0; i < currentFlowNumberInputs.size(); i++) {
                        std::cout << i + 1 << ". " << currentFlowNumberInputs[i]->getNumber() << " (" << currentFlowNumberInputs[i]->getDescription() << ")" << "\n";
                    }

                    // Get the user's choice
                    std::cout << "Enter your choice: ";
                    std::string chosenNumberInput2Str;
                    getline(std::cin, chosenNumberInput2Str);

                    // Verify that the user entered a valid number and within acceptable range
                    if (isValidNumber(chosenNumberInput2Str)) {
                        chosenNumberInputIndex2 = std::stoi(chosenNumberInput2Str) - 1;
                        if (chosenNumberInputIndex2 < 0 || chosenNumberInputIndex2 >= currentFlowNumberInputs.size()) {
                            std::cout << "Invalid choice! Please try again.\n";
                            addErrorAtIndex(1); // Error on the second screen
                        }
                    }
                    else { // The user didn't enter a valid number
                        std::cout << "Invalid choice! Please enter a number.\n";
                        addErrorAtIndex(1); // Error on the second screen
                    }
                }

                // Get the numbers from the chosen NumberInputStep objects
                number1 = currentFlowNumberInputs[chosenNumberInputIndex1]->getNumber();
                number2 = currentFlowNumberInputs[chosenNumberInputIndex2]->getNumber();

                // Ask the user to choose an operation, can't be skipped
                while (true) {
                    // Display available options
                    std::cout << "---------------------------\n";
                    std::cout << "Running Calculus Step:\n";
                    std::cout << "Choose the operation:\n";
                    std::cout << "1. Addition\n";
                    std::cout << "2. Subtraction\n";
                    std::cout << "3. Multiplication\n";
                    std::cout << "4. Division\n";
                    std::cout << "5. Min\n";
                    std::cout << "6. Max\n";

                    // Get the user's choice
                    // Can be the number coresponding to each operation or the operation symbol
                    std::cout << "Enter your choice: ";
                    std::string operationChoice;
                    getline(std::cin, operationChoice);

                    // Perform the calculation based on the user's choices
                    if (operationChoice == "1" || operationChoice == "+") { // Addition
                        add();
                        std::cout << "Result of " << number1 << " + " << number2 << " = " << result << "\n";
                        return; // Exit and continue with the next step
                    } else if (operationChoice == "2" || operationChoice == "-") { // Subtraction
                        subtract();
                        std::cout << "Result of " << number1 << " - " << number2 << " = " << result << "\n";
                        return; // Exit and continue with the next step
                    } else if (operationChoice == "3" || operationChoice == "*") { // Multiplication
                        multiply();
                        std::cout << "Result of " << number1 << " * " << number2 << " = " << result << "\n";
                        return; // Exit and continue with the next step
                    } else if (operationChoice == "4" || operationChoice == "/") { // Division
                        divide();
                        std::cout << "Result of " << number1 << " / " << number2 << " = " << result << "\n";
                        return; // Exit and continue with the next step
                    } else if (operationChoice == "5") { // Min
                        min();
                        std::cout << "Result of min(" << number1 << ", " << number2 << ") = " << result << "\n";
                        return; // Exit and continue with the next step
                    } else if (operationChoice == "6") { // Max
                        max();
                        std::cout << "Result of max(" << number1 << ", " << number2 << ") = " << result << "\n";
                        return; // Exit and continue with the next step
                    } else {
                        std::cout << "Invalid operation choice!\n";
                        addErrorAtIndex(2); // Error on the third screen
                    }
                }
            } else if (choice == "2") { // Skip the step
                std::cout << "Skipping this Calculus Step...\n";
                addSkip();
                return;
            } else { // Invalid choice
                std::cout << "Invalid choice! Please try again.\n";
                addErrorAtIndex(0); // Error on the first screen
            }
        }   
    }
};


// Stores all CalculusStep objects of the current flow
std::vector<CalculusStep*> currentFlowCalculusSteps;


// TextFileStep class
class TextFileStep : public Step {
private:
    std::string description;
    std::string name = "NOFILE"; // Default value
    std::ifstream file;

public:
    TextFileStep() {
        std::cout << "---------------------------\n";
        std::cout << "Creating Text File Step:\n";

        // Get the description
        std::cout << "Text File Description: ";
        std::string description;
        getline(std::cin, description);

        // Assign the input to it's respective field
        this->description = description;
    }


    TextFileStep(std::string description, std::string name) : description(description), name(name + ".txt") {
        try {
            file.open(this->name);
            if (!file) {
                throw std::runtime_error("File not found!");
            }
        } catch (const std::exception& e) { // Throw an error if the file does not exist
            std::cout << "Error: " << e.what() << std::endl;
        }
    }


    // Returns the name of the step
    std::string getStepName() {
        return "File Input Step";
    }


    // Returns the name of the file
    std::string getName() {
        return name;
    }


    // Displays the name of the stored file
    void displayInfoOnScreen() {
        std::cout << "TextFile Step -> Description: " << description << ", Name: " << name << "\n";
    }


    // Called inside the output step, adds the info to the file
    void addInfoToFile(std::string name) {
        std::ofstream file(name, std::ios::app); // Open the file in append mode
        if (!file.is_open()) {
            file << "Error opening file: " << name << "\n";
            return;
        }
        
        file << "---------------------------\n";
        file << "TextFile Step:\n";
        file << "Text File Description: " << this->description << "\n";
        file << "File Name: " << this->name << "\n";
        file << "Contents:\n";
        file.close();

        addContentsFromFirstFileToSecond(this->name, name);
    }


    // Main function that gets called when the step is executed
    void execute() override {
        std::string choice = "0";

        while (choice != "1" || choice != "2") {
            // Display available options
            std::cout << "---------------------------\n";
            std::cout << "Executing Text File Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";

            // Get the user's choice
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);

            std::string filename;

            if (choice == "1") { // Run the step
                while (true) {
                    std::cout << "---------------------------\n";
                    std::cout << "Running Text File Step:\n";
                    std::cout << "File description: " << description << "\n";

                    std::cout << "Enter File Name: ";
                    std::string filename;
                    getline(std::cin, filename);

                    if (!fopen((filename + ".txt").c_str(), "r")) { // Check if the file exists
                        std::cout << "File not found! Please try again.\n";
                        addErrorAtIndex(1); // Error on the second screen
                    } else {
                        this->name = filename + ".txt";
                        break;
                    }
                }

                return; // Exit and continue with the next step
            } else if (choice == "2") { // Skip the step 
                std::cout << "Skipping this step...\n";
                addSkip();
                break; // Exit and continue with the next step
            } else { // Invalid choice
                std::cout << "Invalid choice! Please try again.\n";
                addErrorAtIndex(0); // Error on the first screen
            }
        }
    }
};


// Stores all TextFileStep objects of the current flow
std::vector<TextFileStep*> currentFlowTextFileSteps;


// CsvFileStep class
class CsvFileStep : public Step {
private:
    std::string description;
    std::string name = "NOFILE"; // Default value
    std::ifstream file;

public:
    // Default constructor is called when creating the flow
    CsvFileStep() {
        std::cout << "---------------------------\n";
        std::cout << "Creating Csv File Step:\n";

        // Get the description
        std::cout << "Csv File Description: ";
        std::string description;
        getline(std::cin, description);

        // Assign the input to it's respective field
        this->description = description;
    }


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


    // Returns the name of the step
    std::string getStepName() {
        return "Csv File Step";
    }


    // Returns the name of the file
    std::string getName() {
        return name;
    }


    // Displays the name of the stored file
    void displayInfoOnScreen() {
        std::cout << "CsvFile Step -> Description: " << description << ", Name: " << name << "\n";
    }


    // Called inside the output step, adds the info to the file
    void addInfoToFile(std::string name) {
        std::ofstream file(name, std::ios::app); // Open the file in append mode

        if (!file.is_open()) {
            file << "Error opening file: " << name << "\n";
            return;
        }
        
        file << "---------------------------\n";
        file << "CsvFile Step:\n";
        file << "Description: " << description << "\n";
        file << "Name: " << name << "\n";
        file << "Contents:\n";
        addContentsFromFirstFileToSecond(this->name, name); // Add the contents of the csv file to the output file
        file.close();
    }


    // Main function that gets called when the step is executed
    void execute() override {
        std::string choice = "0";
        while (choice != "1" || choice != "2") {
            // Display available options
            std::cout << "---------------------------\n";
            std::cout << "Running CsvFile Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";

            // Get the user's choice
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);

            if (choice == "1") { // Run the step
                while (true) {
                    std::cout << "---------------------------\n";
                    std::cout << "Running CsvFile Step:\n";
                    std::cout << "File description: " << description << "\n";

                    std::cout << "Enter File Name: ";
                    std::string filename;
                    getline(std::cin, filename);

                    if (!fopen((filename + ".csv").c_str(), "r")) { // Check if the file exists
                        std::cout << "File not found! Please try again.\n";
                        addErrorAtIndex(1); // Error on the second screen
                    } else {
                        this->name = filename + ".csv";
                        break;
                    }
                }

                return; // Exit and continue with the next step
            } else if (choice == "2") {
                std::cout << "Skipping this step...\n";
                addSkip();
                break; // Exit and continue with the next step
            } else { // Invalid choice
                std::cout << "Invalid choice! Please try again.\n";
                addErrorAtIndex(0); // Error on the first screen
            }
        }
    }
};


// Stores all CsvFileStep objects of the current flow
std::vector<CsvFileStep*> currentFlowCsvFileSteps;


// DisplayStep class
class DisplayStep : public Step {
private:
    std::string filename;

public:
    DisplayStep(std::string filename) : filename(filename) {}
    DisplayStep() : filename("NOFILE") {} // Default constructor


    // Returns the name of the step
    std::string getStepName() {
        return "Display Step";
    }


    // Displays the name of the stored file
    void displayInfoOnScreen() {
        std::cout << "Display Step -> Filename: " << filename << "\n";
    }


    // Didnt really need this, it just had to be defined
    void addInfoToFile(std::string name) {
        return;
    }


    // Main function that gets called when the step is executed
    void execute() override {
        while (true) {
            // Display available options
            std::cout << "---------------------------\n";
            std::cout << "Running Display Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";

            // Get the user's choice
            std::cout << "Enter your choice: ";
            std::string choice;
            getline(std::cin, choice);

            if (choice == "1") { // Run the step
                while (true) {
                    // Display all available text and csv files
                    std::cout << "---------------------------\n";
                    std::cout << "Display the contents of which file:\n";

                    // Display a list of available TextFileStep objects and let the user choose
                    std::cout << "Text files:\n";
                    for (int i = 0; i < currentFlowTextFileSteps.size(); i++) {
                        std::cout << i + 1 << ". " << currentFlowTextFileSteps[i]->getName() << "\n";
                    }

                    // Display a list of available CsvFileStep objects and let the user choose
                    std::cout << "Csv files:\n";
                    for (int i = 0; i < currentFlowCsvFileSteps.size(); i++) {
                        std::cout << i + 1 + currentFlowTextFileSteps.size() << ". " << currentFlowCsvFileSteps[i]->getName() << "\n";
                    }

                    // Get the user's choice
                    std::cout << "Enter your choice: ";
                    std::string fileChoice;
                    getline(std::cin, fileChoice);

                    // Verify that the user entered a valid number and within acceptable range
                    if (std::stoi(fileChoice) >= 1 && std::stoi(fileChoice) <= currentFlowTextFileSteps.size()) {
                        // First if is for text files
                        displayContentsOfFile(currentFlowTextFileSteps[std::stoi(fileChoice) - 1]->getName());
                        return; // Exit and continue with the next step
                    } else if (std::stoi(fileChoice) >= currentFlowTextFileSteps.size() + 1 && std::stoi(fileChoice) <= currentFlowTextFileSteps.size() + currentFlowCsvFileSteps.size()) {
                        // This if is for csv files
                        displayContentsOfFile(currentFlowCsvFileSteps[std::stoi(fileChoice) - currentFlowTextFileSteps.size() - 1]->getName());
                        return; // Exit and continue with the next step
                    } else { // Invalid choice
                        std::cout << "Invalid choice! Please try again.\n";
                        addErrorAtIndex(1); // Error on the second screen
                    }
                }
            } else if (choice == "2") { // Skip the step
                std::cout << "Skipping this step...\n";
                addSkip();
                break;
            } else { // Invalid choice
                std::cout << "Invalid choice! Please try again.\n";
                addErrorAtIndex(0); // Error on the first screen
            }
        }
    }
};


class OutputStep : public Step {
private:
    std::string title;
    std::string description;
    std::string previousInfo;
    
    void displayContentsOfFile(std::string name, std::string file) {
        std::ifstream inputFile(name);
        std::ofstream outputFile(file, std::ios::app); // Open file in append mode

        if (!inputFile.is_open()) { // Check if the file was opened successfully
            outputFile << "Error opening file: " << name << "\n";
            return;
        }

        if (!outputFile.is_open()) { // Check if the file was opened successfully
            outputFile << "Error creating/opening file: " << file << "\n";
            return;
        }

        // Display the contents of the file line by line
        std::string line;
        while (std::getline(inputFile, line)) {
            outputFile << line << "\n";
        }

        // Close both files
        inputFile.close();
        outputFile.close();
    }

public:
    OutputStep(std::string title, std::string description, std::string previousInfo) : title(title), description(description), previousInfo(previousInfo) {}
    OutputStep() : title("NO TITLE"), description("NO DESCRIPTION"), previousInfo("NO PREVIOUS INFO") {} // Default constructor


    // Returns the name of the step
    std::string getStepName() {
        return "Output Step";
    }


    // Don't really need this
    void displayInfoOnScreen() {
        return;
    }


    // Don't really need this
    void addInfoToFile(std::string name) {
        return;
    }


    // Adds the description to the output file
    void AddDescriptionToFile(std::string name) {
        std::ofstream file(name, std::ios::app); // Open the file in append mode
        if (!file.is_open()) {
            file << "Error opening file: " << name << "\n";
            return;
        }
        
        file << this->description;
        file.close();
    }


    // Main function that gets called when the step is executed
    void execute() override {
        std::string choice;
        while (true) {
            // Display available options
            std::cout << "---------------------------\n";
            std::cout << "Running Output Step:\n";
            std::cout << "1. Run this step\n";
            std::cout << "2. Skip this step\n";

            // Get the user's choice
            std::cout << "Enter your choice: ";
            getline(std::cin, choice);

            if (choice == "1") { // Run the step
                std::cout << "---------------------------\n";

                // Ask for the name of the output file that should be created
                std::cout << "Enter the title of the output: ";
                getline(std::cin, title);

                // Ask for the description of the output file
                std::cout << "Enter the description of the output: ";
                getline(std::cin, description);

                // Set the class member to the respective value
                this->description = description + "\n";

                // Add the description to the output file
                AddDescriptionToFile(title + ".txt"); 

                std::string prevChoice = "0";

                // User is asked to add information from previous steps until he choses "n" or "N"
                while (prevChoice != "y" || prevChoice != "Y" || prevChoice != "n" || prevChoice != "N") {
                    // Prompt the user to add info from a previous step
                    std::cout << "---------------------------\n";
                    std::cout << "Do you want to display a previous step's info? (y/n): ";
                    getline(std::cin, prevChoice);

                    // Add info from a previous step
                    if (prevChoice == "y" || prevChoice == "Y") {
                        std::cout << "---------------------------\n";
                        std::cout << "Which step do you want to add?\n";

                        // Display a list of available TextFileStep objects and let the user choose
                        for (int i = 0; i < currentFlowSteps.size() - 1; i++) {
                            std::cout << i + 1 << ". ";
                            currentFlowSteps[i]->displayInfoOnScreen();
                        }

                        // Get the user's choice
                        std::cout << "\nEnter your choice: ";
                        std::string stepChoice;
                        getline(std::cin, stepChoice);

                        try {
                            // Verify that the user entered a valid number and within acceptable range
                            if (stoi(stepChoice) >= 1 && stoi(stepChoice) <= currentFlowSteps.size()) { 
                                // Add the info from the chosen step to the output file
                                currentFlowSteps[stoi(stepChoice) - 1]->addInfoToFile(title + ".txt");
                            } else { // Invalid choice
                                std::cout << "Invalid choice! Please try again.\n";
                                addErrorAtIndex(2); // Error on the second screen
                            }
                        } catch (const std::exception& e) {
                            std::cout << "Invalid choice! Please try again.\n";
                            addErrorAtIndex(2); // Error on the second screen
                        }
                    } else if (prevChoice == "n" || prevChoice == "N") { // The user chose not to add any more info
                        return;
                    } else { // Invalid choice
                        std::cout << "Invalid choice! Please try again.\n";
                        addErrorAtIndex(1); // Error on the second screen
                    }
                }
            } else if (choice == "2") {
                std::cout << "Skipping this step...\n";
                addSkip();
                break;
            } else {
                std::cout << "Invalid choice! Please try again.\n";
                addErrorAtIndex(0); // Error on the first screen
            }
        }
    }
};


// Flow class
class Flow {
private:
    int started = 0; // Number of times the flow was started
    std::vector<Step*> steps; // Stores all steps of the flow
    std::string name; // Name of the flow
    std::string createdDate; // Date and time when the flow was created

public:
    Flow(std::string name) : name(name) { // Constructor
        // Set the createdDate to the current date and time
        std::time_t now = std::time(nullptr);
        createdDate = std::asctime(std::localtime(&now));
    }


    // Returns the number of times the flow was started
    int getStarted() {
        return started;
    }


    // Returns the steps of the flow
    std::vector<Step*> getStep() {
        return steps;
    }


    // Returns the name of the flow
    std::string getName() {
        return name;
    }


    // Returns the date and time when the flow was created
    std::string getCreatedDate() {
        return createdDate;
    }


    // If a flow is started it cannot be skipped
    // So the number of times the flow is started is the number of times it was completed
    void addStart() {
        started++;
    }


    // Adds a step to the flow
    void addStep(Step* step) {
        steps.push_back(step);
    }


    // Displays the skips for each step
    void displaySkips() {
        std::cout << "---------------------------\n";
        std::cout << "Skips for each step:\n";

        // Loop through all steps of the flow
        for (size_t i = 0; i < steps.size(); i++) {
            // Display the name of the step and the number of times it was skipped
            std::cout << "Step " << i + 1 << ", " << steps[i]->getStepName() << ": Skipped = " << steps[i]->getSkips() << "\n";
        }
    }


    // Displays the errors for each step on each screen
    void displayErrors() {
        std::cout << "---------------------------\n";
        std::cout << "Errors for each step:\n";
        
        for (size_t i = 0; i < steps.size(); i++) {
            // Displays the name of the step and the number of times it was skipped
            std::cout << "Step " << i + 1 << ", " << steps[i]->getStepName() << ":\n";
            steps[i]->displayErrors();
        }
    }


    // Displays starts and completes
    void displayStartAndCompletes() {
        std::cout << "---------------------------\n";
        std::cout << "Started: " << started << "\n";
        std::cout << "Completed: " << started << "\n";
    }


    // Displays the average errors for each flow
    void displayAverageErrors() {
        int allErrors = 0; // Count all errors from each step
        for (auto step : steps) {
            allErrors += step->totalErrors();
        }

        // Display the average errors per flow started
        std::cout << "---------------------------\n";
        std::cout << "Average errors per flow: " << allErrors / steps.size() / started << "\n";
    }

    
    // Executes all steps of the flow
    void execute() {
        clearCurrentSteps(); // Clears all previous stored teps
        std::cout << "---------------------------\n";
        std::cout << "Executing flow: " << name << "\n";

        // Loop through all steps of the flow
        for (auto step : steps) {
            if (step != nullptr) { // null check
                if (dynamic_cast<NumberInput<float>*>(step) != nullptr) { // Check if current step is a NumberInputStep
                    NumberInput<float>* numberStep = dynamic_cast<NumberInput<float>*>(step);
                    // Add the step to the list of NumberInputStep objects
                    currentFlowNumberInputs.push_back(numberStep);
                }

                if (dynamic_cast<CsvFileStep*>(step) != nullptr) { // Check if current step is a CsvFileStep
                    CsvFileStep* csvFileStep = dynamic_cast<CsvFileStep*>(step);
                    // Add the step to the list of CsvFileStep objects
                    currentFlowCsvFileSteps.push_back(csvFileStep);
                }

                if (dynamic_cast<TextFileStep*>(step) != nullptr) { // Check if current step is a TextFileStep
                    TextFileStep* textFileStep = dynamic_cast<TextFileStep*>(step);
                    // Add the step to the list of TextFileStep objects
                    currentFlowTextFileSteps.push_back(textFileStep);
                }

                if (dynamic_cast<CalculusStep*>(step) != nullptr) { // Check if current step is a CalculusStep
                    CalculusStep* calculusStep = dynamic_cast<CalculusStep*>(step);
                    // Add the step to the list of CalculusStep objects
                    currentFlowCalculusSteps.push_back(calculusStep);
                }

                // Add the step to the list of all steps and execute it
                currentFlowSteps.push_back(step);
                step->execute();
            }
        }

        // Display a confirmation that the flow was executed
        std::cout << "---------------------------\n";
        std::cout << "---------------------------\n";
        std::cout << "Flow execution is done!\n";
        std::cout << "Going back to the start page.\n";
        
        // To be sure the previous steps are cleared, I clear it again
        currentFlowNumberInputs.clear();
    }
};


// Clears all previous stored steps
void clearCurrentSteps() {
    currentFlowSteps.clear();
    currentFlowNumberInputs.clear();
    currentFlowCsvFileSteps.clear();
    currentFlowTextFileSteps.clear();
    currentFlowCalculusSteps.clear();
}


int main() {
    std::vector<Flow*> flows; // Stores all the flows

    while (true) {
        try {
            // Initial options to create or execute a flow
            std::cout << "---------------------------\n";
            std::cout << "---------------------------\n";
            std::cout << "1. Create a new flow\n";
            std::cout << "2. Execute a flow\n";
            std::cout << "3. Delete a flow\n";
            std::cout << "4. See flow analytics\n";
            std::cout << "5. Exit\n";
            std::cout << "Enter your choice: ";
            std::string choice;
            getline(std::cin, choice);

            // Creating a new flow
            if (choice == "1") {

                // Fiving a name to the flow is forced, this cannot be skipped
                std::cout << "---------------------------\n";
                std::cout << "Enter the name of the flow: ";
                std::string name;
                getline(std::cin, name);

                Flow* flow = new Flow(name);
                
                while (true) {
                    // Display all available steps
                    std::cout << "---------------------------\n";
                    std::cout << "Available steps:\n";
                    std::cout << "1. Title: title (string), subtitle (string)\n";
                    std::cout << "2. Text: title (string), copy (string)\n";
                    std::cout << "3. TextInput: description (string), text input (string)\n";
                    std::cout << "4. NumberInput: description (string), number input (string)\n";
                    std::cout << "5. Calculus: steps (integer), operation (string)\n";
                    std::cout << "6. TextFile: description(string), filename(string)\n";
                    std::cout << "7. CsvFile: description(string), filename(string)\n";
                    std::cout << "8. Display: step (intger)\n";
                    std::cout << "9. Output: step(integer), filename(string), title (string), description (string)\n";
                    std::cout << "0. End\n";
                    std::cout << "Enter your choice: ";

                    // Get the user's choice
                    std::string stepChoice;
                    getline(std::cin, stepChoice);

                    if (stepChoice == "0") { // Add the flow to the list of flows and exit the loop
                        // This is basically the end step, didn't need one specifically, so when the user adds the end step
                        // The execution of the flow just stops
                        flows.push_back(flow);
                        break; // Creating the flow is done, go back to the initial page

                    } else if (stepChoice == "1") { // Create and add a new TitleStep
                        // Create the step and add it to the flow
                        Step* step = new TitleStep();
                        flow->addStep(step);
                        std::cout << "Title added successfully!\n";
                    } else if (stepChoice == "2") { // Create and add a new TextStep
                        Step* step = new TextStep();
                        flow->addStep(step);
                        std::cout << "Text added successfully!\n";
                    } else if (stepChoice == "3") { // Create and add a new TextInput
                        Step* step = new TextInput();
                        flow->addStep(step);
                        std::cout << "TextInput added successfully!\n";
                    } else if (stepChoice == "4") { // Create and add a new NumberInput
                        Step* step = new NumberInput<float>();
                        flow->addStep(step);
                        std::cout << "Number added successfully!\n";
                    } else if (stepChoice == "5") { // Create and add a new CalculusStep
                        Step* step = new CalculusStep();
                        flow->addStep(step);
                        std::cout << "Calculus added successfully!\n";
                    } else if (stepChoice == "6") { // Create and add a new TextFileStep
                        Step* step = new TextFileStep();
                        flow->addStep(step);
                        std::cout << "TextFile added successfully!\n";
                    } else if (stepChoice == "7") { // Create and add a new CsvFileStep
                        Step* step = new CsvFileStep();
                        flow->addStep(step);
                        std::cout << "CsvFile added successfully!\n";
                    } else if (stepChoice == "8") { // Create and add a new DisplayStep
                        Step* step = new DisplayStep();
                        flow->addStep(step);
                        std::cout << "Display added successfully!\n";
                    } else if (stepChoice == "9") { // Create and add a new OutputStep
                        Step* step = new OutputStep();
                        flow->addStep(step);
                        std::cout << "Output added successfully!\n";
                    } else { // Insteaf of throwing an error, just display a message and ask the user to try again
                        std::cout << "Invalid choice! Please try again.\n";
                    }
                }
            } else if (choice == "2") { // Execute a flow
                currentFlowNumberInputs.clear();
                // Display all available flows
                std::cout << "---------------------------\n";
                std::cout << "Available flows:\n";

                // Display all available flows
                for (int i = 0; i < flows.size(); i++) {
                    std::cout << i + 1 << ". " << flows[i]->getName() << ", Created: " << flows[i]->getCreatedDate();
                }

                // Get the user's choice
                std::cout << "\nEnter your choice: ";
                std::string flowChoice;
                getline(std::cin, flowChoice);

                // Transform the input into an integer
                try {
                    int choice = stoi(flowChoice);
                    if (choice >= 1 && choice <= flows.size()) {
                        // Execute the flow
                        flows[choice - 1]->addStart();
                        flows[choice - 1]->execute();
                        clearCurrentSteps();
                    } else { 
                        // Invalid choice, go back to the initial page
                        throw std::runtime_error("Invalid Input");
                    }
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << ", going back...\n";
                    continue;
                }
            } else if (choice == "3") { // Delete a flow
                std::cout << "---------------------------\n";
                std::cout << "Available flows:\n";

                // Display all available flows
                for (int i = 0; i < flows.size(); i++) {
                    std::cout << i + 1 << ". " << flows[i]->getName() << "\n";
                }

                // Get the user's choice
                std::cout << "\nEnter your choice: ";
                std::string flowChoice;
                getline(std::cin, flowChoice);

                // Transform the input into an integer
                try {
                    int choice = stoi(flowChoice);
                    if (choice >= 1 && choice <= flows.size()) {
                        // Delete the flow and show the success message
                        flows.erase(flows.begin() + choice - 1);
                        std::cout << "Flow " << flows[choice - 1]->getName() << " deleted successfully!\n";
                    } else {
                        // Invalid choice, go back to the initial page
                        std::cout << "Invalid Input, going back...\n";
                        continue;
                    }
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << ", going back...\n";
                    continue;
                }
            } else if (choice == "4") { // See flow analytics
                std::cout << "---------------------------\n";
                std::cout << "Available flows:\n";

                // Display all available flows
                for (int i = 0; i < flows.size(); i++) {
                    std::cout << i + 1 << ". " << flows[i]->getName() << "\n";
                }

                // Get the user's choice
                std::cout << "\nEnter your choice: ";
                std::string flowChoice;
                getline(std::cin, flowChoice);

                // Transform the input into an integer
                try {
                    int choice = stoi(flowChoice);
                    if (choice >= 1 && choice <= flows.size()) {
                        // Display starts and completes counters
                        flows[choice - 1]->displayStartAndCompletes();

                        // Display skips for each step
                        flows[choice - 1]->displaySkips();

                        // Display errors for each step
                        flows[choice - 1]->displayErrors();

                        // Display average errors for each flow
                        flows[choice - 1]->displayAverageErrors();
                    } else {
                        // Invalid choice, go back to the initial page
                        std::cout << "Invalid Input, going back...\n";
                        continue;
                    }
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << ", going back...\n";
                    continue;
                }
            } else if (choice == "5") {
                // Exit the program
                std::cout << "---------------------------\n";
                std::cout << "Exiting...\n";
                return 0;
            } else {
                throw std::runtime_error("Invalid choice!");
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}