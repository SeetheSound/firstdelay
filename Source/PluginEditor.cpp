/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstDelayAudioProcessorEditor::FirstDelayAudioProcessorEditor(FirstDelayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
      gainAttatchment    (p.state, "gain", gainSlider),
      feedbackAttatchment(p.state, "feedback", feedbackSlider),
      mixAttatchment     (p.state, "mix", mixSlider)
{
    gainSlider    .setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mixSlider     .setSliderStyle(juce::Slider::SliderStyle::Rotary);

    for (auto* slider : { &gainSlider, &feedbackSlider, &mixSlider })
    {
        slider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 30);
        addAndMakeVisible(slider);
    }

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

FirstDelayAudioProcessorEditor::~FirstDelayAudioProcessorEditor()
{
}

//==============================================================================
//!!!Notes from Trey for new developers!!! This is where you design and implement the gui for the users
void FirstDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour (0xff121));

    g.setColour(juce::Colours::forestgreen);
    juce::Rectangle<float> backgroundRect = getLocalBounds().toFloat();
    int numBackgroundRects = 60;
    juce::Point<float> offset = backgroundRect.getBottomRight() / numBackgroundRects;

    for (int i = 0; i < numBackgroundRects; ++i) 
    {
        g.drawRect(backgroundRect);
        backgroundRect += offset;
    }

    juce::Rectangle<int> bounds = getLocalBounds();
    juce::Rectangle<int> textArea = bounds.removeFromLeft((bounds.getWidth() * 2) / 3)
                                          .removeFromBottom(bounds.getHeight() / 2)
                                          .reduced(10);
    juce::ColourGradient gradient(juce::Colour(0xffe62895),
                                  textArea.toFloat().getTopLeft(),
                                  juce::Colour(0xffe43d1b),
                                  textArea.toFloat().getTopRight(),
                                  false);
    g.setGradientFill(gradient);

    g.setFont(textArea.toFloat().getHeight());
    g.drawFittedText("TREY", textArea, juce::Justification::centred, 1);
 
}

void FirstDelayAudioProcessorEditor::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    int margin = 20;

    juce::Rectangle<int> gainBounds = bounds.removeFromRight(getWidth() / 3);
    gainSlider.setBounds(gainBounds.reduced(margin));

    juce::Rectangle<int> knobsBounds = bounds.removeFromTop(getHeight() / 2);
    juce::Rectangle<int> feedbackBounds = knobsBounds.removeFromLeft(knobsBounds.getWidth() / 2);
    feedbackSlider.setBounds(feedbackBounds.reduced(margin));
    mixSlider.setBounds(knobsBounds.reduced(margin));
}
