// 4 Switch Midi Foot Controller
// Based on a Line6 FB4 and Arduino Nano
#include <Bounce2.h>
#include <MIDI.h>
#include <elapsedMillis.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// the MIDI channel number to send messages
const int channel = 1;

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.

Bounce button1 = Bounce(3, 20); // Footswitch ; 5 = 5 ms debounce time
Bounce button2 = Bounce(4, 20);  // Footswitch; which is appropriate for good quality mechanical pushbuttons
Bounce button3 = Bounce(5, 20);
Bounce button4 = Bounce(6, 20);

// Midi CC Value for every button
const int button1_cc = 100;
const int button2_cc = 101;
const int button3_cc = 102;
const int button4_cc = 103;

int ledPin = 13;

void setup() {
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin, LOW);
 
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  

  MIDI.begin();
}


void loop() { 
  //MIDI.read(); // USB MIDI receive

  button1.update();
  button2.update();
  button3.update();
  button4.update();
// Edge Falling: High to Low (Switch goes down, Open to Closed, because off input_pullup)
  if (button1.fallingEdge()) {
    MIDI.sendNoteOn(button1_cc, 127, channel);
  }
  if (button2.fallingEdge()) {
    MIDI.sendNoteOn(button2_cc, 127, channel); 
  }
  if (button3.fallingEdge()) {
    MIDI.sendNoteOn(button3_cc, 127, channel); 
  }
  if (button4.fallingEdge()) {
    MIDI.sendNoteOn(button4_cc, 127, channel); 
  }

 // Edge Rising: Low to High (Switch goes up, Closed to Open, because off input_pullup)
  if (button1.risingEdge()) {
    MIDI.sendNoteOff(button1_cc, 0, channel); 
  }
   if (button2.risingEdge()) {
    MIDI.sendNoteOff(button2_cc, 0, channel);  
  }
   if (button3.risingEdge()) {
    MIDI.sendNoteOff(button3_cc, 0, channel);  
  }
   if (button4.risingEdge()) {
    MIDI.sendNoteOff(button4_cc, 0, channel);  
  }

 
    //while (usbMIDI.read()); // read and discard any incoming MIDI messages
  
}
