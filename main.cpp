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
};
int main() {

      //for int
//    Container<int> s1;
//    std::vector<int> v = {1,2,3,4,3,2,2,8};
//    std::cout << v.capacity() << std::endl;
//    std::vector<int> v2 = {21, 23, 22, 50, 250, 35};
//    s1.erase_remove(v, 2);
    //s1.erase_remove_if(v2);

    Container<A> s1;
    std::vector<A> v;
    v.emplace_back(11);
    v.emplace_back(315);
    v.emplace_back(2);
    v.emplace_back(2);
    v.emplace_back(32);
    std::cout << "\n\n";
    std::cout << "vector ready\n\n";
//    s1.erase_remove(v, A(35));
    s1.erase_remove_if(v);
    return 0;
}
