
#include "PluginProcessor.h"
#include "PluginEditor.h"

static juce::AudioProcessorValueTreeState::ParameterLayout
createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "lowCut", "Low Cut",
        juce::NormalisableRange<float>(20.0f, 250.0f, 1.0f),
        80.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "presence", "Presence",
        juce::NormalisableRange<float>(-6.0f, 6.0f, 0.1f),
        0.0f));

    return layout;
}

KiidAngelVocalSuiteAudioProcessor::
KiidAngelVocalSuiteAudioProcessor()
    : AudioProcessor(BusesProperties()
          .withInput("Input", juce::AudioChannelSet::stereo(), true)
          .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

void KiidAngelVocalSuiteAudioProcessor::prepareToPlay(
    double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec {
        sampleRate,
        static_cast<juce::uint32>(samplesPerBlock),
        static_cast<juce::uint32>(getTotalNumOutputChannels())
    };

    lowCutFilter.reset();
    presenceFilter.reset();

    lowCutFilter.prepare(spec);
    presenceFilter.prepare(spec);
}

void KiidAngelVocalSuiteAudioProcessor::releaseResources()
{
}

void KiidAngelVocalSuiteAudioProcessor::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    juce::ignoreUnused(midiMessages);

    const auto lowCut =
        parameters.getRawParameterValue("lowCut")->load();
    const auto presence =
        parameters.getRawParameterValue("presence")->load();

    *lowCutFilter.state =
        *juce::dsp::IIR::Coefficients<float>::makeHighPass(
            getSampleRate(), lowCut);

    *presenceFilter.state =
        *juce::dsp::IIR::Coefficients<float>::makePeakFilter(
            getSampleRate(), 3500.0f, 0.8f,
            juce::Decibels::decibelsToGain(presence));

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    lowCutFilter.process(context);
    presenceFilter.process(context);
}

juce::AudioProcessorEditor*
KiidAngelVocalSuiteAudioProcessor::createEditor()
{
    return new KiidAngelVocalSuiteAudioProcessorEditor(*this);
}

void KiidAngelVocalSuiteAudioProcessor::getStateInformation(
    juce::MemoryBlock& destinationData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destinationData);
}

void KiidAngelVocalSuiteAudioProcessor::setStateInformation(
    const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(
        getXmlFromBinary(data, sizeInBytes));

    if (xml && xml->hasTagName(parameters.state.getType()))
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KiidAngelVocalSuiteAudioProcessor();
}
