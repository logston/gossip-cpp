# TODO: Can we move this to the WORKSPACE file?
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

# TODO: Why are there three of these rules? Can't we just use one? I tried
# replacing with `grpc_proto_library` and ran into issues.

proto_library(
    name = "gossip_proto",
    srcs = ["gossip.proto"],
	deps = [
        "@com_google_protobuf//:timestamp_proto",
    ],
)

cc_proto_library(
    name = "gossip_cc_proto",
    deps = [":gossip_proto"],
	visibility = ["//visibility:public"],
)

cc_grpc_library(
    name = "gossip_cc_grpc",
    srcs = [":gossip_proto"],
    grpc_only = True,
    deps = [
		":gossip_cc_proto",
	],
	visibility = ["//visibility:public"],
)
