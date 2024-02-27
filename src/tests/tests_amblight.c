#include <assert.h>
#include "../../include/minirt.h"

void	test_analyze_amblight(void)
{
	t_data data;
	init_structs(&data);

	char *test_line = "A 0.2 255,255,255";
	int	result = analyze_amblight(test_line, &data);

	assert(result == OK);

	assert(data.amblight.ratio == 0.2);
	assert(data.amblight.color[0] == 255);
	assert(data.amblight.color[1] == 255);
	assert(data.amblight.color[2] == 255);

	printf("Test #1 - Amblight OK\n");	
}

int	main(void)
{
	test_analyze_amblight();
	return (0);
}
