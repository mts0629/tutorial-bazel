load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "hello-time",
    # Get by glob function
    srcs = glob(["*.cpp"]),
    hdrs = ["hello-time.hpp"],
    visibility = ["//main:__pkg__"],
)
