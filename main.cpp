#include <iostream>
#include "mystack.h"
#include "pentagon.h"
#include <algorithm>
#include "myallocator.h"
#include <map>
void menu() {
    std::cout << "1 - add(1 - push, 2 - insert  by iterator(enter index new elem)\n"
                 "2 - delete(1 - pop, 2 - delete by iterator(enter index)\n"
                 "3 - top\n"
                 "4 - print\n"
                 "5 - count if(enter max area)\n"
                 "6 - exit\n";
}

void usingStack() {
    int command, minicommand,index;
    double val;
    cntr::Stack<pentagon<double>,myal::my_allocator<pentagon<double>,10000>> st;
    for (;;) {
        std::cin >> command;
        if (command == 1) {
            std::cin >> minicommand;
            if (minicommand == 1) {
                pentagon<double> p(std::cin);
                st.Push(p);
            } else if (minicommand == 2) {
                std::cin >> index;
                try {
                    pentagon<double> p(std::cin);
                    st.Insert(index,p);

                } catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                    continue;
                }
            }
        } else if (command == 6) {
            break;
        } else if (command == 2) {
            std::cin >> minicommand;
            if (minicommand == 1) {
                try {
                    st.Pop();
                } catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                    continue;
                }
            }
            if (minicommand == 2) {
                std::cin >> index;
                try {
                    if (index < 0 || index > st.Size) {
                        throw std::logic_error("Out of bounds\n");
                    }
                    auto it = st.begin();
                    for (int i = 0; i < index; ++i) {
                        ++it;
                    }
                    st.Erase(it);
                }
                catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                    continue;
                }
            }
        } else if (command == 3) {
            try {
                st.Top().print(std::cout);
            }
            catch (std::logic_error &e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        } else if (command == 4) {
            for (auto elem: st) {
                elem.print(std::cout);
            }
        } else if (command == 5) {
            std::cin >> val;
            std::cout << std::count_if(st.begin(), st.end(), [val](pentagon<double> r) { return r.area() < val; })
                      << std::endl;
        } else {
            std::cout << "Error command\n";
            continue;
        }
    }
}

int main() {
    //menu();
    //usingStack();
    std::map<int, int, std::less<int>,
    myal::my_allocator<std::pair<const int, int>, 100>> mp;
    for(int i = 0; i < 2; ++i){
        mp[i] = i * i;
    }
    for(int i = 2; i < 10; ++i){
        mp.erase(i - 2);
        mp[i] = i * i;
    }
    for (auto elem : mp) {
        std::cout << elem.first;
    }
    return 0;
}