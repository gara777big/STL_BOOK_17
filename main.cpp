#include <iostream>
#include <vector>
#include <algorithm>
class A{
public:
    int x;
    explicit A(int x_):x(x_) {std::cout << x << " A(int)\n";}
    A(const A& other) {std::cout << "copy A()\n"; x = other.x;}
    A(A&& other) noexcept {std::cout << "move A()\n"; x = other.x;}
    A& operator = (const A& other){
        std::cout << "copy assigment operator A()\n";
        x = other.x; return *this;
    }
    A& operator = (A&& other) noexcept{
        std::cout << "move assigment operator A()\n";
        x = other.x; return *this;
        other.x = 0;
    }
    bool operator == (const A& other) const {
        return this->x == other.x;
    }
    ~A() {std::cout << x << " ~A()\n";}
};
template <typename T>
struct Container{
    void erase_remove(std::vector<T>& v, const T& val){
        std::cout << "f1\n";
        const auto new_end(remove(v.begin(), v.end(), val));
        std::cout << "f2\n";
        v.erase(new_end, v.end());
        std::cout << "f3\n";
        for(auto& i : v){
            std::cout << i.x << " ";
        }
        std::cout << std::endl;
        v.shrink_to_fit();
        std::cout << "f4\n";
    }
    void erase_remove_if(std::vector<T>& v){
        const auto odd([](T& val) { return val.x % 2 != 0;});
        std::cout << "f1\n";
        v.erase(remove_if(v.begin(), v.end(), odd), v.end());
        std::cout << "f2\n";
        for(auto& i : v){
            std::cout << i.x << " ";
        }
        std::cout << std::endl;
        v.shrink_to_fit();
        std::cout << "f4\n";
    }

    void quick_remove_at(std::vector<T>& v, size_t _index){
          if (_index < v.size()) {
              v[_index] = std::move(v.back());
              v.pop_back();
          }
    }
    void quick_remove_at(std::vector<T>& v, typename std::vector<T>::iterator  it){
            if (it != v.end()){
                *it = std::move(v.back());
                v.pop_back();
            }
    }
    void delete_from_vectoO1_index(std::vector<T>& v, size_t _index)
    {
         quick_remove_at(v, _index);
         for(auto& i : v)
         {
             std::cout << i.x << " ";
         }
         std::cout << "\n";
    }
    void delete_from_vecto01_iterator(std::vector<T>& v, typename std::vector<T>::iterator it){
        quick_remove_at(v, it);
        for(auto& i : v)
        {
            std::cout << i.x << " ";
        }
    }

};
int main() {

//erase-remove(remove_if)
/*
    Container<int> s1;
    std::vector<int> v = {1,2,3,4,3,2,2,8};
    std::cout << v.capacity() << std::endl;
    std::vector<int> v2 = {21, 23, 22, 50, 250, 35};
    s1.erase_remove(v, 2);
    s1.erase_remove_if(v2);
    Container<A> s1;
    std::vector<A> v;
    v.emplace_back(11);
    v.emplace_back(315);
    v.emplace_back(2);
    v.emplace_back(2);
    v.emplace_back(32);
    std::cout << "\n\n";
    std::cout << "vector ready\n\n";
    s1.erase_remove_if(v);
*/
//delete from vector O(1)
//for int
//    std::vector<int> v = {32, 31, 12, 354, 596};
//    Container<int> s1;
//    s1.delete_from_vectoO1(v, 2);
//for A

//    Container<A> s1;
//    std::vector<A> v;
//    v.emplace_back(65);
//    v.emplace_back(546);
//    v.emplace_back(212);
//    v.emplace_back(542);
//    v.emplace_back(326);
//    v.emplace_back(1124);
//    std::cout << "\n\n";
//    std::cout << "vector ready\n\n";
//    std::cout << "\n\n";
//    s1.delete_from_vectoO1_index(v, 3);
//    //push_back, erase, clear not call reallocation
//    s1.delete_from_vecto01_iterator(v, v.begin());

    const size_t container_size = 100;
    std::vector<int> v(container_size, 43);
    std::cout << v[container_size + 324] << std::endl;
    try {
        std::cout << v.at(container_size + 3243) << std::endl;
    }catch (std::out_of_range&  e){
         std::cout << e.what() << std::endl;
    }

    return 0;
}
