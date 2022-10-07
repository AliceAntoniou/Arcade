##
## EPITECH PROJECT, 2021
## nanotekspice
## File description:
## Makefile
##

SHELL	=	/bin/sh
CXX	=	g++
RM	= 	rm -rf

SRC	=	../src/AShape.cpp				\
		../src/Errors.cpp				\
		../src/Utils.cpp				\
		../src/Text.cpp

OBJ	=	$(addsuffix .o, $(basename $(SRC)))

LDFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lSDL2 -lSDL2_ttf -shared
CFLAGS	=	-Wall -Wextra -g -fPIC
CPPFLAGS=	-I ../include

OK	=	\e[32m
RED	=	\e[91m
END	=	\e[0m


NAME	=	centipede nibbler sdl2 sfml core
PHONY	:=	all
DEBUG	=	0

define center_text
	echo -e "$(OK)>>>>\t$1$(END)"
endef

ifeq ($(DEBUG), 1)
	CFLAGS += -g -fsanitize=address
endif

all:	

PHONY += centipede
centipede:
	@$(call center_text,$@)
	@$(MAKE) -s centipede/Centipede.o $(OBJ)
	@$(CXX) -o arcade_$@.so centipede/Centipede.o $(OBJ) $(LDFLAGS) && \
	echo -e "$(OK)[DONE]\t$@$(END)" || \
	echo -e "$(RED)[FAILURE]\t$@$(END)"

PHONY += nibbler
nibbler:
	@$(call center_text,$@)
	@$(MAKE) -s nibbler/Nibbler.o $(OBJ)
	@$(CXX) -o arcade_$@.so nibbler/Nibbler.o $(OBJ) $(LDFLAGS) && \
	echo -e "$(OK)[DONE]\t$@$(END)" || \
	echo -e "$(RED)[FAILURE]\t$@$(END)"

PHONY += core
core:
	@$(call center_text,$@)
	@$(MAKE) -s ../src/Core.o $(OBJ)
	@$(CXX) -o arcade_$@.so ../src/Core.o $(OBJ) $(LDFLAGS) && \
	echo -e "$(OK)[DONE]\t$@$(END)" || \
	echo -e "$(RED)[FAILURE]\t$@$(END)"

PHONY += sdl2
sdl2:
	@$(call center_text,$@)
	@$(MAKE) -s sdl2/sdl2.o $(OBJ)
	@$(CXX) -o arcade_$@.so sdl2/sdl2.o $(OBJ) $(LDFLAGS) && \
	echo -e "$(OK)[DONE]\t$@$(END)" || \
	echo -e "$(RED)[FAILURE]\t$@$(END)"

PHONY += sfml
sfml:
	@$(call center_text,$@)
	@$(MAKE) -s sfml/SFML.o $(OBJ)
	@$(CXX) -o arcade_$@.so sfml/SFML.o $(OBJ) $(LDFLAGS) && \
	echo -e "$(OK)[DONE]\t$@$(END)" || \
	echo -e "$(RED)[FAILURE]\t$@$(END)"

PHONY += ncurses
ncurses:
	@$(call center_text,$@)
	@$(MAKE) -s ncurses/Ncurses.o $(OBJ)
	@$(CXX) -o arcade_$@.so ncurses/Ncurses.o $(OBJ) $(LDFLAGS) && \
	echo -e "$(OK)[DONE]\t$@$(END)" || \
	echo -e "$(RED)[FAILURE]\t$@$(END)"

PHONY += graphicals
graphicals: sfml sdl2 ncurses

PHONY += games
games: nibbler centipede


%.o: %.cpp
	@$(CXX) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< && \
	echo -e "$(OK)[OK]\t$<$(END)" || \
	echo -e "$(RED)[FAILURE]\t$<$(END)"

PHONY += clean
clean:
	@find . -type f -name "*.o" -delete
	@echo -e "$(RED)$(NAME) : Removed object files.$(END)"

PHONY += fclean
fclean:
	@find . -type f -name "*.so" -delete
	@echo -e "$(RED)$(NAME) : Removed libs.$(END)"

.PHONY: $(PHONY)
