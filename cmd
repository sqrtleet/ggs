valgrind --tool=memcheck --leak-check=yes  ./
cppcheck --enable=all --suppress=missingIncludeSystem