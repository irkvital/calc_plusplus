CC 			=	gcc
CFLAGS 		=	-Wall -Wextra -std=c11
GCOV_FLAGS 	= 	-fprofile-arcs -ftest-coverage
CHECK_FLAGS =	-lcheck -lm -lpthread 
FLAGS 		=	$(CFLAGS) $(CHECK_FLAGS) $(GCOV_FLAGS)
GFLAGS 		=	$(FLAGS)

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	CHECK_FLAGS += -lsubunit -lrt
endif

vpath 			%.o objs_test
vpath 			%.d objs_test

SRCSTEST 	= 	$(wildcard func/*.c tests/*.c)
OBJSTEST 	= 	$(SRCSTEST:%.c=objs_test/%.o)
DEPENDSTEST = 	$(OBJSTEST:%.o=%.d)
OBJTESTDIR 	= 	objs_test/func objs_test/tests

NAME 		= 	test
REPORT_NAME = 	report

.PHONY: all test gcov_report clean install uninstall dvi dist

all: gcov_report install open

install:
	cmake -S ./Smart_Calc -B ./install
	make -C ./install

open:
ifeq ($(UNAME), Darwin)
	open ./install/Smart_Calc.app
endif
ifeq ($(UNAME), Linux)
	./install/Smart_Calc
endif

uninstall:
	rm -rf ./install

test: $(OBJSTEST)
	@rm -rf $(wildcard objs_test/*.gcda objs_test/tests/*.gcda)
	$(CC) $(OBJSTEST) -o $(NAME) $(GFLAGS)

-include $(DEPENDS) $(DEPENDSTEST)

clean:
	@rm -rf objs_test *.info *.a $(REPORT_NAME) $(NAME) finish *.tgz

objs_test/%.o: %.c
	@mkdir -p $(OBJTESTDIR)
	$(CC) -MMD -o $@ -c $< $(FLAGS)

gcov_report: GFLAGS += -lgcov
gcov_report: test
	./$(NAME)
	lcov -t "$(REPORT_NAME)" -o objs_test/$(REPORT_NAME).info -c -d .
	genhtml objs_test/$(REPORT_NAME).info -o finish

dist:
	rm -rf Smart_Calc_v1.0
	mkdir Smart_Calc_v1.0
	cp -r Makefile Smart_Calc tests func Smart_Calc_v1.0/
	tar cvzf ./Smart_Calc_v1.0.tgz Smart_Calc_v1.0/
	rm -rf Smart_Calc_v1.0/

# Helpers
debug: test
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

san: FLAGS += -fsanitize=address -g
san: test
	./test

h:
ifeq ($(UNAME), Linux)
	firefox finish/index.html
endif
ifeq ($(UNAME), Darwin)
	open finish/index.html
endif
