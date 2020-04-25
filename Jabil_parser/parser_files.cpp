#include "parser_files.h"

Parser_files::Parser_files()
{

}

int Parser_files::Parse_string(QString pattern, QString  string_to_parse){
  QString XML_mark;
  XML_mark = "<" + pattern  + ">";
  int first_parse_index;
  first_parse_index = string_to_parse.indexOf(XML_mark);
  if(first_parse_index < 0){
      Parsed_string = Parse_error;
      return -1;
  }

  string_to_parse.remove(0,first_parse_index + XML_mark.length());

  int second_parse_index;
  XML_mark = "</" + pattern  + ">";
  second_parse_index = string_to_parse.indexOf(XML_mark);
  if(second_parse_index < 0){
      Parsed_string = Parse_error;
      return -1;
  }
  string_to_parse.truncate(second_parse_index);
  Parsed_string = string_to_parse;
  return first_parse_index + second_parse_index + XML_mark.length();
}
QString Parser_files::Get_parsed_string(){
  return Parsed_string;
}
