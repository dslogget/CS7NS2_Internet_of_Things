# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS ${app_sources})

target_add_binary_data(${COMPONENT_TARGET} "certs/AmazonRootCA1.pem" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "certs/3cf24bcf68-certificate.pem.crt" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "certs/3cf24bcf68-private.pem.key" TEXT)