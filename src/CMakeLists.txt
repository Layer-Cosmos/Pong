add_executable(${PROJECT_NAME}
	pong.c
	client.c
	network_msg.c
	pong_window.c
	server.c
	pong_ball.c
	pong_window.c
	pong_game.c
	pong_msg.c
	color.c
	pong_server.c
	pong_client.c
	)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
