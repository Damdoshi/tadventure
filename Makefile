# Erk Makefile Ltd.
# All duties reserved

all:
	bcc -I./include/ -fPIC -rdynamic -Wextra -Wall -g -g3 -ggdb `find . -name "*.c"` -o tadventure
clean:
	find . -name "*~" -delete
fclean:
	rm -f tadventure
re: fclean all
