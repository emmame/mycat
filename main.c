#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// line_numbers specifies if each line should be preceded by the line number
// 1 = line numbering is on
// 0 = line numbering is off
static int line_numbers;

// line_endings specifies if each line should end by a $ character
// 1 = line ending is on
// 0 = line ending is off
static int line_endings;

// Parses the command line arguments, fills in the values for line numbers and line endings
// Returns a pointer to the first file in argv (the previous should be only parameters)
char** parse_commandline (int argc, char **argv)
{
	int j;
	while (*argv != NULL && (*argv)[0] == '-')
	{
		for (j = 1; j < strlen (*argv); j ++)
			{
				switch ((*argv)[j])
				{

					case 'n':
							line_numbers = 1;
							break;
					case 'E': 
							line_endings = 1;
							break;
					default: 
							printf("mycat: invalid option -- '%c'\n", (*argv)[j]);
							exit(-1);
							break;
				}
			}
		argv++;
	}

	return argv;
}

// Prints the contents of the file specified by filename
// Takes into account the line endings and numbering options
void print_current_file (char *filename)
{
	// k represents the line numbers
	static int k = 1;
	unsigned char last = 0;
	FILE *f;

	if (filename == NULL) 
	{
		f = stdin;
	} 
	else
	{
		f = fopen (filename, "r");

		if (f == NULL) 
		{
			//perror("mycat: ");
			printf("mycat: %s: No such file or directory.\n", filename);
			return;
		}
	}

	// ch1, ch2 are the characters read form the file
	char ch1;
	
	while ((ch1 = getc (f)) != EOF)
	{
		if (line_numbers && (last == '\n' || last == 0))
		{
			printf ("\t%d  ", k ++);
		}

		if (line_endings && ch1 == '\n')
		{
			putchar ('$');
		}

		putchar (ch1);
		last = ch1;
	}

	fclose (f);
}

// Implementation

// Testing functions
void test_params (void)
{
	if (line_endings) 
	{
		printf ("Argument -E was used!\n");
	}

	if (line_numbers) 
	{
		printf ("Argument -n was used!\n");
	}
}

int main (int argc, char *argv[])
{
	char** current_filename = parse_commandline (argc, argv + 1);

	if (*current_filename == NULL) 
	{
		print_current_file(NULL);
		return 0;
	}

	while (*current_filename != NULL)
	{
		print_current_file (*current_filename);
		current_filename++;
	}

	//test_params ();
	return 0;
}