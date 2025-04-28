#pragma once

#include <cstddef>
#include <string>

class TextCursor {
 public:
  TextCursor(const std::string& text) : _text(text), _pos(0), _col(1), _line(1) {}

  int column() const {
    return _col;
  }

  int line() const {
    return _line;
  }

  char nextChar() {
    skipWhitespace();
    if (_pos >= _text.size()) return '\0';

    char ch = _text[_pos++];
    if (ch == '\n') {
      ++_line;
      _col = 1;
    } else {
      ++_col;
    }

    return ch;
  }

  char peekChar() {
    size_t tempPos = _pos;
    while (tempPos < _text.size() && isspace(_text[tempPos])) {
      ++tempPos;
    }
    if (tempPos >= _text.size()) return '\0';
    return _text[tempPos];
  }

 private:
  const std::string& _text;
  size_t _pos;
  int _line;
  int _col;

  void skipWhitespace() {
    while (_pos < _text.size() && isspace(_text[_pos])) {
      if (_text[_pos] == '\n') {
        ++_line;
        _col = 1;
      } else {
        ++_col;
      }
      ++_pos;
    }
  }
};