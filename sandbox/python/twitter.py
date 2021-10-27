def combinations(list_get_comb, length_combination):
    """ Generator to get all the combinations of some length of the elements of a list.

    :param list_get_comb: (list) List from which it is wanted to get the combination of its elements.
    :param length_combination: (int) Length of the combinations of the elements of list_get_comb.
    :return:
        * :generator: Generator with the combinations of this list.
    """

    # Generator to get the combinations of the indices of the list
    def get_indices_combinations(sub_list_indices, max_index):
        """ Generator that returns the combinations of the indices

        :param sub_list_indices: (list) Sub-list from which to generate ALL the possible combinations.
        :param max_index: (int) Maximum index.
        :return:
        """
        if len(sub_list_indices) == 1:  # Last index of the list of indices
            for index in range(sub_list_indices[0], max_index + 1):
                yield [index]
        elif all([sub_list_indices[-i - 1] == max_index - i for i in
                  range(len(sub_list_indices))]):  # The current sublist has reached the end
            yield sub_list_indices
        else:
            for comb in get_indices_combinations(sub_list_indices[1:],
                                                 max_index):  # Get all the possible combinations of the sublist sub_list_indices[1:]
                yield [sub_list_indices[0]] + comb
            # Advance one position and check all possible combinations
            new_sub_list = []
            new_sub_list.extend([sub_list_indices[0] + i + 1 for i in range(len(sub_list_indices))])
            for new_comb in get_indices_combinations(new_sub_list, max_index):
                yield new_comb  # Return all the possible combinations of the new list

    # Start the algorithm:
    sub_list_indices = list(range(length_combination))
    for list_indices in get_indices_combinations(sub_list_indices, len(list_get_comb) - 1):
        yield [list_get_comb[i] for i in list_indices]



comb = combinations([])