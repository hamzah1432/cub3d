NAME		= knight
CC			= cc
# CFLAGS		= -Wall -Wextra -Werror
CFLAGS		= 
RM			= rm -f

INCLUDES	= -I./include

OBJDIR		= obj
SRCS		= src/main.c \
# 			  src/init.c \
# 			  src/routine.c \
# 			  src/monitor.c \
# 			  src/utils.c \
# 			  src/cleanup.c \
# 			  src/vaildate_input.c

OBJS		= $(SRCS:src/%.c=$(OBJDIR)/%.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Lminilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
