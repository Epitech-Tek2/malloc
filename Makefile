LD		=	@ld
CC		=	@gcc
ASM		=	@nasm

SRC		=	$(wildcard $(addprefix sources/, *).asm)
NOM		=	$(basename $(notdir $(SRC)))
OBJ		=	$(addprefix sources/, $(addsuffix .o, $(NOM)))
SRC-CRIT	=	$(wildcard $(addprefix tests/, *).c)
SRC-TEST	=	$(addprefix test/, main.c)
OBJ-TEST        =       $(SRC-TEST:.c=.o)
OBJ-CRIT        =       $(SRC-CRIT:.c=.o)

CPPFLAGS	+=	-Wall -Wextra -fPIC -g3
LDFLAGS		+=	-shared
CFLAGS		+=	-Iincludes -fno-builtin
ASFLAGS		+=	-felf64 -Iincludes/
CRITFLAGS	=	-lcriterion --coverage

SURNAME		=	asm
NAME		=	libasm.so

all:	$(NAME)

$(NAME):	$(OBJ)
	@$(LD) $(LDFLAGS) -o $(NAME) $(OBJ)

test_run:	all $(OBJ-CRIT)
	@$(CC) tests/*.c -o unit_tests $(CFLAGS) $(CRITFLAGS) -ldl
	./unit_tests

clean:
	@find . -type f \( -iname "*~" \) -delete
	@$(RM) $(OBJ)
	@$(RM) $(OBJ-ARM)
	@$(RM) $(OBJ-TEST)
	@$(RM) $(OBJ-CRIT)
	@$(RM) $(OBJ-32)
	@$(RM) *.gcno
	@$(RM) *.gcda

fclean:	clean
	@$(RM) $(SURNAME)
	@$(RM) $(NARME)
	@$(RM) $(NAME)
	@$(RM) $(NAME-32)
	@$(RM) unit_tests

re:	fclean all

sources/%.o:	%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<			\
	&& echo "$(GREEN)[OK]$(BOLD)" $< "$(END)"			\
	|| echo "$(RED)[KO]$(BOLD)" $< "$(END)"

sources/%.o:	sources/%.asm
	@$(ASM) $(ASFLAGS) -o $@ $<					\
	&& echo "$(GREEN)[OK]$(BOLD)" $< "$(END)"			\
	|| echo "$(RED)[KO]$(BOLD)" $< "$(END)"

.PHONY: all clean fclean re