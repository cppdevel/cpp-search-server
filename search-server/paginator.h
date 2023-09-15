#pragma once

#include "document.h"

#include <algorithm>
#include <iostream>
#include <vector>

template<typename IteratorRanges>
class IteratorRange {
public:
    explicit IteratorRange(IteratorRanges begin, IteratorRanges end)
        : begin_(begin)
        , end_(end)
        , size_(distance(begin, end))
    {
    }

    IteratorRanges begin() const {
        return begin_;
    }

    IteratorRanges end() const {
        return end_;
    }

    size_t size() const {
        return size_;
    }

private:
    IteratorRanges begin_;
    IteratorRanges end_;
    size_t size_;
};

template <typename ItetatorRangeOut>
std::ostream& operator<<(std::ostream& output, const IteratorRange<ItetatorRangeOut>& page) {
    auto i = page.begin();
    while (i != page.end()) {
        output << *i;
        ++i;
    }
    return output;
}

std::ostream& operator<<(std::ostream& output, const Document& document) {
    using namespace std::string_literals;
    output << "{ document_id = "s << document.id << ", relevance = "s << document.relevance << ", rating = "s << document.rating << " }"s;
    return output;
}

template<typename Pag>
class Paginator {
public:
    Paginator(const Pag& b, const Pag& e, size_t page_size) {
        auto start_size = distance(b, e);
        Pag default_iterator = b;
        for (auto i = 0; i < (start_size / page_size); ++i) {
            pages_.push_back(IteratorRange<Pag>(default_iterator, default_iterator + page_size));
            default_iterator += page_size;
        }
        if (default_iterator != e) {
            pages_.push_back(IteratorRange<Pag>(default_iterator, e));
        }
    }

    auto begin() const {
        return pages_.begin();
    }

    auto end() const {
        return pages_.end();
    }

    size_t size() {
        return pages_.size();
    }
private:
    std::vector<IteratorRange<Pag>> pages_;
};

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}