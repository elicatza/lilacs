# Lilacs
My personal diary manager.

## Dependencies
- Cmake
- Make
- Ninja

## Features
- Config file
- Templates
- Man page

### Templates
templates are stored in plain text files. Within the files you use placeholders with the format {pattern}.
Where pattern is a script you want get the replacement for.
- Date -> {date} -> YYYY-MM-DD
- Time -> {time} -> HH:MM
- Other?

### Config
rootdir = project directory
path_name_convention = yyyy/mm/dd

### Files
- $HOME/.config/lilacs/lilacs.toml?
- $HOME/.config/lilacs/scripts/* -> $HOME/.local/share/lilacs/bin
- $HOME/.config/lilacs/templates/* -> $HOME/.local/share/lilacs/templates
