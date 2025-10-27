/*
 * CS-210 Project Three: Corner Grocer
 * Tristan Ponte
 */

#include <iostream>  // For console input/output (cin, cout)
#include <fstream>   // For file input/output (ifstream, ofstream)
#include <string>    // For using the string data type
#include <map>       // For using the map data structure to store frequencies
#include <iomanip>   // For formatting output (setw)
#include <limits>    // For input validation (numeric_limits)

using namespace std;

/**
 * @class GrocerTracker
 * @brief Manages the grocery item frequency tracking and user interaction.
 *
 * This class provides all functionality required...
 * - Readsthe input file, writes the frequency data file, displays the menu and handling user input, and then executing menu options.
 */
class GrocerTracker {
private:
    // A map to store the frequency of each item.
    // The key is the item name (string), and the value is its count (int)...
    map<string, int> itemFrequencies;

    const string INPUT_FILE_NAME = "CS210_Project_Three_Input_File.txt";
    const string OUTPUT_FILE_NAME = "frequency.dat";

    /**
     * @brief Reads the input file and populates the itemFrequencies map
     * @return true if the file was read successfully and then false otherwise
     */
    bool readInputFile() {
        ifstream inFile(INPUT_FILE_NAME);
        string item;

        // Checks if the file was successfully opened...
        if (!inFile.is_open()) {
            cout << "Error: Could not open input file " << INPUT_FILE_NAME << endl;
            return false;
        }

        // Reads the file word by word
        while (inFile >> item) {
            // Increment the count for this item in the map.
            // If the item isn't in the map yet then it's automatically added with a count of 1
            itemFrequencies[item]++;
        }

        inFile.close();
        return true;
    }

    /**
     * @brief Writes the accumulated frequency data to frequency.dat
     * @return true if the file was written successfully also then false otherwise.
     */
    bool writeFrequencyData() {
        ofstream outFile(OUTPUT_FILE_NAME);

        // Check if the file successfully opened
        if (!outFile.is_open()) {
            cout << "Error: Could not create output file " << OUTPUT_FILE_NAME << endl;
            return false;
        }

        // Iterates through the map and write each pair to the file.
        // 'const auto&' is an efficient way to loop without copying data
        for (const auto& pair : itemFrequencies) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close();
        cout << "Backup data created in " << OUTPUT_FILE_NAME << endl;
        return true;
    }

    /**
     * @brief Displays the main menu options to the user.
     */
    void displayMenu() {
        cout << "\n=============================================" << endl;
        cout << " Corner Grocer Item Tracking Menu" << endl;
        cout << "=============================================" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Print all item frequencies" << endl;
        cout << "3. Print all item histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Enter your choice (1-4): ";
    }

    /**
     * @brief Option 1: Prompts user for an item and prints its frequency.
     */
    void executeOptionOne() {
        string searchItem;
        cout << "Enter the item you wish to search for: ";
        cin >> searchItem;

        // The map::count() function returns 1 if the key exists and 0 if not
        if (itemFrequencies.count(searchItem)) {
            // Use .at() to safely access the value
            cout << "Frequency of " << searchItem << ": " << itemFrequencies.at(searchItem) << endl;
        } else {
            cout << "Item '" << searchItem << "' not found." << endl;
        }
    }

    /**
     * @brief Option 2: Prints a numeric list of all items and their frequencies.
     */
    void executeOptionTwo() {
        cout << "\n--- All Item Frequencies ---" << endl;
        for (const auto& pair : itemFrequencies) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    /**
     * @brief Option 3: Prints a text-based histogram of all items.
     */
    void executeOptionThree() {
        cout << "\n--- All Item Histogram ---" << endl;
        for (const auto& pair : itemFrequencies) {
            // setw(14) sets a fixed width for the item name for clean alignment
            // 'left' makes it left justified...
            cout << left << setw(14) << pair.first << " ";
            
            // Print a '*' for each count
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    /**
     * @brief Gets and validates the user's menu choice.
     * @return A valid integer choice (1-4).
     */
    int getValidatedInput() {
        int choice = 0;
        
        // Loop until a valid choice is entered
        while (true) {
            displayMenu();
            cin >> choice;

            // Check if the input was not an integer
            if (cin.fail()) {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear(); // Clear the error flag
                // Ignore the rest of the bad input line
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            } 
            // Check if the integer was out of the valid range
            else if (choice < 1 || choice > 4) {
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            } 
            // Input is valid
            else {
                break; // Exit the validation loop
            }
        }
        return choice;
    }

public:
    /**
     * @brief Public method to run the main application loop
     */
    void run() {
        // Initial setup: Read input and create backup file
        // If reading fails can't proceed
        if (!readInputFile()) {
            return; // Exit if input file couldn't be read
        }
        
        // Writing the data file is a requirement, but it can
        // continue even if it fails as the data is in memory.
        writeFrequencyData(); 

        int menuChoice = 0;

        // Main menu loop it continues until user selects 4 which will then close out the program and print a final message to the console
        while (menuChoice != 4) {
            menuChoice = getValidatedInput();

            switch (menuChoice) {
                case 1:
                    executeOptionOne();
                    break;
                case 2:
                    executeOptionTwo();
                    break;
                case 3:
                    executeOptionThree();
                    break;
                case 4:
                    cout << "Exiting program. Goodbye!" << endl;
                    break;
                // Default case is not needed because getValidatedInput()
                // ensures the choice is always 1, 2, 3, or 4.
            }
        }
    }
};

/**
 * @brief Main entry point of the program.
 */
int main() {
    // Create an instance of the GrocerTracker class
    GrocerTracker tracker;
    
    // Run the application
    tracker.run();
    
    return 0;
}