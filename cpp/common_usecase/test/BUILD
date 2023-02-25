load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "hello-test",
    # "Heaviness": required time/resources of the test target,
    # "small": 20MB / 1 CPU / 1 min.
    size = "small",
    srcs = ["hello-test.cpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//main:hello-greet",
    ],
)
