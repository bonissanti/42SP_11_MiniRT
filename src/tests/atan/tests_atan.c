#include "../../../include/test.h"

void	test_atan(void)
{
	t_vec3	orientation;

	orientation.x = 0.45083481733371611;
	orientation.y = -0.6311687442672026;
	orientation.z = -0.6311687442672026;

	int y_angle1 = atan(orientation.x / orientation.z);
	int y_angle2 = atan2(orientation.x, orientation.z);
	printf("Atan Y: %d | Atan2 Y: %d\n", y_angle1, y_angle2);

	int x_angle1 = atan(orientation.z / orientation.y);
	int x_angle2 = atan2(orientation.z, orientation.y);
	printf("Atan X: %d | Atan2 X: %d\n", x_angle1, x_angle2);

	int z_angle1 = atan(-orientation.x / orientation.y);
	int z_angle2 = atan2(-orientation.x, orientation.y);
	printf("Atan Z: %d | Atan2 Z: %d\n", z_angle1, z_angle2);
}

