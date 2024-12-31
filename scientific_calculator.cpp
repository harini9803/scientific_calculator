#include <iostream>
#include <cmath>
#include <concepts>
#include <stdexcept>

// Define a concept to ensure the type supports necessary mathematical operations
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

// ScientificCalculator class template
template <Numeric T>
class ScientificCalculator {
public:
    explicit ScientificCalculator(T value = 0) : currentValue(value) {}

    void setCurrentValue(T val) { currentValue = val; }

    T calculateSin() const { return std::sin(currentValue); }
    T calculateCos() const { return std::cos(currentValue); }
    T calculateTan() const { return std::tan(currentValue); }
    T calculateExp() const { return std::exp(currentValue); }

    T calculateLog() const {
        if (currentValue <= 0) throw std::domain_error("Logarithm is undefined for non-positive values.");
        return std::log(currentValue);
    }

    T calculateSqrt() const {
        if (currentValue < 0) throw std::domain_error("Square root is undefined for negative values.");
        return std::sqrt(currentValue);
    }

    T calculatePower(T exponent) const { return std::pow(currentValue, exponent); }
    T calculateFractionalPart() const { return currentValue - std::floor(currentValue); }

    T add(T other) const { return currentValue + other; }
    T subtract(T other) const { return currentValue - other; }
    T multiply(T other) const { return currentValue * other; }

    T divide(T other) const {
        if (other == 0) throw std::invalid_argument("Division by zero is undefined.");
        return currentValue / other;
    }

private:
    T currentValue;
};

// Function to get a valid number from the user
template <typename T>
T promptForNumber(const std::string &message) {
    T number;
    while (true) {
        std::cout << message;
        std::cin >> number;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return number;
        }
    }
}

// Function to display the menu
void displayMenu() {
    std::cout << "1. Sine\n"
              << "2. Cosine\n"
              << "3. Tangent\n"
              << "4. Exponential\n"
              << "5. Logarithm\n"
              << "6. Square Root\n"
              << "7. Power\n"
              << "8. Fractional Part\n"
              << "9. Addition\n"
              << "10. Subtraction\n"
              << "11. Multiplication\n"
              << "12. Division\n"
              << "13. Exit\n"
              << "Enter your selection: ";
}

int main() {
    ScientificCalculator<double> calculator;
    int selection;

    while (true) {
        displayMenu();
        std::cin >> selection;

        if (selection == 13) {
            std::cout << "Exiting the calculator. Goodbye!\n";
            break;
        }

        double value = 0, operand = 0, result = 0;

        try {
            switch (selection) {
                case 1:
                    value = promptForNumber<double>("Enter the value (in radians) for sine: ");
                    calculator.setCurrentValue(value);
                    result = calculator.calculateSin();
                    break;
                case 2:
                    value = promptForNumber<double>("Enter the value (in radians) for cosine: ");
                    calculator.setCurrentValue(value);
                    result = calculator.calculateCos();
                    break;
                case 3:
                    value = promptForNumber<double>("Enter the value (in radians) for tangent: ");
                    calculator.setCurrentValue(value);
                    result = calculator.calculateTan();
                    break;
                case 4:
                    value = promptForNumber<double>("Enter the value for exponential: ");
                    calculator.setCurrentValue(value);
                    result = calculator.calculateExp();
                    break;
                case 5:
                    value = promptForNumber<double>("Enter the value for logarithm: ");
                    calculator.setCurrentValue(value);
                    result = calculator.calculateLog();
                    break;
                case 6:
                    value = promptForNumber<double>("Enter the value for square root: ");
                    calculator.setCurrentValue(value);
                    result = calculator.calculateSqrt();
                    break;
                case 7:
                    value = promptForNumber<double>("Enter the base value: ");
                    operand = promptForNumber<double>("Enter the exponent value: ");
                    calculator.setCurrentValue(value);
                    result = calculator.calculatePower(operand);
                    break;
                case 8:
                    value = promptForNumber<double>("Enter the value to get its fractional part: ");
                    calculator.setCurrentValue(value);
                    result = calculator.calculateFractionalPart();
                    break;
                case 9:
                    value = promptForNumber<double>("Enter the first number: ");
                    operand = promptForNumber<double>("Enter the second number: ");
                    calculator.setCurrentValue(value);
                    result = calculator.add(operand);
                    break;
                case 10:
                    value = promptForNumber<double>("Enter the first number: ");
                    operand = promptForNumber<double>("Enter the second number: ");
                    calculator.setCurrentValue(value);
                    result = calculator.subtract(operand);
                    break;
                case 11:
                    value = promptForNumber<double>("Enter the first number: ");
                    operand = promptForNumber<double>("Enter the second number: ");
                    calculator.setCurrentValue(value);
                    result = calculator.multiply(operand);
                    break;
                case 12:
                    value = promptForNumber<double>("Enter the dividend: ");
                    operand = promptForNumber<double>("Enter the divisor: ");
                    calculator.setCurrentValue(value);
                    result = calculator.divide(operand);
                    break;
                default:
                    std::cout << "Invalid selection. Please choose a valid option.\n";
                    continue;
            }

            std::cout << "Result: " << result << "\n";
        } catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
