/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct _BDelta_Instance BDelta_Instance;

// Callback function must return a pointer to the data requested.
// A "fill and forget" buffer is provided, but can be ignored, so
// long as the data persists throughout the life of bdelta_pass().
typedef const void *(*bdelta_readCallback)(void *handle, void *buf, unsigned place, unsigned num);

BDelta_Instance *bdelta_init_alg(unsigned data1_size, unsigned data2_size,
		bdelta_readCallback cb, void *handle1, void *handle2,
		unsigned tokenSize);
void bdelta_done_alg(BDelta_Instance *b);

void bdelta_pass(BDelta_Instance *b, unsigned blockSize, unsigned minMatchSize, unsigned maxHoleSize, unsigned flags);

void bdelta_swap_inputs(BDelta_Instance *b);
void bdelta_clean_matches(BDelta_Instance *b, unsigned flags);

unsigned bdelta_numMatches(BDelta_Instance *b);

void bdelta_getMatch(BDelta_Instance *b, unsigned matchNum,
	unsigned *p1, unsigned *p2, unsigned *num);

int bdelta_getError(BDelta_Instance *b);
void bdelta_showMatches(BDelta_Instance *b);

// Flags for bdelta_pass()
#define BDELTA_GLOBAL 1
#define BDELTA_SIDES_ORDERED 2

// Flags for bdelta_clean_matches()
#define BDELTA_REMOVE_OVERLAP 1

enum BDELTA_RESULT {
	BDELTA_OK         =  0,
	BDELTA_MEM_ERROR  = -1,
	BDELTA_READ_ERROR = -2
};

#ifdef __cplusplus
}
#endif // __cplusplus
