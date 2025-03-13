#include "Text.h"

std::string Text::ReturnText() {
    std::string val = "";
    for (auto& part : this->parts) {
        if (part.index() == 0) {
            val += std::to_string(std::get<std::function<int()>>(part)());
        } else if (part.index() == 1) {
            val += std::get<std::string>(part);
        }
    }   
    return val; 
}

