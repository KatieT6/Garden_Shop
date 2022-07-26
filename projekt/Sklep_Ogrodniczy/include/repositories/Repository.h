//
// Created by student on 11.06.2022.
//

#ifndef SKLEP_OGRODNICZY_REPOSITORY_H
#define SKLEP_OGRODNICZY_REPOSITORY_H

#include <functional>
#include <vector>
#include <string>
#include <memory>
#include "nlohmann/json.hpp"

template<class T>
class Repository {
private:
    std::vector<T> elements;
public:
    // Repository Constructor
    Repository();

    // Repository Destructor
    virtual ~Repository();

    void add(const T &element);

    //Access Methods
    const T & get(const int i) const;

    // Function removing Object from repository
    void remove(const T &element);

    std::string report();

    int size() const;
    //
    T findBy(const std::function<bool(T)> &predicate) const;

    nlohmann::json getJson() const;

    std::vector<T> findAll(const std::function<bool(T)> &predicate) const;
    };




#endif //SKLEP_OGRODNICZY_REPOSITORY_H
