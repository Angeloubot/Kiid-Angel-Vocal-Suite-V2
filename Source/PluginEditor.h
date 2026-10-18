
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class KiidAngelVocalSuiteAudioProcessorEditor
    : public juce::AudioProcessorEditor
{
public:
    explicit KiidAngelVocalSuiteAudioProcessorEditor(
        KiidAngelVocalSuiteAudioProcessor& processor);

    ~KiidAngelVocalSuiteAudioProcessorEditor() override = default;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    KiidAngelVocalSuiteAudioProcessor& audioProcessor;

    juce::Label titleLabel;
    juce::Label subtitleLabel;
    juce::Label lowCutLabel;
    juce::Label presenceLabel;

    juce::Slider lowCutSlider;
    juce::Slider presenceSlider;

    using SliderAttachment =
        juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> lowCutAttachment;
    std::unique_ptr<SliderAttachment> presenceAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
        KiidAngelVocalSuiteAudioProcessorEditor)
};
