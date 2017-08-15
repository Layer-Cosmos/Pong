add_executable(${PROJECT_NAME}
	pong.c
	client.c
	network_msg.c
	pong_window.c
	server.c
	pong_init.c
	pong_ball.c
	pong_paddle.c
	pong_opt.c
	pong_window.c
	pong_game.c
	pong_msg.c
	color.c
	pong_server.c
	pong_client.c
	pong_event.c
	)


find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} SDL2_ttf)
