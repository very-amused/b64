#pragma once
#include <stddef.h>

const size_t b64_encoded_len(const size_t len);
const size_t b64_decoded_len(const size_t encoded_len);

int b64_encode(const unsigned char *data, const size_t data_len,
		char *result, const size_t result_len);
/*int argon2_mariadb_b64_decode(const char *encoded, const size_t encoded_len,
		unsigned char *data, const size_t data_len); */
