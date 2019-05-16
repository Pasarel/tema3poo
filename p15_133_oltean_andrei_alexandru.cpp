#include <iostream>
#include <string>
#include <list>

using namespace std;

class Vector {
    int *a;
public:
    Vector();
    Vector(int n);
    Vector(int size, int spareme);
    Vector(const Vector& vec);
    ~Vector();    
    int getNth(int n);
    void setNth(int n, int x);
    int size();
    void operator=(const Vector& vec);
    friend istream& operator>>(istream& input, Vector& vec);
    friend ostream& operator<<(ostream& output, const Vector& vec);
};

Vector::Vector() {
    a = NULL;
}

Vector::Vector(int n) {
    int aux = n;
    int count = 0;
    int i = 0;
    while (aux) {
        count++;
        aux = aux / 10;
    }
    a = new int[count + 1];
    a[0] = count;
    while (n) {
        a[count - i] = n % 10;
        n /= 10;
        i++;
    }
}

Vector::Vector(int size, int spareme) {
    a = new int[size + 1];
    a[0] = size;
    spareme++;
}

Vector::Vector(const Vector& vec) {
    this->a = new int[vec.a[0] + 1];
    for (int i = 0; i <= vec.a[0]; i++) {
        this->a[i] = vec.a[i];
    }
}

Vector::~Vector() {
    if (a != NULL)
        delete[] a;
    a = NULL;
}

void Vector::operator=(const Vector& vec) {
    if (a != NULL)
        delete[] this->a;
    this->a = new int[vec.a[0] + 1];
    for (int i = 0; i <= vec.a[0]; i++) {
        this->a[i] = vec.a[i];
    }
}

istream& operator>>(istream& input, Vector& vec) {
    string read;
    input >> read;
    vec.a = new int[read.size() + 1];
    vec.a[0] = read.size();
    for (int i = 1; i <= read.size(); i++) {
        vec.a[i] = read[i - 1] - '0';
    }
    return input;
};

ostream& operator<<(ostream& output, const Vector& vec) {
    int size = vec.a[0];
    for (int i = 1; i <= size; i++) {
        output << vec.a[i];
    }
    return output;
};

int Vector::getNth(int n) {
    return a[n];
}

void Vector::setNth(int n, int x) {
    a[n] = x;
}

int Vector::size() {
    return a[0];
}

class Nr_Natural_Mare {
protected:
    int nrcif;
    Vector V;
    Nr_Natural_Mare sum(const Nr_Natural_Mare& other);
    void assign(const Nr_Natural_Mare& other);
    int isnot(Nr_Natural_Mare& other);
public:
    Nr_Natural_Mare();
    Nr_Natural_Mare(int n);
    Nr_Natural_Mare(const Nr_Natural_Mare& nr);
    ~Nr_Natural_Mare();
    virtual void print();
    void operator=(const Nr_Natural_Mare& mare);
    friend istream& operator>>(istream& input, Nr_Natural_Mare& mare);
    friend ostream& operator<<(ostream& output, const Nr_Natural_Mare& mare);
};

Nr_Natural_Mare::Nr_Natural_Mare() {
    nrcif = 0;
}

Nr_Natural_Mare::Nr_Natural_Mare(int n) {
    Vector aux(n);
    V = aux;
    nrcif = V.size();
}

Nr_Natural_Mare::Nr_Natural_Mare(const Nr_Natural_Mare& nr) {
    Vector aux = nr.V;
    this->V = nr.V;
    this->nrcif = nr.nrcif;
}

Nr_Natural_Mare::~Nr_Natural_Mare() {
    // functia aceasta apeleaza automat destructorul lui Vector V
    // altceva decat de eliberat memoria alocata pentru vector nu mai e de facut
    // deci destructorul acesta este gol
    // l-am scris numai pentru ca cerinta cere ca toate clasele sa aiba un destructor
}

void Nr_Natural_Mare::assign(const Nr_Natural_Mare& a) {
    this->V = a.V;
    this->nrcif = a.nrcif;
}

void Nr_Natural_Mare::operator=(const Nr_Natural_Mare& a) {
    assign(a);
}

