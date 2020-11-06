#ifndef _CTRL_IDENT_h
#define _CTRL_IDENT_h

#define f0 (0.1) //initial frequency[Hz]
#define ff (10) //final frequency [Hz]
#define A (1.5) //amplitude [V]
#define t_c (30) //chirptime[s]
void ctrl_chirp(double t_ch, double *out);
#endif