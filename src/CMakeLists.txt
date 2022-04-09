set(exeName BrawndoPi)

add_executable(${exeName}
	main.cpp
)

install(TARGETS ${exe_name} DESTINATION "${PI_SOURCE_DIR}/bin")