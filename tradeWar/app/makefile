all:
	@make -C ./common
	@make -C ./kernel
	@make -C ./data
	@make -C ./platform
	@make -C ./config
	@make -C ./protocol
	@make -C ./message

	@make -C ./access
	@make -C ./dbwriter
	@make -C ./login
	@make -C ./transit
	@make -C ./allserver
clean:
	@make -C ./common clean
	@make -C ./kernel clean
	@make -C ./data clean
	@make -C ./platform clean
	@make -C ./config clean
	@make -C ./protocol clean
	@make -C ./message clean

	@make -C ./access clean
	@make -C ./dbwriter clean
	@make -C ./login clean
	@make -C ./transit clean
	@make -C ./allserver clean
in:
	@make -C ./access install
	@make -C ./dbwriter install
	@make -C ./login install
	@make -C ./transit install

test_in:
	@make -C ./battle test
	@make -C ./login test

rebuild:
	@make clean
	@make all
