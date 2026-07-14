// Copyright 2024
// Miryoku layout mapping for the Eyelash Sofle keyboard.
//
// The Eyelash Sofle physical layout has 64 keys arranged as:
//   Row 0: 13 keys  (6 left + 1 middle + 6 right)   -- top extras (number row)
//   Row 1: 13 keys  (6 left + 1 middle + 6 right)   -- top alpha row
//   Row 2: 13 keys  (6 left + 1 middle + 6 right)   -- home row
//   Row 3: 13 keys  (6 left + 1 middle + 6 right)   -- bottom alpha row
//   Row 4: 12 keys  (1 left encoder-btn + 3 inner-lower + 2 left thumb cluster
//                    + 1 right encoder-btn + 2 right thumb cluster + 3 inner-lower)
//
// Miryoku uses a 30 alpha + 6 thumb layer with 4 "not-present" slots:
//     K00 K01 K02 K03 K04            K05 K06 K07 K08 K09
//     K10 K11 K12 K13 K14            K15 K16 K17 K18 K19
//     K20 K21 K22 K23 K24            K25 K26 K27 K28 K29
//         N30 N31 K32 K33 K34    K35 K36 K37 N38 N39
//
// The Eyelash Sofle has 3 usable thumb positions per hand (the inner
// bottom-row key plus two rotated thumb-cluster keys), so we can map all
// six thumb slots (K32..K37) directly. The remaining 32 physical keys are
// forced to &none (or a hardcoded encoder-press action) so the Miryoku
// framework only sees the canonical 36-key layout.

#if !defined (MIRYOKU_LAYOUTMAPPING_EYELASH_SOFLE)

#define XXX &none

// The two encoder-press positions (row 4 col 0 on the left, row 4 col 7
// on the right) stay active on every layer so the rotary encoders remain
// useful even when a Miryoku layer is held.
#define MIRYOKU_EYELASH_ENC_L &kp C_MUTE
#define MIRYOKU_EYELASH_ENC_R &kp C_PLAY_PAUSE

#define MIRYOKU_LAYOUTMAPPING_EYELASH_SOFLE( \
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39 \
) \
XXX  XXX  XXX  XXX  XXX  XXX                          XXX  XXX  XXX  XXX  XXX  XXX  XXX \
XXX  K00  K01  K02  K03  K04                          XXX  K05  K06  K07  K08  K09  XXX \
XXX  K10  K11  K12  K13  K14                          XXX  K15  K16  K17  K18  K19  XXX \
XXX  K20  K21  K22  K23  K24                          XXX  K25  K26  K27  K28  K29  XXX \
MIRYOKU_EYELASH_ENC_L  N30  N31  K32  K33  K34        MIRYOKU_EYELASH_ENC_R  K35  K36  K37  N38  N39

#endif

#define MIRYOKU_MAPPING MIRYOKU_LAYOUTMAPPING_EYELASH_SOFLE
