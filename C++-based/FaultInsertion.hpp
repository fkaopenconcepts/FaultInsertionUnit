#include <list>

#define ENABLED		1
#define DISABLED	0

#define CONTINUOUS	1
#define CASE		2
#define DIGITAL		3

#define SAMPLETIME	0.001// Annahme einer Zykluszeit von 1ms (Muss für jedes System angepasst werden) TODO: statistische Abweichungen hinzufügen um reale Systeme wiederzuspiegeln

#define NOISE_ARRAY_SIZE 2003 // Die Größe der Lookup-Tabelle für das Rauschmuster (sollte einer Primzahl entsprechen, damit auch bei verschiedenen Skalierungen alle Werte benutzt werden)

#define SET_TYP(fiu, typ) { fiu.Typ = typ; }
#define SET_FREEZE(fiu, enable) { fiu.Freeze.Enable = enable; }
#define SET_FIXEDVALUE(fiu, enable, value) { fiu.FixedValue.Enable = enable; fiu.FixedValue.Value = value; }
#define SET_DELAY(fiu, enable, delay) { fiu.Delay.Enable = enable; fiu.Delay.Time = delay; }
#define SET_DRIFT(fiu, enable, value, time) { fiu.Drfit.Enable = enable; fiu.Drift.Value = value; fiu.Drift.Time = time; }
#define SET_OFFSET(fiu, enable, value) { fiu.Offest.Enable = enable; fiu.Offset.Value = value; }
#define SET_SLEWRATE(fiu, enable, value) { fiu.Slewrate.Enable = enable; fiu.Slewrate.MaxSlewrate = value; }
#define SET_NOISE(fiu, enable, amplitude, pattern) { fiu.Noise.Enable = enable; fiu.Noise.Amplitude = amplitude; fiu.Noise.Pattern = pattern; }


using namespace std;


typedef struct _Freeze {
	int Enable = DISABLED;
	double LastValue = 0;
} tFreeze;

typedef struct _FixedValue {
	int Enable = DISABLED; 
	int Value;
} tFixedValue;

typedef struct _Delay {
	int Enable = DISABLED;
	int Time;
} tDelay;

typedef struct _Negate {
	int Enable = DISABLED;
} tNegate;

typedef struct _Drift {
	int Enable = DISABLED;
	int Value;
	int Time;
	int Timer;	// Variable um die "Zeit" zu messen in der das Signal bereits schon abdriftet
} tDrift;

typedef struct _Offset {
	int Enable = DISABLED;
	int Value;
} tOffset;

typedef struct _Slewrate {
	int Enable = DISABLED;
	int MaxSlewrate;
	double LastValue = 0;
} tSlewrate;

typedef struct _Noise {
	int Enable = DISABLED;
	double Amplitude;
	int Pattern = 1;	// Beschreibt in welchen Schritten das Rauschmuster durchlaufen werden soll (sozusagen verschiedene Muster).
} tNoise;

typedef struct _FIU {
	int Typ = CONTINUOUS;
	tFreeze Freeze;
	tFixedValue FixedValue;
	tDelay Delay;
	tNegate Negate;
	tDrift Drift;
	tOffset Offset;
	tSlewrate Slewrate;
	tNoise Noise;
} tFIU;

double InsertFaults (double Signal, tFIU* FIU);



