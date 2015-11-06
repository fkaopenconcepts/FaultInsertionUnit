#include <list>

#define ENABLED		1
#define DISABLED	0

#define CONTINUOUS	1
#define CASE		2
#define DIGITAL		3

#define SAMPLETIME	0.001												// Assumption of a sample time = 1ms; needs to be modified in case of different sample times

#define NOISE_ARRAY_SIZE 2003											// Size of the noise pattern array (should be a prime, so that every value is used no matter which pattern size is chosen)

#define SET_TYPE(fiu, type) { fiu.Type = type; }
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
	int Timer;
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
	double Amplitude;													// Factor for the noise pattern
	int Pattern = 1;													// Describes the steps for walking through the noise pattern
} tNoise;

typedef struct _FIU {													// Every FIU contains all the different faults
	int Type = CONTINUOUS;
	tFreeze Freeze;
	tFixedValue FixedValue;
	tDelay Delay;
	tNegate Negate;
	tDrift Drift;
	tOffset Offset;
	tSlewrate Slewrate;
	tNoise Noise;
} tFIU;

double InsertFaults (double Signal, tFIU* FIU);							// The only Function here will check which fault-blocks are enabled and modify the signal accordingly



