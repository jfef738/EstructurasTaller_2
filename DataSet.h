// ===================================================================================
// File:        DataSet.h
// Author:      Alejandro Castro Martinez
// Date:        2025-07-27
// Description: Generic implementation of a mathematical set (DataSet<T>), storing
//              unique elements using a dynamic array (std::vector).
//
//              Supported operations:
//              ----------------------------------------------------------------------
//              DataSet(const std::string& setName)
//                  Constructs a set with the given name.
//
//              std::string getName() const
//                  Returns the name identifier of the set.
//
//              void setName(const std::string& newName)
//                  Assigns a new name to the set.
//
//              void insert(const T& value)
//                  Inserts a new element if it does not already exist in the set.
//
//              bool contains(const T& value) const
//                  Checks whether a given value exists in the set.
//
//              DataSet<T> unionWith(const DataSet<T>& other) const
//                  Returns a new set containing elements from both sets (no duplicates).
//
//              DataSet<T> intersectionWith(const DataSet<T>& other) const
//                  Returns a new set containing only elements common to both sets.
//
//              DataSet<T> differenceWith(const DataSet<T>& other) const
//                  Returns a new set with elements from this set that are not in the other.
//
//              DataSet<T> symmetricDifferenceWith(const DataSet<T>& other) const
//                  Returns a new set with elements in either set, but not in both.
//
//              bool isSubsetOf(const DataSet<T>& other) const
//                  Returns true if this set is a subset of the other.
//
//              bool isEqualTo(const DataSet<T>& other) const
//                  Returns true if both sets contain the same elements.
//
//              size_t size() const
//                  Returns the number of elements in the set.
//
//              std::vector<T> getElements() const
//                  Returns a copy of the internal vector containing all elements.
//
//              void print(std::ostream& os = std::cout) const
//                  Prints the contents of the set to the given output stream.
//              DataSet<DataSet<T>> powerSet() const
//                  Returns all subsets of the current set.
//
//              DataSet<std::pair<T, T>> cartesianProductWith(const DataSet<T>& other) const
//                  Returns the Cartesian product A × B as a set of (a, b) pairs.
// ===================================================================================

#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <iostream>

/**
 * @class DataSet
 * @brief Represents a generic mathematical set using a dynamic array.
 *        This template class stores unique elements of any comparable type.
 *
 * @tparam T Type of elements stored in the set (e.g., int, std::string).
 */
template <typename T>
class DataSet
{
private:
    std::vector<T> elements; ///< Internal container for storing unique elements.
    std::string name;        ///< Identifier name for this set.

public:
    /**
     * @brief Constructs a set with a specific name.
     * @param setName The identifier for this set.
     */
    DataSet(const std::string &setName);

    /**
     * @brief Returns the name of the set.
     * @return The name as a string.
     */
    std::string getName() const;

    /**
     * @brief Sets a new name for the set.
     * @param newName New identifier for the set.
     */
    void setName(const std::string &newName);

    /**
     * @brief Inserts a value into the set only if it's not already present.
     * @param value The element to insert.
     */
    void insert(const T &value);

    /**
     * @brief Checks if the set contains a specific value.
     * @param value The value to check.
     * @return True if the value is present, false otherwise.
     */
    bool contains(const T &value) const;

    /**
     * @brief Returns the union of the current set with another.
     * @param other The set to unite with.
     * @return A new DataSet<T> representing the union.
     */
    DataSet<T> unionWith(const DataSet<T> &other) const;

    /**
     * @brief Returns the intersection of the current set with another.
     * @param other The set to intersect with.
     * @return A new DataSet<T> representing the intersection.
     */
    DataSet<T> intersectionWith(const DataSet<T> &other) const;

    /**
     * @brief Returns the difference between the current set and another.
     * @param other The set to subtract.
     * @return A new DataSet<T> representing the difference.
     */
    DataSet<T> differenceWith(const DataSet<T> &other) const;

    /**
     * @brief Returns the symmetric difference (elements in one set but not both).
     * @param other The other set to compare against.
     * @return A new DataSet<T> representing the symmetric difference.
     */
    DataSet<T> symmetricDifferenceWith(const DataSet<T> &other) const;

    /**
     * @brief Checks if the current set is a subset of another.
     * @param other The set to compare against.
     * @return True if current set is subset of other, false otherwise.
     */
    bool isSubsetOf(const DataSet<T> &other) const;

    /**
     * @brief Checks if the current set is equal to another.
     * @param other The set to compare against.
     * @return True if both sets contain the same elements.
     */
    bool isEqualTo(const DataSet<T> &other) const;

    /**
     * @brief Returns the number of elements in the set.
     * @return The size of the set.
     */
    size_t size() const;

    /**
     * @brief Provides a copy of the set's elements.
     * @return A std::vector<T> containing all elements.
     */
    std::vector<T> getElements() const;

    /**
     * @brief Prints the contents of the set to the given output stream.
     * @param os Output stream (defaults to std::cout).
     */
    void print(std::ostream &os = std::cout) const;

    /**
     * @brief Returns the power set (set of all subsets) of the current set.
     * @return A DataSet<DataSet<T>> containing all subsets.
     */
    DataSet<DataSet<T>> powerSet() const;

    /**
     * @brief Returns the Cartesian product of this set with another.
     * @param other The other set to combine with.
     * @return A DataSet<std::pair<T, T>> representing the Cartesian product.
     */
    DataSet<std::pair<T, T>> cartesianProductWith(const DataSet<T> &other) const;
};

/**
 * @brief Equality operator for DataSet<T>.
 *        Two sets are equal if they have the same elements (ignoring order).
 */
template <typename T>
bool operator==(const DataSet<T>& a, const DataSet<T>& b);


// Include implementation file
#include "DataSet.hxx"

#endif // DATASET_H
