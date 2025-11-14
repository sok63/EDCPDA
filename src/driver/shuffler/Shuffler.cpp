#include "Shuffler.h"
#include <string.h>

Shuffler::Shuffler()
    : alphabet_(nullptr)
    , matrix_(nullptr)
    , alphabet_size_(0)
    , lcg_state_(0)
{
}

Shuffler::~Shuffler()
{
}

bool Shuffler::init(const ShufflerConfig& config, char* alphabet_buffer, char* matrix_buffer)
{
    if (alphabet_buffer == nullptr || matrix_buffer == nullptr) {
        return false;
    }

    if (config.rows == 0 || config.cols == 0 || config.charset_mask == 0) {
        return false;
    }

    config_ = config;
    alphabet_ = alphabet_buffer;
    matrix_ = matrix_buffer;

    build_alphabet();

    if (alphabet_size_ == 0) {
        return false;
    }

    return true;
}

void Shuffler::build_alphabet()
{
    alphabet_size_ = 0;

    if (config_.charset_mask & CHARSET_DIGITS) {
        for (char c = '0'; c <= '9'; c++) {
            alphabet_[alphabet_size_++] = c;
        }
    }

    if (config_.charset_mask & CHARSET_UPPER) {
        for (char c = 'A'; c <= 'Z'; c++) {
            alphabet_[alphabet_size_++] = c;
        }
    }

    if (config_.charset_mask & CHARSET_LOWER) {
        for (char c = 'a'; c <= 'z'; c++) {
            alphabet_[alphabet_size_++] = c;
        }
    }

    if (config_.charset_mask & CHARSET_SPECIAL_1) {
        const char special1[] = "!@#$%^&*";
        for (size_t i = 0; i < sizeof(special1) - 1; i++) {
            alphabet_[alphabet_size_++] = special1[i];
        }
    }

    if (config_.charset_mask & CHARSET_SPECIAL_2) {
        const char special2[] = "()[]{}";
        for (size_t i = 0; i < sizeof(special2) - 1; i++) {
            alphabet_[alphabet_size_++] = special2[i];
        }
    }

    if (config_.charset_mask & CHARSET_SPECIAL_3) {
        const char special3[] = ".,;:";
        for (size_t i = 0; i < sizeof(special3) - 1; i++) {
            alphabet_[alphabet_size_++] = special3[i];
        }
    }

    if (config_.charset_mask & CHARSET_SPECIAL_4) {
        const char special4[] = "-_+=";
        for (size_t i = 0; i < sizeof(special4) - 1; i++) {
            alphabet_[alphabet_size_++] = special4[i];
        }
    }

    if (config_.charset_mask & CHARSET_SPACE) {
        alphabet_[alphabet_size_++] = ' ';
    }
}

uint32_t Shuffler::hash_fnv1a(const char* str) const
{
    uint32_t hash = FNV_OFFSET_BASIS;

    while (*str != '\0') {
        hash ^= static_cast<uint8_t>(*str);
        hash *= FNV_PRIME;
        str++;
    }

    return hash;
}

void Shuffler::lcg_seed(uint32_t seed)
{
    lcg_state_ = seed;
}

uint32_t Shuffler::lcg_next()
{
    lcg_state_ = (LCG_A * lcg_state_ + LCG_C);
    return lcg_state_;
}

uint32_t Shuffler::bounded_random(uint32_t max)
{
    if (max == 0) {
        return 0;
    }

    uint32_t threshold = (0xFFFFFFFFu - max + 1) % max;

    uint32_t value;
    do {
        value = lcg_next();
    } while (value < threshold);

    return value % max;
}

