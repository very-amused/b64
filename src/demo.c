#include "base64.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	size_t data_len = 255;
	char *data = malloc(data_len * sizeof(char));
	printf("Input text: ");
	data_len = getline(&data, &data_len, stdin);
	data_len--; // Disregard trailing newline
	data[data_len] = '\0';

	const size_t encoded_len = b64_encoded_len(data_len);
	char *encoded = malloc(encoded_len * sizeof(char) + 1);
	encoded[encoded_len] = '\0';
	int result;
	result = b64_encode((unsigned char *)data, data_len, encoded, encoded_len);
	if (result != 0) {
		goto end;
	}
	printf("Encoded text: %s\n", encoded);

	if (data_len != b64_decoded_len(encoded, encoded_len)) {
		return 2;
	}
	result = b64_decode(encoded, encoded_len, (unsigned char *)data, data_len);
	if (result != 0) {
		goto end;
	}
	printf("Decoded text: %s\n", data);

end:
	free(data);
	free(encoded);
	return result;
}
