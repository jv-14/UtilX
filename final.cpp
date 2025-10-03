#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <cstring>

using namespace std;

//-----------------------------------EVENT MANAGEMENT SYSTEM--------------------------------------//
class Event {
    private:
        string title;
        string description;
        string date;
        string time;

    public:
        Event(const string& t, const string& d, const string& dt, const string& tm)
            : title(t), description(d), date(dt), time(tm) {}

        void display() const {
            cout << "Title: " << title << endl;
            cout << "Description: " << description << endl;
            cout << "Date: " << date << endl;
            cout << "Time: " << time << endl;
        }

        const string& getTitle() const { return title; }
        const string& getDate() const { return date; }
    };

// Class to represent a calendar with events
class Calendar {
    private:
        vector<Event> events;

    public:
        void addEvent(const Event& event) {
            events.push_back(event);
        }

        void displayEvents() const {
            if (events.empty()) {
                cout << "No events scheduled." << endl;
            } else {
                cout << "Scheduled Events:" << endl;
                for (const auto& event : events) {
                    event.display();
                    cout << "------------------------" << endl;
                }
            }
        }

        void searchEventsOnDate(const string& targetDate) const {
            cout << "Events on " << targetDate << ":" << endl;
            bool found = false;
            for (const auto& event : events) {
                if (event.getDate() == targetDate) {
                    event.display();
                    cout << "------------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No events found on this date." << endl;
            }
        }
    };

//----------------------------------------TIME MANAGEMENT SYSTEM----------------------------------------------//

// Show current local time and date
void showLocalTime()
{
    time_t now = time(0);
    tm* local = localtime(&now);  // Get local time

    cout << "\nYour Local Time:\n";
    cout << "Date: "<< 1900 + local->tm_year << "-"<< 1 + local->tm_mon << "-"<< local->tm_mday << "\n";
    cout << "Time: "<< (local->tm_hour < 10 ? "0" : "") << local->tm_hour << ":"<< (local->tm_min < 10 ? "0" : "") << local->tm_min << ":"<< (local->tm_sec < 10 ? "0" : "") << local->tm_sec << "\n";
}
// Convert local time to a different timezone
void convertToOtherTimeZone(map<string, int>& zones)
{
    string city;

    cout << "\nAvailable Time Zones:\n";
    for (auto& z : zones)
        {
        cout << "- " << z.first << " (UTC ";
        if (z.second >= 0) cout << "+";
        cout << z.second << ")\n";
    }

    cout << "\nEnter city name to convert your time to: ";
    cin.ignore();
    getline(cin, city);

    if (zones.count(city))
        {
        int offset = zones[city];  // Time zone offset (in hours)
        time_t now = time(0);
        tm* local = localtime(&now);  // Get local time

        // Adjust for the offset of the selected city
        local->tm_hour += offset;

        // Normalize the time structure (handle overflow/underflow in hours, etc.)
        mktime(local);  // Adjust tm structure to account for overflow

        cout << "\n>> Local time in " << city << ":\n";
        cout << (local->tm_hour < 10 ? "0" : "") << local->tm_hour << ":"
             << (local->tm_min < 10 ? "0" : "") << local->tm_min << ":"
             << (local->tm_sec < 10 ? "0" : "") << local->tm_sec << "\n";
    } else
     {
        cout << "City not found.\n";
    }
}

// Simple stopwatch using user input instead of delay
void runStopwatch()
 {
    cout << "\nStopwatch - Press ENTER to start...";
    cin.ignore();  // This is required to discard the newline left in the buffer
    cin.get();  // Wait for the user to press ENTER

    time_t start = time(0);
    cout << "Running... Press ENTER to stop.";
    cin.get();  // Wait for the user to press ENTER again

    time_t end = time(0);
    int elapsed = static_cast<int>(end - start);

    int mins = elapsed / 60;
    int secs = elapsed % 60;

    cout << "Time elapsed: " << mins << " minutes and " << secs << " seconds.\n";
}

// Main menu
void showMenu()
{
    cout << "\n============================\n";
    cout << "   TIME MANAGEMENT UTILITY  \n";
    cout << "============================\n";
    cout << "1. View Current Local Time\n";
    cout << "2. Convert Time to Another Country\n";
    cout << "3. Use Stopwatch\n";
    cout << "0. Exit\n";
    cout << "============================\n";
    cout << "Enter your choice: ";
}

//------------------------BANK MANAGEMENT SYSTEM---------------------//
struct Transaction {
    string type;
    double amount;
    };

enum class AccountType {
    SAVINGS,
    CHECKING,
    LOAN
    };

void printLogo() {
    cout << " ~~~WELCOME TO BANK MANAGEMENT SYSTEM~~~ ";
    }

class Account {
    private:
        string accountNumber;
        string ownerName;
        double balance;
        AccountType type;
        vector<Transaction> transactionHistory;
    public:
        Account(string accNum, string owner, double initialBalance, AccountType accType) : accountNumber(accNum), ownerName(owner), balance(initialBalance), type(accType) {}

