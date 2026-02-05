# radspec

A command-line tool that converts between radio frequency and wavelength, and displays the corresponding ITU band designation.

## Build

```
make
```

## Usage

```
./radspec <value><unit>
```

Input can be a frequency or a wavelength. The number and unit can be separated by a space or joined together. Units are case-insensitive.

### Supported units

| Type | Units |
|------|-------|
| Frequency | `hz`, `khz`, `mhz`, `ghz`, `thz` |
| Wavelength | `mm`, `cm`, `m`, `meter`, `meters`, `km` |

### Examples

```
$ ./radspec 10m
29.9792 MHz
Band: High frequency (HF), ITU 7 (3–30 MHz)

$ ./radspec 144 Mhz
2.0819 m
Band: Very high frequency (VHF), ITU 8 (30–300 MHz)

$ ./radspec 1.6mhz
187.3703 m
Band: Medium frequency (MF), ITU 6 (300–3,000 kHz)

$ ./radspec 2 meters
149.8962 MHz
Band: Very high frequency (VHF), ITU 8 (30–300 MHz)
```

## ITU Band Designations

| ITU | Band | Abbreviation | Frequency Range |
|-----|------|--------------|-----------------|
| 1 | Extremely low frequency | ELF | 3–30 Hz |
| 2 | Super low frequency | SLF | 30–300 Hz |
| 3 | Ultra low frequency | ULF | 300–3,000 Hz |
| 4 | Very low frequency | VLF | 3–30 kHz |
| 5 | Low frequency | LF | 30–300 kHz |
| 6 | Medium frequency | MF | 300–3,000 kHz |
| 7 | High frequency | HF | 3–30 MHz |
| 8 | Very high frequency | VHF | 30–300 MHz |
| 9 | Ultra high frequency | UHF | 300–3,000 MHz |
| 10 | Super high frequency | SHF | 3–30 GHz |
| 11 | Extremely high frequency | EHF | 30–300 GHz |
| 12 | Tremendously high frequency | THF | 300–3,000 GHz |
