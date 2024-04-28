/*
* Welcome to True Enum! This library is designed to make it easy to create and use enumerations in C++. The way this stands out from other libraries is that it is designed with modularity, ease of use, customizability, efficiency and security in mind.
* Sounds like alot to implement? Not really, you do not need to do a thing to use this library. Just use it and you're good to go. Every single macro has a default value, meaning you don't have to worry about that unless you want a different default value.
* 
* Preprocessor Macros:
*    - TRUE_ENUM_EXCLUDE_STD_STRING
*       - this will exclude the usage of std::string, setting the TRUE_ENUM_STRINGTYPE to a const char* instead. You do not need to worry about including std::string if you do this as it is taken care of!
*
*    - TRUE_ENUM_ENABLE_NAMESPACE
*       - this will enable the namespace. For those who hate namespaces, or something like that.
*   
*    - TRUE_ENUM_ENABLE_FILE_IO
*       - this will enable file IO. By default this is disabled. This allows you to read from and write to files in the form of a .trueenum file.
*
*    - TRUE_ENUM_ENABLE_OVERWRITE
*       - this will enable overwrite. By default this is disabled. This allows you to overwrite enums if they already exist. This is not enabled when TRUE_ENUM_SECURITY_LEVEL is greater than 1. See TRUE_ENUM_SECURITY_LEVEL for more information.
*           - TRUE_ENUM_FORCE_OVERWRITE
*               - this will force overwrite. By default this is disabled. Even when TRUE_ENUM_SECURITY_LEVEL is greater than 1, this will not allow you to overwrite enums if they already exist.
*
*    - TRUE_ENUM_SECURITY_LEVEL
*       - this will enable security. By default this is 0 (minimal security). This allows you to set the security level. This is not enabled when TRUE_ENUM_ENABLE_OVERWRITE is enabled.
*           Levels :
*               - 0 = minimal security
*               - 1 = moderate Security
*               - 2 = extreme security
*
*   - TRUE_ENUM_MAKE_DATA_STATIC
*       - this will make the data container static. By default this is disabled. This will make the data container static.
*
*   - TRUE_ENUM_EXCLUE_DATA_REFERENCE_FUNCTIONS
*       - defining this means you cannot call functions that return references, they will throw an exception.
* 
* Notes :
* 
*   - This library is not thread safe.
*   - This library requires C++ 17 or higher due to the use of std::any.
* 
* Enjoy and happy coding!
*/

#ifndef TRUE_ENUM_H
#define TRUE_ENUM_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <any>
#include <exception>
#include <functional>
#include <memory>




// logic on whether or not to use const char* or std::string. Just here because it is nice to have :)
#ifdef TRUE_ENUM_EXCLUDE_STD_STRING
    typedef const char* TRUE_ENUM_STRINGTYPE;
#else
    #include <string>
    typedef std::string TRUE_ENUM_STRINGTYPE;
#endif

#ifndef TRUE_ENUM_SECURITY_LEVEL
    #define TRUE_ENUM_SECURITY_LEVEL 0
#endif

// Security level logic.
#if TRUE_ENUM_SECURITY_LEVEL >= 1

    // if security level is 1 or greater we will throw a pre-compile error informing the user.
    #ifdef TRUE_ENUM_ENABLE_OVERWRITE
        // unless the user is forcing overwriting we will throw a pre-compile error informing the user.
        #ifndef TRUE_ENUM_FORCE_OVERWRITE
            #error "TRUE_ENUM_ENABLE_OVERWRITE cannot be set to true when TRUE_ENUM_SECURITY_LEVEL >= 1"
        #endif
    #endif

#endif

// define this if you want to enable file IO, AKA, if you want to be able to write data to a .trueenum file.
#ifdef TRUE_ENUM_ENABLE_FILE_IO
    #include <fstream>
    #include <sstream>
    #include <filesystem>
    namespace fs = std::filesystem;

    #ifdef TRUE_ENUM_ENABLE_NAMESPACE
        namespace TrueEnum {
    #endif

    void writeToFile(const std::string& filename, const std::map<TRUE_ENUM_STRINGTYPE, std::any>& data) {
        std::ofstream file(filename + ".trueenum");
        if (!file.is_open()) {
            throw TrueEnumException("File not found");
        }

        for (auto it = data.begin(); it != data.end(); it++) {
            file << it->first << " " << it->second << std::endl;
        }
        file.close();
    }

    void readFromFile(const std::string& filename, std::map<TRUE_ENUM_STRINGTYPE, std::any>& data) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw TrueEnumException("File not found");
        }
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            TRUE_ENUM_STRINGTYPE name;
            std::any value;
            iss >> name >> value;
            data[name] = value;
        }
        file.close();
    }

    std::map<TRUE_ENUM_STRINGTYPE, std::any> getFromFile(const std::string& filename) {
        std::map<TRUE_ENUM_STRINGTYPE, std::any> data;
        readFromFile(filename, data);
        return data;
    }

    #ifdef TRUE_ENUM_ENABLE_NAMESPACE
        }
    #endif

#endif

