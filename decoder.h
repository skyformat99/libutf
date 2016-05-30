/*
 *    This file is part of Utfx.
 *
 *    Utfx is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Utfx is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Utfx.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTFX_DECODER_H
#define UTFX_DECODER_H

#include "utf32.h"
#include "error.h"

/**
 * @defgroup utfx_decoder utfx_decoder
 * @brief A UTF-8, UTF-16 and UTF-32 decoder
 */

/** The mode of the decoder.
 * This is a combination of the choice of codec and choice of byte order.
 * @ingroup utfx_decoder
 */

typedef enum utfx_decoder_mode {
	/** No mode has been set. */
	UTFX_DECODER_MODE_NONE = 0,
	/** Mode is UTF-8 */
	UTFX_DECODER_MODE_UTF8,
	/** Mode is UTF-16 (little endian) */
	UTFX_DECODER_MODE_UTF16_LE,
	/** Mode is UTF-16 (big endian) */
	UTFX_DECODER_MODE_UTF16_BE,
	/** Mode is UTF-32 (little endian) */
	UTFX_DECODER_MODE_UTF32_LE,
	/** Mode is UTF-32 (big endian) */
	UTFX_DECODER_MODE_UTF32_BE,
	/** Mode is unknown */
	UTFX_DECODER_MODE_UNKNOWN = -1
} utfx_decoder_mode_t;

/** A UTF-8, UTF-16 and UTF-32 decoder.
 * It may be used so that, once the mode is set, the decoding of the input text may be abstracted.
 * @ingroup utfx_decoder
 */

typedef struct {
	/** The mode of the decoder */
	utfx_decoder_mode_t mode;
	/** The last decoded character */
	utf32_t output_char;
} utfx_decoder_t;

/** Initializes a decoder structure.
 * @ingroup utfx_decoder
 */

void utfx_decoder_init(utfx_decoder_t * decoder);

/** Returns the mode of the decoder.
 * @param decoder An initialized decoder structure.
 * @returns The current mode of the decoder.
 * @ingroup utfx_decoder
 */

utfx_decoder_mode_t utfx_decoder_get_mode(const utfx_decoder_t * decoder);

/** Calculate the number of bytes that the input code is expected to occupy.
 * This is usefull for bounds checking.
 * @param decoder An initialized decoder structure.
 * @param input_char A pointer to a UTF-8, UTF-16 or UTF-32 sequence.
 * @param input_size A pointer to the variable that the expected size will be assigned to.
 * @returns On success, @ref UTFX_ERROR_NONE is returned.
 * @ingroup utfx_decoder
 */

utfx_error_t utfx_decoder_get_input_size(utfx_decoder_t * decoder, const void * input_char, unsigned int * input_size);

/** Get the last decoded character from the decoder.
 * @param decoder An initialized decoder structure.
 * @returns The last output character that was decoded.
 * @ingroup utfx_decoder
 */

utf32_t utfx_decoder_get_output_char(const utfx_decoder_t * decoder);

/** Decode an input sequence.
 * @param decoder An intialized decoder structure.
 * @param input_char A UTF-8, UTF-16 or UTF-32 sequence.
 * @returns On success, @ref UTFX_ERROR_NONE is returned.
 * @ingroup utfx_decoder
 */

utfx_error_t utfx_decoder_put_input_char(utfx_decoder_t * decoder, const void * input_char);

/** Decode an input sequence. Fail if the input buffer size isn't large enough.
 * @param decoder An intialized decoder structure.
 * @param input_char A UTF-8, UTF-16 or UTF-32 sequence.
 * @param input_size The maximum size, in bytes, that the decoder can access without failing.
 * @returns On success, @ref UTFX_ERROR_NONE is returned.
 * @ingroup utfx_decoder
 */

utfx_error_t utfx_decoder_put_input_char_safely(utfx_decoder_t * decoder, const void * input_char, unsigned int input_size);

/** Sets the mode of decoder.
 * Setting the mode to @ref UTFX_DECODER_MODE_NONE or @ref UTFX_DECODER_MODE_UNKNOWN will cause errors in subsequent calls to the decoder.
 * @ingroup utfx_decoder
 */

void utfx_decoder_set_mode(utfx_decoder_t * decoder, utfx_decoder_mode_t mode);

#endif /* UTFX_DECODER_H */

