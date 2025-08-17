TARGETS = W16 W32 D16 D32
LIB = libd2sock.lib
TARG = $(foreach T,$(TARGETS),src/$(T)/$(LIB))
INSTS = $(addsuffix /$(LIB),$(TARGETS))
.PHONY: force
all: $(INSTS)

$(INSTS): %/$(LIB): src/%/$(LIB)
	[ -d $* ] || mkdir $*
	cp -f $< $@

src/%/$(LIB): force
	$(MAKE) -C $(dir $@)

clean:
	$(foreach T,$(TARGETS),$(MAKE) -C src/$(T) clean;)
	$(foreach T,$(TARGETS),$(RM) -r $(T);)
