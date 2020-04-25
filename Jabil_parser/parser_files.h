#ifndef PARSER_FILES_H
#define PARSER_FILES_H
#include <QString>

class Parser_files
{
public:
    Parser_files();
    int Parse_string(QString pattern, QString  string_to_parse);
    QString Get_parsed_string();
private:
    QString Parsed_string;
    const QString Parse_error = "Parsing error";

};

#endif // PARSER_FILES_H
