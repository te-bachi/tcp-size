
CC = gcc

all: $(PROGRAMS)

### VARIABLE
define VARIABLE_template
$(1)_OBJECT = $(addprefix obj/,$($(1)_SOURCE:%.c=%.o))
endef

### OBJECT
define OBJECT_template
obj/$($(2):%.c=%.o): src/$($(2))
	@echo "[CC] $$<"
	@$(CC) -o $$@ -c $$< $($(1)_CFLAGS)
endef

### PROGRAM
define PROGRAM_template
$(foreach source,$($(1)_SOURCE),$(eval $(call OBJECT_template,$(1),source)))
$(1): $($(1)_OBJECT)
	@echo "[LD] $$@"
	@$(CC) -o $$@ $($(1)_OBJECT) $($(1)_LDFLAGS)

$(1)_clean:
	@echo "[CLEAR $(1)]"
	@rm -f $(1) $($(1)_OBJECT)
endef

$(foreach prog,$(PROGRAMS),$(eval $(call VARIABLE_template,$(prog))))
$(foreach prog,$(PROGRAMS),$(eval $(call PROGRAM_template,$(prog))))

clean: $(addsuffix _clean,$(PROGRAMS))
