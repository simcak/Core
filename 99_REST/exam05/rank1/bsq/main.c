#include "bsq.h"

int	main(int argc, char* argv[])
{
	if (argc == 1)
		if (execute_bsq(stdin) == -1)
			fprintf(stderr, "map error\n");
	else
	{
		for (int i = 1; i < argc; i++)
		{
			if (convert_file_pointer(argv[i]) == -1)
				fprintf(stderr, "map error\n");
			if (i < argc - 1)
				fprintf(stdout, "\n");
		}
	}
	return 0;
}
