#ifndef _CONVERTCOMMENT_H
#define _CONVERTCOMMENT_H

#include"utili.h"

int convertcomment(FILE *inputfile,FILE *outputfile);
void eventpro(char ch);
void eventpro_no(char ch);
void eventpro_cpp(char ch);
void eventpro_c(char ch);
void eventpro_str(char ch);

//////////////////////////////////////////////////////////

void write_double(char ch1,char ch2,FILE *fp);
void write_ch(char ch,FILE *fp);
char read_ch(FILE *fp);
void close_file(FILE *fp);
FILE* open_file(char *file,char *mode);
#endif
