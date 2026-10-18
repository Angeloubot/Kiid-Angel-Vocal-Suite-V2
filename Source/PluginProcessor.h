
#pragma once

#include <JuceHeader.h>

class KiidAngelVocalSuiteAudioProcessor
    : public juce::AudioProcessor
{
public:
    KiidAngelVocalSuiteAudioProcessor();

    ~KiidAngelVocalSuiteAudioProcessor() override = default;

    void prepareToPlay(double sampleRate,
                       int samplesPerBlock) override;

    void releaseResources() override;

    void processBlock(juce::AudioBuffer<float>& buffer,
                      juce::MidiBuffer& midiMessages) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override
    {
        return "Kiid Angel Vocal Suite";
    }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }

    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(
        juce::MemoryBlock& destinationData) override;

    void setStateInformation(
        const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState parameters;

private:
    juce::dsp::IIR::Filter<float> lowCutFilter;
    juce::dsp::IIR::Filter<float> presenceFilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
        KiidAngelVocalSuiteAudioProcessor)
};
