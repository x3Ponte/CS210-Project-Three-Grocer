# CS210-Project-Three-Grocer
A C++ console application that tracks the frequency of items for a corner grocer.


**Project Files:**
* `ProjectThree.cpp`: The main C++ source code containing the `GrocerTracker` class and `main()` function
* `CS210_Project_Three_Input_File.txt`: The input file containing the list of purchased items
* `frequency.dat`: The backup data file created by the program on its initial run

---

This project involved creating a C++ console application for a Corner Grocer. The program's core function is to analyze a text file listing all items purchased in a day. It counts the frequency of each unique item and then provides a menu driven interface for the user. 

The problem it solves is turning raw sales data (a long list of items) into useful and queryable information. The user has the ability to:
1.  Search for the purchase frequency of a specific item.
2.  Print a list of all unique items and their frequencies.
3.  Print a histogram of all item frequencies.
4.  Exit the program.

To accomplish this the program reads the input file into a `std::map` data structure, which naturally handles the work of counting unique "keys" (the item names). It also demonstrates file output by writing this frequency data to a backup file `frequency.dat`.

### What I Did Particularly Well

I believe the program is well structured and robust. I am particularly happy with:
* **Object-Oriented Approach:** Encapsulating all the logic into a `GrocerTracker` class. This keeps the data (the `itemFrequencies` map) and the functions that operate on it (`readInputFile`, `executeOptionOne`, etc.) neatly bundled.
* **Input Validation:** The `getValidatedInput()` function is very robust. It correctly handles not only out of range numbers but also checks for non numeric input (ex. "abc"). It uses `cin.fail()`, `cin.clear()`, and `cin.ignore()` to prevent the program from crashing or entering an infinite loop.

### Where I Could Enhance the Code

Given more time, I would make several enhancements:

* **Efficiency:** For a *very* large dataset (like millions of items), the `std::map` could be replaced with a `std::unordered_map` . This would provide average $O(1)$ insertion and lookup, making the initial file read and subsequent searches faster.
* **Security & Features:** The current item search (`cin >> searchItem`) only works for single word items. If the list contained "Green Beans," the user could only search for "Green." I would enhance this by using `std::getline(cin, searchItem)` to capture multi word inputs.
* **Functionality:** I could add a function to allow the user to *add* new items to the purchase list which would then update the in memory map and also re write the `frequency.dat` file.

### Most Challenging Pieces

The most challenging part was probably implementing the robust input validation for the menu. Understanding the different states of the `cin` stream and knowing that I had to `clear()` the error *before* `ignore()`-ing the bad input took some research and debugging. 

I overcame this by consulting C++ documentation (cppreference.com) and searched for examples to understand how input streams work. Using the debugger to step through the `getValidatedInput` function and watch the state of `cin` was also invaluable.

### Transferable Skills

This project solidified several skills that are highly transferable:
* **Data Structure Selection:** Understanding *why* a `std::map` was the perfect tool for this job (counting unique items) is a critical skill.
* **File I/O:** Reading from (`ifstream`) and writing to (`ofstream`) files is a fundamental part of most software.
* **Error Handling:** Building a program that doesn't crash when the user does something unexpected is a core of professional development.
* **Modular Design:** Breaking the program into small single purpose functions (`displayMenu`, `executeOptionTwo`, etc.) makes the code far easier to debug and maintain.

### Program Maintainability, Readability, and Adaptability

I focused on making the code clean and professional:
* **Maintainable:** By using a class and private functions, the "internal" logic is hidden. If I need to change how the file is read, I only edit `readInputFile()`, and the rest of the program is unaffected.
* **Readable:** I used descriptive variable and function names (e.g., `itemFrequencies`, `getValidatedInput`) and provided comments to explain *why* certain things were done, not just *what* was done.
* **Adaptable:** The program can be easily adapted. By changing the `INPUT_FILE_NAME` constant, it can run on any input file. New menu options can be added easily by adding a new `executeOptionFive()` function and updating the `switch` statement, without having to rewrite the whole menu loop.
