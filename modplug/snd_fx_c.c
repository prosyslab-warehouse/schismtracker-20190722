#include "snd_fx.h"
#define CLAMP(a,y,z) ((a) < (y) ? (y) : ((a) > (z) ? (z) : (a)))
extern unsigned short FreqS3MTable[16];
static inline int _muldiv(int a, int b, int c)
{
        return ((unsigned long long) a * (unsigned long long) b ) / c;
}



int get_note_from_period(int period)
{
	int n;
	if (!period)
		return 0;
	for (n = 0; n <= 120; n++) {
		/* Essentially, this is just doing a note_to_period(n, 8363), but with less
		computation since there's no c5speed to deal with. */
		if (period >= (32 * FreqS3MTable[n % 12] >> (n / 12)))
			return n + 1;
	}
	return 120;
}

int get_period_from_note(int note, unsigned int c5speed,
        int linear, int min_period, int max_period)
{
        int l;
        if (!note || note > 0xF0)
                return 0;
        note--;
        if (linear) {
                l = (FreqS3MTable[note % 12] << 5) >> (note / 12);
        } else {
                if (!c5speed)
                        c5speed = 1;
                l = _muldiv(8363, (FreqS3MTable[note % 12] << 5), c5speed << (note / 12));
        }
        if (max_period)
                l = CLAMP(l, min_period, max_period);
        return l;
}


unsigned int get_freq_from_period(int period, unsigned int c5speed, int frac, int linear)
{
        if (!period)
                return 0;
        if (linear) {
                if (!c5speed)
                        c5speed = 1;
                return _muldiv(c5speed, 1712L << 8, (period << 8) + frac);
        } else {
                return _muldiv(8363, 1712L << 8, (period << 8) + frac);
        }
}