        string getAccountNumber() const { return accountNumber; }
        string getOwnerName() const { return ownerName; }
        double getBalance() const { return balance; }
        AccountType getAccountType() const { return type; }

    void deposit(double amount) {
        balance += amount;
        recordTransaction("Deposit", amount);
        cout << "Deposited " << amount << " successfully. New balance: " << balance << endl;
    }
    bool withdraw(double amount) {
        if (balance >= amount) {
        balance -= amount;
        recordTransaction("Withdrawal", amount);
        cout << "Withdrawn " << amount << " successfully. New balance: " << balance << endl;
        return true;
    }
    else {
        cout << "Insufficient funds." << endl;
        return false;
    }
    }
    void recordTransaction(string type, double amount) {
        Transaction transaction;
        transaction.type = type;
        transaction.amount = amount;
        transactionHistory.push_back(transaction);
    }

    void displayTransactionHistory() const {
        cout << "\nTransaction History for Account " << accountNumber << ":" << endl;
        cout << "-------------------------------------------" << endl;
        cout << setw(15) << "Type" << setw(15) << "Amount" << setw(25) << "Timestamp" << endl;
        cout << "-------------------------------------------" << endl;
    for (const auto& transaction : transactionHistory) {
        cout << setw(15) << transaction.type << setw(15) << transaction.amount << setw(25);
        }
        cout << endl;
    }
    };
class Bank {
    private:
        vector<Account> accounts;
        map<string, string> credentials;
    public:
        Bank() {
        // Adding predefined bank accounts
        accounts.emplace_back("1", "Parth", 500000.0, AccountType::SAVINGS);
        accounts.emplace_back("2", "Arushi", 75000.0, AccountType::SAVINGS);
        accounts.emplace_back("3", "Ananya", 100000.0, AccountType::SAVINGS);
        accounts.emplace_back("4", "Shoubhik", 100000.0, AccountType::SAVINGS);
        credentials["admin"] = "admin123";
    }
    void createAccount() {
        string accountNumber, ownerName;
        double initialBalance;
        int accountTypeChoice;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter owner name: ";
        cin.ignore();
        getline(cin, ownerName);
        cout << "Enter initial balance: ";
        cin >> initialBalance;
        cout << "Select account type:\n";
        cout << "1. Savings\n";
        cout << "2. Checking\n";
        cout << "3. Loan\n";
        cout << "Enter choice: ";
        cin >> accountTypeChoice;
        AccountType accType;
    switch (accountTypeChoice) {
        case 1:
        accType = AccountType::SAVINGS;
        break;
        case 2:
        accType = AccountType::CHECKING;
        break;
        case 3:
        accType = AccountType::LOAN;
        break;
        default:
        cout << "Invalid choice. Defaulting to savings account." << endl;
        accType = AccountType::SAVINGS;
    }
        accounts.emplace_back(accountNumber, ownerName, initialBalance, accType);
        cout << "Account created successfully." << endl;
    }
    Account* findAccount(string accountNumber) {
        auto it = find_if(accounts.begin(), accounts.end(), [&](const Account& acc) {
        return acc.getAccountNumber() == accountNumber;
    });
    if (it != accounts.end()) {
        return &(*it);
    }
    else {
        return nullptr;
    }
    }
    void deposit() {
        string accountNumber;
        double amount;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        Account* acc = findAccount(accountNumber);
        if (acc) {
        acc->deposit(amount);
        } else {
        cout << "Account not found." << endl;
        }
    }
    void withdraw() {
        string accountNumber;
        double amount;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        Account* acc = findAccount(accountNumber);
        if (acc) {
        acc->withdraw(amount);
        } else {
        cout << "Account not found." << endl;
        }
    }
    void transfer() {
        string fromAccountNumber, toAccountNumber;
        double amount;
        cout << "Enter from account number: ";
        cin >> fromAccountNumber;
        cout << "Enter to account number: ";
        cin >> toAccountNumber;
        cout << "Enter amount to transfer: ";
        cin >> amount;
        Account* fromAcc = findAccount(fromAccountNumber);
        Account* toAcc = findAccount(toAccountNumber);
        if (fromAcc && toAcc) {
        if (fromAcc->withdraw(amount)) {
        toAcc->deposit(amount);
        cout << "Transfer successful." << endl;
        } else {
        cout << "Transfer failed due to insufficient funds." << endl;
        }
        } else {
        cout << "One or both accounts not found." << endl;
        }
    }
    void displayAccountInfo() {
        string accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;
        Account* acc = findAccount(accountNumber);
        if (acc) {
        cout << "\nAccount Information\n";
        cout << "-------------------------------------------" << endl;
        cout << setw(20) << "Account Number: " << acc->getAccountNumber() << endl;
        cout << setw(20) << "Owner Name: " << acc->getOwnerName() << endl;
        cout << setw(20) << "Balance: $" << fixed << setprecision(2) << acc->getBalance() << endl;
        cout << setw(20) << "Account Type: ";
        switch (acc->getAccountType()) {
            case AccountType::SAVINGS:
                cout << "Savings Account" << endl;
                break;
            case AccountType::CHECKING:
                cout << "Checking Account" << endl;
                break;
            case AccountType::LOAN:
                cout << "Loan Account" << endl;
                break;
            }

                acc->displayTransactionHistory();
            }
            else {
                cout << "Account not found." << endl;
            }
        }
    };

//------------------------------TIC - TAC - TOE---------------------------//
class TicTacToeGame {
    private:
        char board[3][3];

