#include"convertcomment.h"

//定义状态
typedef enum
{
	no_comment_state,
	c_comment_state,
	cpp_comment_state,
	end_state,
	str_comment_state
}enum_state;

//定义状态机
typedef struct
{
	FILE *input;
	FILE *output;
	enum_state ulstate;
}state_machine;

//定义全剧状态机
state_machine g_state;
static enum_state g_pre_state;

int convertcomment(FILE *inputfile,FILE *outputfile)
{
	if(inputfile==NULL||outputfile==NULL)
	{
		printf("invalid arugment inputfile or outputfile.\n");
		return -1;
	}

	//初始化状态机
	g_state.input=inputfile;
	g_state.output=outputfile;
	g_state.ulstate=no_comment_state;
	g_pre_state=no_comment_state;

	char ch;
	while(g_state.ulstate != end_state)
	{
		ch=fgetc(g_state.input);
		eventpro(ch);
	}
	return 0;
}

///////////////////////////////////////////////////////
void  write_double(char ch1,char ch2,FILE *fp)
{
	fputc(ch1,fp);
	fputc(ch2,fp);
}

void write_ch(char ch,FILE *fp)
{
	fputc(ch,g_state.output);
}

char read_ch(FILE *fp)
{
	return fgetc(fp);
}

////////////////////////////////////////////////////////

void write_blank_double()
{
	write_double(' ',' ',g_state.output);
}

void write_c(char ch)
{
	switch(ch)
	{
	case '/':
		write_double('/','*',g_state.output);
		break;
	case '*':
		write_double('*','/',g_state.output);
		break;
	}
}

void write_cpp()
{
	write_double('/','/',g_state.output);
}

///////////////////////////////////////////////////////

void eventpro(char ch)
{
	switch(g_state.ulstate)
	{
	case no_comment_state:
		eventpro_no(ch);
		break;
	case c_comment_state:
		eventpro_c(ch);
		break;
	case cpp_comment_state:
		eventpro_cpp(ch);
		break;
	case str_comment_state:
		eventpro_str(ch);
		break;
	}
}

void eventpro_no(char ch)
{
	char nextch;
	switch(ch)
	{
	case '/':
		nextch=read_ch(g_state.input);
		if(nextch=='/')   //进入c++注释
		{
			write_c('/');
			g_state.ulstate=cpp_comment_state;
		}
		else if(nextch=='*') //进入c语言注释
		{
			write_c('/');
			g_state.ulstate=c_comment_state;
		}
		else      //   /s
		{
			write_double(ch,nextch,g_state.output);
		}
		break;
	case '"':
		write_ch(ch,g_state.output);
		g_state.ulstate=str_comment_state;
		break;
	case EOF:
		g_state.ulstate=end_state;
	default:
		write_ch(ch,g_state.output);
		break;

	}
}

void eventpro_c(char ch)
{
	char nextch;
	switch(ch)
	{
		case '/':
			nextch=read_ch(g_state.input);
			if(nextch=='/'||nextch=='*') //  /*12///*3*/
			{
				if(g_pre_state==c_comment_state)
				{
					//write_cpp();
					write_double(ch,nextch,g_state.output);
				}
				else
					write_blank_double();
			}
			else   //  /*1/2*/
			{
				write_double(ch,nextch,g_state.output);
			}
			break;
		case '*':
			nextch=read_ch(g_state.input);
			if(nextch=='/')
			{
				write_c('*');
				g_state.ulstate=no_comment_state;
				g_pre_state=no_comment_state;
			}
			else
			{
				write_ch(ch,g_state.output);
				fseek(g_state.input,-1,SEEK_CUR);
			}
			break;
		case '"':
			write_ch(ch,g_state.output);
			g_pre_state=c_comment_state;
			break;
		case EOF:
			g_state.ulstate=end_state;
			break;
		default:
			write_ch(ch,g_state.output);
	}
}

void eventpro_cpp(char ch)
{
	char nextch;
	char thirdch;
	switch(ch)
	{
	case EOF:
		write_c('*');
		g_state.ulstate=end_state;
		break;
		
	case '/':
		nextch=read_ch(g_state.input);
		if(nextch=='/'||nextch=='*')  //123//  or   //123/*cd
		{
			if(nextch=='/')   //123//abc
			{
				thirdch=read_ch(g_state.input);
				if(thirdch=='/')   //////////////123
				{
					while(thirdch=read_ch(g_state.input)=='/');
						write_ch(thirdch,g_state.output);
				}
				if(g_pre_state==cpp_comment_state)
				{
					write_cpp();
				}
				else
				{
					write_blank_double();
					fseek(g_state.input,-1,SEEK_CUR);
				}
			}
			else if(nextch=='*')
			{
				if(g_pre_state==cpp_comment_state)
				{
					write_double(ch,nextch,g_state.output);
				}
				else
				    write_blank_double();
			}
		}
		else
		{
			write_ch(ch,g_state.output);
			fseek(g_state.input,-1,SEEK_CUR);
		}
		break;
		
	case '*':
		nextch=read_ch(g_state.input);
		if(nextch=='/')
		{
			write_blank_double();
		}
		else
		{
			write_double(ch,nextch,g_state.output);
		}
		break;
	case '"':
		write_ch(ch,g_state.output);
		g_pre_state=cpp_comment_state;
		break;
	case '\n':
		write_c('*');
		write_ch('\n',g_state.output);
		g_state.ulstate=no_comment_state;
		g_pre_state=no_comment_state;
		break;
	default:
		write_ch(ch,g_state.output);
		break;
	}
}

void eventpro_str(char ch)
{
	char nextch;
	switch(ch)
	{
	case '/':
		nextch=read_ch(g_state.input);
		if(nextch=='/')
		{
			write_cpp();
		}
		else if(nextch=='*')
		{
			write_blank_double();
		}
		else
		{
			write_double(ch,nextch,g_state.output);
		}
		break;
	case '*':
		nextch=read_ch(g_state.input);
		if(nextch=='/')
		{
			write_blank_double();
		}
		else
		{
			write_double(ch,nextch,g_state.output);
		}
		break;
	case '"':
		write_ch('"',g_state.output);
		g_state.ulstate=no_comment_state;
		break;
	case EOF:
		g_state.ulstate=end_state;
	default:
		write_ch(ch,g_state.output);
		break;
	}
}