int Nr_Natural_Mare::isnot(Nr_Natural_Mare& other) {
    if (this->nrcif != other.nrcif)
        return 1;
    for (int i = 1; i <= other.nrcif; i++) {
        if (this->V.getNth(i) != other.V.getNth(i))
            return 1;
    }
    return 0;
}

Nr_Natural_Mare Nr_Natural_Mare::sum(const Nr_Natural_Mare& other) {
    int check = (this->nrcif > other.nrcif);
    Nr_Natural_Mare rez = (check) ? *this : other;
    Nr_Natural_Mare& add = (check) ? (Nr_Natural_Mare&) other : *this;
    int i = rez.nrcif;
    int j = add.nrcif;
    int aux = 0;
    int save;
    while (i && j) {
        save = rez.V.getNth(i);
        rez.V.setNth(i, (rez.V.getNth(i) + add.V.getNth(j) + aux) % 10);
        aux = (save + add.V.getNth(j) + aux) / 10;
        i--;
        j--;
    }
    while (i) {
        save = rez.V.getNth(i);
        rez.V.setNth(i, (rez.V.getNth(i) + aux) % 10);
        aux = (save + aux) / 10;
        i--;
    }
    // fuckin hell:
    if (aux) {
        int count = 0;
        int work = 0;
        int newaux = aux;
        while (newaux) {
            save = work;
            work = (work + newaux) % 10;
            newaux = (work + newaux) / 10;
            count++;
        }
        Vector dirty(rez.nrcif + count, 3453493);
        Nr_Natural_Mare actual_rez;
        actual_rez.V = dirty;
        actual_rez.V.setNth(count, 0);
        for (i = count; i > 0; i--) {
            save = actual_rez.V.getNth(i);
            actual_rez.V.setNth(i, (actual_rez.V.getNth(i) + aux) % 10);
            aux = (save + aux) / 10;
        }
        for (i = count + 1; i <= rez.nrcif + count; i++) {
            actual_rez.V.setNth(i, rez.V.getNth(i - count));
        }
        actual_rez.V.setNth(0, rez.nrcif + count);
        actual_rez.nrcif = rez.nrcif + count;
        rez = actual_rez;
    }
    return rez;
}

void Nr_Natural_Mare::print() {
    cout << *this;
}

istream& operator>>(istream& input, Nr_Natural_Mare& mare) {
    input >> mare.V;
    mare.nrcif = mare.V.size();
    return input;
}

ostream& operator<<(ostream& output, const Nr_Natural_Mare& mare) {
    output << mare.V;
    return output;
}

class Numar_Fibonacci_mare: public Nr_Natural_Mare {
    friend istream& operator>>(istream& input, Numar_Fibonacci_mare& fib);
    friend ostream& operator<<(ostream& output, const Numar_Fibonacci_mare& fib);
public:
    Numar_Fibonacci_mare():Nr_Natural_Mare() {};
    Numar_Fibonacci_mare(int n):Nr_Natural_Mare(n) {};
    ~Numar_Fibonacci_mare(){};
    void operator=(const Numar_Fibonacci_mare& other);
    void print();
};

istream& operator>>(istream& input, Numar_Fibonacci_mare& fib) {
    input >> fib.V;
    fib.nrcif = fib.V.size();
    return input;
}

ostream& operator<<(ostream& output, const Numar_Fibonacci_mare& fib) {
    output << fib.V;
    return output;
}

void Numar_Fibonacci_mare::print() {
    cout << *this << endl;
    cout << "Suma Fibonacci:" << endl;
    Numar_Fibonacci_mare prev = 1;
    Numar_Fibonacci_mare curr = 1;
    Numar_Fibonacci_mare aux;
    Numar_Fibonacci_mare check;
    check.assign(curr.sum(prev));
    while (check.isnot(*this)) {
        aux.assign(curr);
        curr.assign(prev.sum(curr));
        prev.assign(aux);
        check.assign(curr.sum(prev));
    }
    cout << prev << " + " << curr << endl;
}

int main() {
    Numar_Fibonacci_mare a;
    cin >> a;
    a.print();
    return 0;
}
