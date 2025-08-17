// ===================================================================================
// File:        DataSet.hxx
// Author:      Alejandro Castro Martinez
// Date:        2025-07-27
// Description: Implementation of the templated class DataSet<T>.
//              Only unique elements are stored internally using std::vector.
// ===================================================================================
// Group 4 | Joel Felipe Martinez | Xamuel Perez | Rafael Held

#ifndef DATASET_HXX
#define DATASET_HXX

#include "DataSet.h"
#include <algorithm> // For std::find

/**
 * @brief Constructs a set with a specific name.
 * @param setName The identifier for this set.
 */
template <typename T>
DataSet<T>::DataSet(const std::string &setName)
    : name(setName), elements() {}

/**
 * @brief Returns the name of the set.
 * @return The name as a string.
 */
template <typename T>
std::string DataSet<T>::getName() const
{
    return name;
}

/**
 * @brief Sets a new name for the set.
 * @param newName New identifier for the set.
 */
template <typename T>
void DataSet<T>::setName(const std::string &newName)
{
    name = newName;
}

/**
 * @brief Inserts a value into the set only if it's not already present.
 * @param value The element to insert.
 */
template <typename T>
void DataSet<T>::insert(const T &value)
{
    if (!this->contains(value))
    {
        this->elements.push_back(value);
    }
    // TODO #02: Implementar la función insert
    // Esta función debe insertar un nuevo valor en el conjunto solo si dicho valor
    // aún no se encuentra presente. Para ello, debe invocar la función contains()
    // previamente implementada. Si el valor no está presente, se debe agregar al conjunto
    // No se permite insertar elementos duplicados bajo ninguna circunstancia.
    // La función debe mantener la semántica de conjunto: todos los elementos únicos.
}

/**
 * @brief Checks if the set contains a specific value.
 * @param value The value to check.
 * @return True if the value is present, false otherwise.
 */
template <typename T>
bool DataSet<T>::contains(const T &value) const
{
    typename std::vector<T>::const_iterator it = this->elements.begin();
    while (it != this->elements.end())
    {
        if (*it == value)
        {
            return true;
        }
        ++it;
    }
    return false;
    // TODO #01: Implementar la función contains
    // Esta función debe verificar si un elemento dado está presente en el conjunto actual.
    // Para ello, debe recorrer la estructura lineal interna
    // y determinar si existe un elemento que sea igual al valor recibido por parámetro.
    // No se permite modificar la estructura ni usar contenedores auxiliares.
    // El valor de retorno debe ser true si el elemento existe, false en caso contrario.
}

/**
 * @brief Returns the union of the current set with another.
 * @param other The set to unite with.
 * @return A new DataSet<T> representing the union.
 */
template <typename T>
DataSet<T> DataSet<T>::unionWith(const DataSet<T> &other) const
{
    DataSet<T> result(this->getName() + " ∪ " + other.getName());
    typename std::vector<T>::const_iterator itA = this->elements.begin();
    while (itA != this->elements.end())
    {
        result.insert(*itA);
        ++itA;
    }

    std::vector<T> elemsB = other.getElements();
    typename std::vector<T>::const_iterator itB = elemsB.begin();
    while (itB != elemsB.end())
    {
        result.insert(*itB);
        ++itB;
    }

    return result;
    // TODO #03: Completar la implementación de la operación unión (unionWith)
    // Esta función debe construir un nuevo conjunto que contenga todos los elementos
    // del conjunto actual y todos los elementos del conjunto recibido por parámetro,
    // sin duplicados. El resultado debe almacenarse en la variable `result` ya definida.
    //
    // No se deben modificar las estructuras internas originales.
    // Se espera que el resultado represente correctamente A ∪ B.
}

/**
 * @brief Returns the intersection of the current set with another.
 * @param other The set to intersect with.
 * @return A new DataSet<T> representing the intersection.
 */
