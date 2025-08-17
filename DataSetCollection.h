// ===================================================================================
// File:        DataSetCollection.h
// Author:      Alejandro Castro
// Date:        2025-07-27
// Description: Declaration of the class DataSetCollection<T>, which stores and manages
//              multiple named DataSet<T> instances using a linear structure (std::deque).
//
//              Supported operations:
//              ----------------------------------------------------------------------
//              void addSet(const DataSet<T>& set)
//                  Adds a new named set to the collection.
//
//              bool hasSet(const std::string& name) const
//                  Checks if a set with the given name exists.
//
//              void insertInto(const std::string& name, const T& value)
//                  Inserts a value into the named set.
//
//              DataSet<T> getSet(const std::string& name) const
//                  Returns a copy of the named set.
//
//              void printSet(const std::string& name) const
//                  Prints the contents of the named set.
//
//              std::vector<std::string> getSetNames() const
//                  Returns a list of all registered set names.
//
//              DataSet<T> operate(const std::string& nameA,
//                                  const std::string& op,
//                                  const std::string& nameB) const
//                  Executes a binary set operation between two named sets.
// ===================================================================================

#ifndef DATASETCOLLECTION_H
#define DATASETCOLLECTION_H

#include <deque>
#include <string>
#include <vector>
#include "DataSet.h"

/**
 * @class DataSetCollection
 * @brief Manages a collection of named sets (DataSet<T>) using a linear structure.
 *        Provides operations for insertion, access, and set algebra using names.
 *
 * @tparam T Type of the elements stored in each DataSet.
 */
template <typename T>
class DataSetCollection
{
private:
    std::deque<DataSet<T>> sets; ///< Linear storage of DataSet<T> objects.

    /**
     * @brief Returns the position index of a set by name.
     * @param name Name to search.
     * @return Index of the set in the deque, or -1 if not found.
     */
    int findIndexByName(const std::string &name) const;

public:
    /**
     * @brief Default constructor.
     */
    DataSetCollection();

    /**
     * @brief Adds a new DataSet<T> to the collection.
     *        If a set with the same name already exists, it is overwritten.
     * @param set A named DataSet<T> instance.
     */
    void addSet(const DataSet<T> &set);

    /**
     * @brief Checks if a set with the given name exists in the collection.
     * @param name Name to search.
     * @return True if found, false otherwise.
     */
    bool hasSet(const std::string &name) const;

    /**
     * @brief Inserts a value into a specific named set.
     * @param name Name of the set.
     * @param value Value to insert.
     */
    void insertInto(const std::string &name, const T &value);

    /**
     * @brief Retrieves a copy of a set by name.
     * @param name Name of the set.
     * @return A copy of the DataSet<T> with that name.
     * @throws std::runtime_error if not found.
     */
    DataSet<T> getSet(const std::string &name) const;

    /**
     * @brief Prints the contents of a named set.
     * @param name Name of the set to print.
     */
    void printSet(const std::string &name) const;

    /**
     * @brief Returns the list of all set names in the collection.
     * @return Vector of set names.
     */
    std::vector<std::string> getSetNames() const;

    /**
     * @brief Executes an operation between two sets (by name).
     * @param nameA First set name.
     * @param op Operation name ("union", "intersection", etc.)
     * @param nameB Second set name.
     * @return Resulting DataSet<T> from the operation.
     * @throws std::runtime_error if sets or operation are invalid.
     */
    DataSet<T> operate(const std::string &nameA,
                       const std::string &op,
                       const std::string &nameB) const;

    /**
     * @brief Executes a unary operation on a named set.
     *        Supported: "powerset"
     * @param name Name of the target set.
     * @param op Operation to execute.
     * @return Resulting DataSet<DataSet<T>> (for powerset).
     */
    DataSet<DataSet<T>> operateUnarySet(const std::string &name,
                                        const std::string &op) const;

    /**
     * @brief Executes a Cartesian product between two sets.
     * @param nameA First set name.
     * @param nameB Second set name.
     * @return A DataSet<std::pair<T, T>> representing A × B.
     */
    DataSet<std::pair<T, T>> cartesianProduct(const std::string &nameA,
                                              const std::string &nameB) const;
};

#include "DataSetCollection.hxx"

#endif // DATASETCOLLECTION_H
