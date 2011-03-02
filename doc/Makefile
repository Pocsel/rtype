
.PHONY : all

all : uml_simple.png uml_service.png uml_threads.png uml_server.png uml_rtype.png uml_client.png uml_phat.png

clean :
	@rm -vf uml_simple.png uml_service.png uml_threads.png uml_server.png uml_rtype.png uml_client.png uml_phat.png

uml_simple.png : uml_simple.dot
		dot -T png -o uml_simple.png uml_simple.dot

uml_service.png : uml_service.dot
		dot -T png -o uml_service.png uml_service.dot

uml_threads.png : uml_threads.dot
		dot -T png -o uml_threads.png uml_threads.dot

uml_server.png : uml_server.dot
		dot -T png -o uml_server.png uml_server.dot

uml_rtype.png : uml_rtype.dot
		dot -T png -o uml_rtype.png uml_rtype.dot

uml_client.png : uml_client.dot
		dot -T png -o uml_client.png uml_client.dot

uml_phat.png : uml_phat.dot
		dot -T png -o uml_phat.png uml_phat.dot

