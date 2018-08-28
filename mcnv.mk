##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=mcnv
ConfigurationName      :=Debug
WorkspacePath          :=/home/remus/RESEARCH_SLL/MetaCNV_v1.2
ProjectPath            :=/home/remus/RESEARCH_SLL/MetaCNV_v1.2
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=remus
Date                   :=12/08/18
CodeLitePath           :=/home/remus/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="mcnv.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell pkg-config gtkmm-3.0 --libs)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -std=c++14 -g -O0 -Wall  $(shell pkg-config gtkmm-3.0 --cflags) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_new_segments_new_segments.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_new_segments_new_segmentsF.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_normalize_normalize.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_normalize_normalizeF.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_normalize_normalize_XY.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_combine_combine.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_combine_combineF.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_combine_combine_XY.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_compress_compress.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_compress_compressF.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_compress_compress_XY.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_match_to_ref_match_to_ref.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_cnvnator_cnvnator.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_cnvnator_cnvnatorsplit.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_cnvnator_cnvnator_female.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Interface_mcnvgui.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.cpp$(DependSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.cpp$(DependSuffix) -MM src/main.cpp

$(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix): src/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix) src/main.cpp

$(IntermediateDirectory)/src_new_segments_new_segments.cpp$(ObjectSuffix): src/new_segments/new_segments.cpp $(IntermediateDirectory)/src_new_segments_new_segments.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/new_segments/new_segments.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_new_segments_new_segments.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_new_segments_new_segments.cpp$(DependSuffix): src/new_segments/new_segments.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_new_segments_new_segments.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_new_segments_new_segments.cpp$(DependSuffix) -MM src/new_segments/new_segments.cpp

$(IntermediateDirectory)/src_new_segments_new_segments.cpp$(PreprocessSuffix): src/new_segments/new_segments.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_new_segments_new_segments.cpp$(PreprocessSuffix) src/new_segments/new_segments.cpp

$(IntermediateDirectory)/src_new_segments_new_segmentsF.cpp$(ObjectSuffix): src/new_segments/new_segmentsF.cpp $(IntermediateDirectory)/src_new_segments_new_segmentsF.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/new_segments/new_segmentsF.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_new_segments_new_segmentsF.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_new_segments_new_segmentsF.cpp$(DependSuffix): src/new_segments/new_segmentsF.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_new_segments_new_segmentsF.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_new_segments_new_segmentsF.cpp$(DependSuffix) -MM src/new_segments/new_segmentsF.cpp

$(IntermediateDirectory)/src_new_segments_new_segmentsF.cpp$(PreprocessSuffix): src/new_segments/new_segmentsF.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_new_segments_new_segmentsF.cpp$(PreprocessSuffix) src/new_segments/new_segmentsF.cpp

$(IntermediateDirectory)/src_normalize_normalize.cpp$(ObjectSuffix): src/normalize/normalize.cpp $(IntermediateDirectory)/src_normalize_normalize.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/normalize/normalize.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_normalize_normalize.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_normalize_normalize.cpp$(DependSuffix): src/normalize/normalize.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_normalize_normalize.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_normalize_normalize.cpp$(DependSuffix) -MM src/normalize/normalize.cpp

$(IntermediateDirectory)/src_normalize_normalize.cpp$(PreprocessSuffix): src/normalize/normalize.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_normalize_normalize.cpp$(PreprocessSuffix) src/normalize/normalize.cpp

$(IntermediateDirectory)/src_normalize_normalizeF.cpp$(ObjectSuffix): src/normalize/normalizeF.cpp $(IntermediateDirectory)/src_normalize_normalizeF.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/normalize/normalizeF.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_normalize_normalizeF.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_normalize_normalizeF.cpp$(DependSuffix): src/normalize/normalizeF.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_normalize_normalizeF.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_normalize_normalizeF.cpp$(DependSuffix) -MM src/normalize/normalizeF.cpp

$(IntermediateDirectory)/src_normalize_normalizeF.cpp$(PreprocessSuffix): src/normalize/normalizeF.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_normalize_normalizeF.cpp$(PreprocessSuffix) src/normalize/normalizeF.cpp

