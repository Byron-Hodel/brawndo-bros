set(exeName BrawndoPi)

set(CMAKE_C_STANDARD 11)

add_executable(${exeName}
	main.cpp
)

target_link_libraries(${exeName}
	curl
)

install(TARGETS ${exeName} DESTINATION "${PROJECT_SOURCE_DIR}/bin")