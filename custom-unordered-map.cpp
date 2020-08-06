/*
 * std::hash, std::equal_to, and std::allocator are libraries introduced in
 * C++11.
 */

#include <cstddef>
#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>

class Record;

template<>
struct std::hash<Record> {
    using argument_type = Record;
    using result_type = std::size_t;

    std::size_t operator()(const Record&) const noexcept;
};

template<>
struct std::equal_to<Record> {
    bool operator()(const Record& lhs, const Record& rhs) const noexcept;
};

template<>
struct std::allocator<Record> {
    friend bool operator==(const std::allocator<Record>&, const std::allocator<Record>&) noexcept;
    friend bool operator!=(const std::allocator<Record>&, const std::allocator<Record>&) noexcept;

    using value_type                             = Record;
    using pointer                                = Record*;
    using const_pointer                          = const Record*;
    using reference                              = Record&;
    using const_reference                        = const Record&;
    using size_type                              = std::size_t;
    using difference_type                        = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal                        = std::true_type;

    constexpr allocator() noexcept;
    
    constexpr allocator(const allocator& other) noexcept;

    template<class T>
    constexpr allocator(const allocator<T>& other) noexcept;

    ~allocator() noexcept;

#if __cplusplus >= 202002L

    [[nodiscard]]
    constexpr Record* allocate(std::size_t n);

    constexpr void deallocate(Record* p, std::size_t n);

#else

    Record* allocate(std::size_t n);

    void deallocate(Record* p, std::size_t n);

#endif

private:
    Record* begin_;
    Record* end_;
    Record* capacity_;
};

class Record {
    inline friend bool operator==(const Record&, const Record&) noexcept;
    inline friend bool operator!=(const Record&, const Record&) noexcept;
    inline friend bool operator<(const Record&, const Record&) noexcept;
    inline friend bool operator>(const Record&, const Record&) noexcept;
    inline friend bool operator<=(const Record&, const Record&) noexcept;
    inline friend bool operator>=(const Record&, const Record&) noexcept;
    friend std::size_t std::hash<Record>::operator()(const Record&) const noexcept;

public:
    std::string get_name() const {return name;}
    int get_product_code() const {return product_code;}

private:
    std::string name;
    int product_code;
};

inline bool operator==(const Record& lhs, const Record& rhs) noexcept
{
    return lhs.name == rhs.name && lhs.product_code == rhs.product_code;
}

inline bool operator!=(const Record& lhs, const Record& rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator<(const Record& lhs, const Record& rhs) noexcept
{
    if (lhs.product_code < rhs.product_code)
        return true;
    else if (lhs.product_code > rhs.product_code)
        return false;
    else
        return lhs.name < rhs.name;
}

inline bool operator>(const Record& lhs, const Record& rhs) noexcept
{
    return  rhs < lhs;
}

inline bool operator<=(const Record& lhs, const Record& rhs) noexcept
{
    return lhs > rhs;
}

inline bool operator>=(const Record& lhs, const Record& rhs) noexcept
{
    return lhs < rhs;
}

std::size_t std::hash<Record>::operator()(const Record& r) const noexcept
{
    return std::hash<std::string>()(r.name) ^ std::hash<int>()(r.product_code);
}

bool std::equal_to<Record>::operator()(const Record& lhs, const Record& rhs) const noexcept
{
    return lhs == rhs;
}

constexpr std::allocator<Record>::allocator() noexcept
    : begin_{nullptr}, end_{nullptr}, capacity_{nullptr}
{
}

constexpr std::allocator<Record>::allocator(const allocator& other) noexcept
    : begin_{other.begin_}, end_{other.end_}, capacity_{other.capacity_}
{
}

template<class T>
constexpr std::allocator<Record>::allocator(const allocator<T>& other) noexcept
    : begin_{nullptr}, end_{nullptr}, capacity_{nullptr}
{}

std::allocator<Record>::~allocator() noexcept
{}

#if __cplusplus >= 202002L

[[nodiscard]]
constexpr Record* std::allocator<Record>::allocate(std::size_t n)
{
    begin_ = end_ = new Record{n};
    capacity_ = begin_ + n;
    return begin_;
}

constexpr void std::allocator<Record>::deallocate(Record* p, std::size_t n)
{
    delete[] (p + n);
}

#else

Record* std::allocator<Record>::allocate(std::size_t n)
{
    begin_ = end_ = new Record[n];
    capacity_ = begin_ + n;
    return begin_;
}

void std::allocator<Record>::deallocate(Record* p, std::size_t n)
{
    delete[] (p + n);
}

#endif

bool operator==(const std::allocator<Record>&,
                const std::allocator<Record>&) noexcept
{
    return true;
}

bool operator!=(const std::allocator<Record>&,
                const std::allocator<Record>&) noexcept
{
    return false;
}

int main()
{
    std::unordered_map<int, Record> uo;
}