template <typename T>
DataSet<T> DataSet<T>::intersectionWith(const DataSet<T> &other) const
{
    DataSet<T> result(this->getName() + " ∩ " + other.getName());
    typename std::vector<T>::const_iterator it = this->elements.begin();
    while (it != this->elements.end())
    {
        const T &val = *it;
        if (other.contains(val))
        {
            result.insert(val);
        }
        ++it;
    }
    return result;
    // TODO #04: Implementar la operación intersección (intersectionWith)
    // Esta función debe construir un nuevo conjunto que contenga únicamente los elementos
    // que están presentes tanto en el conjunto actual como en el conjunto recibido.
    //
    // La variable `result` ya está declarada y lista para usar.
    // No se deben modificar los conjuntos originales.
    // El resultado debe representar correctamente A ∩ B.
}

/**
 * @brief Returns the difference between the current set and another.
 * @param other The set to subtract.
 * @return A new DataSet<T> representing the difference.
 */
template <typename T>
DataSet<T> DataSet<T>::differenceWith(const DataSet<T> &other) const
{
    DataSet<T> result(this->getName() + "-" + other.getName());
    typename std::vector<T>::const_iterator it = this->elements.begin();
    while (it != this->elements.end())
    {
        const T &val = *it;
        if (!other.contains(val))
        {
            result.insert(val);
        }
        ++it;
    }

    return result;
    // TODO #05: Implementar la operación diferencia (differenceWith)
    // Esta función debe construir un nuevo conjunto que contenga todos los elementos
    // que están en el conjunto actual (`this`) pero que **no** están presentes en el conjunto `other`.
    //
    // La variable `result` ya está definida. No modifique los conjuntos originales.
    // El resultado debe representar correctamente A − B.
}

/**
 * @brief Returns the symmetric difference (elements in one set but not both).
 * @param other The other set to compare against.
 * @return A new DataSet<T> representing the symmetric difference.
 */
template <typename T>
DataSet<T> DataSet<T>::symmetricDifferenceWith(const DataSet<T> &other) const
{
    DataSet<T> result(this->getName() + " symmetric_difference " + other.getName());
    typename std::vector<T>::const_iterator itA = this->elements.begin();
    while (itA != this->elements.end())
    {
        const T &valA = *itA;
        if (!other.contains(valA))
        {
            result.insert(valA);
        }
        ++itA;
    }
    std::vector<T> elemsB = other.getElements();
    typename std::vector<T>::const_iterator itB = elemsB.begin();
    while (itB != elemsB.end())
    {
        const T &valB = *itB;
        if (!this->contains(valB))
        {
            result.insert(valB);
        }
        ++itB;
    }

    return result;
    // TODO #06: Implementar la operación diferencia simétrica (symmetricDifferenceWith)
    // La diferencia simétrica entre dos conjuntos A y B se define como:
    // (A − B) ∪ (B − A). El resultado debe contener los elementos que están en
    // exactamente uno de los dos conjuntos, pero no en ambos.
    //
    // Resultado esperado: un nuevo DataSet<T> que represente A △ B.
}

/**
 * @brief Checks if the current set is a subset of another.
 * @param other The set to compare against.
 * @return True if current set is subset of other, false otherwise.
 */
template <typename T>
bool DataSet<T>::isSubsetOf(const DataSet<T> &other) const
{
    std::vector<T> elems = this->getElements();
    typename std::vector<T>::const_iterator it = elems.begin();
    while (it != elems.end())
    {
        const T &val = *it;
        if (!other.contains(val))
        {
            return false;
        }
        ++it;
    }
    return true;
    // TODO #07: Implementar la verificación de subconjunto (isSubsetOf)
    // Esta función debe determinar si el conjunto actual es subconjunto del conjunto `other`.
    // Es decir, debe retornar true si todos los elementos del conjunto actual están presentes
    // en el conjunto `other`. En caso contrario, debe retornar false.
    //
    // Esta operación no debe modificar ninguno de los conjuntos involucrados.
    // El resultado debe respetar la definición formal de subconjunto: A ⊆ B.
}

