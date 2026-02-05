#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define C 299792458.0

typedef struct {
	const char *suffix;
	int is_freq;
	double multiplier;
} unit_t;

static const unit_t units[] = {
	{"terahertz",    1, 1e12},
	{"thz",          1, 1e12},
	{"gigahertz",    1, 1e9},
	{"ghz",          1, 1e9},
	{"megahertz",    1, 1e6},
	{"mhz",          1, 1e6},
	{"kilohertz",    1, 1e3},
	{"khz",          1, 1e3},
	{"hertz",        1, 1},
	{"hz",           1, 1},
	{"kilometers",   0, 1e3},
	{"kilometer",    0, 1e3},
	{"km",           0, 1e3},
	{"meters",       0, 1},
	{"meter",        0, 1},
	{"centimeters",  0, 1e-2},
	{"centimeter",   0, 1e-2},
	{"cm",           0, 1e-2},
	{"millimeters",  0, 1e-3},
	{"millimeter",   0, 1e-3},
	{"mm",           0, 1e-3},
	{"m",            0, 1},
};

#define NUM_UNITS (sizeof(units) / sizeof(units[0]))

typedef struct {
	const char *name;
	const char *abbrev;
	int itu;
	double lo_hz;
	double hi_hz;
	const char *range;
} band_t;

static const band_t bands[] = {
	{"Extremely low frequency",      "ELF", 1,  3,     30,     "3\xe2\x80\x93" "30 Hz"},
	{"Super low frequency",          "SLF", 2,  30,    300,    "30\xe2\x80\x93" "300 Hz"},
	{"Ultra low frequency",          "ULF", 3,  300,   3e3,    "300\xe2\x80\x93" "3,000 Hz"},
	{"Very low frequency",           "VLF", 4,  3e3,   30e3,   "3\xe2\x80\x93" "30 kHz"},
	{"Low frequency",                "LF",  5,  30e3,  300e3,  "30\xe2\x80\x93" "300 kHz"},
	{"Medium frequency",             "MF",  6,  300e3, 3e6,    "300\xe2\x80\x93" "3,000 kHz"},
	{"High frequency",               "HF",  7,  3e6,   30e6,   "3\xe2\x80\x93" "30 MHz"},
	{"Very high frequency",          "VHF", 8,  30e6,  300e6,  "30\xe2\x80\x93" "300 MHz"},
	{"Ultra high frequency",         "UHF", 9,  300e6, 3e9,    "300\xe2\x80\x93" "3,000 MHz"},
	{"Super high frequency",         "SHF", 10, 3e9,   30e9,   "3\xe2\x80\x93" "30 GHz"},
	{"Extremely high frequency",     "EHF", 11, 30e9,  300e9,  "30\xe2\x80\x93" "300 GHz"},
	{"Tremendously high frequency",  "THF", 12, 300e9, 3e12,   "300\xe2\x80\x93" "3,000 GHz"},
};

#define NUM_BANDS (sizeof(bands) / sizeof(bands[0]))

static void str_lower(char *dst, const char *src, size_t n)
{
	size_t i;
	for (i = 0; i < n - 1 && src[i]; i++)
		dst[i] = tolower((unsigned char)src[i]);
	dst[i] = '\0';
}

static const unit_t *find_unit(const char *s)
{
	char lower[32];
	str_lower(lower, s, sizeof(lower));

	for (size_t i = 0; i < NUM_UNITS; i++) {
		if (strcmp(lower, units[i].suffix) == 0)
			return &units[i];
	}
	return NULL;
}

static const band_t *find_band(double freq_hz)
{
	for (size_t i = 0; i < NUM_BANDS; i++) {
		if (freq_hz >= bands[i].lo_hz && freq_hz < bands[i].hi_hz)
			return &bands[i];
	}
	return NULL;
}

static void print_freq(double hz)
{
	if (hz >= 1e12)
		printf("%.4f THz\n", hz / 1e12);
	else if (hz >= 1e9)
		printf("%.4f GHz\n", hz / 1e9);
	else if (hz >= 1e6)
		printf("%.4f MHz\n", hz / 1e6);
	else if (hz >= 1e3)
		printf("%.4f kHz\n", hz / 1e3);
	else
		printf("%.4f Hz\n", hz);
}

static void print_wavelength(double m)
{
	if (m >= 1000.0)
		printf("%.4f km\n", m / 1000.0);
	else if (m >= 1.0)
		printf("%.4f m\n", m);
	else if (m >= 0.01)
		printf("%.4f cm\n", m * 100.0);
	else
		printf("%.4f mm\n", m * 1000.0);
}

static void print_band(double freq_hz)
{
	const band_t *b = find_band(freq_hz);
	if (b)
		printf("Band: %s (%s), ITU %d (%s)\n",
		       b->name, b->abbrev, b->itu, b->range);
	else
		printf("Band: Unknown\n");
}

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3) {
		fprintf(stderr, "Usage: %s <value><unit>\n", argv[0]);
		fprintf(stderr, "  e.g. %s 144mhz\n", argv[0]);
		fprintf(stderr, "       %s 10 m\n", argv[0]);
		return 1;
	}

	char *endptr;
	double value = strtod(argv[1], &endptr);

	const char *unit_str;
	if (argc == 3) {
		unit_str = argv[2];
	} else {
		while (*endptr && isspace((unsigned char)*endptr))
			endptr++;
		unit_str = endptr;
	}

	if (value <= 0 || *unit_str == '\0') {
		fprintf(stderr, "Error: invalid input\n");
		return 1;
	}

	const unit_t *u = find_unit(unit_str);
	if (!u) {
		fprintf(stderr, "Error: unknown unit '%s'\n", unit_str);
		return 1;
	}

	double freq_hz, wavelength_m;

	if (u->is_freq) {
		freq_hz = value * u->multiplier;
		wavelength_m = C / freq_hz;
		print_wavelength(wavelength_m);
	} else {
		wavelength_m = value * u->multiplier;
		freq_hz = C / wavelength_m;
		print_freq(freq_hz);
	}

	print_band(freq_hz);
	printf("\n");

	return 0;
}
