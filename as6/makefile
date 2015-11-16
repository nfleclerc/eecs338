NAME := as6
SERVER := mother.o
CLIENTA := tina.o
CLIENTB := judy.o
RPC_SVC := cookie_xdr.c cookie_svc.c
RPC_CLNT := cookie_clnt.c cookie_xdr.c
CC := gcc
ARGS := -Wall -g
LIBS := -lnsl

.PHONY: clean distclean

all: $(CLIENTA) $(CLIENTB) $(SERVER)

$(CLIENTA):
	$(CC) $(ARGS) tina.c $(RPC_CLNT) -o $(CLIENTA) $(LIBS) 

$(CLIENTB):
	$(CC) $(ARGS) judy.c $(RPC_CLNT) -o $(CLIENTB) $(LIBS) 

$(SERVER):
	$(CC) $(ARGS) mother.c $(RPC_SVC) -o $(SERVER) $(LIBS) 

clean:
	@- $(RM) -f $(SERVER) $(CLIENTS) 

clean-rpc:
	@- $(RM) -f  $(RPC_CLNT) $(RPC_SVC)

distclean: clean
