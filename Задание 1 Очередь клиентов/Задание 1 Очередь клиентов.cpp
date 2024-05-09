// Задание 1 Очередь клиентов.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>

std::atomic_int Cl_count = 0;


void Clients(int Cl_max) {
    while (Cl_max > Cl_count) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        Cl_count++;
        std::cout << "Добавлен новый клиент! Клиенты: " << Cl_count << std::endl;
    }
}

void Operator() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (Cl_count > 0) {
            std::cout << "Оператор завершил работу с клиентом! Клиенты: " << Cl_count << std::endl;
            Cl_count--;
        }
        else {
            std::cout << "Оператор завершил работу! Клиенты: " << Cl_count << std::endl;
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");

    int Cl_max = 0;
    

    std::cout << "Введите количество клиентов: ";
    std::cin >> Cl_max;

    std::thread c(Clients, Cl_max);
    std::thread o(Operator);

    c.join();
    o.join();

}
