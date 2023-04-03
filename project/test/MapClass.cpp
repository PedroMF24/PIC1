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

using namespace std;



// template<typename T>
// struct is_container {
//     static constexpr bool value = false;
// };

// template<typename... Ts>
// struct is_container_helper {};

// template<typename T>
// struct is_container<
//     T,
//     std::void_t<
//         typename T::value_type,
//         typename T::size_type,
//         typename T::allocator_type,
//         typename T::iterator,
//         typename T::const_iterator,
//         decltype(std::declval<T>().size()),
//         decltype(std::declval<T>().begin()),
//         decltype(std::declval<T>().end()),
//         decltype(std::declval<T>().cbegin()),
//         decltype(std::declval<T>().cend())
//     >
// > : std::conditional_t<
//     std::is_same_v<
//         typename T::value_type,
//         typename std::remove_cv<typename std::remove_reference<decltype(*std::declval<T>().begin())>::type>::type
//     >,
//     std::true_type,
//     std::false_type
// >{};

// template<typename T>
// constexpr bool is_container_v = is_container<T>::value;






template<typename KeyType, typename ValueType>
class MyMap {
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
        return myMap[key];
    }

    // Return a const reference to the map
    const std::map<KeyType, ValueType>& GetMap() const {
        return myMap;
    }

    // void PrintMap() const {
    //     for (const auto& pair : myMap) {
    //         std::cout << "Key: " << pair.first << std::endl;
    //         std::cout << "Value: ";

    //         if constexpr (std::is_same_v<Value, std::vector<double>>) {
    //             for (const auto& v : value) {
    //                 std::cout << v << " ";
    //             }
    //         }
    //         else {
    //             std::cout << value;
    //         }

    //         std::cout << std::endl;
    //     }
    // }

    // friend std::ostream& operator<<(std::ostream& os, const MyMap& map) {
    //     for (const auto& pair : map.myMap) {
    //         os << "(" << pair.first << ", " << pair.second << ") ";
    //     }
    //     return os;
    // }

    friend std::ostream& operator<<(std::ostream& os, const MyMap& map) {
        for (const auto& pair : map.myMap) {
            os << "(" << pair.first << ", ";

            if constexpr (std::is_same_v<Value, std::vector<double>>) {
                os << "[";
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

class MyUnorderedMap {
private:
    unordered_map<KeyType, ValueType> myUnorderedMap;

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
        return myUnorderedMap[key];
    }

    // Return a const reference to the map
    const std::map<KeyType, ValueType>& GetMap() const {
        return myMap;
    }

    // void PrintMap() const {
    //     for (const auto& [key, value] : myMap) {
    //         std::cout << "Key: " << key << std::endl;
    //         std::cout << "Value: ";

    //         if constexpr (std::is_same_v<Value, std::vector<double>>) {
    //             for (const auto& v : value) {
    //                 std::cout << v << " ";
    //             }
    //         }
    //         else {
    //             std::cout << value;
    //         }

    //         std::cout << std::endl;
    //     }
    // }

    // friend std::ostream& operator<<(std::ostream& os, const MyUnorderedMap& map) {
    //     for (const auto& pair : map.myMap) {
    //         os << "(" << pair.first << ", " << pair.second << ") ";
    //     }
    //     return os;
    // }

    friend std::ostream& operator<<(std::ostream& os, const MyUnorderedMap& map) {
        for (const auto& pair : map.myMap) {
            os << "(" << pair.first << ", ";

            if constexpr (std::is_same_v<Value, std::vector<double>>) {
                os << "[";
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
    MyUnorderedMap<KeyType, ValueType> operator+(const MyUnorderedMap<KeyType, OtherValueType>& other) const {
        static_assert(is_same_v<ValueType, OtherValueType>, "Map value types must be the same.");
        MyUnorderedMap<KeyType, ValueType> result;
        for (const auto& pair : myUnorderedMap) {
            auto it = other.myUnorderedMap.find(pair.first);
            if (it != other.myUnorderedMap.end()) {
                result.myUnorderedMap[pair.first] = pair.second + it->second;
            }
        }
        return result;
    }
};



int main() {

    MyMap<int, string> intToStringMap;
    intToStringMap.Insert(1, "one");
    intToStringMap.Insert(2, "two");
    cout << intToStringMap.Get(1) << endl; // prints "one"

    MyMap<string, double> stringToDoubleMap;
    stringToDoubleMap.Insert("pi", 3.14159);
    cout << stringToDoubleMap.Get("pi") << endl; // prints 3.14159

    MyUnorderedMap<int, string> intToStringUnorderedMap;
    intToStringUnorderedMap.Insert(1, "one");
    intToStringUnorderedMap.Insert(2, "two");
    cout << intToStringUnorderedMap.Get(1) << endl; // prints "one"

    MyUnorderedMap<string, double> stringToDoubleUnorderedMap;
    stringToDoubleUnorderedMap.Insert("pi", 3.14159);
    cout << stringToDoubleUnorderedMap.Get("pi") << endl; // prints 3.14159


MyMap<string, double> mapA;
mapA.Insert("X", 3.0);
mapA.Insert("Y", 2.0);

cout << mapA << endl;

MyMap<string, double> mapB;
mapB.Insert("X", 5.0);
mapB.Insert("Z", 1.0);

auto mapC = mapA + mapB;
cout << "mapC: ";
for (const auto& pair : mapC.GetMap()) {
    cout << "(" << pair.first << ", " << pair.second << ") ";
}
cout << endl;

MyMap<std::string, int> myMap;
myMap.Insert("foo", 42);

// Get a const reference to the map and print its contents
const auto& mapRef = myMap.GetMap();
for (const auto& pair : mapRef) {
    std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
}

    return 0;
}


