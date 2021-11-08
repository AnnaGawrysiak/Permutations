#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

int fact(int num)
{
    int factorial = 1;

    for (int i = 1; i <= num; i++) {
        factorial = factorial * i;
    }
    return factorial;
}

std::pair<int, int> find_index_of_largest_mobile_and_its_adjacent(std::vector<std::pair<int, bool>>& current)
{
    int index = -1;
    int index_adjacent = -1;
    int largest = std::numeric_limits<int>::min();
    for (int i = 0; i < current.size(); i++) 
    {
        //std::cout << "current.at(i).first: " << current.at(i).first << " ";

        if((i-1) >= 0 && current.at(i).second == 1)
        {
            if (current.at(i).first > current.at(i - 1).first && current.at(i).first > largest)
            {
                largest = current.at(i).first;
                index = i;
                index_adjacent = i - 1;
            }
        }
        else if((i+1) < current.size() && current.at(i).second == 0)
        {
            if (current.at(i).first > current.at(i + 1).first && current.at(i).first > largest)
            {
                largest = current.at(i).first;
                index = i;
                index_adjacent = i + 1;
            }
        }

    }

    //std::cout << "the_largest_mobile_index: " << index << "the_largest_nr: " << largest << " ! ";

    return std::make_pair(index, index_adjacent);
}

void switch_direction_of_all_elements_greater_than_the_mobile(std::vector<std::pair<int, bool>>& current, int index)
{
    for (int i = 0; i < current.size(); i++)
    {
        if (current.at(i).first > current.at(index).first )
        {
            current.at(i).second = !current.at(i).second;
        }
    }
}

std::vector<std::vector<std::pair<int, bool>>> permutations(std::vector<int>& nr)
{
    std::vector<std::vector<std::pair<int, bool>>> all_of_permutations;
    std::vector<std::pair<int, bool>> current_permutation;
    // initial direction if from right to left (bool 1). Opposite direction is marked as 0.
    for(auto& item : nr)
    {
        current_permutation.push_back(std::make_pair(item, 1));
    }

    all_of_permutations.push_back(current_permutation);

    for (int i = 0; i < fact(nr.size()); i++)// fact(str.size()); //n! for string of length n
    {
        std::pair<int, int> index_of_the_largest_mobile_and_its_adjacent = find_index_of_largest_mobile_and_its_adjacent(current_permutation);

        if (index_of_the_largest_mobile_and_its_adjacent.first != -1)
        {
            std::swap(current_permutation.at(index_of_the_largest_mobile_and_its_adjacent.first).first, current_permutation.at(index_of_the_largest_mobile_and_its_adjacent.second).first);
            all_of_permutations.push_back(current_permutation);

            for (i = 0; i < current_permutation.size(); i++)
            {
                std::cout << current_permutation.at(i).first << " ";
            }

            std::cout << std::endl;
            switch_direction_of_all_elements_greater_than_the_mobile(current_permutation, index_of_the_largest_mobile_and_its_adjacent.first);
        }
        else 
            return all_of_permutations;

    }

    return all_of_permutations;
}

std::vector<std::vector<int>> permute(std::vector<int>& some_number)
{
    std::vector<std::vector<std::pair<int, bool>>> my_vec = permutations(some_number);
    std::vector<int> single_numbers = {};
    std::vector<std::vector<int>> all_combinations = {};

    for (auto item : my_vec)
    {
        for (int i = 0; i < item.size(); i++)
        {
            single_numbers.push_back(item.at(i).first);
        }

        all_combinations.push_back(single_numbers);
        single_numbers.clear();
    }

    return all_combinations;
}

int main()
{
    std::vector<int> some_number = { 1, 2, 3, 4 };
    std::vector<std::vector<int>> all_permutations = permute(some_number);

    for (auto& item : all_permutations)
    {
        for (auto& item2 : item)
        {
            std::cout << item2 << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

