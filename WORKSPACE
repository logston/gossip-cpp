# Load Protobuf
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_protobuf",
    strip_prefix = "protobuf-3.19.0",
    urls = [
        "https://github.com/protocolbuffers/protobuf/archive/v3.19.0.tar.gz",
    ],
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

# Load gRPC
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/refs/tags/v1.45.2.tar.gz",
    ],
	strip_prefix = "grpc-1.45.2",
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
# TODO: Why do we need to load two deps? What's the difference between
# grpc_extra_deps and grpc_deps?
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()
