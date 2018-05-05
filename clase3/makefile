CC65 = cc65
CA65 = ca65
LD65 = ld65
NAME = clase3
DEPEN = PALETTE.c CODE.c

$(NAME).nes: $(NAME).o reset.o nes.cfg
	$(LD65) -C nes.cfg -o $(NAME).nes reset.o $(NAME).o nes.lib
# if linux uncomment the next line
	rm *.o
	nestopia $(NAME).nes
# windows	
#	del *.o	
	@echo $(NAME).nes created

reset.o: reset.s
	$(CA65) reset.s

$(NAME).o: $(NAME).s
	$(CA65) $(NAME).s

$(NAME).s: $(NAME).c $(DEPEN)
	$(CC65) -Oi $(NAME).c --add-source

clean:
# if linux uncomment the next line
	rm $(NAME).nes
# windows
#	del $(NAME).nes

