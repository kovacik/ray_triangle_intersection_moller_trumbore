all:
	cd tests && $(MAKE) all
	cd samples && $(MAKE) all

clean:
	cd tests && $(MAKE) clean
	cd samples && $(MAKE) clean

test:
	cd tests && $(MAKE) run

sample:
	cd samples && $(MAKE) run

run:
	make test & make sample
                    
.PHONY: all clean test sample run