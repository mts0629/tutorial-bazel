load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

# Pre-compiled library (header-only)
cc_library(
    name = "constants",
    hdrs = ["constants.hpp"],
    visibility = ["//test:__pkg__"],
)

cc_library(
    name = "hello-greet",
    srcs = ["hello-greet.cpp"],
    hdrs = ["hello-greet.hpp"],
    deps = ["//main:constants"],
    visibility = ["//test:__pkg__"],
)

cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cpp"],
    deps = [
        "//main:hello-greet",
        "//lib:hello-time",
    ],
)
