#include "PluginEditor.h"
#include "PluginProcessor.h"


//==============================================================================
ModLinePluginAudioProcessorEditor::ModLinePluginAudioProcessorEditor(ModLinePluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(200, 300);

    mix_slider_.setSliderStyle(juce::Slider::LinearBarVertical);
    mix_slider_.setRange(0.0, 1, .01);
    mix_slider_.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    mix_slider_.setPopupDisplayEnabled(true, false, this);
    mix_slider_.setTextValueSuffix(" Mix");
    mix_slider_.setValue(.5f);
    mix_slider_.addListener(this);

    width_slider_.setSliderStyle(juce::Slider::LinearBarVertical);
    width_slider_.setRange(0.0, 30, 1);
    width_slider_.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    width_slider_.setPopupDisplayEnabled(true, false, this);
    width_slider_.setTextValueSuffix(" Width");
    width_slider_.setValue(30);
    width_slider_.addListener(this);

    speed_slider_.setSliderStyle(juce::Slider::LinearBarVertical);
    speed_slider_.setRange(0.0, 5, 0.01);
    speed_slider_.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    speed_slider_.setPopupDisplayEnabled(true, false, this);
    speed_slider_.setTextValueSuffix(" Freq");
    speed_slider_.setValue(5);
    speed_slider_.addListener(this);

    addAndMakeVisible(mix_slider_);
    addAndMakeVisible(width_slider_);
    addAndMakeVisible(speed_slider_);

    mix_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.value_tree_state_, "mix", mix_slider_);
    width_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.value_tree_state_, "width", width_slider_);
    speed_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.value_tree_state_, "speed", speed_slider_);
}

ModLinePluginAudioProcessorEditor::~ModLinePluginAudioProcessorEditor()
{
}

//==============================================================================
void ModLinePluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);

    g.drawFittedText("ModLine", getLocalBounds(), juce::Justification::centredTop, 1);
}

void ModLinePluginAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    const int width = 20;
    const int height = 200;

    mix_slider_.setBounds(bounds.removeFromLeft(40).withSizeKeepingCentre(width, height));
    width_slider_.setBounds(bounds.removeFromLeft(40).withSizeKeepingCentre(width, height));
    speed_slider_.setBounds(bounds.removeFromLeft(40).withSizeKeepingCentre(width, height));
}

void ModLinePluginAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &mix_slider_)
    {

    }
    else if(slider == &width_slider_)
    {

    }
    else if (slider == &speed_slider_)
    {

    }
}