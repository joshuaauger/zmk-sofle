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
// Diamond CENTER key. Vendor had ENTER here, but we already have ENTER on
// the right outer pinky (row 3) AND on the Miryoku thumb K35 (tap = ENTER).
// Three enters on the right side is excessive, so this becomes a momentary
// BUTTON-layer switch instead — which gives mouse buttons on both thumbs
// and clipboard (undo/cut/copy/paste/redo) on the alphas while held.
// BUTTON was otherwise only reachable by holding Z or `/`.
#define ES_ARROW_C  &mo U_BUTTON

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
//
// Following Juraj Fiala's Miryoku-on-Sofle pattern
// (https://jurf.github.io/2023/07/11/60-percent-miryoku/):
//
//   "The left and right [outer pinky] columns contain all the leftover
//    keys. The keys that already existed on the three main rows ([, ;, ])
//    have their positions unchanged."
//
// I.e. the outer pinky rows 1..3 hold the bracket/symbol/backtick keys
// exactly where they sit on Miryoku's NUM layer, so hitting the outer
// pinky is consistent whether or not you're holding NUM.
//
// This eliminates the previous ad-hoc bindings (TAB / LALT / LSHFT on
// the left, BSLH / APOS / ENTER on the right) which were all duplicates
// of keys already on the thumb cluster or home-row mods, and it matches
// a published, well-thought-out Sofle Miryoku port instead of my earlier
// invented placement.
//
// Miryoku NUM layer left column (K00 / K10 / K20):
#define ES_R1_L0    &kp LBKT       // [   — Miryoku NUM K00
#define ES_R2_L0    &kp SEMI       // ;   — Miryoku NUM K10
#define ES_R3_L0    &kp GRAVE      // `   — Miryoku NUM K20
// Miryoku NUM layer right column (K04 / K14 / K24):
#define ES_R1_R6    &kp RBKT       // ]   — Miryoku NUM K04
#define ES_R2_R6    &kp EQUAL      // =   — Miryoku NUM K14
#define ES_R3_R6    &kp BSLH       // \   — Miryoku NUM K24

// Row-4 hard-coded extras. Juraj's Sofle only has 1 extra per side (which
// he uses for `&to U_BASE` — return from tap/gaming layer). We have TWO
// extras per side, so:
//
//   Left  col 1: LCTRL   (vendor-consistent; useful for Ctrl+X etc.
//                         without home-row-mod shenanigans)
//   Left  col 2: LALT    (user wanted LALT accessible; Miryoku K33 thumb
//                         hold-tap ate the vendor's LALT slot at row 4
//                         col 3, so we put it here. LGUI is still on the
//                         A home-row-mod.)
//   Right col 11: RSHFT  (vendor-consistent; helps when home-row-mod
//                         shift on F is awkward for capital-F etc.)
//   Right col 12: RALT   (was DEL in vendor, but DEL is on Miryoku K37
//                         thumb tap. RALT is otherwise only on the X/DOT
//                         home-row-mods, so making it a dedicated key
//                         mirrors LALT on the left.)
#define ES_R4_L1    &kp LCTRL      // orig LCTRL slot
#define ES_R4_L2    &kp LALT       // was LGUI; LGUI is on A home-row-mod
#define ES_R4_R4    &kp RSHFT      // orig RSHFT slot
#define ES_R4_R5    &kp RALT       // was DEL; DEL is on K37 thumb tap

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
