#include <string>
#include <cstdlib> // для system("cls") / system("clear")
#include <limits>

using namespace std;

class Railway {
private:
    string name;         // Название 
    double ticketPrice;  // Стоимость билета
    int totalSeats;      // Общее количество мест во всех самолетах
    int soldTickets;     // Количество проданных билетов

public:
    Railway(const string& railwayName, double price, int seats)
        : name(railwayName), ticketPrice(price), totalSeats(seats), soldTickets(0) {}

    void sellTickets(int number) {
        if (number <= (totalSeats - soldTickets)) {
            soldTickets += number;
            cout << "Sold " << number << " tickets." << endl;
        }
        else {
            cout << "There are not enough available places for sale " << number << " tickets." << endl;
        }
    }

    double calculateTotalRevenue() const {
        return totalSeats * ticketPrice - soldTickets * ticketPrice;
    }

    void displayInfo() const {
        cout << "Railway: " << name << endl;
        cout << "Ticket cost: " << ticketPrice << endl;
        cout << "Total number of seats: " << totalSeats << endl;
        cout << "Tickets sold: " << soldTickets << endl;
        cout << "Total cost of tickets: " << calculateTotalRevenue() << endl;
    }
};

void clearConsole() {
#ifdef _WIN32
    system("cls");  // Очистка консоли для Windows
#else
    system("clear"); // Очистка консоли для Linux/Unix
#endif
}

bool isValidNumber(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Функция для безопасного ввода числа с проверкой на некорректный ввод
template <typename T>
T getValidInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        cin >> input;

        if (isValidNumber(input)) {
            try {
                if constexpr (is_same<T, int>::value) {
                    return stoi(input);
                }
                else if constexpr (is_same<T, double>::value) {
                    return stod(input);
                }
            }
            catch (const invalid_argument& e) {
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }
        else {
            cout << "Invalid input. Please enter only numbers." << endl;
        }
    }
}

int main() {
    Railway* railway = nullptr;
    bool OnDisplay = true;
    short int choice;

    while (OnDisplay) {
        clearConsole();
        cout << "Database Administrator Console:\n";
        cout << "1. To add a new Railway to the database.\n";
        cout << "2. Current information about the Railway.\n";
        cout << "3. Calculating total revenue.\n";
        cout << "4. Sell tickets.\n";
        cout << "5. Exit.\n";


        choice = getValidInput<int>("lol: ");
        switch (choice) {
        case 1: {
            clearConsole();
            string airportname;
            double airportprice;
            int airportseats;

            cout << "Enter the name of the Railway: ";
            cin >> airportname;
            airportprice = getValidInput<double>("Enter the ticket price: ");
            airportseats = getValidInput<int>("Enter the total number of seats: ");

            // Создаем новый ржд
            railway = new Railway(airportname, airportprice, airportseats);
            cout << "Railway added successfully!" << endl;
            break;
        }
        case 2: {
            clearConsole();
            if (railway) {
                railway->displayInfo();
            }
            else {
                cout << "No Railway data available. Please add an railway first." << endl;
            }
            break;
        }
        case 3: {
            clearConsole();
            if (railway) {
                cout << "Total revenue: " << railway->calculateTotalRevenue() << endl;
            }
            else {
                cout << "No railway data available. Please add an Railway first." << endl;
            }
            break;
        }
        case 4: {
            clearConsole();
            if (railway) {
                int ticketsToSell = getValidInput<int>("Enter the number of tickets to sell: "); // безопасный ввод
                railway->sellTickets(ticketsToSell);
            }
            else {
                cout << "No railway data available. Please add an railway first." << endl;
            }
            break;
        }
        case 5: {
            clearConsole();
            cout << "Exiting the program..." << endl;
            OnDisplay = false;
            break;
        }
        default: {
            clearConsole();
            cout << "Invalid choice. Please try again." << endl;
        }
        }


        if (OnDisplay) {
            cout << "Press Enter to continue...";
            cin.ignore(); // Игнорируем символ новой строки после ввода числа
            cin.get(); // Ожидаем нажатия клавиши
        }
    }


    if (railway) {
        delete railway;
    }

    return 0;
}
