#include <iostream>
#include <vector>
#include <cassert>
#include "stack.h"

/**
 * @brief Class customizzata di double per testare le funzioni dello stack
*/
class doubleCustom {

public:
    doubleCustom(double d) : d(d) {}
    doubleCustom(): d(0) {}
    doubleCustom(const doubleCustom &other) : d(other.d) {}
    doubleCustom(doubleCustom &&other) : d(other.d) {}
    ~doubleCustom() {}

    operator double() const {
        return d;
    }
    
    doubleCustom &operator=(const doubleCustom &other) {
        d = other.d;
        return *this;
    }

    bool operator==(const doubleCustom &other) const {
        return d == other.d;
    }

    double getD() const {
        return d;
    }

private:
    double d;
};

/**
 * @brief Class customizzata di User(name, age) per testare le funzioni dello stack
*/
class userCustom {

public:
    userCustom(std::string name, unsigned int age) : name_(name), age_(age) {}
    userCustom(): name_(""), age_(0) {}
    userCustom(const userCustom &other) : name_(other.name_), age_(other.age_) {}
    userCustom(userCustom &&other) : name_(other.name_), age_(other.age_) {}
    ~userCustom() {}

    operator std::string() const {
        return name_;
    }
    
    userCustom &operator=(const userCustom &other) {
        name_ = other.name_;
        age_ = other.age_;
        return *this;
    }

    bool operator==(const userCustom &other) const {
        return name_ == other.name_ && age_ == other.age_;
    }

    std::string getName() const {
        return name_;
    }

    unsigned int getAge() const {
        return age_;
    }

    // ridefinizione dell'operatore di output per la classe userCustom
    friend std::ostream& operator<<(std::ostream& os, const userCustom& uc) {
        os << "(" << uc.getName() << " " << uc.getAge() << ")";
        return os;
    }

private:
    std::string name_;
    unsigned int age_;
};

/**
 * @brief Funzione di test di creazione e assegnamento per lo stack di tipo T
*/
void testCreazioneAssegnamento() {
    std::cout << "----- Creazione, assegnamento e confronto stack tipo T -----" << std::endl;
    
    // Stack con costruttore di default senza parametri
    Stack<int> s1;
    assert(s1.max_size() == 0);
    assert(s1.empty());

    // Stack con costruttore di default con parametri
    Stack<int> s2(5);
    assert(s2.max_size() == 5);
    assert(s2.empty());

    std::vector<int> v = {5, 10, 15, 20, 25};

    s2.fill(v.begin(), v.end());

    assert(s2.top() == 25);
    assert(s2.full());

    Stack<std::string> ss(5);

    ss.push("progetto");
    ss.push("di");
    ss.push("c++");

    std::cout << "Stack ss (string con parametri + push()): " << ss << std::endl;

    // Stack con costruttore di copia
    Stack<int> s3(s2);

    Stack<doubleCustom> s4(3);
    assert(s4.max_size() == 3);
    assert(s4.empty());

    std::vector<doubleCustom> v4 = {doubleCustom(5), doubleCustom(10), doubleCustom(15)};
    s4.fill(v4.begin(), v4.end());

    doubleCustom d(15);

    assert(s4.top() == d);
    assert(s4.full());

    Stack<doubleCustom> s5(s4);

    std::vector<doubleCustom> v5 = {doubleCustom(1), doubleCustom(2), doubleCustom(3)};

    s5.fill(v5.begin(), v5.end());

    std::cout << "Stack s1 (senza parametri): " << s1 << std::endl;

    std::cout << "Stack s2 (con parametri + fill()): " << s2 << std::endl;

    std::cout << "Stack s3 (costruttore di copia): " << s3 << std::endl;

    std::cout << "Stack s4 (con tipo custom double + fill()): " << s4 << std::endl;

    std::cout << "Stack s5 (copia da s4, customDouble sovrascritti con fill()): " << s5 << std::endl;

    Stack<int> s9 = s2;

    assert(s9 == s2);

    std::cout << "Stack s9 (assegnamento da s2): " << s9 << std::endl;
}

/**
 * @brief Funzione di test di push e pop per lo stack di tipo T
*/
void testSvuotamento() {
    std::cout << "----- Svuotamento stack tipo T -----" << std::endl;

    // Stack con costruttore di default con parametri
    Stack<char> s1(7);

    std::vector<char> v = {'a', '?', '2', '#', 'B', 'T', 'S'};

    s1.fill(v.begin(), v.end());

    std::cout << "Stack s1 pieno (char con parametri + fill()): " << s1 << std::endl;

    char a = s1.pop();

    char b = s1.pop();

    char c = s1.top();

    std::cout << "Pop di " << a << " e " << b << ", inoltre il top in questo momento é: " << c << std::endl << std::endl;

    s1.clear();

    assert(s1.empty());

    std::cout << "Stack s1 vuoto dopo il clear: " << s1 << std::endl;

    std::vector<userCustom> v2 = {userCustom("Mario", 25), userCustom("Luigi", 30), userCustom("Pippo", 35)};

    // Stack con costruttore di default con parametri
    Stack<userCustom> s2(v2.begin(), v2.end());

    std::cout << "Stack s2 pieno (userCustom con iteratori): " << s2 << std::endl;

    s2.pop();

    std::cout << "Stack s2 dopo il pop: " << s2 << std::endl;

    s2.clear();

    assert(s2.empty());

    std::cout << "Stack s2 vuoto dopo il clear: " << s2 << std::endl;
}

