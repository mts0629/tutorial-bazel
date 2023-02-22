load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

# Library rule
cc_library(
    # Target name, "hello-greet"
    name = "hello-greet",
    # Source list
    srcs = ["hello-greet.cpp"],
    # Header list
    hdrs = ["hello-greet.hpp"],
)

cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cpp"],
    # Dependency list
    deps = [
        # Dependent target (library)
        "//main:hello-greet",
        # Can be specified with relative path:
        # ":hello-greet"
    ],
)
