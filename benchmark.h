#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

/* benchmark.c */
struct benchmark;

extern void bm_init(struct benchmark **);
extern void bm_free(struct benchmark **);
extern void bm_start(struct benchmark *);
extern void bm_finish(struct benchmark *);
extern double bm_result(const struct benchmark *);

#endif /* __BENCHMARK_H__ */

