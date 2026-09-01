#pragma once

#define PANIC(fmt, ...)                                                         \
    do {                                                                        \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);   \
        while (true);                                                           \
    } while (0);                                                                \

struct sbiret {
    long error;
    long value;
};