# Missing features

## Not possible without provided USB captures
- Fix keymapping on ISO boards and the Ajazz AK33
- Fix reactive_color variants on the AjazzAK33

## Not planned for now (until keymapping works on all boards)
- Read keymapping and macros if possible
- Macros

## Not supported in the official software
- Reading custom led pattern (most likely not possible)

## TODO
- move macro storage to string based format:
	- Determine maximum amount of actions in one macro

## Where to implement missing features
- Macros: write_key_mapping_ansi() (writers.cpp)
- Keymapping on ISO or Ajazz AK33: new function in writers.cpp (similar to write_key_mapping_ansi()) and appropriate selection code in main

# 1.0
- remove -A option