        // Initializes the game board
        void initializeBoard() {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    board[i][j] = ' ';
        }

        // Displays the initial cell numbers for player reference
        void displayCellNumbers() const {
            int count = 1;
            cout << "\n\n\t  ";
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    cout << count++;
                    if (j < 2) cout << "  |  ";
                }
                if (i < 2) cout << "\n\t----------------\n\t  ";
            }
            cout << "\n\n\n";
        }

        // Displays the current game board
        void showBoard() const {
            cout << "\n\n\t  ";
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    cout << board[i][j];
                    if (j < 2) cout << "  |  ";
                }
                if (i < 2) cout << "\n\t----------------\n\t  ";
            }
            cout << "\n\n\n";
        }

        // Updates the board with a player's move
        bool updateBoard(int cell, char playerSign) {
            int row = (cell - 1) / 3;
            int col = (cell - 1) % 3;

            if (board[row][col] != ' ') {
                cout << "\nInvalid: Cell is already filled!\n";
                return false;
            }

            board[row][col] = playerSign;
            showBoard();
            return true;
        }

        // Checks if a player has won
        bool checkWinner(char sg) const {
            // Rows, Columns and Diagonals
            for (int i = 0; i < 3; ++i) {
                if (board[i][0] == sg && board[i][1] == sg && board[i][2] == sg) return true;
                if (board[0][i] == sg && board[1][i] == sg && board[2][i] == sg) return true;
            }
            if ((board[0][0] == sg && board[1][1] == sg && board[2][2] == sg) ||
                (board[0][2] == sg && board[1][1] == sg && board[2][0] == sg)) return true;

            return false;
        }

        // Runs one session of the game
        void playSession() {
            int cell = 0, playCount = 0;
            char playerSign = ' ';
            bool gameResult = false;

            while (!gameResult && playCount < 9) {
                playerSign = (playCount % 2 == 0) ? 'X' : 'O';
                cout << "\nPlayer " << (playerSign == 'X' ? 1 : 2) << " [ " << playerSign << " ] : ";
                cin >> cell;

                if (cell == -1) {
                    cout << "\n\tGame Terminated\n";
                    return;
                }

                if (cell >= 1 && cell <= 9) {
                    if (updateBoard(cell, playerSign)) {
                        gameResult = checkWinner(playerSign);
                        if (gameResult) {
                            cout << "\t * Player " << (playerSign == 'X' ? 1 : 2) << " Won!! *\n";
                        }
                        ++playCount;
                    }
                } else {
                    cout << "\nPlease Enter a valid cell value (1-9) or -1 to exit\n";
                }
            }

            if (!gameResult && playCount == 9) {
                cout << "\n\t * Draw...  *\n";
            }

            cout << "\n\t --- Game Over --- \n";
        }

    public:
        // Starts the full game loop
        void start() {
            cout << "--------- Tic Tac Toe ----------\n\n";
            cout << "\n* Instructions \n";
            cout << "\tPlayer 1 sign = X\n";
            cout << "\tPlayer 2 sign = O\n";
            cout << "\n\tTo exit from the game, Enter -1\n";

            int userChoice = 1;

            while (userChoice) {
                initializeBoard();
                displayCellNumbers();
                playSession();

                cout << "\n* Menu\n";
                cout << "\nPress 1 to Restart";
                cout << "\nPress 0 for Exit";
                cout << "\n\nChoice: ";
                cin >> userChoice;
                cin.ignore(); // Clear newline
                cout << "\n";
            }

            cout << "\n :: Thanks for playing Tic Tac Toe game! :: \n";
        }
    };

