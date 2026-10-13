cmake_minimum_required(VERSION 3.10.0)
project(Practica2_EEDD VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Practica2_EEDD ControlParques.cpp Especie.cpp LectorCSV.cpp Parque.cpp main.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})