/**
 * @brief Funzione di test di push e pop per lo stack di tipo T con iteratori
*/
void testCostruttoreIterato() {
    std::cout << "----- Costruttore iterato stack tipo T -----" << std::endl;

    std::vector<int> v = {5, 10, 15, 20, 25, 30, 35};

    // Stack con costruttore con iteratori
    Stack<int> s1(v.begin(), v.end());

    std::cout << "Stack s1 pieno (con iteratori): " << s1 << std::endl;

    s1.clear();

    assert(s1.empty());

    std::cout << "Stack s1 vuoto dopo il clear: " << s1 << std::endl;

    std::vector<int> v2 = {9, 8, 7, 6, 5, 4, 3};

    Stack<int> s2(v2.begin(), v2.end());

    Stack<int>::const_iterator start = s2.begin();
    Stack<int>::const_iterator end = s2.end();

    std::cout << "Lettura con iteratore di s2 (da fondo a cima): " << std::endl;

    std::cout << "[ ";
    for (; start != end; ++start) {
        std::cout << *start << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl << std::endl;

}

/**
 * @brief Funzione di test di lettura con iteratore read only per lo stack di tipo T
*/
void testLetturaOnlyStack() {
    std::cout << "----- Lettura con iteratore stack tipo T -----" << std::endl;

    std::vector<int> v = {5, 10, 15, 20, 25, 30, 35};

    // Stack con costruttore con iteratori
    Stack<int> s1(v.begin(), v.end());

    std::cout << "Stack s1 pieno (int con iteratori): " << s1 << std::endl;
    std::cout << "Lettura con iteratore read only (da cima a fondo): " << std::endl;

    Stack<int>::readOnlyIterator start = s1.readOnlyBegin();
    Stack<int>::readOnlyIterator end = s1.readOnlyEnd();

    std::cout << "[ ";
    while (start != end) {
        std::cout << *start << " ";
        start++;
    }
    // std::cout << *start << " ";
    std::cout << "]" << std::endl << std::endl;

    std::vector<userCustom> v2 = {userCustom("Mario", 20), 
                                  userCustom("Pippo", 21), 
                                  userCustom("Luigi", 22)};

    // Stack con costruttore con iteratori
    Stack<userCustom> s2(v2.begin(), v2.end());

    std::cout << "Stack s2 pieno (userCustom con iteratori): " << s2 << std::endl;
    std::cout << "Lettura con iteratore read only (da cima a fondo): " << std::endl;

    Stack<userCustom>::readOnlyIterator start2 = s2.readOnlyBegin();
    Stack<userCustom>::readOnlyIterator end2 = s2.readOnlyEnd();

    std::cout << "[ ";
    while (start2 != end2) {
        std::cout << *start2 << " ";
        start2++;
    }
    // std::cout << *start2 << " ";
    std::cout << "]" << std::endl << std::endl;
}

/**
 * @brief Funtore per il checkif()
*/
struct biggerThan5 {
    bool operator()(int i) const {
        return i > 5;
    }
};

/**
 * @brief Funtore per il checkif()
*/
struct isOdd {
    bool operator()(int i) const {
        return i % 2 != 0;
    }
};

/**
 * @brief Funtore per il checkif()
*/
struct ageBiggerThan20 {
    bool operator()(userCustom u) const {
        return u.getAge() > 20;
    }
};

/**
 * @brief Funtore per il checkif()
*/
struct nameIsLuigi {
    bool operator()(userCustom u) const {
        return u.getName() == "Luigi";
    }
};

/**
 * @brief Funtore per il checkif()
*/
struct nameIsPippo {
    bool operator()(userCustom u) const {
        return u.getName() == "Pippo";
    }
};

/**
 * @brief Funzione di test del checkif() per elementi dello stack di tipo T
*/
void testCheckif() {
    std::cout << "----- Checkif stack tipo T -----" << std::endl;

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};

    // Stack con costruttore con iteratori
    Stack<int> s1(v.begin(), v.end());

    std::cout << "Stack s1 pieno (con iteratori): " << s1 << std::endl;

    std::cout << "test elemento top() int > 5" << std::endl << std::endl;
    // assert del checkif() con funtore
    assert(s1.checkif(biggerThan5(), s1.top()));

    s1.pop();

    assert(s1.checkif(isOdd(), s1.top()));

    std::vector<userCustom> v2 = {userCustom("Mario", 20), 
                                  userCustom("Pippo", 21), 
                                  userCustom("Luigi", 22)};

    Stack<userCustom> s2(v2.begin(), v2.end());

    std::cout << "Stack s2 pieno (userCustom con iteratori): " << s2 << std::endl;

    std::cout << "test elemento top() userCustom age > 20" << std::endl;
    assert(s2.checkif(ageBiggerThan20(), s2.top()));

    std::cout << "test elemento top() userCustom name == Luigi" << std::endl;
    assert(s2.checkif(nameIsLuigi(), s2.top()));

    userCustom luigi = s2.pop();

    std::cout << "test elemento top() userCustom name == Pippo (dopo il pop)" << std::endl;
    assert(s2.checkif(nameIsPippo(), s2.top()));
}

int main() {
    testCreazioneAssegnamento();
    testSvuotamento();
    testCostruttoreIterato();
    testLetturaOnlyStack();
    testCheckif();
    return 0;
}