void Shuffler::fisher_yates_shuffle(char* array, size_t length)
{
    if (length <= 1) {
        return;
    }

    for (size_t i = length - 1; i > 0; i--) {
        uint32_t j = bounded_random(i + 1);

        char temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void Shuffler::shuffle_alphabet(const char* control_word)
{
    uint32_t seed = hash_fnv1a(control_word);

    size_t len = 0;
    while (control_word[len] != '\0') {
        len++;
    }
    seed ^= (len * FNV_PRIME);

    lcg_seed(seed);

    fisher_yates_shuffle(alphabet_, alphabet_size_);
}

void Shuffler::fill_matrix(const char* control_word)
{
    uint32_t seed = hash_fnv1a(control_word);

    const char* ptr = control_word;
    uint32_t pos = 0;
    while (*ptr != '\0') {
        seed ^= (static_cast<uint8_t>(*ptr) * (pos + 1) * FNV_PRIME);
        ptr++;
        pos++;
    }

    lcg_seed(seed);

    size_t matrix_size = static_cast<size_t>(config_.rows) * config_.cols;
    for (size_t i = 0; i < matrix_size; i++) {
        uint32_t idx = bounded_random(alphabet_size_);
        matrix_[i] = alphabet_[idx];
    }
}

void Shuffler::swap_rows(uint16_t row1, uint16_t row2)
{
    if (row1 == row2) {
        return;
    }

    size_t offset1 = static_cast<size_t>(row1) * config_.cols;
    size_t offset2 = static_cast<size_t>(row2) * config_.cols;

    for (uint16_t col = 0; col < config_.cols; col++) {
        char temp = matrix_[offset1 + col];
        matrix_[offset1 + col] = matrix_[offset2 + col];
        matrix_[offset2 + col] = temp;
    }
}

void Shuffler::swap_cols(uint16_t col1, uint16_t col2)
{
    if (col1 == col2) {
        return;
    }

    for (uint16_t row = 0; row < config_.rows; row++) {
        size_t offset = static_cast<size_t>(row) * config_.cols;
        char temp = matrix_[offset + col1];
        matrix_[offset + col1] = matrix_[offset + col2];
        matrix_[offset + col2] = temp;
    }
}

void Shuffler::permute_rows(const char* control_word)
{
    uint32_t seed = hash_fnv1a(control_word);

    const char* ptr = control_word;
    uint32_t pos = 0;
    while (*ptr != '\0') {
        seed = seed * FNV_PRIME + static_cast<uint8_t>(*ptr) * (pos * pos + 1);
        ptr++;
        pos++;
    }

    lcg_seed(seed);

    // Fisher-Yates for rows
    for (uint16_t i = config_.rows - 1; i > 0; i--) {
        uint32_t j = bounded_random(i + 1);
        swap_rows(i, static_cast<uint16_t>(j));
    }
}

void Shuffler::permute_cols(const char* control_word)
{
    uint32_t seed = hash_fnv1a(control_word);

    const char* ptr = control_word;
    uint32_t pos = 0;
    while (*ptr != '\0') {
        seed = seed + (static_cast<uint8_t>(*ptr) ^ (pos + 7)) * FNV_PRIME;
        ptr++;
        pos++;
    }

    lcg_seed(seed);

    // Fisher-Yates for cols
    for (uint16_t i = config_.cols - 1; i > 0; i--) {
        uint32_t j = bounded_random(i + 1);
        swap_cols(i, static_cast<uint16_t>(j));
    }
}

bool Shuffler::shuffle(const char* control_word1, const char* control_word2)
{
    if (control_word1 == nullptr || control_word2 == nullptr) {
        return false;
    }

    if (alphabet_ == nullptr || matrix_ == nullptr || alphabet_size_ == 0) {
        return false;
    }

    shuffle_alphabet(control_word1);

    fill_matrix(control_word1);

    permute_rows(control_word2);
    permute_cols(control_word2);

    return true;
}

const char* Shuffler::get_matrix() const
{
    return matrix_;
}

uint16_t Shuffler::get_rows() const
{
    return config_.rows;
}

uint16_t Shuffler::get_cols() const
{
    return config_.cols;
}

size_t Shuffler::get_alphabet_size() const
{
    return alphabet_size_;
}