//----------------------------ROCK PAPER SCISSORS-----------------------------//
class RPSGame {
    private:
        char playerChoice;
        char computerChoice;

    public:
        // Constructor to seed RNG
        RPSGame() {
            srand(time(0));
        }

        // Function to generate computer move
        void generateComputerChoice() {
            int n = rand() % 100;

            if (n < 33)
                computerChoice = 's'; // Stone
            else if (n >= 33 && n < 66)
                computerChoice = 'p'; // Paper
            else
                computerChoice = 'z'; // Scissor
        }

        // Function to get user input
        void getPlayerChoice() {
            cout << "\nEnter 's' for STONE, 'p' for PAPER, 'z' for SCISSORS: ";
            cin >> playerChoice;

            // Validate input
            while (playerChoice != 's' && playerChoice != 'p' && playerChoice != 'z') {
                cout << "Invalid input. Please enter 's', 'p', or 'z': ";
                cin >> playerChoice;
            }
        }

        // Determine winner
        int determineWinner() {
            if (playerChoice == computerChoice)
                return -1; // Draw

            if ((playerChoice == 's' && computerChoice == 'z') ||
                (playerChoice == 'p' && computerChoice == 's') ||
                (playerChoice == 'z' && computerChoice == 'p'))
                return 1; // Player wins
            else
                return 0; // Computer wins
        }