// define this if you want to disaable the namespace.
#ifndef TRUE_ENUM_EXCLUDE_NAMESPACE
namespace TrueEnum {
#endif

typedef struct TrueEnumConfig {
    size_t memoryLimit; // in bytes. 0 = no limit, and it will use the default system memory limit.
} TrueEnumConfig;



class TrueEnumException : public std::exception {
public:
    TrueEnumException(const std::string& msg) : msg(msg) {}
    virtual const char* what() const throw() {
        return msg.c_str();
    }
private:
    std::string msg;
};

template<typename T>
class ITrueEnum {
private:
    static inline TrueEnumConfig trueEnumConfig = { 0 };
public:
    #ifdef TRUE_ENUM_MAKE_DATA_STATIC
        static inline std::map<T, std::any> enumContainer;
    #else
        std::map<T, std::any> enumContainer;
        
    #endif

    ITrueEnum() {}

    template<typename t>
    void addEnum(const T& name, t value) {
        // First we need to calculate the memory usage
        size_t memUsage = getMemoryUsage(name);
        if (trueEnumConfig.memoryLimit > 0 && memUsage > trueEnumConfig.memoryLimit) {
            throw TrueEnumException("Memory limit exceeded");
        } else {
            // check to see if the name already exists, if it does, throw an exception unless TRUE_ENUM_ENABLE_OVERWRITE is set to true
            if (enumContainer.find(name) != enumContainer.end()) {
                #ifdef TRUE_ENUM_ENABLE_OVERWRITE
                    enumContainer[name] = std::any(value);
                #else
                    throw TrueEnumException("Enum already exists");
                #endif
            } else {
                enumContainer[name] = std::any(value);
            }
        }
    }

    template<typename t>
    t getEnum(const T& name) {
        if (enumContainer.find(name) == enumContainer.end()) {
            throw TrueEnumException("Enum not found");
        } else {
            return std::any_cast<t>(enumContainer[name]);
        }
    }

    template<typename t>
    void setEnum(const T& name, t value) {
		enumContainer[name] = std::any(value);
	}


    #ifndef TRUE_ENUM_EXCLUDE_DATA_REFERENCE_FUNCTIONS
    template<typename t>
    t& getEnumRef(const T& name) {
        if (enumContainer.find(name) == enumContainer.end()) {
            throw TrueEnumException("Enum not found");
        } else {
            return std::any_cast<t>(enumContainer[name]);
        }
    }
    #endif

    bool exists(const T& name) {
        return enumContainer.find(name) != enumContainer.end();
    }

    bool isEmpty() {
        return enumContainer.empty();
    }

    void clear() {
        if (!enumContainer.empty()) {
            enumContainer.clear();
        } else {
            
            // Will only throw if security level is greater than 1 
            #if TRUE_ENUM_SECURITY_LEVEL >= 1
            throw TrueEnumException("Enum is already empty");
            #endif
        }
    }

    size_t size() {
        return enumContainer.size();
    }

    size_t getMemoryUsage() {
        size_t total = 0;
        for (auto it = enumContainer.begin(); it != enumContainer.end(); it++) {
            total += sizeof(it->first);
            total += sizeof(it->second);
        }
        return total;
    }

    size_t getMemoryUsage(const T& name) {
        return sizeof(enumContainer[name]);
    }

    // Print with a function (you define your own on this one)
    void print(std::function<void(const T&, const std::any&)> func) {
        for (auto it = enumContainer.begin(); it != enumContainer.end(); it++) {
            func(it->first, it->second);
        }
    }

    std::shared_ptr<ITrueEnum<T>> clone() {
        return std::make_shared<ITrueEnum<T>>(*this);
    }

    std::shared_ptr<ITrueEnum<T>> clone(const T& name) {
        return std::make_shared<ITrueEnum<T>>(*this, name);
    }

    std::shared_ptr<ITrueEnum<T>> clone(const T& name, const std::any& value) {
        return std::make_shared<ITrueEnum<T>>(*this, name, value);
    }

    std::shared_ptr<ITrueEnum<T>> clone(const T& name, const T& value) {
        return std::make_shared<ITrueEnum<T>>(*this, name, value);
    }

    std::map<T, std::any>* getMapPtr() {
        return &enumContainer;
    }

    #ifndef TRUE_ENUM_EXCLUDE_DATA_REFERENCE_FUNCTIONS
    std::map<T, std::any>& getMapRef() {
        if (enumContainer.empty()) {
            
            throw TrueEnumException("Enum is empty, so it is not possible to get a reference to it!");
            
        } else {
            return enumContainer;
        }
    }
    #endif

    std::map<T, std::any> getMap() {
        return enumContainer;
    }

    static inline void setTrueEnumMemoryLimit(size_t limit) {
        trueEnumConfig.memoryLimit = limit;
    }
};

// This is the main class. You mainly want to use this.
class TrueEnumStr : public ITrueEnum<TRUE_ENUM_STRINGTYPE> {};

#ifndef TRUE_ENUM_EXCLUDE_NAMESPACE
}
#endif

#endif