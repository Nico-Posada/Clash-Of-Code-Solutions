#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <x86intrin.h>

#define _512_BIT_CHUNK_SIZE 64

int main()
{
    char message[256];
    scanf("%[^\n]", message);

    unsigned hashes[8] = { 
        0xcbbb9d5d, 0x629a292a, 0x9159015a, 0x152fecd8,
        0x67332667, 0x8eb44a87, 0xdb0c2e0d, 0x47b5481d
    };

    const unsigned cube_roots[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    
    const unsigned str_len = strlen(message);
    const unsigned bit_len = str_len * 8U;

    // init bitsets
    const unsigned to_alloc = _512_BIT_CHUNK_SIZE * ((unsigned char)(bit_len >> 9) + 1);
    unsigned char* bitsets = malloc(to_alloc);
    memset(bitsets, 0, to_alloc);

    // append the string
    memcpy(bitsets, message, str_len);

    // do the rest of SHA-256 boilerplate
    bitsets[str_len] = 0b10000000;
    int cur_size = str_len;
    while (cur_size % _512_BIT_CHUNK_SIZE != 60)
        bitsets[++cur_size] = 0U;

    *(unsigned*)&bitsets[cur_size] = _bswap(bit_len);
    cur_size += 4;

    // perform compression and getting hash value for each chunk
    int chunks = cur_size / _512_BIT_CHUNK_SIZE;
    for (int chunk = 0; chunk < chunks; ++chunk)
    {
        int offset = chunk * _512_BIT_CHUNK_SIZE;

        // convert to bitsets of size 32
        unsigned bitsets_32[_512_BIT_CHUNK_SIZE] = {0};
        for (int i = offset; i < _512_BIT_CHUNK_SIZE + offset; i += 4)
            bitsets_32[(i/4) & 0xF] = _bswap(*(unsigned*)&bitsets[i]);

        // perform the first chunk thingy idk
        for (int i = 16; i < _512_BIT_CHUNK_SIZE; ++i)
        {
            unsigned n1 = bitsets_32[i - 15];
            unsigned n2 = bitsets_32[i - 2];

            unsigned s0 = _rotr(n1, 7) ^ _rotr(n1, 18) ^ (n1 >> 3);
            unsigned s1 = _rotr(n2, 17) ^ _rotr(n2, 19) ^ (n2 >> 10);

            unsigned result = bitsets_32[i - 16] + s0 + bitsets_32[i - 7] + s1;
            bitsets_32[i] = result;
        }

        unsigned a = hashes[0], b = hashes[1], c = hashes[2], d = hashes[3], e = hashes[4], f = hashes[5], g = hashes[6], h = hashes[7];
        for (int i = 0; i < _512_BIT_CHUNK_SIZE; ++i)
        {
            unsigned S1 = _rotr(e, 6) ^ _rotr(e, 11) ^ _rotr(e, 25);
            unsigned ch = (e & f) ^ (~e & g);
            unsigned temp1 = h + S1 + ch + cube_roots[i] + bitsets_32[i];
            unsigned S0 = _rotr(a, 2) ^ _rotr(a, 13) ^ _rotr(a, 22);
            unsigned maj = (a & b) ^ (a & c) ^ (b & c);
            unsigned temp2 = S0 + maj;
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        hashes[0] += a;
        hashes[1] += b;
        hashes[2] += c;
        hashes[3] += d;
        hashes[4] += e;
        hashes[5] += f;
        hashes[6] += g;
        hashes[7] += h;
    }

    for (int i = 0; i < sizeof(hashes) / sizeof(unsigned); ++i)
        printf("%08x", hashes[i]);

    free(bitsets);
}
