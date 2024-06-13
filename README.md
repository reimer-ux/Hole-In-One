# Hole-In-One!

A simple timing-based game for the [Arduino Circuit Playground Express](https://store.arduino.cc/products/circuit-playground-express). Can you master all five stages?

Drop the ball into the highlight "hole" to win! The game begins once powered on. There are five stages to get through, but be cautious! You only have five lives. The ball spins in a circle, and the user needs to press either the right or left button button to stop it. If it's not on the highlighted section, you lose a life! If it is, you move on to the next stage. But don't celebrate yet! Each stage ramps up in speed. If you pass all the stages, you win. Good luck!

If the jingles and brightness are annoying, flip the switch to enable *night mode*, which decreases the overall brightness and mutes the speaker.

### Inputs

- Left button `D4`
- Right button `D5`
- Slide switch `D7`

### Outputs

- Speaker `A0`
- NeoPixels `D8`

![Pinout diagram](https://cdn-learn.adafruit.com/assets/assets/000/047/156/original/circuit_playground_Adafruit_Circuit_Playground_Express_Pinout.png?1507829017)
