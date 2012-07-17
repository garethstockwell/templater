MAKEFILE          = Makefile
DEL_FILE          = del
DEL_DIR           = rmdir
CHK_DIR_EXISTS    = if not exist
MKDIR             = mkdir
MOVE              = move
MAKE              = make
SBS               = sbs
RELEASE_DIR       = /epoc32/release
SELFSIGNED_CERT   = sis/selfsigned.cer
SELFSIGNED_KEY    = sis/selfsigned.key

PROJECT           = {{PROJECT}l}
SIS               = sis/$(PROJECT).sis
SELFSIGNED_SIS    = sis/$(PROJECT).selfsigned.sis

PLATFORM          = armv5
BUILD             = urel
TARGET            = $(RELEASE_DIR)/$(PLATFORM)/$(BUILD)/$(PROJECT).exe

first: sis

# Aliases

target: $(TARGET)
sis: $(SELFSIGNED_SIS)

export:
	cd group && $(SBS) export

cleanexport:
	cd group && $(SBS) cleanexport

runonphone: sis
	runonphone $(RUN_ON_PHONE_OPTIONS) --sis sis/{{PROJECT}l}.selfsigned.sis {{PROJECT}l}.exe $(RUN_OPTIONS)

distclean: clean
	$(DEL_FILE) $(SIS)
	$(DEL_FILE) $(SELFSIGNED_SIS)

clean:
	cd group && $(SBS) reallyclean

# Actual rules

$(TARGET):
	cd group && $(SBS) -c $(PLATFORM)_$(BUILD)

$(SIS): $(TARGET)
	cd sis && makesis $(PROJECT).pkg

$(SELFSIGNED_SIS): $(SIS)
	signsis $(SIS) $(SELFSIGNED_SIS) $(SELFSIGNED_CERT) $(SELFSIGNED_KEY)

