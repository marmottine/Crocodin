#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>

#if __cplusplus >= 201103L
#include <memory>
#include <unordered_map>
#else
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
namespace std {
    using boost::shared_ptr;
    using boost::unordered_map;
    using boost::static_pointer_cast;
    using boost::dynamic_pointer_cast;
    using boost::make_shared;
}
#endif

class Resources {
public:
    template<typename T>
    std::shared_ptr<T> get(const std::string& path);

private:
    std::unordered_map<std::string, std::shared_ptr<void> > contents;
};

template<typename T>
std::shared_ptr<T> loadResource(const std::string& path);

#include "Resources.tpp"

#endif
