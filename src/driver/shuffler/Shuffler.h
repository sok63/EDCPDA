#pragma once

#include <stddef.h>
#include <stdint.h>

#define CHARSET_DIGITS 0x01 // 0-9
#define CHARSET_UPPER 0x02 // A-Z
#define CHARSET_LOWER 0x04 // a-z
#define CHARSET_SPECIAL_1 0x08 // !@#$%^&*
#define CHARSET_SPECIAL_2 0x10 // ()[]{}
#define CHARSET_SPECIAL_3 0x20 // .,;:
#define CHARSET_SPECIAL_4 0x40 // -_+=
#define CHARSET_SPACE 0x80 // space

struct ShufflerConfig
{
    uint8_t charset_mask;
    uint16_t rows;
    uint16_t cols;
};

class Shuffler
{
public:
    Shuffler();
    ~Shuffler();

    bool init(const ShufflerConfig& config, char* alphabet_buffer, char* matrix_buffer);
    bool shuffle(const char* control_word1, const char* control_word2);

    const char* get_matrix() const;

    uint16_t get_rows() const;
    uint16_t get_cols() const;

    size_t get_alphabet_size() const;

private:
    // LCG Numerical Recipes
    static const uint32_t LCG_A = 1664525u;
    static const uint32_t LCG_C = 1013904223u;

    // FNV-1a
    static const uint32_t FNV_OFFSET_BASIS = 2166136261u;
    static const uint32_t FNV_PRIME = 16777619u;

    ShufflerConfig config_;
    char* alphabet_;
    char* matrix_;
    size_t alphabet_size_;
    uint32_t lcg_state_;

    void build_alphabet();

    uint32_t hash_fnv1a(const char* str) const;

    uint32_t lcg_next();

    void lcg_seed(uint32_t seed);

    uint32_t bounded_random(uint32_t max);

    void fisher_yates_shuffle(char* array, size_t length);

    void shuffle_alphabet(const char* control_word);

    void fill_matrix(const char* control_word);

    void permute_rows(const char* control_word);
    void permute_cols(const char* control_word);

    void swap_rows(uint16_t row1, uint16_t row2);
    void swap_cols(uint16_t col1, uint16_t col2);
};
