#include <algorithm>
#include <random>
#include <stdexcept>

// Function to pick a random element from a container
template <typename Container>
typename Container::value_type get_random_element(const Container& container)
{
    if (container.empty())
    {
        throw std::out_of_range("Container is empty");
    }

    std::random_device                    rd;
    std::mt19937                          generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, container.size() - 1);

    size_t random_index = distribution(generator);
    auto   it = container.begin();
    std::advance(it, random_index);

    return *it;
}

// Function to check if a container contains a given element
template <typename Container>
bool contains(const Container&                      container,
              const typename Container::value_type& element)
{

    return std::find(std::begin(container), std::end(container), element) !=
           std::end(container);
}
