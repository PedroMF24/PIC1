#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <functional>
#include <unordered_map>

#include <type_traits>

// Compile like this: g++ -std=c++17 MapGPT_test.cpp -o MyMaps.exe

using namespace std;

class KeyNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Key not found in map";
    }
};

/*
// Throw exception if T doesn't have output operator<<
template <typename T>
void throw_if_no_output_operator() {
    if constexpr (!has_output_operator<T>::value) {
        throw std::runtime_error("Value type does not have output operator<< overloaded");
    }
}

template<typename T>
class has_output_operator
{
    template<typename U>
    static constexpr auto test(U* p) -> decltype(std::declval<std::ostream&>() << *p, bool{}) { return true; }
    
    template<typename U>
    static constexpr bool test(...) { return false; }
    
public:
    static constexpr bool value = test<T>(nullptr);
};*/

template<typename KeyType, typename ValueType>
class MyMap : public KeyNotFoundException {
public:
    // constructor
    MyMap() = default;
    ~MyMap() = default;

    // method to Insert a key-value pair into the map
    void Insert(KeyType key, ValueType value) {
        myMap[key] = value;
    }

    // method to get the value associated with a key in the map
    ValueType Get(KeyType key) {
        if (myMap.count(key)) {
            return myMap[key];
        } else {
            throw KeyNotFoundException();
        }
    }
    // ValueType Get(KeyType key) {
    //     if (myMap.count(key)) {
    //         return myMap[key];
    //     } else {
    //         cerr << "**Error: Key " << key << " does not exist in map" << endl;
    //         exit(0); 
    //     }
    // }

    // Return a const reference to the map
    const std::map<KeyType, ValueType>& GetMap() const {
        return myMap;
    }

    // friend std::ostream& operator<<(std::ostream& os, const MyMap& map) {
    //     for (const auto& pair : map.myMap) {
    //         os << "(" << pair.first << ", " << pair.second << ") ";
    //     }
    //     return os;
    // }

    friend std::ostream& operator<<(std::ostream& os, const MyMap& map) {
        for (const auto& pair : map.myMap) {
            os << "(" << pair.first << ", ";

            if constexpr (std::is_same_v<ValueType, std::vector<double>>) {
                os << "[ ";
                for (const auto& v : pair.second) {
                    os << v << " ";
                }
                os << "]";
            }
            else {
                os << pair.second;
            }

            os << ") ";
        }
        return os;
    }

    // operator+ overload for element-wise addition of two maps
    template<typename OtherValueType>
    MyMap<KeyType, ValueType> operator+(const MyMap<KeyType, OtherValueType>& other) const {
        static_assert(is_same_v<ValueType, OtherValueType>, "Map value types must be the same.");
        MyMap<KeyType, ValueType> result;
        set_union(myMap.begin(), myMap.end(), other.myMap.begin(), other.myMap.end(),
                        std::inserter(result.myMap, result.myMap.begin()));
        return result;
    }

private:
    map<KeyType, ValueType> myMap;
};


template<typename KeyType, typename ValueType>
class MyUnorderedMap : public KeyNotFoundException { // public has_output_operator {
public:
    // constructor
    MyUnorderedMap() = default;
    ~MyUnorderedMap() = default;

    // method to Insert a key-value pair into the unordered map
    void Insert(KeyType key, ValueType value) {
        myUnorderedMap[key] = value;
    }

    // method to get the value associated with a key in the unordered map
    ValueType Get(KeyType key) {
        if (myUnorderedMap.count(key)) {
            return myUnorderedMap[key];
        } else {
            throw KeyNotFoundException();
        }
    }
    // ValueType Get(KeyType key) {
    //     if (myUnorderedMap.count(key)) {
    //         return myUnorderedMap[key];
    //     } else {
    //         cerr << "**Error: Key " << key << " does not exist in map" << endl;
    //         exit(0);
    //     }
    // }

    // // Return a const reference to the map
    // const std::unordered_map<KeyType, ValueType>& GetMap() const {
    //     return myUnorderedMap;
    // }

    // friend std::ostream& operator<<(std::ostream& os, const MyUnorderedMap& map) {
    //     for (const auto& [key, value] : map.myUnorderedMap) {
    //         os << "(" << key << ", " << value << ") ";
    //     }
    //     return os;
    // }

    // Return a const reference to the unordered map
    const std::unordered_map<KeyType, ValueType>& GetUnorderedMap() const {
        return myUnorderedMap;
    }

    // operator+ overload for element-wise addition of two maps
    template<typename OtherValueType>
    MyUnorderedMap<KeyType, ValueType> operator+(const MyUnorderedMap<KeyType, OtherValueType>& other) const {
        static_assert(is_same_v<ValueType, OtherValueType>, "Map value types must be the same.");
        MyUnorderedMap<KeyType, ValueType> result;
        set_union(myUnorderedMap.begin(), myUnorderedMap.end(), other.myUnorderedMap.begin(), other.myUnorderedMap.end(),
                        std::inserter(result.myUnorderedMap, result.myUnorderedMap.begin()));
        return result;
    }