        // Display result
        void showResult() {
            cout << "\nYou chose: " << choiceToWord(playerChoice)
                 << " | Computer chose: " << choiceToWord(computerChoice) << "\n";

            int result = determineWinner();
            if (result == -1)
                cout << "Result: It's a Draw!" << endl;
            else if (result == 1)
                cout << "Result: You Win!" << endl;
            else
                cout << "Result: You Lose!" << endl;
        }

        // Convert char to word for display
        string choiceToWord(char c) {
            if (c == 's') return "Stone";
            else if (c == 'p') return "Paper";
            else if (c == 'z') return "Scissors";
            return "Unknown";
        }

        // The main game method
        void play() {
            getPlayerChoice();
            generateComputerChoice();
            showResult();
        }
    };

//------------------------------JUMANJI-----------------------------//
class player
{
    public:
    int pos;
public:
    player()
    {
        pos=1;
    }
    int movePlayer(player currentPlayer, int roll)
{
    int newPosition = pos + roll;
    // Define the positions of Boosts and degrades
    int condition[101];

    for (int i = 0; i <= 100; i++) {
        condition[i] = 0;
    }

      // here positive weights represent a Positive Outcome
      // and negative weights represent a Negative outcome
    condition[2] = -1;
    condition[4] = 3;
    condition[7] = 5;
    condition[10] = 35;
    condition[18] = 7;
    condition[15] = -3;
    condition[14] = 3;
    condition[22] = -10;
    condition[32] = -4;
    condition[35] = 5;
    condition[38] = 4;
    condition[53] = -6;
    condition[56] = -8;
    condition[59] = 6;
    condition[73] = 6;
    condition[77] = 2;
    condition[95] = 2;
    condition[91] = 6;
    condition[99] = -50;




    int newSquare=newPosition + condition[newPosition];


        switch(newPosition)
        {
            case(2):cout<<"Oops! Volcano erruption! Go back to start !!!";
            break;
            case(4):cout<<"You found a hidden passage! Move forward 3 spaces!!";
            break;
            case(7):cout<<"You find the first piece of incomplete map!!!";
            break;
            case(10):cout<<"Found an underground tunnel, take a big jump to 45";
            break;
            case(18):cout<<"Get a lift by Jumanji's unique insects, move forward by 7 spaces";
            break;
            case(15):cout<<"A venomous snake crosses your path. Move back 3 spaces";
            break;
            case(14):cout<<"A wise old monkey shows you the way. Move forward 3 spaces";
            break;
            case(22):cout<<"A sudden thunderstorm strikes! Move back 10 spaces";
            break;
            case(32):cout<<"You slip on a mossy rock. Move back 4 spaces";
            break;
            case(35):cout<<"A friendly elephant gives you a ride. Move forward 5 spaces";
            break;
            case(38):cout<<"The river current pushes you forward. Advance 4 spaces";
            break;
            case(53):cout<<"Rhino attack, save yourself and move back 6 spaces";
            break;
            case(56):cout<<"A mischievous monkey stole your supplies. Move back 8 spaces";
            break;
            case(59):case(73):cout<<"You discover a magical shortcut! Jump ahead 6 spaces";
            break;
            case(77):case(95):cout<<"You discover a magical fruit! Jump ahead 2 spaces";
            break;
            case(91):cout<<"A sparkling treasure motivates you! Move forward 6 spaces";
            break;
            case(99):cout<<"You fell of the cliff into the Hanoi River, You're 50 spaces back";
            break;

        }

    if (newSquare > 100) {
        return currentPlayer.pos; // Player cannot move beyond
                              // square 100
    }

    return newSquare;
}
};
class Game
{
    public:
    player player1,player2;
    int board[101];
public:
    Game()
    {
        player1.pos=0;player2.pos=0;
    }
    int rollDie()
    {
        return rand()%6+1;
    }
void printBoard()
{
    for (int i=1; i<= 100; i++)
{
board[i] =i ;
}
int alt = 0; // to switch between the alternate nature of the board
int iterLR = 101; // iterator to print from left to right
int iterRL = 80; // iterator to print from right to left
int val = 100;
while (val--)
{
if (alt == 0) {
iterLR--;
if (iterLR==player1.pos) {
cout<<"#P1    ";
}
else if (iterLR == player2.pos) {
cout<<"#P2    ";
}
else
cout<<board[iterLR]<<"\t";
if (iterLR % 10 == 1) {
cout<<"\n\n";
alt = 1;
iterLR -= 10;
}
}

else {
            iterRL++;
            if (iterRL == player1.pos) {
                cout<<"#P1    ";
            }
            else if (iterRL == player2.pos) {
                cout<<"#P2    ";
            }
            else
                cout<<board[iterRL]<<"\t";

            if (iterRL % 10 == 0) {
                cout<<"\n\n";
                alt = 0;
                iterRL -= 30;
            }
        }
        if (iterRL == 10)
            break;
    }
    printf("\n");
}
};



