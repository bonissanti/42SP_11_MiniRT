#include <stdio.h>
#include <stdbool.h>
#include "../../include/minirt.h"
// #include "../intersection/intersections.c" // Include the file containing the function

int main() {
    // Test case 1: Ray intersects with AABB
    t_aabb bbox1 = { {0, 0, 0}, {2, 2, 2} };
    t_ray ray1 = {INFINITY, {1, 1, -1}, {0, 0, 1}, NULL };
    _Bool result1 = intersection_aabb(&bbox1, ray1);
    printf("Test case 1: %s\n", result1 ? "Passed" : "Failed");

    // Test case 2: Ray does not intersect with AABB
    t_aabb bbox2 = { {0, 0, 0}, {2, 2, 2} };
    t_ray ray2 = { INFINITY, {3, 3, 3}, {0, 0, 1}, NULL };
    _Bool result2 = intersection_aabb(&bbox2, ray2);
    printf("Test case 2: %s\n", !result2 ? "Passed" : "Failed");

    // Test case 3: Ray origin inside AABB
    t_aabb bbox3 = { {0, 0, 0}, {2, 2, 2} };
    t_ray ray3 = { INFINITY, {1, 1, 1}, {0, 0, 1}, NULL };
    _Bool result3 = intersection_aabb(&bbox3, ray3);
    printf("Test case 3: %s\n", result3 ? "Passed" : "Failed");

    return 0;
}