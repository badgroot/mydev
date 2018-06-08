cmake_minimum_required(VERSION 3.5.0)
project(ftp)
add_executable(ftp_client client.c)
add_executable(ftp_server server.c)