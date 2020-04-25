#include "parser_files.h"

Parser_files::Parser_files()
{

}

int Parser_files::Parse_string(QString pattern, QString  string_to_parse){
  QString XML_mark;
  XML_mark = "<" + pattern  + ">";
  int parsed_index;
  parsed_index = string_to_parse.indexOf(XML_mark);
  if(parsed_index < 0){
      Parsed_string = Parse_error;
      return -1;
  }

  string_to_parse.remove(0,parsed_index + XML_mark.length());

  XML_mark = "</" + pattern  + ">";
  parsed_index = string_to_parse.indexOf(XML_mark);
  if(parsed_index < 0){
      Parsed_string = Parse_error;
      return -1;
  }
  string_to_parse.truncate(parsed_index);
  Parsed_string = string_to_parse;
  return parsed_index;
}
QString Parser_files::Get_parsed_string(){
  return Parsed_string;
}
