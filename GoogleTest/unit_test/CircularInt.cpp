/** Includes */
#include "CircularInt.hpp"

/**
 * \brief this class implements all the operators of the object CircularInt.
 * To implement the operators the number is first modified as the operator works, then, replace in his definition space.
 * \author Johann and Samuel.
 */

/**
 * \brief  Constructor.
 * This is the constructor for the object CircleInt.
 * \param minimum
 * \param maximum
 * Complexity : O(1).
 */
CircularInt::CircularInt(const int minimum, const int maximum) {
    if (maximum < minimum) {
        cout << "error in the constructor : minimum > maximum." << endl;
        exit(0);
    }
    this->minimum = minimum;
    this->maximum = maximum;
    this->circle = maximum - minimum + 1; //The circle is the number of naturals numbers in the definition space.
    this->currentNumber = minimum;        //Initialization of the number as minimum of the definition space.
}

//Operators.

/**
 * \brief This operator do copy assignment
 * \param circularInt
 * param success description of param here removes warning
 * \return the object CircularInt after the copy assignment.
 * Complexity : O(1).
 */
CircularInt& CircularInt::operator= (CircularInt circularInt){
    swap(currentNumber,circularInt.currentNumber);
    swap(maximum,circularInt.maximum);
    swap(minimum,circularInt.minimum);
    swap(circle,circularInt.circle);
    return *this ;
}

/**
 * \brief This operator increments the currentNumber of the CircularInt by the integer "increment".
 * \param increment
 * \return the object CircularInt after the incrementation.
 * Complexity : O(1).
 */
CircularInt& CircularInt::operator+= (const int increment) {
    currentNumber = currentNumber + increment;
    currentNumber = moduloOperation();
    return *this;
}

/**
 * From wikipedia (https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B) :
 * Note: C++ uses the unnamed dummy-parameter int to differentiate between prefix and postfix increment operators.
 * This operator increment the number of the object CircularInt by +1 like postfix.
 * Attention, the return is the initial number without the modification.
 * \brief In contrary of a++, we first return a and then do the incrementation.
 * \param increment (As explain above).
 * \return the object CircularInt before the incrementation.
 * Complexity : O(1).
 */
CircularInt CircularInt::operator++ (const int increment) {
    const CircularInt answer = *this;
    currentNumber = currentNumber + 1;
    currentNumber = moduloOperation();
    return answer;
}

/**
 * \brief This operator do  - currentNumber which means maximum - number.
 * For example with the hour in the definition space {1, 12} it's should calculate 12 - number.
 * This method only return an object and do not have any side effect on the object.
 * \return the object CircularInt after the modification.
 * Complexity : O(1).
 */
CircularInt CircularInt::operator- () {
    CircularInt answer = *this;
    answer.currentNumber =  maximum - currentNumber;
    answer.currentNumber = answer.moduloOperation();
    return answer;
}

/**
 * \brief This operator do currentNumber * multiplier.
 * \param multiplier
 * \return the object CircularInt after the modification.
 * Complexity : O(1).
 */
CircularInt& CircularInt::operator*= (const int multiplier) {
    currentNumber = currentNumber * multiplier;
    currentNumber = moduloOperation();
    return *this;
}

/**
 * \brief This operator work as : currentNumber / divisor.
 * if number % divisor != 0 there no answer.
 * This method only return an object and do not have any side effect on the object.
 * \param divisor
 * \return the object CircularInt after the division (if it's happen).
 * Complexity : O(1).
 */
CircularInt CircularInt::operator/ (int divisor) {
    if(currentNumber % divisor != 0) {
        throw string(NotDivisible(*this, divisor).what());
    }
    else {
       CircularInt answer = *this;
       answer.currentNumber = answer.currentNumber / divisor;
       answer.currentNumber = answer.moduloOperation();
       return answer;
    }
}

// Operators that we added.

/**
 * From wikipedia (https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B) :
 * Note: C++ uses the unnamed dummy-parameter int to differentiate between prefix and postfix increment operators.
 * \brief This operator increment the number of the object CircularInt by +1 like prefix.
 * \return the number after the incrementation.
 * Complexity : O(1).
 */
CircularInt& CircularInt::operator++ () {
    currentNumber = currentNumber + 1;
    currentNumber = moduloOperation();
    return *this;
}

/**
 * \brief This operator decrement the number of the CircularInt by the number decrement.
 * \param decrement
 * \return the number after the incrementation.
 * Complexity : O(1).
 */
CircularInt& CircularInt::operator-= (const int decrement) {
    currentNumber = currentNumber - decrement;
    currentNumber = moduloOperation();
    return *this;
}

