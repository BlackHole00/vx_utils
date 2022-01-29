add_executable(VxUtilsTests
    main.c
)

target_link_libraries(VxUtilsTests PRIVATE VxUtils)

add_test(
    NAME VxUtilsTests
    COMMAND VxUtilsTests -C
)