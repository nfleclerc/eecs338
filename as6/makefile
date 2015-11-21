CC = gcc
CFLAGS = -g -Wall
TSOURCE = tina.c cookie_clnt.c #cookie_xdr.c
JSOURCE = judy.c cookie_clnt.c #cookie_xdr.c
SSOURCE = cookie_svc.c mother.c #cookie_xdr.c
RPCSRC = cookie.x
RPCGEN = cookie.h cookie_clnt.c cookie_svc.c #cookie_xdr.c
CLIENT_A = tina
CLIENT_B = judy
SERVER = mother
LIBS = -lnsl

all: $(CLIENT_A) $(CLIENT_B) $(SERVER)

tina: $(TSOURCE) $(RPCGEN)
	$(CC) $(LIBS) $(CFLAGS) -o $(CLIENT_A) $(TSOURCE) $(LIBS)

judy: $(JSOURCE) $(RPCGEN)
	$(CC) $(LIBS) $(CFLAGS) -o $(CLIENT_B) $(JSOURCE) $(LIBS)

mother: $(SSOURCE) $(RPCGEN)
	$(CC) $(LIBS) $(CFLAGS) -o $(SERVER) $(SSOURCE) $(LIBS)

$(RPCGEN): $(RPCSRC)
	rpcgen $(RPCSRC)
clean:
	@- rm -f $(CLIENT_A) $(CLIENT_B)  $(SERVER)
	
clean-all: clean 
	@- rm -f $(RPCGEN)
