file(GLOB srcs "*.cpp*")
file(GLOB hdrs "*.h")


add_library(${StackLib} STATIC ${srcs} ${hdrs})