/**
 * From wikipedia (https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B) :
 * Note: C++ uses the unnamed dummy-parameter int to differentiate between prefix and postfix decrement operators.
 * This operator decrement the number of the object CircularInt by -1 like postfix.
 * Attention, the return is the initial number without the modification.
 * \brief In contrary of a--, we first return a and then do -1.
 * \param increment (As explain above).
 * \return the object CircularInt before the modification.
 * Complexity : O(1).
 */
CircularInt CircularInt::operator-- (const int decrement) {
    const CircularInt answer = *this;
    currentNumber = currentNumber - 1;
    currentNumber = moduloOperation();
    return answer;
}

/**
 * From wikipedia (https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B) :
 * Note: C++ uses the unnamed dummy-parameter int to differentiate between prefix and postfix decrement operators.
 * This operator decrement the number of the object CircularInt by -1 like prefix.
 * Attention, the return is the initial number without the modification.
 * \return the object CircularInt after the modification.
 * Complexity : O(1).
 */
CircularInt& CircularInt::operator-- () {
    currentNumber = currentNumber - 1;
    currentNumber = moduloOperation();
    return *this;
}

/**
 * \brief This operator is a modular division.
 * source of the help for the implementation : https://www.geeksforgeeks.org/modular-division/
 * \param divisor
 * \return the object CircularInt after the modification (if it's happen).
 */
CircularInt CircularInt::operator%= (const int divisor) {
    currentNumber = currentNumber % circle;
    int inv = modInverse(divisor);
    if (inv == -1)
        throw string(NotDivisible(*this, divisor).what());
    currentNumber = (inv * currentNumber) % circle;
    currentNumber = moduloOperation();
    return *this;
}

/**
 * \brief This operators do hour + increment.
 * \attention at the difference of +=, this operator only return a new object circularInt without side effect on the "this".
 * \param increment
 * \return an object CircularInt after the incrementation.
 */
CircularInt CircularInt::operator+ (const int increment) {
    CircularInt answer = *this;
    answer.currentNumber = answer.currentNumber + increment;
    answer.currentNumber = answer.moduloOperation();
    return answer;
}

/**
 * \brief This operators do hour - decrement.
 * \attention at the difference of -=, this operator only return a new object circularInt without side effect on the "this".
 * \param decrement
 * \return an object CircularInt after the modification.
 */
CircularInt CircularInt::operator- (const int decrement) {
    CircularInt answer = *this;
    answer.currentNumber = answer.currentNumber - decrement;
    answer.currentNumber = answer.moduloOperation();
    return answer;
}

/**
 * \brief This operators do hour * multiplier.
 * \attention at the difference of *=, this operator only return a new object circularInt without side effect on the "this".
 * \param multiplier
 * \return an object CircularInt after the modification.
 */
CircularInt CircularInt::operator* (const int multiplier) {
    CircularInt answer = *this;
    answer.currentNumber = answer.currentNumber * multiplier;
    answer.currentNumber = answer.moduloOperation();
    return answer;
}

/**
 * \brief This operator check if two object CircularInt are equal.
 * \attention : by equal we means that all the parameter of the object are equal.
 * \param circularInt
 * \return true if it's equal, false if not.
 */
bool CircularInt::operator ==(CircularInt const& circularInt) {
    if (currentNumber == circularInt.getCurrentNumber() &&
        minimum == circularInt.getMinimum() &&
        maximum == circularInt.getMaximum())
        return true;
    return false;
}

/**
 * \brief This operator check if two object CircularInt are different.
 * \attention : by different we means that at least one the parameter of the object is different.
 * \param circularInt
 * \return true if it's different, false if not.
 */
bool CircularInt::operator !=(CircularInt const& circularInt) {
    if (currentNumber != circularInt.getCurrentNumber() ||
        minimum != circularInt.getMinimum() ||
        maximum != circularInt.getMaximum())
        return true;
    return false;
}

/**
 * \brief This operator check if the first object is smaller than the second.
 * \attention : we worried only to the parameter currentNumber.
 * \param circularInt
 * \return true if it's smaller, false if not.
 */
bool CircularInt::operator <(CircularInt const& circularInt)const {
    if(currentNumber < circularInt.getCurrentNumber())
        return true ;
    return false ;
}

/**
 * \brief This operator check if the first object is bigger than the second.
 * \attention : we worried only to the parameter currentNumber.
 * \param circularInt
 * \return true if it's bigger, false if not.
 */
bool CircularInt::operator >(CircularInt const& circularInt)const {
    if(currentNumber > circularInt.getCurrentNumber())
        return true ;
    return false ;
}
/**
 * \brief This operator check if the first object is bigger or equal than the second.
 * \attention : we worried only to the parameter currentNumber.
 * \param circularInt
 * \return true if it's bigger or equal, false if not.
 */
