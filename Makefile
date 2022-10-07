##
## EPITECH PROJECT, 2021
## nanotekspice
## File description:
## Makefile
##

SHELL	=	/bin/sh
CXX	=	g++
RM	= 	rm -rf

MAIN	=	src/main.cpp

SRC	=	src/AShape.cpp				\
		src/Errors.cpp				\
		src/Utils.cpp				\
		src/Text.cpp				\
		src/Core.cpp

OBJ	=	$(addsuffix .o, $(basename $(SRC)))

LDFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lSDL2 -lSDL2_ttf -lncurses
CFLAGS	=	-Wall -Wextra -g -fPIC -fno-gnu-unique
CPPFLAGS=	-I include

OK	=	\e[32m
RED	=	\e[91m
END	=	\e[0m

T_PRUNE	=

SRC_T	=	tests/unit_tests.cpp

NAME	=	core
PHONY	:=	all
DEBUG	=	0

define center_text
	echo -e "$(OK)>>>>\t$1$(END)"
endef

ifeq ($(DEBUG), 1)
	LDFLAGS += -fsanitize=address
	CFLAGS += -g -fsanitize=address
endif

all: core
	@$(MAKE) -s -C lib/ graphicals
	@$(MAKE) -s -C lib/ games


PHONY += core
core: $(SRC) $(MAIN)
	@$(call center_text,$@)
	$(eval OBJ += $(MAIN:.cpp=.o))
	@$(MAKE) -s $(OBJ)
	@$(CXX) -o arcade $(OBJ) $(LDFLAGS) && \
	echo -e "$(OK)[DONE]\t$($@)$(END)" || \
	echo -e "$(RED)[FAILURE]\t$($@)$(END)"

PHONY += games
games:
	@$(MAKE) -s -C lib/ $@
	
PHONY += graphicals
graphicals:
	@$(MAKE) -s -C lib/ $@

%.o: %.cpp
	@$(CXX) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< && \
	echo -e "$(OK)[OK]\t$<$(END)" || \
	echo -e "$(RED)[FAILURE]\t$<$(END)"

PHONY += rm_prompt
rm_prompt:
	@$(call center_text,Clean)

PHONY += clean
clean: rm_prompt
	@$(RM) $(OBJ) $(MAIN:.cpp=.o)
	@$(MAKE) -s -C lib/ $@
	@echo -e "$(RED)$(NAME) : Removed object files.$(END)"

PHONY += fclean
fclean: clean rm_prompt
	@$(RM) arcade
	@$(MAKE) -s -C lib/ $@
	@echo -e "$(RED)$(NAME) : Removed arcade.$(END)"

PHONY += fltclean
fltclean: fclean

PHONY += re
re: fltclean all

.PHONY: $(PHONY)
