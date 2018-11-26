all:
	mkdir -p obj
	$(MAKE) -C src

.PHONY: clean

clean:
	$(MAKE) -C src clean