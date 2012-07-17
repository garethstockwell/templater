MAKEFILE          = Makefile
DEL_FILE          = del
DEL_DIR           = rmdir
CHK_DIR_EXISTS    = if not exist
MKDIR             = mkdir
MOVE              = move
DEBUG_PLATFORMS   = winscw gcce armv5 armv6
RELEASE_PLATFORMS = gcce armv5 armv6
MAKE              = make
SBS               = sbs
PKG               = {{PROJECT}l}.pkg
BINARY_TARGET     = /epoc32/release/armv5/udeb/{{PROJECT}l}.exe

first: default
default: debug-armv5
all: debug release

debug:
	cd group && $(SBS) -c winscw_udeb.mwccinc -c gcce_udeb -c armv5_udeb -c armv6_udeb
release:
	cd group && $(SBS) -c gcce_urel -c armv5_urel -c armv6_urel
debug-winscw:
	cd group && $(SBS) -c winscw_udeb.mwccinc
debug-gcce:
	cd group && $(SBS) -c gcce_udeb
debug-armv5:
	cd group && $(SBS) -c armv5_udeb
debug-armv6:
	cd group && $(SBS) -c armv6_udeb
release-gcce:
	cd group && $(SBS) -c gcce_urel
release-armv5:
	cd group && $(SBS) -c armv5_urel
release-armv6:
	cd group && $(SBS) -c armv6_urel

export:
	cd group && $(SBS) export

cleanexport:
	cd group && $(SBS) cleanexport

check: first

$(BINARY_TARGET): release-armv5

sis: $(BINARY_TARGET) sis/$(PKG)
	cd sis && makesis $(PKG)

runonphone: sis
	runonphone $(RUN_ON_PHONE_OPTIONS) --sis sis/{{PROJECT}l}.sis {{PROJECT}l}.exe $(RUN_OPTIONS)

distclean: clean

clean:
	cd group && $(SBS) reallyclean

clean-debug:
	cd group && $(SBS) reallyclean -c winscw_udeb -c gcce_udeb -c armv5_udeb -c armv6_udeb
clean-release:
	cd group && $(SBS) reallyclean -c gcce_urel -c armv5_urel -c armv6_urel
clean-debug-winscw:
	cd group && $(SBS) reallyclean -c winscw_udeb
clean-debug-gcce:
	cd group && $(SBS) reallyclean -c gcce_udeb
clean-debug-armv5:
	cd group && $(SBS) reallyclean -c armv5_udeb
clean-debug-armv6:
	cd group && $(SBS) reallyclean -c armv6_udeb
clean-release-gcce:
	cd group && $(SBS) reallyclean -c gcce_urel
clean-release-armv5:
	cd group && $(SBS) reallyclean -c armv5_urel
clean-release-armv6:
	cd group && $(SBS) reallyclean -c armv6_urel