//------------------------------HANGMAN-----------------------------//
int getRandomIndex(int size) {
    return rand() % size;
}
void guess(const char word[]) {
    int lives = 6;
    char guessed[20];
    char inputChar;
    int wordLength = strlen(word);

    // Initialize guessed array with asterisks
    for (int i = 0; i < wordLength; i++) {
        guessed[i] = '*';
    }
    guessed[wordLength] = '\0'; // Null-terminate the string

    while (lives > 0) {
        bool correct = false;

        cout << "\nYou have " << lives << " lives left." << endl;
        cout << "Enter a character to guess: ";
        cin >> inputChar;

        for (int i = 0; i < wordLength; i++) {
            if (tolower(word[i]) == tolower(inputChar) && guessed[i] == '*') {
                guessed[i] = word[i];
                correct = true;
            }
        }

        // Show the current guessed word
        for (int i = 0; i < wordLength; i++) {
            cout << guessed[i] << " ";
        }
        cout << "\n";

        if (!correct) {
            cout << "\nWrong guess!\n";
            lives--;
        } else {
            cout << "Go ahead... you're right!\n";
        }

        // Draw hangman depending on lives
        switch (lives) {
            case 5:
                cout << "\n\t+---+\n\t |   |\n";
                break;
            case 4:
                cout << "\n\t+---+\n\t |   |\n\t O   |\n";
                break;
            case 3:
                cout << "\n\t+---+\n\t |   |\n\t O   |\n\t/|\\  |\n";
                break;
            case 2:
                cout << "\n\t+---+\n\t |   |\n\t O   |\n\t/|\\  |\n\t/    |\n";
                break;
            case 1:
                cout << "\n\t+---+\n\t |   |\n\t O   |\n\t/|\\  |\n\t/ \\  |\n\t     |\n\t=========\n";
                break;
        }

        // Check if the word is fully guessed
        if (strcmp(word, guessed) == 0) {
            cout << "\n\n~~ Congratulations! You won the game! ~~\n";
            cout << "\nThe word was: " << word << endl;
            return; // Exit the guess function
        }
    }

    // If lives are 0
    cout << "\nYou did not guess the full word!... Better luck next time.";
    cout << "\nThe word was: " << word << endl;
    cout << "\n\t+---+\n\t |   |\n\t O   |\n\t/|\\  |\n\t/ \\  |\n\t     |\n\t=========\n";
}


