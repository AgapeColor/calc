#include "parser.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static Operation parse_op(const char* opt) {
    if (!opt) return NONE;

    if (strcmp(opt, "add") == 0)  return ADD;
    if (strcmp(opt, "sub") == 0)  return SUB;
    if (strcmp(opt, "mul") == 0)  return MUL;
    if (strcmp(opt, "div") == 0)  return DIV;
    if (strcmp(opt, "pow") == 0)  return POW;
    if (strcmp(opt, "fact") == 0) return FACT;

    return NONE;
}

static int parse_num(const char* opt, long long& num) {
    if (!opt) return 1;

    errno = 0;
    char* end = 0;
    num = strtoll(opt, &end, 10);
    if (errno != 0)   return 1;
    if (end == opt)   return 1;
    if (*end != '\0') return 1;

    return 0;
}

void print_help(const char* app) {
    printf("Usage:\n");
    printf("  %s -o add  -a 2 -b 3\n", app);
    printf("  %s -o fact -a 5\n", app);
    
    printf("\nOptions:\n");
    printf("  -o, --op   add|sub|mul|div|pow|fact\n");
    printf("  -a, --a    first integer\n");
    printf("  -b, --b    second integer (not for fact)\n");
    printf("  -h, --help show this help\n");
}

int parse_args(int argc, char** argv, Context& ctx) {
    static struct option long_options[] = {
        {"op",   required_argument, 0, 'o'},
        {"a",    required_argument, 0, 'a'},
        {"b",    required_argument, 0, 'b'},
        {"help", no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };
    
    int c = 0;

    while ((c = getopt_long(argc, argv, "o:a:b:h", long_options, 0)) != -1) {
        switch (c) {
            case 'o':
                ctx.operation = parse_op(optarg);
                break;
            case 'a':
                if (parse_num(optarg, ctx.a) != 0) return 1;
                ctx.has_a = true;
                break;
            case 'b':
                if (parse_num(optarg, ctx.b) != 0) return 1;
                ctx.has_b = true;
                break;
            case 'h':
                print_help(argv[0]);
                return 1;
            default:
                return 1;
        }
    }

    return 0;
}
