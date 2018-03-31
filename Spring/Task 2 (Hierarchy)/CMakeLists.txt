cmake_minimum_required(VERSION 3.9)
project(Task_2__Hierarchy_)

set(CMAKE_CXX_STANDARD 11)

add_executable(Task_2__Hierarchy_ sources/main.cpp sources/ice_cream/ice_cream.cpp sources/ice_cream/ice_cream.h sources/ice_cream/fruit_ice/fruit_ice.cpp sources/ice_cream/fruit_ice/fruit_ice.h sources/ice_cream/milky_ice_cream/milky_ice_cream.cpp sources/ice_cream/milky_ice_cream/milky_ice_cream.h sources/ice_cream/milky_ice_cream/ice_cream_cone/ice_cream_cone.cpp sources/ice_cream/milky_ice_cream/ice_cream_cone/ice_cream_cone.h sources/ingredient/ingredient.cpp sources/ingredient/ingredient.h sources/ice_cream/milky_ice_cream/shaved_ice/shaved_ice.cpp sources/ice_cream/milky_ice_cream/shaved_ice/shaved_ice.h)