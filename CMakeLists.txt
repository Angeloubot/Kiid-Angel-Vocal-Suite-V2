
cmake_minimum_required(VERSION 3.22)

project(KiidAngelVocalSuite VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.8
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(JUCE)

juce_add_plugin(KiidAngelVocalSuite
    COMPANY_NAME "Angelous Jew Records"
    BUNDLE_ID "com.angelousjewrecords.vocalsuite"
    PLUGIN_MANUFACTURER_CODE KdAn
    PLUGIN_CODE KAvS
    FORMATS VST3
    PRODUCT_NAME "Kiid Angel Vocal Suite"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
)

target_sources(KiidAngelVocalSuite
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
)

target_link_libraries(KiidAngelVocalSuite
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
)
