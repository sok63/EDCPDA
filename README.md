# EDC PDA

Project for transforming the M5Stack PaperS3 into a PDA for daily use.

## Tech Debt

- Rewrite TouchGesture driver (need support TWOF gestures)
- Rewrite Shuffler and add console app for PC (to not lost all passwords while lose M5 Paper S3)

## Changes

### Version 0.0.20

- Format all code with clang-format
- Update versions of GFX & M5Unified dependences (now they eat 17kb RAM more)
- Add ToogleButton widget
- In PassGen you can now select alphabet (UPPER/LOWER/DIGITS/SPECIAL/SPACE and their combinations) 
- Fix that header draw all frames on trasparent bottom
- Start work with dirty flag in widgets
- Change list of gestures at now to more simplier list
- Now touch driver detects two finger gestures and do all better than previous one (but not as needed) 
- SWIPE DOWN starting from header position now special action to return to menu application (will be changed soon)

### Version 0.0.19

- Start develop Widgets
- Header is now Widget, not separate Application
- Password Generator (PassGen) application