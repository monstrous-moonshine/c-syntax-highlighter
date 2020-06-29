OBJDIR = obj
CFLAGS = -g

objects = $(addprefix $(OBJDIR)/, common.o main.o number.o punct.o \
	scanner.o token.o tokenlist.o tokentype.o util.o)

vpath %.c src

shc: $(objects)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -v $(OBJDIR)

.PHONY: clean
clean:
	-rm $(objects)
