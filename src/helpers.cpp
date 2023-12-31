#include "helpers.hpp"

#include <random>

std::random_device rd;
std::mt19937 rng(rd());

double default_probability_generator() {
    return std::generate_canonical<double, 10>(rng);
}

ProbabilityGenerator probability_generator = default_probability_generator;
