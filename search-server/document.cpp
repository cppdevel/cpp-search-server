#include "document.h"

std::ostream& operator<<(std::ostream& output, const Document& document) {
    using namespace std::string_literals;
    output << "{ document_id = "s << document.id << ", relevance = "s << document.relevance << ", rating = "s << document.rating << " }"s;
    return output;
}