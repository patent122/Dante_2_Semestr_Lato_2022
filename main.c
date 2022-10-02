#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tested_declarations.h"
#include "rdebug.h"

#define M_PI 3.14159265358979323846

enum figure_types 
{
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};
struct point_t
{
    int px;
    int y;
};
struct rectangle_t
{
    struct point_t kolejne;
    int width;
    int height;
};
struct circle_t
{
    struct point_t c;
    float r;
};
struct triangle_t
{
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};
struct figure_t {
    union
    {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};

float area_triangle(const struct triangle_t* t);
float area_rectangle(const struct rectangle_t* r);
float area_circle(const struct circle_t* c);
float area_figure(const struct figure_t* figura);
void display_rectangle(const struct rectangle_t* rect);
void display_triangle(const struct triangle_t* t);
void display_circle(const struct circle_t* circ);
void display_figure(struct figure_t* figura);
int sort_by_area(struct figure_t** figury, int size);

int main()
{
    struct figure_t figury[50];
    int odpowiedz = 0;
    int px = 0;

    while (px < 50)
    {
        printf("Enter figure's type: ");
        if (scanf("%d", &odpowiedz) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        if (odpowiedz == 0)
        {
            break;
        }
        if (odpowiedz == 1)
        {
            printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3): ");
            (figury + px)->type = 1;
            int blad = scanf("%d %d %d %d %d %d", &(figury + px)->triangle.p1.px, &(figury + px)->triangle.p1.y,
                &(figury + px)->triangle.p2.px, &(figury + px)->triangle.p2.y,
                &(figury + px)->triangle.p3.px, &(figury + px)->triangle.p3.y);
            if (blad != 6)
            {
                printf("Incorrect input\n");
                return 1;
            }
        }
        else if (odpowiedz == 2)
        {
            printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");
            (figury + px)->type = 2;
            int blad = scanf("%d %d %d %d", &(figury + px)->rect.kolejne.px, &(figury + px)->rect.kolejne.y,
                &(figury + px)->rect.width, &(figury + px)->rect.height);
            if (blad != 4)
            {
                printf("Incorrect input\n");
                return 1;
            }
        }
        else if (odpowiedz == 3)
        {
            printf("Enter coordinates and radius of a circle: ");
            (figury + px)->type = 3;
            int blad = scanf("%d %d %f", &(figury + px)->circ.c.px, &(figury + px)->circ.c.y, &(figury + px)->circ.r);

            if (blad != 3)
            {
                printf("Incorrect input\n");
                return 1;
            }
        }
        else
        {
            printf("Incorrect input data\n");
            return 2;
        }

        px++;
    }
    for (int i = 0; i < px; i++)
    {
        if ((figury + i)->type == 1)
        {
            if
                (
                    ((figury + i)->triangle.p1.px == (figury + i)->triangle.p2.px) && ((figury + i)->triangle.p1.y == (figury + i)->triangle.p2.y) ||
                    ((figury + i)->triangle.p2.px == (figury + i)->triangle.p3.px) && ((figury + i)->triangle.p2.y == (figury + i)->triangle.p3.y) ||
                    ((figury + i)->triangle.p1.px == (figury + i)->triangle.p3.px) && ((figury + i)->triangle.p1.y == (figury + i)->triangle.p3.y)
                    )
            {
                printf("Incorrect input data");
                return 2;
            }
        }
        else if ((figury + i)->type == 2)
        {
            if ((figury + i)->rect.height < 0 || (figury + i)->rect.width < 0)
            {
                printf("Incorrect input data");
                return 2;
            }
        }
        else if ((figury + i)->type == 3)
        {
            if ((figury + i)->circ.r <= 0)
            {
                printf("Incorrect input data");
                return 2;
            }
        }
    }

    struct figure_t* kolejne[50];

    for (int i = 0; i < px; i++) {
        *(kolejne + i) = figury + i;
    }

    sort_by_area(kolejne, px);

    for (int i = 0; i < px; ++i)
    {
        display_figure(*(kolejne + i));
    }

    return 0;
}

float area_triangle(const struct triangle_t* t)
{
    if (t == NULL || &t->p1 == NULL || &t->p2 == NULL || &t->p3 == NULL) return -1;

    if (t->p1.px == t->p2.px && t->p1.y == t->p2.y) {
        return -1;
    }
    if (t->p1.px == t->p3.px && t->p1.y == t->p3.y) {
        return -1;
    }
    if (t->p2.px == t->p3.px && t->p2.y == t->p3.y) {
        return -1;
    }

    float px = (t->p2.px - t->p1.px) * (t->p3.y - t->p1.y) - (t->p2.y - t->p1.y) * (t->p3.px - t->p1.px);

    if (px == 0)
    {
        return -1;
    }

    return 0.5 * abs(px);
}

float area_rectangle(const struct rectangle_t* r)
{
    if (r == NULL || r->width < 0 || r->height < 0) return -1;
    return (float)(r->width * r->height);
}

float area_circle(const struct circle_t* c)
{
    if (c == NULL) return -1;
    if (c->r <= 0) return -1;

    return M_PI * pow(c->r, 2);
}

float area_figure(const struct figure_t* figura)
{
    if (figura == NULL) return -1;

    if (figura->type == TRIANGLE)
    {
        if
            (
                (figura->triangle.p1.px == figura->triangle.p2.px && figura->triangle.p1.y == figura->triangle.p2.y) ||
                (figura->triangle.p1.px == figura->triangle.p3.px && figura->triangle.p1.y == figura->triangle.p3.y) ||
                (figura->triangle.p2.px == figura->triangle.p3.px && figura->triangle.p2.y == figura->triangle.p3.y)
                )
        {
            return -1;
        }
        else
        {
            return area_triangle(&figura->triangle);
        }
    }
    else if (figura->type == RECTANGLE)
    {
        if (figura->rect.height < 0 || figura->rect.width < 0)
            return -1;
        else
            return area_rectangle(&figura->rect);
    }
    else if (figura->type == CIRCLE)
    {
        if (figura->circ.r <= 0)
            return -1;
        else
            return area_circle(&figura->circ);
    }
    else
    {
        return -1;
    }
}

void display_rectangle(const struct rectangle_t* rect)
{
    if (rect == NULL)
    {
        return;
    }
    printf("Rectangle (%d, %d), width = %d, height = %d\n", rect->kolejne.px, rect->kolejne.y, rect->width, rect->height);
}

void display_triangle(const struct triangle_t* t)
{
    if (t == NULL)
    {
        return;
    }
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)\n", 
        t->p1.px, t->p1.y, t->p2.px, t->p2.y, t->p3.px, t->p3.y);
}

void display_circle(const struct circle_t* circ)
{
    if (circ == NULL)
    {
        return;
    }
    printf("Circle (%d, %d), radius = %f\n", circ->c.px, circ->c.y, circ->r);
}

void display_figure(struct figure_t* figura)
{
    if (figura == NULL)
    {
        return;
    }
    if (figura->type == 1)
    {
        display_triangle(&figura->triangle);
    }
    else if (figura->type == 2)
    {
        display_rectangle(&figura->rect);
    }
    else if (figura->type == 3)
    {
        display_circle(&figura->circ);
    }
    else
    {
        return;
    }
}

int sort_by_area(struct figure_t** figury, int size)
{
    struct figure_t* figura;
    if (figury == NULL || size < 1) return 1;

    for (int i = 0; i < size; ++i)
    {
        if (area_figure(*(figury + i)) == -1) return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (area_figure(*(figury + j)) < area_figure(*(figury + j + 1)))
            {
                figura = *(figury + j + 1);
                *(figury + j + 1) = *(figury + j);
                *(figury + j) = figura;
            }
        }
    }
    return 0;
}