$(IntermediateDirectory)/src_normalize_normalize_XY.cpp$(ObjectSuffix): src/normalize/normalize_XY.cpp $(IntermediateDirectory)/src_normalize_normalize_XY.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/normalize/normalize_XY.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_normalize_normalize_XY.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_normalize_normalize_XY.cpp$(DependSuffix): src/normalize/normalize_XY.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_normalize_normalize_XY.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_normalize_normalize_XY.cpp$(DependSuffix) -MM src/normalize/normalize_XY.cpp

$(IntermediateDirectory)/src_normalize_normalize_XY.cpp$(PreprocessSuffix): src/normalize/normalize_XY.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_normalize_normalize_XY.cpp$(PreprocessSuffix) src/normalize/normalize_XY.cpp

$(IntermediateDirectory)/src_combine_combine.cpp$(ObjectSuffix): src/combine/combine.cpp $(IntermediateDirectory)/src_combine_combine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/combine/combine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_combine_combine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_combine_combine.cpp$(DependSuffix): src/combine/combine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_combine_combine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_combine_combine.cpp$(DependSuffix) -MM src/combine/combine.cpp

$(IntermediateDirectory)/src_combine_combine.cpp$(PreprocessSuffix): src/combine/combine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_combine_combine.cpp$(PreprocessSuffix) src/combine/combine.cpp

$(IntermediateDirectory)/src_combine_combineF.cpp$(ObjectSuffix): src/combine/combineF.cpp $(IntermediateDirectory)/src_combine_combineF.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/combine/combineF.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_combine_combineF.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_combine_combineF.cpp$(DependSuffix): src/combine/combineF.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_combine_combineF.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_combine_combineF.cpp$(DependSuffix) -MM src/combine/combineF.cpp

$(IntermediateDirectory)/src_combine_combineF.cpp$(PreprocessSuffix): src/combine/combineF.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_combine_combineF.cpp$(PreprocessSuffix) src/combine/combineF.cpp

$(IntermediateDirectory)/src_combine_combine_XY.cpp$(ObjectSuffix): src/combine/combine_XY.cpp $(IntermediateDirectory)/src_combine_combine_XY.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/combine/combine_XY.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_combine_combine_XY.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_combine_combine_XY.cpp$(DependSuffix): src/combine/combine_XY.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_combine_combine_XY.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_combine_combine_XY.cpp$(DependSuffix) -MM src/combine/combine_XY.cpp

$(IntermediateDirectory)/src_combine_combine_XY.cpp$(PreprocessSuffix): src/combine/combine_XY.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_combine_combine_XY.cpp$(PreprocessSuffix) src/combine/combine_XY.cpp

$(IntermediateDirectory)/src_compress_compress.cpp$(ObjectSuffix): src/compress/compress.cpp $(IntermediateDirectory)/src_compress_compress.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/compress/compress.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_compress_compress.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_compress_compress.cpp$(DependSuffix): src/compress/compress.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_compress_compress.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_compress_compress.cpp$(DependSuffix) -MM src/compress/compress.cpp

$(IntermediateDirectory)/src_compress_compress.cpp$(PreprocessSuffix): src/compress/compress.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_compress_compress.cpp$(PreprocessSuffix) src/compress/compress.cpp

$(IntermediateDirectory)/src_compress_compressF.cpp$(ObjectSuffix): src/compress/compressF.cpp $(IntermediateDirectory)/src_compress_compressF.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/compress/compressF.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_compress_compressF.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_compress_compressF.cpp$(DependSuffix): src/compress/compressF.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_compress_compressF.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_compress_compressF.cpp$(DependSuffix) -MM src/compress/compressF.cpp

$(IntermediateDirectory)/src_compress_compressF.cpp$(PreprocessSuffix): src/compress/compressF.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_compress_compressF.cpp$(PreprocessSuffix) src/compress/compressF.cpp

$(IntermediateDirectory)/src_compress_compress_XY.cpp$(ObjectSuffix): src/compress/compress_XY.cpp $(IntermediateDirectory)/src_compress_compress_XY.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/compress/compress_XY.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_compress_compress_XY.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_compress_compress_XY.cpp$(DependSuffix): src/compress/compress_XY.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_compress_compress_XY.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_compress_compress_XY.cpp$(DependSuffix) -MM src/compress/compress_XY.cpp

$(IntermediateDirectory)/src_compress_compress_XY.cpp$(PreprocessSuffix): src/compress/compress_XY.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_compress_compress_XY.cpp$(PreprocessSuffix) src/compress/compress_XY.cpp

