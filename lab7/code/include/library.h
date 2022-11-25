#ifndef H_LIBRARY
#define H_LIBRARY
#include <string>

namespace Library {
    class book_entry_t
    {
    public:
        std::string ISBN;
        std::string name;
        std::string author;
        int cur_number;
        int total_number;
    };

    
}

#endif