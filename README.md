# Eyelash Sofle – Miryoku (QWERTY) ZMK Firmware

Personal ZMK firmware for the [Eyelash Sofle] split keyboard, running the
[Miryoku] layout with QWERTY alphas. Forked from the vendor-provided
[a741725193/zmk-sofle] repository so we can keep the Eyelash board
definition, DYA extensions, and studio support while replacing the stock
keymap with Miryoku.

[Eyelash Sofle]: https://github.com/a741725193/zmk-sofle
[Miryoku]: https://github.com/manna-harbour/miryoku
[a741725193/zmk-sofle]: https://github.com/a741725193/zmk-sofle

---

## Contents

- [What this firmware is](#what-this-firmware-is)
- [Hardware](#hardware)
- [Layout overview (Miryoku QWERTY)](#layout-overview-miryoku-qwerty)
- [Physical key mapping on the Eyelash Sofle](#physical-key-mapping-on-the-eyelash-sofle)
- [Design decisions](#design-decisions)
- [Preserved Eyelash-specific behaviour](#preserved-eyelash-specific-behaviour)
- [Building](#building)
- [Flashing](#flashing)
- [Studio (live remapping)](#studio-live-remapping)
- [Repository layout](#repository-layout)
- [Known issues / potential improvements](#known-issues--potential-improvements)
- [Credits](#credits)

---

## What this firmware is

- **Board / shield:** `nice_nano_v2` + `eyelash_sofle_left` / `eyelash_sofle_right`
  (plus a `settings_reset` build for wiping persisted settings).
- **ZMK upstream:** the `cormoran/zmk` fork on branch `v0.3-branch+dya` — this
  is what provides pointing, runtime sensor rotate, DYA studio, ble
  management, battery history, etc. See `config/west.yml`.
- **Layout:** [Miryoku] (Manna Harbour) — 30 alphas + 6 thumbs across
  10 layers, with home-row mods and layer-tap thumbs. QWERTY alpha variant.
- **Reference implementation:** the [miryoku_zmk] framework is vendored
  under `config/miryoku/`, and an Eyelash-Sofle-specific physical layout
  mapping lives at `config/miryoku/mapping/eyelash_sofle.h`.

[miryoku_zmk]: https://github.com/manna-harbour/miryoku_zmk

---

## Hardware

The Eyelash Sofle is a variant of the classic Sofle with:

- 6 columns × 4 rows per hand + a thumb cluster,
- an extra "inner middle" column of 4 keys per hand (arrows on the stock
  layout),
- two EC11 rotary encoders (one per half),
- WS2812 underglow and per-key backlight,
- built-in `nice!view` display support (both halves).

Total addressable positions: **64 keys** (13 + 13 + 13 + 13 + 12).

---

## Layout overview (Miryoku QWERTY)

Miryoku uses ten layers. Only the base layer is active by default; the
others are held via a layer-tap on a thumb key on the opposite hand.

| #   | Layer  | Held from       | Purpose                                               |
| --- | ------ | --------------- | ----------------------------------------------------- |
| 0   | BASE   | –               | QWERTY alphas + home-row mods + layer-tap thumbs      |
| 1   | EXTRA  | – (via BASE)    | Alternate base (also QWERTY in this build)            |
| 2   | TAP    | – (via BASE)    | Base without any hold-tap behaviour (for fast typing) |
| 3   | BUTTON | Bottom pinkie   | Mouse buttons + mods + clipboard on both hands        |
| 4   | NAV    | Left primary    | Arrows, editing keys, clipboard                       |
| 5   | MOUSE  | Left secondary  | Mouse movement + scroll wheel                         |
| 6   | MEDIA  | Left tertiary   | Media, RGB, Bluetooth, output toggle                  |
| 7   | NUM    | Right primary   | Numpad + brackets                                     |
| 8   | SYM    | Right secondary | Shifted symbols                                       |
| 9   | FUN    | Right tertiary  | F1–F12 + system keys                                  |

### Home-row mods (QWERTY)

Held taps on the home row produce modifiers; short taps produce the
letter as normal.

| Left | A     | S   | D       | F     |
| ---- | ----- | --- | ------- | ----- |
| Mod  | Super | Alt | Control | Shift |

| Right | J     | K       | L   | '     |
| ----- | ----- | ------- | --- | ----- |
| Mod   | Shift | Control | Alt | Super |

`Z` / `/` are layer-taps to the **BUTTON** layer; `X` / `.` are
tap = letter, hold = **RAlt**.

### Thumb keys (BASE)

| Slot            | Tap     | Hold (layer) |
| --------------- | ------- | ------------ |
| Left tertiary   | Esc     | MEDIA        |
| Left primary    | Space   | NAV          |
| Left secondary  | Tab     | MOUSE        |
| Right secondary | Enter   | SYM          |
| Right primary   | Backsp. | NUM          |
| Right tertiary  | Del     | FUN          |

See the [Miryoku reference manual](https://github.com/manna-harbour/miryoku/tree/master/docs/reference)
for the full contents of every layer.

---

## Physical key mapping on the Eyelash Sofle

Miryoku's canonical layout is 30 alphas + 6 thumbs (+ 4 optional
"not-present" slots). The Eyelash Sofle has **64 physical keys** — a
number row, a middle arrow-diamond cluster, outer pinky columns, and 4
extra inner-bottom keys next to the thumb clusters. Rather than let
those extras go to `&none`, we **hard-code useful always-on defaults**
for them so every physical key does something on every layer:

```
Row 0 (number row, y ≈ 0.25):
  Esc  1   2   3   4   5      UP         6   7   8   9   0   Bsp

Row 1 (top alpha, y ≈ 1.25):
  Tab  Q   W   E   R   T      DOWN       Y   U   I   O   P   \

Row 2 (home row, y ≈ 2.25):
  CW*  A/⌘ S/⌥ D/⌃ F/⇧ G      LEFT       H   J/⇧ K/⌃ L/⌥ '/⌘ ;

Row 3 (bottom alpha, y ≈ 3.25):
  ⇧    Z*  X/⌥ᴿ C   V   B      RIGHT      N   M   ,   ./⌥ᴿ /*  Enter

Row 4 (thumbs + encoder + arrow-center):
  Mute ⌃  ⌘  Esc Spc Tab      Enter      Ent Bsp Del ⇧   Del
           |  MED NAV MOU     [ctr]      SYM NUM FUN
```

- `CW*` = `&caps_word` (tap-to-shift-word).
- Home-row mods (LGUI / LALT / LCTRL / LSHFT on the left; mirrored on
  the right) fire on hold, letter fires on tap.
- `Z*` and `/*` are layer-taps to the **BUTTON** layer.
- `X/⌥ᴿ` and `./⌥ᴿ` are tap = letter, hold = **RAlt**.
- The 6 thumb keys are layer-taps into the six Miryoku sub-layers.
- The left encoder rotates for volume up/down on every layer.
- The arrow diamond and number row are hard-coded and layer-transparent,
  so they work in the middle of any Miryoku layer.

Encoder rotation:

| Encoder | CW / CCW              | Behaviour                                                           |
| ------- | --------------------- | ------------------------------------------------------------------- |
| Left    | Volume Up / Down      | `rsr_vol` runtime-sensor-rotate, live-remappable via DYA Studio     |
| Right   | (no hardware encoder) | The board only has one encoder — right-side rotation isn't wired up |

The mapping macro is defined in
[`config/miryoku/mapping/eyelash_sofle.h`](config/miryoku/mapping/eyelash_sofle.h).

---

## Design decisions

- **Miryoku over the stock keymap.** The vendor keymap is a serviceable
  6×4-with-mods layout, but has no home-row mods, uses `mo` layer switches
  (no layer-tap), and only exposes two mouse layers. Miryoku gives us a
  well-thought-out ergonomic layout with a mature reference.
- **QWERTY alphas.** Selected explicitly so we don't have to retrain
  muscle memory. Trivially swappable via one `#define` in
  `config/eyelash_sofle.keymap` (`MIRYOKU_ALPHAS_QWERTY` → e.g.
  `MIRYOKU_ALPHAS_COLEMAKDH`). See [Alternatives](#trying-a-different-variant).
- **Vendored Miryoku framework.** `config/miryoku/` is a straight copy of
  the upstream [miryoku_zmk] framework. Keeping it local means:
  - The build has no extra `west.yml` dependency to babysit.
  - Local edits and experiments are easy.
  - It also keeps working when Miryoku's upstream changes underneath us.
- **Encoder press stays layer-transparent.** The single (left) encoder
  button is far away from any Miryoku layer switch, so hard-coding it to
  `C_MUTE` is nearly free ergonomically and keeps mute-on-every-layer
  as an always-available shortcut.
- **All 64 physical keys do something on every layer.** The Miryoku
  canonical layout is only 36 keys, so an out-of-the-box port would
  leave 28 physical keys inert. Instead, this mapping hard-codes the
  number row (`1`–`0`), the arrow diamond (⬆⬇⬅➡ + Enter in the middle),
  the outer pinky columns (`Tab` / `Caps Word` / `Shift` on the left,
  `\` / `;` / `Enter` on the right), and the four extra inner-bottom
  keys (`Ctrl` / `Gui` on the left, `Shift` / `Delete` on the right) so
  they behave like a standard Sofle regardless of which Miryoku layer
  is active. The trade-off is that these keys are **not**
  layer-aware — the number row always types digits, even on the FUN
  layer.
- **Soft-off kludge instead of bootloader.** `MIRYOKU_KLUDGE_SOFT_OFF`
  routes Miryoku's "bootloader" corner key to `&soft_off`. Combined with
  the 2000 ms `hold-time-ms` we already configure, a single tap does
  nothing — you must hold for two seconds to power down. The three-key
  `Q + S + Z` softoff combo from the original keymap is preserved as an
  additional gesture.
- **Global shift-morphs enabled.** `MIRYOKU_KLUDGE_GLOBALSHIFTFUNCTIONS`
  turns the RGB and external-power keys into shift-morphs — Shift +
  `RGB Toggle` becomes `RGB Off`, Shift + `EP Toggle` becomes `EP Off`,
  etc. This board has both RGB and EXT_POWER enabled in `.conf` so the
  bindings are always meaningful.
- **`.orig` backup of the previous keymap.** `config/eyelash_sofle.keymap.orig`
  is kept in-tree as a reference for the previous vendor layout.

### Trying a different variant

Every Miryoku option is a plain `#define` at the top of
`config/eyelash_sofle.keymap`. Some of the more useful ones:

| Define                                          | Effect                               |
| ----------------------------------------------- | ------------------------------------ |
| `MIRYOKU_ALPHAS_COLEMAKDH` (default when unset) | Colemak-DH alphas                    |
| `MIRYOKU_ALPHAS_QWERTY` (current)               | QWERTY alphas                        |
| `MIRYOKU_ALPHAS_DVORAK`                         | Dvorak                               |
| `MIRYOKU_LAYERS_FLIP`                           | Flip primary/secondary sides         |
| `MIRYOKU_NAV_INVERTEDT`                         | Inverted-T arrow arrangement on Nav  |
| `MIRYOKU_NAV_VI`                                | HJKL vi-style arrows on Nav          |
| `MIRYOKU_CLIPBOARD_MAC` / `_WIN`                | Platform-specific clipboard bindings |

See the [Miryoku reference](https://github.com/manna-harbour/miryoku/tree/master/docs/reference)
for the full list.

---

## Preserved Eyelash-specific behaviour

Anything that was working on the stock firmware and isn't part of the
Miryoku layer definitions was ported over:

- **Pointer & scroll input processors** (`&mmv_input_listener`, `&msc_input_listener`)
  scaled 2:1 on X and 2:1 for scroll.
- **`&mmv` / `&msc` tuning** — acceleration, time-to-max-speed, trigger period.
- **`&soft_off { hold-time-ms = <2000>; }`** so a stray tap doesn't
  shut the keyboard down.
- **`softoff` combo** on `Q + S + Z` (positions `14 / 28 / 40`).
- **`SHIFT_MCLK` macro** — press-and-hold Shift + middle-click for
  drag-select-in-a-terminal-style gestures.
- **`rsr_vol` / `rsr_trans`** runtime-sensor-rotate behaviours, applied
  to every Miryoku layer via a merged `keymap { … }` node at the bottom
  of the file.

Everything else (RGB, backlight, BT, ext-power, sleep, EC11 debounce,
Bluetooth TX power, 32 kHz XTAL) comes from `config/eyelash_sofle.conf`,
which was left untouched.

---

## Building

Builds run in GitHub Actions via [zmkfirmware/zmk/.github/workflows/build-user-config.yml][build-workflow].
`build.yaml` produces three artifacts:

| Artifact                       | Board / shield                                   | Notes                                                              |
| ------------------------------ | ------------------------------------------------ | ------------------------------------------------------------------ |
| `eyelash_sofle-miryoku-left`   | `nice_nano_v2` + `eyelash_sofle_left nice_view`  | Includes ZMK Studio (`studio-rpc-usb-uart`, `CONFIG_ZMK_STUDIO=y`) |
| `eyelash_sofle-miryoku-right`  | `nice_nano_v2` + `eyelash_sofle_right nice_view` |                                                                    |
| `eyelash_sofle-settings_reset` | `nice_nano_v2` + `settings_reset`                | Flash to wipe persisted settings (BT pairings, etc.)               |

[build-workflow]: https://github.com/zmkfirmware/zmk/blob/main/.github/workflows/build-user-config.yml

To build locally you'd need a full ZMK / west environment; the easiest
path is to push and grab the artifacts from the workflow run.

---

## Flashing

1. Put the target half in bootloader mode (double-tap the on-board
   reset, or use the `settings_reset` build first if things are wedged).
2. Copy the matching `.uf2` from the workflow artifact:
   - Left half → `eyelash_sofle-miryoku-left.uf2`
   - Right half → `eyelash_sofle-miryoku-right.uf2`
3. The nice!nano will reboot into the new firmware automatically.

### Full reset (recommended after any keymap / config change)

If the halves stop talking to each other, or one side stops responding
after a flash, do a full re-pair:

1. Flash **`eyelash_sofle-settings_reset.uf2`** to **both halves**
   (double-tap reset, drag the file over, wait for it to reboot).
2. Flash **`eyelash_sofle-miryoku-left.uf2`** to the left half.
3. Flash **`eyelash_sofle-miryoku-right.uf2`** to the right half.
4. Let the two halves discover each other (a few seconds, usually).

This is the standard ZMK split re-pair procedure and clears Bluetooth
pairings + any persisted settings.

> **If only one half is responsive, or only the left-hand alphas type,
> the split BLE pairing is almost certainly the culprit.** The right
> half is a peripheral — it only forwards matrix events; the whole
> keymap lives on the central (left). If it can't reach the central,
> nothing on the right side will do anything, regardless of the keymap.

---

## Studio (live remapping)

The left half is built with ZMK Studio (`studio-rpc-usb-uart` snippet,
`CONFIG_ZMK_STUDIO=y`, locking disabled). This lets you re-map keys
without reflashing:

- Web ZMK Studio: <https://zmk.studio>
- DYA Studio (the cormoran fork's enhanced flavour):
  <https://studio.dya.cormoran.works/>

Plug the left half in via USB and connect from the studio app. Note
that hold-tap and layer-tap bindings will show up as the raw Miryoku
`u_mt` / `u_lt` behaviours.

---

## Repository layout

```
zmk-sofle/
├── boards/shields/eyelash_sofle/      # Board definition (kscan, physical layout, overlays)
├── config/
│   ├── eyelash_sofle.conf             # ZMK config (RGB, BT, sleep, debounce, …)
│   ├── eyelash_sofle.json             # Physical layout for keymap editors
│   ├── eyelash_sofle.keymap           # THIS repo's Miryoku QWERTY keymap
│   ├── eyelash_sofle.keymap.orig      # Backup of the vendor-provided keymap
│   ├── miryoku/                       # Vendored miryoku_zmk framework
│   │   ├── mapping/
│   │   │   └── eyelash_sofle.h        # Physical-layout mapping (this board)
│   │   ├── miryoku.dtsi               # Layer generation
│   │   ├── miryoku.h                  # Preprocessor plumbing
│   │   ├── miryoku_babel/             # Alpha-set alternatives + layer selection
│   │   ├── miryoku_behaviors.dtsi
│   │   ├── miryoku_clipboard.h
│   │   ├── miryoku_double_tap_guard.dtsi
│   │   ├── miryoku_mousekeys.dtsi
│   │   ├── miryoku_shift_functions.dtsi
│   │   └── miryoku_kludge_*.dtsi      # Optional workarounds (thumb combos, tap delay, …)
│   └── west.yml                       # ZMK + module dependencies (cormoran fork)
├── keymap-drawer/                     # SVG renders (STALE — see below)
├── build.yaml                         # GitHub Actions build matrix
└── README.md                          # (this file)
```

---

## Known issues / potential improvements

### Known issues

- **Keymap-drawer SVGs are stale.** `keymap-drawer/eyelash_sofle.svg` and
  the associated YAML were tuned for the vendor layout. Rendering the
  Miryoku layout will produce something correct but visually noisy until
  the `raw_binding_map` in `keymap_drawer.config.yaml` is retuned for
  Miryoku's `&u_mt` / `&u_lt` / `&u_to_U_*` bindings.
- **DT node names are uppercase (`BASE`, `NAV`, …).** These come straight
  from the Miryoku macro. dtc accepts them, but some editors / linters
  complain. Not a real problem, but noisy.
- **The board only has a left encoder.** The right-side `sensor-bindings`
  slot is filled with `&rsr_trans` (a no-op) because there is no right
  encoder to bind. If a future hardware revision adds one, replace the
  placeholder in `config/eyelash_sofle.keymap`.
- **Hard-coded extras override Miryoku on their layers.** Row 0 always
  types 1–0 (never F-keys), the arrow diamond always types arrows, etc.
  That's a deliberate trade-off (see [Design decisions](#design-decisions))
  — if you want layer-specific behaviour on the extras, override them
  per-layer via a `keymap { LAYER { bindings = <…>; }; };` block.

### Potential improvements

- **Layer-aware encoder bindings.** The framework supports adding a
  `sensor-bindings` per layer. E.g. NAV could bind rotate → PgUp/PgDn,
  NUM → +/-, MEDIA → hue rotate. Currently every layer just gets
  `rsr_vol` (volume).
- **Layer-aware extras.** The hard-coded number row / arrow diamond /
  outer pinkies are the same on every layer. Overriding e.g. the number
  row to become F1–F10 on the FUN layer would recover Miryoku's original
  layered semantics.
- **Retune keymap-drawer for Miryoku.** Add `&u_mt`, `&u_lt`, and
  `&u_to_U_*` entries to `raw_binding_map` and regenerate the SVG so it
  can be embedded here.
- **Add a Colemak-DH build in `build.yaml`.** Set `MIRYOKU_ALPHAS_COLEMAKDH`
  via `cmake-args: -DCONFIG_…=y` — or provide a second keymap file — for
  users who want to try Miryoku "as designed".
- **Enable `MIRYOKU_NAV_INVERTEDT`.** Personal preference; the
  inverted-T arrow arrangement is arguably nicer than the default row
  layout on a Sofle-sized board.
- **Investigate `MIRYOKU_KLUDGE_TAPDELAY`.** Miryoku's default tap-hold
  timings can feel slow. The tap-delay kludge tightens things up. Worth
  trying if hold-tap misfires are annoying.
- **Combos beyond `softoff`.** The Sofle has plenty of key real estate
  for combos (bracket pairs, escape on `Q+W`, etc.). Left as-is for now
  to avoid competing with Miryoku's home-row mods.

---

## Credits

- **[Miryoku]** — Manna Harbour. The layout, the reference manual, and
  the ZMK implementation this fork is built on.
- **[a741725193/zmk-sofle]** — the Eyelash Sofle board definition and
  vendor firmware this repo forked from.
- **[cormoran/zmk]** — the ZMK fork (`v0.3-branch+dya`) providing
  pointing, DYA studio, runtime sensor rotate, BLE management, and other
  extensions used here.
- **[ZMK]** — the underlying firmware.

[ZMK]: https://zmk.dev
[cormoran/zmk]: https://github.com/cormoran/zmk