int main() {
    cout<<"------------------------------------------------------------------------------------------------------\n";
		cout<<"|  -------------------------------------------------------------------------------------------------  |\n";
		cout<<"| |                                                                                                 | |\n";
		cout<<"| |                                 ~~~WELCOME TO UTILIX~~~                                         | |\n";
		cout<<"| |                                                                                                 | |\n";
		cout<<"|  -------------------------------------------------------------------------------------------------  |\n";
		cout<<"-----------------------------------------------------------------------------------------------------\n\n";

    int choice;


    do {
        cout << "\nWhat app do you want to use?\n";
        cout << "Enter 1 for the Event Manager.\n";
        cout << "Enter 2 for the Time Management System.\n";
        cout << "Enter 3 for the Bank Management System.\n";
        cout << "Enter 4 for the Gaming Arcade.\n";
        cout << "Enter 5 to Exit.\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Calendar calendar;
                calendar.addEvent(Event("T3", "UNIVERSAL HUMAN VALUES ", "2025-05-14", "02:30 PM"));
                calendar.addEvent(Event("T3", "PHYSICS ", "2025-05-16", "10:00 AM"));
                calendar.addEvent(Event("T3", "MATHS ", "2025-05-19", "02:30 PM"));
                calendar.addEvent(Event("T3", "SOFTWARE DEVELOPMENT FUNDAMENTALS", "2025-05-22", "10:00 AM"));
                calendar.addEvent(Event("PROJECT EVALUATION", "SOFTWARE DEVELOPMENT LAB", "2025-04-28", "02:00 PM"));

                int eventChoice;
                do {
                    cout << "\nCalendar Management System\n";
                    cout << "1. Add Event\n";
                    cout << "2. Display All Events\n";
                    cout << "3. Search Events by Date\n";
                    cout << "4. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> eventChoice;

                    if (eventChoice == 1) {
                        string title, description, date, time;
                        cout << "Enter event title: ";
                        cin.ignore();
                        getline(cin, title);
                        cout << "Enter event description: ";
                        getline(cin, description);
                        cout << "Enter event date (YYYY-MM-DD): ";
                        getline(cin, date);
                        cout << "Enter event time: ";
                        getline(cin, time);

                        calendar.addEvent(Event(title, description, date, time));
                        cout << "Event added successfully.\n";
                    }
                    else if (eventChoice == 2) {
                        calendar.displayEvents();
                    }
                    else if (eventChoice == 3) {
                        string searchDate;
                        cout << "Enter date to search events (YYYY-MM-DD): ";
                        cin.ignore();
                        getline(cin, searchDate);
                        calendar.searchEventsOnDate(searchDate);
                    }
                    else if (eventChoice == 4) {
                        cout << "Exiting Calendar System.\n";
                    }
                    else {
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (eventChoice != 4);

                break;
            }

            case 2: {
                map<string, int> timeZones = {
                    {"New York", -4},
                    {"London", 0},
                    {"Paris", 1},
                    {"Dubai", 4},
                    {"India", 5},
                    {"Japan", 9},
                    {"Sydney", 10}
                };

                int timeChoice;
                do {
                    showMenu();
                    cin >> timeChoice;

                    switch (timeChoice) {
                        case 1:
                            showLocalTime();
                            break;
                        case 2:
                            convertToOtherTimeZone(timeZones);
                            break;
                        case 3:
                            runStopwatch();
                            break;
                        case 0:
                            cout << "Exiting Time Management System.\n";
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }

                    if (timeChoice != 0) {
                        cout << "\nPress ENTER to return to the menu...";
                        cin.ignore();
                        cin.get();
                    }

                } while (timeChoice != 0);

                break;
            }

            case 3: {
                Bank bank;
                int bankChoice;
                do {
                    printLogo();
                    cout << "\nBank System Menu\n";
                    cout << "1. Create Account\n";
                    cout << "2. Deposit\n";
                    cout << "3. Withdraw\n";
                    cout << "4. Transfer\n";
                    cout << "5. Display Account Info\n";
                    cout << "6. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> bankChoice;

                    switch (bankChoice) {
                        case 1:
                            bank.createAccount();
                            break;
                        case 2:
                            bank.deposit();
                            break;
                        case 3:
                            bank.withdraw();
                            break;
                        case 4:
                            bank.transfer();
                            break;
                        case 5:
                            bank.displayAccountInfo();
                            break;
                        case 6:
                            cout << "Exiting Bank System.\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                } while (bankChoice != 6);

                break;
            }

            case 4: {
                int gameChoice;
                cout << "WELCOME TO GAMING ARCADE\n\n";

                do {
                    cout << "Choose the game you want to play:\n";
                    cout << "1. Tic-Tac-Toe\n";
                    cout << "2. Rock Paper Scissors\n";
                    cout << "3. Jumanji\n";
                    cout << "4. Hangman\n";
                    cout << "5. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> gameChoice;

                    switch (gameChoice) {
                        case 1: {
                            TicTacToeGame game;
                            game.start();
                            break;
                        }
                        case 2: {
                            RPSGame game;
                            char playAgain;
                            do {
                                game.play();
                                cout << "\nDo you want to play again? (y/n): ";
                                cin >> playAgain;
                                while (playAgain != 'y' && playAgain != 'n') {
                                    cout << "Invalid input. Enter 'y' to play again or 'n' to exit: ";
                                    cin >> playAgain;
                                }
                            } while (playAgain == 'y');
                            cout << "\nThanks for playing!\n";
                            break;
                        }
                        case 4: {
                            char playAgain;
                            const char words[28][20] = {
                                "helicopter", "professional", "perfectionist", "declaration", "espionage", "knapsack",
                                "congratulations", "psychology", "acknowledgment", "application", "challenge", "pneumonia",
                                "larynx", "phenomenal", "fragrance", "instrument", "principal", "immediately",
                                "principle", "contiguous", "collage", "changeable", "conscientious", "hierarchy",
                                "millennium", "neighbour", "perseverance", "playwright"
                            };

                            srand(time(0));

                            do {
                                cout << "\nLet's play the Hangman game!\n\n";

                                int randomIndex = getRandomIndex(28);
                                char selectedWord[20];
                                strcpy(selectedWord, words[randomIndex]);

                                guess(selectedWord);

                                cout << "\nDo you want to play again? (Y/y for yes): ";
                                cin >> playAgain;

                            } while (playAgain == 'Y' || playAgain == 'y');

                            cout << "\nThank you for playing Hangman. Goodbye!\n";
                            break;
                        }
                        case 3: {
                            cout << "Welcome to Jumanji!\n";
                            Game g1;
                            srand(time(0));
                            int currentPlayer = 1;
                            int won = 0;

                            while (!won) {
                                cout << "\nPlayer " << currentPlayer << ", press Enter to roll the die...";
                                cin.ignore();
                                cin.get();
                                int roll = g1.rollDie();
                                printf("You rolled a %d.\n", roll);

                                if (currentPlayer == 1) {
                                    g1.player1.pos = g1.player1.movePlayer(g1.player1, roll);
                                    if (g1.player1.pos > 100) {
                                        cout << "Try again next time!\n";
                                    } else {
                                        printf("Player 1 is now at square %d.\n\n", g1.player1.pos);
                                        g1.printBoard();
                                        if (g1.player1.pos == 100) {
                                            cout << "Player 1 wins!\n";
                                            won = 1;
                                        }
                                    }
                                } else {
                                    g1.player2.pos = g1.player2.movePlayer(g1.player2, roll);
                                    if (g1.player2.pos > 100) {
                                        cout << "Try again next time!\n";
                                    } else {
                                        printf("Player 2 is now at square %d.\n\n", g1.player2.pos);
                                        g1.printBoard();
                                        if (g1.player2.pos == 100) {
                                            cout << "Player 2 wins!\n";
                                            won = 1;
                                        }
                                    }
                                }

                                currentPlayer = (currentPlayer == 1) ? 2 : 1;
                            }

                            break;
                        }
                        case 5:
                            cout << "Exiting Gaming Arcade.\n";
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }

                } while (gameChoice != 5);

                break;
            }

            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}

