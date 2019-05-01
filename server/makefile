all:
	@make -C outerlib
	@make -C baselib/src
	@make -j8 -C proto
	@make -j8 -C access
	@make -C app
	@make -C cgiapp
clean:
	@make -C outerlib clean
	@make -C baselib/src clean
	@make -C proto clean
	@make -C access clean
	@make -C app clean
	@make -C cgiapp clean
