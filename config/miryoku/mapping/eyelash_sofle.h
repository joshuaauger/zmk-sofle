// Copyright 2024
// Miryoku layout mapping for the Eyelash Sofle keyboard.
//
// The Eyelash Sofle is NOT a canonical 36-key board — it is a 64-key
// Sofle variant with a middle "arrow diamond" cluster, a number row,
// outer pinky columns on both sides, and 4 extra inner-bottom keys.
// Miryoku only knows about 30 alphas + 6 thumbs (+ 4 optional "not
// present" slots), so this mapping keeps the Miryoku core on the alpha
// block and hard-codes useful defaults for the 28 extra physical keys
// instead of leaving them dead.
//
// Physical position summary (x/y from config/eyelash_sofle.json):
//
//   Row 0 (number row, y ≈ 0.25):
//     col 0..5:  left outer pinkie + N1..N5             (6 keys)
//     col 7:     ARROW-DIAMOND TOP  (x=9.25, y=0.25)    (1 key)
//     col 8..13: N6..N0 + right outer pinkie            (6 keys)
//
//   Row 1 (top alpha, y ≈ 1.25):
//     col 0..5:  outer + Q..T                            (6 keys)
//     col 7:     ARROW-DIAMOND BOTTOM (x=9.25, y=2.25)   (1 key)
//     col 8..13: Y..P + outer                            (6 keys)
//
//   Row 2 (home row, y ≈ 2.25):
//     col 0..5:  outer + A..G                            (6 keys)
//     col 7:     ARROW-DIAMOND LEFT   (x=8.25, y=1.25)   (1 key)
//     col 8..13: H..' + outer                            (6 keys)
//
//   Row 3 (bottom alpha, y ≈ 3.25):
//     col 0..5:  outer + Z..B                            (6 keys)
//     col 7:     ARROW-DIAMOND RIGHT  (x=10.25, y=1.25)  (1 key)
//     col 8..13: N../ + outer                            (6 keys)
//
//   Row 4 (thumbs + encoder + arrow-center):
//     col 0:  left encoder press  (x=8, y=3.5)
//     col 1:  left extra (x=3.5)     [orig LCTRL]
//     col 2:  left extra (x=4.5)     [orig LGUI]
//     col 3:  left inner-thumb (x=5.5)                 → Miryoku tertiary L
//     col 4:  left thumb outer, rotated (x=7)          → Miryoku primary  L
//     col 5:  left thumb inner, rotated (x=8.25)       → Miryoku secondary L
//     col 7:  ARROW-DIAMOND CENTER (x=9.25, y=1.25)    [orig ENTER]
//     col 8:  right thumb inner, rotated (x=10.25)     → Miryoku secondary R
//     col 9:  right thumb outer, rotated (x=11.5)      → Miryoku primary  R
//     col 10: right inner-thumb (x=13)                 → Miryoku tertiary R
//     col 11: right extra (x=14)     [orig RSHFT]
//     col 12: right extra (x=15)     [orig DELETE]
//
// Miryoku parameter positions:
//     K00 K01 K02 K03 K04            K05 K06 K07 K08 K09
//     K10 K11 K12 K13 K14            K15 K16 K17 K18 K19
//     K20 K21 K22 K23 K24            K25 K26 K27 K28 K29
//         N30 N31 K32 K33 K34    K35 K36 K37 N38 N39
//
// N30 / N31 / N38 / N39 are always &none from Miryoku's layer files
// (they represent "not present" positions on the canonical layout). We
// accept them in the parameter list for interface compatibility but
// route the corresponding physical keys to hard-coded modifiers instead.

#if !defined (MIRYOKU_LAYOUTMAPPING_EYELASH_SOFLE)

// ---- Always-on extras (layer-transparent) --------------------------------
// These bindings appear on every layer (Miryoku included) because they
// are inserted directly into the mapping expansion below rather than
// being routed through the layer definitions.

// Left encoder push button (Row 4, col 0).
#define ES_ENC_L    &kp C_MUTE

// Arrow diamond cluster in the middle column.
#define ES_ARROW_U  &kp UP
#define ES_ARROW_D  &kp DOWN
#define ES_ARROW_L  &kp LEFT
#define ES_ARROW_R  &kp RIGHT
// Diamond CENTER key — Enter here matches the vendor keymap, and gives
// you a thumb-free Enter when the right thumb is holding a layer.
#define ES_ARROW_C  &kp RET

// Number row (Row 0). ESC/BSPC on outer pinkies match the vendor layout.
#define ES_R0_L0    &kp ESC
#define ES_R0_L1    &kp N1
#define ES_R0_L2    &kp N2
#define ES_R0_L3    &kp N3
#define ES_R0_L4    &kp N4
#define ES_R0_L5    &kp N5
#define ES_R0_R1    &kp N6
#define ES_R0_R2    &kp N7
#define ES_R0_R3    &kp N8
#define ES_R0_R4    &kp N9
#define ES_R0_R5    &kp N0
#define ES_R0_R6    &kp BSPC

// Outer pinky columns for rows 1..3.
#define ES_R1_L0    &kp TAB
#define ES_R1_R6    &kp BSLH
#define ES_R2_L0    &caps_word
#define ES_R2_R6    &kp SEMI       // ':' when shifted — Miryoku's SQT is on K19
#define ES_R3_L0    &kp LSHFT
#define ES_R3_R6    &kp ENTER      // second Enter, mirrors vendor keymap

// Row-4 hard-coded extras (were N30 / N31 / N38 / N39 in Miryoku).
#define ES_R4_L1    &kp LCTRL      // orig LCTRL slot
#define ES_R4_L2    &kp LGUI       // orig LGUI  slot
#define ES_R4_R4    &kp RSHFT      // orig RSHFT slot
#define ES_R4_R5    &kp DEL        // orig DELETE slot

// ---- Miryoku layout mapping macro ----------------------------------------
//
// Miryoku's layer alternatives supply 40 tokens (K00..K29, N30, N31,
// K32..K37, N38, N39). We accept all 40 for interface compatibility but
// only route K00..K29 and K32..K37 into physical positions; the four
// N-slots (which are always U_NP / &none in Miryoku's layer files) are
// intentionally dropped so we can put LCTRL/LGUI/RSHFT/DEL at those
// physical positions instead.

#define MIRYOKU_LAYOUTMAPPING_EYELASH_SOFLE( \
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39 \
) \
ES_R0_L0  ES_R0_L1  ES_R0_L2  ES_R0_L3  ES_R0_L4  ES_R0_L5           ES_ARROW_U   ES_R0_R1  ES_R0_R2  ES_R0_R3  ES_R0_R4  ES_R0_R5  ES_R0_R6 \
ES_R1_L0  K00       K01       K02       K03       K04                ES_ARROW_D   K05       K06       K07       K08       K09       ES_R1_R6 \
ES_R2_L0  K10       K11       K12       K13       K14                ES_ARROW_L   K15       K16       K17       K18       K19       ES_R2_R6 \
ES_R3_L0  K20       K21       K22       K23       K24                ES_ARROW_R   K25       K26       K27       K28       K29       ES_R3_R6 \
ES_ENC_L  ES_R4_L1  ES_R4_L2  K32       K33       K34                ES_ARROW_C   K35       K36       K37       ES_R4_R4  ES_R4_R5

#endif

#define MIRYOKU_MAPPING MIRYOKU_LAYOUTMAPPING_EYELASH_SOFLE