bool CircularInt::operator >=(CircularInt const& circularInt)const {
    if(currentNumber >= circularInt.getCurrentNumber())
        return true ;
    return false ;
}
/**
 * \brief This operator check if the first object is smaller or equal than the second.
 * \attention : we worried only to the parameter currentNumber.
 * \param circularInt
 * \return true if it's smaller or equal, false if not.
 */
bool CircularInt::operator <=(CircularInt const& circularInt)const {
    if(currentNumber <= circularInt.getCurrentNumber())
        return true ;
    return false ;
}


//Getters

/**
 * \brief getter for the currentNumber.
 * \return the currentNumber.
 */
int CircularInt::getCurrentNumber() const {
    return currentNumber;
}

/**
 * \brief getter for the minimum.
 * \return the minimum.
 */
int CircularInt::getMinimum() const {
    return minimum;
}

/**
 * \brief getter for the maximum.
 * \return the maximum.
 */
int CircularInt::getMaximum() const {
    return maximum;
}

// Setter

/**
 * \brief setter for the currentNumber.
 * \param numb
 * \void method
 */
void CircularInt::setCurrentNumber(int numb) {
    currentNumber = numb;
    moduloOperation();
}


//privates methods.

//friends operators.

/**
 * \brief This friend operator print. (As toString in Java).
 * \param os
 * \param circularInt
 * \return os.
 * Complexity : O(1).
 */
ostream& operator<<(ostream& os, const CircularInt& circularInt) {
    os << circularInt.currentNumber;
    return os;
}

/**
 * \brief This operator acts as integer - currentNumber.
 * \param decrement
 * \param circularInt
 * \return circularInt.
 * Complexity : O(1).
 */
CircularInt operator- (const int decrement, const CircularInt& circularInt) {
    CircularInt answer = circularInt;
    answer.currentNumber = decrement - circularInt.currentNumber;
    answer.currentNumber = answer.moduloOperation();
    return answer;
}

/**
 * \brief This operator acts as a.currentNumber + b.currentNumber.
 * \param circularInt1
 * \param circularInt2
 * \return circularInt.
 * Complexity : O(1).
 */
CircularInt operator+ (const CircularInt& circularInt1, const CircularInt& circularInt2) {
    CircularInt circularInt = circularInt1;
    circularInt.currentNumber = circularInt1.currentNumber + circularInt2.currentNumber;
    circularInt.currentNumber = circularInt.moduloOperation();
    return circularInt;
}

//helps functions.

/**
 * \brief this inline function is the most important function.
 * Given a natural number x, and a definition space, we find a formula which find a new
 * number y such that x % circle = y % circle and y is include in the definition space.
 * For a definition space {a, b} and an integer x we have :
 * the formula is : currentNumber + (ceil(b - currentNumber) / (b - a + 1)) * (b - a + 1).
 * \return the number with the same remainder modulo circle but in the definition space.
 * Complexity : O(1).
 */
int CircularInt::moduloOperation() {
    return currentNumber + (ceil(((double) minimum - (double) currentNumber) / (double) circle))* circle;
}

/**
 * \brief this help function is calculate the modulo inverse of the divisor.
 * source : https://www.geeksforgeeks.org/modular-division/
 * \param divisor
 * \return the modular inverse.
 */
int CircularInt::modInverse(int divisor) {
    int x, y;
    int g = gcdExtended(divisor, circle, &x, &y);
    if (g != 1)
        return -1;
    return (x % circle + circle) % circle;
}

/**
 * \brief this help function is calculate the grand common divisor.
 * source : https://www.geeksforgeeks.org/modular-division/
 * \param divisor
 * \param number
 * \param divisor
 * \param x
 * \param y
 * \return the gcd.
 */
 int CircularInt::gcdExtended(int number, int divisor, int *x, int *y) {
    if (number == 0) {
        *x = 0, *y = 1;
        return divisor;
    }
    int x1, y1;
    int gcd = gcdExtended(divisor % number, number, &x1, &y1);
    *x = y1 - (divisor / number) * x1;
    *y = x1;
    return gcd;
}

/**
 * \brief Constructor of the exception NotDivisible.
 * \param circularInt
 * \param divisor
 * The error message is here built.
 */
NotDivisible::NotDivisible(CircularInt circularInt, int divisor): runtime_error("") {
    stringstream ss;
    ss <<
    "There is no number x in {" <<
    circularInt.getMinimum() <<
    ", " <<
    circularInt.getMaximum() <<
    "} such that x * " <<
    divisor <<
    " = " <<
    circularInt.getCurrentNumber();
    static_cast<runtime_error&>(*this) = runtime_error(ss.str());
}
