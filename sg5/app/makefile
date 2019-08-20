all:
	@make -j8 -C ./platform
	@make -j8 -C ./data
	@make -j8 -C ./logic
	@make -j8 -C ./cgi
	@make -j8 -C ./test
clean:
	@make -C ./platform clean
	@make -C ./data clean
	@make -C ./logic clean
	@make -C ./cgi clean
	@make -C ./test clean
install:
	@make -C ./platform install
	@make -C ./data install
	@make -C ./logic install
	@make -C ./cgi install
