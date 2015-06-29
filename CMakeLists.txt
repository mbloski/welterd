cmake_minimum_required(VERSION 2.6)

project(welterd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(
/usr/include/glib-2.0
/usr/lib/glib-2.0/include
/usr/include/gdk-pixbuf-2.0
/usr/include/gtk-3.0
/usr/include/pango-1.0
/usr/include/cairo /usr/include/atk-1.0
)

subdirs(src)
