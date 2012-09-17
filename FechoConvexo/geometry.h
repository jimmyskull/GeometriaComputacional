#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <stdbool.h>

struct Point2i {
    int X;
    int Y;
};

typedef struct Point2i Point;

static inline bool pointcmp(const Point a, const Point b)
{
    return (a.X == b.X) && (a.Y == b.Y);
}

/** Retorna duas vezes o valor da área do triângulo formado pelos
 * pontos |a|, |b| e |c|. */
static inline int area2(const Point a, const Point b, const Point c)
{
    return (a.X * b.Y) - (a.Y * b.X) 
         + (a.Y * c.X) - (a.X * c.Y) 
         + (b.X * c.Y) - (c.X * b.Y);
}

/** Retorna o dobro da área de um polígono |polygon| com |n|
 * vértices. */
static inline int area_poly2(const int n, const Point *polygon)
{
    int i, sum = 0;
    for (i = 1; i < n - 1; i++)
        sum += area2(polygon[0], polygon[i], polygon[i + 1]);
    return sum;
}

/** Retorna se o ponto |c| está à esquerda da reta orientada |ab|. */
static inline bool left(const Point a, const Point b, const Point c)
{
    return area2(a, b, c) > 0;
}

/** Retorna se |c| está à esquerda ou sob a reta orientada |ab|. */
static inline bool lefton(const Point a, const Point b, const Point c)
{
    return area2(a, b, c) >= 0;
}

/** Retorna se |a|, |b| e |c| são colineares. */
static inline bool collinear(const Point a, const Point b, const Point c)
{
    return area2(a, b, c) == 0;
}

/** Retorna se o segmentos de reta |ab| intersecta o segumento
 * |cd| propriamente (apenas um ponto em comum entre os segmentos. */
static inline bool intersect_prop(const Point a, const Point b, 
    const Point c, const Point d)
{
    if (collinear(a, b, c) || collinear(a, b, d)
        || collinear(c, d, a) || collinear(c, d, b))
        return false;
    return (left(a, b, c) ^ left(a, b, d))
        && (left(c, d, a) ^ left(c, d, b));
}

/** Retorna se os pontos |a|, |b| e |c| são colineares e |c| é um
 * ponto do segmento fechado |ab|. */
static inline bool between(const Point a, const Point b, const Point c)
{
    if (!collinear(a, b, c))
        return false;
    if (a.X != b.X)
        return ((a.X <= c.X) && (c.X <= b.X))
            || ((a.X >= c.X) && (c.X >= b.X));
    else
        return ((a.Y <= c.Y) && (c.Y <= b.Y))
            || ((a.Y >= c.Y) && (c.Y >= b.Y));
}

/** Retorna se o segmento |ab| e o segmento |cd| intersectam-se. */
static inline bool intersect(const Point a, const Point b, const Point c,
    const Point d)
{
    if (intersect_prop(a, b, c, d))
        return true;
    return between(a, b, c) || between(a, b, d) 
        || between(c, d, a) || between(c, d, b);
}

/** Retorna se a diagonal |i||j| é uma diagnonal própria internta
 * ou externa do polígono |polygon|. */
static inline bool diagonalie(const int i, const int j, const int n,
    const Point *polygon)
{
    int k, k1;

    for (k = 0; k < n; k++) { /* Para cada aresta k,k+1 de polygon */
        k1 = (k + 1) % n;
        if (k == 1 || k1 == i || k == j || k1 == j)
            continue;
        if (intersect(polygon[i], polygon[j], polygon[k], polygon[k1]))
            return false;
    }
    return true;
}

/** Retorna se |i||j| intersecta arestas do polígono |p|, testando
 * se o segmento |i||j| é interior a |p| na vizinhança. */
static inline bool in_cone(const int i, const int j, const int n,
    const Point *p)
{
    int i1 = (i + 1) % n;
    int in1 = (i + n - 1) % n;
    if (lefton(p[in1], p[i], p[i1]))
        return left(p[i], p[j], p[in1])
            && left(p[j], p[i], p[i1]);
    return !(lefton(p[i], p[j], p[i1]) && lefton(p[j], p[i], p[in1]));
}

/** Retorna de |i||j| é uma diagonal do polígono P. */
static inline bool diagonal(const int i, const int j, const int n,
    const Point *polygon)
{
    return in_cone(i, j, n, polygon) && diagonalie(i, j, n, polygon);
}

#endif /* __GEOMETRY_H__ */

