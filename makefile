TARGETS = W16 W32 D16 D32
LIB = libd2sock.a
TARG = $(foreach T,$(TARGETS),src/$(T)/$(LIB))
all: $(TARG)

src/%/$(LIB):
	$(MAKE) -C $(dir $@)

clean:
	$(foreach T,$(TARGETS),$(MAKE) -C src/$(T) clean;)
