
#include "PluginEditor.h"

KiidAngelVocalSuiteAudioProcessorEditor::
KiidAngelVocalSuiteAudioProcessorEditor(
    KiidAngelVocalSuiteAudioProcessor& processor)
    : AudioProcessorEditor(&processor),
      audioProcessor(processor)
{
    setSize(560, 380);

    titleLabel.setText(
        "KIID ANGEL", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(28.0f, juce::Font::bold));
    titleLabel.setColour(
        juce::Label::textColourId, juce::Colours::white);
    titleLabel.setJustificationType(
        juce::Justification::centred);

    subtitleLabel.setText(
        "VOCAL SUITE | VERSION 0.1",
        juce::dontSendNotification);
    subtitleLabel.setFont(juce::Font(12.0f));
    subtitleLabel.setColour(
        juce::Label::textColourId,
        juce::Colour(0xffb8b8c8));
    subtitleLabel.setJustificationType(
        juce::Justification::centred);

    lowCutLabel.setText(
        "LOW CUT (Hz)", juce::dontSendNotification);
    presenceLabel.setText(
        "PRESENCE (dB)", juce::dontSendNotification);

    for (auto* label : { &lowCutLabel, &presenceLabel })
    {
        label->setFont(juce::Font(14.0f, juce::Font::bold));
        label->setColour(
            juce::Label::textColourId, juce::Colours::white);
        label->setJustificationType(
            juce::Justification::centred);
        addAndMakeVisible(*label);
    }

    for (auto* slider : { &lowCutSlider, &presenceSlider })
    {
        slider->setSliderStyle(
            juce::Slider::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(
            juce::Slider::TextBoxBelow, false, 90, 24);
        slider->setColour(
            juce::Slider::rotarySliderFillColourId,
            juce::Colour(0xffd4a84f));
        slider->setColour(
            juce::Slider::thumbColourId, juce::Colours::white);
        slider->setColour(
            juce::Slider::textBoxTextColourId, juce::Colours::white);
        slider->setColour(
            juce::Slider::textBoxBackgroundColourId,
            juce::Colour(0xff20202b));
        addAndMakeVisible(*slider);
    }

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(subtitleLabel);

    lowCutAttachment =
        std::make_unique<SliderAttachment>(
            audioProcessor.parameters, "lowCut", lowCutSlider);

    presenceAttachment =
        std::make_unique<SliderAttachment>(
            audioProcessor.parameters, "presence", presenceSlider);
}

void KiidAngelVocalSuiteAudioProcessorEditor::paint(
    juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff11111a));

    g.setColour(juce::Colour(0xffd4a84f));
    g.fillRoundedRectangle(
        18.0f, 18.0f,
        static_cast<float>(getWidth() - 36),
        4.0f, 2.0f);

    g.setColour(juce::Colour(0xff292938));
    g.drawRoundedRectangle(
        12.0f, 12.0f,
        static_cast<float>(getWidth() - 24),
        static_cast<float>(getHeight() - 24),
        12.0f, 1.5f);

    g.setColour(juce::Colour(0xffd4a84f));
    g.setFont(juce::Font(11.0f));
    g.drawFittedText(
        "ANGELOU'S JEW RECORDS",
        20, getHeight() - 36, getWidth() - 40, 18,
        juce::Justification::centred, 1);
}

void KiidAngelVocalSuiteAudioProcessorEditor::resized()
{
    titleLabel.setBounds(20, 32, getWidth() - 40, 40);
    subtitleLabel.setBounds(20, 72, getWidth() - 40, 24);

    const int sectionWidth = (getWidth() - 80) / 2;

    lowCutLabel.setBounds(25, 130, sectionWidth, 28);
    lowCutSlider.setBounds(25, 155, sectionWidth, 155);

    presenceLabel.setBounds(
        55 + sectionWidth, 130, sectionWidth, 28);
    presenceSlider.setBounds(
        55 + sectionWidth, 155, sectionWidth, 155);
}