    // operator<< overload for printing the unordered map
    friend std::ostream& operator<<(std::ostream& os, const MyUnorderedMap& map) {
        for (const auto& pair : map.myUnorderedMap) {
            os << "(" << pair.first << ", ";

            if constexpr (std::is_same_v<ValueType, std::vector<double>>) {
                os << "[ ";
                for (const auto& v : pair.second) {
                    os << v << " ";
                }
                os << "]";
            }
            else {
                // try {
                    // throw_if_no_output_operator<ValueType>();
                    os << pair.second;
                // } catch (std::runtime_error& e) {
                    // std::cerr << "**Error: Entry in map does not have operator '<<' overloaded" << std::endl;
                    // std::cerr << e.what() << std::endl;
                    // exit(1);
                // }
            }
            os << ") ";
        }
        return os;
    }
    private:
    std::unordered_map<KeyType, ValueType> myUnorderedMap;
};






void TestMyMaps() {
    // Testing MyMap
std::cout << "Testing MyMap" << std::endl;
MyMap<int, std::string> myMap;
myMap.Insert(1, "one");
myMap.Insert(2, "two");
myMap.Insert(3, "three");
myMap.Insert(4, "four");
std::cout << myMap << std::endl;
std::cout << myMap.Get(1) << std::endl;
std::cout << myMap.Get(2) << std::endl;

MyMap<int, std::vector<double>> myMap2;
myMap2.Insert(1, {1.0, 2.0, 3.0});
myMap2.Insert(2, {2.0, 3.0, 4.0});
myMap2.Insert(3, {3.0, 4.0, 5.0});
myMap2.Insert(4, {4.0, 5.0, 6.0});
std::cout << myMap2 << std::endl;
std::cout << myMap2.Get(1)[0] << std::endl;
std::cout << myMap2.Get(2)[1] << std::endl;

// Testing MyUnorderedMap
std::cout << "Testing MyUnorderedMap" << std::endl;
MyUnorderedMap<int, std::string> myUnorderedMap;
myUnorderedMap.Insert(1, "one");
myUnorderedMap.Insert(2, "two");
myUnorderedMap.Insert(3, "three");
myUnorderedMap.Insert(4, "four");
std::cout << myUnorderedMap << std::endl;
std::cout << myUnorderedMap.Get(1) << std::endl;
std::cout << myUnorderedMap.Get(2) << std::endl;

MyUnorderedMap<int, std::vector<double>> myUnorderedMap2;
myUnorderedMap2.Insert(1, {1.0, 2.0, 3.0});
myUnorderedMap2.Insert(2, {2.0, 3.0, 4.0});
myUnorderedMap2.Insert(3, {3.0, 4.0, 5.0});
myUnorderedMap2.Insert(4, {4.0, 5.0, 6.0});
std::cout << myUnorderedMap2 << std::endl;
std::cout << myUnorderedMap2.Get(1)[0] << std::endl;
std::cout << myUnorderedMap2.Get(2)[1] << std::endl;
}

void TestColorPalette() {
    // Testing ColorPalette
std::cout << "Testing ColorPalette" << std::endl;
MyUnorderedMap<string, int> myUnorderedMap;
myUnorderedMap.Insert("Black", 1);
myUnorderedMap.Insert("Red", 2);
myUnorderedMap.Insert("Green", 3);
myUnorderedMap.Insert("Blue", 4);
std::cout << myUnorderedMap << std::endl;
std::cout << myUnorderedMap.Get("Black") << std::endl;
std::cout << myUnorderedMap.Get("Blue") << std::endl;
// std::cout << myUnorderedMap.Get("NADA") << std::endl;
}

void TryStatement() {
    MyUnorderedMap<string, int> myMap;
    try {
        auto value = myMap.Get("nonexistent_key");
    } catch (const KeyNotFoundException& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        // handle error
    }
}

class Person {
    public:
    Person(string name, int age) : Name(name), Age(age) {};
    ~Person() = default;

    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "Name: " << person.Name << " Age: " << person.Age << endl;
        return os;
    }

    private:
    string Name;
    int Age;
};

// void TestPersonMap () {
//     // Testing PersonMap
// std::cout << "Testing PersonMap" << std::endl;
// MyUnorderedMap<string, Person> PersonMap;

// Person Captain("Pedro", 20);
// Person Cook("Dinis", 19);
// Person Programmer("Eduardo", 20);

// PersonMap.Insert("Captain", Captain);
// PersonMap.Insert("Cook", Cook);
// PersonMap.Insert("Programmer", Programmer);

// std::cout << PersonMap << std::endl;
// std::cout << PersonMap.Get("Captain") << std::endl;
// std::cout << PersonMap.Get("Cook") << std::endl;
// }


/**
 * @brief MAIN ZONE
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * @return int 
 */

int main() {
    TestMyMaps();
    TestColorPalette();
    TryStatement();
    // TestPersonMap();

// Does not work
    // MyUnorderedMap<string, pair<string, int>> myUnorderedMap;
    // myUnorderedMap.Insert("Pedro", make_pair("Physics", 16));
    // myUnorderedMap.Insert("Rita", make_pair("Biology", 20));
    // cout << myUnorderedMap << endl;

return 0; 
}