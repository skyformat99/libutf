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

/* The following comment tells doxygen to parse the comments of this file. */

/** @file */

#ifndef LIBUTF_UTF32_H
#define LIBUTF_UTF32_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** The UTF-32 data type.
 * This is the type that all codecs are decoded to and decoded from.
 * For client code using this library, it is the ideal type to use for parsing since it can be directly indexed.
 * @ingroup libutf-procedural
 */

typedef uint32_t utf32_t;

/** The maximum value of a UTF-32 value.
 * Note that this is not the same as the maximum of the data type.
 * @ingroup libutf-procedural
 */

extern const utf32_t utf32_max;

/** The minimum value of a UTF-32 value.
 * This value is zero, and is here mainly for symmetry.
 * @ingroup libutf-procedural
 */

extern const utf32_t utf32_min;

/** Converts a UTF-32BE sequence to a UTF-32 native endian type.
 * @param src The address of the UTF-32LE sequence.
 * @returns The UTF-32 sequence in native endian format.
 * @ingroup libutf-procedural
 */

utf32_t utf32be(const void * src);

/** Converts a UTF-32LE sequence to a UTF-32 native endian type.
 * @param src The address of the UTF-32LE sequence.
 * @returns The UTF-32 sequence in native endian format.
 * @ingroup libutf-procedural
 */

utf32_t utf32le(const void * src);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBUTF_UTF32_H */
