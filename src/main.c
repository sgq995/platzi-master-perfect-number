#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Benchmarking
#define BENCH_ENABLE 0
#if BENCH_ENABLE
#define BENCH_START() int64_t benchmark = 0
#define BENCH_TICK() benchmark++
#define BENCH_PRINT() printf("\nBenchmark ticks: %lld\n", benchmark)
#else
#define BENCH_START()
#define BENCH_TICK()
#define BENCH_PRINT()
#endif

// Types
typedef void (*iterator_func_t)(void *context, int64_t num);

typedef struct sum_context {
  int64_t total;
} sum_context_t;

// Iterator functions
void print_it(void *context, int64_t num) {
  printf("%lld ", num);
}

void sum_it(void *context, int64_t num) {
  sum_context_t *sum_context = (sum_context_t *)context;
  sum_context->total += num;
}

// Slow
void divisors_slow(int64_t num, iterator_func_t it_func, void *context) {
  BENCH_START();

  int64_t limit = num / 2 + 1;
  for (int64_t test_div = 1; test_div < limit; ++test_div) {
    if (num % test_div == 0) {
      it_func(context, test_div);
    }

    BENCH_TICK();
  }

  BENCH_PRINT();
}

void print_divisors_slow(int64_t num) {
  divisors_slow(num, print_it, NULL);
}

// Fast
void divisors_fast(int64_t num, iterator_func_t it_func, void *context) {
  BENCH_START();

  int64_t limit = num / 2 + 1;
  int64_t test_div = 2;
  
  it_func(context, 1L);
  while (test_div < limit) {
    if (num % test_div == 0) {
      limit = num / test_div;

      it_func(context, test_div);
      if (test_div != num / test_div) {
        it_func(context, num / test_div);
      }
    }

    ++test_div;

    BENCH_TICK();
  }

  BENCH_PRINT();
}

void print_divisors_fast(int64_t num) {
  divisors_fast(num, print_it, NULL);
}

void sum_divisors_fast(int64_t num, sum_context_t *context) {
  divisors_fast(num, sum_it, context);
}

// Perfect number
bool is_perfect_number(int64_t num) {
  if (num == 1) {
    return false;
  }

  sum_context_t context = { .total = 0, };
  sum_divisors_fast(num, &context);

  return num == context.total;
}

// Commands
void help(const char *program) {
  printf("Por favor ejecute el programa con parametros\n");
  printf("\t%s n1 n2 n3 ...\n\n", program);
}

void verify_perfect_number(int64_t n) {    
  printf("El número %lld ", n);

  bool is_perfect = is_perfect_number(n);
  printf(is_perfect ? "" : "NO ");
  printf("es perfecto\n");
}

// Test
void test() {
  int64_t tests[] = { 6, 14, 28, 496, 8128 };
  int64_t n;

  for (int i = 0; i < 5; ++i) {
    n = tests[i];
    
    verify_perfect_number(n);
  }
}

// Main
int main(int argc, const char **argv) {
  if (argc > 1) {
    int64_t n;
    for (int i = 1; i < argc; ++i) {
      n = atoll(argv[i]);

      verify_perfect_number(n);
    }

    return 0;
  } else {
    help(argv[0]);

    return 1;
  }
}
