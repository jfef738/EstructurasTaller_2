// ===================================================================================
// File:        main.cxx
// Author:      Alejandro Castro Martinez
// Date:        2025-07-27
// Description: Entry point for the Set Algebra Simulator.
//              This program reads a plain-text file containing named sets and
//              algebraic operations, processes the content using DataSet<T> and
//              DataSetCollection<T>, and prints the results.
//
//              USAGE:
//              $ ./simulador input_file.in
//
//              Input format:
//              ----------------------------------------------------------------------
//              A <count>       # Name of set and number of elements
//              <values...>     # Elements of the set (space-separated integers)
//              B <count>
//              <values...>
//              ...
//              Q               # Start of query section
//              print A
//              union A B
//              intersection A B
//              difference A B
//              symmetric_difference A B
// ===================================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "DataSet.h"
#include "DataSetCollection.h"

/**
 * @brief Removes leading and trailing whitespace from a string.
 */
std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

/**
 * @brief Parses a line of space-separated integers and returns them in a vector.
 */
std::vector<int> parseIntList(const std::string &line)
{
    std::istringstream iss(line);
    std::vector<int> result;
    int val;
    while (iss >> val)
        result.push_back(val);
    return result;
}

int main(int argc, char *argv[])
{
    // Check correct number of command-line arguments
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " input_file.in" << std::endl;
        return 1;
    }

    // Attempt to open the input file
    std::ifstream fin(argv[1]);
    if (!fin.is_open())
    {
        std::cerr << "Error: Cannot open file '" << argv[1] << "'" << std::endl;
        return 1;
    }

    DataSetCollection<int> collection; // Main structure holding all named sets
    std::string line;

    // ============================
    // Phase 1: Read all sets
    // ============================
    // Each set starts with a line: <name> <count>
    // Followed by a line of space-separated integers (the set elements)
    // Reading stops when the line "Q" is found
    while (std::getline(fin, line))
    {
        line = trim(line);
        if (line.empty())
            continue; // Skip empty lines
        if (line[0] == '#')
            continue; // Skip comments
        if (line == "Q")
            break; // End of set definitions

        std::istringstream iss(line);
        std::string setName;
        int count;

        // Parse set name and number oA 5f expected elements
        iss >> setName >> count;

        // Create empty set with that name
        DataSet<int> set(setName);

        // Read elements in the next line
        if (count > 0 && std::getline(fin, line))
        {
            std::vector<int> values = parseIntList(line);
            for (int val : values)
            {
                set.insert(val); // Ensures uniqueness
            }
        }

        // Add the set to the collection (overwrites if already exists)
        collection.addSet(set);
    }

    // ============================
    // Phase 2: Execute operations
    // ============================
    // After line "Q", each line represents an operation:
    // print <A>
    // union <A> <B>
    // intersection <A> <B>
    // difference <A> <B>
    // symmetric_difference <A> <B>
    while (std::getline(fin, line))
    {
        line = trim(line);

        if (line.empty())
            continue; // Skip empty lines
        if (line[0] == '#')
            continue; // Skip comments
        if (line == "Q")
            break; // End of set definitions

        std::istringstream iss(line);
        std::string op, nameA, nameB;
        iss >> op;

        if (op == "print")
        {
            // Single-set operation: print the contents
            iss >> nameA;
            collection.printSet(nameA);
        }
        else if (op == "union" || op == "intersection" ||
                 op == "difference" || op == "symmetric_difference")
        {
            // Binary operation: requires two set names
            iss >> nameA >> nameB;
            try
            {
                DataSet<int> result = collection.operate(nameA, op, nameB);
                result.print(std::cout); // Print result
                std::cout << std::endl;
            }
            catch (const std::exception &ex)
            {
                std::cerr << "Error: " << ex.what() << std::endl;
            }
        }
        else if (op == "issubset")
        {
            iss >> nameA >> nameB;
            try
            {
                DataSet<int> A = collection.getSet(nameA);
                DataSet<int> B = collection.getSet(nameB);
                bool result = A.isSubsetOf(B);
                std::cout << "Is " << nameA << " ⊆ " << nameB << "? "
                          << (result ? "Yes ✅" : "No ❌") << std::endl;
            }
            catch (const std::exception &ex)
            {
                std::cerr << "Error during issubset: " << ex.what() << std::endl;
            }
        }

        else if (op == "isequal")
        {
            iss >> nameA >> nameB;
            try
            {
                DataSet<int> A = collection.getSet(nameA);
                DataSet<int> B = collection.getSet(nameB);
                bool result = A.isEqualTo(B);
                std::cout << "Are " << nameA << " and " << nameB << " equal? "
                          << (result ? "Yes ✅" : "No ❌") << std::endl;
            }
            catch (const std::exception &ex)
            {
                std::cerr << "Error during isequal: " << ex.what() << std::endl;
            }
        }
        else if (op == "size")
        {
            iss >> nameA;
            try
            {
                DataSet<int> A = collection.getSet(nameA);
                std::cout << "Size of set " << nameA << ": " << A.size() << " element(s)" << std::endl;
            }
            catch (const std::exception &ex)
            {
                std::cerr << "Error during size: " << ex.what() << std::endl;
            }
        }
        else if (op == "powerset")
        {
            // Unary operation: powerset <SetName>
            iss >> nameA;
            try
            {
                DataSet<DataSet<int>> result = collection.operateUnarySet(nameA, "powerset");

                std::cout << "Power set of " << nameA << " contains "
                          << result.size() << " subsets:\n";

                std::vector<DataSet<int>> subsets = result.getElements();
                for (const auto &subset : subsets)
                {
                    subset.print(std::cout);
                    std::cout << std::endl;
                }
            }
            catch (const std::exception &ex)
            {
                std::cerr << "Error during powerset: " << ex.what() << std::endl;
            }
        }

        else if (op == "cartesian")
        {
            // Binary operation: cartesian <SetA> <SetB>
            iss >> nameA >> nameB;
            try
            {
                DataSet<std::pair<int, int>> result = collection.cartesianProduct(nameA, nameB);

                std::cout << "Cartesian product " << nameA << " × " << nameB
                          << " (" << result.size() << " pairs):\n";

                std::vector<std::pair<int, int>> pairs = result.getElements();
                std::cout << "{";
                for (size_t i = 0; i < pairs.size(); ++i)
                {
                    std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ")";
                    if (i < pairs.size() - 1)
                        std::cout << ", ";
                }
                std::cout << "}" << std::endl;
            }
            catch (const std::exception &ex)
            {
                std::cerr << "Error during cartesian product: " << ex.what() << std::endl;
            }
        }
        else
        {
            // Unknown or unsupported operation
            std::cerr << "Unknown operation: " << op << std::endl;
        }
    }

    fin.close();
    return 0;
}
