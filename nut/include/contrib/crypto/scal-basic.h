/* scal-basic.h */
/*
    This file is part of the ARM-Crypto-Lib.
    Copyright (C) 2011  Daniel Otte (daniel.otte@rub.de)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCAL_BASIC_H_
#define SCAL_BASIC_H_

#include <stdlib.h>
#include <stdint.h>
#include <crypto/streamcipher_descriptor.h>
#include <crypto/keysize_descriptor.h>

uint8_t scal_cipher_init(const scdesc_t* cipher_descriptor,
                         const void* key, uint16_t keysize_b,
                         const void* iv,  uint16_t ivsize_b, scgen_ctx_t* ctx);
void scal_cipher_free(scgen_ctx_t* ctx);
uint8_t scal_cipher_gen_byte(scgen_ctx_t* ctx);
void scal_cipher_gen_block(void* block, scgen_ctx_t* ctx);
void scal_cipher_gen_fillblock(void* block, uint16_t blocksize_B, scgen_ctx_t* ctx);
uint16_t scal_cipher_getBlocksize_b(const scdesc_t* desc);
void* scal_cipher_getKeysizeDesc(const scdesc_t* desc);
void* scal_cipher_getIVsizeDesc(const scdesc_t* desc);


#endif /* SCAL_BASIC_H_ */
