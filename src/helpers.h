#pragma once

template <typename Container>
typename Container::value_type get_random_element(const Container& container);

template <typename Container>
bool contains(const Container&                      container,
              const typename Container::value_type& element);

#include "helpers.cpp"
// Including the implementation file here because adding each template
// declaration to the implementation file would be tedious and error-prone.