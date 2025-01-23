cmake_minimum_required(VERSION 3.28)

add_library(src_lib
        LeakyBucket/LeakyBucketQueue.cpp
        LeakyBucket/LeakyBucketMiddleware.cpp
)