$(IntermediateDirectory)/src_match_to_ref_match_to_ref.cpp$(ObjectSuffix): src/match_to_ref/match_to_ref.cpp $(IntermediateDirectory)/src_match_to_ref_match_to_ref.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/match_to_ref/match_to_ref.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_match_to_ref_match_to_ref.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_match_to_ref_match_to_ref.cpp$(DependSuffix): src/match_to_ref/match_to_ref.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_match_to_ref_match_to_ref.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_match_to_ref_match_to_ref.cpp$(DependSuffix) -MM src/match_to_ref/match_to_ref.cpp

$(IntermediateDirectory)/src_match_to_ref_match_to_ref.cpp$(PreprocessSuffix): src/match_to_ref/match_to_ref.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_match_to_ref_match_to_ref.cpp$(PreprocessSuffix) src/match_to_ref/match_to_ref.cpp

$(IntermediateDirectory)/src_cnvnator_cnvnator.cpp$(ObjectSuffix): src/cnvnator/cnvnator.cpp $(IntermediateDirectory)/src_cnvnator_cnvnator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/cnvnator/cnvnator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_cnvnator_cnvnator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_cnvnator_cnvnator.cpp$(DependSuffix): src/cnvnator/cnvnator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_cnvnator_cnvnator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_cnvnator_cnvnator.cpp$(DependSuffix) -MM src/cnvnator/cnvnator.cpp

$(IntermediateDirectory)/src_cnvnator_cnvnator.cpp$(PreprocessSuffix): src/cnvnator/cnvnator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_cnvnator_cnvnator.cpp$(PreprocessSuffix) src/cnvnator/cnvnator.cpp

$(IntermediateDirectory)/src_cnvnator_cnvnatorsplit.cpp$(ObjectSuffix): src/cnvnator/cnvnatorsplit.cpp $(IntermediateDirectory)/src_cnvnator_cnvnatorsplit.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/cnvnator/cnvnatorsplit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_cnvnator_cnvnatorsplit.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_cnvnator_cnvnatorsplit.cpp$(DependSuffix): src/cnvnator/cnvnatorsplit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_cnvnator_cnvnatorsplit.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_cnvnator_cnvnatorsplit.cpp$(DependSuffix) -MM src/cnvnator/cnvnatorsplit.cpp

$(IntermediateDirectory)/src_cnvnator_cnvnatorsplit.cpp$(PreprocessSuffix): src/cnvnator/cnvnatorsplit.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_cnvnator_cnvnatorsplit.cpp$(PreprocessSuffix) src/cnvnator/cnvnatorsplit.cpp

$(IntermediateDirectory)/src_cnvnator_cnvnator_female.cpp$(ObjectSuffix): src/cnvnator/cnvnator_female.cpp $(IntermediateDirectory)/src_cnvnator_cnvnator_female.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/cnvnator/cnvnator_female.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_cnvnator_cnvnator_female.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_cnvnator_cnvnator_female.cpp$(DependSuffix): src/cnvnator/cnvnator_female.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_cnvnator_cnvnator_female.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_cnvnator_cnvnator_female.cpp$(DependSuffix) -MM src/cnvnator/cnvnator_female.cpp

$(IntermediateDirectory)/src_cnvnator_cnvnator_female.cpp$(PreprocessSuffix): src/cnvnator/cnvnator_female.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_cnvnator_cnvnator_female.cpp$(PreprocessSuffix) src/cnvnator/cnvnator_female.cpp

$(IntermediateDirectory)/src_Interface_mcnvgui.cpp$(ObjectSuffix): src/Interface/mcnvgui.cpp $(IntermediateDirectory)/src_Interface_mcnvgui.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/remus/RESEARCH_SLL/MetaCNV_v1.2/src/Interface/mcnvgui.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Interface_mcnvgui.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Interface_mcnvgui.cpp$(DependSuffix): src/Interface/mcnvgui.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Interface_mcnvgui.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Interface_mcnvgui.cpp$(DependSuffix) -MM src/Interface/mcnvgui.cpp

$(IntermediateDirectory)/src_Interface_mcnvgui.cpp$(PreprocessSuffix): src/Interface/mcnvgui.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Interface_mcnvgui.cpp$(PreprocessSuffix) src/Interface/mcnvgui.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


