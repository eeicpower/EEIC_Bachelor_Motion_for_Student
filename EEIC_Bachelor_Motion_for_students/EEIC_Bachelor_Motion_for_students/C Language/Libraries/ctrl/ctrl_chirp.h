#ifndef _CTRL_IDENT_h
#define _CTRL_IDENT_h

#define f0 (1) //initial frequency[Hz]
#define ff (200) //final frequency [Hz]
#define A (2) //amplitude [V]
#define t_c (30) //chirptime[s]
void ctrl_chirp(double t_ch, double *out);

#endif