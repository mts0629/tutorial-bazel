# Package "lib"
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "hello-time",
    srcs = ["hello-time.cpp"],
    hdrs = ["hello-time.hpp"],
    # Grants access to "//main" package (w/o subpackages)
    visibility = ["//main:__pkg__"],
)
