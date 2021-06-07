#!/bin/sh

mkdir $1

touch "src/$1/$1.h"
cat <<EOF > src/$1/$1.cpp
#include "$1.h"
EOF

cat <<EOF > src/$1/CMakeLists.txt
add_executable($1 $1.cpp)
target_compile_features($1 $2)

EOF
