#---------------------------------------------------------------------------------
# Clear the implicit built in rules
# Template makefile
#---------------------------------------------------------------------------------

export GRRLIB_INC   := ../lib/jpeg/include
export GRRLIB_LIB   := ../lib/jpeg/lib/wii

export JPEG_INC     := ../lib/jpeg/include
export JPEG_LIB     := ../lib/jpeg/lib/wii

export PNG_INC	     := ../lib/png/include
export PNG_LIB	     := ../lib/png/lib/wii

export PNGU_INC	  := ../lib/pngu/include
export PNGU_LIB	  := ../lib/pngu/lib/wii

export ZLIB_INC	  := ../lib/pngu/include
export ZLIB_LIB	  := ../lib/pngu/lib/wii

export FREETYPE_INC := ../lib/freetype/include
export FREETYPE_LIB := ../lib/freetype/lib/wii

export XML_INC	     := ../lib/mxml/include
export XML_LIB	     := ../lib/mxml/lib/wii

.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET	:=	boot
BUILD		:=	build
SOURCES	:=	src
IMAGES	:=	images
DATA		:=	snd
FONT		:=	font
XML  		:=	xml
INCLUDES	:= inc

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CFLAGS		= -g -O2 -Wall $(MACHDEP) $(INCLUDE)
CXXFLAGS	=	$(CFLAGS)
LDFLAGS	=	-g $(MACHDEP) -mrvl -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:=  -lgrrlib -lfreetype -lfat -ljpeg -lpngu -lpng -lz -lmodplay -lmxml -lwiiuse -lbte -lasnd -logc -lm

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= 

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(IMAGES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
					$(foreach dir,$(FONT),$(CURDIR)/$(dir)) \
					$(foreach dir,$(XML),$(CURDIR)/$(dir))
					

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(IMAGES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(IMAGES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES		:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))
FONTFILES	:=	$(foreach dir,$(FONT),$(notdir $(wildcard $(dir)/*.*)))
sXMLFILES	:=	$(foreach dir,$(XML),$(notdir $(wildcard $(dir)/*.s)))
SXMLFILES	:=	$(foreach dir,$(XML),$(notdir $(wildcard $(dir)/*.S)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
					$(addsuffix .o,$(FONTFILES)) \
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) \
					$(sFILES:.s=.o) $(SFILES:.S=.o) \
					$(sXMLFILES:.s=.o) $(SXMLFILES:.S=.o)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------

export INCLUDE	:=	-I$(LIBOGC_INC) \
					-I$(JPEG_INC) \
					-I$(PNG_INC) \
					-I$(PNGU_INC) \
					-I$(ZLIB_INC) \
					-I$(XML_INC) \
					-I$(FREETYPE_INC) \
               -I$(GRRLIB_INC) \
               $(foreach dir,$(INCLUDES), -iquote $(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS), -L$(dir)/lib) \
					-L$(LIBOGC_LIB) \
					-L$(JPEG_LIB) \
					-L$(PNG_LIB) \
					-L$(PNGU_LIB) \
					-L$(ZLIB_LIB) \
					-L$(XML_LIB) \
					-L$(FREETYPE_LIB) \
					-L$(GRRLIB_LIB) 

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol

#---------------------------------------------------------------------------------
run:
	wiiload $(TARGET).dol


#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).dol: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)


#---------------------------------------------------------------------------------
# This rule links in binary data with the .png or .jpg or .mod or.xml extension
#---------------------------------------------------------------------------------
%.png.o	:	%.png
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2c)

-include $(DEPENDS)

%.jpg.o	:	%.jpg
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

-include $(DEPENDS)

%.mod.o	:	%.mod
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

%.pcm.o	:	%.pcm
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
	
	
%.wav.o	:	%.wav
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
	
-include $(DEPENDS)

%.ttf.o	:	%.ttf
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

%.xml.o	:	%.xml
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
