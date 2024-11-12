all: publicador suscriptor sistema

publicador: Publicador.c
	gcc -o publicador Publicador.c

suscriptor: Suscriptor.c
	gcc -o suscriptor Suscriptor.c

sistema: SistemaDeComunicacion.c
	gcc -o sistema SistemaDeComunicacion.c

clean:
	rm -f publicador suscriptor sistema
