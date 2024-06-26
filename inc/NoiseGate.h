/*
 * Company: Blackaddr Audio
 * Effect Name: Noise Gate
 * Description: A noise gate with controllable threshold, opening/closing times and DC removal filter.
 *
 * This file was auto-generated by Aviate Audio Effect Creator for the Multiverse.
 */
#pragma once

#include <Audio.h>
#include <arm_math.h>
#include "Aviate/AudioEffectWrapper.h"

//!s - START_USER_INCLUDES - put your #includes below this line before the matching END
//!e - END_USER_INCLUDES

namespace BlackaddrAudio_NoiseGate {

//!s - START_USER_EFFECT_TYPES - put your effect types below this line before the matching END
//!e - END_USER_EFFECT_TYPES

#define AUDIOSTREAM_INT16
using AudioBlock    = audio_block_t;
using AudioDataType = int16_t;
#define audioBlockReceiveReadOnly receiveReadOnly
#define audioBlockReceiveWritable receiveWritable
#define audioBlockAllocate        allocate

class NoiseGate : public AudioStream, public Aviate::AudioEffectWrapper {
public:
    static constexpr unsigned NUM_INPUTS  = 1;
    static constexpr unsigned NUM_OUTPUTS = 1;

    // List of effect control names
    enum {
        Bypass_e = 0,
        Volume_e = 1,
        Threshold_e = 2,
        Attackms_e = 3,
        Holdms_e = 4,
        Releasems_e = 5,
        Gate_e = 6,
        InputLevel_e = 7,
        DCFilter_e = 8,
        DCFilterEnable_e = 9,
        NUM_CONTROLS
    };

    //!s - START_USER_CLASS_TYPES - put your custom class types below this line before the matching END
    //!e - END_USER_CLASS_TYPES

    NoiseGate();

    //!s - START_USER_CONSTRUCTORS - put your custom constructors below this line before the matching END
    //!e - END_USER_CONSTRUCTORS

    virtual ~NoiseGate();

    // Standard EFX interface functions - do not change these declaration
    virtual void update(); // main audio processing loop function
    void mapMidiControl(int parameter, int midiCC, int midiChannel = 0) override;
    void processMidi(int status, int data1, int data2) override;
    void setParam(int paramIndex, float paramValue) override;
    float getUserParamValue(int paramIndex, float normalizedParamValue);
    const char* getName() override;
    const uint8_t* getRblk() override;

    // control value set functions, must take floats between 0.0f and 1.0f - do not change these declarations
    void volume(float value) override;
    void threshold(float value);
    void attackms(float value);
    void holdms(float value);
    void releasems(float value);
    void gate(float value);
    void inputlevel(float value);
    void dcfilter(float value);
    void dcfilterenable(float value);

    //!s - START_USER_PUBLIC_MEMBERS - put your public members below this line before the matching END
    //!e - END_USER_PUBLIC_MEMBERS

private:
    audio_block_t *m_inputQueueArray[1]; // required by AudioStream base class, array size is num inputs
    int m_midiConfig[NUM_CONTROLS][2]; // stores the midi parameter mapping

    // m_bypass and m_volume are already provided by the base class AudioEffectWrapper or AudioEffectFloat
    float m_threshold = 0.0f;
    float m_attackms = 0.0f;
    float m_holdms = 0.0f;
    float m_releasems = 0.0f;
    float m_gate = 0.0f;
    float m_inputlevel = 0.0f;
    float m_dcfilter = 0.0f;
    float m_dcfilterenable = 0.0f;

    audio_block_t* m_basicInputCheck(audio_block_t* inputAudioBlock, unsigned outputChannel);

    //!s - START_USER_PRIVATE_MEMBERS - put your private members below this line before the matching END
    static constexpr float INPUT_LEVEL_ALPHA_FACTOR = 0.075f;
    float32_t averageInputLinearAbs;
    float32_t linearThreshold;
	float32_t prev_gain_dB = 0;
	float32_t openingTimeConst, closingTimeConst;
	float lastGainBlockValue = 0;
	int32_t counter, holdTimeNumSamples = 0;
	bool falling = false;
	bool _isOpen = false;
    bool gateFullyOpen = true;

    void calcGain(float *input, float *gainBlock, unsigned numSamples);
    void calcSmoothedGain(float *gain_block, unsigned numSamples);
    void gateReset();
    void sendReports(float gate, float inputLevel);

    unsigned m_skipUpdateCount = 0;
    bool m_signalDetect = false;
    float m_dcValueSum = 0.0f;
    float m_dcValue = 0.0f;
    unsigned m_dcValueCount = 0;
    bool m_calibrateEnabled = false;
    //!e - END_USER_PRIVATE_MEMBERS

};

}
