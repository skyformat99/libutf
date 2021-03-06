/*
 *    This file is part of libutf.
 *
 *    libutf is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    libutf is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with libutf.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libutf/utf8.h>

size_t utf8_decode(const char * in_s, char32_t * out){

	const unsigned char * in = (const unsigned char *)(in_s);

	if (in[0] <= 0x7F){
		*out = 0x7F & in[0];
		return 1;
	} else if (in[0] <= 0xDF){
		*out = (0x1F & in[0]) << 0x06;
		*out += 0x3F & in[1];
		return 2;
	} else if (in[0] <= 0xEF){
		*out = (0x0F & in[0]) << 0x0C;
		*out += (0x3F & in[1]) << 0x06;
		*out += 0x3F & in[2];
		return 3;
	} else if (in[0] <= 0xF7){
		*out = (0x07 & in[0]) << 0x12;
		*out += (0x3F & in[1]) << 0x0C;
		*out += (0x3F & in[2]) << 0x06;
		*out += 0x3F & in[3];
		return 4;
	}

	/* out of range */
	return 0;
}

size_t utf8_decode_length(char in_s){

	unsigned char in = (unsigned char)(in_s);

	if (in < 0x80){
		return 1;
	} else if (in < 0xE0){
		return 2;
	} else if (in < 0xF0){
		return 3;
	} else if (in < 0xF8){
		return 4;
	}

	/* out of range */
	return 0;
}

size_t utf8_decode_string(const char * in, char32_t * out){

	int i = 0;
	int j = 0;
	int k = 0;

	while (in[i]){
		j = utf8_decode(&in[i], &out[k]);
		if (!j){
			return i;
		} else {
			i += j;
		}
		k++;
	}

	return i;
}

size_t utf8_encode(char32_t in, char * out){

	if (in < 0x80){
		out[0] = (char) in;
		return 1;
	} else if (in < 0x0800){
		out[0] = (char) (((in >> 0x06) & 0x1F)) | 0xC0;
		out[1] = (char) (((in >> 0x00) & 0x3F)) | 0x80;
		return 2;
	} else if (in < 0x010000){
		out[0] = (char) (((in >> 0x0C) & 0x0F)) | 0xE0;
		out[1] = (char) (((in >> 0x06) & 0x3F)) | 0x80;
		out[2] = (char) (((in >> 0x00) & 0x3F)) | 0x80;
		return 3;
	} else if (in < 0x110000){
		out[0] = (char) (((in >> 0x12) & 0x07)) | 0xF0;
		out[1] = (char) (((in >> 0x0C) & 0x3F)) | 0x80;
		out[2] = (char) (((in >> 0x06) & 0x3F)) | 0x80;
		out[3] = (char) (((in >> 0x00) & 0x3F)) | 0x80;
		return 4;
	}

	/* out of range */
	return 0;
}

size_t utf8_encode_length(char32_t in){

	if (in < 0x80){
		return 1;
	} else if (in < 0x800){
		return 2;
	} else if (in < 0x010000){
		return 3;
	} else if (in < 0x110000){
		return 4;
	}

	/* out of range */
	return 0;
}

size_t utf8_strlen(const char * in, unsigned int in_size){
	size_t i = 0;
	size_t j = 0;
	size_t size = 0;
	while (i < in_size){
		j = utf8_decode_length(in[i]);
		if (j == 0){
			break;
		}
		i += j;
		size++;
	}
	return size;
}

char32_t * utf8_to_utf32(const char * in){

	size_t in_size;

	for (in_size = 0; in[in_size]; in_size++);

	return utf8_to_utf32_s(in, in_size, NULL);
}

char32_t * utf8_to_utf32_s(const char * in, size_t in_len, size_t * out_len_ptr){

	char32_t out_char;
	char32_t * tmp;
	char32_t * out = NULL;
	size_t out_len = 0;
	size_t i;
	size_t point_size;

	i = 0;

	while (i < in_len){
		point_size = utf8_decode_length(in[i]);
		if ((point_size == 0) || (point_size > (in_len - i))){
			break;
		}
		if (utf8_decode(&in[i], &out_char) != point_size){
			break;
		}
		out_len++;
		tmp = realloc(out, sizeof(*out) * (out_len + 1));
		if (tmp == NULL){
			free(out);
			return NULL;
		}
		out = tmp;
		out[out_len - 1] = out_char;
		out[out_len - 0] = 0;
		i += point_size;
	}

	if (out_len_ptr != 0){
		*out_len_ptr = out_len;
	}

	return out;
}

