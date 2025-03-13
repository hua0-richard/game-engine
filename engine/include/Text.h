#include <vector>
#include <memory>
#include <variant>
#include <string>
#include <type_traits>
#include <functional>

class Text {
    public: 
        std::vector<std::variant<std::function<int()>, std::string>> parts; 
        
        void AppendText(const std::string& text) {
            parts.push_back(text);
        }
        
        void AppendText(int& value) {
            // store a lambda which takes in a reference to an int and returns the dereferenced value
            // could have used pointer
            // this is safer
            parts.push_back([&value]() -> int { return value; });
        }
        
        void AppendText(const char* text) {
            parts.push_back(std::string(text));
        }
        
        template <typename First, typename... Rest>
        void AppendText(First& first, Rest&... rest) {
            AppendText(first);
            AppendText(rest...);
        }
        
        std::string ReturnText();
};