/**
 * @brief Checks if the current set is equal to another.
 * @param other The set to compare against.
 * @return True if both sets contain the same elements.
 */
template <typename T>
bool DataSet<T>::isEqualTo(const DataSet<T> &other) const
{
    return this->isSubsetOf(other) && other.isSubsetOf(*this);
    // TODO #08: Implementar la verificación de igualdad entre conjuntos (isEqualTo)
    // Esta función debe retornar true si ambos conjuntos contienen exactamente los mismos elementos,
    // sin importar el orden. Es decir, si A = B en términos de contenido.
    //
    // Para ello, puede utilizar la propiedad matemática de doble inclusión:
    // A = B ⇔ (A ⊆ B) ∧ (B ⊆ A)
    //
    // Se deben usar las funciones ya implementadas: isSubsetOf()
    // La función no debe modificar ninguno de los conjuntos.
    // El resultado debe reflejar igualdad lógica entre conjuntos, no igualdad estructural interna.
}

/**
 * @brief Returns the number of elements in the set.
 * @return The size of the set.
 */
template <typename T>
size_t DataSet<T>::size() const
{
    // TODO #09: Implementar la función size()
    // Esta función debe retornar la cantidad total de elementos almacenados en el conjunto actual.
    // No se deben realizar recorridos ni contadores manuales.
    //
    // el número de elementos únicos contenidos en el conjunto.
    return 1;
}

/**
 * @brief Provides a copy of the set's elements.
 * @return A std::vector<T> containing all elements.
 */
template <typename T>
std::vector<T> DataSet<T>::getElements() const
{
    return elements;
}

template <typename T>
void DataSet<T>::print(std::ostream &os) const
{
    if (!name.empty())
    {
        os << name << " = ";
    }
    os << "{";
    for (size_t i = 0; i < elements.size(); ++i)
    {
        os << elements[i];
        if (i < elements.size() - 1)
        {
            os << ", ";
        }
    }
    os << "}";
}

/**
 * @brief Returns the power set (set of all subsets) of the current set.
 */
template <typename T>
DataSet<DataSet<T>> DataSet<T>::powerSet() const
{
    DataSet<DataSet<T>> result(this->getName() + " Power Set");
    // TODO #10: Implementar la operación conjunto potencia (powerSet)
    // Esta función debe retornar el conjunto potencia del conjunto actual,
    // es decir, un nuevo conjunto que contenga todos los subconjuntos posibles.
    //
    // El resultado debe ser de tipo DataSet<DataSet<T>>, y cada subconjunto debe
    // representarse como una instancia de DataSet<T>. Se deben incluir el conjunto vacío
    // y el conjunto original.
    //
    // No se permite modificar el conjunto original.
    // Se debe asegurar que los subconjuntos insertados en el resultado sean únicos.
    return result;
}

/**
 * @brief Returns the Cartesian product A × B as a set of (a, b) pairs.
 */
template <typename T>
DataSet<std::pair<T, T>> DataSet<T>::cartesianProductWith(const DataSet<T> &other) const
{

    DataSet<std::pair<T, T>> result(this->getName() + " × " + other.getName());
    // TODO #11: Implementar la operación producto cartesiano (cartesianProductWith)
    // Esta función debe retornar un nuevo conjunto que represente el producto cartesiano
    // A × B, es decir, el conjunto de todos los pares ordenados (a, b) donde
    // a pertenece al conjunto actual (`this`) y b pertenece al conjunto `other`.
    //
    // No se deben modificar los conjuntos originales.
    // El resultado debe incluir todos los pares posibles del producto A × B.

    return result;
}

/**
 * @brief Equality operator for DataSet<T>.
 *        Two sets are equal if they have the same elements (ignoring order).
 */
template <typename T>
bool operator==(const DataSet<T> &a, const DataSet<T> &b)
{
    return a.isEqualTo(b);
}

#endif // DATASET_HXX
