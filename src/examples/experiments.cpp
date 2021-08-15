#include <vector>
#include <fstream>
#include <iostream>
#include "lipp.h"

template<typename Key>
std::vector<Key> load_data(const std::string &filename) {
    using key_type = Key;

    /* Open file. */
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
        exit(EXIT_FAILURE);

    /* Read number of keys. */
    uint64_t n_keys;
    in.read(reinterpret_cast<char*>(&n_keys), sizeof(uint64_t));

    /* Initialize vector. */
    std::vector<key_type> data;
    data.resize(n_keys);

    /* Read keys. */
    in.read(reinterpret_cast<char*>(data.data()), n_keys * sizeof(key_type));
    in.close();

    return data;
}

int main(int argc, char *argv[])
{
    /* Load keys. */
    auto keys = load_data<uint64_t>("data/wiki_ts_200M_uint64");

    std::vector<std::pair<uint64_t, uint64_t>>  key_value_pairs;
    key_value_pairs.reserve(keys.size());

    for (auto& key : keys) {
      key_value_pairs.push_back(std::make_pair(key, 100));
    }
    std::cout << "keys loaded" << std::endl;

    /* Build LIPP. */
    LIPP<uint64_t, uint64_t> lipp;
    lipp.bulk_load(key_value_pairs.data(), key_value_pairs.size());
    std::cout << "LIPP index built succesfully" << std::endl;
}

