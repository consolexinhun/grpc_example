cmake_minimum_required(VERSION 3.5)
project(grpc)

find_package(Threads REQUIRED)
find_package(protobuf REQUIRED)
find_package(gRPC REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set (grpc_src 
${CMAKE_CURRENT_SOURCE_DIR}/gen_code/test.grpc.pb.cc
${CMAKE_CURRENT_SOURCE_DIR}/gen_code/test.pb.cc
)

foreach(_target server client)
    add_executable(${_target} "${CMAKE_CURRENT_SOURCE_DIR}/${_target}.cc" ${grpc_src})
    target_link_libraries(${_target}
        gRPC::grpc++_reflection
        gRPC::grpc++
        protobuf::libprotobuf
    )
endforeach()

# add_executable(server "${CMAKE_CURRENT_SOURCE_DIR}/server.cc" ${grpc_src})
# target_link_libraries(server
#     gRPC::grpc++_reflection
#     gRPC::grpc++
#     protobuf::libprotobuf
# )
