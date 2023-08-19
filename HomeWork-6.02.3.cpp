#include <iostream>
#include <mutex>

class Data {
public:
    Data(int aa, char bb) : a{ aa }, b{ bb } {};
    int a;
    char b;
    std::mutex mx;
};

void print_data(const Data& d) {
    std::cout << "a: " << d.a << "; b: " << d.b << std::endl;
}  

void swap1(Data& d1, Data& d2) {
    d1.mx.lock();
    d2.mx.lock();
    auto tmp_a = d1.a;
    auto tmp_b = d1.b;
    d1.a = d2.a;
    d1.b = d2.b;
    d2.a = tmp_a;
    d2.b = tmp_b;
    d1.mx.unlock();
    d2.mx.unlock();
}

void swap2(Data& d1, Data& d2) {
    std::scoped_lock(d1.mx, d2.mx);
    auto tmp_a = d1.a;
    auto tmp_b = d1.b;
    d1.a = d2.a;
    d1.b = d2.b;
    d2.a = tmp_a;
    d2.b = tmp_b;

}

void swap3(Data& d1, Data& d2) {
    std::unique_lock(d1.mx);
    std::unique_lock(d2.mx);
    auto tmp_a = d1.a;
    auto tmp_b = d1.b;
    d1.a = d2.a;
    d1.b = d2.b;
    d2.a = tmp_a;
    d2.b = tmp_b;

}


int main()
{
    Data d1(1, 'a');
    Data d2(2, 'b');
    std::cout << "Initial data: " << std::endl;
    print_data(d1);
    print_data(d2);
    std::cout << "Swap 1 data: " << std::endl;
    swap1(d1, d2);
    print_data(d1);
    print_data(d2);
    std::cout << "Swap 2 data: " << std::endl;
    swap2(d1, d2);
    print_data(d1);
    print_data(d2);
    std::cout << "Swap 3 data: " << std::endl;
    swap3(d1, d2);
    print_data(d1);
    print_data(d2);
}
