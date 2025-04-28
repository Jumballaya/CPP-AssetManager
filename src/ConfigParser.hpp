#pragma once

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Config.hpp"
#include "TextCursor.hpp"

class ConfigParser {
 public:
  static Config loadFromFile(const std::string& filepath) {
    Config config;
    std::ifstream file(filepath);
    if (!file) {
      throw std::runtime_error("Failed to open config file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    parseJsonLike(buffer.str(), config);

    return config;
  }

 private:
  static void parseJsonLike(const std::string& text, Config& config) {
    TextCursor cursor(text);
    char ch = cursor.nextChar();
    if (ch != '{') throwParserError("JSON must start with '{'", cursor);

    while (true) {
      if (ch == '\0') break;

      if (cursor.peekChar() != '"') throwParserError("JSON keys are strings that start with '\"'", cursor);
      auto key = parseKey(cursor);
      ch = cursor.nextChar();
      if (ch != ':') throwParserError("JSON keys and values are separated with ':'", cursor);

      auto peek = cursor.peekChar();
      if (peek == '"') {
        config.set(key, parseString(cursor));
      } else if (isNumber(peek)) {
        config.set(key, parseNumber(cursor));
      } else if (peek == '[') {
        config.set(key, parseArray(cursor));
      } else if (peek == 't' || peek == 'f') {
        config.set(key, parseBool(cursor));
      }

      ch = cursor.nextChar();
      if (ch == ',') {
        continue;  // Expect next key
      } else if (ch == '}') {
        break;  // End of object
      } else {
        throwParserError("Expected ',' or '}' after value", cursor);
      }
    }
  }

  static ConfigValue parseString(TextCursor& cursor) {
    char ch = cursor.nextChar();
    if (ch != '"') throwParserError("Expected '\"' at beginning of string", cursor);

    std::string result;
    while (true) {
      ch = cursor.nextChar();
      if (ch == '\0') {
        throwParserError("Unexpected EOF while parsing string", cursor);
      } else if (ch == '"') {
        break;
      } else if (ch == '\\') {
        char next = cursor.nextChar();
        if (next == '"')
          result += '"';
        else if (next == '\\')
          result += '\\';
        else if (next == 'n')
          result += '\n';
        else if (next == 't')
          result += '\t';
        else
          throwParserError("Unsupported escape sequence in string", cursor);
      } else {
        result += ch;
      }
    }
    return ConfigValue{std::move(result)};
  }

  static std::string parseKey(TextCursor& cursor) {
    char ch = cursor.nextChar();
    if (ch != '"') throwParserError("Expected '\"' at beginning of string", cursor);

    std::string result;
    while (true) {
      ch = cursor.nextChar();
      if (ch == '\0') {
        throwParserError("Unexpected EOF while parsing string", cursor);
      } else if (ch == '"') {
        break;
      } else if (ch == '\\') {
        char next = cursor.nextChar();
        if (next == '"')
          result += '"';
        else if (next == '\\')
          result += '\\';
        else if (next == 'n')
          result += '\n';
        else if (next == 't')
          result += '\t';
        else
          throwParserError("Unsupported escape sequence in string", cursor);
      } else {
        result += ch;
      }
    }
    return result;
  }

  static ConfigValue parseNumber(TextCursor& cursor) {
    std::string numStr;
    char ch = cursor.peekChar();

    while ((ch >= '0' && ch <= '9') || ch == '-' || ch == '.' || ch == '+') {
      numStr += cursor.nextChar();
      ch = cursor.peekChar();
    }

    if (numStr.find('.') != std::string::npos) {
      return ConfigValue(std::stof(numStr));
    }
    return ConfigValue(std::stoi(numStr));
  }

  static ConfigValue parseArray(TextCursor& cursor) {
    char ch = cursor.nextChar();
    if (ch != '[') throwParserError("Expected '[' at beginning of array", cursor);

    std::vector<float> array;

    while (true) {
      ch = cursor.peekChar();
      if (ch == ']') {
        cursor.nextChar();
        break;
      }

      auto value = parseNumber(cursor);

      if (value.is<float>()) {
        array.push_back(value.get<float>());
      } else if (value.is<int>()) {
        array.push_back(static_cast<float>(value.get<int>()));
      } else {
        throwParserError("Expected number inside array", cursor);
      }

      ch = cursor.nextChar();
      if (ch == ',') continue;  // next element
      if (ch == ']') break;

      throwParserError("Expected ',' or ']' after array element", cursor);
    }

    return ConfigValue(std::move(array));
  }

  static ConfigValue parseBool(TextCursor& cursor) {
    char ch = cursor.peekChar();

    if (ch == 't') {
      // Expect "true"
      if (cursor.nextChar() != 't') throwParserError("Expected 'true'", cursor);
      if (cursor.nextChar() != 'r') throwParserError("Expected 'true'", cursor);
      if (cursor.nextChar() != 'u') throwParserError("Expected 'true'", cursor);
      if (cursor.nextChar() != 'e') throwParserError("Expected 'true'", cursor);
      return ConfigValue{true};
    } else if (ch == 'f') {
      // Expect "false"
      if (cursor.nextChar() != 'f') throwParserError("Expected 'false'", cursor);
      if (cursor.nextChar() != 'a') throwParserError("Expected 'false'", cursor);
      if (cursor.nextChar() != 'l') throwParserError("Expected 'false'", cursor);
      if (cursor.nextChar() != 's') throwParserError("Expected 'false'", cursor);
      if (cursor.nextChar() != 'e') throwParserError("Expected 'false'", cursor);
      return ConfigValue{false};
    } else {
      throwParserError("Unexpected character while parsing bool", cursor);
    }
  }

  static bool isNumber(char ch) {
    // allows for a leading '-' or '+'
    return (ch >= '0' && ch <= '9') || ch == '-' || ch == '+';
  }

  [[noreturn]] static void throwParserError(const std::string& message, const TextCursor& cursor) {
    throw std::runtime_error(
        message + " at line " + std::to_string(cursor.line()) + ", column " + std::to_string(cursor.column()));
  }
};