// ===================================================================================
// File:        DataSetCollection.hxx
// Author:      Alejandro Castro
// Date:        2025-07-27
// Description: Implementation of the class DataSetCollection<T>, using a deque
//              to store named sets and allowing linear access and manipulation.
// ===================================================================================

#ifndef DATASETCOLLECTION_HXX
#define DATASETCOLLECTION_HXX

#include "DataSetCollection.h"
#include <stdexcept>
#include <iostream>

/**
 * @brief Default constructor.
 */
template <typename T>
DataSetCollection<T>::DataSetCollection() : sets()
{
    // No initialization needed; deque starts empty.
}

/**
 * @brief Returns the position index of a set by name.
 * @param name Name to search.
 * @return Index of the set in the deque, or -1 if not found.
 */
template <typename T>
int DataSetCollection<T>::findIndexByName(const std::string &name) const
{
    for (size_t i = 0; i < sets.size(); ++i)
    {
        if (sets[i].getName() == name)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

/**
 * @brief Adds a new DataSet<T> to the collection.
 *        If a set with the same name already exists, it is overwritten.
 * @param set A named DataSet<T> instance.
 */
template <typename T>
void DataSetCollection<T>::addSet(const DataSet<T> &set)
{
    int index = findIndexByName(set.getName());
    if (index != -1)
    {
        sets[index] = set; // Overwrite existing set
    }
    else
    {
        sets.push_back(set); // Add new set
    }
}

/**
 * @brief Checks if a set with the given name exists in the collection.
 * @param name Name to search.
 * @return True if found, false otherwise.
 */
template <typename T>
bool DataSetCollection<T>::hasSet(const std::string &name) const
{
    return findIndexByName(name) != -1;
}

/**
 * @brief Inserts a value into a specific named set.
 * @param name Name of the set.
 * @param value Value to insert.
 */
template <typename T>
void DataSetCollection<T>::insertInto(const std::string &name, const T &value)
{
    int index = findIndexByName(name);
    if (index == -1)
    {
        throw std::runtime_error("Set '" + name + "' not found.");
    }
    sets[index].insert(value);
}

/**
 * @brief Prints the contents of a named set.
 * @param name Name of the set to print.
 */
template <typename T>
void DataSetCollection<T>::printSet(const std::string &name) const
{
    int index = findIndexByName(name);
    if (index == -1)
    {
        std::cerr << "Set '" << name << "' not found." << std::endl;
        return;
    }
    sets[index].print(std::cout);
    std::cout << std::endl;
}

/**
 * @brief Retrieves a copy of a set by name.
 * @param name Name of the set.
 * @return A copy of the DataSet<T> with that name.
 * @throws std::runtime_error if not found.
 */
template <typename T>
DataSet<T> DataSetCollection<T>::getSet(const std::string &name) const
{
    int index = findIndexByName(name);
    if (index == -1)
    {
        throw std::runtime_error("Set '" + name + "' not found.");
    }
    return sets[index];
}

/**
 * @brief Returns the list of all set names in the collection.
 * @return Vector of set names.
 */
template <typename T>
std::vector<std::string> DataSetCollection<T>::getSetNames() const
{
    std::vector<std::string> names;
    for (const DataSet<T> &set : sets)
    {
        names.push_back(set.getName());
    }
    return names;
}

/**
 * @brief Executes an operation between two sets (by name).
 * @param nameA First set name.
 * @param op Operation name ("union", "intersection", "difference", "symmetric_difference")
 * @param nameB Second set name.
 * @return Resulting DataSet<T> from the operation.
 * @throws std::runtime_error if sets or operation are invalid.
 */
template <typename T>
DataSet<T> DataSetCollection<T>::operate(const std::string &nameA,
                                         const std::string &op,
                                         const std::string &nameB) const
{
    DataSet<T> A = getSet(nameA);
    DataSet<T> B = getSet(nameB);
    DataSet<T> result(A.getName() + " " + op + " " + B.getName());

    if (op == "union")
    {
        result = A.unionWith(B);
    }
    else if (op == "intersection")
    {
        result = A.intersectionWith(B);
    }
    else if (op == "difference")
    {
        result = A.differenceWith(B);
    }
    else if (op == "symmetric_difference")
    {
        result = A.symmetricDifferenceWith(B);
    }
    else
    {
        throw std::runtime_error("Invalid operation: '" + op + "'");
    }

    // Opcional: construir un nombre para el resultado
    result.setName("(" + nameA + " " + op + " " + nameB + ")");
    return result;
}

template <typename T>
DataSet<DataSet<T>> DataSetCollection<T>::operateUnarySet(const std::string &name,
                                                          const std::string &op) const
{
    DataSet<T> A = getSet(name);
    if (op == "powerset")
    {
        return A.powerSet();
    }
    else
    {
        throw std::runtime_error("Unsupported unary operation: '" + op + "'");
    }
}

template <typename T>
DataSet<std::pair<T, T>> DataSetCollection<T>::cartesianProduct(const std::string &nameA,
                                                                const std::string &nameB) const
{
    DataSet<T> A = getSet(nameA);
    DataSet<T> B = getSet(nameB);
    return A.cartesianProductWith(B);
}

#endif // DATASETCOLLECTION_HXX
