#include "base64.h"
#include <stdlib.h>

static const char STD_ENCODING[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const size_t b64_encoded_len(const size_t len) {
	return ((len / 3) * 4) + (len % 3 > 0 ? 4 : 0);
}

const size_t b64_decoded_len(const size_t encoded_len) {
	return ((encoded_len/ 4) * 3) + // Each full group of 4 encoded -> 4 bytes
		(encoded_len % 4 > 0) + // Add trailing bytes
		(encoded_len % 4 > 0 ? 1 : 0); // If there are trailing bytes present, the decoded result will be 1 byte less
}

// Encode up to 3 bytes from src into dst
static void encode_group(const unsigned char *data, const size_t data_len, char *result) {
	// Byte 1
	result[0] = STD_ENCODING[data[0] >> 2];

	// Byte 2
	if (data_len == 1) {
		result[1] = STD_ENCODING[data[0] << 4 & 0x30];
		return;
	}
	result[1] = STD_ENCODING[data[0] << 4 & 0x30 | data[1] >> 4];

	// Byte 3
	if (data_len == 2) {
		result[2] = STD_ENCODING[data[1] << 2 & 0x3C];
		return;
	}
	result[2] = STD_ENCODING[data[1] << 2 & 0x3C | data[2] >> 6];

	// Byte 4
	result[3] = STD_ENCODING[data[2] & 0x3F];
}

// Decode up to 2 base64 indexes to result
static void decode_group(const unsigned char *indexes, unsigned char *result, const size_t result_len) {
	// Byte 1
	result[0] = indexes[0] << 2 | indexes[1] >> 4;
	if (result_len == 1) {
		return;
	}

	// Byte 2
	result[1] = indexes[1] << 4 | indexes[2] >> 2;
	if (result_len == 2) {
		return;
	}

	// Byte 3
	result[2] = indexes[2] << 6 | indexes[3];
}

// ASCII to index,
// Convert each ASCII character code in encoded to a usable index for decoding
// *indexes will be allocated and thus should not be allocated before calling
static int _atoi(const unsigned char *encoded, const size_t encoded_len, unsigned char **indexes, size_t *indexes_len) {
	*indexes_len = encoded_len;
	// Strip up to 2 padding characters off the end
	for (size_t i = encoded_len - 2; i < encoded_len; i++) {
		if (encoded[i] == '=') {
			(*indexes_len)--;
		}
	}
	*indexes = malloc(*indexes_len * sizeof(unsigned char));

	// Convert from ASCII character codes to 0-63
	for (size_t i = 0; i < *indexes_len; i++) {
		if (encoded[i] >= '0' && encoded[i] <= '9') {
			// 0-9
			*indexes[i] = encoded[i] + 4;
		} else if (encoded[i] >= 'A' && encoded[i] <= 'Z') {
			// A-Z
			*indexes[i] = encoded[i] - 65;
		} else if (encoded[i] >= 'a' && encoded[i] <= 'z') {
			// a-z
			*indexes[i] = encoded[i] - 71;
		} else if (encoded[i] == '+') {
			// +
			*indexes[i] = 62;
		} else if (encoded[i] == '/') {
			// /
			*indexes[i] = 63;
		} else {
			// Invalid character
			return 1;
		}
	}

	return 0;
}

int b64_encode(const unsigned char *data, const size_t data_len, char *result, const size_t result_len) {
	if (result_len != b64_encoded_len(data_len)) {
		return 1;
	}
	size_t data_offset = 0, // Offset from beinning of data
				result_offset = 0; // Offset from beginning of result
	// Encode all groups of 3 bytes
	for (; data_offset < data_len - 2; data_offset += 3, result_offset += 4) {
		encode_group(data + data_offset, 3, result + result_offset);
	}

	// Encode trailing bytes and add padding
	switch (data_len % 3) {
	case 1:
		encode_group(data + (data_len - 1), 1, result + (result_len - 4));
		result[result_len - 2] = '=';
		result[result_len - 1] = '=';
		break;

	case 2:
		encode_group(data + (data_len - 2), 2, result + (result_len - 4));
		result[result_len - 1] = '=';
	}

	return 0;
}

