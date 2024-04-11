#include "../../../include/test.h"

void	print_inter_list(t_inter_list *list)
{
	t_inter_list *current;
	int count = 0;

	current = list;
	while (current)
	{
		printf("Intersection %d: \n", ++count);
		printf(" t = %f\n", current->t);
		printf(" Point: (%f, %f, %f)\n", current->inter.point.x, current->inter.point.y, current->inter.point.z);
		printf(" Normal: (%f, %f, %f)\n", current->inter.normal.x, current->inter.normal.y, current->inter.normal.z);

		current = current->next;
		printf("\n");
	}
}

void	test_intersection_obj(void)
{
	t_inter_list 	*inter_list;
	t_sphere		sphere;
	t_object 		*node;
	t_ray			ray;

	node = (t_object *)malloc(sizeof(t_object));
		if (!node)
			printf("F\n");
	sphere.position = set_coords(0, 0, 5);
	sphere.diameter = 1.0;
	matrix_identity(&sphere.transform);
	matrix_identity(&sphere.inversed_t);

	node->type = SPHERE;
	node->object = &sphere;
	node->next = NULL;

	ray.origin = set_coords(0, 0, 0);
	ray.direction = set_vector(0, 0, 1);

	if (intersection_obj(node, &ray, &inter_list))
	{
		printf("intersection found\n");
		print_inter_list(inter_list);
	}
	else
		printf("No intersections were found\n");
}

// void	test_intersection_obj(void)
// {
// 	t_inter_list *inter_list;
// 	t_data		data;
// 	t_ray		ray;
//
// 	char *test_line = "sp 0.0,0.0,0.0 1 255,1,30";
//
// 	analyze_sphere(test_line + 2, &data);
// 	ray.direction = set_vector(0, 0, 1);
// 	ray.origin = set_coords(0, 0, -5);
//
// 	if (intersection_obj(data.objects, &ray, &inter_list))
// 	{
// 		printf("Intersection found\n");
// 		print_inter_list(inter_list);
// 	}
// 	else 
// 		printf("No intersections were found\n");
// }

