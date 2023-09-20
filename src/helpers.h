#pragma once

template <typename Container>
typename Container::value_type get_random_element(const Container& container);

#include "helpers.cpp"
// Including the implementation file here because adding each template
// declaration to the implementation file would be tedious and error-prone.